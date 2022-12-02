//=============================================================================
//
// タイトルシーン処理 [titleScene.cpp]
// Author : 鶴間俊樹
// Author : 佐藤瞭平
// Author : 加藤瑞葵
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
#include "PresetSetEffect.h"
#include "meshwall.h"
#include "skydome.h"

#include "effect.h"

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

#define CLOUD_POS					(D3DXVECTOR3(0.0f, -5.0f, 2000.0f))			//雲の位置
#define CLOUD_RADIUS				(5000.0f)									//雲の半径
#define CLOUD_MESH_NUM				(12)										//メッシュを敷き詰める数
#define CLOUD_ROTATE_SPEED			(0.0015f)									//雲の回転量
#define CLOUD_COLOR					(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f))			//雲の色

#define TITLE_FOG_COLOR							(D3DXCOLOR(1.0f, 0.9f, 0.3f, 1.0f))			//フォグの色
#define TITLE_BACK_BUFF							(D3DXCOLOR(0.1f, 0.7f, 1.0f, 1.0f))			//バックバッファーの色

#define TITLE_SCENE_END_CAMERA_ROT_X			(10.0f)			//カメラの最終的な向きX
#define TITLE_SCENE_END_CAMERA_POS_Z			(-550.0f)		//カメラの最終的な位置Z
#define TITLE_SCENE_END_CAMERA_POS_Y			(20.0f)			//カメラの最終的な位置Y
#define TITLE_SCENE_CAMERA_ROTATE_SPEED			(0.01f)			//カメラの回転スピード

#define TITLE_SCENE_THE_FINAL_LOGO_SIZE_X			(654.0f)			//ザファイナルロゴのサイズX
#define TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y			(74.0f)				//ザファイナルロゴのサイズY
#define TITLE_SCENE_THE_FINAL_LOGO_INIT_SIZE_X		(654.0f * 20.0f)	//ザファイナルロゴの初期サイズX
#define TITLE_SCENE_THE_FINAL_LOGO_INIT_SIZE_Y		(74.0f * 20.0f)		//ザファイナルロゴの初期サイズY
#define TITLE_SCENE_THE_FINAL_LOGO_POS_Y			(365.0f)			//ザファイナルロゴの位置Y
#define TITLE_SCENE_THE_FINAL_LOGO_CREATE_COUNTER	(20)				//ザファイナルロゴの生成するタイミング
#define TITLE_SCENE_THE_FINAL_LOGO_DEC_SIZE			(0.89f)				//ザファイナルロゴのサイズ減算量

#define TITLE_SCENE_CHARA_LOGO_SIZE				(170.0f)			//文字ロゴのサイズ
#define TITLE_SCENE_CHARA_LOGO_INIT_SIZE		(170.0f * 10.0f)	//文字ロゴの初期サイズ
#define TITLE_SCENE_CHARA_LOGO_POS_Y			(220.0f)			//文字ロゴの位置Y
#define TITLE_SCENE_CHARA_LOGO_POS_X			(15.0f)				//文字ロゴの位置X調整値
#define TITLE_SCENE_CHARA_DEC_SIZE				(0.91f)				//文字ロゴのサイズ減算量
#define TITLE_SCENE_CHARA_CREATE_COUNTER		(30)				//文字ロゴの生成するタイミング

#define TITLE_SCENE_EXPLOSION_LOGO_POS				(D3DXVECTOR3(850.0f, 174.0f, 0.0f))		//爆発UIの位置
#define TITLE_SCENE_EXPLOSION_LOGO_SIZE_X			(362.0f)								//爆発UIのサイズX
#define TITLE_SCENE_EXPLOSION_LOGO_SIZE_Y			(316.0f)								//爆発UIのサイズY
#define TITLE_SCENE_EXPLOSION_LOGO_SIZE_MIN			(0.9f)									//爆発UIのサイズ最小値
#define TITLE_SCENE_EXPLOSION_LOGO_SIZE_MAX			(1.1f)									//爆発UIのサイズ最大値
#define TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE		(0.001f)								//爆発UIのスケール加算量
#define TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE_MIN	(0.99f)									//爆発UIのスケール加算量最小値
#define TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE_MAX	(1.01f)									//爆発UIのスケール加算量最大値

#define TITLE_SCENE_CAR_LOGO_ADD_MOVE		(0.2f)				//車ロゴの移動量加算量
#define TITLE_SCENE_CAR_LOGO_ADD_MOVE_MAX	(30.0f)				//車ロゴの移動量最大値
#define TITLE_SCENE_CAR_LOGO_LEFT_MOVE		(22.8f)				//車ロゴの左から来るときの移動量初速
#define TITLE_SCENE_CAR_LOGO_STOP_COUNTER	(180)				//車ロゴが停止している時間

#define TITLE_SCENE_FLOOR_POS_Z		(-1000.0f)			//床の位置Z
#define TITLE_SCENE_FLOOR_NUM		(8)					//床の分割数
#define TITLE_SCENE_FLOOR_SIZE		(1000.0f)			//床のサイズ
	
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
	memset(m_pTitleLogoChara, NULL, sizeof(m_pTitleLogoChara[TITLE_LOGO_CHARA_NUM]));
	m_pTheFinalLogo = nullptr;
	m_pTitleLogo = nullptr;
	m_nFrameCounter = 0;
	m_phase = PHASE::NONE;
	m_fBoundMove = 0.0f;
	m_pExplosionLogo = nullptr;
	m_bExplosionAddSize = false;
	m_pTitleLogoCar = nullptr;
	m_bCarLogoRight = false;
	m_fCarLogoMove = 0.0f;
	m_bCreateAllLogo = false;
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

	//変数初期化
	memset(m_pTitleLogoChara, NULL, sizeof(m_pTitleLogoChara[TITLE_LOGO_CHARA_NUM]));
	m_pTheFinalLogo = nullptr;
	m_nFrameCounter = 0;
	m_phase = PHASE::CHARACTOR_LOGO;
	m_pTitleLogo = nullptr;
	m_fBoundMove = 1.02f;
	m_pExplosionLogo = nullptr;
	m_bExplosionAddSize = true;
	m_pTitleLogoCar = nullptr;
	m_bCarLogoRight = true;
	m_fCarLogoMove = 0.0f;
	m_bCreateAllLogo = false;

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
		pRenderer->SetEffectFogRange(200.0f, 12000.0f);
		//バックバッファをフォグの色に合わせる
		pRenderer->SetBackBuffColor(TITLE_BACK_BUFF);
	}	

	CEffect::Create(D3DXVECTOR3(0.0f, 1000.0f, 0.0f), CEffect::EFFECT_TYPE::SUN, 600.0f, 600.0f, true);

	////雲の生成
	CSkyDome::Create(CLOUD_POS, CLOUD_MESH_NUM, CLOUD_MESH_NUM, CLOUD_RADIUS, CLOUD_ROTATE_SPEED);

	//床の生成
	CMeshwall::Create(D3DXVECTOR3(0.0f, 0.0f, TITLE_SCENE_FLOOR_POS_Z), D3DXVECTOR3(D3DX_PI* 0.5f, 0.0f, 0.0f),
		              TITLE_SCENE_FLOOR_NUM, TITLE_SCENE_FLOOR_NUM, TITLE_SCENE_FLOOR_SIZE, TITLE_SCENE_FLOOR_SIZE,
		              CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);

	//砂丘生成
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_DUNE_00, D3DXVECTOR3(1000.0f, -100.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_DUNE_01, D3DXVECTOR3(-1000.0f, -100.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_DUNE_02, D3DXVECTOR3(-1200.0f, -100.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//サボテン生成
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_CACTUS_00, D3DXVECTOR3(600.0f, 0.0f, 1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_CACTUS_01, D3DXVECTOR3(400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_CACTUS_02, D3DXVECTOR3(-400.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//木の生成
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_TREE_00, D3DXVECTOR3(-300.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//空の鳥
	CObjectModel* pBird = CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_BIRD, D3DXVECTOR3(0.0f, 2000.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	if (pBird != nullptr) {
		pBird->SetRotSpeed(D3DXVECTOR3(0.0f, 0.015f, 0.0f));
		CModel* pBirdModel = pBird->GetPtrModel();
		if (pBirdModel != nullptr) {
			pBirdModel->SetPos(D3DXVECTOR3(2000.0f, 0.0f, 0.0f));
		}
	}

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
		//スペキュラーの設定
		pModel->SetMaterialSpecular(colModel / 2.0f + D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), 0);
		pModel->SetMaterialPower(2.0f, 0);
	}


	// ゲーム終了UI
	CObject2D::Create(ESC_POS, CTexture::TEXTURE_TYPE::QUIT_GAME, ESC_WIDTH, ESC_HEIGHT);

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

	//フェーズによって処理分け
	switch (m_phase)
	{
	case CTitleScene::PHASE::CHARACTOR_LOGO:
		//文字のロゴの処理
		CharactorLogo();
		break;
	case CTitleScene::PHASE::THE_FINAL_LOGO:
		//ザファイナルのロゴの処理
		TheFinalLogo();
		break;
	case CTitleScene::PHASE::BOUND_LOGO:
		//ザロゴのバウンドの処理
		BoundLogo();
		break;
	case CTitleScene::PHASE::STOP_TITLE_LOGO:
		//タイトルロゴ停止の処理
		StopTitleLogo();
		break;
	default:
		break;
	}

	//プレイヤーモデルの処理
	PlayerModel();

	//カメラの処理
	Camera();

	//ロゴ消す処理
	DeleteLogo();

	//全てのロゴを生成する処理
	if (CreateAllLogo()) return;

	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
		//フェードの取得
		pFade = pManager->GetFade();
		//サウンドの取得
		pSound = pManager->GetSound();
	}

	if (pInput == nullptr || pFade == nullptr || !m_bCreateAllLogo) return;

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
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ENGINE);

			m_nFrameCounter = 0;
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

		m_nFrameCounter++;

		if (m_nFrameCounter == 1)
		{
			CManager* pManager = CManager::GetManager();	//マネージャーの取得
			if (pManager == nullptr) return;
			//サウンドの取得
			CSound* pSound = nullptr;
			if (pManager != nullptr) pSound = pManager->GetSound();
			//音を再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_TITLE_CAR);
		}
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
	rot.x -= TITLE_SCENE_CAMERA_ROTATE_SPEED;
	//既定の値以下になったら
	if (rot.x < TITLE_SCENE_END_CAMERA_ROT_X * (D3DX_PI / 180.0f)) rot.x = TITLE_SCENE_END_CAMERA_ROT_X * (D3DX_PI / 180.0f);

	//向き設定
	pCamera->SetRot(rot);
}

//=============================================================================
//文字のロゴの処理
//=============================================================================
void CTitleScene::CharactorLogo()
{
	//カウンターを加算
	m_nFrameCounter++;

	if (m_nFrameCounter < TITLE_SCENE_CHARA_CREATE_COUNTER) return;

	m_nFrameCounter = TITLE_SCENE_CHARA_CREATE_COUNTER;

	for (int nCntCharaLogo = 0; nCntCharaLogo < TITLE_LOGO_CHARA_NUM; nCntCharaLogo++)
	{
		//最初以外
		if (nCntCharaLogo > 0)
		{
			//サイズを取得
			D3DXVECTOR3 beforeSize = m_pTitleLogoChara[nCntCharaLogo - 1]->GetSize();

			if (beforeSize.x != TITLE_SCENE_CHARA_LOGO_SIZE || beforeSize.y != TITLE_SCENE_CHARA_LOGO_SIZE) return;
		}

		//生成されていなかったら
		if (m_pTitleLogoChara[nCntCharaLogo] == nullptr)
		{
			//生成する
			m_pTitleLogoChara[nCntCharaLogo] =
				CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f -
				((TITLE_SCENE_CHARA_LOGO_SIZE - TITLE_SCENE_CHARA_LOGO_POS_X) * (TITLE_LOGO_CHARA_NUM / 2.0f)) + ((TITLE_SCENE_CHARA_LOGO_SIZE - TITLE_SCENE_CHARA_LOGO_POS_X) / 2.0f) +
					(TITLE_SCENE_CHARA_LOGO_SIZE - TITLE_SCENE_CHARA_LOGO_POS_X) * nCntCharaLogo,
					TITLE_SCENE_CHARA_LOGO_POS_Y,
					0.0f),
					static_cast<CTexture::TEXTURE_TYPE>(static_cast<int>(CTexture::TEXTURE_TYPE::TITLE_LOGO_CHARACTOR_00) + nCntCharaLogo),
					TITLE_SCENE_CHARA_LOGO_INIT_SIZE, TITLE_SCENE_CHARA_LOGO_INIT_SIZE);
		}

		//サイズを取得
		D3DXVECTOR3 size = m_pTitleLogoChara[nCntCharaLogo]->GetSize();

		if (size.x > TITLE_SCENE_CHARA_LOGO_SIZE || size.y > TITLE_SCENE_CHARA_LOGO_SIZE)
		{
			//小さくする
			size *= TITLE_SCENE_CHARA_DEC_SIZE;
		}

		if (size.x < TITLE_SCENE_CHARA_LOGO_SIZE) 
		{ 
			size.x = TITLE_SCENE_CHARA_LOGO_SIZE;
		}
		if (size.y < TITLE_SCENE_CHARA_LOGO_SIZE)
		{
			size.y = TITLE_SCENE_CHARA_LOGO_SIZE;

			CManager* pManager = CManager::GetManager();	//マネージャーの取得
			if (pManager == nullptr) return;
			//サウンドの取得
			CSound* pSound = nullptr;
			if (pManager != nullptr) pSound = pManager->GetSound();
			//音を再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_TITLE_CHAR_CREATE);
		}
		//サイズ設定
		m_pTitleLogoChara[nCntCharaLogo]->SetSize(size);
	}

	if (m_pTitleLogoChara[TITLE_LOGO_CHARA_NUM - 1] == nullptr) return;
	//生成されていたら
	
	//サイズを取得
	D3DXVECTOR3 size = m_pTitleLogoChara[TITLE_LOGO_CHARA_NUM - 1]->GetSize();
	if (size.x != TITLE_SCENE_CHARA_LOGO_SIZE || size.y != TITLE_SCENE_CHARA_LOGO_SIZE) return;

	//次のフェーズにする
	m_phase = PHASE::THE_FINAL_LOGO;

	//初期化
	m_nFrameCounter = 0;
}

//=============================================================================
//ザファイナルのロゴの処理
//=============================================================================
void CTitleScene::TheFinalLogo()
{
	//カウンターを加算
	m_nFrameCounter++;

	if (m_nFrameCounter < TITLE_SCENE_THE_FINAL_LOGO_CREATE_COUNTER) return;

	m_nFrameCounter = TITLE_SCENE_THE_FINAL_LOGO_CREATE_COUNTER;

	//生成されていなかったら
	if (m_pTheFinalLogo == nullptr)
	{
		//爆発ロゴ
		m_pExplosionLogo = CObject2D::Create(TITLE_SCENE_EXPLOSION_LOGO_POS, CTexture::TEXTURE_TYPE::TITLE_LOGO_EXPLOSION,
			                                 TITLE_SCENE_EXPLOSION_LOGO_SIZE_X, TITLE_SCENE_EXPLOSION_LOGO_SIZE_Y);

		//車ロゴ
		m_pTitleLogoCar = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::TITLE_LOGO_CAR,
			                                SCREEN_WIDTH, SCREEN_HEIGHT);

		// タイトルロゴ
		m_pTitleLogo = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::TITLE_LOGO,
			                             SCREEN_WIDTH, SCREEN_HEIGHT);

		//ザファイナルロゴ
		m_pTheFinalLogo = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TITLE_SCENE_THE_FINAL_LOGO_POS_Y, 0.0f),
			                                CTexture::TEXTURE_TYPE::TITLE_LOGO_THE_FINAL,
		                                    TITLE_SCENE_THE_FINAL_LOGO_INIT_SIZE_X, TITLE_SCENE_THE_FINAL_LOGO_INIT_SIZE_Y);

		for (int nCntCharaLogo = 0; nCntCharaLogo < TITLE_LOGO_CHARA_NUM; nCntCharaLogo++)
		{
			//生成されていなかったら
			if (m_pTitleLogoChara[nCntCharaLogo] == nullptr) continue;
			//消す
			m_pTitleLogoChara[nCntCharaLogo]->Uninit();
			m_pTitleLogoChara[nCntCharaLogo] = nullptr;
		}
	}

	//サイズを取得
	D3DXVECTOR3 size = m_pTheFinalLogo->GetSize();

	//小さくする
	size *= TITLE_SCENE_THE_FINAL_LOGO_DEC_SIZE;
	if (size.x < TITLE_SCENE_THE_FINAL_LOGO_SIZE_X) size.x = TITLE_SCENE_THE_FINAL_LOGO_SIZE_X;
	if (size.y < TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y) size.y = TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y;
	//サイズ設定
	m_pTheFinalLogo->SetSize(size);

	if (size.x != TITLE_SCENE_THE_FINAL_LOGO_SIZE_X || size.y != TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y) return;
	//フェーズをバウンドにする
	m_phase = PHASE::BOUND_LOGO;
	//初期化
	m_nFrameCounter = 0;

	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//音を再生
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_TITLE_LOGO_CREATE);
}

//=============================================================================
//ロゴのバウンドの処理
//=============================================================================
void CTitleScene::BoundLogo()
{
	if (m_pTitleLogo != nullptr)
	{
		//サイズを取得
		D3DXVECTOR3 size = m_pTitleLogo->GetSize();
		//小さくする
		size *= m_fBoundMove;
		if (size.x < SCREEN_WIDTH) size.x = SCREEN_WIDTH;
		if (size.y < SCREEN_HEIGHT) size.y = SCREEN_HEIGHT;
		//サイズ設定
		m_pTitleLogo->SetSize(size);
	}

	if (m_pTheFinalLogo != nullptr)
	{
		//サイズを取得
		D3DXVECTOR3 size = m_pTheFinalLogo->GetSize();
		//小さくする
		size *= m_fBoundMove;
		if (size.x < TITLE_SCENE_THE_FINAL_LOGO_SIZE_X) size.x = TITLE_SCENE_THE_FINAL_LOGO_SIZE_X;
		if (size.y < TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y) size.y = TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y;
		//サイズ設定
		m_pTheFinalLogo->SetSize(size);
	}

	m_fBoundMove -= 0.001f;

	if (m_pTheFinalLogo->GetSize().x == TITLE_SCENE_THE_FINAL_LOGO_SIZE_X && m_pTheFinalLogo->GetSize().y == TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y &&
		m_pTitleLogo->GetSize().x == SCREEN_WIDTH && m_pTitleLogo->GetSize().y == SCREEN_HEIGHT)
	{
		//フェーズをタイトルロゴ停止にする
		m_phase = PHASE::STOP_TITLE_LOGO;
		m_fBoundMove = 1.0f;
		//全てのロゴを生成した状態にする
		m_bCreateAllLogo = true;
	}
}

//=============================================================================
//タイトルロゴ停止
//=============================================================================
void CTitleScene::StopTitleLogo()
{
	//爆発ロゴの処理
	ExplosionLogo();

	//車ロゴの処理
	CarLogo();
}

//=============================================================================
//爆発ロゴの処理
//=============================================================================
void CTitleScene::ExplosionLogo()
{
	if (m_pExplosionLogo == nullptr) return;

	//サイズを取得
	D3DXVECTOR3 size = m_pExplosionLogo->GetSize();

	//サイズを変える
	size *= m_fBoundMove;

	if (size.x < TITLE_SCENE_EXPLOSION_LOGO_SIZE_X * TITLE_SCENE_EXPLOSION_LOGO_SIZE_MIN) m_bExplosionAddSize = true;
	else if (size.x > TITLE_SCENE_EXPLOSION_LOGO_SIZE_X * TITLE_SCENE_EXPLOSION_LOGO_SIZE_MAX) m_bExplosionAddSize = false;

	//サイズ設定
	m_pExplosionLogo->SetSize(size);

	//スケール加算量
	float fAddScalse = TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE;
	//小さくするときは逆にする
	if (!m_bExplosionAddSize) fAddScalse *= -1.0f;
	//スケールを加算
	m_fBoundMove += fAddScalse;

	if (m_fBoundMove > TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE_MAX) m_fBoundMove = TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE_MAX;
	else if (m_fBoundMove < TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE_MIN) m_fBoundMove = TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE_MIN;
}

//=============================================================================
//車ロゴの処理
//=============================================================================
void CTitleScene::CarLogo()
{
	if (m_bPushKey) return;

	if (m_pTitleLogoCar == nullptr) return;

	if (m_nFrameCounter == 0)
	{
		//位置取得
		D3DXVECTOR3 pos = m_pTitleLogoCar->GetPos();
		//加算量
		float fAddMove = TITLE_SCENE_CAR_LOGO_ADD_MOVE;
		//左から来るときは減速するようにする
		if(!m_bCarLogoRight) fAddMove *= -1.0f;

		//移動量加算
		m_fCarLogoMove += fAddMove;

		//移動量最大値と最小値を設定
		if (m_fCarLogoMove > TITLE_SCENE_CAR_LOGO_ADD_MOVE_MAX) m_fCarLogoMove = TITLE_SCENE_CAR_LOGO_ADD_MOVE_MAX;
		else if(m_fCarLogoMove < 0.0f) m_fCarLogoMove = 0.0f;

		//動かす
		pos.x += m_fCarLogoMove;

		if (pos.x >= SCREEN_WIDTH + SCREEN_WIDTH / 2.0f)
		{
			//位置をずらす
			pos.x = -SCREEN_WIDTH + SCREEN_WIDTH / 2.0f;
			//右にいない状態にする
			m_bCarLogoRight = false;
			//ギリギリ止まれるような速度にする
			m_fCarLogoMove = TITLE_SCENE_CAR_LOGO_LEFT_MOVE;
		}

		if (!m_bCarLogoRight && pos.x > SCREEN_WIDTH / 2.0f)
		{
			pos.x = SCREEN_WIDTH / 2.0f;
			m_nFrameCounter++;
		}

		//位置設定
		m_pTitleLogoCar->SetPos(pos);

		return;
	}

	m_nFrameCounter++;
	if (m_nFrameCounter < TITLE_SCENE_CAR_LOGO_STOP_COUNTER) return;

	m_nFrameCounter = 0;
	//右にいる状態にする
	m_bCarLogoRight = true;
	//0にする
	m_fCarLogoMove = 0.0f;
}

//=============================================================================
//全てのロゴを生成する処理
//=============================================================================
bool CTitleScene::CreateAllLogo()
{
	if (m_bCreateAllLogo) return false;
	//ロゴが全て生成されていないなら

	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	CInput* pInput = nullptr;	//入力デバイスへのポインタ
	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
	}
	if (pInput == nullptr) return false;

	if (!pInput->GetTrigger(CInput::CODE::SELECT, 0)) return false;

	//決定キーを押したとき

	for (int nCntCharaLogo = 0; nCntCharaLogo < TITLE_LOGO_CHARA_NUM; nCntCharaLogo++)
	{
		//生成されていなかったら
		if (m_pTitleLogoChara[nCntCharaLogo] == nullptr) continue;
		//消す
		m_pTitleLogoChara[nCntCharaLogo]->Uninit();
		m_pTitleLogoChara[nCntCharaLogo] = nullptr;
	}

	//生成されていなかったら
	if (m_pExplosionLogo == nullptr)
	{
		//爆発ロゴ
		m_pExplosionLogo = CObject2D::Create(TITLE_SCENE_EXPLOSION_LOGO_POS, CTexture::TEXTURE_TYPE::TITLE_LOGO_EXPLOSION,
			                                 TITLE_SCENE_EXPLOSION_LOGO_SIZE_X, TITLE_SCENE_EXPLOSION_LOGO_SIZE_Y);
	}

	//生成されていなかったら
	if (m_pTitleLogoCar == nullptr)
	{
		//車ロゴ
		m_pTitleLogoCar = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::TITLE_LOGO_CAR,
			                                SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	//生成されていなかったら
	if (m_pTitleLogo == nullptr)
	{
		// タイトルロゴ
		m_pTitleLogo = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::TITLE_LOGO,
			                             SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	else
	{
		//サイズ設定
		m_pTitleLogo->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	}

	//生成されていなかったら
	if (m_pTheFinalLogo == nullptr)
	{
		//ザファイナルロゴ
		m_pTheFinalLogo = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TITLE_SCENE_THE_FINAL_LOGO_POS_Y, 0.0f),
			                                CTexture::TEXTURE_TYPE::TITLE_LOGO_THE_FINAL,
		                                    TITLE_SCENE_THE_FINAL_LOGO_SIZE_X, TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y);
	}
	else
	{
		//サイズ設定
		m_pTheFinalLogo->SetSize(D3DXVECTOR3(TITLE_SCENE_THE_FINAL_LOGO_SIZE_X, TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y, 0.0f));
	}

	//全てのロゴが生成されている状態にする
	m_bCreateAllLogo = true;

	//フェーズをタイトルロゴ停止にする
	m_phase = PHASE::STOP_TITLE_LOGO;

	//変数初期化
	m_fBoundMove = 1.0f;
	m_nFrameCounter = 0;

	return true;
}

//=============================================================================
//ロゴ消す処理
//=============================================================================
void CTitleScene::DeleteLogo()
{
	if (!m_bPushKey) return;

	//決定ボタンが押されていたら

	//生成されていたら
	if (m_pExplosionLogo != nullptr)
	{
		//位置取得
		D3DXVECTOR3 pos = m_pExplosionLogo->GetPos();
		//サイズ取得
		D3DXVECTOR3 size = m_pExplosionLogo->GetSize();
		//動かす
		pos.y -= 20.0f;
		//位置設定
		m_pExplosionLogo->SetPos(pos);

		if (pos.y <= 0.0f - size.y / 2.0f)
		{
			//消す
			m_pExplosionLogo->Uninit();
			m_pExplosionLogo = nullptr;
		}
	}

	//生成されていたら
	if (m_pTitleLogoCar != nullptr)
	{
		//位置取得
		D3DXVECTOR3 pos = m_pTitleLogoCar->GetPos();
		//サイズ取得
		D3DXVECTOR3 size = m_pTitleLogoCar->GetSize();
		//動かす
		pos.y -= 20.0f;
		pos.x = SCREEN_WIDTH / 2.0f;
		//位置設定
		m_pTitleLogoCar->SetPos(pos);

		if (pos.y <= 0.0f - size.y / 2.0f)
		{
			//消す
			m_pTitleLogoCar->Uninit();
			m_pTitleLogoCar = nullptr;
		}
	}

	//生成されていたら
	if (m_pTitleLogo != nullptr)
	{
		//位置取得
		D3DXVECTOR3 pos = m_pTitleLogo->GetPos();
		//サイズ取得
		D3DXVECTOR3 size = m_pTitleLogo->GetSize();
		//動かす
		pos.y -= 20.0f;
		//位置設定
		m_pTitleLogo->SetPos(pos);

		if (pos.y <= 0.0f - size.y / 2.0f)
		{
			//消す
			m_pTitleLogo->Uninit();
			m_pTitleLogo = nullptr;
		}
	}

	//生成されていたら
	if (m_pTheFinalLogo != nullptr)
	{
		//位置取得
		D3DXVECTOR3 pos = m_pTheFinalLogo->GetPos();
		//サイズ取得
		D3DXVECTOR3 size = m_pTheFinalLogo->GetSize();
		//動かす
		pos.y -= 20.0f;
		//位置設定
		m_pTheFinalLogo->SetPos(pos);

		if (pos.y <= 0.0f - size.y / 2.0f)
		{
			//消す
			m_pTheFinalLogo->Uninit();
			m_pTheFinalLogo = nullptr;
		}
	}
}
