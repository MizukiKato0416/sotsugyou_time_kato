//=============================================================================
//
// 人狼決定処理 [find_wolf_scene.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "find_wolf_scene.h"
#include "manager.h"
#include "renderer.h"
#include "find_wolf_camera.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "object2D.h"
#include "object_player.h"
#include "objectModelUI.h"
#include "ToScreen.h"
#include "score_ui.h"
#include "score.h"
#include "gameScene.h"
#include "timer.h"
#include "coverDisplay.h"
#include "next_button.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FIND_WOLF_SCENE_SELECT_ICON_SIZE_X			(440.0f * 0.2f)						//選択アイコンのサイズX
#define FIND_WOLF_SCENE_SELECT_ICON_SIZE_Y			(314.0f * 0.2f)						//選択アイコンのサイズY
#define FIND_WOLF_SCENE_SELECT_ICON_POS_Y			(130.0f)							//選択アイコンの位置Y
#define FIND_WOLF_SCENE_SELECT_ICON_POS_X_DIFFER	(40.0f)								//選択アイコンの位置Xの間隔
#define FIND_WOLF_SCENE_SELECT_ICON_DECIDE_COLOR	(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f))	//選択アイコンの決定時のカラー
#define FIND_WOLF_SCENE_SELECT_ICON_MOVE			(0.08f)								//選択アイコンの移動量
#define FIND_WOLF_SCENE_SELECT_ICON_ADD_MOVE_POS	((rand() % 101 + 100) / 10.0f)		//選択アイコンが加速できる範囲

#define FIND_WOLF_SCENE_SELECT_TIME					(10)		//選択できる時間
#define FIND_WOLF_SCENE_SELECT_ALL_INTERVAL			(90)		//全員が選択してから次のフェーズに行くまでの間隔

#define FIND_WOLF_SCENE_SCORE_UI_SCALE				(D3DXVECTOR3(0.5f, 0.5f, 0.5f))		//スコアUIのスケール
#define FIND_WOLF_SCENE_SCORE_UI_POS_Y				(50.0f)								//スコアUIの位置Y
#define FIND_WOLF_SCENE_SCORE_UI_POS_X				(140.0f)							//スコアUIの位置X
#define FIND_WOLF_SCENE_SCORE_UI_POS_DIFFER_Y		(90.0f)								//スコアUIの位置Yの距離

#define FIND_WOLF_SCENE_PLAYER_DIFFER				(150.0f)			//プレイヤー間の距離

#define FIND_WOLF_SCENE_PLAYER_INDEX_UI_POS_Y		(100.0f)			//プレイヤーインデックスUIの位置Y
#define FIND_WOLF_SCENE_PLAYER_INDEX_UI_SIZE_X		(201.0f * 0.5f)		//プレイヤーインデックスUIのサイズX
#define FIND_WOLF_SCENE_PLAYER_INDEX_UI_SIZE_Y		(181.0f * 0.5f)		//プレイヤーインデックスUIのサイズY

#define FIND_WOLF_SCENE_PLAYER_WAIT_TIME			(240)				//結果発表の時間

#define FIND_WOLF_SCENE_POINT_UI_SIZE_X				(80.0f)				//ポイントUIのサイズX
#define FIND_WOLF_SCENE_POINT_UI_SIZE_Y				(80.0f)				//ポイントUIのサイズY
#define FIND_WOLF_SCENE_POINT_UI_POS_Y				(150.0f)			//ポイントUIの位置Y
#define FIND_WOLF_SCENE_POINT_UI_POS_X_DIFFER		(40.0f)				//ポイントUIの位置Xの間隔
#define FIND_WOLF_SCENE_POINT_UI_DEC_ALPHA			(0.05f)				//ポイントUIのα値減算量
#define FIND_WOLF_SCENE_POINT_UI_MOVE				(2.0f)				//ポイントUIの移動量
#define FIND_WOLF_SCENE_POINT_UI_DEC_COUNTER		(60)				//ポイントUIが消え始めるまでの時間

#define STENCIL_CIRCLE_SIZE (280.0f)	//ステンシルマスクのサイズ
#define STENCIL_CIRCLE_SPEED (24.0f)	//ステンシルマスクの速度

#define FIND_WOLF_SCENE_NEXT_BUTTON_POS			(D3DXVECTOR3(960.0f, 670.0f, 0.0f))		//次に進むボタンの位置
#define FIND_WOLF_SCENE_NEXT_BUTTON_SIZE		(D3DXVECTOR3(60.0f, 60.0f, 0.0f))		//次に進むボタンのサイズ
#define FIND_WOLF_SCENE_NEXT_BUTTON_COUNTER		(15)									//次に進むボタンの見えるようになるまでのカウンター
#define FIND_WOLF_SCENE_NEXT_BUTTON_DEC_ALPHA	(0.015f)								//次に進むボタンのα値減算量

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CFindWolfScene::CFindWolfScene()
{	
	memset(m_apScoreUi, NULL, sizeof(m_apScoreUi[MAX_OBJECT_PLAYER_NUM]));
	memset(m_pSelectIcon, NULL, sizeof(m_pSelectIcon[MAX_OBJECT_PLAYER_NUM]));
	memset(m_pPointUi, NULL, sizeof(m_pPointUi[MAX_OBJECT_PLAYER_NUM]));
	memset(m_select, 0, sizeof(m_select[MAX_OBJECT_PLAYER_NUM]));
	memset(m_bSelectFloat, false, sizeof(m_bSelectFloat[MAX_OBJECT_PLAYER_NUM]));
	m_phase = PHASE::NONE;
	m_pTutorial = nullptr;
	m_nFrameCounter = 0;
	m_bAddPoint = false;

	m_pWaitBlack = nullptr;
	m_pCircleStencilMask = nullptr;

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		m_aPosPlayer2D[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fSelectMove[nCntPlayer] = 0.0f;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CFindWolfScene::~CFindWolfScene()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void CFindWolfScene::Init(void) {

	//変数初期化
	m_phase = PHASE::TUTORIAL_1;
	memset(m_pSelectIcon, NULL, sizeof(m_pSelectIcon[MAX_OBJECT_PLAYER_NUM]));
	memset(m_pPointUi, NULL, sizeof(m_pPointUi[MAX_OBJECT_PLAYER_NUM]));
	memset(m_select, 0, sizeof(m_select[MAX_OBJECT_PLAYER_NUM]));
	memset(m_bSelectFloat, false, sizeof(m_bSelectFloat[MAX_OBJECT_PLAYER_NUM]));
	m_nFrameCounter = 0;
	m_bAddPoint = false;

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		m_fSelectMove[nCntPlayer] = 0.0f;
	}

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//カメラの設定
	if (pManager != nullptr) pManager->SetCamera(CFindWolfCamera::Create());

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
		pRenderer->SetEffectFogColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		pRenderer->SetEffectFogRange(800.0f, 4500.0f);
		//バックバッファをフォグの色に合わせる
		pRenderer->SetBackBuffColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}

	//------------------------------
	//オブジェクトの初期設定
	//------------------------------

	//スタジアムの生成
	CObjectModel::Create(CModel::MODELTYPE::OBJ_ATTACK_CAR_STAGE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		const float fDist = FIND_WOLF_SCENE_PLAYER_DIFFER;	//プレイヤー同士の距離
		D3DXVECTOR3 posModel = D3DXVECTOR3(fDist * (-MAX_OBJECT_PLAYER_NUM / 2.0f) + fDist / 2.0f + nIdxPlayer * fDist, 0.0f, 0.0f);	//左端から並べる
		CObjectModel* pPlayerModel = CObjectModel::Create(CModel::MODELTYPE::OBJ_CAR, posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		if (pPlayerModel == nullptr) continue;
		CModel* pModel = pPlayerModel->GetPtrModel();

		m_aPosPlayer2D[nIdxPlayer] = WorldToScreen(posModel);

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

		//プレイヤーのインデックスのUIを生成
		CObject2D *pPlayerIndexUi = CObject2D::Create(m_aPosPlayer2D[nIdxPlayer] + D3DXVECTOR3(0.0f, FIND_WOLF_SCENE_PLAYER_INDEX_UI_POS_Y, 0.0f),
			                                          CTexture::TEXTURE_TYPE::PLAYER_NUM_1,
			                                          FIND_WOLF_SCENE_PLAYER_INDEX_UI_SIZE_X, FIND_WOLF_SCENE_PLAYER_INDEX_UI_SIZE_Y);
		pPlayerIndexUi->SetTexType(static_cast<CTexture::TEXTURE_TYPE>
			                       (static_cast<int> (CTexture::TEXTURE_TYPE::PLAYER_NUM_1) + nIdxPlayer));

		//スコアの位置
		D3DXVECTOR3 scorePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		if (nIdxPlayer < MAX_OBJECT_PLAYER_NUM / 2)
		{
			scorePos = D3DXVECTOR3(FIND_WOLF_SCENE_SCORE_UI_POS_X,
				                   FIND_WOLF_SCENE_SCORE_UI_POS_Y + FIND_WOLF_SCENE_SCORE_UI_POS_DIFFER_Y * nIdxPlayer ,
				                   0.0f);
		}
		else
		{
			scorePos = D3DXVECTOR3(SCREEN_WIDTH - FIND_WOLF_SCENE_SCORE_UI_POS_X,
				                   FIND_WOLF_SCENE_SCORE_UI_POS_Y + FIND_WOLF_SCENE_SCORE_UI_POS_DIFFER_Y * (nIdxPlayer - 2),
				                   0.0f);
		}

		//スコアUIの生成 
		m_apScoreUi[nIdxPlayer] = CScoreUi::Create(scorePos, FIND_WOLF_SCENE_SCORE_UI_SCALE, nIdxPlayer + 1);
		//スコアの設定
		m_apScoreUi[nIdxPlayer]->GetScore()->SetScore(40 - (CGameScene::GetRanking(nIdxPlayer) - 1) * 10);
	}

	//説明UIの生成
	m_pTutorial = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                            CTexture::TEXTURE_TYPE::WOLF_FIND_TUTORIAL_1, SCREEN_WIDTH, SCREEN_HEIGHT);

	//次へUIの生成
	m_pNexButton = CNextButton::Create(FIND_WOLF_SCENE_NEXT_BUTTON_POS, FIND_WOLF_SCENE_NEXT_BUTTON_SIZE,
		                               CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_3, FIND_WOLF_SCENE_NEXT_BUTTON_COUNTER,
		                               FIND_WOLF_SCENE_NEXT_BUTTON_DEC_ALPHA);

	//------------------------------
	//BGMの再生
	//------------------------------
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME);
	}

#ifdef _DEBUG
	//Zバッファテクスチャの表示
	CObject2D* pZBuff = CObject2D::Create(D3DXVECTOR3(70.0f, 120.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, 100.0f, 100.0f);
	if (pZBuff != nullptr) {
		pZBuff->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
		pZBuff->SetUseZBuffTexture(true);
	}

#endif

	CGameScene::SetWereWolfPlayerIndex(2);
}

//=============================================================================
// 終了処理
//=============================================================================
void CFindWolfScene::Uninit(void) {	

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
void CFindWolfScene::Update(void) {		
	
	//処理分け
	switch (m_phase)
	{
	case CFindWolfScene::PHASE::TUTORIAL_1:
		Tutorial1();		//説明1処理
		break;
	case CFindWolfScene::PHASE::TUTORIAL_2:
		Tutorial2();		//説明2処理
		break;
	case CFindWolfScene::PHASE::WOLF_DECIDE:
		WolfDecide();		//人狼決定処理
		break;
	case CFindWolfScene::PHASE::TUTORIAL_3:
		Tutorial3();		//説明3処理
		break;
	case CFindWolfScene::PHASE::WAIT:
		Wait();				//待つ処理
		break;
	case CFindWolfScene::PHASE::ANSWER:
		Answer();			//回答処理
		break;
	case CFindWolfScene::PHASE::TUTORIAL_4:
		Tutorial4();		//説明4処理
		break;
	case CFindWolfScene::PHASE::DEC_WOLF_POINT:
		DecWolfPoint();		//人狼のポイントマイナス処理
		break;
	case CFindWolfScene::PHASE::ADD_PLAYER_POINT:
		AddPlayerPoint();	//人狼以外のポイント加算処理
		break;
	case CFindWolfScene::PHASE::DEC_PLAYER_POINT:
		DecPlayerPoint();	//人狼以外のポイントマイナス処理
		break;
	case CFindWolfScene::PHASE::ADD_WOLF_POINT:
		AddWolfPoint();		//人狼のポイント加算処理
		break;
	case CFindWolfScene::PHASE::FINISH:
		Finish();			//終了処理
		break;
	default:
		break;
	}

}

//=============================================================================
//説明1
//=============================================================================
void CFindWolfScene::Tutorial1()
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
	}

	//ボタンを押したら
	if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT), 0))
	{
		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		//サウンドの取得
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音を再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_OK);

		//次のフェーズにする
		m_phase = PHASE::TUTORIAL_2;

		//テクスチャを変える
		m_pTutorial->SetTexType(CTexture::TEXTURE_TYPE::WOLF_FIND_TUTORIAL_2);
	}
}

//=============================================================================
//説明2
//=============================================================================
void CFindWolfScene::Tutorial2()
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
	}

	//ボタンを押したら
	if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT), 0))
	{
		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		//サウンドの取得
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音を再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_OK);

		//次のフェーズにする
		m_phase = PHASE::WOLF_DECIDE;

		//消す
		m_pTutorial->Uninit();
		m_pTutorial = nullptr;

		if (m_pNexButton != nullptr)
		{
			m_pNexButton->Uninit();
			m_pNexButton = nullptr;
		}

		for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
		{
			//選択用アイコンの生成
			m_pSelectIcon[nIdxPlayer] = CObject2D::Create(m_aPosPlayer2D[0], 
				                                          static_cast<CTexture::TEXTURE_TYPE>(static_cast<int>(CTexture::TEXTURE_TYPE::WOLF_SELECT_ICON_1) + nIdxPlayer),
				                                          FIND_WOLF_SCENE_SELECT_ICON_SIZE_X, FIND_WOLF_SCENE_SELECT_ICON_SIZE_Y);
			//選択用アイコンUIの位置設定処理
			SelectIconSetPos(nIdxPlayer, m_select[nIdxPlayer]);
		}

		//生成されていなかったら
		if (m_pTimerFrame == nullptr)
		{
			//タイマーの生成
			m_pTimerFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 61.0f, 0.0f), CTexture::TEXTURE_TYPE::TIMER_FRAME, 220.0f, 80.0f);
			m_pTimer = CTimer::Create(FIND_WOLF_SCENE_SELECT_TIME, 2, CTexture::TEXTURE_TYPE::NUMBER_003, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 75.0f, 40.0f, 0.0f), 50.0f);
		}
	}
}

//=============================================================================
//人狼決定処理
//=============================================================================
void CFindWolfScene::WolfDecide()
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
	}
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	int nNumDecide = 0;

	//選択アイコンの移動処理
	SelectIconMove();

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		//決定されていたら
		if (m_pSelectIcon[nIdxPlayer]->GetColor() == FIND_WOLF_SCENE_SELECT_ICON_DECIDE_COLOR)
		{
			nNumDecide++;
			continue;
		}

		//決定されていなかったら
		//タイマーが０になった場合
		if (m_pTimer != nullptr) {
			if (m_pTimer->GetScore() <= 0) {
				//色を黒くして薄くする
				m_pSelectIcon[nIdxPlayer]->SetColor(FIND_WOLF_SCENE_SELECT_ICON_DECIDE_COLOR);

				//マネージャーの取得
				CManager* pManager = CManager::GetManager();
				//サウンドの取得
				CSound* pSound = nullptr;
				if (pManager != nullptr) pSound = pManager->GetSound();
				//音を再生
				if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
				continue;
			}
		}


		//右を押したら
		if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT_RIGHT), nIdxPlayer))
		{
			if (static_cast<int>(m_select[nIdxPlayer]) >= static_cast<int>(SELECT::PLAYER_4))continue;

			//キャスト
			int nSelect = static_cast<int>(m_select[nIdxPlayer]);
			//次にする
			nSelect++;
			m_select[nIdxPlayer] = static_cast<SELECT>(nSelect);

			//選択用アイコンUIの位置設定処理
			SelectIconSetPos(nIdxPlayer, m_select[nIdxPlayer]);

			//音を再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_CURSOR);
		}
		//左を押したら
		else if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT_LFET), nIdxPlayer))
		{
			if (static_cast<int>(m_select[nIdxPlayer]) <= static_cast<int>(SELECT::PLAYER_1)) continue;

			//キャスト
			int nSelect = static_cast<int>(m_select[nIdxPlayer]);
			//前にする
			nSelect--;
			m_select[nIdxPlayer] = static_cast<SELECT>(nSelect);

			//選択用アイコンUIの位置設定処理
			SelectIconSetPos(nIdxPlayer, m_select[nIdxPlayer]);

			//音を再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_CURSOR);
		}
		//決定を押したら
		else if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT), nIdxPlayer))
		{
			//色を黒くして薄くする
			m_pSelectIcon[nIdxPlayer]->SetColor(FIND_WOLF_SCENE_SELECT_ICON_DECIDE_COLOR);

			//マネージャーの取得
			CManager* pManager = CManager::GetManager();
			//サウンドの取得
			CSound* pSound = nullptr;
			if (pManager != nullptr) pSound = pManager->GetSound();
			//音を再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
		}
	}

	//全員決定していなかったら
	if (nNumDecide != MAX_OBJECT_PLAYER_NUM) return;
	
	//全員決定したら
	m_nFrameCounter++;

	if (m_nFrameCounter <= FIND_WOLF_SCENE_SELECT_ALL_INTERVAL) return;

	m_nFrameCounter = 0;
	//タイマーを消す
	if (m_pTimerFrame != nullptr)
	{
		m_pTimer->Uninit();
		m_pTimer = nullptr;

		m_pTimerFrame->Uninit();
		m_pTimerFrame = nullptr;
	}

	//次のフェーズにする
	m_phase = PHASE::TUTORIAL_3;

	//説明UIの生成
	m_pTutorial = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                            CTexture::TEXTURE_TYPE::WOLF_FIND_TUTORIAL_3, SCREEN_WIDTH, SCREEN_HEIGHT);

	//次へUIの生成
	m_pNexButton = CNextButton::Create(FIND_WOLF_SCENE_NEXT_BUTTON_POS, FIND_WOLF_SCENE_NEXT_BUTTON_SIZE,
		                               CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_3, FIND_WOLF_SCENE_NEXT_BUTTON_COUNTER,
		                               FIND_WOLF_SCENE_NEXT_BUTTON_DEC_ALPHA);
}

//=============================================================================
//説明3
//=============================================================================
void CFindWolfScene::Tutorial3()
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
	}

	//選択アイコンの移動処理
	SelectIconMove();

	//ボタンを押したら
	if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT), 0))
	{
		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		//サウンドの取得
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音を再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_OK);

		//黒い画面の生成
		m_pWaitBlack = CCoverDisplay::Create(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

		//ステンシルの円
		m_pCircleStencilMask = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, m_aPosPlayer2D[0].y, 0.0f),
			CTexture::TEXTURE_TYPE::CIRCLE, STENCIL_CIRCLE_SIZE, STENCIL_CIRCLE_SIZE);
		if (m_pCircleStencilMask != nullptr) {
			m_pCircleStencilMask->SetStencilMask(true);
			m_pCircleStencilMask->SetDrawStencil(true);
		}

		//次のフェーズにする
		m_phase = PHASE::WAIT;

		//消す
		m_pTutorial->Uninit();
		m_pTutorial = nullptr;

		if (m_pNexButton != nullptr)
		{
			m_pNexButton->Uninit();
			m_pNexButton = nullptr;
		}
	}
}

//=============================================================================
//待つ処理
//=============================================================================
void CFindWolfScene::Wait()
{
	m_nFrameCounter++;

	//選択アイコンの移動処理
	SelectIconMove();

	//黒い画面のアルファ値の増加
	if (m_pWaitBlack != nullptr) {
		D3DXCOLOR colLast = m_pWaitBlack->GetColor();	//前回の色
		if(colLast.a < 0.5f) m_pWaitBlack->SetColor(colLast + D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.02f));
	}

	//ステンシルの円の横移動
	if (m_pCircleStencilMask != nullptr) {
		D3DXVECTOR3 posMask = m_pCircleStencilMask->GetPos();
		posMask += D3DXVECTOR3(STENCIL_CIRCLE_SPEED, 0.0f, 0.0f);
		if (posMask.x > SCREEN_WIDTH + STENCIL_CIRCLE_SIZE / 2.0f) {
			posMask.x = -STENCIL_CIRCLE_SIZE / 2.0f;
		}
		m_pCircleStencilMask->SetPos(posMask);
	}

	if (m_nFrameCounter < FIND_WOLF_SCENE_PLAYER_WAIT_TIME) return;
	m_nFrameCounter = 0;

	//ステンシルの円を強制移動
	if (m_pCircleStencilMask != nullptr) {
		//人狼プレイヤーの位置に設定
		m_pCircleStencilMask->SetPos(m_aPosPlayer2D[CGameScene::GetWereWolfPlayerIndex() - 1]);
	}

	//次のフェーズにする
	m_phase = PHASE::ANSWER;

	if (m_pTutorial == nullptr)
	{
		//説明UIの生成
		m_pTutorial = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
			                            static_cast<CTexture::TEXTURE_TYPE>
			                            (static_cast<int>(CTexture::TEXTURE_TYPE::WOLF_ANSWER_1) + CGameScene::GetWereWolfPlayerIndex() - 1),
			                            SCREEN_WIDTH, SCREEN_HEIGHT);

		//次へUIの生成
		m_pNexButton = CNextButton::Create(FIND_WOLF_SCENE_NEXT_BUTTON_POS, FIND_WOLF_SCENE_NEXT_BUTTON_SIZE,
			                               CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_3, FIND_WOLF_SCENE_NEXT_BUTTON_COUNTER,
			                               FIND_WOLF_SCENE_NEXT_BUTTON_DEC_ALPHA);
	}
}

//=============================================================================
//回答処理
//=============================================================================
void CFindWolfScene::Answer()
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
	}

	//選択アイコンの移動処理
	SelectIconMove();

	//ボタンを押したら
	if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT), 0))
	{
		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		//サウンドの取得
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音を再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_OK);

		//次のフェーズにする
		m_phase = PHASE::TUTORIAL_4;

		//テクスチャを変える
		m_pTutorial->SetTexType(CTexture::TEXTURE_TYPE::WOLF_FIND_TUTORIAL_4);

		//黒い画面の破棄
		if (m_pWaitBlack != nullptr) {
			m_pWaitBlack->Uninit();
			m_pWaitBlack = nullptr;
		}

		//ステンシルマスクの破棄
		if (m_pCircleStencilMask != nullptr) {
			m_pCircleStencilMask->Uninit();
			m_pCircleStencilMask = nullptr;
		}
	}
}

//=============================================================================
//説明4
//=============================================================================
void CFindWolfScene::Tutorial4()
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
	}

	//選択アイコンの移動処理
	SelectIconMove();

	//ボタンを押したら
	if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT), 0))
	{
		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		//サウンドの取得
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音を再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_OK);

		//消す
		m_pTutorial->Uninit();
		m_pTutorial = nullptr;

		if (m_pNexButton != nullptr)
		{
			m_pNexButton->Uninit();
			m_pNexButton = nullptr;
		}

		for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
		{
			//消す
			if (m_pSelectIcon[nIdxPlayer] != nullptr)
			{
				m_pSelectIcon[nIdxPlayer]->Uninit();
				m_pSelectIcon[nIdxPlayer] = nullptr;
			}
		}

		//次のフェーズにする
		m_phase = PHASE::DEC_WOLF_POINT;

		for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
		{
			if (m_pPointUi[nIdxPlayer] == nullptr)
			{
				//人狼を選んでいなかったら または自身が人狼だったら
				if (m_select[nIdxPlayer] != static_cast<SELECT>(CGameScene::GetWereWolfPlayerIndex() - 1) ||
					nIdxPlayer == CGameScene::GetWereWolfPlayerIndex() - 1) continue;

				//人狼を選んでいたら且つ自身が人狼でなかったら

				//人狼の上にアイコンを生成
				m_pPointUi[nIdxPlayer] = CObject2D::Create(m_aPosPlayer2D[CGameScene::GetWereWolfPlayerIndex() - 1],
					                                       static_cast<CTexture::TEXTURE_TYPE>(static_cast<int>(CTexture::TEXTURE_TYPE::WOLF_POINT_UI_1) + CGameScene::GetWereWolfPlayerIndex() - 1),
					                                       FIND_WOLF_SCENE_POINT_UI_SIZE_X, FIND_WOLF_SCENE_POINT_UI_SIZE_Y);
				//UIの位置設定処理
				PointUiSetPos(nIdxPlayer, CGameScene::GetWereWolfPlayerIndex() - 1);

				//スコアの設定
				m_apScoreUi[CGameScene::GetWereWolfPlayerIndex() - 1]->GetScore()->AddScore(-10);

				//次のフェーズを変える
				m_phase = PHASE::DEC_WOLF_POINT;
			}
		}
	}
}

//=============================================================================
//人狼のポイントマイナス処理
//=============================================================================
void CFindWolfScene::DecWolfPoint()
{
	//ポイント減算処理
	if (!DecPoint()) return;

	//全部消えていたら次のフェーズにする
	m_phase = PHASE::ADD_PLAYER_POINT;

	m_nFrameCounter = 0;

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		if (m_pPointUi[nIdxPlayer] == nullptr)
		{
			//人狼を選んでいなかったら または自身が人狼だったら
			if (m_select[nIdxPlayer] != static_cast<SELECT>(CGameScene::GetWereWolfPlayerIndex() - 1) ||
				nIdxPlayer == CGameScene::GetWereWolfPlayerIndex() - 1) continue;

			//人狼を選んでいたら且つ自身が人狼でなかったら

			//自分の上にアイコンを生成
			m_pPointUi[nIdxPlayer] = CObject2D::Create(m_aPosPlayer2D[nIdxPlayer],
				                                       static_cast<CTexture::TEXTURE_TYPE>(static_cast<int>(CTexture::TEXTURE_TYPE::WOLF_POINT_UI_1) + CGameScene::GetWereWolfPlayerIndex() - 1),
				                                       FIND_WOLF_SCENE_POINT_UI_SIZE_X, FIND_WOLF_SCENE_POINT_UI_SIZE_Y);
			//見えない状態にする
			m_pPointUi[nIdxPlayer]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pPointUi[nIdxPlayer]->SetPos(m_pPointUi[nIdxPlayer]->GetPos() + D3DXVECTOR3(0.0f, -FIND_WOLF_SCENE_POINT_UI_POS_Y, 0.0f));
		}
	}
}

//=============================================================================
//人狼以外のポイント加算処理
//=============================================================================
void CFindWolfScene::AddPlayerPoint()
{
	//ポイント加算処理
	if (!AddPoint(false)) return;

	//全部消えていたら
	//次のフェーズにする
	m_phase = PHASE::FINISH;

	m_nFrameCounter = 0;
	m_bAddPoint = false;

	int nCntMissPlayer = 0;
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		if (m_pPointUi[nIdxPlayer] == nullptr)
		{
			//人狼を選んでたら または自身が人狼だったら
			if (m_select[nIdxPlayer] == static_cast<SELECT>(CGameScene::GetWereWolfPlayerIndex() - 1) ||
				nIdxPlayer == CGameScene::GetWereWolfPlayerIndex() - 1) continue;

			//人狼を選んでいなかったら且つ自身が人狼でなかったら
			nCntMissPlayer++;
			//自分の上にアイコンを生成
			m_pPointUi[nIdxPlayer] = CObject2D::Create(m_aPosPlayer2D[nIdxPlayer] + D3DXVECTOR3(0.0f, -FIND_WOLF_SCENE_POINT_UI_POS_Y, 0.0f),
				                                       static_cast<CTexture::TEXTURE_TYPE>(static_cast<int>(CTexture::TEXTURE_TYPE::WOLF_POINT_UI_1) + nIdxPlayer),
				                                       FIND_WOLF_SCENE_POINT_UI_SIZE_X, FIND_WOLF_SCENE_POINT_UI_SIZE_Y);

			//スコアの設定
			m_apScoreUi[nIdxPlayer]->GetScore()->AddScore(-10);

			//次のフェーズを変える
			m_phase = PHASE::DEC_PLAYER_POINT;
		}
	}
}

//=============================================================================
//人狼以外のポイントマイナス処理
//=============================================================================
void CFindWolfScene::DecPlayerPoint()
{
	//ポイント減算処理
	if (!DecPoint()) return;

	//全部消えていたら次のフェーズにする
	m_phase = PHASE::ADD_WOLF_POINT;

	m_nFrameCounter = 0;

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		if (m_pPointUi[nIdxPlayer] == nullptr)
		{
			//人狼を選んでたら または自身が人狼だったら
			if (m_select[nIdxPlayer] == static_cast<SELECT>(CGameScene::GetWereWolfPlayerIndex() - 1) ||
				nIdxPlayer == CGameScene::GetWereWolfPlayerIndex() - 1) continue;

			//人狼を選んでいなかったら且つ自身が人狼でなかったら

			//人狼の上にアイコンを生成
			m_pPointUi[nIdxPlayer] = CObject2D::Create(m_aPosPlayer2D[CGameScene::GetWereWolfPlayerIndex() - 1],
				                                       static_cast<CTexture::TEXTURE_TYPE>(static_cast<int>(CTexture::TEXTURE_TYPE::WOLF_POINT_UI_1) + nIdxPlayer),
				                                       FIND_WOLF_SCENE_POINT_UI_SIZE_X, FIND_WOLF_SCENE_POINT_UI_SIZE_Y);
			//見えない状態にする
			m_pPointUi[nIdxPlayer]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			//UIの位置設定処理
			PointUiSetPos(nIdxPlayer, CGameScene::GetWereWolfPlayerIndex() - 1);
		}
	}
}

//=============================================================================
//人狼のポイント加算処理
//=============================================================================
void CFindWolfScene::AddWolfPoint()
{
	//ポイント加算処理
	if (!AddPoint(true)) return;

	//全部消えていたら

	//次のフェーズにする
	m_phase = PHASE::FINISH;

	m_nFrameCounter = 0;
}

//=============================================================================
//終了処理
//=============================================================================
void CFindWolfScene::Finish()
{
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//現在の入力デバイスの取得
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;

	if (pInput->GetTrigger(CInput::CODE::SELECT, 0)) {
		//フェードの取得
		CFade* pFade = pManager->GetFade();		//フェードへのポインタ
		if (pFade != nullptr) pFade->SetFade(CScene::SCENE_TYPE::SELECT_GAME, 0.02f, 60);
	}
}

//=============================================================================
//選択用アイコンUIの位置設定処理
//=============================================================================
void CFindWolfScene::SelectIconSetPos(const int nIdxPlayer, const SELECT select)
{
	if(m_pSelectIcon[nIdxPlayer] == nullptr)
	{ 
		return;
	}

	//位置設定
	m_pSelectIcon[nIdxPlayer]->SetPos(m_aPosPlayer2D[static_cast<int>(select)]);

	//位置を少しずつずらす
	D3DXVECTOR3 pos = m_pSelectIcon[nIdxPlayer]->GetPos();
	pos += D3DXVECTOR3(-(FIND_WOLF_SCENE_SELECT_ICON_POS_X_DIFFER * 2.0f) + (FIND_WOLF_SCENE_SELECT_ICON_POS_X_DIFFER / 2.0f) + (FIND_WOLF_SCENE_SELECT_ICON_POS_X_DIFFER * nIdxPlayer),
		               -FIND_WOLF_SCENE_SELECT_ICON_POS_Y,
		               0.0f);
	m_pSelectIcon[nIdxPlayer]->SetPos(pos);
}

//=============================================================================
//ポイントUIの位置設定処理
//=============================================================================
void CFindWolfScene::PointUiSetPos(const int nIdxPlayer, int nObjectPlayerIndex)
{
	if (m_pPointUi[nIdxPlayer] == nullptr)
	{
		return;
	}

	//位置設定
	m_pPointUi[nIdxPlayer]->SetPos(m_aPosPlayer2D[nObjectPlayerIndex]);

	//位置を少しずつずらす
	D3DXVECTOR3 pos = m_pPointUi[nIdxPlayer]->GetPos();
	pos += D3DXVECTOR3(-(FIND_WOLF_SCENE_POINT_UI_POS_X_DIFFER * 2.0f) + (FIND_WOLF_SCENE_POINT_UI_POS_X_DIFFER / 2.0f) + (FIND_WOLF_SCENE_POINT_UI_POS_X_DIFFER * nIdxPlayer),
		               -FIND_WOLF_SCENE_POINT_UI_POS_Y,
		               0.0f);
	m_pPointUi[nIdxPlayer]->SetPos(pos);
}

//=============================================================================
//ポイント減算処理
//=============================================================================
bool CFindWolfScene::DecPoint()
{
	int nUninitCount = 0;
	m_nFrameCounter++;

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		if (m_pPointUi[nIdxPlayer] == nullptr) {
			nUninitCount++;
			continue;
		}

		//生成されていたら

		//一定時間見えるようにする
		if (m_nFrameCounter < FIND_WOLF_SCENE_POINT_UI_DEC_COUNTER) continue;


		//カラー取得
		D3DXCOLOR col = m_pPointUi[nIdxPlayer]->GetColor();
		if (col.a <= 0.0f)
		{
			//消す
			m_pPointUi[nIdxPlayer]->Uninit();
			m_pPointUi[nIdxPlayer] = nullptr;
			continue;
		}

		//薄くする
		col.a -= FIND_WOLF_SCENE_POINT_UI_DEC_ALPHA;
		if (col.a < 0.0f) col.a = 0.0f;
		//カラー設定
		m_pPointUi[nIdxPlayer]->SetColor(col);

		//位置取得
		D3DXVECTOR3 pos = m_pPointUi[nIdxPlayer]->GetPos();
		//上に動かす
		pos.y -= FIND_WOLF_SCENE_POINT_UI_MOVE;
		//位置設定
		m_pPointUi[nIdxPlayer]->SetPos(pos);
	}

	if (nUninitCount != MAX_OBJECT_PLAYER_NUM) return false;

	return true;
}

//=============================================================================
//ポイント加算処理
//=============================================================================
bool CFindWolfScene::AddPoint(const bool bAddPointWolf)
{
	int nCntStop = 0;
	int nCntPointGetPlayer = 0;
	int nUninitCount = 0;

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		if (m_pPointUi[nIdxPlayer] == nullptr) {
			nUninitCount++;
			continue;
		}

		//生成されていたら

		//カラー取得
		D3DXCOLOR col = m_pPointUi[nIdxPlayer]->GetColor();

		//スコアが加算されていないなら
		if (!m_bAddPoint)
		{
			nCntPointGetPlayer++;
			if (col.a >= 1.0f) {
				nCntStop++;
				continue;
			}

			//濃くする
			col.a += FIND_WOLF_SCENE_POINT_UI_DEC_ALPHA;
			if (col.a > 1.0f) col.a = 1.0f;
			//カラー設定
			m_pPointUi[nIdxPlayer]->SetColor(col);

			//位置取得
			D3DXVECTOR3 pos = m_pPointUi[nIdxPlayer]->GetPos();
			//下に動かす
			pos.y += FIND_WOLF_SCENE_POINT_UI_MOVE;
			//位置設定
			m_pPointUi[nIdxPlayer]->SetPos(pos);
		}
		//スコアが加算されているなら
		else
		{
			if (col.a <= 0.0f)
			{
				//消す
				m_pPointUi[nIdxPlayer]->Uninit();
				m_pPointUi[nIdxPlayer] = nullptr;
				continue;
			}

			//薄くする
			col.a -= FIND_WOLF_SCENE_POINT_UI_DEC_ALPHA;
			if (col.a < 0.0f) col.a = 0.0f;
			//カラー設定
			m_pPointUi[nIdxPlayer]->SetColor(col);
		}
	}

	//全部消えていたら
	if (nUninitCount == MAX_OBJECT_PLAYER_NUM) return true;

	//消えていないなら
	//全部止まって居なかったら
	if (nCntPointGetPlayer != nCntStop) return false;

	//全部止まっていたら
	if (m_bAddPoint) return false;

	m_nFrameCounter++;

	//一定時間見えるようにする
	if (m_nFrameCounter < FIND_WOLF_SCENE_POINT_UI_DEC_COUNTER) return false;

	//ポイントが加算された状態にする
	m_bAddPoint = true;
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		if (m_pPointUi[nIdxPlayer] == nullptr) continue;

		//生成されていたら
		//人狼に加算しないなら
		if (!bAddPointWolf)
		{
			//スコアの設定
			m_apScoreUi[nIdxPlayer]->GetScore()->AddScore(10);
		}
		else
		{//人狼に加算するなら
			//スコアの設定
			m_apScoreUi[CGameScene::GetWereWolfPlayerIndex() - 1]->GetScore()->AddScore(10);
		}

		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		//サウンドの取得
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音を再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_POINT_1);
	}

	return false;
}

//=============================================================================
//選択アイコンの処理
//=============================================================================
void CFindWolfScene::SelectIconMove()
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		if (m_pSelectIcon[nCntPlayer] == nullptr) return;

		//生成されていたら
		//位置取得
		D3DXVECTOR3 pos = m_pSelectIcon[nCntPlayer]->GetPos();

		//移動量
		float fMove = FIND_WOLF_SCENE_SELECT_ICON_MOVE;
		//切替なら移動量を逆向きにする
		if (m_bSelectFloat[nCntPlayer]) fMove *= -1;

		//移動量設定
		m_fSelectMove[nCntPlayer] += fMove;

		//移動量の上限設定
		if (m_fSelectMove[nCntPlayer] > 1.0f) m_fSelectMove[nCntPlayer] = 1.0f;
		else if (m_fSelectMove[nCntPlayer] < -1.0f) m_fSelectMove[nCntPlayer] = -1.0f;

		pos.y -= m_fSelectMove[nCntPlayer];

		//位置設定
		m_pSelectIcon[nCntPlayer]->SetPos(pos);

		//デフォルトの位置を設定
		float fDefaultPos = m_aPosPlayer2D[nCntPlayer].y - FIND_WOLF_SCENE_SELECT_ICON_POS_Y;

		//加速できる範囲をランダムで設定
		float fAddMovePos = FIND_WOLF_SCENE_SELECT_ICON_ADD_MOVE_POS;

		//加速できる最大の位置を設定
		float fMaxPos = 0.0f;
		if (!m_bSelectFloat[nCntPlayer]) fMaxPos = fDefaultPos - fAddMovePos;
		//切替なら逆向きにする
		else fMaxPos = fDefaultPos + fAddMovePos;

		//加速できる最大の位置を通過したら切り替える
		if (pos.y <= fMaxPos && !m_bSelectFloat[nCntPlayer]) m_bSelectFloat[nCntPlayer] = true;
		else if (pos.y >= fMaxPos && m_bSelectFloat[nCntPlayer]) m_bSelectFloat[nCntPlayer] = false;
	}
}
