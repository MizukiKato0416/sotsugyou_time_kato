//=============================================================================
//
// �^�C�g���V�[������ [titleScene.cpp]
// Author : �ߊԏr��
// Author : �����ĕ�
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
#include "selectMenu2D.h"
#include "objectModel.h"
#include "PresetSetEffect.h"
#include "meshwall.h"
#include "object_player.h"

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

#define TITLE_SCENE_CLOUD_NUM					(1)											//�_�̐�
#define TITLE_SCENE_CLOUD_POS					(D3DXVECTOR3(0.0f, 0.0f, 1000.0f))			//�_�̈ʒu
#define TITLE_SCENE_CLOUD_SIZE					(2000.0f)									//�_�̃T�C�Y
#define TITLE_SCENE_CLOUD_MESH_NUM				(2)											//���b�V����~���l�߂鐔
#define TITLE_SCENE_CLOUD_MOVE_SPEED			(0.00035f)									//�e�N�X�`���𓮂�������
#define TITLE_SCENE_CLOUD_MOVE_SPEED_INTERVAL	(0.00025f)									//���̉_�̃e�N�X�`���𓮂��������̊Ԋu
#define TITLE_SCENE_CLOUD_COLOR					(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f))			//�_�̐F

#define TITLE_FOG_COLOR							(D3DXCOLOR(0.1f, 0.0f, 0.2f, 1.0f))			//�t�H�O�̐F
#define TITLE_BACK_BUFF							(D3DXCOLOR(0.1f, 0.7f, 1.0f, 1.0f))			//�o�b�N�o�b�t�@�[�̐F

#define TITLE_SCENE_END_CAMERA_ROT_X			(10.0f)		//�J�����̍ŏI�I�Ȍ���X
#define TITLE_SCENE_END_CAMERA_POS_Z			(-550.0f)	//�J�����̍ŏI�I�ȈʒuZ
#define TITLE_SCENE_END_CAMERA_POS_Y			(20.0f)		//�J�����̍ŏI�I�ȈʒuY

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
	m_pCloud.clear();
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
		pRenderer->SetEffectFogRange(200.0f, 4000.0f);
		//�o�b�N�o�b�t�@���t�H�O�̐F�ɍ��킹��
		pRenderer->SetBackBuffColor(TITLE_BACK_BUFF);
	}	

	//�_�̐���
	for (int nCntCloud = 0; nCntCloud < TITLE_SCENE_CLOUD_NUM; nCntCloud++)
	{
		m_pCloud.push_back(CMeshwall::Create(TITLE_SCENE_CLOUD_POS, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			                                 TITLE_SCENE_CLOUD_MESH_NUM, TITLE_SCENE_CLOUD_MESH_NUM, TITLE_SCENE_CLOUD_SIZE, TITLE_SCENE_CLOUD_SIZE,
			                                 CTexture::TEXTURE_TYPE::MESH_CLOUD));
		//���Z����������
		m_pCloud[nCntCloud]->SetAlphaBlend(true);
		//�`�揇�̐ݒ�
		m_pCloud[nCntCloud]->SetDrawPriority(CObject::DRAW_PRIORITY::CLEAR);
		//���C�g���I�t�ɂ���
		m_pCloud[nCntCloud]->SetLight(false);
		//�F�̐ݒ�
		m_pCloud[nCntCloud]->SetColor(TITLE_SCENE_CLOUD_COLOR);
	}

	//���̐���
	CMeshwall::Create(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(D3DX_PI*0.5f, 0.0f, 0.0f), 8, 4, 1000.0f, 500.0f,
		              CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);

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
	}


	// �Q�[���I��UI
	CObject2D::Create(ESC_POS, CTexture::TEXTURE_TYPE::QUIT_GAME, ESC_WIDTH, ESC_HEIGHT);
	// �^�C�g�����S
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::TITLE_LOGO, SCREEN_WIDTH, SCREEN_HEIGHT);
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

	//�_�̏���
	Cloud();

	//�v���C���[���f���̏���
	PlayerModel();

	//�J�����̏���
	Camera();

	if (pManager != nullptr) {
		//���݂̓��̓f�o�C�X�̎擾
		pInput = pManager->GetInputCur();
		//�t�F�[�h�̎擾
		pFade = pManager->GetFade();
		//�T�E���h�̎擾
		pSound = pManager->GetSound();
	}

	if (pInput == nullptr || pFade == nullptr) return;

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
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
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
//�_�̏���
//=============================================================================
void CTitleScene::Cloud()
{
	for (int nCntCloud = 0; nCntCloud < TITLE_SCENE_CLOUD_NUM; nCntCloud++)
	{
		if (m_pCloud[nCntCloud] == nullptr)
		{
			continue;
		}

		//�e�N�X�`�����W�ړ�����
		m_pCloud[nCntCloud]->SetMoveTex(TITLE_SCENE_CLOUD_MOVE_SPEED + TITLE_SCENE_CLOUD_MOVE_SPEED_INTERVAL * nCntCloud, 0.0f);
	}
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
	rot.x -= 0.01f;
	//����̒l�ȉ��ɂȂ�����
	if (rot.x < TITLE_SCENE_END_CAMERA_ROT_X * (D3DX_PI / 180.0f)) rot.x = TITLE_SCENE_END_CAMERA_ROT_X * (D3DX_PI / 180.0f);

	//�����ݒ�
	pCamera->SetRot(rot);
}