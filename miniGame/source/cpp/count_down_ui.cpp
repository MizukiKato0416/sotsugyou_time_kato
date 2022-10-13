//=============================================================================
//
// カウントダウンUI処理 [count_down_ui.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "count_down_ui.h"
#include "object2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define COUNT_DOWN_UI_NUMBER_SIZE_X			(188.0f)			//ナンバーのサイズX
#define COUNT_DOWN_UI_NUMBER_SIZE_Y			(226.0f)			//ナンバーのサイズY
#define COUNT_DOWN_UI_START_SIZE_X			(434.0f * 0.8f)		//STARTのサイズX
#define COUNT_DOWN_UI_START_SIZE_Y			(127.0f * 0.8f)		//STARTのサイズY

#define COUNT_DOWN_UI_NUMBER_SIZE_ADD_X		(COUNT_DOWN_UI_NUMBER_SIZE_X / 38.0f)		//ナンバーサイズ加算値
#define COUNT_DOWN_UI_NUMBER_SIZE_ADD_Y		(COUNT_DOWN_UI_NUMBER_SIZE_Y / 38.0f)		//ナンバーサイズ加算値
#define COUNT_DOWN_UI_START_SIZE_ADD		(1.02f)										//スタートサイズ加算値
#define COUNT_DOWN_UI_START_ADD_ALPHA		(0.1f)										//スタートα値加算値
#define COUNT_DOWN_UI_START_DEC_ALPHA		(0.1f)										//スタートα値減算値

#define COUNT_DOWN_UI_NEXT_UI_COUNT					(60)		//次のUIにするまでのカウント
#define COUNT_DOWN_UI_NUMBER_SIZE_DEC_COUNT			(10)		//ナンバーUIを小さくするタイミングのカウント 
#define COUNT_DOWN_UI_NUMBER_SIZE_DEC_STOP_COUNT	(20)		//ナンバーUIを小さくするのをやめるタイミングのカウント 
#define COUNT_DOWN_UI_START_ALPHA_DEC_COUNT			(30)		//スタートUIを薄くするタイミングのカウント 

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCountDownUi::CCountDownUi()
{
	m_pCountUi = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_bStart = false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CCountDownUi::~CCountDownUi()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CCountDownUi* CCountDownUi::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale) {
	CCountDownUi* pCountDownUi;
	pCountDownUi = new CCountDownUi();
	if (pCountDownUi == nullptr) return nullptr;

	pCountDownUi->m_pos = pos;
	pCountDownUi->m_scale = scale;
	pCountDownUi->SetPos(pos);
	pCountDownUi->Init();

	return pCountDownUi;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCountDownUi::Init(void) {
	
	//変数初期化
	m_bStart = false;

	//カウントダウンUIの生成
	m_pCountUi = CObject2D::Create(m_pos, CTexture::TEXTURE_TYPE::COUNT_DOWN_3,
		                           COUNT_DOWN_UI_NUMBER_SIZE_X * m_scale.x, COUNT_DOWN_UI_NUMBER_SIZE_Y * m_scale.y);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCountDownUi::Uninit(void) {

	if (m_pCountUi != nullptr)
	{
		m_pCountUi->Uninit();
		m_pCountUi = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCountDownUi::Update(void) {
	//生成されていたら
	if (m_pCountUi != nullptr)
	{
		//ゲームスタートじゃないとき
		if (m_pCountUi->GetTexType() != CTexture::TEXTURE_TYPE::COUNT_DOWN_START)
		{
			if (m_nCounter >= COUNT_DOWN_UI_NEXT_UI_COUNT)
			{
				//サイズを元に戻す
				m_pCountUi->SetSize(D3DXVECTOR3(COUNT_DOWN_UI_NUMBER_SIZE_X * m_scale.x, COUNT_DOWN_UI_NUMBER_SIZE_Y * m_scale.y, 0.0f));
				m_nCounter = 0;

				//テクスチャの変更
				if (m_pCountUi->GetTexType() == CTexture::TEXTURE_TYPE::COUNT_DOWN_3)
				{
					m_pCountUi->SetTexType(CTexture::TEXTURE_TYPE::COUNT_DOWN_2);
				}
				else if (m_pCountUi->GetTexType() == CTexture::TEXTURE_TYPE::COUNT_DOWN_2)
				{
					m_pCountUi->SetTexType(CTexture::TEXTURE_TYPE::COUNT_DOWN_1);
				}
				else
				{
					m_pCountUi->SetTexType(CTexture::TEXTURE_TYPE::COUNT_DOWN_START);

					//色取得
					D3DXCOLOR col = m_pCountUi->GetColor();
					//薄くする
					col.a = 0.0f;
					//色設定
					m_pCountUi->SetColor(col);
					//サイズを設定
					m_pCountUi->SetSize(D3DXVECTOR3(COUNT_DOWN_UI_START_SIZE_X * m_scale.x, COUNT_DOWN_UI_START_SIZE_Y * m_scale.y, 0.0f));
					//スタート状態にする
					m_bStart = true;
				}
			}
			else if (m_nCounter < COUNT_DOWN_UI_NUMBER_SIZE_DEC_STOP_COUNT)
			{
				//サイズの変更量
				float fAddSizeX = -COUNT_DOWN_UI_NUMBER_SIZE_ADD_X;
				float fAddSizeY = -COUNT_DOWN_UI_NUMBER_SIZE_ADD_Y;

				//サイズ取得
				D3DXVECTOR3 size = m_pCountUi->GetSize();

				if (m_nCounter < COUNT_DOWN_UI_NUMBER_SIZE_DEC_COUNT)
				{
					fAddSizeX *= -1.0f;
					fAddSizeY *= -1.0f;
				}

				//サイズを変える
				size.x += fAddSizeX;
				size.y += fAddSizeY;

				//サイズ設定
				m_pCountUi->SetSize(size);
			}
		}
		else
		{//ゲームスタートの時
			if (m_nCounter >= COUNT_DOWN_UI_START_ALPHA_DEC_COUNT)
			{
				//カラー取得
				D3DXCOLOR col = m_pCountUi->GetColor();
				//薄くする
				col.a -= COUNT_DOWN_UI_START_DEC_ALPHA;
				//見えなくなったら
				if (col.a <= 0.0f)
				{
					//消す
					m_pCountUi->Uninit();
					m_pCountUi = nullptr;
					return;
				}
				else
				{
					//色設定
					m_pCountUi->SetColor(col);
				}
			}
			else
			{
				//カラー取得
				D3DXCOLOR col = m_pCountUi->GetColor();
				//見えないなら
				if (col.a < 1.0f)
				{
					//濃くする
					col.a += COUNT_DOWN_UI_START_ADD_ALPHA;
					
					if (col.a > 1.0f)
					{
						col.a = 1.0f;
					}

					//色設定
					m_pCountUi->SetColor(col);
				}
			}

			//サイズ取得
			D3DXVECTOR3 size = m_pCountUi->GetSize();
			//サイズを変える
			size *= COUNT_DOWN_UI_START_SIZE_ADD;
			//サイズ設定
			m_pCountUi->SetSize(size);
		}
	}

	m_nCounter++;
}