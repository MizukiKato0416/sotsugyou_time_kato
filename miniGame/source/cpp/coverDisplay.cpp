//=============================================================================
//
// 画面全体を覆う処理 [coverDisplay.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "coverDisplay.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCoverDisplay::CCoverDisplay()
{
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	SetEnableStencil(true);
}
//=============================================================================
// デストラクタ
//=============================================================================
CCoverDisplay::~CCoverDisplay()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CCoverDisplay* CCoverDisplay::Create(D3DXCOLOR col) {
	CCoverDisplay* pCoverDisplay;
	pCoverDisplay = new CCoverDisplay();
	if (pCoverDisplay == nullptr) return nullptr;

	pCoverDisplay->Init();
	pCoverDisplay->SetColor(col);

	return pCoverDisplay;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCoverDisplay::Init(void) {
	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCoverDisplay::Uninit(void) {
	CObject2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCoverDisplay::Update(void) {
	CObject2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CCoverDisplay::Draw(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;
	//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);

	CObject2D::Draw();

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
}