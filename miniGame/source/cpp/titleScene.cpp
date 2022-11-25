//=============================================================================
//
// タイトルシーン処理 [titleScene.cpp]
// Author : 鶴間俊樹
// Author : 佐藤瞭平
//
//=============================================================================
#include "titleScene.h"
#include "manager.h"
#include "renderer.h"
#include "titleCamera.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "object2D.h"
#include "selectMenu2D.h"
#include "objectModel.h"
#include "PresetSetEffect.h"
#include "meshwall.h"
#include "object_player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ESC_POS (D3DXVECTOR3(120.0f, 40.0f, 0.0f))
#define ESC_WIDTH (200.0f)
#define ESC_HEIGHT (40.0f)
#define NEXT_LOGO_POS (D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 550.0f, 0.0f))
#define NEXT_LOGO_WIDTH (400.0f)
#define NEXT_LOGO_HEIGHT (100.0f)

#define TITLE_SCENE_PLAYER_DIFFER			(150.0f)			//プレイヤー間の距離
#define TITLE_SCENE_PLAYER_POS_Z			(3000.0f)			//プレイヤーの位置Z
#define TITLE_SCENE_PLAYER_MOVE				(30.0f)				//プレイヤーの移動量

#define TITLE_SCENE_CLOUD_NUM					(1)											//雲の数
#define TITLE_SCENE_CLOUD_POS					(D3DXVECTOR3(0.0f, 0.0f, 1000.0f))			//雲の位置
#define TITLE_SCENE_CLOUD_SIZE					(2000.0f)									//雲のサイズ
#define TITLE_SCENE_CLOUD_MESH_NUM				(2)											//メッシュを敷き詰める数
#define TITLE_SCENE_CLOUD_MOVE_SPEED			(0.00035f)									//テクスチャを動かす速さ
#define TITLE_SCENE_CLOUD_MOVE_SPEED_INTERVAL	(0.00025f)									//次の雲のテクスチャを動かす速さの間隔
#define TITLE_SCENE_CLOUD_COLOR					(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f))			//雲の色

#define TITLE_FOG_COLOR							(D3DXCOLOR(0.1f, 0.0f, 0.2f, 1.0f))			//フォグの色
#define TITLE_BACK_BUFF							(D3DXCOLOR(0.1f, 0.7f, 1.0f, 1.0f))			//バックバッファーの色

#define TITLE_SCENE_END_CAMERA_ROT_X			(10.0f)		//カメラの最終的な向きX
#define TITLE_SCENE_END_CAMERA_POS_Z			(-550.0f)	//カメラの最終的な位置Z
#define TITLE_SCENE_END_CAMERA_POS_Y			(20.0f)		//カメラの最終的な位置Y

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CObject2D * CTitleScene::m_pNext = nullptr;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTitleScene::CTitleScene() :m_fMaxCol(1.0f), m_nDivideNum(2), m_nMaxColTime(3)
{	
	m_bPushKey = false;
	m_nFadeTime = 120;
	m_nColorTime = 0;
	memset(m_pPlayerModel, NULL, sizeof(m_pPlayerModel[MAX_OBJECT_PLAYER_NUM]));
	m_pCloud.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleScene::~CTitleScene()
{

}

//=============================================================================
// タイトルシーンの初期化処理
//=============================================================================
void CTitleScene::Init(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//カメラの設定
	if (pManager != nullptr) pManager->SetCamera(CTitleCamera::Create());

	//------------------------------
	//ライトの初期設定
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ライトの射影変換
	//ライトのプロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 200.0f, 1800.0f);

	D3DXMATRIX mtxLightView;   // ライトビュー変換
	D3DXVECTOR3 posLightV = D3DXVECTOR3(0.0f, 1200.0f, -1000.0f);	//ライトの視点の位置
	D3DXVECTOR3 posLightR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//ライトの注視点の位置
	D3DXVECTOR3 vecLight = -D3DXVECTOR3(posLightV - posLightR);		//ライトのベクトル
	D3DXVec3Normalize(&vecLight, &vecLight);	//ベクトルを正規化
	//ライトのビューマトリックスを生成
	D3DXMatrixLookAtLH(&mtxLightView, &posLightV, &D3DXVECTOR3(posLightV + vecLight), &D3DXVECTOR3(0, 1, 0));
	//シェーダのライトを設定
	if (pRenderer != nullptr) {
		pRenderer->SetEffectLightMatrixView(mtxLightView);
		pRenderer->SetEffectLightVector(D3DXVECTOR4(vecLight, 1.0f));
		pRenderer->SetEffectLightMatrixProj(mtxLightProj);
	}

	//------------------------------
	//フォグの初期設定
	//------------------------------
	if (pRenderer != nullptr) {
		pRenderer->SetEffectFogEnable(true);
		pRenderer->SetEffectFogColor(TITLE_FOG_COLOR);
		pRenderer->SetEffectFogRange(200.0f, 4000.0f);
		//バックバッファをフォグの色に合わせる
		pRenderer->SetBackBuffColor(TITLE_BACK_BUFF);
	}	

	//雲の生成
	for (int nCntCloud = 0; nCntCloud < TITLE_SCENE_CLOUD_NUM; nCntCloud++)
	{
		m_pCloud.push_back(CMeshwall::Create(TITLE_SCENE_CLOUD_POS, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			                                 TITLE_SCENE_CLOUD_MESH_NUM, TITLE_SCENE_CLOUD_MESH_NUM, TITLE_SCENE_CLOUD_SIZE, TITLE_SCENE_CLOUD_SIZE,
			                                 CTexture::TEXTURE_TYPE::MESH_CLOUD));
		//加算合成をする
		m_pCloud[nCntCloud]->SetAlphaBlend(true);
		//描画順の設定
		m_pCloud[nCntCloud]->SetDrawPriority(CObject::DRAW_PRIORITY::CLEAR);
		//ライトをオフにする
		m_pCloud[nCntCloud]->SetLight(false);
		//色の設定
		m_pCloud[nCntCloud]->SetColor(TITLE_SCENE_CLOUD_COLOR);
	}

	//床の生成
	CMeshwall::Create(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(D3DX_PI*0.5f, 0.0f, 0.0f), 8, 4, 1000.0f, 500.0f,
		              CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);

	//プレイヤーの生成
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		const float fDist = TITLE_SCENE_PLAYER_DIFFER;	//プレイヤー同士の距離
		D3DXVECTOR3 posModel = D3DXVECTOR3(fDist * (-MAX_OBJECT_PLAYER_NUM / 2.0f) + fDist / 2.0f + nIdxPlayer * fDist,
			                               0.0f,
			                               TITLE_SCENE_PLAYER_POS_Z);	//左端から並べる
		m_pPlayerModel[nIdxPlayer] = CObjectModel::Create(CModel::MODELTYPE::OBJ_CAR, posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		if (m_pPlayerModel == nullptr) continue;
		CModel* pModel = m_pPlayerModel[nIdxPlayer]->GetPtrModel();

		if (pModel == nullptr) continue;
		D3DXCOLOR colModel;	//モデルのマテリアル色
		switch (nIdxPlayer)
		{
		case 0:
			colModel = OBJECT_PLAYER_COLOR_1P;
			break;
		case 1:
			colModel = OBJECT_PLAYER_COLOR_2P;
			break;
		case 2:
			colModel = OBJECT_PLAYER_COLOR_3P;
			break;
		case 3:
			colModel = OBJECT_PLAYER_COLOR_4P;
			break;
		default:
			colModel = OBJECT_PLAYER_COLOR_1P;
			break;
		}
		pModel->SetMaterialDiffuse(colModel, 0);	//マテリアルの設定
	}


	// ゲーム終了UI
	CObject2D::Create(ESC_POS, CTexture::TEXTURE_TYPE::QUIT_GAME, ESC_WIDTH, ESC_HEIGHT);
	// タイトルロゴ
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::TITLE_LOGO, SCREEN_WIDTH, SCREEN_HEIGHT);
	// 次に行かせるロゴ
	m_pNext = CObject2D::Create(NEXT_LOGO_POS, CTexture::TEXTURE_TYPE::TEXT_GAMESTART, NEXT_LOGO_WIDTH, NEXT_LOGO_HEIGHT);

	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_TITLE);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_TITLE);
	}

	//オブジェクトのポーズが無いように設定
	CObject::SetUpdatePauseLevel(0);


#ifdef _DEBUG
	//Zバッファテクスチャの表示
	CObject2D* pZBuff = CObject2D::Create(D3DXVECTOR3(70.0f, 120.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, 100.0f, 100.0f);
	if (pZBuff != nullptr) {
		pZBuff->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
		pZBuff->SetUseZBuffTexture(true);
	}
#endif

}

//=============================================================================
// タイトルシーンの終了処理
//=============================================================================
void CTitleScene::Uninit(void) {	

	//シーンの終了処理
	CScene::Uninit();

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//音の停止
	if (pSound != nullptr) {
		pSound->StopSound();
	}
}

//=============================================================================
// タイトルシーンの更新処理
//=============================================================================
void CTitleScene::Update(void) {		
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	CInput* pInput = nullptr;	//入力デバイスへのポインタ
	CFade* pFade = nullptr;		//フェードへのポインタ
	CSound* pSound = nullptr;	//サウンドへのポインタ
	D3DXCOLOR col = m_pNext->GetColor(); // 次に行かせるロゴの色の取得

	//雲の処理
	Cloud();

	//プレイヤーモデルの処理
	PlayerModel();

	//カメラの処理
	Camera();

	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
		//フェードの取得
		pFade = pManager->GetFade();
		//サウンドの取得
		pSound = pManager->GetSound();
	}

	if (pInput == nullptr || pFade == nullptr) return;

	//決定キーを押したとき
	if (pInput->GetTrigger(CInput::CODE::SELECT, 0) && !m_bPushKey) 
	{		
		//フェード中だった場合
		if (pFade->GetFade()) 
		{
			//フェードをスキップ
			pFade->SkipFade();
		}		
		else
		{
			// 押されたとき
			m_bPushKey = true;

			//決定音の再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
		}
	}

	//決定キーが押されたとき
	if (m_bPushKey)
	{		
		// 色の状態を取得
		m_bCol = ChangeColTime(m_bCol);
		// 点滅処理(状態遷移)
		if (m_bCol)
		{
			// α値の変更
			col.a = m_fMaxCol;		
		}
		else
		{
			// α値の変更
			col.a = m_fMaxCol / m_nDivideNum;			
		}		
		// 次に行かせるロゴの色の設定
		m_pNext->SetColor(col);

		// 遷移する時間が0より小さくなっていたら
		if (m_nFadeTime < 0)
		{
			// 0を代入してマイナス値にならないようにする
			m_nFadeTime = 0;	
			//シーン遷移開始			
			if (pFade != nullptr) pFade->SetFade(CScene::SCENE_TYPE::SELECT_GAME, 0.02f, 60);
		}
		else
		{
			//遷移する時間が0より小さくなっていたら
			m_nFadeTime--;
		}
	}
}

//=============================================================================
// タイトルシーンの色が変わる時間の処理
//=============================================================================
bool CTitleScene::ChangeColTime(bool bCol)
{
	// 色を変える時間を加算
	m_nColorTime++;

	// 時間が最大時間に行ったら
	if (m_nColorTime > m_nMaxColTime)
	{
		// bCol = trueのとき
		if (bCol)
		{
			bCol = false;
		}
		else // それ以外
		{
			bCol = true;
		}
		// 色を変える時間を初期化
		m_nColorTime = 0;
	}

	return bCol;
}

//=============================================================================
//雲の処理
//=============================================================================
void CTitleScene::Cloud()
{
	for (int nCntCloud = 0; nCntCloud < TITLE_SCENE_CLOUD_NUM; nCntCloud++)
	{
		if (m_pCloud[nCntCloud] == nullptr)
		{
			continue;
		}

		//テクスチャ座標移動処理
		m_pCloud[nCntCloud]->SetMoveTex(TITLE_SCENE_CLOUD_MOVE_SPEED + TITLE_SCENE_CLOUD_MOVE_SPEED_INTERVAL * nCntCloud, 0.0f);
	}
}

//=============================================================================
//プレイヤーのモデルの処理
//=============================================================================
void CTitleScene::PlayerModel()
{
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		if (m_pPlayerModel == nullptr || !m_bPushKey) continue;

		//生成されていたら且つスタートボタンが押されていたら

		//位置取得
		D3DXVECTOR3 pos = m_pPlayerModel[nIdxPlayer]->GetPos();
		//移動量を設定
		pos.z += -TITLE_SCENE_PLAYER_MOVE;
		//位置設定
		m_pPlayerModel[nIdxPlayer]->SetPos(pos);

		//---------------------------------
		//煙
		CPresetEffect::SetEffect3D(0, pos, {}, {});
		//---------------------------------
	}
}

//=============================================================================
//カメラの処理
//=============================================================================
void CTitleScene::Camera()
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//カメラの取得
	CCamera* pCamera = nullptr;
	if (pManager != nullptr) pCamera = pManager->GetCamera();

	//カメラが生成されている且つ決定ボタンが押されていたら
	if (pCamera == nullptr || !m_bPushKey) return;

	//向き取得
	D3DXVECTOR3 rot = pCamera->GetRot();

	if (rot.x <= TITLE_SCENE_END_CAMERA_ROT_X * (D3DX_PI / 180.0f)) return;

	//向きを動かす
	rot.x -= 0.01f;
	//既定の値以下になったら
	if (rot.x < TITLE_SCENE_END_CAMERA_ROT_X * (D3DX_PI / 180.0f)) rot.x = TITLE_SCENE_END_CAMERA_ROT_X * (D3DX_PI / 180.0f);

	//向き設定
	pCamera->SetRot(rot);
}