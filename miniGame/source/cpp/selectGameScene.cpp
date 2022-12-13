//=============================================================================
//
// �Q�[���I���V�[������ [selectGameScene.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "selectGameScene.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "object2D.h"
#include "selectMenu3D.h"
#include "gameScene.h"
#include "default_camera.h"
#include "coverDisplay.h"
#include "next_button.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_GAME_NUM ((int)CScene::SCENE_TYPE::GAME_MAX - (int)CScene::SCENE_TYPE::GAME_01)	//�Q�[���̍ő吔
#define MENU_SELECT_NUM (MAX_GAME_NUM + 1)	//�����_�����ǉ�

#define MENU_BG_MOVE_SPEED		(D3DXVECTOR2(0.001f, 0.001f))		//�w�i�̈ړ����x

#define MENU_NEXT_BUTTON_POS			(D3DXVECTOR3(1240.0f, 680.0f, 0.0f))	//���ɐi�ރ{�^���̈ʒu
#define MENU_NEXT_BUTTON_SIZE			(D3DXVECTOR3(70.0f, 70.0f, 0.0f))		//���ɐi�ރ{�^���̃T�C�Y
#define MENU_NEXT_BUTTON_COUNTER		(15)									//���ɐi�ރ{�^���̌�����悤�ɂȂ�܂ł̃J�E���^�[
#define MENU_NEXT_BUTTON_DEC_ALPHA		(0.015f)								//���ɐi�ރ{�^���̃��l���Z��

#define MENU_DECIDE_UI_SIZE_X			(514.0f * 0.4f)		//����UI�̃T�C�YX
#define MENU_DECIDE_UI_SIZE_Y			(216.0f * 0.4f)		//����UI�̃T�C�YY
#define MENU_DECIDE_UI_POS				(20.0f)				//����UI�̈ʒu�����l

#define MENU_ALOW_UI_SIZE				(320.0f * 0.28f)	//���UI�̃T�C�Y
#define MENU_ALOW_UI_INIT_POS_X			(270.0f)			//���UI�̈ʒu�����lX
#define MENU_ALOW_UI_INIT_POS_Y			(630.0f)			//���UI�̈ʒuY
#define MENU_ALOW_UI_POS_MIN			(267.0f)			//���UI�̈ʒu�ŏ��l
#define MENU_ALOW_UI_POS_MAX			(273.0f)			//���UI�̈ʒu�ő�l
#define MENU_ALOW_UI_MOVE_MAX			(0.5f)				//���UI�̈ړ��ʍő�l
#define MENU_ALOW_UI_MOVE				(0.05f)				//���UI�̈ړ���

#define MENU_GAME_TITLE_UI_SIZE_X		(1697.0f * 0.2f)	//�Q�[���^�C�g��UI�̃T�C�YX
#define MENU_GAME_TITLE_UI_SIZE_Y		(631.0f * 0.2f)		//�Q�[���^�C�g��UI�̃T�C�YY

#define MENU_GAME_MODE_UI_SIZE_X		(480.0f * 0.7f)		//���[�hUI�̃T�C�YX
#define MENU_GAME_MODE_UI_SIZE_Y		(220.0f * 0.7f)		//���[�hUI�̃T�C�YY

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CSelectGameScene::CSelectGameScene()
{
	m_pMenuBG = nullptr;
	m_pMenuGame = nullptr;
	m_nFadeTime = 0;
	m_bWolfMode = false;
	m_pTutorial = nullptr;
	m_pModeUi = nullptr;
	m_pMenuNoneMoveUi = nullptr;
	memset(m_pAlowUi, NULL, sizeof(m_pAlowUi[SELECT_GAME_SCENE_ALOW_UI_NUM]));
	memset(m_fAlowUiMove, 0, sizeof(m_fAlowUiMove[SELECT_GAME_SCENE_ALOW_UI_NUM]));
	memset(m_bAlowUiMoveChange, false, sizeof(m_bAlowUiMoveChange[SELECT_GAME_SCENE_ALOW_UI_NUM]));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSelectGameScene::~CSelectGameScene()
{

}

//=============================================================================
// �Q�[���I���V�[���̏���������
//=============================================================================
void CSelectGameScene::Init(void) {
	//�e�N�X�`���̃��[�h
	CTexture::Load("select");

	//�ϐ�������
	memset(m_fAlowUiMove, 0, sizeof(m_fAlowUiMove[SELECT_GAME_SCENE_ALOW_UI_NUM]));
	m_bAlowUiMoveChange[0] = false;
	m_bAlowUiMoveChange[1] = true;
	m_nFadeTime = 30;

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�����_���[�̎擾
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//�J�����̐ݒ�
	if (pManager != nullptr) pManager->SetCamera(CDefaultCamera::Create());	//���Ńf�t�H���g�J����

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
		pRenderer->SetEffectFogEnable(false);
	}

	//BGM�̍Đ�
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_MENU);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_MENU);
	}

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
//�I�u�W�F�N�g��������
//=============================================================================
void CSelectGameScene::CreateObject(void)
{
	//------------------------------
	//UI�̐���
	//------------------------------
	// �w�i
	m_pMenuBG = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::BG_MENU, SCREEN_WIDTH, SCREEN_HEIGHT);

	//�X�e�[�W�̐���
	CObjectModelUI *pModel = CObjectModelUI::Create(CModel::MODELTYPE::OBJ_MENU_STAGE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	if (pModel != nullptr)
	{
		pModel->SetViewCamera(D3DXVECTOR3(0.0f, 200.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//�w�i
	m_pMenuNoneMoveUi = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::MENU_NONE_MOVE_UI,
		                                  SCREEN_WIDTH, SCREEN_HEIGHT);

	//�I�����j���[�̐���
	m_pMenuGame = CSelectMenu3D::Create(MENU_SELECT_NUM, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 250.0f, CModel::MODELTYPE::OBJ_BALLOON_PINK, 800.0f, 200.0f, false, true);

	if (m_pMenuGame != nullptr) {
		//�Q�[�����Ƃ̃��f���̔z��
		const CModel::MODELTYPE typeModelGame[MENU_SELECT_NUM] =
		{
			CModel::MODELTYPE::OBJ_BALLOON_PINK,
			CModel::MODELTYPE::OBJ_CAR,
			CModel::MODELTYPE::OBJ_BOM,
			CModel::MODELTYPE::OBJ_HATENA,
		};

		//�S���f���̐ݒ�
		for (int nIdxModel = 0; nIdxModel < MENU_SELECT_NUM; nIdxModel++)
		{
			//���j���[��UI�I�u�W�F�N�g�̎擾
			CObjectModelUI* pObjModelUI = m_pMenuGame->GetModelUI(nIdxModel);
			if (pObjModelUI == nullptr) continue;

			//�X�e���V���L��
			//pObjModelUI->SetEnableStencil(true);

			//��]���x�̐ݒ�
			pObjModelUI->SetRotSpeed(D3DXVECTOR3(0.0f, 0.02f, 0.0f));

			//UI�I�u�W�F�N�g�̃��f���̎擾
			CModel* pModel = pObjModelUI->GetPtrModel();
			if (pModel == nullptr) continue;

			//���f����ݒ�
			pModel->SetModelType(typeModelGame[nIdxModel]);

			const D3DXCOLOR colSpecular = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);	//�X�y�L�����[�̐F
																				//�}�e���A���̐ݒ�
			for (int nCnt = 0; nCnt < MAX_MATERIAL; nCnt++)
			{
				pModel->SetMaterialSpecular(colSpecular, nCnt);
				pModel->SetMaterialPower(6.0f, nCnt);
			}
		}
	}

	//�Q�[�����̐���
	m_pGameName = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, MENU_ALOW_UI_INIT_POS_Y, 0.0f), CTexture::TEXTURE_TYPE::TEXT_TITLENAME_BALLOON,
		MENU_GAME_TITLE_UI_SIZE_X, MENU_GAME_TITLE_UI_SIZE_Y);
	//���UI�̐���
	m_pAlowUi[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - MENU_ALOW_UI_INIT_POS_X, MENU_ALOW_UI_INIT_POS_Y, 0.0f),
		CTexture::TEXTURE_TYPE::ARROW_LEFT, MENU_ALOW_UI_SIZE, MENU_ALOW_UI_SIZE);
	m_pAlowUi[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + MENU_ALOW_UI_INIT_POS_X, MENU_ALOW_UI_INIT_POS_Y, 0.0f),
		CTexture::TEXTURE_TYPE::ARROW_RIGHT, MENU_ALOW_UI_SIZE, MENU_ALOW_UI_SIZE);

	//���[�hUI�̐���
	m_pModeUi = CObject2D::Create(D3DXVECTOR3(MENU_GAME_MODE_UI_SIZE_X / 2.0f, MENU_GAME_MODE_UI_SIZE_Y / 2.0f, 0.0f),
		CTexture::TEXTURE_TYPE::MENU_MODE_NORMAL, MENU_GAME_MODE_UI_SIZE_X, MENU_GAME_MODE_UI_SIZE_Y);
}

//=============================================================================
// �Q�[���I���V�[���̏I������
//=============================================================================
void CSelectGameScene::Uninit(void) {
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
// �Q�[���I���V�[���̍X�V����
//=============================================================================
void CSelectGameScene::Update(void) {
	//���[�h���I�����Ă��Ȃ�������
	if (!CTexture::GetLoadFinish()) return;

	//�V�[���̍X�V����
	CScene::Update();

	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	CFade* pFade = nullptr;		//�t�F�[�h�ւ̃|�C���^
	CSound* pSound = nullptr;	//�T�E���h�ւ̃|�C���^

	if (pManager != nullptr) {
		//�t�F�[�h�̎擾
		pFade = pManager->GetFade();
		//�T�E���h�̎擾
		pSound = pManager->GetSound();
	}

	if (pFade == nullptr || m_pMenuGame == nullptr) return;

	//���͏���
	UpdateInput();

	//����L�[�������ꂽ�Ƃ�
	if (m_bSelectGame)
	{
		//�����_���I�𒆂̏���
		if (m_pMenuGame->GetRoulette()) {
			//�I����
			if (m_pMenuGame->GetCountRoulette() == 0 && m_pMenuGame->GetCountRotate() == 0) {
				//�I���̃��b�N
				m_pMenuGame->SetLockChangeSelect(true);
				//���[���b�g��Ԃ̏I��
				m_pMenuGame->SetRoulette(false);	
				//���艹�̍Đ�
				if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
				//�Q�[���^�C�g���̐ؑ�
				ChangeGameTitle();
			}
		}
		// �J�ڂ��鎞�Ԃ�0��菬�����Ȃ��Ă�����
		else if (m_nFadeTime < 0)
		{
			// 0�������ă}�C�i�X�l�ɂȂ�Ȃ��悤�ɂ���
			m_nFadeTime = 0;

			//�J�ڂ̎��Ԑݒ�
			float fDecAlpha = 0.04f;
			int nStopCount = 30;
			if (m_nextScene == SCENE_TYPE::TITLE)
			{
				fDecAlpha = 0.1f;
				nStopCount = 10;
			}

			//�V�[���J�ڊJ�n			
			if (pFade != nullptr) pFade->SetFade(m_nextScene, fDecAlpha, nStopCount);
			//�I���̃��b�N
			m_pMenuGame->SetLockChangeSelect(true);
		}
		else
		{
			//�t�F�[�h�J�n�J�E���g����
			m_nFadeTime--;
		}
	}
	else {
		//�Q�[���^�C�g���̐ؑ�
		ChangeGameTitle();
	}

	//�w�i�̓����̏���
	BgMove();

	//���UI�̏���
	AlowUi();
}

//=============================================================================
// ���͏���
//=============================================================================
void CSelectGameScene::UpdateInput(void) {
	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	CInput* pInput = pManager->GetInputCur();	//���̓f�o�C�X�ւ̃|�C���^
	CFade* pFade = pManager->GetFade();		//�t�F�[�h�ւ̃|�C���^
	CSound* pSound = pManager->GetSound();	//�T�E���h�ւ̃|�C���^
	if (pInput == nullptr || pFade == nullptr || m_pMenuGame == nullptr || m_bSelectGame) return;

	//�`���[�g���A���؂�ւ� �ړ��\���̂�
	if (pInput->GetTrigger(CInput::CODE::CHECK_Y, 0) && !m_pMenuGame->GetLockChangeSelect()) {
		//�t�F�[�h���������ꍇ
		if (pFade->GetFade())
		{
			//�t�F�[�h���X�L�b�v
			pFade->SkipFade();
		}
		else {
			//�`���[�g���A���؂�ւ�
			ChangeTutorial();			
		}
	}

	//�`���[�g���A������
	if ((pInput->GetTrigger(CInput::CODE::SELECT, 0) || pInput->GetTrigger(CInput::CODE::BACK, 0)) && m_pTutorial != nullptr) {
		//�`���[�g���A���؂�ւ�
		ChangeTutorial();
		return;	//�I�����A���ɂȂ�Ȃ��悤�ɏI��
	}

	if (m_pTutorial != nullptr) return;	//�`���[�g���A���������ꂽ�ꍇ��̓��͂͂Ȃ�

	//�R���؂�ւ�
	if (pInput->GetTrigger(CInput::CODE::CHECK_X, 0)) {
		//�t�F�[�h���������ꍇ
		if (pFade->GetFade())
		{
			//�t�F�[�h���X�L�b�v
			pFade->SkipFade();
		}
		else {
			//���[�h�؂�ւ�
			ChangeMode(!m_bWolfMode);
		}
	}

	//����L�[���������Ƃ�
	if (pInput->GetTrigger(CInput::CODE::SELECT, 0))
	{
		//�t�F�[�h���������ꍇ
		if (pFade->GetFade())
		{
			//�t�F�[�h���X�L�b�v
			pFade->SkipFade();
		}
		//�I�����b�N���ł͂Ȃ��Ƃ�
		else if(!m_pMenuGame->GetLockChangeSelect())
		{
			//���݂̑I�����̔ԍ����擾
			int nIdxCurSelect = m_pMenuGame->GetIdxCurSelect();

			// �����ꂽ�t���O
			m_bSelectGame = true;
			//�I���̃��b�N
			m_pMenuGame->SetLockChangeSelect(true);
			//���艹�̍Đ�
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);

			//�����_���I����
			if (nIdxCurSelect == MAX_GAME_NUM) {
				nIdxCurSelect = rand() % MAX_GAME_NUM;	//�����_���ȑI��
				//���j���[�̐ݒ�
				m_pMenuGame->SetIdxCurSelect(nIdxCurSelect);	//�I��ԍ��̐ݒ�
				m_pMenuGame->BeginRoulette(FPS * 3, 0.2f * D3DX_PI, 0.985f);	//���[���b�g�J�n
			}

			//���̃V�[���̌���
			m_nextScene = (CScene::SCENE_TYPE)(nIdxCurSelect + (int)CScene::SCENE_TYPE::GAME_01);	

			//�Q�[�����[�h�ݒ�
			CGameScene::SetWereWolfMode(m_bWolfMode);
		}
	}
	//�߂�L�[����
	else if (pInput->GetTrigger(CInput::CODE::BACK, 0)) {
		// �����ꂽ�t���O
		m_bSelectGame = true;
		//�I���̃��b�N
		m_pMenuGame->SetLockChangeSelect(true);
		//���艹�̍Đ�
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_CANCEL);

		//���̃V�[���̌���
		m_nextScene = CScene::SCENE_TYPE::TITLE;

		//�V�[���J�ڂ��n�܂�܂ł̎��Ԃ�ݒ�
		m_nFadeTime = 0;
	}
}

//=============================================================================
// �`���[�g���A���\���̐؂�ւ�
//=============================================================================
void CSelectGameScene::ChangeTutorial(void) {
	//�`���[�g���A������
	if (m_pTutorial == nullptr) {
		CTexture::TEXTURE_TYPE typeTex;

		switch (m_pMenuGame->GetIdxCurSelect() + (int)CScene::SCENE_TYPE::GAME_01)
		{
			//���D
		case (int)CScene::SCENE_TYPE::GAME_01:
			if (m_bWolfMode) {
				typeTex = CTexture::TEXTURE_TYPE::TUTORIAL_BALLOON_WOLF;
			}
			else {
				typeTex = CTexture::TEXTURE_TYPE::TUTORIAL_BALLOON;
			}
			break;
			//����
		case (int)CScene::SCENE_TYPE::GAME_02:
			if (m_bWolfMode) {
				typeTex = CTexture::TEXTURE_TYPE::TUTORIAL_ATTACK_WOLF;
			}
			else {
				typeTex = CTexture::TEXTURE_TYPE::TUTORIAL_ATTACK;
			}
			break;
			//�����_��(��)
		case (int)CScene::SCENE_TYPE::GAME_MAX:
			typeTex = CTexture::TEXTURE_TYPE::TUTORIAL_RANDOM;
			break;
		default:
			typeTex = CTexture::TEXTURE_TYPE::BG_MENU;
			break;
		}

		//�w�i�ύX
		m_pTutorial = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), typeTex, SCREEN_WIDTH * 1.0f, SCREEN_HEIGHT * 1.0f);
		//����UI�̐���
		m_pNextButton = CNextButton::Create(MENU_NEXT_BUTTON_POS, MENU_NEXT_BUTTON_SIZE,
			                                CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_3, MENU_NEXT_BUTTON_COUNTER,
			                                MENU_NEXT_BUTTON_DEC_ALPHA);

		//�I����ʂ̈ړ������b�N
		if (m_pMenuGame != nullptr) m_pMenuGame->SetLockChangeSelect(true);
	}
	//�ʏ탂�[�h�ɕύX
	else {
		//�`���[�g���A����ʂ̔j��
		m_pTutorial->Uninit();
		m_pTutorial = nullptr;

		m_pNextButton->Uninit();
		m_pNextButton = nullptr;

		//�I����ʂ̈ړ����b�N������
		if (m_pMenuGame != nullptr) m_pMenuGame->SetLockChangeSelect(false);
	}

	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	CSound* pSound = nullptr;	//�T�E���h�ւ̃|�C���^

	if (pManager != nullptr) {
		//�T�E���h�̎擾
		pSound = pManager->GetSound();
	}

	//�ύX���̐ݒ�
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_GET);
}

//=============================================================================
//�Q�[���^�C�g���̐ؑ�
//=============================================================================
void CSelectGameScene::ChangeGameTitle()
{
	//���ݑI�΂�Ă���Q�[���ɂ���ă^�C�g���̖��O��ς���
	switch (m_pMenuGame->GetIdxCurSelect() + (int)CScene::SCENE_TYPE::GAME_01)
	{
		//�o���[��
	case (int)CScene::SCENE_TYPE::GAME_01:
		if (m_pGameName->GetTexType() == CTexture::TEXTURE_TYPE::TEXT_TITLENAME_BALLOON && !m_pMenuGame->GetRoulette()) return;
		m_pGameName->SetTexType(CTexture::TEXTURE_TYPE::TEXT_TITLENAME_BALLOON);
		break;
		//�Ԃ����
	case (int)CScene::SCENE_TYPE::GAME_02:
		if (m_pGameName->GetTexType() == CTexture::TEXTURE_TYPE::TEXT_TITLENAME_ATTACK && !m_pMenuGame->GetRoulette()) return;
		m_pGameName->SetTexType(CTexture::TEXTURE_TYPE::TEXT_TITLENAME_ATTACK);
		break;
		//�X�g�b�v
	case (int)CScene::SCENE_TYPE::GAME_03:
		if (m_pGameName->GetTexType() == CTexture::TEXTURE_TYPE::TEXT_GAMESTART && !m_pMenuGame->GetRoulette()) return;
		m_pGameName->SetTexType(CTexture::TEXTURE_TYPE::TEXT_GAMESTART);
		break;
		//�����_��
	case (int)CScene::SCENE_TYPE::GAME_MAX:
		if (m_pGameName->GetTexType() == CTexture::TEXTURE_TYPE::TEXT_TITLENAME_RANDOM) return;
		m_pGameName->SetTexType(CTexture::TEXTURE_TYPE::TEXT_TITLENAME_RANDOM);
		break;
	default:
		break;
	}
}

//=============================================================================
// �R�����[�h�̐؂�ւ�
//=============================================================================
void CSelectGameScene::ChangeMode(bool bWolf) {
	m_bWolfMode = bWolf;

	//�R�����[�h�ɕύX
	if (m_bWolfMode) {
		//�w�i�ύX
		if (m_pMenuBG != nullptr) m_pMenuBG->SetTexType(CTexture::TEXTURE_TYPE::BG_MENU_WOLF);
		if (m_pMenuNoneMoveUi != nullptr) m_pMenuNoneMoveUi->SetTexType(CTexture::TEXTURE_TYPE::MENU_NONE_MOVE_UI_WOLF);
		if (m_pModeUi != nullptr) m_pModeUi->SetTexType(CTexture::TEXTURE_TYPE::MENU_MODE_WOLF);
	}
	//�ʏ탂�[�h�ɕύX
	else {
		//�w�i�ύX
		if (m_pMenuBG != nullptr) m_pMenuBG->SetTexType(CTexture::TEXTURE_TYPE::BG_MENU);
		if (m_pMenuNoneMoveUi != nullptr) m_pMenuNoneMoveUi->SetTexType(CTexture::TEXTURE_TYPE::MENU_NONE_MOVE_UI);
		if (m_pModeUi != nullptr) m_pModeUi->SetTexType(CTexture::TEXTURE_TYPE::MENU_MODE_NORMAL);
	}

	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	CSound* pSound = nullptr;	//�T�E���h�ւ̃|�C���^

	if (pManager != nullptr) {
		//�T�E���h�̎擾
		pSound = pManager->GetSound();
	}

	//�ύX���̐ݒ�
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_GET);
}

//=============================================================================
//�w�i�̓����̏���
//=============================================================================
void CSelectGameScene::BgMove(){
	if (m_pMenuBG == nullptr) return;

	//�w�i�𓮂���
	m_pMenuBG->SetMoveTex(MENU_BG_MOVE_SPEED.x, MENU_BG_MOVE_SPEED.y);
}

//=============================================================================
//���UI�̓�������
//=============================================================================
void CSelectGameScene::AlowUi()
{
	for (int nCntAlow = 0; nCntAlow < SELECT_GAME_SCENE_ALOW_UI_NUM; nCntAlow++)
	{
		if (m_pAlowUi[nCntAlow] == nullptr) continue;

		//�ʒu�擾
		D3DXVECTOR3 pos = m_pAlowUi[nCntAlow]->GetPos();

		//�ړ��ʉ��Z
		if(m_bAlowUiMoveChange[nCntAlow]) m_fAlowUiMove[nCntAlow] += MENU_ALOW_UI_MOVE;
		else m_fAlowUiMove[nCntAlow] -= MENU_ALOW_UI_MOVE;
		
		//�ړ��ʍő�l�𒴂�����
		if (m_fAlowUiMove[nCntAlow] > MENU_ALOW_UI_MOVE_MAX) m_fAlowUiMove[nCntAlow] = MENU_ALOW_UI_MOVE_MAX;
		else if (m_fAlowUiMove[nCntAlow] < -MENU_ALOW_UI_MOVE_MAX) m_fAlowUiMove[nCntAlow] = -MENU_ALOW_UI_MOVE_MAX;

		//�ʒu�ɉ��Z
		pos.x += m_fAlowUiMove[nCntAlow];

		//�ʒu���f
		m_pAlowUi[nCntAlow]->SetPos(pos);

		float fPosMax = SCREEN_WIDTH / 2.0f - MENU_ALOW_UI_POS_MIN;
		float fPosMin = SCREEN_WIDTH / 2.0f - MENU_ALOW_UI_POS_MAX;
		if (nCntAlow == 1)
		{
			fPosMax = SCREEN_WIDTH / 2.0f + MENU_ALOW_UI_POS_MAX;
			fPosMin = SCREEN_WIDTH / 2.0f + MENU_ALOW_UI_POS_MIN;
		}

		if (pos.x <= fPosMin)
		{
			if (!m_bAlowUiMoveChange[nCntAlow]) m_bAlowUiMoveChange[nCntAlow] = true;
		}
		else if (pos.x >= fPosMax)
		{
			if (m_bAlowUiMoveChange[nCntAlow]) m_bAlowUiMoveChange[nCntAlow] = false;
		}
	}
}
