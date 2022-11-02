//=============================================================================
//
// �Q�[���V�[������ [gameScene.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "gameScene.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "gameCamera.h"
#include "fade.h"
#include "timer.h"
#include "object2D.h"
#include "object_player_balloon_car.h"
#include "meshwall.h"
#include "wallCylinder.h"
#include "pauseMenu.h"
#include "balloon.h"
#include "itemBox.h"
#include "count_down_ui.h"
#include "finish_ui.h"
#include "player.h"

//�G�t�F�N�g
#include "plane.h"
#include "PresetSetEffect.h"

#include "player_icon.h"
#include "ToScreen.h"
#include "check.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GAME_FINISH_UI_NUM						 (5)		//�t�B�j�b�V��UI�̐�

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
bool CGameScene::m_bWereWolfMode = true;
int CGameScene::m_nWereWolfPlayerIndex = 1;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGameScene::CGameScene()
{
	m_pTimer = nullptr;
	m_bAllCheck = false;
	m_bReady = false;
	m_pCheck = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameScene::~CGameScene()
{

}

//=============================================================================
// �Q�[���V�[���̏���������
//=============================================================================
void CGameScene::Init(void) {
	//�ϐ�������
	m_bAllCheck = false;
	m_bReady = true;

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�
	CObject::SetUpdatePauseLevel(0);
	
	//�`�F�b�N�A�C�R���̐���
	m_pCheck = CCheck::Create(MAX_OBJECT_PLAYER_NUM);

#ifdef _DEBUG
	//Z�o�b�t�@�e�N�X�`���̕\��
	CObject2D* pZBuff = CObject2D::Create(D3DXVECTOR3(70.0f, 70.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, 100.0f, 100.0f);
	if (pZBuff != nullptr) {
		pZBuff->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
		pZBuff->SetUseZBuffTexture(true);
	}
#endif
}

//=============================================================================
// �Q�[���V�[���̏I������
//=============================================================================
void CGameScene::Uninit(void) {

	//�V�[���̃v���C���[�̐ݒ�
	SetPlayer(nullptr);

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
// �Q�[���V�[���̍X�V����
//=============================================================================
void CGameScene::Update(void) {


}

//=============================================================================
// �|�[�Y���j���[�̔j��
//=============================================================================
void CGameScene::DeletePauseMenu(void) {
	//�|�[�Y���j���[�̔j��
	if (m_pMenuPause != nullptr) {
		m_pMenuPause->Uninit();
		m_pMenuPause = nullptr;
	}
}

//=============================================================================
// �Q�[���I�[�o�[
//=============================================================================
void CGameScene::GameOver(void) {
	if (m_bGameOver) return;

	m_bGameOver = true;

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//�Q�[���I�[�o�[�����Đ�
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_TIME_UP);


	//�t�B�j�b�V��UI����
	CFinishUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 0, 1.0f);
	for (int nCntFinish = 0; nCntFinish < GAME_FINISH_UI_NUM; nCntFinish++)
	{
		CFinishUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), nCntFinish + 1, 0.4f);
	}

	//�^�C�}�[���~
	if (m_pTimer != nullptr) {
		m_pTimer->SetStop(true);
	}

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�i�O�̂��߁j
	CObject::SetUpdatePauseLevel(0);
}
