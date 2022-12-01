//=============================================================================
//
// チェックアイコン処理 [check_icon.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "check_icon.h"
#include "object2D.h"
#include "input.h"
#include "manager.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CHECK_ICON_FRAME_DEFAULT_SIZE		(D3DXVECTOR3(320.0f, 320.0f, 0.0f))						//フレームのデフォルトサイズ
#define CHECK_ICON_BUTTON_DEFAULT_SIZE		(D3DXVECTOR3(250.0f * 0.8f, 250.0 * 0.8f, 0.0f))		//ボタンのデフォルトサイズ
#define CHECK_ICON_BUTTON_POS_Y				(25.0f)													//ボタンの位置Y調整値

#define CHECK_ICON_DEC_ALPHA		(0.05f)			//α値減算量

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCheckIcon::CCheckIcon()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pFrame = nullptr;
	m_pButton = nullptr;
	m_nPlayerNum = 0;
	m_nCounter = 0;
	m_nDelay = 0;
	m_bCheck = false;
	m_bUninit = false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CCheckIcon::~CCheckIcon()
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CCheckIcon* CCheckIcon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale, const int nNumPlayer) {
	CCheckIcon* pCheckIcon;
	pCheckIcon = new CCheckIcon();
	if (pCheckIcon == nullptr) return nullptr;

	pCheckIcon->m_pos = pos;
	pCheckIcon->m_scale = scale;
	pCheckIcon->m_nPlayerNum = nNumPlayer;
	pCheckIcon->Init();

	return pCheckIcon;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCheckIcon::Init(void) {
	
	//変数初期化
	m_bCheck = false;
	m_bUninit = false;
	m_nCounter = 0;
	m_nDelay = 0;

	//フレームの生成
	m_pFrame = CObject2D::Create(m_pos, CTexture::TEXTURE_TYPE((int)CTexture::TEXTURE_TYPE::CHECK_ICON_FRAME_1 + m_nPlayerNum - 1),
		                         CHECK_ICON_FRAME_DEFAULT_SIZE.x * m_scale.x, CHECK_ICON_FRAME_DEFAULT_SIZE.y * m_scale.y);

	//ボタンの生成
	m_pButton = CObject2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + CHECK_ICON_BUTTON_POS_Y, 0.0f),
		                          CTexture::TEXTURE_TYPE((int)CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_1 + m_nPlayerNum - 1),
								  CHECK_ICON_BUTTON_DEFAULT_SIZE.x * m_scale.x, CHECK_ICON_BUTTON_DEFAULT_SIZE.y * m_scale.y);


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCheckIcon::Uninit(void) {

	if (m_pFrame != nullptr)
	{
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pButton != nullptr)
	{
		m_pButton->Uninit();
		m_pButton = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCheckIcon::Update(void) {
	
	//チェック出来ていなかったら
	if (!m_bCheck)
	{
		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		CInput* pInput = nullptr;
		if (pManager != nullptr) {
			//現在の入力デバイスの取得
			pInput = pManager->GetInputCur();
		}

		//ボタンを押したら
		if (pInput->GetTrigger(CInput::CODE((int)CInput::CODE::CHECK_X + m_nPlayerNum - 1), m_nPlayerNum - 1))
		{
			//チェック状態にする
			m_bCheck = true;

			//ボタンのテクスチャ変更
			m_pButton->SetTexType(CTexture::TEXTURE_TYPE((int)CTexture::TEXTURE_TYPE::CHECK_ICON_OK_1 + m_nPlayerNum - 1));

			//マネージャーの取得
			CManager* pManager = CManager::GetManager();
			//サウンドの取得
			CSound* pSound = nullptr;
			if (pManager != nullptr) pSound = pManager->GetSound();
			//音を再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_OK);
		}
	}

	if (m_bUninit)
	{
		//α値減算処理
		DecAlpha();
	}
}

//=============================================================================
//α値減算処理
//=============================================================================
void CCheckIcon::DecAlpha()
{
	if (m_nCounter >= m_nDelay)
	{
		m_nCounter = m_nDelay;

		if (m_pFrame != nullptr)
		{
			//色取得
			D3DXCOLOR flameCol = m_pFrame->GetColor();
			//薄くする
			flameCol.a -= CHECK_ICON_DEC_ALPHA;
			//見えなくなったら
			if (flameCol.a <= CHECK_ICON_DEC_ALPHA)
			{
				//消す
				m_pFrame->Uninit();
				m_pFrame = nullptr;
			}
			else
			{
				//カラー設定
				m_pFrame->SetColor(flameCol);
			}
		}

		if (m_pButton != nullptr)
		{
			//色取得
			D3DXCOLOR bttonCol = m_pButton->GetColor();
			//薄くする
			bttonCol.a -= CHECK_ICON_DEC_ALPHA;
			//見えなくなったら
			if (bttonCol.a <= CHECK_ICON_DEC_ALPHA)
			{
				//消す
				m_pButton->Uninit();
				m_pButton = nullptr;
			}
			else
			{
				//カラー設定
				m_pButton->SetColor(bttonCol);
			}
		}
	}
	else
	{
		m_nCounter++;
	}
}
