//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int CPlayer::m_nObjectPlayerNum = 0;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CPlayer::CPlayer()
{
	//総数を加算
	m_nObjectPlayerNum++;
	m_nIndex = m_nObjectPlayerNum;
	m_bUpdate = false;

}
//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CPlayer* CPlayer::Create() {
	CPlayer* pPlayer;
	pPlayer = new CPlayer();
	if (pPlayer == nullptr) return nullptr;

	pPlayer->Init();

	return pPlayer;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(void) {
	
	//変数初期化
	m_bUpdate = true;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void) {

	//総数を減らす
	m_nObjectPlayerNum--;

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void) {
	
}