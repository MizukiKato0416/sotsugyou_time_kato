//=============================================================================
//
// プレイヤーアイコン処理 [player_icon.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "player_icon.h"
#include "object2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_ICON_FRAME_SIZE			(D3DXVECTOR3(373.0f, 261.0f, 0.0f))		//フレームの大きさ
#define PLAYER_ICON_PLAYER_NUM_SIZE		(D3DXVECTOR3(201.0f, 181.0f, 0.0f))		//プレイヤー番号の大きさ

#define PLAYER_ICON_ADD_ALPHA			(0.09f)		//α値加算量

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObjectPlayerIcon::CObjectPlayerIcon()
{
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_texTypeFrame = CTexture::TEXTURE_TYPE::NONE;
	m_texTypePlayerNum = CTexture::TEXTURE_TYPE::NONE;
	m_pFrame = nullptr;
	m_pPlayerNum = nullptr;
	m_state = STATE::ADD_ALPHA;
}
//=============================================================================
// デストラクタ
//=============================================================================
CObjectPlayerIcon::~CObjectPlayerIcon()
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CObjectPlayerIcon* CObjectPlayerIcon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale,
	                             const CTexture::TEXTURE_TYPE texTypeFrame, const CTexture::TEXTURE_TYPE texTypePlayerNum) {
	CObjectPlayerIcon* pPlayerIcon;
	pPlayerIcon = new CObjectPlayerIcon();
	if (pPlayerIcon == nullptr) return nullptr;

	pPlayerIcon->m_texTypeFrame = texTypeFrame;
	pPlayerIcon->m_texTypePlayerNum = texTypePlayerNum;
	pPlayerIcon->m_scale = scale;
	pPlayerIcon->m_pos = pos;
	pPlayerIcon->Init();

	return pPlayerIcon;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObjectPlayerIcon::Init(void) {
	//吹き出しの生成
	m_pFrame = CObject2D::Create(m_pos, m_texTypeFrame, PLAYER_ICON_FRAME_SIZE.x * m_scale.x, PLAYER_ICON_FRAME_SIZE.y * m_scale.y);
	//カラー設定
	m_pFrame->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	//ちょっと右にずらすよ
	m_pos.x += 10.0f;
	//プレイヤー番号の生成
	m_pPlayerNum = CObject2D::Create(m_pos, m_texTypePlayerNum, PLAYER_ICON_PLAYER_NUM_SIZE.x * m_scale.x, PLAYER_ICON_PLAYER_NUM_SIZE.y * m_scale.y);
	//カラー設定
	m_pPlayerNum->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObjectPlayerIcon::Uninit(void) {

	if (m_pFrame != nullptr)
	{
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pPlayerNum != nullptr)
	{
		m_pPlayerNum->Uninit();
		m_pPlayerNum = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CObjectPlayerIcon::Update(void) {
	
	switch (m_state)
	{
	case CObjectPlayerIcon::STATE::ADD_ALPHA:
		//α値加算処理
		StateAddAlpha();
		break;
	case CObjectPlayerIcon::STATE::NONE:
		//何もしない処理
		StateNone();
		break;
	case CObjectPlayerIcon::STATE::DEC_ALPHA:
		//α値減算処理
		StateDecAlpha();
		break;
	default:
		break;
	}
}

//=============================================================================
//α値加算処理
//=============================================================================
void CObjectPlayerIcon::StateAddAlpha(){

	int nCntClear = 0;

	//生成されていたら
	if (m_pFrame != nullptr)
	{
		//カラー取得
		D3DXCOLOR col = m_pFrame->GetColor();

		if (col.a < 1.0f)
		{
			//濃くする
			col.a += PLAYER_ICON_ADD_ALPHA;
			if (col.a > 1.0f)
			{
				col.a = 1.0f;
				nCntClear++;
			}
			//色設定
			m_pFrame->SetColor(col);
		}
	}

	//生成されていたら
	if (m_pPlayerNum != nullptr)
	{
		//カラー取得
		D3DXCOLOR col = m_pPlayerNum->GetColor();

		if (col.a < 1.0f)
		{
			//濃くする
			col.a += PLAYER_ICON_ADD_ALPHA;
			if (col.a > 1.0f)
			{
				col.a = 1.0f;
				nCntClear++;
			}
			//色設定
			m_pPlayerNum->SetColor(col);
		}
	}

	if (nCntClear == 2)
	{
		m_state = STATE::NONE;
	}
}

//=============================================================================
//何もしない処理
//=============================================================================
void CObjectPlayerIcon::StateNone(){

	//生成されていたら
	if (m_pFrame != nullptr)
	{
		//カラー取得
		D3DXCOLOR col = m_pFrame->GetColor();

		if (col.a != 1.0f)
		{
			col.a = 1.0f;
			//色設定
			m_pFrame->SetColor(col);
		}
	}

	//生成されていたら
	if (m_pPlayerNum != nullptr)
	{
		//カラー取得
		D3DXCOLOR col = m_pPlayerNum->GetColor();

		if (col.a != 1.0f)
		{
			col.a = 1.0f;
			//色設定
			m_pPlayerNum->SetColor(col);
		}
	}
}

//=============================================================================
//α値減算処理
//=============================================================================
void CObjectPlayerIcon::StateDecAlpha(){
	//生成されていたら
	if (m_pFrame != nullptr)
	{
		//カラー取得
		D3DXCOLOR col = m_pFrame->GetColor();

		if (col.a > 0.0f)
		{
			//薄くする
			col.a -= PLAYER_ICON_ADD_ALPHA;
			//色設定
			m_pFrame->SetColor(col);
			if (col.a < 0.0f)
			{
				col.a = 0.0f;
				//消す
				m_pFrame->Uninit();
				m_pFrame = nullptr;
			}
		}
	}

	//生成されていたら
	if (m_pPlayerNum != nullptr)
	{
		//カラー取得
		D3DXCOLOR col = m_pPlayerNum->GetColor();

		if (col.a > 0.0f)
		{
			//薄くする
			col.a -= PLAYER_ICON_ADD_ALPHA;
			//色設定
			m_pPlayerNum->SetColor(col);
			if (col.a < 0.0f)
			{
				col.a = 0.0f;
				//消す
				m_pPlayerNum->Uninit();
				m_pPlayerNum = nullptr;
			}
		}
	}
}