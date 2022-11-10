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

//=============================================================================
// マクロ定義
//=============================================================================
#define FIND_WOLF_SCENE_SELECT_ICON_SIZE_X			(440.0f * 0.2f)							//選択アイコンのサイズX
#define FIND_WOLF_SCENE_SELECT_ICON_SIZE_Y			(314.0f * 0.2f)							//選択アイコンのサイズY
#define FIND_WOLF_SCENE_SELECT_ICON_DECIDE_COLOR	(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f))		//選択アイコンの決定時のカラー

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
	memset(m_select, 0, sizeof(m_select[MAX_OBJECT_PLAYER_NUM]));
	m_phase = PHASE::NONE;
	m_pTutorial = nullptr;
	m_nFrameCounter = 0;

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		m_aPosPlayer2D[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	memset(m_select, 0, sizeof(m_select[MAX_OBJECT_PLAYER_NUM]));
	m_nFrameCounter = 0;

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//カメラの設定
	if (pManager != nullptr) pManager->SetCamera(CFindWolfCamera::Create());	//なにか一つカメラが無いと描画されないのでとりあえずゲームカメラ

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
		m_phase = PHASE::WAIT;

		//消す
		m_pTutorial->Uninit();
		m_pTutorial = nullptr;
	}
}

//=============================================================================
//待つ処理
//=============================================================================
void CFindWolfScene::Wait()
{
	m_nFrameCounter++;

	if (m_nFrameCounter < FIND_WOLF_SCENE_PLAYER_WAIT_TIME) return;
	m_nFrameCounter = 0;

	//次のフェーズにする
	m_phase = PHASE::ANSWER;

	if (m_pTutorial == nullptr)
	{
		//説明UIの生成
		m_pTutorial = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
			                            static_cast<CTexture::TEXTURE_TYPE>
			                            (static_cast<int>(CTexture::TEXTURE_TYPE::WOLF_ANSWER_1) + CGameScene::GetWereWolfPlayerIndex() - 1),
			                            SCREEN_WIDTH, SCREEN_HEIGHT);
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

		//次のフェーズにする
		m_phase = PHASE::DEC_WOLF_POINT;
	}
}

//=============================================================================
//人狼のポイントマイナス処理
//=============================================================================
void CFindWolfScene::DecWolfPoint()
{
}

//=============================================================================
//人狼以外のポイント加算処理
//=============================================================================
void CFindWolfScene::AddPlayerPoint()
{
}

//=============================================================================
//人狼以外のポイントマイナス処理
//=============================================================================
void CFindWolfScene::DecPlayerPoint()
{
}

//=============================================================================
//人狼のポイント加算処理
//=============================================================================
void CFindWolfScene::AddWolfPoint()
{
}

//=============================================================================
//選択用アイコンUIの位置設定処理
//=============================================================================
void CFindWolfScene::SelectIconSetPos(const int nIdxPlayer, const SELECT select)
{
	//位置設定
	m_pSelectIcon[nIdxPlayer]->SetPos(m_aPosPlayer2D[static_cast<int>(select)]);

	//位置を少しずつずらす
	D3DXVECTOR3 pos = m_pSelectIcon[nIdxPlayer]->GetPos();
	pos += D3DXVECTOR3(-(40.0f * 2.0f) + (40.0f / 2.0f) + (40.0f * nIdxPlayer), -150.0f, 0.0f);
	m_pSelectIcon[nIdxPlayer]->SetPos(pos);
}
