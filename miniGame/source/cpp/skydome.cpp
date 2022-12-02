//=============================================================================
//
// ドームの空の処理 [skydome.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "skydome.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSkyDome::CSkyDome() : CMeshdome()
{

}

//=============================================================================
// オーバーロードされたコンストラクタ
//=============================================================================
CSkyDome::CSkyDome(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumXZ, int nNumY, float fRadius) : CMeshdome(pos, rot, nNumXZ, nNumY, fRadius, false)
{
	//描画順の設定
	SetDrawPriority(DRAW_PRIORITY::BG);	//背景

	SetTexType(CTexture::TEXTURE_TYPE::MESH_CLOUD_DOME);
}

//=============================================================================
// デストラクタ
//=============================================================================
CSkyDome::~CSkyDome()
{

}

//=============================================================================
// ドームの空の生成処理
//=============================================================================
CSkyDome* CSkyDome::Create(D3DXVECTOR3 pos, int nNumXZ, int nNumY, float fRadius, float fRotSpeed) {
	CSkyDome* pSkyDome;
	pSkyDome = new CSkyDome(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), nNumXZ, nNumY, fRadius);
	if (pSkyDome == nullptr) return nullptr;

	pSkyDome->Init();

	//加算合成をする
	pSkyDome->SetAlphaBlend(true);
	//描画順の設定
	pSkyDome->SetDrawPriority(CObject::DRAW_PRIORITY::CLEAR);
	//ライトをオフにする
	pSkyDome->SetLight(false);
	//回転量の設定
	pSkyDome->SetRotate(D3DXVECTOR3(0.f, fRotSpeed, 0.f));

	return pSkyDome;
}

//=============================================================================
// ドームの空を球状に生成処理
//=============================================================================
void CSkyDome::CreateSphere(D3DXVECTOR3 pos, int nNumXZ, int nNumY, float fRadius, float fRotSpeed) {
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//空の角度
		D3DXVECTOR3 offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//下半分の設定
		if (nCnt == 1) {
			rot = D3DXVECTOR3(D3DX_PI, 0.0f, 0.0f);
			offset = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		}
		
		CSkyDome* pSkyDome;
		pSkyDome = new CSkyDome(pos + offset, rot, nNumXZ, nNumY, fRadius);
		if (pSkyDome == nullptr) return;

		pSkyDome->Init();

		//加算合成をする
		pSkyDome->SetAlphaBlend(true);
		//描画順の設定
		pSkyDome->SetDrawPriority(CObject::DRAW_PRIORITY::CLEAR);
		//ライトをオフにする
		pSkyDome->SetLight(false);
		//回転量の設定
		pSkyDome->SetRotate(D3DXVECTOR3(0.f, fRotSpeed, 0.f));
	}
}

//=============================================================================
// ドームの空の初期化処理
//=============================================================================
HRESULT CSkyDome::Init(void) {
	CMeshdome::Init();

	return S_OK;
}

//=============================================================================
// ドームの空の終了処理
//=============================================================================
void CSkyDome::Uninit(void) {
	CMeshdome::Uninit();
}

//=============================================================================
// ドームの空の更新処理
//=============================================================================
void CSkyDome::Update(void) {
	CMeshdome::Update();
}

//=============================================================================
// ドームの空の描画処理
//=============================================================================
void CSkyDome::Draw(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;
	//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;

	//Zテクスチャに書き込まない
	if (pRenderer->GetDrawZTex()) return;

	bool bDefFog = pRenderer->GetEffectFogEnable();	//現在のフォグを取得
	//フォグなし
	pRenderer->SetEffectFogEnable(false);

	//描画
	CMeshdome::Draw();

	//フォグの状態を戻す
	pRenderer->SetEffectFogEnable(bDefFog);
}