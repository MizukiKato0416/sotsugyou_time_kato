//=============================================================================
//
// ゲームシーン処理 [gameScene.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "gameScene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "gameCamera.h"
#include "fade.h"
#include "timer.h"
#include "score.h"
#include "stage.h"
#include "object2D.h"
#include "player.h"
#include "effect.h"
#include "terrain.h"
#include "meshwall.h"
#include "wallCylinder.h"
#include "pauseMenu.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GAME_TIME (300)
#define TEXT_FILE_NAME_HISCORE "data/TEXT/save_hiscore.txt"
#define TEXT_FILE_NAME_APPLETYPE "data/TEXT/save_appletype.txt"
#define FOG_COLOR (D3DXCOLOR(0.1f, 0.0f, 0.2f, 1.0f))	//フォグの色
#define FOG_COLOR_GAMECLEAR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	//フォグの色

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGameScene::CGameScene()
{
	m_pStage = nullptr;
	m_pTimer = nullptr;
	m_pMenuGameEnd = nullptr;
	m_nGameScore = 0;

	m_nCntGameClear = 0;
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
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//カメラの設定
	if (pManager != nullptr) pManager->SetCamera(CGameCamera::Create());

	//------------------------------
	//ライトの初期設定
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ライトの射影変換
	//ライトのプロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 800.0f, 5500.0f);

	D3DXMATRIX mtxLightView;   // ライトビュー変換
	D3DXVECTOR3 posLight = D3DXVECTOR3(0.0f, 4800.0f, -1920.0f);	//ライトの位置
	D3DXVECTOR3 vecLight;	//ライトのベクトル
	D3DXVec3Normalize(&vecLight, &posLight);
	vecLight *= -1;
	//ライトのビューマトリックスを生成
	D3DXMatrixLookAtLH(&mtxLightView, &posLight, &D3DXVECTOR3(posLight + vecLight), &D3DXVECTOR3(0, 1, 0));
	//シェーダのライトを設定
	if (pRenderer != nullptr) {
		pRenderer->SetEffectLightMatrixView(mtxLightView);
		pRenderer->SetEffectLightVector(D3DXVECTOR4(vecLight, 1.0f));
		pRenderer->SetEffectLightMatrixProj(mtxLightProj);
	}

	//月のビルボード生成
	CBillboard* pMoon = CBillboard::Create(D3DXVECTOR3(-800.0f, 1500.0f, -2000.0f), CTexture::TEXTURE_TYPE::MOON, 200.0f, 200.0f);
	if (pMoon != nullptr) pMoon->SetDrawPriority(CObject::DRAW_PRIORITY::BG);

	//------------------------------
	//フォグの初期設定
	//------------------------------
	if (pRenderer != nullptr) {
		pRenderer->SetEffectFogEnable(false);
		pRenderer->SetEffectFogColor(FOG_COLOR);
		pRenderer->SetEffectFogRange(800.0f, 4500.0f);
		//バックバッファをフォグの色に合わせる
		pRenderer->SetBackBuffColor(FOG_COLOR);
	}

	//------------------------------
	//モーション情報のロード
	//------------------------------

	//オブジェクトのポーズが無いように設定
	CObject::SetUpdatePauseLevel(0);

	//ステージの生成
	//if (m_pStage == nullptr) m_pStage = new CStage;
	//if (m_pStage != nullptr) m_pStage->CreateStage(TEXT_FILE_NAME_STAGE_GAME);
	CMeshwall::Create(D3DXVECTOR3(0.0f, 0.0f, -1500.0f), D3DXVECTOR3(D3DX_PI*0.5f, 0.0f, 0.0f), 4, 4, 1000.0f, 1000.0f, CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);

	//円柱の壁の生成
	CWallCylinder::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), 800.0f, 40.0f, CTexture::TEXTURE_TYPE::NONE, true);

	//プレイヤーの生成
	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//シーンのプレイヤーの設定
	SetPlayer(pPlayer);

	//タイマーの生成
	m_pTimerFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 61.0f, 0.0f), CTexture::TEXTURE_TYPE::TIMER_FRAME, 220.0f, 80.0f);
	m_pTimer = CTimer::Create(GAME_TIME, 3, CTexture::TEXTURE_TYPE::NUMBER_003, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 75.0f, 40.0f, 0.0f), 50.0f);

	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME);
	}

#ifdef _DEBUG
	//Zバッファテクスチャの表示
	CObject2D* pZBuff = CObject2D::Create(D3DXVECTOR3(70.0f, 70.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, 100.0f, 100.0f);
	if (pZBuff != nullptr) {
		pZBuff->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
		pZBuff->SetUseZBuffTexture(true);
	}
#endif

	m_nGameScore = 0;
}

//=============================================================================
// ゲームシーンの終了処理
//=============================================================================
void CGameScene::Uninit(void) {
	//ステージの破棄
	if (m_pStage != nullptr) {
		delete m_pStage;
		m_pStage = nullptr;
	}

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
#ifdef _DEBUG
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//現在の入力デバイスの取得
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;

	//ゲームオーバー
	if (pInput->GetTrigger(CInput::CODE::DEBUG_1)) {
		GameOver();
	}

	//タイム追加
	if (pInput->GetTrigger(CInput::CODE::DEBUG_3)) {
		if (m_pTimer != nullptr) m_pTimer->AddScore(50);
	}
#endif

	//ゲームオーバー時
	if (m_bGameOver) {
		UpdateGameOver();
	}
	//ゲーム中
	else
	{
		UpdateGame();
	}
}

//=============================================================================
// ゲーム中の更新
//=============================================================================
void CGameScene::UpdateGame(void) {
	//ポーズメニューがある場合は更新なし
	if (m_pMenuPause != nullptr) return;

	//ゲーム終了していないときにタイマーが０になった場合
	if (m_pTimer != nullptr && !m_bGameOver) {
		if (m_pTimer->GetScore() <= 0) {
			//ゲーム終了
			GameOver();
		}
	}

	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//現在の入力デバイスの取得
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;
	//サウンドの取得
	CSound* pSound = pManager->GetSound();	//サウンドへのポインタ
	if (pSound == nullptr) return;
	//フェードの取得
	CFade* pFade = pManager->GetFade();	//フェードのポインタ
	if (pFade == nullptr) return;

	//ポーズ
	if (pInput->GetTrigger(CInput::CODE::PAUSE) && !pFade->GetFade()) {
		//ポーズメニュークラスを生成
		m_pMenuPause = CPauseMenu::Create();
		//サウンドを再生
		pSound->PlaySound(CSound::SOUND_LABEL::TITLE_OPEN);
	}
}

//=============================================================================
// ゲームオーバー時の更新
//=============================================================================
void CGameScene::UpdateGameOver(void) {
	if (m_pMenuGameEnd == nullptr) return;

	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//現在の入力デバイスの取得
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;
	//フェードの取得
	CFade* pFade = pManager->GetFade();		//フェードへのポインタ
	if (pFade == nullptr) return;
	//サウンドの取得
	CSound* pSound = pManager->GetSound();	//サウンドへのポインタ
	if (pSound == nullptr) return;

	//選択時
	if (pInput->GetTrigger(CInput::CODE::SELECT)) {
		switch (m_pMenuGameEnd->GetIdxCurSelect())
		{
		case 0:
			//タイトルへシーン遷移
			pFade->SetFade(CScene::SCENE_TYPE::TITLE, 0.02f, 60);
			break;
		case 1:
			//ゲームを再プレイ
			pFade->SetFade(CScene::SCENE_TYPE::GAME, 0.02f, 60);
			break;
		}

		//選択決定音の再生
		pSound->PlaySound(CSound::SOUND_LABEL::TITLE_START);
	}
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
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::GAMEOVER);

	//プレイヤーの取得
	CPlayer* pPlayer = GetPlayer();
	if (pPlayer != nullptr) {
		//プレイヤーのゲームオーバー時の処理
		pPlayer->GameOver();
	}

	//ゲームオーバーテキストの表示
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 300.0f, 0.0f), CTexture::TEXTURE_TYPE::TEXT_GAMEOVER, 600.0f, 150.0f);

	//ゲーム終了メニューの生成
	CreateMenuEndGame();

	//タイマーを停止
	if (m_pTimer != nullptr) {
		m_pTimer->SetStop(true);
	}

	//オブジェクトのポーズが無いように設定（念のため）
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
// ゲーム終了時の選択メニューの生成
//=============================================================================
void CGameScene::CreateMenuEndGame(void) {
	//すでに生成されている場合終了
	if (m_pMenuGameEnd != nullptr) return;

	//メニューの生成
	m_pMenuGameEnd = CSelectMenu2D::Create(2, true);
	if (m_pMenuGameEnd == nullptr) return;

	//背景の設定
	m_pMenuGameEnd->SetMenuBG(CTexture::TEXTURE_TYPE::MENU_BG, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 600.0f, 0.0f), 600.0f, 80.0f);
	//横選択
	m_pMenuGameEnd->SetSelectType(CSelectMenu::SELECT_TYPE::HORIZONTAL);
	//選択肢UIの詳細設定
	m_pMenuGameEnd->SetSelectUI(0, D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 130.0f, 600.0f, 0.0f), 220.0f, 40.0f, CTexture::TEXTURE_TYPE::TEXT_QUIT);
	m_pMenuGameEnd->SetSelectUI(1, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 130.0f, 600.0f, 0.0f), 220.0f, 40.0f, CTexture::TEXTURE_TYPE::TEXT_RETRY);
	//選択肢アイコンの生成
	m_pMenuGameEnd->CreateSelectIcon(D3DXVECTOR3(-80.0f, 0.0f, 0.0f), 40.0f, 40.0f, CTexture::TEXTURE_TYPE::SELECT_ICON);
	m_pMenuGameEnd->SetIconPosOffset(1, D3DXVECTOR3(-105.0f, 0.0f, 0.0f));
}