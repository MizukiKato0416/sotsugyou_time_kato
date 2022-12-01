//=============================================================================
//
// ボム生成処理 [create_bom_manager.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "create_bom_manager.h"
#include "bom.h"
#include "gameScene02.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CREATE_BOM_MANAGER_BOM_POS_Y		(500.0f)		//ボムを生成する位置Y

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCreateBomManager::CCreateBomManager()
{
	m_nFrameCounter = 0;
	m_nFrame = 0;
	m_nNumBom = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CCreateBomManager::~CCreateBomManager()
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CCreateBomManager* CCreateBomManager::Create(const int nFrame, const int nNumBom) {
	CCreateBomManager* pCheckIcon;
	pCheckIcon = new CCreateBomManager();
	if (pCheckIcon == nullptr) return nullptr;

	pCheckIcon->m_nFrame = nFrame;
	pCheckIcon->m_nNumBom = nNumBom;
	pCheckIcon->Init();

	return pCheckIcon;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCreateBomManager::Init(void) {
	
	//変数初期化
	m_nFrameCounter = 0;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCreateBomManager::Uninit(void) {
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCreateBomManager::Update(void) {
	
	m_nFrameCounter++;

	if (m_nFrameCounter > m_nFrame)
	{
		m_nFrameCounter = 0;

		float fRot = 0.0f;
		float fDiffer = 0.0f;
		D3DXVECTOR3 bomPos = D3DXVECTOR3(0.0f, CREATE_BOM_MANAGER_BOM_POS_Y, 0.0f);

		//ボムの生成
		for (int nCntBom = 0; nCntBom < m_nNumBom; nCntBom++)
		{
			//遠さをランダムで決める
			fDiffer = (rand() % (int)(GAME_02_STAGE_SIZE) * 100.0f) / 100.0f;
			//向きをランダムで決める
			fRot = (rand() % 629 + -314) / 100.0f;

			//決めた位置に出す
			bomPos.x = sinf(fRot) * fDiffer;
			bomPos.z = cosf(fRot) * fDiffer;

			CBom::Create(bomPos);
		}
	}
}