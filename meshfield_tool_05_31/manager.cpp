//================================================
//マネージャ処理
//Author:加藤瑞葵
//================================================
#include "renderer.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "input_pad_d.h"
#include "input_mouse.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "texture.h"
#include "x_load.h"
#include "game01.h"
#include "fade.h"
#include "sound.h"

//================================================
//静的メンバ変数宣言
//================================================
CManager *CManager::s_pManager = nullptr;
CRenderer *CManager::m_pRenderer = nullptr;
CInputKeyboard *CManager::m_pInputKeyboard = nullptr;
CInputPadX *CManager::m_pInputPadX = nullptr;
CInputPadD *CManager::m_pInputPadD = nullptr;
CInputMouse *CManager::m_pInputMouse = nullptr;
CCamera* CManager::m_apCamera[MAX_CAMERA] = { nullptr };
CLight *CManager::m_apLight[MAX_LIGHT] = { nullptr };
CTexture *CManager::m_pTexture = nullptr;
CXload *CManager::m_pXload = nullptr;
CGame01 *CManager::m_pGame01 = nullptr;
CManager::MODE CManager::m_mode = MODE::GAME01;
CFade *CManager::m_pFade = nullptr;
HWND CManager::m_hWnd = NULL;

//================================================
//デフォルトコンストラクタ
//================================================
CManager::CManager()
{
	
}

//================================================
//デストラクタ
//================================================
CManager::~CManager()
{

}

//================================================
//初期化処理
//================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//時刻で初期化
	srand((unsigned int)time(NULL));

	m_hWnd = hWnd;

	//レンダリングクラスの生成
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer;
		if (m_pRenderer != nullptr)
		{
			m_pRenderer->Init(hWnd, bWindow);
		}
	}

	//キーボードクラスの生成
	if (m_pInputKeyboard == nullptr)
	{
		m_pInputKeyboard = new CInputKeyboard;
		if (m_pInputKeyboard != nullptr)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	//Xパッドクラスの生成
	if (m_pInputPadX == nullptr)
	{
		m_pInputPadX = new CInputPadX;
		if (m_pInputPadX != nullptr)
		{
			m_pInputPadX->Init(hInstance, hWnd);
		}
	}

	//Dパッドクラスの生成
	if (m_pInputPadD == nullptr)
	{
		m_pInputPadD = new CInputPadD;
		if (m_pInputPadD != nullptr)
		{
			m_pInputPadD->Init(hInstance, hWnd);
		}
	}

	//マウスクラスの生成
	if (m_pInputMouse == nullptr)
	{
		m_pInputMouse = new CInputMouse;
		if (m_pInputMouse != nullptr)
		{
			m_pInputMouse->Init(hInstance, hWnd);
		}
	}

	//テクスチャクラスの生成
	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture;
		if (m_pTexture != nullptr)
		{
			m_pTexture->Init();
		}
	}

	//xファイル読み込みクラスの生成
	if (m_pXload == nullptr)
	{
		m_pXload = new CXload;
		if (m_pXload != nullptr)
		{
			m_pXload->Init();
		}
	}

	//ライトの生成
	m_apLight[0] = CLight::Create(D3DXVECTOR3(-0.6f, -0.5f, 0.6f), D3DXVECTOR3(40000.0f, 80000.0f, -40000.0f));
	m_apLight[1] = CLight::Create(D3DXVECTOR3(0.4f, 0.5f, -0.4f), D3DXVECTOR3(-10000.0f, 0.0f, 10000.0f));
	m_apLight[2] = CLight::Create(D3DXVECTOR3(0.0f, -0.2f, 0.6f), D3DXVECTOR3(10000.0f, 0.0f, -10000.0f));

	//フェードクラスの生成
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
							MODE::GAME01);	

	return S_OK;
}

//================================================
//終了処理
//================================================
void CManager::Uninit(void)
{
	//全てのオブジェクトの破棄
	CObject::ReleaseAll();

	//Xファイル読み込みクラスの破棄
	if (m_pXload != nullptr)
	{
		//終了処理
		m_pXload->Uninit();

		//メモリの開放
		delete m_pXload;
		m_pXload = nullptr;
	}

	//カメラの破棄
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (m_apCamera[nCntCamera] != nullptr)
		{
			//終了処理
			m_apCamera[nCntCamera]->Uninit();

			//メモリの開放
			delete m_apCamera[nCntCamera];
			m_apCamera[nCntCamera] = nullptr;
		}
	}

	//ライトの破棄
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		if (m_apLight[nCntLight] != nullptr)
		{
			//終了処理
			m_apLight[nCntLight]->Uninit();

			//メモリの開放
			delete m_apLight[nCntLight];
			m_apLight[nCntLight] = nullptr;
		}
	}

	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		//終了処理
		m_pTexture->Uninit();

		//メモリの開放
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//マウスクラスの破棄
	if (m_pInputMouse != nullptr)
	{
		//終了処理
		m_pInputMouse->Uninit();

		//メモリの開放
		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}

	//Dパッドクラスの破棄
	if (m_pInputPadD != nullptr)
	{
		//終了処理
		m_pInputPadD->Uninit();

		//メモリの開放
		delete m_pInputPadD;
		m_pInputPadD = nullptr;
	}

	//Xパッドクラスの破棄
	if (m_pInputPadX != nullptr)
	{
		//終了処理
		m_pInputPadX->Uninit();

		//メモリの開放
		delete m_pInputPadX;
		m_pInputPadX = nullptr;
	}

	//キーボードクラスの破棄
	if (m_pInputKeyboard != nullptr)
	{
		//終了処理
		m_pInputKeyboard->Uninit();

		//メモリの開放
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//レンダラークラスの破棄
	if (m_pRenderer != nullptr)
	{
		//終了処理
		m_pRenderer->Uninit();

		//メモリの開放
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//メモリの開放
	delete s_pManager;
	s_pManager = nullptr;
}

//================================================
//更新処理
//================================================
void CManager::Update(void)
{
	//キーボード
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	//Dパッド
	if (m_pInputPadD != nullptr)
	{
		m_pInputPadD->Update();
	}

	//マウス
	if (m_pInputMouse != nullptr)
	{
		m_pInputMouse->Update();
	}

	//Xパッド
	if (m_pInputPadX != nullptr)
	{
		m_pInputPadX->Update();
	}

	//レンダラー
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	//カメラの更新処理
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (m_apCamera[nCntCamera] != nullptr)
		{
			m_apCamera[nCntCamera]->Update();
		}
	}
}

//================================================
//描画処理
//================================================
void CManager::Draw(void)
{
	//レンダラー
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}

//================================================
//インスタンス取得処理
//================================================
CManager *CManager::GetInstance(void)
{
	if (s_pManager == nullptr)
	{
		s_pManager = new CManager;
	}
	return s_pManager;
}

//=============================================================================
// Renderer取得処理
//=============================================================================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// InputKeyboard取得処理
//=============================================================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// InputXPad取得処理
//=============================================================================
CInputPadX* CManager::GetInputPadX(void)
{
	return m_pInputPadX;
}

//=============================================================================
// InputDPad取得処理
//=============================================================================
CInputPadD* CManager::GetInputPadD(void)
{
	return m_pInputPadD;
}

//=============================================================================
// マウス取得処理
//=============================================================================
CInputMouse * CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//=============================================================================
// light取得処理
//=============================================================================
CLight* CManager::GetLight(void)
{
	return m_apLight[0];
}

//=============================================================================
// テクスチャ取得処理
//=============================================================================
CTexture* CManager::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// camera取得処理
//=============================================================================
CCamera** CManager::GetCamera(void)
{
	return &m_apCamera[0];
}

//=============================================================================
// Xload取得処理
//=============================================================================
CXload* CManager::GetXload(void)
{
	return m_pXload;
}

//=============================================================================
// game01取得処理
//=============================================================================
CGame01* CManager::GetGame01(void)
{
	return m_pGame01;
}

//=======================================================================
//モード設定処理
//=======================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE::GAME01:
		if (m_pGame01 != nullptr)
		{
			//カメラの破棄
			for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
			{
				if (m_apCamera[nCntCamera] != nullptr)
				{
					//終了処理
					m_apCamera[nCntCamera]->Uninit();

					//メモリの開放
					delete m_apCamera[nCntCamera];
					m_apCamera[nCntCamera] = nullptr;
				}
			}

			m_pGame01->Uninit();
			m_pGame01 = nullptr;
		}
		break;
	default:
		break;
	}

	//全てのオブジェクトの破棄
	CObject::ReleaseAll();

	m_mode = mode;

	switch (mode)
	{
	case MODE::GAME01:
		//ゲーム01クラスの生成
		if (m_pGame01 == nullptr)
		{
			m_pGame01 = new CGame01;
			if (m_pGame01 != nullptr)
			{
				//メインカメラの生成
				for (int nCntCamera = 0; nCntCamera < MAX_MAIN_CAMERA; nCntCamera++)
				{
					m_apCamera[nCntCamera] = CCamera::Create(CAMERA_INIT_POS, D3DXVECTOR3(CAMERA_INIT_ROT_X, D3DX_PI, 0.0f),
																(float)(SCREEN_WIDTH / MAX_MAIN_CAMERA * nCntCamera), 0.0f,
																(float)(SCREEN_WIDTH / MAX_MAIN_CAMERA), (float)SCREEN_HEIGHT);
					m_apCamera[nCntCamera]->SetNum(nCntCamera);
				}

				m_pGame01->Init();
			}
		}
		break;
	}
}


//=============================================================================
// モード取得処理
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// fade取得処理
//=============================================================================
CFade* CManager::GetFade(void)
{
	return m_pFade;
}