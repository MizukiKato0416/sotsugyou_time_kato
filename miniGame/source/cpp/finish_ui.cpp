//=============================================================================
//
// フィニッシュUI処理 [finish.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "finish_ui.h"
#include "manager.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FINISH_UI_DEFAULT_SIZE		(D3DXVECTOR3(450.0f * 1.2f, 120.0f * 1.2f, 0.0f))											//UIのデフォルトサイズ
#define FINISH_UI_INIT_SIZE			(D3DXVECTOR3(FINISH_UI_DEFAULT_SIZE.x * 3.0f, FINISH_UI_DEFAULT_SIZE.y * 3.0f, 0.0f))		//UIの初期サイズ

#define FINISH_UI_DEC_SIZE			(0.93f)		//UIのサイズ減算値
#define FINISH_UI_ADD_SIZE			(1.01f)		//UIのサイズ加算値

#define FINISH_UI_INIT_COLOR		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))		//UIの初期カラー
#define FINISH_UI_ADD_COLOR_ALPHA	(0.2f)									//UIのα値加算量
#define FINISH_UI_DEC_COLOR_ALPHA	(0.015f)								//UIのα値減算量

#define FINISH_UI_STATE_NONE_COUNT	(60)									//何もしない状態の時間

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CFinishUi::CFinishUi()
{
	m_state = STATE::DEC_SIZE;
	m_nFrameCounter = 0;
	m_nDelay = 0;
	m_nDelayCounter = 0;
	m_fMaxAlpha = 0.0f;
}
//=============================================================================
// デストラクタ
//=============================================================================
CFinishUi::~CFinishUi()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CFinishUi* CFinishUi::Create(const D3DXVECTOR3 pos, const int nDelay, const float fMaxAlpha) {
	CFinishUi* pFinishUi;
	pFinishUi = new CFinishUi();
	if (pFinishUi == nullptr) return nullptr;

	pFinishUi->m_nDelay = nDelay;
	pFinishUi->m_fMaxAlpha = fMaxAlpha;
	pFinishUi->SetPos(pos);
	pFinishUi->SetSize(FINISH_UI_INIT_SIZE);
	pFinishUi->Init();

	return pFinishUi;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFinishUi::Init(void) {
	
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//音を再生
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_TIME_UP);

	//変数初期化
	m_state = STATE::DEC_SIZE;
	m_nFrameCounter = 0;
	m_nDelayCounter = 0;

	//テクスチャの設定
	SetTexType(CTexture::TEXTURE_TYPE::FINISH);

	//カラーの設定
	SetColor(FINISH_UI_INIT_COLOR);

	//オブジェクトの初期化
	CObject2D::Init();
	SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFinishUi::Uninit(void) {
	//オブジェクトの破棄
	CObject2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CFinishUi::Update(void) {

	if (m_nDelayCounter < m_nDelay)
	{
		m_nDelayCounter++;
		return;
	}
	

	switch (m_state)
	{
	case CFinishUi::STATE::DEC_SIZE:
		//サイズ減算処理
		StateDecSize();
		break;
	case CFinishUi::STATE::NONE:
		//何もしない処理
		StateNone();
		break;
	case CFinishUi::STATE::ADD_SIZE:
		//サイズ加算処理
		if (StateAddSize())
		{
			//消す
			Uninit();
			return;
		}
		break;
	default:
		break;
	}

	//更新処理
	CObject2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CFinishUi::Draw(void) {
	//描画処理
	CObject2D::Draw();
}

//=============================================================================
//サイズ減算処理
//=============================================================================
void CFinishUi::StateDecSize()
{
	//サイズ取得
	D3DXVECTOR3 size = GetSize();
	//小さくする
	size *= FINISH_UI_DEC_SIZE;
	if (size.x < FINISH_UI_DEFAULT_SIZE.x)
	{
		size.x = FINISH_UI_DEFAULT_SIZE.x;
	}
	if (size.y < FINISH_UI_DEFAULT_SIZE.y)
	{
		size.y = FINISH_UI_DEFAULT_SIZE.y;
	}
	//サイズ設定
	SetSize(size);


	//カラー取得
	D3DXCOLOR col = GetColor();
	if (col.a < m_fMaxAlpha)
	{
		//濃くする
		col.a += FINISH_UI_ADD_COLOR_ALPHA;
		if (col.a > m_fMaxAlpha)
		{
			col.a = m_fMaxAlpha;
		}
		//カラー設定
		SetColor(col);
	}


	//既定のサイズになったら
	if (size.x <= FINISH_UI_DEFAULT_SIZE.x && size.y <= FINISH_UI_DEFAULT_SIZE.y)
	{
		//何もしない状態にする
		m_state = STATE::NONE;
	}
}

//=============================================================================
//何もしない処理
//=============================================================================
void CFinishUi::StateNone()
{
	//フレームカウントを加算
	m_nFrameCounter++;
	if (m_nFrameCounter > FINISH_UI_STATE_NONE_COUNT)
	{
		//サイズ加算状態にする
		m_state = STATE::ADD_SIZE;
		//リセット
		m_nFrameCounter = 0;
	}
}

//=============================================================================
//サイズ加算処理
//=============================================================================
bool CFinishUi::StateAddSize()
{
	//サイズ取得
	D3DXVECTOR3 size = GetSize();
	//大きくする
	size *= FINISH_UI_ADD_SIZE;
	//サイズ設定
	SetSize(size);


	//カラー取得
	D3DXCOLOR col = GetColor();
	if (col.a > 0.0f)
	{
		//薄くする
		col.a -= FINISH_UI_DEC_COLOR_ALPHA;
		if (col.a < 0.0f)
		{
			col.a = 0.0f;
			//カラー設定
			SetColor(col);
			return true;
		}
		//カラー設定
		SetColor(col);
	}
	return false;
}