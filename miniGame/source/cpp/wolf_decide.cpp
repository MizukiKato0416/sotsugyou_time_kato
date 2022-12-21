//=============================================================================
//
// 人狼決定処理 [wolf_decide.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "wolf_decide.h"
#include "object2D.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "object_player.h"
#include "gameScene.h"
#include "next_button.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define WOLF_DECIDE_SHAKE_MAX_TIME	(180)				//振動する時間
#define WOLF_DECIDE_SHAKE_INTERVAL	(60)				//振動する間隔
#define WOLF_DECIDE_BRINK_INTERVAL	(30)				//点滅する間隔
#define WOLF_DECIDE_SHAKE_NUM		(7000)				//振動する量
#define WOLF_DECIDE_SHAKE_TIME		(45)				//一回の振動で振動する時間
#define WOLF_DECIDE_SHAKE_UI_SIZE_X	(1282.0f * 0.7f)	//振動UIのサイズX
#define WOLF_DECIDE_SHAKE_UI_SIZE_Y	(167.0f * 0.7f)		//振動UIのサイズY

#define WOLF_DECIDE_NEXT_BUTTON_POS			(D3DXVECTOR3(960.0f, 670.0f, 0.0f))		//次に進むボタンの位置
#define WOLF_DECIDE_NEXT_BUTTON_SIZE		(D3DXVECTOR3(60.0f, 60.0f, 0.0f))		//次に進むボタンのサイズ
#define WOLF_DECIDE_NEXT_BUTTON_COUNTER		(15)									//次に進むボタンの見えるようになるまでのカウンター
#define WOLF_DECIDE_NEXT_BUTTON_DEC_ALPHA	(0.015f)								//次に進むボタンのα値減算量


//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CWolfDecide::CWolfDecide()
{
	m_pBg = nullptr;
	m_pShakeUI = nullptr;
	m_pTutorialUI = nullptr;
	m_phase = PHASE::NONE;
}
//=============================================================================
// デストラクタ
//=============================================================================
CWolfDecide::~CWolfDecide()
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CWolfDecide* CWolfDecide::Create(void) {
	CWolfDecide* pWolfDecide;
	pWolfDecide = new CWolfDecide();
	if (pWolfDecide == nullptr) return nullptr;

	pWolfDecide->Init();

	return pWolfDecide;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWolfDecide::Init(void) {
	
	//変数初期化
	m_nShakeUiCounter = 0;
	m_phase = PHASE::SHAKE_TUTORIAL;

	//人狼を決める
	int nWolfPlayerIndex = (rand() % MAX_OBJECT_PLAYER_NUM) + 1;
	//人狼を設定
	CGameScene::SetWereWolfPlayerIndex(nWolfPlayerIndex);


	//背景の暗いやつ
	m_pBg = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pBg->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));


	//説明UI
	m_pTutorialUI = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                              CTexture::TEXTURE_TYPE::WOLF_SHAKE_TUTORIAL, SCREEN_WIDTH, SCREEN_HEIGHT);

	//次へUIの生成
	m_pNextButton = CNextButton::Create(WOLF_DECIDE_NEXT_BUTTON_POS, WOLF_DECIDE_NEXT_BUTTON_SIZE,
		                               CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_3, WOLF_DECIDE_NEXT_BUTTON_COUNTER, WOLF_DECIDE_NEXT_BUTTON_DEC_ALPHA);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CWolfDecide::Uninit(void) {

	//生成されていたら
	if (m_pBg != nullptr)
	{
		//消す
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	//消す
	if (m_pTutorialUI != nullptr)
	{
		m_pTutorialUI->Uninit();
		m_pTutorialUI = nullptr;
	}

	//消す
	if (m_pShakeUI != nullptr)
	{
		m_pShakeUI->Uninit();
		m_pShakeUI = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CWolfDecide::Update(void) {
	//処理分け
	switch (m_phase)
	{
	case CWolfDecide::PHASE::SHAKE_TUTORIAL:
		//振動説明処理
		ShakeTutorial();
		break;
	case CWolfDecide::PHASE::SHAKE:
		//振動処理
		Shake();
		break;
	case CWolfDecide::PHASE::GAME_START:
		//ゲームスタート処理
		GameStart();
		break;
	default:
		break;
	}
}

//=============================================================================
//振動説明処理
//=============================================================================
void CWolfDecide::ShakeTutorial()
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
		if (m_pTutorialUI != nullptr)
		{
			m_pTutorialUI->Uninit();
			m_pTutorialUI = nullptr;
		}

		if (m_pNextButton != nullptr)
		{
			m_pNextButton->Uninit();
			m_pNextButton = nullptr;
		}

		//次のフェーズにする
		m_phase = PHASE::SHAKE;

		//振動UIの生成
		if (m_pShakeUI == nullptr)
		{
			m_pShakeUI = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                                   CTexture::TEXTURE_TYPE::WOLF_SHAKE, WOLF_DECIDE_SHAKE_UI_SIZE_X, WOLF_DECIDE_SHAKE_UI_SIZE_Y);
		}
	}
}

//=============================================================================
//振動処理
//=============================================================================
void CWolfDecide::Shake()
{
	if (m_pShakeUI == nullptr)
	{
		return;
	}

	m_nShakeUiCounter++;

	//指定時間になったら
	if (m_nShakeUiCounter > WOLF_DECIDE_SHAKE_MAX_TIME)
	{
		//消す
		m_pShakeUI->Uninit();
		m_pShakeUI = nullptr;

		//次のフェーズにする
		m_phase = PHASE::GAME_START;

		//説明UI
		m_pTutorialUI = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
			                              CTexture::TEXTURE_TYPE::WOLF_SHAKE_START, SCREEN_WIDTH, SCREEN_HEIGHT);

		//次へUIの生成
		m_pNextButton = CNextButton::Create(WOLF_DECIDE_NEXT_BUTTON_POS, WOLF_DECIDE_NEXT_BUTTON_SIZE,
			                               CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_3, WOLF_DECIDE_NEXT_BUTTON_COUNTER, WOLF_DECIDE_NEXT_BUTTON_DEC_ALPHA);

		return;
	}

	//指定フレーム毎に
	if (m_nShakeUiCounter % WOLF_DECIDE_BRINK_INTERVAL == 0)
	{
		//カラー取得
		D3DXCOLOR col = m_pShakeUI->GetColor();
		//見えていないなら
		if (col.a == 0.0f)
		{
			//見えるようにする
			col.a = 1.0f;
		}
		else
		{//見えているなら
		 //見えないようにする
			col.a = 0.0f;
		}
		//カラー設定処理
		m_pShakeUI->SetColor(col);
	}

	//指定フレーム毎に
	if (m_nShakeUiCounter % WOLF_DECIDE_SHAKE_INTERVAL == 0)
	{
		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		CInput* pInput = nullptr;
		CInputGamepadX *pPadX = nullptr;
		if (pManager != nullptr) {
			//現在の入力デバイスの取得
			pInput = pManager->GetInputCur();
			pPadX = dynamic_cast<CInputGamepadX*>(pInput);
		}

		for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
		{
			//人狼じゃなかったら
			if (pPadX != nullptr && nCntPlayer != CGameScene::GetWereWolfPlayerIndex() - 1)
			{
				//振動させる
				pPadX->SetVibration(WOLF_DECIDE_SHAKE_NUM, WOLF_DECIDE_SHAKE_NUM, WOLF_DECIDE_SHAKE_TIME, nCntPlayer);
			}
		}
	}
}

//=============================================================================
//ゲームスタート処理
//=============================================================================
void CWolfDecide::GameStart()
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
		if (m_pTutorialUI != nullptr)
		{
			m_pTutorialUI->Uninit();
			m_pTutorialUI = nullptr;
		}

		if (m_pNextButton != nullptr)
		{
			m_pNextButton->Uninit();
			m_pNextButton = nullptr;
		}

		//フェーズを次にする
		m_phase = PHASE::UNINIT;
	}
}
