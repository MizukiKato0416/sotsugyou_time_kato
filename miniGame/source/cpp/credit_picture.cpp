//=============================================================================
//
// クレジットの絵処理 [credit_picture.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "credit_picture.h"
#include "object2D.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CREDIT_PICTURE_FRAME_SIZE		(1.8f)		//フレームのサイズ
#define CREDIT_PICTURE_OBJECT_NUM		(2)			//生成するオブジェクトの数

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCreditPicture::CCreditPicture()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRot = 0.0f;
	m_fMoveY = 0.0f;
	m_texType = CTexture::TEXTURE_TYPE::NONE;
	m_pPicture = nullptr;
	m_pFrame = nullptr;
}
//=============================================================================
// デストラクタ
//=============================================================================
CCreditPicture::~CCreditPicture()
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CCreditPicture* CCreditPicture::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale, const float fRot, const CTexture::TEXTURE_TYPE texType,
	                                   const float fMoveY) {
	CCreditPicture* pCreditPicture;
	pCreditPicture = new CCreditPicture();
	if (pCreditPicture == nullptr) return nullptr;

	pCreditPicture->m_pos = pos;
	pCreditPicture->m_scale = scale;
	pCreditPicture->m_fRot = fRot;
	pCreditPicture->m_texType = texType;
	pCreditPicture->m_fMoveY = fMoveY;
	pCreditPicture->Init();

	return pCreditPicture;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCreditPicture::Init(void) {
	
	//変数初期化
	
	//フレームの生成
	m_pFrame = CObject2D::Create(m_pos, CTexture::TEXTURE_TYPE::CREDIT_PICTURE_FRAME,
		                         SCREEN_WIDTH * CREDIT_PICTURE_FRAME_SIZE * m_scale.x, SCREEN_HEIGHT * CREDIT_PICTURE_FRAME_SIZE * m_scale.y);
	m_pFrame->SetAngle(3.14f);

	//絵の生成
	m_pPicture = CObject2D::Create(m_pos, m_texType, SCREEN_WIDTH * m_scale.x, SCREEN_HEIGHT * m_scale.y);
	m_pPicture->SetAngle(3.14f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCreditPicture::Uninit(void) {

	//破棄
	if (m_pPicture != nullptr)
	{
		m_pPicture->Uninit();
		m_pPicture = nullptr;
	}
	if (m_pFrame != nullptr)
	{
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCreditPicture::Update(void) {
	//消した数
	int nCntUninit = 0;
	//移動処理
	if (Move(m_pPicture)) nCntUninit++;
	if (Move(m_pFrame)) nCntUninit++;

	//全部消えたらクラス破棄
	if (nCntUninit >= CREDIT_PICTURE_OBJECT_NUM) Uninit();
}

//=============================================================================
//移動処理
//=============================================================================
bool CCreditPicture::Move(CObject2D * &pObject2D)
{
	if (pObject2D == nullptr) return true;

	//位置とサイズ取得
	D3DXVECTOR3 pos = pObject2D->GetPos();
	D3DXVECTOR3 size = pObject2D->GetSize();

	//移動
	pos.y += m_fMoveY;

	//位置反映
	pObject2D->SetPos(pos);

	//完全に見えなくなったら
	if (pos.y <= 0.0f - size.x / 2.0f)
	{
		//消す
		pObject2D->Uninit();
		pObject2D = nullptr;
		return true;
	}
	return false;
}
