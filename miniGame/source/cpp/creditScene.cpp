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

//=============================================================================
// �}�N����`
//=============================================================================
#define CREDIT_SCENE_BG_MOVE_SPEED		(D3DXVECTOR2(0.001f, 0.001f))		//�w�i�̈ړ����x

#define CREDIT_SCENE_CREDIT_SIZE_Y		(7809.0f)		//�N���W�b�g�T�C�YY
#define CREDIT_SCENE_CREDIT_MOVE		(1.7f)			//�N���W�b�g�̈ړ����x

#define CREDIT_SCENE_FADE_SPEED		(60)			//�t�F�[�h�̑��x
#define CREDIT_SCENE_FADE_DELAY		(180)			//�t�F�[�h����܂ł̒x��

#define CREDIT_SCENE_PICTURE_CREATE_POS		(D3DXVECTOR3(400.0f, 1000.0f, 0.0f))		//�G�̐����ʒu
#define CREDIT_SCENE_PICTURE_CREATE_SCALE	(D3DXVECTOR3(0.35f, 0.35f, 0.35f))			//�G�̑傫��
#define CREDIT_SCENE_PICTURE_SPEED			(1.5f)										//�G�̈ړ����x
#define CREDIT_SCENE_PICTURE_ROT			(float((rand() % 61 + -30) / 100.0f))		//�G�̌����͈̔�
#define CREDIT_SCENE_CREATE_INTERVAL		(480)										//�G�̐����Ԋu
#define CREDIT_SCENE_INIT_CREATE_INTERVAL	(360)										//�G�̍ŏ��̐����Ԋu

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CCreditScene::CCreditScene()
{
	m_pBg = nullptr;
	m_pCredit = nullptr;
	m_bCanFade = false;
	m_nFrameCounter = 0;
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
	m_bCanFade = false;
	m_nFrameCounter = CREDIT_SCENE_INIT_CREATE_INTERVAL;

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
//�I�u�W�F�N�g��������
//=============================================================================
void CCreditScene::CreateObject(void)
{
	//�w�i
	m_pBg = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pBg->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	//�N���W�b�g����
	m_pCredit = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, CREDIT_SCENE_CREDIT_SIZE_Y / 2.0f + SCREEN_HEIGHT, 0.0f),
		                          CTexture::TEXTURE_TYPE::CREDIT_CREDIT, SCREEN_WIDTH, CREDIT_SCENE_CREDIT_SIZE_Y);
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

	//�N���W�b�g����
	Credit();

	//�G��������
	CreatePicture();

	//�w�i����
	Bg();

	//�J�ڏ���
	Fade();
}

//=============================================================================
//�w�i����
//=============================================================================
void CCreditScene::Bg()
{
	if (m_pBg == nullptr) return;

	//�w�i�𓮂���
	//m_pBg->SetMoveTex(CREDIT_SCENE_BG_MOVE_SPEED.x, CREDIT_SCENE_BG_MOVE_SPEED.y);
}

//=============================================================================
//�J�ڏ���
//=============================================================================
void CCreditScene::Fade()
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

	if (m_nFrameCounter % CREDIT_SCENE_CREATE_INTERVAL == 0 && m_nFrameCounter < 3500)
	{
		//�G�̐���
		CCreditPicture::Create(CREDIT_SCENE_PICTURE_CREATE_POS, CREDIT_SCENE_PICTURE_CREATE_SCALE, CREDIT_SCENE_PICTURE_ROT,
			                   CTexture::TEXTURE_TYPE::MESH_CAR_TIRE, -CREDIT_SCENE_PICTURE_SPEED);
	}
}
