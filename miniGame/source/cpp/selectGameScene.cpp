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

#include "titleCamera.h"

#include "coverDisplay.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_GAME_NUM ((int)CScene::SCENE_TYPE::GAME_MAX - (int)CScene::SCENE_TYPE::GAME_01)	//�Q�[���̍ő吔
#define MENU_SELECT_NUM (MAX_GAME_NUM + 1)	//�����_�����ǉ�

#define MENU_BG_MOVE_SPEED		(D3DXVECTOR2(0.001f, 0.001f))		//�w�i�̈ړ����x

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
	m_nFadeTime = FPS;
	m_bWolfMode = false;
	m_pTutorial = nullptr;
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
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�����_���[�̎擾
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//�J�����̐ݒ�
	if (pManager != nullptr) pManager->SetCamera(CTitleCamera::Create());	//���Ń^�C�g���J����

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

	//------------------------------
	//UI�̐���
	//------------------------------
	// �w�i
	m_pMenuBG = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::BG_MENU, SCREEN_WIDTH, SCREEN_HEIGHT);

	//BGM�̍Đ�
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_TITLE);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_TITLE);
	}

	//�I�����j���[�̔w�i
	CObject2D* pMenuStencil = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 250.0f, 0.0f), CTexture::TEXTURE_TYPE::ITEM_UI_FRAME_2, 1000.0f, 450.0f);
	if (pMenuStencil != nullptr) {
		pMenuStencil->SetDrawStencil(true);
	}

	//�I�����j���[�̐���
	m_pMenuGame = CSelectMenu3D::Create(MENU_SELECT_NUM, D3DXVECTOR3(0.0f, 100.0f, 0.0f), 300.0f, CModel::MODELTYPE::OBJ_BALLOON_PINK, 800.0f, 300.0f, false);

	if (m_pMenuGame != nullptr) {
		//�Q�[�����Ƃ̃��f���̔z��
		const CModel::MODELTYPE typeModelGame[MENU_SELECT_NUM] =
		{	
			CModel::MODELTYPE::OBJ_BALLOON_PINK,
			CModel::MODELTYPE::OBJ_CAR,
			CModel::MODELTYPE::OBJ_HATENA,
		};

		//�S���f���̐ݒ�
		for (int nIdxModel = 0; nIdxModel < MENU_SELECT_NUM; nIdxModel++)
		{
			//���j���[��UI�I�u�W�F�N�g�̎擾
			CObjectModelUI* pObjModelUI = m_pMenuGame->GetModelUI(nIdxModel);
			if (pObjModelUI == nullptr) continue;

			//�X�e���V���L��
			pObjModelUI->SetEnableStencil(true);

			//��]���x�̐ݒ�
			pObjModelUI->SetRotSpeed(D3DXVECTOR3(0.0f, 0.02f, 0.0f));

			//UI�I�u�W�F�N�g�̃��f���̎擾
			CModel* pModel = pObjModelUI->GetPtrModel();
			if (pModel == nullptr) continue;

			//���f����ݒ�
			pModel->SetModelType(typeModelGame[nIdxModel]);
		}
	}

	//�Q�[�����̔w�i
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 600.0f, 0.0f), CTexture::TEXTURE_TYPE::MENU_GAME_TITLE_FRAME_UI, 500.0f, 180.0f);
	//�Q�[�����̐���
	m_pGameName = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 600.0f, 0.0f), CTexture::TEXTURE_TYPE::TEXT_TITLENAME, 400.0f, 150.0f);
	//���UI�̐���
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 350.f, 600.0f, 0.0f), CTexture::TEXTURE_TYPE::ARROW_LEFT, 100.0f, 100.0f);
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 350.f, 600.0f, 0.0f), CTexture::TEXTURE_TYPE::ARROW_RIGHT, 100.0f, 100.0f);

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

	//�w�i�̓����̏���
	BgMove();

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
			}
		}
		// �J�ڂ��鎞�Ԃ�0��菬�����Ȃ��Ă�����
		else if (m_nFadeTime < 0)
		{
			// 0�������ă}�C�i�X�l�ɂȂ�Ȃ��悤�ɂ���
			m_nFadeTime = 0;
			//�V�[���J�ڊJ�n			
			if (pFade != nullptr) pFade->SetFade(m_nextScene, 0.02f, 60);
			//�I���̃��b�N
			m_pMenuGame->SetLockChangeSelect(true);
		}
		else
		{
			//�t�F�[�h�J�n�J�E���g����
			m_nFadeTime--;
		}
	}
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
			typeTex = CTexture::TEXTURE_TYPE::MESH_CLOUD;
			break;
		default:
			typeTex = CTexture::TEXTURE_TYPE::BG_MENU;
			break;
		}

		//�w�i�ύX
		m_pTutorial = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), typeTex, SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.9f);
		//�I����ʂ̈ړ������b�N
		if (m_pMenuGame != nullptr) m_pMenuGame->SetLockChangeSelect(true);
	}
	//�ʏ탂�[�h�ɕύX
	else {
		//�`���[�g���A����ʂ̔j��
		m_pTutorial->Uninit();
		m_pTutorial = nullptr;

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
// �R�����[�h�̐؂�ւ�
//=============================================================================
void CSelectGameScene::ChangeMode(bool bWolf) {
	m_bWolfMode = bWolf;

	//�R�����[�h�ɕύX
	if (m_bWolfMode) {
		//�w�i�ύX
		if (m_pMenuBG != nullptr) m_pMenuBG->SetTexType(CTexture::TEXTURE_TYPE::BG_MENU_WOLF);
	}
	//�ʏ탂�[�h�ɕύX
	else {
		//�w�i�ύX
		if (m_pMenuBG != nullptr) m_pMenuBG->SetTexType(CTexture::TEXTURE_TYPE::BG_MENU);
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
