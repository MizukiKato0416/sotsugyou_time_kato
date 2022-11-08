//=============================================================================
//
// ゲームシーン処理 [gameScene.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "gameScene.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "gameCamera.h"
#include "fade.h"
#include "timer.h"
#include "object2D.h"
#include "object_player_balloon_car.h"
#include "meshwall.h"
#include "wallCylinder.h"
#include "pauseMenu.h"
#include "balloon.h"
#include "itemBox.h"
#include "count_down_ui.h"
#include "finish_ui.h"
#include "player.h"

//エフェクト
#include "plane.h"
#include "PresetSetEffect.h"

#include "player_icon.h"
#include "ToScreen.h"
#include "check.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GAME_FINISH_UI_NUM						 (5)		//フィニッシュUIの数

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
bool CGameScene::m_bWereWolfMode = false;
int CGameScene::m_nWereWolfPlayerIndex = 0;
int CGameScene::m_aRanking[MAX_OBJECT_PLAYER_NUM] = { 0, 0, 0, 0 };

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGameScene::CGameScene()
{
	m_pTimer = nullptr;
	m_bAllCheck = false;
	m_bReady = false;
	m_bLockPauseMenu = false;
	m_pCheck = nullptr;

	for (int nCntSavePlayer = 0; nCntSavePlayer < MAX_OBJECT_PLAYER_NUM; nCntSavePlayer++)
	{
		m_aRanking[nCntSavePlayer] = 0;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameScene::~CGameScene()
{

}

//=============================================================================
// ゲームシーンの初期化処理
//=============================================================================
void CGameScene::Init(void) {
	//変数初期化
	m_bAllCheck = false;
	m_bReady = true;
	m_bLockPauseMenu = false;
	for (int nCntSavePlayer = 0; nCntSavePlayer < MAX_OBJECT_PLAYER_NUM; nCntSavePlayer++)
	{
		m_aRanking[nCntSavePlayer] = 0;
	}

	//オブジェクトのポーズが無いように設定
	CObject::SetUpdatePauseLevel(0);
	
	//チェックアイコンの生成
	m_pCheck = CCheck::Create(MAX_OBJECT_PLAYER_NUM);

#ifdef _DEBUG
	//Zバッファテクスチャの表示
	CObject2D* pZBuff = CObject2D::Create(D3DXVECTOR3(70.0f, 70.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, 100.0f, 100.0f);
	if (pZBuff != nullptr) {
		pZBuff->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
		pZBuff->SetUseZBuffTexture(true);
	}
#endif
}

//=============================================================================
// ゲームシーンの終了処理
//=============================================================================
void CGameScene::Uninit(void) {
	//シーンのプレイヤーの設定
	SetPlayer(nullptr);

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
// ゲームシーンの更新処理
//=============================================================================
void CGameScene::Update(void) {
	//毎フレーム終了時にロック解除
	m_bLockPauseMenu = false;
}

//=============================================================================
// ポーズメニューの生成
//=============================================================================
void CGameScene::CreatePauseMenu(void) {
	if (m_pMenuPause != nullptr) DeletePauseMenu();

	//ポーズメニュークラスを生成
	m_pMenuPause = CPauseMenu::Create();
}

//=============================================================================
// ポーズメニューの破棄
//=============================================================================
void CGameScene::DeletePauseMenu(void) {
	//ポーズメニューの破棄
	if (m_pMenuPause != nullptr) {
		m_pMenuPause->Uninit();
		m_pMenuPause = nullptr;
	}

	//破棄してすぐは生成できないように
	m_bLockPauseMenu = true;
}

//=============================================================================
// ゲームオーバー
//=============================================================================
void CGameScene::GameOver(void) {
	if (m_bGameOver) return;

	m_bGameOver = true;

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//ゲームオーバー音を再生
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_TIME_UP);


	//フィニッシュUI生成
	CFinishUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 0, 1.0f);
	for (int nCntFinish = 0; nCntFinish < GAME_FINISH_UI_NUM; nCntFinish++)
	{
		CFinishUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), nCntFinish + 1, 0.4f);
	}

	//タイマーを停止
	if (m_pTimer != nullptr) {
		m_pTimer->SetStop(true);
	}

	//オブジェクトのポーズが無いように設定（念のため）
	CObject::SetUpdatePauseLevel(0);
}
