//=============================================================================
//
// �|�[�Y���j���[���� [pauseMenu.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "pauseMenu.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "gameScene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define NUM_SELECT (3)
#define SELECT_TITLE_POS (D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 300.0f, 0.0f))
#define SELECT_RESTATE_POS (D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 450.0f, 0.0f))
#define SELECT_CONTINUE_POS (D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 600.0f, 0.0f))
#define SELECT_UI_WIDTH (500.0f)
#define SELECT_UI_HEIGHT (100.0f)
#define SELECT_ICON_POS (D3DXVECTOR3(-250.0f, 0.0f, 0.0f))
#define SELECT_ICON_WIDTH (70.0f)
#define SELECT_ICON_HEIGHT (50.0f)

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CPauseMenu::CPauseMenu() : CSelectMenu2D(NUM_SELECT, true)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPauseMenu::~CPauseMenu()
{

}

//=============================================================================
// �|�[�Y���j���[�̐�������
//=============================================================================
CPauseMenu* CPauseMenu::Create(void) {
	CPauseMenu* pPauseMenu;
	pPauseMenu = new CPauseMenu();
	if (pPauseMenu == nullptr) return nullptr;

	//�|�[�Y�̐ݒ�
	pPauseMenu->SetPauseLevel(AddUpdatePauseLevel());	//�|�[�Y�̃��x�����グ�ĕԂ�l�Ń|�[�Y�X�V�\���x�����擾���A�I�u�W�F�N�g�̃|�[�Y���x���Ƃ��Đݒ�

	pPauseMenu->Init();

	return pPauseMenu;
}

//=============================================================================
// �|�[�Y���j���[�̏���������
//=============================================================================
HRESULT CPauseMenu::Init(void) {
#ifndef _DEBUG
	//�w�i�̐ݒ�
	SetMenuBG(CTexture::TEXTURE_TYPE::PAUSE_BG, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);	
#endif
	//�c�I��
	SetSelectType(CSelectMenu::SELECT_TYPE::VERTICAL);
	//�I����UI�̏ڍאݒ�
	SetSelectUI(0, SELECT_TITLE_POS, SELECT_UI_WIDTH, SELECT_UI_HEIGHT, CTexture::TEXTURE_TYPE::PAUSE_CONTINUE);
	SetSelectUI(1, SELECT_RESTATE_POS, SELECT_UI_WIDTH, SELECT_UI_HEIGHT, CTexture::TEXTURE_TYPE::PAUSE_RESTART);
	SetSelectUI(2, SELECT_CONTINUE_POS, SELECT_UI_WIDTH, SELECT_UI_HEIGHT, CTexture::TEXTURE_TYPE::PAUSE_MENU);
	//�I�����A�C�R���̐���
	CreateSelectIcon(SELECT_ICON_POS, SELECT_ICON_WIDTH, SELECT_ICON_HEIGHT, CTexture::TEXTURE_TYPE::SELECT_ICON);
	SetIconPosOffset(1, D3DXVECTOR3(-230.0f, 0.0f, 0.0f));

	CSelectMenu2D::Init();

	return S_OK;
}

//=============================================================================
// �|�[�Y���j���[�̏I������
//=============================================================================
void CPauseMenu::Uninit(void) {
	CSelectMenu2D::Uninit();

	//�|�[�Y�̃��x����������
	//SubUpdatePauseLevel();	//�|�[�Y���j���[�̑I���ɂ���ĕ��򂳂���悤�ɂ��邽�߃R�����g�A�E�g
}

//=============================================================================
// �|�[�Y���j���[�̍X�V����
//=============================================================================
void CPauseMenu::Update(void) {
	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	//���݂̓��̓f�o�C�X�̎擾
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;
	//�t�F�[�h�̎擾
	CFade* pFade = pManager->GetFade();		//�t�F�[�h�ւ̃|�C���^
	if (pFade == nullptr) return;
	//�Q�[���V�[���̎擾
	CGameScene* pGameScene = pManager->GetGameScene();		//�t�F�[�h�ւ̃|�C���^
	if (pGameScene == nullptr) return;
	//�T�E���h�̎擾
	CSound* pSound = pManager->GetSound();	//�T�E���h�ւ̃|�C���^
	if (pSound == nullptr) return;

	if (pInput != nullptr) {
		//�I�������
		if (pInput->GetTrigger(CInput::CODE::SELECT, 0) && !GetLockChangeSelect()) {
			switch (GetIdxCurSelect())
			{
				//�Q�[���ĊJ
			case 0:
				//�Q�[���V�[���̃|�[�Y���j���[��j������
				pGameScene->DeletePauseMenu();
				//�|�[�Y�̃��x����������
				SubUpdatePauseLevel();
				//�T�E���h���Đ�
				pSound->PlaySound(CSound::SOUND_LABEL::SE_CANCEL);
				return;
				break;

				//���g���C
			case 1:
				//�Q�[���V�[���̃|�[�Y���j���[��j������
				pGameScene->DeletePauseMenu();
				//���݂̃V�[���������[�h
				pFade->SetFade(CScene::GetSceneType(), 0.02f, 0);
				//�T�E���h���Đ�
				pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
				break;

				//�Q�[���I���ɖ߂�
			case 2:
				//�Q�[���V�[���̃|�[�Y���j���[��j������
				pGameScene->DeletePauseMenu();
				//�Q�[���I���V�[���J��
				pFade->SetFade(CScene::SCENE_TYPE::SELECT_GAME , 0.02f, 0);
				//�T�E���h���Đ�
				pSound->PlaySound(CSound::SOUND_LABEL::SE_CANCEL);
				break;
			}
		}
	}

	CSelectMenu2D::Update();
}