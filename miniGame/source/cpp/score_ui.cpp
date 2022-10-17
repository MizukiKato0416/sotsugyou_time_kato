//=============================================================================
//
// スコアUI処理 [score_ui.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "score_ui.h"
#include "object2D.h"
#include "score.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SCORE_UI_FRAME_SIZE		(D3DXVECTOR3(500.0f, 150.0f, 0.0f))	//フレームのサイズ
#define SCORE_UI_SCORE_SIZE		(90.0f)								//スコアのサイズ
#define SCORE_UI_SCORE_POS_X	(10.0f)								//スコアの位置

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CScoreUi::CScoreUi()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nPlayerNum = 0;
	m_pFrame = nullptr;
	m_pScore = nullptr;
}
//=============================================================================
// デストラクタ
//=============================================================================
CScoreUi::~CScoreUi()
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CScoreUi* CScoreUi::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale, const int nNumPlayer) {
	CScoreUi* pScoreUi;
	pScoreUi = new CScoreUi();
	if (pScoreUi == nullptr) return nullptr;

	pScoreUi->m_pos = pos;
	pScoreUi->m_scale = scale;
	pScoreUi->m_nPlayerNum = nNumPlayer;
	pScoreUi->Init();

	return pScoreUi;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScoreUi::Init(void) {
	
	//フレームの生成
	m_pFrame = CObject2D::Create(m_pos, CTexture::TEXTURE_TYPE((int)CTexture::TEXTURE_TYPE::SCORE_FRAME_1 + m_nPlayerNum - 1),
		                         SCORE_UI_FRAME_SIZE.x * m_scale.x, SCORE_UI_FRAME_SIZE.y * m_scale.y);

	//スコアの位置
	D3DXVECTOR3 scorePos = m_pos;
	//位置を上にあげる
	scorePos.y -= SCORE_UI_SCORE_SIZE * m_scale.x / 2.0f;
	//右にずらす
	scorePos.x += (SCORE_UI_SCORE_SIZE * m_scale.x / 2.0f) + (SCORE_UI_SCORE_SIZE * m_scale.x) + SCORE_UI_SCORE_POS_X;

	//スコアの生成
	m_pScore = CScore::Create(1, CTexture::TEXTURE_TYPE::NUMBER_003, scorePos, SCORE_UI_SCORE_SIZE * m_scale.x);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScoreUi::Uninit(void) {

	if (m_pFrame != nullptr)
	{
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScoreUi::Update(void) {
	
	
}