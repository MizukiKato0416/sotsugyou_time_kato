//=============================================================================
//
// �N���W�b�g�V�[������ [creditScene.cpp]
// Author : ��������
//
//=============================================================================
#include "creditScene.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
#include "object2D.h"
#include "credit_picture.h"
#include "default_camera.h"
#include "objectModel.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CREDIT_SCENE_BG_MOVE_SPEED			(0.28f)			//�w�i�̈ړ����x
#define CREDIT_SCENE_BG_SIZE_Y				(1516.0f)		//�w�i�̃T�C�YY
#define CREDIT_SCENE_BG_STAGE_MOVE_SPEED	(0.11f)			//�w�i�X�e�[�W�̈ړ���
#define CREDIT_SCENE_BG_CAR_CHANGE_COUNTER	(168)			//�w�i�Ԃ�ς���܂ł̎���
#define CREDIT_SCENE_BG_CAR_SPEED			(1.0f)			//�w�i�Ԃ̈ړ����x
#define CREDIT_SCENE_BG_CAR_SIZE			(1.3f)			//�w�i�Ԃ̃T�C�Y
#define CREDIT_SCENE_BG_TITLE_DEC_SIZE		(0.0002f)		//�w�i�^�C�g���̃T�C�Y�k���l
#define CREDIT_SCENE_BG_TITLE_SIZE			(1.05f)			//�w�i�^�C�g���̃T�C�Y
#define CREDIT_SCENE_BG_FADE_SPEED			(60)			//�w�i�̃t�F�[�h�̎���

#define CREDIT_SCENE_CREDIT_SIZE_Y		(7809.0f)		//�N���W�b�g�T�C�YY
#define CREDIT_SCENE_CREDIT_MOVE		(1.32f)			//�N���W�b�g�̈ړ����x

#define CREDIT_SCENE_FADE_SPEED		(150)			//�t�F�[�h�̑��x
#define CREDIT_SCENE_FADE_DELAY		(380)			//�t�F�[�h����܂ł̒x��

#define CREDIT_SCENE_PICTURE_CREATE_POS				(D3DXVECTOR3(350.0f, 1000.0f, 0.0f))		//�G�̐����ʒu
#define CREDIT_SCENE_PICTURE_CREATE_SCALE			(D3DXVECTOR3(0.35f, 0.35f, 0.35f))			//�G�̑傫��
#define CREDIT_SCENE_PICTURE_SPEED					(1.2f)										//�G�̈ړ����x
#define CREDIT_SCENE_PICTURE_ROT					(0.1f)										//�G�̌���
#define CREDIT_SCENE_PICTURE_CREATE_INTERVAL		(600)										//�G�̐����Ԋu
#define CREDIT_SCENE_PICTURE_INIT_CREATE_INTERVAL	(360)										//�G�̍ŏ��̐����Ԋu
#define CREDIT_SCENE_PICTURE_LAST_CREATE			(4900)										//�G�̐������~�߂�܂ł̎���

#define CREDIT_SCENE_SKIP_ICON_SIZE_X				(408.0f * 0.4f)				//�X�L�b�v�A�C�R���̃T�C�YX
#define CREDIT_SCENE_SKIP_ICON_SIZE_Y				(94.0f * 0.4f)				//�X�L�b�v�A�C�R���̃T�C�YY
#define CREDIT_SCENE_SKIP_UNINIT_COUNT				(180)						//�X�L�b�v�A�C�R����������܂ł̎���
#define CREDIT_SCENE_SKIP_DEC_ALPH					(0.07f)						//�X�L�b�v�A�C�R���̃��l�����l

#define CREDIT_SCENE_CAR_MODEL_ROTATE_SPEED			(-0.001f)							//�ԃ��f���̃J������]���x
#define CREDIT_SCENE_CAR_MODEL_FADE_SPEED			(60)								//�ԃ��f���̃t�F�[�h���x
#define CREDIT_SCENE_CAR_MODEL_CAMERA_ROT			(D3DXVECTOR3(-0.3f, 0.3f, 0.0f))	//�ԃ��f���̃J��������
#define CREDIT_SCENE_CAR_MODEL_CAMERA_DIST			(300.0f)							//�ԃ��f���̃J��������
#define CREDIT_SCENE_CAR_MODEL_COUNTER				(600)								//�ԃ��f���̏o������

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CCreditScene::CCreditScene()
{
	m_pModelCar = nullptr;
	m_pBg = nullptr;
	m_pBgStage = nullptr;
	m_pCredit = nullptr;
	m_pFade = nullptr;
	m_pSkipIcon = nullptr;
	m_bCanFade = false;
	m_bPictureRot = false;
	m_bFade = false;
	m_bFadeIn = false;
	m_bUninitSkipIcon = false;
	m_nFrameCounter = 0;
	m_nSkipIconCounter = 0;
	m_nPictureTex = 0;
	m_phase = PHASE::NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCreditScene::~CCreditScene()
{

}

//=============================================================================
// ����������
//=============================================================================
void CCreditScene::Init(void) {
	//�e�N�X�`���̃��[�h
	CTexture::Load("credit");

	//�ϐ�������
	m_pModelCar = nullptr;
	m_bCanFade = false;
	m_nFrameCounter = 0;
	m_nSkipIconCounter = 0;
	m_bPictureRot = false;
	m_phase = PHASE::MODEL_CAR;
	m_pFade = nullptr;
	m_bFade = false;
	m_bFadeIn = true;
	m_pBgStage = nullptr;
	m_pSkipIcon = nullptr;
	m_bUninitSkipIcon = false;
	m_nPictureTex = 0;


	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�����_���[�̎擾
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//�J�����̐ݒ�
	if (pManager != nullptr) pManager->SetCamera(CDefaultCamera::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CREDIT_SCENE_CAR_MODEL_CAMERA_ROT,
		                                                                CREDIT_SCENE_CAR_MODEL_CAMERA_DIST));

	//------------------------------
	//���C�g�̏����ݒ�
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ���C�g�̎ˉe�ϊ�
	//���C�g�̃v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 600.0f, 1200.0f);

	D3DXMATRIX mtxLightView;   // ���C�g�r���[�ϊ�
	D3DXVECTOR3 posLightV = D3DXVECTOR3(200.0f, 800.0f, -400.0f);	//���C�g�̎��_�̈ʒu
	D3DXVECTOR3 posLightR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���C�g�̒����_�̈ʒu
	D3DXVECTOR3 vecLight = -D3DXVECTOR3(posLightV - posLightR);		//���C�g�̃x�N�g��
	D3DXVec3Normalize(&vecLight, &vecLight);	//�x�N�g���𐳋K��
	//���C�g�̃r���[�}�g���b�N�X�𐶐�
	D3DXMatrixLookAtLH(&mtxLightView, &posLightV, &D3DXVECTOR3(posLightV + vecLight), &D3DXVECTOR3(0, 1, 0));
	//�V�F�[�_�̃��C�g��ݒ�
	if (pRenderer != nullptr) {
		pRenderer->SetEffectLightMatrixView(mtxLightView);
		pRenderer->SetEffectLightVector(D3DXVECTOR4(vecLight, 1.0f));
		pRenderer->SetEffectLightMatrixProj(mtxLightProj);
	}
	//------------------------------
	//�t�H�O�̏����ݒ�
	//------------------------------
	if (pRenderer != nullptr) {
		pRenderer->SetEffectFogEnable(false);
		//�o�b�N�o�b�t�@���t�H�O�̐F�ɍ��킹��
		pRenderer->SetBackBuffColor(D3DXCOLOR(0.1f, 0.7f, 1.0f, 1.0f));
	}
	
}

//=============================================================================
//�I�u�W�F�N�g��������
//=============================================================================
void CCreditScene::CreateObject(void)
{
	//�Ԃ̐���
	m_pModelCar = CObjectModel::Create(CModel::MODELTYPE::OBJ_CREDIT_OP_CAR, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	CModel* pModel = m_pModelCar->GetPtrModel();
	if (pModel != nullptr)
	{
		for (int i = 0; i < 14; i++)
		{
			pModel->SetMaterialSpecular(D3DXCOLOR(0.98f, 0.98f, 0.98f, 1.f), i);
			pModel->SetMaterialPower(8.0f, i);
		}
	}

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//------------------------------
	//BGM�̍Đ�
	//------------------------------
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_CREDIT);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_CREDIT);
	}
}

//=============================================================================
// �I������
//=============================================================================
void CCreditScene::Uninit(void) {
	//�V�[���̏I������
	CScene::Uninit();

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//���̒�~
	if (pSound != nullptr) {
		pSound->StopSound();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CCreditScene::Update(void) {
	//���[�h���I�����Ă��Ȃ�������
	if (!CTexture::GetLoadFinish()) return;

	//�V�[���̍X�V����
	CScene::Update();

	//�t�F�[�Y�ɂ�鏈������
	switch (m_phase)
	{
	case CCreditScene::PHASE::MODEL_CAR:
		//�ԃ��f������
		ModelCar();
		break;
	case CCreditScene::PHASE::BG_CAR_00:
		//�w�i�ԏ���
		BgCar00();
		break;
	case CCreditScene::PHASE::BG_CAR_01:
		//�w�i�ԏ���
		BgCar01();
		break;
	case CCreditScene::PHASE::BG_TITLE:
		//�w�i�^�C�g������
		BgTitle();
		break;
	case CCreditScene::PHASE::BG_00:
		//�N���W�b�g����
		Credit();
		//�G��������
		CreatePicture();
		//�w�i����
		Bg00();
		break;
	case CCreditScene::PHASE::BG_01:
		//�N���W�b�g����
		Credit();
		//�G��������
		CreatePicture();
		//�w�i�X�e�[�W����
		BgStage();
		break;
	default:
		break;
	}

	//�X�L�b�v�A�C�R������
	SkipIcon();

	//�t�F�[�h����
	Fade();

	//�J�ڏ���
	SceneFade();
}

//=============================================================================
//�ԃ��f������
//=============================================================================
void CCreditScene::ModelCar()
{
	m_nFrameCounter++;
	if (m_nFrameCounter > CREDIT_SCENE_CAR_MODEL_COUNTER)
	{
		//�t�F�[�h�����Ԃɂ���
		SetFade(CREDIT_SCENE_CAR_MODEL_FADE_SPEED, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		//�t�F�[�h�A�E�g�ɂȂ�����
		if (!m_bFadeIn)
		{
			m_nFrameCounter = 0;
		
			//�w�i
			m_pBg = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
				                      CTexture::TEXTURE_TYPE::BG_CREDIT_CAR_00,
				                      SCREEN_WIDTH * CREDIT_SCENE_BG_CAR_SIZE, SCREEN_HEIGHT * CREDIT_SCENE_BG_CAR_SIZE);
			m_pBg->SetDrawPriority(CObject::DRAW_PRIORITY::BG);
			
			//�t�F�[�Y��ς���
			m_phase = PHASE::BG_CAR_00;
			//����
			if (m_pModelCar != nullptr)
			{
				m_pModelCar->Uninit();
				m_pModelCar = nullptr;
			}
			return;
		}
	}

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�J�����̎擾
	CCamera* pCamera = nullptr;
	if (pManager != nullptr) pCamera = pManager->GetCamera();
	if (pCamera == nullptr) return;

	//�����擾
	D3DXVECTOR3 rot = pCamera->GetRot();
	//�����𓮂���
	rot.y -= CREDIT_SCENE_CAR_MODEL_ROTATE_SPEED;
	//�����ݒ�
	pCamera->SetRot(rot);
}

//=============================================================================
//�w�i�ԏ���
//=============================================================================
void CCreditScene::BgCar00()
{
	if (m_pBg == nullptr) return;

	m_nFrameCounter++;
	if (m_nFrameCounter > CREDIT_SCENE_BG_CAR_CHANGE_COUNTER)
	{
		m_nFrameCounter = 0;

		//�e�N�X�`����ς���
		m_pBg->SetTexType(CTexture::TEXTURE_TYPE::BG_CREDIT_CAR_01);
		//�ʒu�ς���
		m_pBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
		//�t�F�[�Y��ς���
		m_phase = PHASE::BG_CAR_01;
		return;
	}

	//�ʒu�擾
	D3DXVECTOR3 pos = m_pBg->GetPos();
	//�ړ�������
	pos.x += CREDIT_SCENE_BG_CAR_SPEED;
	//�ʒu���f
	m_pBg->SetPos(pos);
}

//=============================================================================
//�w�i�ԏ���
//=============================================================================
void CCreditScene::BgCar01()
{
	if (m_pBg == nullptr) return;

	m_nFrameCounter++;
	if (m_nFrameCounter > CREDIT_SCENE_BG_CAR_CHANGE_COUNTER)
	{
		m_nFrameCounter = 0;

		//�e�N�X�`����ς���
		m_pBg->SetTexType(CTexture::TEXTURE_TYPE::BG_CREDIT_TITLE);
		//�ʒu�ς���
		m_pBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
		//�T�C�Y��ς���
		m_pBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH * CREDIT_SCENE_BG_TITLE_SIZE, SCREEN_HEIGHT * CREDIT_SCENE_BG_TITLE_SIZE, 0.0f));

		//�t�F�[�Y��ς���
		m_phase = PHASE::BG_TITLE;
		return;
	}

	//�ʒu�擾
	D3DXVECTOR3 pos = m_pBg->GetPos();
	//�ړ�������
	pos.x -= CREDIT_SCENE_BG_CAR_SPEED;
	//�ʒu���f
	m_pBg->SetPos(pos);
}

//=============================================================================
//�w�i�^�C�g������
//=============================================================================
void CCreditScene::BgTitle()
{
	if (m_pBg == nullptr) return;

	m_nFrameCounter++;
	if (m_nFrameCounter > CREDIT_SCENE_BG_CAR_CHANGE_COUNTER)
	{
		//�t�F�[�h�����Ԃɂ���
		SetFade(CREDIT_SCENE_BG_FADE_SPEED, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		//�t�F�[�h�A�E�g�ɂȂ�����
		if (!m_bFadeIn)
		{
			m_nFrameCounter = CREDIT_SCENE_PICTURE_INIT_CREATE_INTERVAL;
			//����
			m_pBg->Uninit();
			m_pBg = nullptr;

			//�w�i
			m_pBg = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT + (SCREEN_HEIGHT - (CREDIT_SCENE_BG_SIZE_Y / 2.0f)), 0.0f),
				                      CTexture::TEXTURE_TYPE::BG_CREDIT_01, SCREEN_WIDTH, CREDIT_SCENE_BG_SIZE_Y);
			m_pBg->SetDrawPriority(CObject::DRAW_PRIORITY::BG);

			//�N���W�b�g����
			m_pCredit = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, CREDIT_SCENE_CREDIT_SIZE_Y / 2.0f + SCREEN_HEIGHT, 0.0f),
				                          CTexture::TEXTURE_TYPE::CREDIT_CREDIT, SCREEN_WIDTH, CREDIT_SCENE_CREDIT_SIZE_Y);
			m_pCredit->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);

			//�t�F�[�Y��ς���
			m_phase = PHASE::BG_00;
			return;
		}
	}

	//�T�C�Y�擾
	D3DXVECTOR3 size = m_pBg->GetSize();
	//����������
	size.x -= SCREEN_WIDTH * CREDIT_SCENE_BG_TITLE_DEC_SIZE;
	size.y -= SCREEN_HEIGHT * CREDIT_SCENE_BG_TITLE_DEC_SIZE;
	//�ʒu���f
	m_pBg->SetSize(size);
}

//=============================================================================
//�w�i����
//=============================================================================
void CCreditScene::Bg00()
{
	if (m_pBg == nullptr) return;
	//�ʒu�擾
	D3DXVECTOR3 pos = m_pBg->GetPos();

	//�ړ�������
	pos.y -= CREDIT_SCENE_BG_MOVE_SPEED;
	//�~�߂�
	if (pos.y < 0.0f - ((CREDIT_SCENE_BG_SIZE_Y / 2.0f) - SCREEN_HEIGHT) + 5.0f)
	{
		//�t�F�[�h�����Ԃɂ���
		SetFade(CREDIT_SCENE_BG_FADE_SPEED, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		//�t�F�[�h�A�E�g�ɂȂ�����
		if (!m_bFadeIn)
		{
			//�w�i��ύX
			m_pBg->SetTexType(CTexture::TEXTURE_TYPE::BG_CREDIT_02);
			//�T�C�Y�ƈʒu�ύX
			m_pBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
			m_pBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
			//�t�F�[�Y��ς���
			m_phase = PHASE::BG_01;

			//�w�i�X�e�[�W�𐶐�
			m_pBgStage = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                                   CTexture::TEXTURE_TYPE::BG_CREDIT_03, SCREEN_WIDTH, SCREEN_HEIGHT);
			return;
		}
	}
	//�ʒu���f
	m_pBg->SetPos(pos);
}

//=============================================================================
//�w�i�X�e�[�W����
//=============================================================================
void CCreditScene::BgStage()
{
	if (m_pBgStage == nullptr) return;
	//�ʒu�擾
	D3DXVECTOR3 pos = m_pBgStage->GetPos();
	//�ړ�������
	pos.y += CREDIT_SCENE_BG_STAGE_MOVE_SPEED;
	//�ʒu���f
	m_pBgStage->SetPos(pos);
}

//=============================================================================
//�J�ڏ���
//=============================================================================
void CCreditScene::SceneFade()
{
	if (!m_bCanFade) return;

	//�J�ڂł����ԂȂ�

	m_nFrameCounter++;
	if (m_nFrameCounter <= CREDIT_SCENE_FADE_DELAY) return;

	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;

	//�t�F�[�h�̎擾
	CFade* pFade = pManager->GetFade();		//�t�F�[�h�ւ̃|�C���^
	if (pFade == nullptr) return;

	if (pFade->GetChangeFade()) return;
	//�^�C�g���ɑJ��
	if (pFade != nullptr) pFade->SetFade(CScene::SCENE_TYPE::SELECT_GAME, CREDIT_SCENE_FADE_SPEED, 30, 0);
}

//=============================================================================
//�t�F�[�h����
//=============================================================================
void CCreditScene::Fade()
{
	if (!m_bFade) return;

	//�t�F�[�h�̐���
	if (m_pFade == nullptr)
	{
		m_pFade = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE,
			                        SCREEN_WIDTH, SCREEN_HEIGHT);
		m_pFade->SetColor(m_fadeCol);
		m_pFade->SetDrawPriority(CObject::DRAW_PRIORITY::UI);
	}

	//�J���[�擾
	D3DXCOLOR fadeCol = m_pFade->GetColor();

	//�t�F�[�h����ʂ�ݒ�
	float AddCol = 1.0f / m_nFadeTime;


	if (m_bFadeIn)
	{
		//���l��Z������
		fadeCol.a += AddCol;
		if (fadeCol.a >= 1.0f)
		{
			fadeCol.a = 1.0f;
			//�t�F�[�h�A�E�g�ɂ���
			m_bFadeIn = false;
		}
	}
	else
	{
		//���l�𔖂�����
		fadeCol.a -= AddCol;
		if (fadeCol.a <= 0.0f)
		{
			fadeCol.a = 0.0f;
			//�t�F�[�h�C���ɂ���
			m_bFadeIn = true;
			//�t�F�[�h���I������
			m_bFade = false;
			//����
			m_pFade->Uninit();
			m_pFade = nullptr;
			return;
		}
	}
	//�J���[�ݒ�
	m_pFade->SetColor(fadeCol);
}

//=============================================================================
//�X�L�b�v�A�C�R������
//=============================================================================
void CCreditScene::SkipIcon()
{
	//�t�F�[�h�ł����ԂȂ�
	if (m_bCanFade) return;

	//������Ԃ�������
	if (m_bUninitSkipIcon)
	{
		if (m_pSkipIcon == nullptr) return;

		//�J���[�擾
		D3DXCOLOR col = m_pSkipIcon->GetColor();
		//��������
		col.a -= CREDIT_SCENE_SKIP_DEC_ALPH;
		//�����Ȃ��Ȃ�����
		if (col.a <= 0.0f)
		{
			//����
			m_pSkipIcon->Uninit();
			m_pSkipIcon = nullptr;

			//�����Ȃ���Ԃɂ���
			m_bUninitSkipIcon = false;
			return;
		}
		//�J���[�ݒ�
		m_pSkipIcon->SetColor(col);
	}
	else
	{//������Ԃ���Ȃ�������
		CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
		if (pManager == nullptr) return;
		//���݂̓��̓f�o�C�X�̎擾
		CInput* pInput = pManager->GetInputCur();
		if (pInput == nullptr) return;

		if (pInput->GetTrigger(CInput::CODE::SELECT, 0)) {
			
			//�X�L�b�v�A�C�R������������Ă��Ȃ�������
			if (m_pSkipIcon == nullptr)
			{
				//�X�L�b�v�A�C�R���̐���
				m_pSkipIcon = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - CREDIT_SCENE_SKIP_ICON_SIZE_X / 2.0f,
					                                        SCREEN_HEIGHT - CREDIT_SCENE_SKIP_ICON_SIZE_Y / 2.0f, 0.0f),
					                            CTexture::TEXTURE_TYPE::CREDIT_SKIP_ICON, CREDIT_SCENE_SKIP_ICON_SIZE_X, CREDIT_SCENE_SKIP_ICON_SIZE_Y);
				m_pSkipIcon->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
			}
			else
			{
				//�t�F�[�h�̎擾
				CFade* pFade = pManager->GetFade();		//�t�F�[�h�ւ̃|�C���^
				if (pFade == nullptr) return;

				if (pFade->GetChangeFade()) return;
				//�^�C�g���ɑJ��
				if (pFade != nullptr) pFade->SetFade(CScene::SCENE_TYPE::SELECT_GAME, CREDIT_SCENE_FADE_SPEED, 30, 0);
				return;
			}
		}

		//�X�L�b�v�A�C�R������������Ă��Ȃ�������
		if (m_pSkipIcon == nullptr) return;

		m_nSkipIconCounter++;
		if (m_nSkipIconCounter > CREDIT_SCENE_SKIP_UNINIT_COUNT)
		{
			m_nSkipIconCounter = 0;
			//������Ԃɂ���
			m_bUninitSkipIcon = true;
			return;
		}
	}
}

//=============================================================================
//�N���W�b�g����
//=============================================================================
void CCreditScene::Credit()
{
	if (m_pCredit == nullptr) return;

	//�ʒu�擾
	D3DXVECTOR3 pos = m_pCredit->GetPos();

	if (pos.y == -CREDIT_SCENE_CREDIT_SIZE_Y / 2.0f + SCREEN_HEIGHT) return;

	//�ړ�������
	pos.y -= CREDIT_SCENE_CREDIT_MOVE;
	if (pos.y <= -CREDIT_SCENE_CREDIT_SIZE_Y / 2.0f + SCREEN_HEIGHT)
	{
		pos.y = -CREDIT_SCENE_CREDIT_SIZE_Y / 2.0f + SCREEN_HEIGHT;
		//�t�F�[�h�ł����Ԃɂ���
		m_bCanFade = true;
		//���Z�b�g
		m_nFrameCounter = 0;
	}

	//�ʒu���f
	m_pCredit->SetPos(pos);
}

//=============================================================================
//�G��������
//=============================================================================
void CCreditScene::CreatePicture()
{
	m_nFrameCounter++;

	if (m_nFrameCounter % CREDIT_SCENE_PICTURE_CREATE_INTERVAL == 0 && m_nFrameCounter < CREDIT_SCENE_PICTURE_LAST_CREATE)
	{
		//�����̐ݒ�
		float fRot = CREDIT_SCENE_PICTURE_ROT;
		//�������t�ɂ���
		if (m_bPictureRot) fRot *= -1.0f;

		//�G�̐���
		CCreditPicture::Create(CREDIT_SCENE_PICTURE_CREATE_POS, CREDIT_SCENE_PICTURE_CREATE_SCALE, fRot,
			                   static_cast<CTexture::TEXTURE_TYPE>(static_cast<int>(CTexture::TEXTURE_TYPE::CREDIT_PICTURE_00) + m_nPictureTex),
			                   -CREDIT_SCENE_PICTURE_SPEED);
		//�e�N�X�`�������ɕς���
		m_nPictureTex++;

		//�����̐؂�ւ�
		if (m_bPictureRot) m_bPictureRot = false;
		else m_bPictureRot = true;
	}
}

//=============================================================================
//�t�F�[�h�ݒ菈��
//=============================================================================
void CCreditScene::SetFade(const int nCnt, const D3DXCOLOR col)
{
	if (m_bFade) return;

	//�ݒ�
	m_nFadeTime = nCnt;
	m_fadeCol = col;

	//�t�F�[�h����悤�ɂ���
	m_bFade = true;
}
