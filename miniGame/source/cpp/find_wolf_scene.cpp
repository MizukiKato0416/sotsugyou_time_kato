//=============================================================================
//
// �l�T���菈�� [find_wolf_scene.cpp]
// Author : ��������
//
//=============================================================================
#include "find_wolf_scene.h"
#include "manager.h"
#include "renderer.h"
#include "gameCamera.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "object2D.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFindWolf::CFindWolf()
{	
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFindWolf::~CFindWolf()
{

}

//=============================================================================
// ����������
//=============================================================================
void CFindWolf::Init(void) {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�����_���[�̎擾
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//�J�����̐ݒ�
	if (pManager != nullptr) pManager->SetCamera(CGameCamera::Create());	//�Ȃɂ���J�����������ƕ`�悳��Ȃ��̂łƂ肠�����Q�[���J����

	//------------------------------
	//UI�̐���
	//------------------------------
	// �w�i
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::BG_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	
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
void CFindWolf::Uninit(void) {	

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
void CFindWolf::Update(void) {		
	
}