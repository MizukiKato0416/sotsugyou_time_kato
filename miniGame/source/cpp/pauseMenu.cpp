//=============================================================================
//
// ポーズメニュー処理 [pauseMenu.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "pauseMenu.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "gameScene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define NUM_SELECT (3)
#define SELECT_TITLE_POS (D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 300.0f, 0.0f))
#define SELECT_RESTATE_POS (D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 450.0f, 0.0f))
#define SELECT_CONTINUE_POS (D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 600.0f, 0.0f))
#define SELECT_UI_WIDTH (500.0f)
#define SELECT_UI_HEIGHT (100.0f)
#define SELECT_ICON_POS (D3DXVECTOR3(-250.0f, 0.0f, 0.0f))
#define SELECT_ICON_WIDTH (70.0f)
#define SELECT_ICON_HEIGHT (50.0f)

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CPauseMenu::CPauseMenu() : CSelectMenu2D(NUM_SELECT, true)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CPauseMenu::~CPauseMenu()
{

}

//=============================================================================
// ポーズメニューの生成処理
//=============================================================================
CPauseMenu* CPauseMenu::Create(void) {
	CPauseMenu* pPauseMenu;
	pPauseMenu = new CPauseMenu();
	if (pPauseMenu == nullptr) return nullptr;

	//ポーズの設定
	pPauseMenu->SetPauseLevel(AddUpdatePauseLevel());	//ポーズのレベルを上げて返り値でポーズ更新可能レベルを取得し、オブジェクトのポーズレベルとして設定

	pPauseMenu->Init();

	return pPauseMenu;
}

//=============================================================================
// ポーズメニューの初期化処理
//=============================================================================
HRESULT CPauseMenu::Init(void) {
#ifndef _DEBUG
	//背景の設定
	SetMenuBG(CTexture::TEXTURE_TYPE::PAUSE_BG, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);	
#endif
	//縦選択
	SetSelectType(CSelectMenu::SELECT_TYPE::VERTICAL);
	//選択肢UIの詳細設定
	SetSelectUI(0, SELECT_TITLE_POS, SELECT_UI_WIDTH, SELECT_UI_HEIGHT, CTexture::TEXTURE_TYPE::PAUSE_CONTINUE);
	SetSelectUI(1, SELECT_RESTATE_POS, SELECT_UI_WIDTH, SELECT_UI_HEIGHT, CTexture::TEXTURE_TYPE::PAUSE_RESTART);
	SetSelectUI(2, SELECT_CONTINUE_POS, SELECT_UI_WIDTH, SELECT_UI_HEIGHT, CTexture::TEXTURE_TYPE::PAUSE_MENU);
	//選択肢アイコンの生成
	CreateSelectIcon(SELECT_ICON_POS, SELECT_ICON_WIDTH, SELECT_ICON_HEIGHT, CTexture::TEXTURE_TYPE::SELECT_ICON);
	SetIconPosOffset(1, D3DXVECTOR3(-230.0f, 0.0f, 0.0f));

	CSelectMenu2D::Init();

	return S_OK;
}

//=============================================================================
// ポーズメニューの終了処理
//=============================================================================
void CPauseMenu::Uninit(void) {
	CSelectMenu2D::Uninit();

	//ポーズのレベルを下げる
	//SubUpdatePauseLevel();	//ポーズメニューの選択によって分岐させるようにするためコメントアウト
}

//=============================================================================
// ポーズメニューの更新処理
//=============================================================================
void CPauseMenu::Update(void) {
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//現在の入力デバイスの取得
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;
	//フェードの取得
	CFade* pFade = pManager->GetFade();		//フェードへのポインタ
	if (pFade == nullptr) return;
	//ゲームシーンの取得
	CGameScene* pGameScene = pManager->GetGameScene();		//フェードへのポインタ
	if (pGameScene == nullptr) return;
	//サウンドの取得
	CSound* pSound = pManager->GetSound();	//サウンドへのポインタ
	if (pSound == nullptr) return;

	if (pInput != nullptr) {
		//選択を入力
		if (pInput->GetTrigger(CInput::CODE::SELECT, 0) && !GetLockChangeSelect()) {
			switch (GetIdxCurSelect())
			{
				//ゲーム再開
			case 0:
				//ゲームシーンのポーズメニューを破棄する
				pGameScene->DeletePauseMenu();
				//ポーズのレベルを下げる
				SubUpdatePauseLevel();
				//サウンドを再生
				pSound->PlaySound(CSound::SOUND_LABEL::SE_CANCEL);
				return;
				break;

				//リトライ
			case 1:
				//ゲームシーンのポーズメニューを破棄する
				pGameScene->DeletePauseMenu();
				//現在のシーンをリロード
				pFade->SetFade(CScene::GetSceneType(), 0.02f, 0);
				//サウンドを再生
				pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
				break;

				//ゲーム選択に戻る
			case 2:
				//ゲームシーンのポーズメニューを破棄する
				pGameScene->DeletePauseMenu();
				//ゲーム選択シーン遷移
				pFade->SetFade(CScene::SCENE_TYPE::SELECT_GAME , 0.02f, 0);
				//サウンドを再生
				pSound->PlaySound(CSound::SOUND_LABEL::SE_CANCEL);
				break;
			}
		}
	}

	CSelectMenu2D::Update();
}