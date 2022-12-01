//=============================================================================
//
// 次に進むボタンUI処理 [next_button.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "next_button.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CNextButton::CNextButton()
{
	m_nFrameCounter = 0;
	m_nCounter = 0;
	m_fDecAlpha = 0.0f;
}
//=============================================================================
// デストラクタ
//=============================================================================
CNextButton::~CNextButton()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CNextButton* CNextButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const CTexture::TEXTURE_TYPE texType,
		                         const int nCounter, const float fDecAlpha) {
	CNextButton* pNextButton;
	pNextButton = new CNextButton();
	if (pNextButton == nullptr) return nullptr;

	pNextButton->m_nCounter = nCounter;
	pNextButton->m_fDecAlpha = fDecAlpha;
	pNextButton->Init();
	pNextButton->SetPos(pos);
	pNextButton->SetSize(size);
	pNextButton->SetTexType(texType);

	return pNextButton;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNextButton::Init(void) {

	//変数初期化
	m_nFrameCounter = 0;

	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNextButton::Uninit(void) {
	CObject2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CNextButton::Update(void) {

	//カラー取得
	D3DXCOLOR col = GetColor();

	if (col.a <= 0.0f)
	{
		m_nFrameCounter++;
		if (m_nFrameCounter <= m_nCounter) return;

		//指定されたフレームになったら
		m_nFrameCounter = 0;
		//見えるようにする
		col.a = 1.0f;
		
	}
	else
	{
		//薄くする
		col.a -= m_fDecAlpha;
	}
	//カラー設定
	SetColor(col);

	CObject2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CNextButton::Draw(void) {
	CObject2D::Draw();
}