//=============================================================================
//
// チェックアイコン処理 [check_icon.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "check_icon.h"
#include "object2D.h"
#include "objectModelUI.h"
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

#define CHECK_ICON_MODEL_CAMERA_POS_R		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))			//モデル用のカメラの位置R
#define CHECK_ICON_MODEL_CAMERA_POS_V		(D3DXVECTOR3(0.0f, 250.0f, -800.0f))		//モデル用のカメラの位置V

#define CHECK_ICON_MODEL_ROTATE_SPPED		(0.02f)		//モデルの回転速度

#define CHECK_ICON_NEXT_MODEL_CREATE_POS	(200.0f)	//次のモデルの生成位置Y


//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCheckIcon::CCheckIcon()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pFrame = nullptr;
	m_pButton = nullptr;
	m_pPlayerModel = nullptr;
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
CCheckIcon* CCheckIcon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 posModel, const D3DXVECTOR3 scale, const int nNumPlayer) {
	CCheckIcon* pCheckIcon;
	pCheckIcon = new CCheckIcon();
	if (pCheckIcon == nullptr) return nullptr;

	pCheckIcon->m_pos = pos;
	pCheckIcon->m_posModel = posModel;
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

	//プレイヤーのモデル生成
	m_pPlayerModel = CObjectModelUI::Create(CModel::MODELTYPE::OBJ_CAR, m_posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	m_pPlayerModel->SetViewCamera(CHECK_ICON_MODEL_CAMERA_POS_V, CHECK_ICON_MODEL_CAMERA_POS_R);
	//マテリアルの設定
	SetMaterial(m_pPlayerModel);

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

	if (m_pPlayerModel != nullptr)
	{
		m_pPlayerModel->Uninit();
		m_pPlayerModel = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCheckIcon::Update(void) {
	
	//モデル回転処理
	RotateModel();

	//モデル選択処理
	SelectModel();

	//決定処理
	Decide();

	//消すなら
	if (m_bUninit)
	{
		//α値減算処理
		DecAlpha();
	}
}

//=============================================================================
//決定処理
//=============================================================================
void CCheckIcon::Decide()
{
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

//=============================================================================
//マテリアル設定処理
//=============================================================================
void CCheckIcon::SetMaterial(CObjectModelUI *pPlayerModel)
{
	//モデルのポインタ取得
	CModel* pModel = pPlayerModel->GetPtrModel();
	if (pModel == nullptr) return;
	D3DXCOLOR colModel;	//モデルのマテリアル色
	switch (m_nPlayerNum - 1)
	{
	case 0:
		colModel = OBJECT_PLAYER_COLOR_1P;
		break;
	case 1:
		colModel = OBJECT_PLAYER_COLOR_2P;
		break;
	case 2:
		colModel = OBJECT_PLAYER_COLOR_3P;
		break;
	case 3:
		colModel = OBJECT_PLAYER_COLOR_4P;
		break;
	default:
		colModel = OBJECT_PLAYER_COLOR_1P;
		break;
	}
	pModel->SetMaterialDiffuse(colModel, 0);	//マテリアルの設定
}

//=============================================================================
//モデル回転処理
//=============================================================================
void CCheckIcon::RotateModel()
{
	if (m_pPlayerModel == nullptr) return;

	//モデルを回転させる
	m_pPlayerModel->SetRotSpeed(D3DXVECTOR3(0.0f, CHECK_ICON_MODEL_ROTATE_SPPED, 0.0f));
}

//=============================================================================
//モデル選択処理
//=============================================================================
void CCheckIcon::SelectModel()
{
	if (m_pPlayerModel == nullptr) return;

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
	}

	//ボタンを押したら
	if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT_UP), m_nPlayerNum - 1))
	{//上
		//モデルのポインタ取得
		CModel* pModel = m_pPlayerModel->GetPtrModel();

		//現在のモデルのタイプ取得
		CModel::MODELTYPE modelType = pModel->GetModelType();
		//モデルのタイプが最後なら最初に戻す
		if (modelType == CModel::MODELTYPE::OBJ_CAR_03) modelType = CModel::MODELTYPE::OBJ_CAR;
		else
		{
			//タイプを数値に
			int nType = static_cast<int>(modelType);
			//次のモデルにする
			nType++;
			modelType = static_cast<CModel::MODELTYPE>(nType);
		}
		//モデルのタイプを変える
		pModel->SetModelType(modelType);
		//マテリアル設定
		SetMaterial(m_pPlayerModel);
	}
	else if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT_DOWN), m_nPlayerNum - 1))
	{//下
		 //モデルのポインタ取得
		CModel* pModel = m_pPlayerModel->GetPtrModel();

		//現在のモデルのタイプ取得
		CModel::MODELTYPE modelType = pModel->GetModelType();
		//モデルのタイプが最初なら最後にする
		if (modelType == CModel::MODELTYPE::OBJ_CAR) modelType = CModel::MODELTYPE::OBJ_CAR_03;
		else
		{
			//タイプを数値に
			int nType = static_cast<int>(modelType);
			//前のモデルにする
			nType--;
			modelType = static_cast<CModel::MODELTYPE>(nType);
		}
		//モデルのタイプを変える
		pModel->SetModelType(modelType);
		//マテリアル設定
		SetMaterial(m_pPlayerModel);
	}
}
