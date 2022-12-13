//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include <thread>
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "sound.h"
#include "renderer.h"
#include "fade.h"
#include "scene.h"
#include "object.h"
#include "loading_ui.h"
#include "object3D.h"
#include "texture.h"
#include "model.h"

#include "gameScene.h"

//エフェクト
#include "LoadEffect.h"
#include "plane.h"
#include "Sphere.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MANAGER_LOADING_UI_SIZE_X		(1872.0f / 4.0f * 1.0f)								//サイズX
#define MANAGER_LOADING_UI_SIZE_Y		(81.0f			* 1.0f)								//サイズY
#define MANAGER_LOADING_UI_POS_X		(SCREEN_WIDTH - MANAGER_LOADING_UI_SIZE_X / 2.0f)	//位置X
#define MANAGER_LOADING_UI_POS_Y		(SCREEN_HEIGHT - MANAGER_LOADING_UI_SIZE_Y / 2.0f)	//位置Y

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CManager* CManager::m_pManager = nullptr;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CManager::CManager() {
	m_pRenderer = nullptr;
	m_pInputCur = nullptr;
	m_pInputKeyboard = nullptr;
	m_pInputGamepadX = nullptr;
	m_bEnableXInput = false;
	m_pCamera = nullptr;
	m_pSound = nullptr;
	m_pFade = nullptr;
	m_pScene = nullptr;
	m_pLoadingUi = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager() {

}

//=============================================================================
//ローディング画面の処理
//=============================================================================
void CManager::LoadingPolygon()
{
	//ロードでないなら
	if (CTexture::GetLoadFinish())
	{
		if (m_pLoadingUi != nullptr)
		{
			//消す
			m_pLoadingUi->Uninit();
			m_pLoadingUi = nullptr;
		}
		return;
	}

	//ロード中なら
	if (m_pLoadingUi == nullptr)
	{
		//ロードを生成
		m_pLoadingUi = CLoadingUi::Create(D3DXVECTOR3(MANAGER_LOADING_UI_POS_X, MANAGER_LOADING_UI_POS_Y, 0.0f), 
			                              D3DXVECTOR3(MANAGER_LOADING_UI_SIZE_X, MANAGER_LOADING_UI_SIZE_Y, 0.0f));
	}
}

//=============================================================================
// マネージャーの生成
//=============================================================================
void CManager::Create(void) {
	//生成されていない場合生成
	if (m_pManager == nullptr) m_pManager = new CManager;
}
 
//=============================================================================
// マネージャーの破棄
//=============================================================================
void CManager::Destroy(void) {
	if (m_pManager != nullptr) {
		delete m_pManager;
		m_pManager = nullptr;
	}
}

//=============================================================================
// マネージャーの取得 
//=============================================================================
CManager* CManager::GetManager(void) {
	return m_pManager;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow) {
	//乱数の種の初期化
	srand((unsigned)time(nullptr));

	//変数初期化
	m_pLoadingUi = nullptr;

	//------------------------------
	//インスタンス生成
	//------------------------------
	//キーボードの生成
	if (m_pInputKeyboard == nullptr) m_pInputKeyboard = new CInputKeyboard;
	if (m_pInputKeyboard != nullptr) m_pInputKeyboard->Init(hInstance, hWnd);	//初期化
	//ゲームパッドの生成(Xinput)
	if (m_pInputGamepadX == nullptr) m_pInputGamepadX = new CInputGamepadX;
	if (m_pInputGamepadX != nullptr) {
		//初期化
		m_pInputGamepadX->Init();
		//現在の入力デバイスの設定		
		if (m_pInputGamepadX->GetConnectGamepad(0)) {	//ゲームパッドが接続されている場合
			m_pInputCur = m_pInputGamepadX;	//ゲームパッド操作
			m_bEnableXInput = true;
		}
		else {	//ゲームパッドが接続されていない場合
			m_pInputCur = m_pInputKeyboard;	//キーボード操作
			m_bEnableXInput = false;
		}
	}

	//レンダラーのインスタンス生成
	if (m_pRenderer == nullptr) m_pRenderer = new CRenderer;
	if (m_pRenderer != nullptr) m_pRenderer->Init(hWnd, bWindow);

	//サウンドの生成
	if (m_pSound == nullptr) m_pSound = new CSound;
	if (m_pSound != nullptr) m_pSound->Init(hWnd);

	//フェードの生成
	if (m_pFade == nullptr) m_pFade = new CFade;
	if (m_pFade != nullptr) m_pFade->Init();

	//テクスチャのロード
	CTexture::AllSceneTextureLoad();

	//------------------------------
	//ロード
	//------------------------------
	//モデルのロード
	CModel::Load();

	//エフェクト情報のロード
	CLoadEffect::EffectStateLoad(LOAD_PRESET_TEXT);
	CPlane::CreateTextureFile();
	CSphere::CreateTextureSphere();

	//シーンの生成
	CScene::ChangeScene(m_pScene, CScene::SCENE_TYPE::SELECT_GAME);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void) {
	//オブジェクトの破棄
	CObject::ReleaseAll();

	//フェードの破棄
	if (m_pFade != nullptr) {
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	//シーンの破棄
	if (m_pScene != nullptr) {
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//カメラの破棄
	if (m_pCamera != nullptr) {
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//サウンドの破棄
	if (m_pSound != nullptr) {
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	//モデルのアンロード
	CModel::Unload();
	//テクスチャのアンロード
	CTexture::Unload(true);
	//レンダラーの破棄
	if (m_pRenderer != nullptr) {
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//キーボードの破棄
	if (m_pInputKeyboard != nullptr) {
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}
	//ゲームパッドの破棄(Xinput)
	if (m_pInputGamepadX != nullptr) {
		m_pInputGamepadX->Uninit();
		delete m_pInputGamepadX;
		m_pInputGamepadX = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void) {
	//サウンドの再生開始時フラグをリセット
	if (m_pSound != nullptr) {
		m_pSound->ResetBeginPlay();
	}

	//キーボードの更新処理
	if (m_pInputKeyboard != nullptr) {
		m_pInputKeyboard->Update();
	}
	//ゲームパッドの更新処理(Xinput)
	if (m_pInputGamepadX != nullptr) {
		m_pInputGamepadX->Update();
	}
	//現在の入力デバイスの設定
	if (m_pInputGamepadX != nullptr) {
		//ゲームパッドが接続されている場合
		if (m_pInputGamepadX->GetConnectGamepad(0)) {
			m_pInputCur = m_pInputGamepadX;
			m_bEnableXInput = true;
		}
		else {
			m_pInputCur = m_pInputKeyboard;
			m_bEnableXInput = false;
		}
	}

	//レンダラーの更新処理
	if (m_pRenderer != nullptr) {
		m_pRenderer->Update();
	}

	//ローディング画面の処理
	LoadingPolygon();

	//シーンの更新処理
	if (m_pScene != nullptr) m_pScene->Update();

	//ロードが終了したら
	if (CTexture::GetLoadFinish())
	{
		//フェードの更新処理
		if (m_pFade != nullptr) m_pFade->Update();
	}

	//カメラの更新
	if (m_pCamera != nullptr) m_pCamera->Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void) {
	//レンダラーの描画
	if (m_pRenderer != nullptr) m_pRenderer->Draw();
}

//=============================================================================
// シーンの変更
//=============================================================================
void CManager::ChangeScene(int nTypeScene) {
	//シーンの変更
	CScene::ChangeScene(m_pScene, (CScene::SCENE_TYPE)nTypeScene);
}

//=============================================================================
// カメラの設定
//=============================================================================
void CManager::SetCamera(CCamera* pCamera) {
	if (pCamera == nullptr) return;
	//現在のカメラの破棄
	if (m_pCamera != nullptr) m_pCamera->Uninit();
	//新しいカメラの設定
	m_pCamera = pCamera;
}

//=============================================================================
// ゲームシーンの取得
//=============================================================================
CGameScene* CManager::GetGameScene(void) {
	return dynamic_cast<CGameScene*>(m_pScene);
}