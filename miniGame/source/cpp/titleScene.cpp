//=============================================================================
//
// �^�C�g���V�[������ [titleScene.cpp]
// Author : �ߊԏr��
// Author : �����ĕ�
// Author : ��������
//
//=============================================================================
#include "titleScene.h"
#include "manager.h"
#include "renderer.h"
#include "titleCamera.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "object2D.h"
#include "PresetSetEffect.h"
#include "meshwall.h"
#include "skydome.h"

#include "effect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ESC_POS (D3DXVECTOR3(120.0f, 40.0f, 0.0f))
#define ESC_WIDTH (200.0f)
#define ESC_HEIGHT (40.0f)
#define NEXT_LOGO_POS (D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 550.0f, 0.0f))
#define NEXT_LOGO_WIDTH (400.0f)
#define NEXT_LOGO_HEIGHT (100.0f)

#define TITLE_SCENE_PLAYER_DIFFER			(150.0f)			//�v���C���[�Ԃ̋���
#define TITLE_SCENE_PLAYER_POS_Z			(3000.0f)			//�v���C���[�̈ʒuZ
#define TITLE_SCENE_PLAYER_MOVE				(30.0f)				//�v���C���[�̈ړ���

#define CLOUD_POS					(D3DXVECTOR3(0.0f, -5.0f, 2000.0f))			//�_�̈ʒu
#define CLOUD_RADIUS				(5000.0f)									//�_�̔��a
#define CLOUD_MESH_NUM				(12)										//���b�V����~���l�߂鐔
#define CLOUD_ROTATE_SPEED			(0.0015f)									//�_�̉�]��
#define CLOUD_COLOR					(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f))			//�_�̐F

#define TITLE_FOG_COLOR							(D3DXCOLOR(1.0f, 0.9f, 0.3f, 1.0f))			//�t�H�O�̐F
#define TITLE_BACK_BUFF							(D3DXCOLOR(0.1f, 0.7f, 1.0f, 1.0f))			//�o�b�N�o�b�t�@�[�̐F

#define TITLE_SCENE_END_CAMERA_ROT_X			(10.0f)			//�J�����̍ŏI�I�Ȍ���X
#define TITLE_SCENE_END_CAMERA_POS_Z			(-550.0f)		//�J�����̍ŏI�I�ȈʒuZ
#define TITLE_SCENE_END_CAMERA_POS_Y			(20.0f)			//�J�����̍ŏI�I�ȈʒuY
#define TITLE_SCENE_CAMERA_ROTATE_SPEED			(0.01f)			//�J�����̉�]�X�s�[�h

#define TITLE_SCENE_THE_FINAL_LOGO_SIZE_X			(654.0f)			//�U�t�@�C�i�����S�̃T�C�YX
#define TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y			(74.0f)				//�U�t�@�C�i�����S�̃T�C�YY
#define TITLE_SCENE_THE_FINAL_LOGO_INIT_SIZE_X		(654.0f * 20.0f)	//�U�t�@�C�i�����S�̏����T�C�YX
#define TITLE_SCENE_THE_FINAL_LOGO_INIT_SIZE_Y		(74.0f * 20.0f)		//�U�t�@�C�i�����S�̏����T�C�YY
#define TITLE_SCENE_THE_FINAL_LOGO_POS_Y			(365.0f)			//�U�t�@�C�i�����S�̈ʒuY
#define TITLE_SCENE_THE_FINAL_LOGO_CREATE_COUNTER	(20)				//�U�t�@�C�i�����S�̐�������^�C�~���O
#define TITLE_SCENE_THE_FINAL_LOGO_DEC_SIZE			(0.89f)				//�U�t�@�C�i�����S�̃T�C�Y���Z��

#define TITLE_SCENE_CHARA_LOGO_SIZE				(170.0f)			//�������S�̃T�C�Y
#define TITLE_SCENE_CHARA_LOGO_INIT_SIZE		(170.0f * 10.0f)	//�������S�̏����T�C�Y
#define TITLE_SCENE_CHARA_LOGO_POS_Y			(220.0f)			//�������S�̈ʒuY
#define TITLE_SCENE_CHARA_LOGO_POS_X			(15.0f)				//�������S�̈ʒuX�����l
#define TITLE_SCENE_CHARA_DEC_SIZE				(0.91f)				//�������S�̃T�C�Y���Z��
#define TITLE_SCENE_CHARA_CREATE_COUNTER		(30)				//�������S�̐�������^�C�~���O

#define TITLE_SCENE_EXPLOSION_LOGO_POS				(D3DXVECTOR3(850.0f, 174.0f, 0.0f))		//����UI�̈ʒu
#define TITLE_SCENE_EXPLOSION_LOGO_SIZE_X			(362.0f)								//����UI�̃T�C�YX
#define TITLE_SCENE_EXPLOSION_LOGO_SIZE_Y			(316.0f)								//����UI�̃T�C�YY
#define TITLE_SCENE_EXPLOSION_LOGO_SIZE_MIN			(0.9f)									//����UI�̃T�C�Y�ŏ��l
#define TITLE_SCENE_EXPLOSION_LOGO_SIZE_MAX			(1.1f)									//����UI�̃T�C�Y�ő�l
#define TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE		(0.001f)								//����UI�̃X�P�[�����Z��
#define TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE_MIN	(0.99f)									//����UI�̃X�P�[�����Z�ʍŏ��l
#define TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE_MAX	(1.01f)									//����UI�̃X�P�[�����Z�ʍő�l

#define TITLE_SCENE_CAR_LOGO_ADD_MOVE		(0.2f)				//�ԃ��S�̈ړ��ʉ��Z��
#define TITLE_SCENE_CAR_LOGO_ADD_MOVE_MAX	(30.0f)				//�ԃ��S�̈ړ��ʍő�l
#define TITLE_SCENE_CAR_LOGO_LEFT_MOVE		(22.8f)				//�ԃ��S�̍����痈��Ƃ��̈ړ��ʏ���
#define TITLE_SCENE_CAR_LOGO_STOP_COUNTER	(180)				//�ԃ��S����~���Ă��鎞��

#define TITLE_SCENE_FLOOR_POS_Z		(-1000.0f)			//���̈ʒuZ
#define TITLE_SCENE_FLOOR_NUM		(8)					//���̕�����
#define TITLE_SCENE_FLOOR_SIZE		(1000.0f)			//���̃T�C�Y
	
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CObject2D * CTitleScene::m_pNext = nullptr;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTitleScene::CTitleScene() :m_fMaxCol(1.0f), m_nDivideNum(2), m_nMaxColTime(3)
{	
	m_bPushKey = false;
	m_nFadeTime = 120;
	m_nColorTime = 0;
	memset(m_pPlayerModel, NULL, sizeof(m_pPlayerModel[MAX_OBJECT_PLAYER_NUM]));
	memset(m_pTitleLogoChara, NULL, sizeof(m_pTitleLogoChara[TITLE_LOGO_CHARA_NUM]));
	m_pTheFinalLogo = nullptr;
	m_pTitleLogo = nullptr;
	m_nFrameCounter = 0;
	m_phase = PHASE::NONE;
	m_fBoundMove = 0.0f;
	m_pExplosionLogo = nullptr;
	m_bExplosionAddSize = false;
	m_pTitleLogoCar = nullptr;
	m_bCarLogoRight = false;
	m_fCarLogoMove = 0.0f;
	m_bCreateAllLogo = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitleScene::~CTitleScene()
{

}

//=============================================================================
// �^�C�g���V�[���̏���������
//=============================================================================
void CTitleScene::Init(void) {

	//�ϐ�������
	memset(m_pTitleLogoChara, NULL, sizeof(m_pTitleLogoChara[TITLE_LOGO_CHARA_NUM]));
	m_pTheFinalLogo = nullptr;
	m_nFrameCounter = 0;
	m_phase = PHASE::CHARACTOR_LOGO;
	m_pTitleLogo = nullptr;
	m_fBoundMove = 1.02f;
	m_pExplosionLogo = nullptr;
	m_bExplosionAddSize = true;
	m_pTitleLogoCar = nullptr;
	m_bCarLogoRight = true;
	m_fCarLogoMove = 0.0f;
	m_bCreateAllLogo = false;

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�����_���[�̎擾
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//�J�����̐ݒ�
	if (pManager != nullptr) pManager->SetCamera(CTitleCamera::Create());

	//------------------------------
	//���C�g�̏����ݒ�
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ���C�g�̎ˉe�ϊ�
	//���C�g�̃v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 200.0f, 1800.0f);

	D3DXMATRIX mtxLightView;   // ���C�g�r���[�ϊ�
	D3DXVECTOR3 posLightV = D3DXVECTOR3(0.0f, 1200.0f, -1000.0f);	//���C�g�̎��_�̈ʒu
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
		pRenderer->SetEffectFogEnable(true);
		pRenderer->SetEffectFogColor(TITLE_FOG_COLOR);
		pRenderer->SetEffectFogRange(200.0f, 12000.0f);
		//�o�b�N�o�b�t�@���t�H�O�̐F�ɍ��킹��
		pRenderer->SetBackBuffColor(TITLE_BACK_BUFF);
	}	

	CEffect::Create(D3DXVECTOR3(0.0f, 1000.0f, 0.0f), CEffect::EFFECT_TYPE::SUN, 600.0f, 600.0f, true);

	////�_�̐���
	CSkyDome::Create(CLOUD_POS, CLOUD_MESH_NUM, CLOUD_MESH_NUM, CLOUD_RADIUS, CLOUD_ROTATE_SPEED);

	//���̐���
	CMeshwall::Create(D3DXVECTOR3(0.0f, 0.0f, TITLE_SCENE_FLOOR_POS_Z), D3DXVECTOR3(D3DX_PI* 0.5f, 0.0f, 0.0f),
		              TITLE_SCENE_FLOOR_NUM, TITLE_SCENE_FLOOR_NUM, TITLE_SCENE_FLOOR_SIZE, TITLE_SCENE_FLOOR_SIZE,
		              CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);

	//���u����
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_DUNE_00, D3DXVECTOR3(1000.0f, -100.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_DUNE_01, D3DXVECTOR3(-1000.0f, -100.0f, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_DUNE_02, D3DXVECTOR3(-1200.0f, -100.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//�T�{�e������
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_CACTUS_00, D3DXVECTOR3(600.0f, 0.0f, 1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_CACTUS_01, D3DXVECTOR3(400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_CACTUS_02, D3DXVECTOR3(-400.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//�؂̐���
	CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_TREE_00, D3DXVECTOR3(-300.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//��̒�
	CObjectModel* pBird = CObjectModel::Create(CModel::MODELTYPE::OBJ_TITLE_BIRD, D3DXVECTOR3(0.0f, 2000.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	if (pBird != nullptr) {
		pBird->SetRotSpeed(D3DXVECTOR3(0.0f, 0.015f, 0.0f));
		CModel* pBirdModel = pBird->GetPtrModel();
		if (pBirdModel != nullptr) {
			pBirdModel->SetPos(D3DXVECTOR3(2000.0f, 0.0f, 0.0f));
		}
	}

	//�v���C���[�̐���
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		const float fDist = TITLE_SCENE_PLAYER_DIFFER;	//�v���C���[���m�̋���
		D3DXVECTOR3 posModel = D3DXVECTOR3(fDist * (-MAX_OBJECT_PLAYER_NUM / 2.0f) + fDist / 2.0f + nIdxPlayer * fDist,
			                               0.0f,
			                               TITLE_SCENE_PLAYER_POS_Z);	//���[������ׂ�
		m_pPlayerModel[nIdxPlayer] = CObjectModel::Create(CModel::MODELTYPE::OBJ_CAR, posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		if (m_pPlayerModel == nullptr) continue;
		CModel* pModel = m_pPlayerModel[nIdxPlayer]->GetPtrModel();

		if (pModel == nullptr) continue;
		D3DXCOLOR colModel;	//���f���̃}�e���A���F
		switch (nIdxPlayer)
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
		//�X�y�L�����[�̐ݒ�
		pModel->SetMaterialSpecular(colModel / 2.0f + D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), 0);
		pModel->SetMaterialPower(2.0f, 0);
	}


	// �Q�[���I��UI
	CObject2D::Create(ESC_POS, CTexture::TEXTURE_TYPE::QUIT_GAME, ESC_WIDTH, ESC_HEIGHT);

	// ���ɍs�����郍�S
	m_pNext = CObject2D::Create(NEXT_LOGO_POS, CTexture::TEXTURE_TYPE::TEXT_GAMESTART, NEXT_LOGO_WIDTH, NEXT_LOGO_HEIGHT);

	//BGM�̍Đ�
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_TITLE);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_TITLE);
	}

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�
	CObject::SetUpdatePauseLevel(0);


#ifdef _DEBUG
	//Z�o�b�t�@�e�N�X�`���̕\��
	CObject2D* pZBuff = CObject2D::Create(D3DXVECTOR3(70.0f, 120.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, 100.0f, 100.0f);
	if (pZBuff != nullptr) {
		pZBuff->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
		pZBuff->SetUseZBuffTexture(true);
	}
#endif

}

//=============================================================================
// �^�C�g���V�[���̏I������
//=============================================================================
void CTitleScene::Uninit(void) {	

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
// �^�C�g���V�[���̍X�V����
//=============================================================================
void CTitleScene::Update(void) {		
	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	CInput* pInput = nullptr;	//���̓f�o�C�X�ւ̃|�C���^
	CFade* pFade = nullptr;		//�t�F�[�h�ւ̃|�C���^
	CSound* pSound = nullptr;	//�T�E���h�ւ̃|�C���^
	D3DXCOLOR col = m_pNext->GetColor(); // ���ɍs�����郍�S�̐F�̎擾

	//�t�F�[�Y�ɂ���ď�������
	switch (m_phase)
	{
	case CTitleScene::PHASE::CHARACTOR_LOGO:
		//�����̃��S�̏���
		CharactorLogo();
		break;
	case CTitleScene::PHASE::THE_FINAL_LOGO:
		//�U�t�@�C�i���̃��S�̏���
		TheFinalLogo();
		break;
	case CTitleScene::PHASE::BOUND_LOGO:
		//�U���S�̃o�E���h�̏���
		BoundLogo();
		break;
	case CTitleScene::PHASE::STOP_TITLE_LOGO:
		//�^�C�g�����S��~�̏���
		StopTitleLogo();
		break;
	default:
		break;
	}

	//�v���C���[���f���̏���
	PlayerModel();

	//�J�����̏���
	Camera();

	//���S��������
	DeleteLogo();

	//�S�Ẵ��S�𐶐����鏈��
	if (CreateAllLogo()) return;

	if (pManager != nullptr) {
		//���݂̓��̓f�o�C�X�̎擾
		pInput = pManager->GetInputCur();
		//�t�F�[�h�̎擾
		pFade = pManager->GetFade();
		//�T�E���h�̎擾
		pSound = pManager->GetSound();
	}

	if (pInput == nullptr || pFade == nullptr || !m_bCreateAllLogo) return;

	//����L�[���������Ƃ�
	if (pInput->GetTrigger(CInput::CODE::SELECT, 0) && !m_bPushKey) 
	{		
		//�t�F�[�h���������ꍇ
		if (pFade->GetFade()) 
		{
			//�t�F�[�h���X�L�b�v
			pFade->SkipFade();
		}		
		else
		{
			// �����ꂽ�Ƃ�
			m_bPushKey = true;

			//���艹�̍Đ�
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ENGINE);

			m_nFrameCounter = 0;
		}
	}

	//����L�[�������ꂽ�Ƃ�
	if (m_bPushKey)
	{		
		// �F�̏�Ԃ��擾
		m_bCol = ChangeColTime(m_bCol);
		// �_�ŏ���(��ԑJ��)
		if (m_bCol)
		{
			// ���l�̕ύX
			col.a = m_fMaxCol;		
		}
		else
		{
			// ���l�̕ύX
			col.a = m_fMaxCol / m_nDivideNum;			
		}		
		// ���ɍs�����郍�S�̐F�̐ݒ�
		m_pNext->SetColor(col);

		// �J�ڂ��鎞�Ԃ�0��菬�����Ȃ��Ă�����
		if (m_nFadeTime < 0)
		{
			// 0�������ă}�C�i�X�l�ɂȂ�Ȃ��悤�ɂ���
			m_nFadeTime = 0;	
			//�V�[���J�ڊJ�n			
			if (pFade != nullptr) pFade->SetFade(CScene::SCENE_TYPE::SELECT_GAME, 0.02f, 60);
		}
		else
		{
			//�J�ڂ��鎞�Ԃ�0��菬�����Ȃ��Ă�����
			m_nFadeTime--;
		}
	}
}

//=============================================================================
// �^�C�g���V�[���̐F���ς�鎞�Ԃ̏���
//=============================================================================
bool CTitleScene::ChangeColTime(bool bCol)
{
	// �F��ς��鎞�Ԃ����Z
	m_nColorTime++;

	// ���Ԃ��ő厞�Ԃɍs������
	if (m_nColorTime > m_nMaxColTime)
	{
		// bCol = true�̂Ƃ�
		if (bCol)
		{
			bCol = false;
		}
		else // ����ȊO
		{
			bCol = true;
		}
		// �F��ς��鎞�Ԃ�������
		m_nColorTime = 0;
	}

	return bCol;
}

//=============================================================================
//�v���C���[�̃��f���̏���
//=============================================================================
void CTitleScene::PlayerModel()
{
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		if (m_pPlayerModel == nullptr || !m_bPushKey) continue;

		//��������Ă����犎�X�^�[�g�{�^����������Ă�����

		//�ʒu�擾
		D3DXVECTOR3 pos = m_pPlayerModel[nIdxPlayer]->GetPos();
		//�ړ��ʂ�ݒ�
		pos.z += -TITLE_SCENE_PLAYER_MOVE;
		//�ʒu�ݒ�
		m_pPlayerModel[nIdxPlayer]->SetPos(pos);

		//---------------------------------
		//��
		CPresetEffect::SetEffect3D(0, pos, {}, {});
		//---------------------------------

		m_nFrameCounter++;

		if (m_nFrameCounter == 1)
		{
			CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
			if (pManager == nullptr) return;
			//�T�E���h�̎擾
			CSound* pSound = nullptr;
			if (pManager != nullptr) pSound = pManager->GetSound();
			//�����Đ�
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_TITLE_CAR);
		}
	}
}

//=============================================================================
//�J�����̏���
//=============================================================================
void CTitleScene::Camera()
{
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�J�����̎擾
	CCamera* pCamera = nullptr;
	if (pManager != nullptr) pCamera = pManager->GetCamera();

	//�J��������������Ă��銎����{�^����������Ă�����
	if (pCamera == nullptr || !m_bPushKey) return;

	//�����擾
	D3DXVECTOR3 rot = pCamera->GetRot();

	if (rot.x <= TITLE_SCENE_END_CAMERA_ROT_X * (D3DX_PI / 180.0f)) return;

	//�����𓮂���
	rot.x -= TITLE_SCENE_CAMERA_ROTATE_SPEED;
	//����̒l�ȉ��ɂȂ�����
	if (rot.x < TITLE_SCENE_END_CAMERA_ROT_X * (D3DX_PI / 180.0f)) rot.x = TITLE_SCENE_END_CAMERA_ROT_X * (D3DX_PI / 180.0f);

	//�����ݒ�
	pCamera->SetRot(rot);
}

//=============================================================================
//�����̃��S�̏���
//=============================================================================
void CTitleScene::CharactorLogo()
{
	//�J�E���^�[�����Z
	m_nFrameCounter++;

	if (m_nFrameCounter < TITLE_SCENE_CHARA_CREATE_COUNTER) return;

	m_nFrameCounter = TITLE_SCENE_CHARA_CREATE_COUNTER;

	for (int nCntCharaLogo = 0; nCntCharaLogo < TITLE_LOGO_CHARA_NUM; nCntCharaLogo++)
	{
		//�ŏ��ȊO
		if (nCntCharaLogo > 0)
		{
			//�T�C�Y���擾
			D3DXVECTOR3 beforeSize = m_pTitleLogoChara[nCntCharaLogo - 1]->GetSize();

			if (beforeSize.x != TITLE_SCENE_CHARA_LOGO_SIZE || beforeSize.y != TITLE_SCENE_CHARA_LOGO_SIZE) return;
		}

		//��������Ă��Ȃ�������
		if (m_pTitleLogoChara[nCntCharaLogo] == nullptr)
		{
			//��������
			m_pTitleLogoChara[nCntCharaLogo] =
				CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f -
				((TITLE_SCENE_CHARA_LOGO_SIZE - TITLE_SCENE_CHARA_LOGO_POS_X) * (TITLE_LOGO_CHARA_NUM / 2.0f)) + ((TITLE_SCENE_CHARA_LOGO_SIZE - TITLE_SCENE_CHARA_LOGO_POS_X) / 2.0f) +
					(TITLE_SCENE_CHARA_LOGO_SIZE - TITLE_SCENE_CHARA_LOGO_POS_X) * nCntCharaLogo,
					TITLE_SCENE_CHARA_LOGO_POS_Y,
					0.0f),
					static_cast<CTexture::TEXTURE_TYPE>(static_cast<int>(CTexture::TEXTURE_TYPE::TITLE_LOGO_CHARACTOR_00) + nCntCharaLogo),
					TITLE_SCENE_CHARA_LOGO_INIT_SIZE, TITLE_SCENE_CHARA_LOGO_INIT_SIZE);
		}

		//�T�C�Y���擾
		D3DXVECTOR3 size = m_pTitleLogoChara[nCntCharaLogo]->GetSize();

		if (size.x > TITLE_SCENE_CHARA_LOGO_SIZE || size.y > TITLE_SCENE_CHARA_LOGO_SIZE)
		{
			//����������
			size *= TITLE_SCENE_CHARA_DEC_SIZE;
		}

		if (size.x < TITLE_SCENE_CHARA_LOGO_SIZE) 
		{ 
			size.x = TITLE_SCENE_CHARA_LOGO_SIZE;
		}
		if (size.y < TITLE_SCENE_CHARA_LOGO_SIZE)
		{
			size.y = TITLE_SCENE_CHARA_LOGO_SIZE;

			CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
			if (pManager == nullptr) return;
			//�T�E���h�̎擾
			CSound* pSound = nullptr;
			if (pManager != nullptr) pSound = pManager->GetSound();
			//�����Đ�
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_TITLE_CHAR_CREATE);
		}
		//�T�C�Y�ݒ�
		m_pTitleLogoChara[nCntCharaLogo]->SetSize(size);
	}

	if (m_pTitleLogoChara[TITLE_LOGO_CHARA_NUM - 1] == nullptr) return;
	//��������Ă�����
	
	//�T�C�Y���擾
	D3DXVECTOR3 size = m_pTitleLogoChara[TITLE_LOGO_CHARA_NUM - 1]->GetSize();
	if (size.x != TITLE_SCENE_CHARA_LOGO_SIZE || size.y != TITLE_SCENE_CHARA_LOGO_SIZE) return;

	//���̃t�F�[�Y�ɂ���
	m_phase = PHASE::THE_FINAL_LOGO;

	//������
	m_nFrameCounter = 0;
}

//=============================================================================
//�U�t�@�C�i���̃��S�̏���
//=============================================================================
void CTitleScene::TheFinalLogo()
{
	//�J�E���^�[�����Z
	m_nFrameCounter++;

	if (m_nFrameCounter < TITLE_SCENE_THE_FINAL_LOGO_CREATE_COUNTER) return;

	m_nFrameCounter = TITLE_SCENE_THE_FINAL_LOGO_CREATE_COUNTER;

	//��������Ă��Ȃ�������
	if (m_pTheFinalLogo == nullptr)
	{
		//�������S
		m_pExplosionLogo = CObject2D::Create(TITLE_SCENE_EXPLOSION_LOGO_POS, CTexture::TEXTURE_TYPE::TITLE_LOGO_EXPLOSION,
			                                 TITLE_SCENE_EXPLOSION_LOGO_SIZE_X, TITLE_SCENE_EXPLOSION_LOGO_SIZE_Y);

		//�ԃ��S
		m_pTitleLogoCar = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::TITLE_LOGO_CAR,
			                                SCREEN_WIDTH, SCREEN_HEIGHT);

		// �^�C�g�����S
		m_pTitleLogo = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::TITLE_LOGO,
			                             SCREEN_WIDTH, SCREEN_HEIGHT);

		//�U�t�@�C�i�����S
		m_pTheFinalLogo = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TITLE_SCENE_THE_FINAL_LOGO_POS_Y, 0.0f),
			                                CTexture::TEXTURE_TYPE::TITLE_LOGO_THE_FINAL,
		                                    TITLE_SCENE_THE_FINAL_LOGO_INIT_SIZE_X, TITLE_SCENE_THE_FINAL_LOGO_INIT_SIZE_Y);

		for (int nCntCharaLogo = 0; nCntCharaLogo < TITLE_LOGO_CHARA_NUM; nCntCharaLogo++)
		{
			//��������Ă��Ȃ�������
			if (m_pTitleLogoChara[nCntCharaLogo] == nullptr) continue;
			//����
			m_pTitleLogoChara[nCntCharaLogo]->Uninit();
			m_pTitleLogoChara[nCntCharaLogo] = nullptr;
		}
	}

	//�T�C�Y���擾
	D3DXVECTOR3 size = m_pTheFinalLogo->GetSize();

	//����������
	size *= TITLE_SCENE_THE_FINAL_LOGO_DEC_SIZE;
	if (size.x < TITLE_SCENE_THE_FINAL_LOGO_SIZE_X) size.x = TITLE_SCENE_THE_FINAL_LOGO_SIZE_X;
	if (size.y < TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y) size.y = TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y;
	//�T�C�Y�ݒ�
	m_pTheFinalLogo->SetSize(size);

	if (size.x != TITLE_SCENE_THE_FINAL_LOGO_SIZE_X || size.y != TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y) return;
	//�t�F�[�Y���o�E���h�ɂ���
	m_phase = PHASE::BOUND_LOGO;
	//������
	m_nFrameCounter = 0;

	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//�����Đ�
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_TITLE_LOGO_CREATE);
}

//=============================================================================
//���S�̃o�E���h�̏���
//=============================================================================
void CTitleScene::BoundLogo()
{
	if (m_pTitleLogo != nullptr)
	{
		//�T�C�Y���擾
		D3DXVECTOR3 size = m_pTitleLogo->GetSize();
		//����������
		size *= m_fBoundMove;
		if (size.x < SCREEN_WIDTH) size.x = SCREEN_WIDTH;
		if (size.y < SCREEN_HEIGHT) size.y = SCREEN_HEIGHT;
		//�T�C�Y�ݒ�
		m_pTitleLogo->SetSize(size);
	}

	if (m_pTheFinalLogo != nullptr)
	{
		//�T�C�Y���擾
		D3DXVECTOR3 size = m_pTheFinalLogo->GetSize();
		//����������
		size *= m_fBoundMove;
		if (size.x < TITLE_SCENE_THE_FINAL_LOGO_SIZE_X) size.x = TITLE_SCENE_THE_FINAL_LOGO_SIZE_X;
		if (size.y < TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y) size.y = TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y;
		//�T�C�Y�ݒ�
		m_pTheFinalLogo->SetSize(size);
	}

	m_fBoundMove -= 0.001f;

	if (m_pTheFinalLogo->GetSize().x == TITLE_SCENE_THE_FINAL_LOGO_SIZE_X && m_pTheFinalLogo->GetSize().y == TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y &&
		m_pTitleLogo->GetSize().x == SCREEN_WIDTH && m_pTitleLogo->GetSize().y == SCREEN_HEIGHT)
	{
		//�t�F�[�Y���^�C�g�����S��~�ɂ���
		m_phase = PHASE::STOP_TITLE_LOGO;
		m_fBoundMove = 1.0f;
		//�S�Ẵ��S�𐶐�������Ԃɂ���
		m_bCreateAllLogo = true;
	}
}

//=============================================================================
//�^�C�g�����S��~
//=============================================================================
void CTitleScene::StopTitleLogo()
{
	//�������S�̏���
	ExplosionLogo();

	//�ԃ��S�̏���
	CarLogo();
}

//=============================================================================
//�������S�̏���
//=============================================================================
void CTitleScene::ExplosionLogo()
{
	if (m_pExplosionLogo == nullptr) return;

	//�T�C�Y���擾
	D3DXVECTOR3 size = m_pExplosionLogo->GetSize();

	//�T�C�Y��ς���
	size *= m_fBoundMove;

	if (size.x < TITLE_SCENE_EXPLOSION_LOGO_SIZE_X * TITLE_SCENE_EXPLOSION_LOGO_SIZE_MIN) m_bExplosionAddSize = true;
	else if (size.x > TITLE_SCENE_EXPLOSION_LOGO_SIZE_X * TITLE_SCENE_EXPLOSION_LOGO_SIZE_MAX) m_bExplosionAddSize = false;

	//�T�C�Y�ݒ�
	m_pExplosionLogo->SetSize(size);

	//�X�P�[�����Z��
	float fAddScalse = TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE;
	//����������Ƃ��͋t�ɂ���
	if (!m_bExplosionAddSize) fAddScalse *= -1.0f;
	//�X�P�[�������Z
	m_fBoundMove += fAddScalse;

	if (m_fBoundMove > TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE_MAX) m_fBoundMove = TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE_MAX;
	else if (m_fBoundMove < TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE_MIN) m_fBoundMove = TITLE_SCENE_EXPLOSION_LOGO_ADD_SCALE_MIN;
}

//=============================================================================
//�ԃ��S�̏���
//=============================================================================
void CTitleScene::CarLogo()
{
	if (m_bPushKey) return;

	if (m_pTitleLogoCar == nullptr) return;

	if (m_nFrameCounter == 0)
	{
		//�ʒu�擾
		D3DXVECTOR3 pos = m_pTitleLogoCar->GetPos();
		//���Z��
		float fAddMove = TITLE_SCENE_CAR_LOGO_ADD_MOVE;
		//�����痈��Ƃ��͌�������悤�ɂ���
		if(!m_bCarLogoRight) fAddMove *= -1.0f;

		//�ړ��ʉ��Z
		m_fCarLogoMove += fAddMove;

		//�ړ��ʍő�l�ƍŏ��l��ݒ�
		if (m_fCarLogoMove > TITLE_SCENE_CAR_LOGO_ADD_MOVE_MAX) m_fCarLogoMove = TITLE_SCENE_CAR_LOGO_ADD_MOVE_MAX;
		else if(m_fCarLogoMove < 0.0f) m_fCarLogoMove = 0.0f;

		//������
		pos.x += m_fCarLogoMove;

		if (pos.x >= SCREEN_WIDTH + SCREEN_WIDTH / 2.0f)
		{
			//�ʒu�����炷
			pos.x = -SCREEN_WIDTH + SCREEN_WIDTH / 2.0f;
			//�E�ɂ��Ȃ���Ԃɂ���
			m_bCarLogoRight = false;
			//�M���M���~�܂��悤�ȑ��x�ɂ���
			m_fCarLogoMove = TITLE_SCENE_CAR_LOGO_LEFT_MOVE;
		}

		if (!m_bCarLogoRight && pos.x > SCREEN_WIDTH / 2.0f)
		{
			pos.x = SCREEN_WIDTH / 2.0f;
			m_nFrameCounter++;
		}

		//�ʒu�ݒ�
		m_pTitleLogoCar->SetPos(pos);

		return;
	}

	m_nFrameCounter++;
	if (m_nFrameCounter < TITLE_SCENE_CAR_LOGO_STOP_COUNTER) return;

	m_nFrameCounter = 0;
	//�E�ɂ����Ԃɂ���
	m_bCarLogoRight = true;
	//0�ɂ���
	m_fCarLogoMove = 0.0f;
}

//=============================================================================
//�S�Ẵ��S�𐶐����鏈��
//=============================================================================
bool CTitleScene::CreateAllLogo()
{
	if (m_bCreateAllLogo) return false;
	//���S���S�Đ�������Ă��Ȃ��Ȃ�

	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	CInput* pInput = nullptr;	//���̓f�o�C�X�ւ̃|�C���^
	if (pManager != nullptr) {
		//���݂̓��̓f�o�C�X�̎擾
		pInput = pManager->GetInputCur();
	}
	if (pInput == nullptr) return false;

	if (!pInput->GetTrigger(CInput::CODE::SELECT, 0)) return false;

	//����L�[���������Ƃ�

	for (int nCntCharaLogo = 0; nCntCharaLogo < TITLE_LOGO_CHARA_NUM; nCntCharaLogo++)
	{
		//��������Ă��Ȃ�������
		if (m_pTitleLogoChara[nCntCharaLogo] == nullptr) continue;
		//����
		m_pTitleLogoChara[nCntCharaLogo]->Uninit();
		m_pTitleLogoChara[nCntCharaLogo] = nullptr;
	}

	//��������Ă��Ȃ�������
	if (m_pExplosionLogo == nullptr)
	{
		//�������S
		m_pExplosionLogo = CObject2D::Create(TITLE_SCENE_EXPLOSION_LOGO_POS, CTexture::TEXTURE_TYPE::TITLE_LOGO_EXPLOSION,
			                                 TITLE_SCENE_EXPLOSION_LOGO_SIZE_X, TITLE_SCENE_EXPLOSION_LOGO_SIZE_Y);
	}

	//��������Ă��Ȃ�������
	if (m_pTitleLogoCar == nullptr)
	{
		//�ԃ��S
		m_pTitleLogoCar = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::TITLE_LOGO_CAR,
			                                SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	//��������Ă��Ȃ�������
	if (m_pTitleLogo == nullptr)
	{
		// �^�C�g�����S
		m_pTitleLogo = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::TITLE_LOGO,
			                             SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	else
	{
		//�T�C�Y�ݒ�
		m_pTitleLogo->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	}

	//��������Ă��Ȃ�������
	if (m_pTheFinalLogo == nullptr)
	{
		//�U�t�@�C�i�����S
		m_pTheFinalLogo = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TITLE_SCENE_THE_FINAL_LOGO_POS_Y, 0.0f),
			                                CTexture::TEXTURE_TYPE::TITLE_LOGO_THE_FINAL,
		                                    TITLE_SCENE_THE_FINAL_LOGO_SIZE_X, TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y);
	}
	else
	{
		//�T�C�Y�ݒ�
		m_pTheFinalLogo->SetSize(D3DXVECTOR3(TITLE_SCENE_THE_FINAL_LOGO_SIZE_X, TITLE_SCENE_THE_FINAL_LOGO_SIZE_Y, 0.0f));
	}

	//�S�Ẵ��S����������Ă����Ԃɂ���
	m_bCreateAllLogo = true;

	//�t�F�[�Y���^�C�g�����S��~�ɂ���
	m_phase = PHASE::STOP_TITLE_LOGO;

	//�ϐ�������
	m_fBoundMove = 1.0f;
	m_nFrameCounter = 0;

	return true;
}

//=============================================================================
//���S��������
//=============================================================================
void CTitleScene::DeleteLogo()
{
	if (!m_bPushKey) return;

	//����{�^����������Ă�����

	//��������Ă�����
	if (m_pExplosionLogo != nullptr)
	{
		//�ʒu�擾
		D3DXVECTOR3 pos = m_pExplosionLogo->GetPos();
		//�T�C�Y�擾
		D3DXVECTOR3 size = m_pExplosionLogo->GetSize();
		//������
		pos.y -= 20.0f;
		//�ʒu�ݒ�
		m_pExplosionLogo->SetPos(pos);

		if (pos.y <= 0.0f - size.y / 2.0f)
		{
			//����
			m_pExplosionLogo->Uninit();
			m_pExplosionLogo = nullptr;
		}
	}

	//��������Ă�����
	if (m_pTitleLogoCar != nullptr)
	{
		//�ʒu�擾
		D3DXVECTOR3 pos = m_pTitleLogoCar->GetPos();
		//�T�C�Y�擾
		D3DXVECTOR3 size = m_pTitleLogoCar->GetSize();
		//������
		pos.y -= 20.0f;
		pos.x = SCREEN_WIDTH / 2.0f;
		//�ʒu�ݒ�
		m_pTitleLogoCar->SetPos(pos);

		if (pos.y <= 0.0f - size.y / 2.0f)
		{
			//����
			m_pTitleLogoCar->Uninit();
			m_pTitleLogoCar = nullptr;
		}
	}

	//��������Ă�����
	if (m_pTitleLogo != nullptr)
	{
		//�ʒu�擾
		D3DXVECTOR3 pos = m_pTitleLogo->GetPos();
		//�T�C�Y�擾
		D3DXVECTOR3 size = m_pTitleLogo->GetSize();
		//������
		pos.y -= 20.0f;
		//�ʒu�ݒ�
		m_pTitleLogo->SetPos(pos);

		if (pos.y <= 0.0f - size.y / 2.0f)
		{
			//����
			m_pTitleLogo->Uninit();
			m_pTitleLogo = nullptr;
		}
	}

	//��������Ă�����
	if (m_pTheFinalLogo != nullptr)
	{
		//�ʒu�擾
		D3DXVECTOR3 pos = m_pTheFinalLogo->GetPos();
		//�T�C�Y�擾
		D3DXVECTOR3 size = m_pTheFinalLogo->GetSize();
		//������
		pos.y -= 20.0f;
		//�ʒu�ݒ�
		m_pTheFinalLogo->SetPos(pos);

		if (pos.y <= 0.0f - size.y / 2.0f)
		{
			//����
			m_pTheFinalLogo->Uninit();
			m_pTheFinalLogo = nullptr;
		}
	}
}
