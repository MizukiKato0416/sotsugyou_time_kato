//=============================================================================
//
// リザルトシーン処理 [resultScene.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "resultScene.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
#include "object2D.h"
#include "objectModelUI.h"
#include "object_player.h"
#include "ToScreen.h"
#include "gameCamera.h"
#include "gameScene.h"
#include "next_button.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define RESULT_SCENE_POINT_UI_SIZE		(D3DXVECTOR3(325.0f * 0.5f, 128.0f* 0.5f, 0.0f))	//ポイントUIのサイズ
#define RESULT_SCENE_POINT_UI_ADD_ALPHA	(0.08f)												//ポイントUIのα値加算値
#define RESULT_SCENE_POINT_UI_ADD_POS_Y	(3.0f)												//ポイントUIの位置加算値
#define RESULT_SCENE_POINT_UI_COUNTER	(150)												//ポイントUIの見えるようになるまでのカウント

#define RESULT_SCENE_CHANGE_SCENE_COUNTER		(180)			//シーン遷移ができるようになるまでのカウンター
#define RESULT_SCENE_CHANGE_SCENE_COUNTER_WOLF	(210)			//シーン遷移ができるようになるまでのカウンター人狼モード

#define RESULT_SCENE_PLAYER_INIT_POS_Z		(950.0f)	//プレイヤーの初期位置Z
#define RESULT_SCENE_PLAYER_MOVE			(25.0f)		//プレイヤーの移動量
#define RESULT_SCENE_PLAYER_ROTATE_SPEED	(0.05f)		//プレイヤーの回転速度

#define RESULT_SCENE_NEXT_BUTTON_POS			(D3DXVECTOR3(1150.0f, 670.0f, 0.0f))	//次に進むボタンの位置
#define RESULT_SCENE_NEXT_BUTTON_SIZE			(D3DXVECTOR3(70.0f, 70.0f, 0.0f))		//次に進むボタンのサイズ
#define RESULT_SCENE_NEXT_BUTTON_COUNTER		(15)									//次に進むボタンの見えるようになるまでのカウンター
#define RESULT_SCENE_NEXT_BUTTON_DEC_ALPHA		(0.015f)								//次に進むボタンのα値減算量

#define RESULT_SCENE_RESULT_UI_SIZE_X			(1230.0f * 0.7f)	//結果発表UIのサイズX
#define RESULT_SCENE_RESULT_UI_SIZE_Y			(184.0f * 0.7f)		//結果発表UIのサイズY
#define RESULT_SCENE_RESULT_UI_POS_Y			(100.0f)			//結果発表UIの位置Y

#define RESULT_SCENE_RANKING_UI_SIZE_X			(150.0f)			//順位UIのサイズ
#define RESULT_SCENE_RANKING_UI_SIZE_Y			(150.0f)			//順位UIのサイズ
#define RESULT_SCENE_RANKING_UI_POS_Y			(200.0f)			//順位UIの位置調整値

#define RESULT_SCENE_BG_MOVE_SPEED		(D3DXVECTOR2(0.001f, 0.001f))		//背景の移動速度


//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CResultScene::CResultScene()
{
	m_pBg = nullptr;
	memset(m_apPointUi, NULL, sizeof(m_apPointUi[MAX_OBJECT_PLAYER_NUM]));
	memset(m_pPlayerModel, NULL, sizeof(m_pPlayerModel[MAX_OBJECT_PLAYER_NUM]));
	m_nFrameCounter = 0;
	m_pNexButton = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResultScene::~CResultScene()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void CResultScene::Init(void) {

	//変数初期化
	m_nFrameCounter = 0;
	m_pNexButton = nullptr;


	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//カメラの設定
	if (pManager != nullptr) pManager->SetCamera(CGameCamera::Create());	//なにか一つカメラが無いと描画されないのでとりあえずゲームカメラ

	//------------------------------
	//ライトの初期設定
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ライトの射影変換
	//ライトのプロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 100.0f, 3000.0f);

	D3DXMATRIX mtxLightView;   // ライトビュー変換
	D3DXVECTOR3 posLightV = D3DXVECTOR3(200.0f, 2000.0f, -200.0f);	//ライトの視点の位置
	D3DXVECTOR3 posLightR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//ライトの注視点の位置
	D3DXVECTOR3 vecLight = -D3DXVECTOR3(posLightV - posLightR);	//ライトのベクトル
	D3DXVec3Normalize(&vecLight, &vecLight);	//ベクトルを正規化
	//ライトのビューマトリックスを生成
	D3DXMatrixLookAtLH(&mtxLightView, &posLightV, &posLightR, &D3DXVECTOR3(0, 0, 1));
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
		pRenderer->SetEffectFogEnable(false);
	}

	//------------------------------
	//オブジェクトの初期設定
	//------------------------------
	m_pBg = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::BG_RESULT, SCREEN_WIDTH, SCREEN_HEIGHT);

	//------------------------------
	//ランキング表示
	//------------------------------
	int aPlayerRank[MAX_OBJECT_PLAYER_NUM];	//プレイヤーのランクの配列 インデックスはプレイヤーのインデックスと対応

	//プレイヤーランクの取得
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		aPlayerRank[nIdxPlayer] = CGameScene::GetRanking(nIdxPlayer);
	}

	//プレイヤーの表示順の設定
	int aOrderPlayer[MAX_OBJECT_PLAYER_NUM];
	memset(aOrderPlayer, -1, sizeof(aOrderPlayer));
	int nCurRank = 1;	//現在のランク
	int nIdxOrder = 0;	//順番のインデックス

	while (nCurRank <= MAX_OBJECT_PLAYER_NUM)
	{
		bool bDecision = false;	//順番の決定

		for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
		{
			if (aOrderPlayer[nIdxPlayer] != -1) continue;	//順番が決定されていた場合除外

			//ランクが一致していた場合
			if (aPlayerRank[nIdxPlayer] == nCurRank) {
				aOrderPlayer[nIdxPlayer] = nIdxOrder;	//順番の設定
				nIdxOrder++;	//順番の加算
				bDecision = true;	//順番の決定
				break;
			}
		}
		//ランクが一致しなかった場合
		if (!bDecision) {
			nCurRank++;	//ランクの加算
		}
	}

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		//aOrderPlayer[nIdxPlayer] = nIdxPlayer;


		const float fDist = 180.0f;	//プレイヤー同士の距離
		D3DXVECTOR3 posModel = D3DXVECTOR3(fDist * (-MAX_OBJECT_PLAYER_NUM / 2.0f) + fDist / 2.0f + (aOrderPlayer[nIdxPlayer]) * fDist, 0.0f, RESULT_SCENE_PLAYER_INIT_POS_Z);	//左端から1位を並べる
		m_pPlayerModel[nIdxPlayer] = CObjectModelUI::Create(CModel::MODELTYPE::OBJ_CAR, posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		if (m_pPlayerModel == nullptr) continue;
		m_pPlayerModel[nIdxPlayer]->SetViewCamera(D3DXVECTOR3(0.0f, 400.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		CModel* pModel = m_pPlayerModel[nIdxPlayer]->GetPtrModel();

		//ランキングのUI生成
		D3DXVECTOR3 posRankUI = WorldToScreen(D3DXVECTOR3(posModel.x, posModel.y, 0.0f), m_pPlayerModel[nIdxPlayer]->GetViewMatrix());
		CObject2D* pRankUI = CObject2D::Create(posRankUI + D3DXVECTOR3(0.0f, RESULT_SCENE_RANKING_UI_POS_Y, 0.0f),
			                                   CTexture::TEXTURE_TYPE::PLAYER_NUM_1, RESULT_SCENE_RANKING_UI_SIZE_X, RESULT_SCENE_RANKING_UI_SIZE_Y);

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


		//順位UIのテクスチャ設定
		if (pRankUI == nullptr) continue;
		pRankUI->SetTexType(static_cast<CTexture::TEXTURE_TYPE>(static_cast<int> (CTexture::TEXTURE_TYPE::RANKING_1) + (aPlayerRank[nIdxPlayer] - 1)));

		//人狼モードでなかったら
		if (!CGameScene::GetWereWolfMode()) continue;

		//ポイントUIを生成
		m_apPointUi[nIdxPlayer] = CObject2D::Create(posRankUI - D3DXVECTOR3(0.0f, 100.0f, 0.0f), CTexture::TEXTURE_TYPE::ADD_POINT_40, 
			                                        RESULT_SCENE_POINT_UI_SIZE.x, RESULT_SCENE_POINT_UI_SIZE.y);
		m_apPointUi[nIdxPlayer]->SetTexType(static_cast<CTexture::TEXTURE_TYPE>
			                               (static_cast<int> (CTexture::TEXTURE_TYPE::ADD_POINT_40) + (aPlayerRank[nIdxPlayer] - 1)));
		m_apPointUi[nIdxPlayer]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	//結果発表UIの生成
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, RESULT_SCENE_RESULT_UI_POS_Y, 0.0f), CTexture::TEXTURE_TYPE::RESULT_UI,
		              RESULT_SCENE_RESULT_UI_SIZE_X, RESULT_SCENE_RESULT_UI_SIZE_Y);

	//------------------------------
	//BGMの再生
	//------------------------------
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CResultScene::Uninit(void) {
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
// 更新処理
//=============================================================================
void CResultScene::Update(void) {

	//フレームカウント処理
	FrameCounter();

	//次に進むボタンUIの処理
	NextButton();

	//背景処理
	Bg();

	//プレイヤーの処理
	Player();

	//ポイントUIの処理
	PointUI();

	//遷移処理
	Fade();
}

//=============================================================================
//ポイントUIの処理
//=============================================================================
void CResultScene::PointUI()
{
	//人狼モードでなかったら
	if (!CGameScene::GetWereWolfMode())
	{
		return;
	}

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		//生成されていなかったら
		if (m_apPointUi[nIdxPlayer] == nullptr) continue;

		//既定の値になっていなかったら
		if (m_nFrameCounter <= RESULT_SCENE_POINT_UI_COUNTER) continue;

		//薄くなっていない状態なら
		if (m_apPointUi[nIdxPlayer]->GetColor().a == 1.0f) continue;

		//カラー取得
		D3DXCOLOR col = m_apPointUi[nIdxPlayer]->GetColor();
		//濃くする
		col.a += RESULT_SCENE_POINT_UI_ADD_ALPHA;
		if (col.a > 1.0f)
		{
			col.a = 1.0f;

			//マネージャーの取得
			CManager* pManager = CManager::GetManager();
			//サウンドの取得
			CSound* pSound = nullptr;
			if (pManager != nullptr) pSound = pManager->GetSound();
			//音を再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_POINT_1);
		}
		//カラー設定
		m_apPointUi[nIdxPlayer]->SetColor(col);

		//位置取得
		D3DXVECTOR3 pos = m_apPointUi[nIdxPlayer]->GetPos();
		//動かす
		pos.y -= RESULT_SCENE_POINT_UI_ADD_POS_Y;
		//位置設定
		m_apPointUi[nIdxPlayer]->SetPos(pos);
	}
}

//=============================================================================
//プレイヤーの処理
//=============================================================================
void CResultScene::Player()
{
	int aPlayerRank[MAX_OBJECT_PLAYER_NUM];	//プレイヤーのランクの配列 インデックスはプレイヤーのインデックスと対応

	//プレイヤーランクの取得
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		aPlayerRank[nIdxPlayer] = CGameScene::GetRanking(nIdxPlayer);
	}
	//プレイヤーの表示順の設定
	int aOrderPlayer[MAX_OBJECT_PLAYER_NUM];
	memset(aOrderPlayer, -1, sizeof(aOrderPlayer));
	int nCurRank = 1;	//現在のランク
	int nIdxOrder = 0;	//順番のインデックス

	while (nCurRank <= MAX_OBJECT_PLAYER_NUM)
	{
		bool bDecision = false;	//順番の決定

		for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
		{
			if (aOrderPlayer[nIdxPlayer] != -1) continue;	//順番が決定されていた場合除外

			//ランクが一致していた場合
			if (aPlayerRank[nIdxPlayer] == nCurRank) {
				aOrderPlayer[nIdxPlayer] = nIdxOrder;	//順番の設定
				nIdxOrder++;	//順番の加算
				bDecision = true;	//順番の決定
				break;
			}
		}
		//ランクが一致しなかった場合
		if (!bDecision) {
			nCurRank++;	//ランクの加算
		}
	}

	for (int nIdxPlayer = MAX_OBJECT_PLAYER_NUM - 1; nIdxPlayer >= 0; nIdxPlayer--)
	{
		for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
		{
			if (aOrderPlayer[nCntPlayer] != nIdxPlayer) continue;

			if (m_pPlayerModel[nCntPlayer] == nullptr) continue;

			//生成されていたら

			//位置取得
			D3DXVECTOR3 pos = m_pPlayerModel[nCntPlayer]->GetPos();

			//位置Zが0なら
			if (pos.z == 0.0f)
			{
				m_pPlayerModel[nCntPlayer]->SetRotSpeed(D3DXVECTOR3(RESULT_SCENE_PLAYER_ROTATE_SPEED, RESULT_SCENE_PLAYER_ROTATE_SPEED, RESULT_SCENE_PLAYER_ROTATE_SPEED));
				continue;
			}

			//移動させる
			pos.z -= RESULT_SCENE_PLAYER_MOVE;
			//0より小さかったら0にする
			if (pos.z < 0.0f) pos.z = 0.0f;
			//位置設定
			m_pPlayerModel[nCntPlayer]->SetPos(pos);
			return;
		}
	}
}

//=============================================================================
//次に進むUI処理
//=============================================================================
void CResultScene::NextButton()
{
	int nChangeSceneCounter = RESULT_SCENE_CHANGE_SCENE_COUNTER;

	//人狼モードなら
	if (CGameScene::GetWereWolfMode()) nChangeSceneCounter = RESULT_SCENE_CHANGE_SCENE_COUNTER_WOLF;

	//既定の値になっていなかったら
	if (m_nFrameCounter < nChangeSceneCounter) return;

	if (m_pNexButton != nullptr) return;

	//次へUIの生成
	m_pNexButton = CNextButton::Create(RESULT_SCENE_NEXT_BUTTON_POS, RESULT_SCENE_NEXT_BUTTON_SIZE,
		                               CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_3, RESULT_SCENE_NEXT_BUTTON_COUNTER,
		                               RESULT_SCENE_NEXT_BUTTON_DEC_ALPHA);
}

//=============================================================================
//背景処理
//=============================================================================
void CResultScene::Bg()
{
	if (m_pBg == nullptr) return;

	//背景を動かす
	m_pBg->SetMoveTex(RESULT_SCENE_BG_MOVE_SPEED.x, RESULT_SCENE_BG_MOVE_SPEED.y);
}

//=============================================================================
//遷移処理
//=============================================================================
void CResultScene::Fade()
{
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//現在の入力デバイスの取得
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;

	if (pInput->GetTrigger(CInput::CODE::SELECT, 0)) {
		//フェードの取得
		CFade* pFade = pManager->GetFade();		//フェードへのポインタ
		if (pFade == nullptr) return;

		if (pFade->GetChangeFade()) return;

		//シーン遷移するまでのカウント
		float fChangeSceneCount = RESULT_SCENE_CHANGE_SCENE_COUNTER;
		//遷移先
		CScene::SCENE_TYPE sceneType = CScene::SCENE_TYPE::SELECT_GAME;

		//人狼モードなら
		if (CGameScene::GetWereWolfMode())
		{
			fChangeSceneCount = RESULT_SCENE_CHANGE_SCENE_COUNTER_WOLF;
			sceneType = CScene::SCENE_TYPE::FIND_WOLF;
		}

		if (m_nFrameCounter < fChangeSceneCount) return;
		if (pFade != nullptr) pFade->SetFade(sceneType, 0.02f, 60);

		//サウンドの取得
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音を再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_OK);
	}
}

//=============================================================================
//フレームカウント処理
//=============================================================================
void CResultScene::FrameCounter()
{
	m_nFrameCounter++;

	//既定の値以下だったら
	if (m_nFrameCounter <= RESULT_SCENE_CHANGE_SCENE_COUNTER_WOLF) return;

	m_nFrameCounter = RESULT_SCENE_CHANGE_SCENE_COUNTER_WOLF;
}
