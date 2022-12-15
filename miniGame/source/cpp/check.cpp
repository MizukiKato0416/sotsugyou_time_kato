//=============================================================================
//
// チェック処理 [check.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "check.h"
#include "check_icon.h"
#include "object2D.h"
#include "count_down_ui.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CHECK_CHECK_ICON_UNINIT_COUNT	(30)		//チェックアイコンが消えるまでの時間
#define CHECK_FRAME_DEC_ALPHA			(0.02f)		//背景のα値減少量

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCheck::CCheck()
{
	m_apCheckIcon.clear();
	m_nNumPlayer = 0;
	m_bCheckAll = false;
	m_bAllUninit = false;
	m_bCreateCountDownUi = false;
	m_pFrame = nullptr;
	m_state = STATE::NONE;
	m_pCountDownUi = nullptr;
	m_pTutorial = nullptr;
}
//=============================================================================
// デストラクタ
//=============================================================================
CCheck::~CCheck()
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CCheck* CCheck::Create(const int nNumPlayer) {
	CCheck* pCheckIcon;
	pCheckIcon = new CCheck();
	if (pCheckIcon == nullptr) return nullptr;

	pCheckIcon->m_nNumPlayer = nNumPlayer;
	pCheckIcon->Init();

	return pCheckIcon;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCheck::Init(void) {
	
	//変数初期化
	m_bCheckAll = false;
	m_bAllUninit = false;
	m_state = STATE::CHECK;
	m_pCountDownUi = nullptr;
	m_bCreateCountDownUi = true;

	//背景の暗いやつ
	m_pFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::CHECK_BG, SCREEN_WIDTH, SCREEN_HEIGHT);

	const float fDist = 380.0f;	//プレイヤー同士の距離

	for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
	{
		//プレイヤーモデルの位置
		D3DXVECTOR3 posModel = D3DXVECTOR3(fDist * (-m_nNumPlayer / 2.0f) + fDist / 2.0f + nCntPlayer * fDist, -50.0f, 0.0f);

		//チェックアイコンの生成
		m_apCheckIcon.push_back(CCheckIcon::Create(D3DXVECTOR3(SCREEN_WIDTH / (m_nNumPlayer * 2) * (1 + nCntPlayer * 2), SCREEN_HEIGHT / 2.0f, 0.0f),
			                                       posModel, D3DXVECTOR3(0.85f, 0.85f, 0.85f), nCntPlayer + 1));
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCheck::Uninit(void) {

	//生成されていたら
	if (m_pFrame != nullptr)
	{
		//消す
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
	{
		//アイコンが生成されていたら
		if (m_apCheckIcon[nCntPlayer] != nullptr)
		{
			//消す
			m_apCheckIcon[nCntPlayer]->Uninit();
			m_apCheckIcon[nCntPlayer] = nullptr;
		}
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCheck::Update(void) {
	
	switch (m_state)
	{
	case CCheck::STATE::CHECK:
		//チェック処理
		Check();
		break;
	case CCheck::STATE::COUNTDOWN:
		//カウントダウン処理
		CountDown();
		break;
	default:
		break;
	}
}

//=============================================================================
//フレームを消す処理
//=============================================================================
void CCheck::DecFrame()
{
	if (m_pFrame != nullptr)
	{
		//カラー取得
		D3DXCOLOR col = m_pFrame->GetColor();
		//薄くする
		col.a -= CHECK_FRAME_DEC_ALPHA;

		//見えなくなったら
		if (col.a <= 0.0f)
		{
			col.a = 0.0f;
			//消す
			m_pFrame->Uninit();
			m_pFrame = nullptr;
		}
		else
		{
			m_pFrame->SetColor(col);
		}
	}
}

//=============================================================================
//チェック処理
//=============================================================================
void CCheck::Check()
{
	//チェック出来ていなかったら
	if (!m_bCheckAll)
	{
		int nCheck = 0;
		int nNumPlayer = m_nNumPlayer;
#ifdef _DEBUG
		nNumPlayer = 1;
#else
		nNumPlayer = 1;
#endif // !_DEBUG

		for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
		{
			//アイコンが生成されていなかったら
			if (m_apCheckIcon[nCntPlayer] == nullptr)
			{
				continue;
			}

			if (m_apCheckIcon[nCntPlayer]->GetCheck())
			{
				//増やす
				nCheck++;
			}
		}

		//チェック数がプレイヤーの数と一致していたら
		if (nCheck == nNumPlayer)
		{
			//全員がチェック出来た状態にする
			m_bCheckAll = true;
		}
	}

	//全員がチェック出来たら
	if (m_bCheckAll)
	{
		//フレームを消す処理
		DecFrame();

		int nCntUninit = 0;
		for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
		{
			//アイコンが生成されていなかったら
			if (m_apCheckIcon[nCntPlayer] == nullptr)
			{
				nCntUninit++;
				continue;
			}

			//消さない状態なら
			if (!m_apCheckIcon[nCntPlayer]->GetUninit())
			{
				//消す
				m_apCheckIcon[nCntPlayer]->SetUninit(true, CHECK_CHECK_ICON_UNINIT_COUNT);
			}

			//UIが消えたなら
			if (m_apCheckIcon[nCntPlayer]->GetFrame() == nullptr &&m_apCheckIcon[nCntPlayer]->GetButton() == nullptr)
			{
				//消す
				m_apCheckIcon[nCntPlayer]->Uninit();
				m_apCheckIcon[nCntPlayer] = nullptr;
			}
		}

		//全部消えていたら且つ生成する状態なら
		if (nCntUninit == m_nNumPlayer && m_bCreateCountDownUi)
		{
			//カウントダウンUIの生成
			if (m_pCountDownUi == nullptr)
			{
				m_pCountDownUi = CCountDownUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			}

			m_bAllUninit = true;
			//カウントダウン状態にする
			m_state = STATE::COUNTDOWN;
		}
	}
}

//=============================================================================
//カウントダウン処理
//=============================================================================
void CCheck::CountDown()
{
	//カウントUIが消えていたら
	if (m_pCountDownUi->GetCountUi() == nullptr)
	{
		//カウントダウンUIを消す
		m_pCountDownUi->Uninit();
		m_pCountDownUi = nullptr;

		m_state = STATE::NONE;
	}
}