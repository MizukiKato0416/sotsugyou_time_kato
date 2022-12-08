//=============================================================================
//
// ロードUI処理 [loading_ui.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "loading_ui.h"
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LOADING_UI_MAX_ANIM_X		(4)		//アニメーションのX最大値
#define LOADING_UI_MAX_ANIM_Y		(1)		//アニメーションのY最大値
#define LOADING_UI_ANIM_COUNTER		(20)	//アニメーションの速さ

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CLoadingUi::CLoadingUi()
{
	m_nFrameCounter = 0;
	m_nAnimCounter = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CLoadingUi::~CLoadingUi()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CLoadingUi* CLoadingUi::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size) {
	CLoadingUi* pLoadingUi;
	pLoadingUi = new CLoadingUi();
	if (pLoadingUi == nullptr) return nullptr;

	pLoadingUi->SetPos(pos);
	pLoadingUi->SetSize(size);
	pLoadingUi->Init();

	return pLoadingUi;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLoadingUi::Init(void) {
	//変数初期化
	m_nFrameCounter = 0;
	m_nAnimCounter = 0;

	//オブジェクトの初期化
	CObject2D::Init();

	//プライオリティの設定
	SetDrawPriority(CObject::DRAW_PRIORITY::LOADING);
	//テクスチャの設定
	SetTexType(CTexture::TEXTURE_TYPE::NOW_LOADING);
	//テクスチャの設定
	SetTexAnim(m_nAnimCounter, LOADING_UI_MAX_ANIM_X, LOADING_UI_MAX_ANIM_Y);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLoadingUi::Uninit(void) {
	//オブジェクトの破棄
	CObject2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLoadingUi::Update(void) {
	//フレームをカウント
	m_nFrameCounter++;
	if (m_nFrameCounter > LOADING_UI_ANIM_COUNTER)
	{
		m_nFrameCounter = 0;
		//アニメーションを進める
		m_nAnimCounter++;
		//最後まで行ったら最初に戻す
		if (m_nAnimCounter >= LOADING_UI_MAX_ANIM_X) m_nAnimCounter = 0;

		//テクスチャアニメーションの設定
		SetTexAnim(m_nAnimCounter, LOADING_UI_MAX_ANIM_X, LOADING_UI_MAX_ANIM_Y);
	}

	//更新処理
	CObject2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CLoadingUi::Draw(void) {
	//描画処理
	CObject2D::Draw();
}