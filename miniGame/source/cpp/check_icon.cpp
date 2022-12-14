//=============================================================================
//
// チェックアイコン処理 [check_icon.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "check_icon.h"
#include "object2D.h"
#include "objectModelUI.h"
#include "object_player.h"
#include "gameScene.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CHECK_ICON_FRAME_DEFAULT_SIZE		(D3DXVECTOR3(320.0f, 320.0f, 0.0f))						//フレームのデフォルトサイズ
#define CHECK_ICON_BUTTON_DEFAULT_SIZE		(D3DXVECTOR3(250.0f * 1.1f, 250.0 * 1.1f, 0.0f))		//ボタンのデフォルトサイズ
#define CHECK_ICON_BUTTON_POS_Y				(25.0f)													//ボタンの位置Y調整値

#define CHECK_ICON_DEC_ALPHA		(0.05f)			//α値減算量

#define CHECK_ICON_MODEL_CAMERA_POS_R		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//モデル用のカメラの位置R
#define CHECK_ICON_MODEL_CAMERA_POS_V		(D3DXVECTOR3(0.0f, 250.0f, -1000.0f))		//モデル用のカメラの位置V

#define CHECK_ICON_MODEL_ROTATE_SPPED		(0.02f)		//モデルの回転速度

#define CHECK_ICON_NEXT_MODEL_CREATE_POS	(200.0f)	//次のモデルの生成位置Y

#define CHECK_ICON_SELECT_FRAME_SIZE	(120.0f)	//選択アイコンのフレームのサイズ
#define CHECK_ICON_SELECT_SIZE			(30.0f)		//選択アイコンのサイズ


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
	m_pSelectUi.clear();
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

	//プレイヤーのモデル生成
	D3DXVECTOR3 posAdd = D3DXVECTOR3(0.0f, 5000.0f, 0.0f);	//影の影響をなくすための高さ
	m_pPlayerModel = CObjectModelUI::Create(CModel::MODELTYPE::OBJ_CAR, m_posModel + posAdd, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	m_pPlayerModel->SetViewCamera(CHECK_ICON_MODEL_CAMERA_POS_V + posAdd, CHECK_ICON_MODEL_CAMERA_POS_R + posAdd);
	//マテリアルの設定
	SetMaterial(m_pPlayerModel);

	//モデルの種類の数を取得
	int nModelType = static_cast<int>(CModel::MODELTYPE::OBJ_CAR_03) - static_cast<int>(CModel::MODELTYPE::OBJ_CAR) + 1;
	for (int nCntModel = 0; nCntModel < nModelType; nCntModel++)
	{
		//サイズ
		float fSizeX = (CHECK_ICON_FRAME_DEFAULT_SIZE.x - CHECK_ICON_SELECT_FRAME_SIZE) * m_scale.x;
		//距離
		float fUiDiffer = fSizeX / (nModelType + 1);
		//位置
		D3DXVECTOR3 uiPos = m_pos;
		uiPos.x += (-(fUiDiffer * (nModelType / 2.0f)) + (fUiDiffer / 2.0f)) + (fUiDiffer * nCntModel);
		uiPos.y += 120.0f * m_scale.y;

		//選択アイコンの生成
		m_pSelectUi.push_back(CObject2D::Create(uiPos, CTexture::TEXTURE_TYPE::CHECK_ICON_SELECT_NOT,
			                  CHECK_ICON_SELECT_SIZE * m_scale.x, CHECK_ICON_SELECT_SIZE * m_scale.y));
	}

	//最初だけ選択されている状態にする
	m_pSelectUi[0]->SetTexType(CTexture::TEXTURE_TYPE::CHECK_ICON_SELECT);

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
		if (pInput->GetTrigger(CInput::CODE::SELECT, m_nPlayerNum - 1))
		{
			//チェック状態にする
			m_bCheck = true;

			//プレイヤーのモデルタイプを保存
			CPlayer::SetModelType(m_nPlayerNum - 1, m_pPlayerModel->GetModelType());

			//ボタンの生成
			m_pButton = CObject2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + CHECK_ICON_BUTTON_POS_Y, 0.0f),
				                          CTexture::TEXTURE_TYPE((int)CTexture::TEXTURE_TYPE::CHECK_ICON_OK_1 + m_nPlayerNum - 1),
										  CHECK_ICON_BUTTON_DEFAULT_SIZE.x * m_scale.x, CHECK_ICON_BUTTON_DEFAULT_SIZE.y * m_scale.y);
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

		//生成数取得
		int nNumIconUi = m_pSelectUi.size();

		for (int nCntSelectIconUi = 0; nCntSelectIconUi < nNumIconUi; nCntSelectIconUi++)
		{
			//生成チェック
			if (m_pSelectUi[nCntSelectIconUi] == nullptr) return;

			//色取得
			D3DXCOLOR selectUiCol = m_pSelectUi[nCntSelectIconUi]->GetColor();
			//薄くする
			selectUiCol.a -= CHECK_ICON_DEC_ALPHA;
			//見えなくなったら
			if (selectUiCol.a <= CHECK_ICON_DEC_ALPHA)
			{
				//消す
				m_pSelectUi[nCntSelectIconUi]->Uninit();
				m_pSelectUi[nCntSelectIconUi] = nullptr;
			}
			else
			{
				//カラー設定
				m_pSelectUi[nCntSelectIconUi]->SetColor(selectUiCol);
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
void CCheckIcon::SetMaterial(CObjectModel *pPlayerModel)
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
	//マテリアルの設定
	pModel->SetMaterialDiffuse(colModel, 0);	
	pModel->SetMaterialSpecular(colModel / 2.0f + D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.5f), 0);
	pModel->SetMaterialPower(3.0f, 0);
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

//============================================================================																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																															=
//モデル選択処理
//============================================================================
void CCheckIcon::SelectModel()
{
	//決定されていたら
	if (m_bCheck) return;

	if (m_pPlayerModel == nullptr) return;

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
	}

	//ボタンを押したら
	if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT_RIGHT), m_nPlayerNum - 1))
	{//右
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

		//選択アイコン処理
		SelectIconUi();

		//プレイヤーのモデルタイプ設定処理
		SetPlayerType();

		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		//サウンドの取得
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音を再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_CURSOR);
	}
	else if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT_LEFT), m_nPlayerNum - 1))
	{//左
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

		//選択アイコン処理
		SelectIconUi();

		//プレイヤーのモデルタイプ設定処理
		SetPlayerType();

		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		//サウンドの取得
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音を再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_CURSOR);
	}
}

//============================================================================																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																															=
//選択アイコン処理
//============================================================================
void CCheckIcon::SelectIconUi()
{
	//モデルのポインタ取得
	CModel* pModel = m_pPlayerModel->GetPtrModel();
	//現在のモデルのタイプ取得
	CModel::MODELTYPE modelType = pModel->GetModelType();

	//現在のモデルが何番目なのか求める
	int nModelType = static_cast<int>(modelType) - static_cast<int>(CModel::MODELTYPE::OBJ_CAR);

	//生成数取得
	int nNumIconUi = m_pSelectUi.size();

	for (int nCntSelectIconUi = 0; nCntSelectIconUi < nNumIconUi; nCntSelectIconUi++)
	{
		//生成チェック
		if (m_pSelectUi[nModelType] == nullptr) return;

		//一致していたら
		if (nCntSelectIconUi == nModelType)
		{
			//現在のモデル番目の選択アイコンを選択されている状態にする
			m_pSelectUi[nCntSelectIconUi]->SetTexType(CTexture::TEXTURE_TYPE::CHECK_ICON_SELECT);
		}
		else
		{
			//選択されていない状態にする
			m_pSelectUi[nCntSelectIconUi]->SetTexType(CTexture::TEXTURE_TYPE::CHECK_ICON_SELECT_NOT);
		}
	}
}

//============================================================================																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																															=
//プレイヤーのモデルタイプ設定処理
//============================================================================
void CCheckIcon::SetPlayerType()
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//シーンの取得
	CGameScene* pGameScene = nullptr;
	if (pManager != nullptr) pGameScene = pManager->GetGameScene();

	if (pGameScene == nullptr) return;

	//プレイヤーのポインタ取得
	CObjectPlayer* pPlayer = pGameScene->GetPlayer(m_nPlayerNum - 1);

	if (pPlayer == nullptr) return;

	//モデルのポインタ取得
	CModel* pPlayerModel = pPlayer->GetPtrModel();
	//モデルのポインタ取得
	CModel* pModel = m_pPlayerModel->GetPtrModel();

	//モデルのタイプ設定
	pPlayerModel->SetModelType(pModel->GetModelType());
	//マテリアル設定
	SetMaterial(pPlayer);
}
