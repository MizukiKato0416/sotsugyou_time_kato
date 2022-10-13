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

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CPlayerIcon::CPlayerIcon()
{
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// デストラクタ
//=============================================================================
CPlayerIcon::~CPlayerIcon()
{
	m_texTypeFrame = CTexture::TEXTURE_TYPE::NONE;
	m_texTypePlayerNum = CTexture::TEXTURE_TYPE::NONE;
}

//=============================================================================
// 生成処理
//=============================================================================
CPlayerIcon* CPlayerIcon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale,
	                             const CTexture::TEXTURE_TYPE texTypeFrame, const CTexture::TEXTURE_TYPE texTypePlayerNum) {
	CPlayerIcon* pPlayerIcon;
	pPlayerIcon = new CPlayerIcon();
	if (pPlayerIcon == nullptr) return nullptr;

	pPlayerIcon->m_texTypeFrame = texTypeFrame;
	pPlayerIcon->m_texTypePlayerNum = texTypePlayerNum;
	pPlayerIcon->m_scale = scale;
	pPlayerIcon->SetPos(pos);
	pPlayerIcon->Init();

	return pPlayerIcon;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayerIcon::Init(void) {
	
	//吹き出しの生成
	//CObject2D::Create(GetPos(), m_texTypeFrame, PLAYER_ICON_FRAME_SIZE);

	//プレイヤー番号の生成
	//CObject2D::Create(GetPos(), m_texTypePlayerNum, PLAYER_ICON_PLAYER_NUM_SIZE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayerIcon::Uninit(void) {


	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayerIcon::Update(void) {
	
}