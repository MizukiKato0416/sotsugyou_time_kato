//=============================================================================
//
// �l�T���菈�� [wolf_decide.cpp]
// Author : ��������
//
//=============================================================================
#include "wolf_decide.h"
#include "object2D.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "object_player.h"
#include "gameScene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define WOLF_DECIDE_SHAKE_MAX_TIME	(180)		//�U�����鎞��
#define WOLF_DECIDE_SHAKE_INTERVAL	(60)		//�U������Ԋu
#define WOLF_DECIDE_SHAKE_NUM		(15000)		//�U�������
#define WOLF_DECIDE_SHAKE_TIME		(45)		//���̐U���ŐU�����鎞��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CWolfDecide::CWolfDecide()
{
	m_pBg = nullptr;
	m_pShakeUI = nullptr;
	m_pTutorialUI = nullptr;
	m_phase = PHASE::NONE;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWolfDecide::~CWolfDecide()
{
	
}

//=============================================================================
// ��������
//=============================================================================
CWolfDecide* CWolfDecide::Create(void) {
	CWolfDecide* pWolfDecide;
	pWolfDecide = new CWolfDecide();
	if (pWolfDecide == nullptr) return nullptr;

	pWolfDecide->Init();

	return pWolfDecide;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWolfDecide::Init(void) {
	
	//�ϐ�������
	m_nShakeUiCounter = 0;
	m_phase = PHASE::SHAKE_TUTORIAL;

	//�l�T�����߂�
	int nWolfPlayerIndex = (rand() % MAX_OBJECT_PLAYER_NUM) + 1;
	//�l�T��ݒ�
	CGameScene::SetWereWolfPlayerIndex(nWolfPlayerIndex);


	//�w�i�̈Â����
	m_pBg = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pBg->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));


	//����UI
	m_pTutorialUI = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                              CTexture::TEXTURE_TYPE::WOLF_SHAKE_TUTORIAL, SCREEN_WIDTH, SCREEN_HEIGHT);


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWolfDecide::Uninit(void) {

	//��������Ă�����
	if (m_pBg != nullptr)
	{
		//����
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	//����
	if (m_pTutorialUI != nullptr)
	{
		m_pTutorialUI->Uninit();
		m_pTutorialUI = nullptr;
	}

	//����
	if (m_pShakeUI != nullptr)
	{
		m_pShakeUI->Uninit();
		m_pShakeUI = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CWolfDecide::Update(void) {
	
	//��������
	switch (m_phase)
	{
	case CWolfDecide::PHASE::SHAKE_TUTORIAL:
		//�U����������
		ShakeTutorial();
		break;
	case CWolfDecide::PHASE::SHAKE:
		//�U������
		Shake();
		break;
	case CWolfDecide::PHASE::GAME_START:
		//�Q�[���X�^�[�g����
		GameStart();
		break;
	default:
		break;
	}
}

//=============================================================================
//�U����������
//=============================================================================
void CWolfDecide::ShakeTutorial()
{
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//���݂̓��̓f�o�C�X�̎擾
		pInput = pManager->GetInputCur();
	}

	//�{�^������������
	if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT), 0))
	{
		//�}�l�[�W���[�̎擾
		CManager* pManager = CManager::GetManager();
		//�T�E���h�̎擾
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//�����Đ�
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_OK);

		//����
		if (m_pTutorialUI != nullptr)
		{
			m_pTutorialUI->Uninit();
			m_pTutorialUI = nullptr;
		}

		//���̃t�F�[�Y�ɂ���
		m_phase = PHASE::SHAKE;

		//�U��UI�̐���
		if (m_pShakeUI == nullptr)
		{
			m_pShakeUI = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                                   CTexture::TEXTURE_TYPE::WOLF_SHAKE, 1282.0f * 0.7f, 167.0f * 0.7f);
		}
	}
}

//=============================================================================
//�U������
//=============================================================================
void CWolfDecide::Shake()
{
	if (m_pShakeUI == nullptr)
	{
		return;
	}

	m_nShakeUiCounter++;

	//�w�莞�ԂɂȂ�����
	if (m_nShakeUiCounter > WOLF_DECIDE_SHAKE_MAX_TIME)
	{
		//����
		m_pShakeUI->Uninit();
		m_pShakeUI = nullptr;

		//���̃t�F�[�Y�ɂ���
		m_phase = PHASE::GAME_START;

		//����UI
		m_pTutorialUI = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
			                              CTexture::TEXTURE_TYPE::WOLF_SHAKE_START, SCREEN_WIDTH, SCREEN_HEIGHT);

		return;
	}

	//�w��t���[������
	if (m_nShakeUiCounter % WOLF_DECIDE_SHAKE_INTERVAL == 0)
	{
		//�J���[�擾
		D3DXCOLOR col = m_pShakeUI->GetColor();
		//�����Ă��Ȃ��Ȃ�
		if (col.a == 0.0f)
		{
			//������悤�ɂ���
			col.a = 1.0f;
		}
		else
		{//�����Ă���Ȃ�
			//�����Ȃ��悤�ɂ���
			col.a = 0.0f;
		}
		//�J���[�ݒ菈��
		m_pShakeUI->SetColor(col);

		//�}�l�[�W���[�̎擾
		CManager* pManager = CManager::GetManager();
		CInput* pInput = nullptr;
		CInputGamepadX *pPadX = nullptr;
		if (pManager != nullptr) {
			//���݂̓��̓f�o�C�X�̎擾
			pInput = pManager->GetInputCur();
			pPadX = dynamic_cast<CInputGamepadX*>(pInput);
		}

		for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
		{
			//�l�T����Ȃ�������
			if (pPadX != nullptr && nCntPlayer != CGameScene::GetWereWolfPlayerIndex() - 1)
			{
				//�U��������
				pPadX->SetVibration(WOLF_DECIDE_SHAKE_NUM, WOLF_DECIDE_SHAKE_NUM, WOLF_DECIDE_SHAKE_TIME, nCntPlayer);
			}
		}
	}
}

//=============================================================================
//�Q�[���X�^�[�g����
//=============================================================================
void CWolfDecide::GameStart()
{
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//���݂̓��̓f�o�C�X�̎擾
		pInput = pManager->GetInputCur();
	}

	//�{�^������������
	if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT), 0))
	{
		//�}�l�[�W���[�̎擾
		CManager* pManager = CManager::GetManager();
		//�T�E���h�̎擾
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//�����Đ�
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_OK);

		//����
		if (m_pTutorialUI != nullptr)
		{
			m_pTutorialUI->Uninit();
			m_pTutorialUI = nullptr;
		}

		//�t�F�[�Y�����ɂ���
		m_phase = PHASE::UNINIT;
	}
}
