//=============================================================================
//
// �`�F�b�N�A�C�R������ [check_icon.cpp]
// Author : ��������
//
//=============================================================================
#include "check_icon.h"
#include "object2D.h"
#include "objectModelUI.h"
#include "input.h"
#include "manager.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CHECK_ICON_FRAME_DEFAULT_SIZE		(D3DXVECTOR3(320.0f, 320.0f, 0.0f))						//�t���[���̃f�t�H���g�T�C�Y
#define CHECK_ICON_BUTTON_DEFAULT_SIZE		(D3DXVECTOR3(250.0f * 0.8f, 250.0 * 0.8f, 0.0f))		//�{�^���̃f�t�H���g�T�C�Y
#define CHECK_ICON_BUTTON_POS_Y				(25.0f)													//�{�^���̈ʒuY�����l

#define CHECK_ICON_DEC_ALPHA		(0.05f)			//���l���Z��

#define CHECK_ICON_MODEL_CAMERA_POS_R		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))			//���f���p�̃J�����̈ʒuR
#define CHECK_ICON_MODEL_CAMERA_POS_V		(D3DXVECTOR3(0.0f, 250.0f, -800.0f))		//���f���p�̃J�����̈ʒuV

#define CHECK_ICON_MODEL_ROTATE_SPPED		(0.02f)		//���f���̉�]���x

#define CHECK_ICON_NEXT_MODEL_CREATE_POS	(200.0f)	//���̃��f���̐����ʒuY


//=============================================================================
// �f�t�H���g�R���X�g���N�^
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
// �f�X�g���N�^
//=============================================================================
CCheckIcon::~CCheckIcon()
{
	
}

//=============================================================================
// ��������
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
// ����������
//=============================================================================
HRESULT CCheckIcon::Init(void) {
	
	//�ϐ�������
	m_bCheck = false;
	m_bUninit = false;
	m_nCounter = 0;
	m_nDelay = 0;

	//�t���[���̐���
	m_pFrame = CObject2D::Create(m_pos, CTexture::TEXTURE_TYPE((int)CTexture::TEXTURE_TYPE::CHECK_ICON_FRAME_1 + m_nPlayerNum - 1),
		                         CHECK_ICON_FRAME_DEFAULT_SIZE.x * m_scale.x, CHECK_ICON_FRAME_DEFAULT_SIZE.y * m_scale.y);

	//�{�^���̐���
	m_pButton = CObject2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + CHECK_ICON_BUTTON_POS_Y, 0.0f),
		                          CTexture::TEXTURE_TYPE((int)CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_1 + m_nPlayerNum - 1),
								  CHECK_ICON_BUTTON_DEFAULT_SIZE.x * m_scale.x, CHECK_ICON_BUTTON_DEFAULT_SIZE.y * m_scale.y);

	//�v���C���[�̃��f������
	m_pPlayerModel = CObjectModelUI::Create(CModel::MODELTYPE::OBJ_CAR, m_posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	m_pPlayerModel->SetViewCamera(CHECK_ICON_MODEL_CAMERA_POS_V, CHECK_ICON_MODEL_CAMERA_POS_R);
	//�}�e���A���̐ݒ�
	SetMaterial(m_pPlayerModel);

	return S_OK;
}

//=============================================================================
// �I������
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

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCheckIcon::Update(void) {
	
	//���f����]����
	RotateModel();

	//���f���I������
	SelectModel();

	//���菈��
	Decide();

	//�����Ȃ�
	if (m_bUninit)
	{
		//���l���Z����
		DecAlpha();
	}
}

//=============================================================================
//���菈��
//=============================================================================
void CCheckIcon::Decide()
{
	//�`�F�b�N�o���Ă��Ȃ�������
	if (!m_bCheck)
	{
		//�}�l�[�W���[�̎擾
		CManager* pManager = CManager::GetManager();
		CInput* pInput = nullptr;
		if (pManager != nullptr) {
			//���݂̓��̓f�o�C�X�̎擾
			pInput = pManager->GetInputCur();
		}

		//�{�^������������
		if (pInput->GetTrigger(CInput::CODE((int)CInput::CODE::CHECK_X + m_nPlayerNum - 1), m_nPlayerNum - 1))
		{
			//�`�F�b�N��Ԃɂ���
			m_bCheck = true;

			//�{�^���̃e�N�X�`���ύX
			m_pButton->SetTexType(CTexture::TEXTURE_TYPE((int)CTexture::TEXTURE_TYPE::CHECK_ICON_OK_1 + m_nPlayerNum - 1));

			//�}�l�[�W���[�̎擾
			CManager* pManager = CManager::GetManager();
			//�T�E���h�̎擾
			CSound* pSound = nullptr;
			if (pManager != nullptr) pSound = pManager->GetSound();
			//�����Đ�
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_OK);
		}
	}
}

//=============================================================================
//���l���Z����
//=============================================================================
void CCheckIcon::DecAlpha()
{
	if (m_nCounter >= m_nDelay)
	{
		m_nCounter = m_nDelay;

		if (m_pFrame != nullptr)
		{
			//�F�擾
			D3DXCOLOR flameCol = m_pFrame->GetColor();
			//��������
			flameCol.a -= CHECK_ICON_DEC_ALPHA;
			//�����Ȃ��Ȃ�����
			if (flameCol.a <= CHECK_ICON_DEC_ALPHA)
			{
				//����
				m_pFrame->Uninit();
				m_pFrame = nullptr;
			}
			else
			{
				//�J���[�ݒ�
				m_pFrame->SetColor(flameCol);
			}
		}

		if (m_pButton != nullptr)
		{
			//�F�擾
			D3DXCOLOR bttonCol = m_pButton->GetColor();
			//��������
			bttonCol.a -= CHECK_ICON_DEC_ALPHA;
			//�����Ȃ��Ȃ�����
			if (bttonCol.a <= CHECK_ICON_DEC_ALPHA)
			{
				//����
				m_pButton->Uninit();
				m_pButton = nullptr;
			}
			else
			{
				//�J���[�ݒ�
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
//�}�e���A���ݒ菈��
//=============================================================================
void CCheckIcon::SetMaterial(CObjectModelUI *pPlayerModel)
{
	//���f���̃|�C���^�擾
	CModel* pModel = pPlayerModel->GetPtrModel();
	if (pModel == nullptr) return;
	D3DXCOLOR colModel;	//���f���̃}�e���A���F
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
	pModel->SetMaterialDiffuse(colModel, 0);	//�}�e���A���̐ݒ�
}

//=============================================================================
//���f����]����
//=============================================================================
void CCheckIcon::RotateModel()
{
	if (m_pPlayerModel == nullptr) return;

	//���f������]������
	m_pPlayerModel->SetRotSpeed(D3DXVECTOR3(0.0f, CHECK_ICON_MODEL_ROTATE_SPPED, 0.0f));
}

//=============================================================================
//���f���I������
//=============================================================================
void CCheckIcon::SelectModel()
{
	if (m_pPlayerModel == nullptr) return;

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//���݂̓��̓f�o�C�X�̎擾
		pInput = pManager->GetInputCur();
	}

	//�{�^������������
	if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT_UP), m_nPlayerNum - 1))
	{//��
		//���f���̃|�C���^�擾
		CModel* pModel = m_pPlayerModel->GetPtrModel();

		//���݂̃��f���̃^�C�v�擾
		CModel::MODELTYPE modelType = pModel->GetModelType();
		//���f���̃^�C�v���Ō�Ȃ�ŏ��ɖ߂�
		if (modelType == CModel::MODELTYPE::OBJ_CAR_03) modelType = CModel::MODELTYPE::OBJ_CAR;
		else
		{
			//�^�C�v�𐔒l��
			int nType = static_cast<int>(modelType);
			//���̃��f���ɂ���
			nType++;
			modelType = static_cast<CModel::MODELTYPE>(nType);
		}
		//���f���̃^�C�v��ς���
		pModel->SetModelType(modelType);
		//�}�e���A���ݒ�
		SetMaterial(m_pPlayerModel);
	}
	else if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT_DOWN), m_nPlayerNum - 1))
	{//��
		 //���f���̃|�C���^�擾
		CModel* pModel = m_pPlayerModel->GetPtrModel();

		//���݂̃��f���̃^�C�v�擾
		CModel::MODELTYPE modelType = pModel->GetModelType();
		//���f���̃^�C�v���ŏ��Ȃ�Ō�ɂ���
		if (modelType == CModel::MODELTYPE::OBJ_CAR) modelType = CModel::MODELTYPE::OBJ_CAR_03;
		else
		{
			//�^�C�v�𐔒l��
			int nType = static_cast<int>(modelType);
			//�O�̃��f���ɂ���
			nType--;
			modelType = static_cast<CModel::MODELTYPE>(nType);
		}
		//���f���̃^�C�v��ς���
		pModel->SetModelType(modelType);
		//�}�e���A���ݒ�
		SetMaterial(m_pPlayerModel);
	}
}
