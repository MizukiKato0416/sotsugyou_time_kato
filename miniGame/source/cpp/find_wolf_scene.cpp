//=============================================================================
//
// �l�T���菈�� [find_wolf_scene.cpp]
// Author : ��������
//
//=============================================================================
#include "find_wolf_scene.h"
#include "manager.h"
#include "renderer.h"
#include "find_wolf_camera.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "object2D.h"
#include "object_player.h"
#include "objectModelUI.h"
#include "ToScreen.h"
#include "score_ui.h"
#include "score.h"
#include "gameScene.h"
#include "timer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FIND_WOLF_SCENE_SELECT_ICON_SIZE_X			(440.0f * 0.2f)							//�I���A�C�R���̃T�C�YX
#define FIND_WOLF_SCENE_SELECT_ICON_SIZE_Y			(314.0f * 0.2f)							//�I���A�C�R���̃T�C�YY
#define FIND_WOLF_SCENE_SELECT_ICON_DECIDE_COLOR	(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f))		//�I���A�C�R���̌��莞�̃J���[

#define FIND_WOLF_SCENE_SELECT_TIME					(10)		//�I���ł��鎞��
#define FIND_WOLF_SCENE_SELECT_ALL_INTERVAL			(90)		//�S�����I�����Ă��玟�̃t�F�[�Y�ɍs���܂ł̊Ԋu

#define FIND_WOLF_SCENE_SCORE_UI_SCALE				(D3DXVECTOR3(0.5f, 0.5f, 0.5f))		//�X�R�AUI�̃X�P�[��
#define FIND_WOLF_SCENE_SCORE_UI_POS_Y				(50.0f)								//�X�R�AUI�̈ʒuY
#define FIND_WOLF_SCENE_SCORE_UI_POS_X				(140.0f)							//�X�R�AUI�̈ʒuX
#define FIND_WOLF_SCENE_SCORE_UI_POS_DIFFER_Y		(90.0f)								//�X�R�AUI�̈ʒuY�̋���

#define FIND_WOLF_SCENE_PLAYER_DIFFER				(150.0f)			//�v���C���[�Ԃ̋���

#define FIND_WOLF_SCENE_PLAYER_INDEX_UI_POS_Y		(100.0f)			//�v���C���[�C���f�b�N�XUI�̈ʒuY
#define FIND_WOLF_SCENE_PLAYER_INDEX_UI_SIZE_X		(201.0f * 0.5f)		//�v���C���[�C���f�b�N�XUI�̃T�C�YX
#define FIND_WOLF_SCENE_PLAYER_INDEX_UI_SIZE_Y		(181.0f * 0.5f)		//�v���C���[�C���f�b�N�XUI�̃T�C�YY

#define FIND_WOLF_SCENE_PLAYER_WAIT_TIME			(240)				//���ʔ��\�̎���


//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFindWolfScene::CFindWolfScene()
{	
	memset(m_apScoreUi, NULL, sizeof(m_apScoreUi[MAX_OBJECT_PLAYER_NUM]));
	memset(m_pSelectIcon, NULL, sizeof(m_pSelectIcon[MAX_OBJECT_PLAYER_NUM]));
	memset(m_select, 0, sizeof(m_select[MAX_OBJECT_PLAYER_NUM]));
	m_phase = PHASE::NONE;
	m_pTutorial = nullptr;
	m_nFrameCounter = 0;

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		m_aPosPlayer2D[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFindWolfScene::~CFindWolfScene()
{

}

//=============================================================================
// ����������
//=============================================================================
void CFindWolfScene::Init(void) {

	//�ϐ�������
	m_phase = PHASE::TUTORIAL_1;
	memset(m_pSelectIcon, NULL, sizeof(m_pSelectIcon[MAX_OBJECT_PLAYER_NUM]));
	memset(m_select, 0, sizeof(m_select[MAX_OBJECT_PLAYER_NUM]));
	m_nFrameCounter = 0;

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�����_���[�̎擾
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//�J�����̐ݒ�
	if (pManager != nullptr) pManager->SetCamera(CFindWolfCamera::Create());	//�Ȃɂ���J�����������ƕ`�悳��Ȃ��̂łƂ肠�����Q�[���J����

	//------------------------------
	//���C�g�̏����ݒ�
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ���C�g�̎ˉe�ϊ�
							   //���C�g�̃v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 100.0f, 3000.0f);

	D3DXMATRIX mtxLightView;   // ���C�g�r���[�ϊ�
	D3DXVECTOR3 posLightV = D3DXVECTOR3(200.0f, 2000.0f, -200.0f);	//���C�g�̎��_�̈ʒu
	D3DXVECTOR3 posLightR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���C�g�̒����_�̈ʒu
	D3DXVECTOR3 vecLight = -D3DXVECTOR3(posLightV - posLightR);	//���C�g�̃x�N�g��
	D3DXVec3Normalize(&vecLight, &vecLight);	//�x�N�g���𐳋K��
												//���C�g�̃r���[�}�g���b�N�X�𐶐�
	D3DXMatrixLookAtLH(&mtxLightView, &posLightV, &posLightR, &D3DXVECTOR3(0, 0, 1));
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
		pRenderer->SetEffectFogColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		pRenderer->SetEffectFogRange(800.0f, 4500.0f);
		//�o�b�N�o�b�t�@���t�H�O�̐F�ɍ��킹��
		pRenderer->SetBackBuffColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}

	//------------------------------
	//�I�u�W�F�N�g�̏����ݒ�
	//------------------------------

	//�X�^�W�A���̐���
	CObjectModel::Create(CModel::MODELTYPE::OBJ_ATTACK_CAR_STAGE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		const float fDist = FIND_WOLF_SCENE_PLAYER_DIFFER;	//�v���C���[���m�̋���
		D3DXVECTOR3 posModel = D3DXVECTOR3(fDist * (-MAX_OBJECT_PLAYER_NUM / 2.0f) + fDist / 2.0f + nIdxPlayer * fDist, 0.0f, 0.0f);	//���[������ׂ�
		CObjectModel* pPlayerModel = CObjectModel::Create(CModel::MODELTYPE::OBJ_CAR, posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		if (pPlayerModel == nullptr) continue;
		CModel* pModel = pPlayerModel->GetPtrModel();

		m_aPosPlayer2D[nIdxPlayer] = WorldToScreen(posModel);

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

		//�v���C���[�̃C���f�b�N�X��UI�𐶐�
		CObject2D *pPlayerIndexUi = CObject2D::Create(m_aPosPlayer2D[nIdxPlayer] + D3DXVECTOR3(0.0f, FIND_WOLF_SCENE_PLAYER_INDEX_UI_POS_Y, 0.0f),
			                                          CTexture::TEXTURE_TYPE::PLAYER_NUM_1,
			                                          FIND_WOLF_SCENE_PLAYER_INDEX_UI_SIZE_X, FIND_WOLF_SCENE_PLAYER_INDEX_UI_SIZE_Y);
		pPlayerIndexUi->SetTexType(static_cast<CTexture::TEXTURE_TYPE>
			                       (static_cast<int> (CTexture::TEXTURE_TYPE::PLAYER_NUM_1) + nIdxPlayer));

		//�X�R�A�̈ʒu
		D3DXVECTOR3 scorePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		if (nIdxPlayer < MAX_OBJECT_PLAYER_NUM / 2)
		{
			scorePos = D3DXVECTOR3(FIND_WOLF_SCENE_SCORE_UI_POS_X,
				                   FIND_WOLF_SCENE_SCORE_UI_POS_Y + FIND_WOLF_SCENE_SCORE_UI_POS_DIFFER_Y * nIdxPlayer ,
				                   0.0f);
		}
		else
		{
			scorePos = D3DXVECTOR3(SCREEN_WIDTH - FIND_WOLF_SCENE_SCORE_UI_POS_X,
				                   FIND_WOLF_SCENE_SCORE_UI_POS_Y + FIND_WOLF_SCENE_SCORE_UI_POS_DIFFER_Y * (nIdxPlayer - 2),
				                   0.0f);
		}

		//�X�R�AUI�̐��� 
		m_apScoreUi[nIdxPlayer] = CScoreUi::Create(scorePos, FIND_WOLF_SCENE_SCORE_UI_SCALE, nIdxPlayer + 1);
		//�X�R�A�̐ݒ�
		m_apScoreUi[nIdxPlayer]->GetScore()->SetScore(40 - (CGameScene::GetRanking(nIdxPlayer) - 1) * 10);
	}

	//����UI�̐���
	m_pTutorial = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                            CTexture::TEXTURE_TYPE::WOLF_FIND_TUTORIAL_1, SCREEN_WIDTH, SCREEN_HEIGHT);

	//------------------------------
	//BGM�̍Đ�
	//------------------------------
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME);
	}

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
// �I������
//=============================================================================
void CFindWolfScene::Uninit(void) {	

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
void CFindWolfScene::Update(void) {		
	
	//��������
	switch (m_phase)
	{
	case CFindWolfScene::PHASE::TUTORIAL_1:
		Tutorial1();		//����1����
		break;
	case CFindWolfScene::PHASE::TUTORIAL_2:
		Tutorial2();		//����2����
		break;
	case CFindWolfScene::PHASE::WOLF_DECIDE:
		WolfDecide();		//�l�T���菈��
		break;
	case CFindWolfScene::PHASE::TUTORIAL_3:
		Tutorial3();		//����3����
		break;
	case CFindWolfScene::PHASE::WAIT:
		Wait();				//�҂���
		break;
	case CFindWolfScene::PHASE::ANSWER:
		Answer();			//�񓚏���
		break;
	case CFindWolfScene::PHASE::TUTORIAL_4:
		Tutorial4();		//����4����
		break;
	case CFindWolfScene::PHASE::DEC_WOLF_POINT:
		DecWolfPoint();		//�l�T�̃|�C���g�}�C�i�X����
		break;
	case CFindWolfScene::PHASE::ADD_PLAYER_POINT:
		AddPlayerPoint();	//�l�T�ȊO�̃|�C���g���Z����
		break;
	case CFindWolfScene::PHASE::DEC_PLAYER_POINT:
		DecPlayerPoint();	//�l�T�ȊO�̃|�C���g�}�C�i�X����
		break;
	case CFindWolfScene::PHASE::ADD_WOLF_POINT:
		AddWolfPoint();		//�l�T�̃|�C���g���Z����
		break;
	default:
		break;
	}

}

//=============================================================================
//����1
//=============================================================================
void CFindWolfScene::Tutorial1()
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

		//���̃t�F�[�Y�ɂ���
		m_phase = PHASE::TUTORIAL_2;

		//�e�N�X�`����ς���
		m_pTutorial->SetTexType(CTexture::TEXTURE_TYPE::WOLF_FIND_TUTORIAL_2);
	}
}

//=============================================================================
//����2
//=============================================================================
void CFindWolfScene::Tutorial2()
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

		//���̃t�F�[�Y�ɂ���
		m_phase = PHASE::WOLF_DECIDE;

		//����
		m_pTutorial->Uninit();
		m_pTutorial = nullptr;


		for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
		{
			//�I��p�A�C�R���̐���
			m_pSelectIcon[nIdxPlayer] = CObject2D::Create(m_aPosPlayer2D[0], 
				                                          static_cast<CTexture::TEXTURE_TYPE>(static_cast<int>(CTexture::TEXTURE_TYPE::WOLF_SELECT_ICON_1) + nIdxPlayer),
				                                          FIND_WOLF_SCENE_SELECT_ICON_SIZE_X, FIND_WOLF_SCENE_SELECT_ICON_SIZE_Y);
			//�I��p�A�C�R��UI�̈ʒu�ݒ菈��
			SelectIconSetPos(nIdxPlayer, m_select[nIdxPlayer]);
		}

		//��������Ă��Ȃ�������
		if (m_pTimerFrame == nullptr)
		{
			//�^�C�}�[�̐���
			m_pTimerFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 61.0f, 0.0f), CTexture::TEXTURE_TYPE::TIMER_FRAME, 220.0f, 80.0f);
			m_pTimer = CTimer::Create(FIND_WOLF_SCENE_SELECT_TIME, 2, CTexture::TEXTURE_TYPE::NUMBER_003, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 75.0f, 40.0f, 0.0f), 50.0f);
		}
	}
}

//=============================================================================
//�l�T���菈��
//=============================================================================
void CFindWolfScene::WolfDecide()
{
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//���݂̓��̓f�o�C�X�̎擾
		pInput = pManager->GetInputCur();
	}
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	int nNumDecide = 0;

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		//���肳��Ă�����
		if (m_pSelectIcon[nIdxPlayer]->GetColor() == FIND_WOLF_SCENE_SELECT_ICON_DECIDE_COLOR)
		{
			nNumDecide++;
			continue;
		}

		//���肳��Ă��Ȃ�������
		//�^�C�}�[���O�ɂȂ����ꍇ
		if (m_pTimer != nullptr) {
			if (m_pTimer->GetScore() <= 0) {
				//�F���������Ĕ�������
				m_pSelectIcon[nIdxPlayer]->SetColor(FIND_WOLF_SCENE_SELECT_ICON_DECIDE_COLOR);

				//�}�l�[�W���[�̎擾
				CManager* pManager = CManager::GetManager();
				//�T�E���h�̎擾
				CSound* pSound = nullptr;
				if (pManager != nullptr) pSound = pManager->GetSound();
				//�����Đ�
				if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
				continue;
			}
		}


		//�E����������
		if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT_RIGHT), nIdxPlayer))
		{
			if (static_cast<int>(m_select[nIdxPlayer]) >= static_cast<int>(SELECT::PLAYER_4))continue;

			//�L���X�g
			int nSelect = static_cast<int>(m_select[nIdxPlayer]);
			//���ɂ���
			nSelect++;
			m_select[nIdxPlayer] = static_cast<SELECT>(nSelect);

			//�I��p�A�C�R��UI�̈ʒu�ݒ菈��
			SelectIconSetPos(nIdxPlayer, m_select[nIdxPlayer]);

			//�����Đ�
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_CURSOR);
		}
		//������������
		else if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT_LFET), nIdxPlayer))
		{
			if (static_cast<int>(m_select[nIdxPlayer]) <= static_cast<int>(SELECT::PLAYER_1)) continue;

			//�L���X�g
			int nSelect = static_cast<int>(m_select[nIdxPlayer]);
			//�O�ɂ���
			nSelect--;
			m_select[nIdxPlayer] = static_cast<SELECT>(nSelect);

			//�I��p�A�C�R��UI�̈ʒu�ݒ菈��
			SelectIconSetPos(nIdxPlayer, m_select[nIdxPlayer]);

			//�����Đ�
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_CURSOR);
		}
		//�������������
		else if (pInput->GetTrigger(CInput::CODE(CInput::CODE::SELECT), nIdxPlayer))
		{
			//�F���������Ĕ�������
			m_pSelectIcon[nIdxPlayer]->SetColor(FIND_WOLF_SCENE_SELECT_ICON_DECIDE_COLOR);

			//�}�l�[�W���[�̎擾
			CManager* pManager = CManager::GetManager();
			//�T�E���h�̎擾
			CSound* pSound = nullptr;
			if (pManager != nullptr) pSound = pManager->GetSound();
			//�����Đ�
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
		}
	}

	//�S�����肵�Ă��Ȃ�������
	if (nNumDecide != MAX_OBJECT_PLAYER_NUM) return;
	
	//�S�����肵����
	m_nFrameCounter++;

	if (m_nFrameCounter <= FIND_WOLF_SCENE_SELECT_ALL_INTERVAL) return;

	m_nFrameCounter = 0;
	//�^�C�}�[������
	if (m_pTimerFrame != nullptr)
	{
		m_pTimer->Uninit();
		m_pTimer = nullptr;

		m_pTimerFrame->Uninit();
		m_pTimerFrame = nullptr;
	}

	//���̃t�F�[�Y�ɂ���
	m_phase = PHASE::TUTORIAL_3;

	//����UI�̐���
	m_pTutorial = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                            CTexture::TEXTURE_TYPE::WOLF_FIND_TUTORIAL_3, SCREEN_WIDTH, SCREEN_HEIGHT);
}

//=============================================================================
//����3
//=============================================================================
void CFindWolfScene::Tutorial3()
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

		//���̃t�F�[�Y�ɂ���
		m_phase = PHASE::WAIT;

		//����
		m_pTutorial->Uninit();
		m_pTutorial = nullptr;
	}
}

//=============================================================================
//�҂���
//=============================================================================
void CFindWolfScene::Wait()
{
	m_nFrameCounter++;

	if (m_nFrameCounter < FIND_WOLF_SCENE_PLAYER_WAIT_TIME) return;
	m_nFrameCounter = 0;

	//���̃t�F�[�Y�ɂ���
	m_phase = PHASE::ANSWER;

	if (m_pTutorial == nullptr)
	{
		//����UI�̐���
		m_pTutorial = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
			                            static_cast<CTexture::TEXTURE_TYPE>
			                            (static_cast<int>(CTexture::TEXTURE_TYPE::WOLF_ANSWER_1) + CGameScene::GetWereWolfPlayerIndex() - 1),
			                            SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

//=============================================================================
//�񓚏���
//=============================================================================
void CFindWolfScene::Answer()
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

		//���̃t�F�[�Y�ɂ���
		m_phase = PHASE::TUTORIAL_4;

		//�e�N�X�`����ς���
		m_pTutorial->SetTexType(CTexture::TEXTURE_TYPE::WOLF_FIND_TUTORIAL_4);
	}
}

//=============================================================================
//����4
//=============================================================================
void CFindWolfScene::Tutorial4()
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
		m_pTutorial->Uninit();
		m_pTutorial = nullptr;

		//���̃t�F�[�Y�ɂ���
		m_phase = PHASE::DEC_WOLF_POINT;
	}
}

//=============================================================================
//�l�T�̃|�C���g�}�C�i�X����
//=============================================================================
void CFindWolfScene::DecWolfPoint()
{
}

//=============================================================================
//�l�T�ȊO�̃|�C���g���Z����
//=============================================================================
void CFindWolfScene::AddPlayerPoint()
{
}

//=============================================================================
//�l�T�ȊO�̃|�C���g�}�C�i�X����
//=============================================================================
void CFindWolfScene::DecPlayerPoint()
{
}

//=============================================================================
//�l�T�̃|�C���g���Z����
//=============================================================================
void CFindWolfScene::AddWolfPoint()
{
}

//=============================================================================
//�I��p�A�C�R��UI�̈ʒu�ݒ菈��
//=============================================================================
void CFindWolfScene::SelectIconSetPos(const int nIdxPlayer, const SELECT select)
{
	//�ʒu�ݒ�
	m_pSelectIcon[nIdxPlayer]->SetPos(m_aPosPlayer2D[static_cast<int>(select)]);

	//�ʒu�����������炷
	D3DXVECTOR3 pos = m_pSelectIcon[nIdxPlayer]->GetPos();
	pos += D3DXVECTOR3(-(40.0f * 2.0f) + (40.0f / 2.0f) + (40.0f * nIdxPlayer), -150.0f, 0.0f);
	m_pSelectIcon[nIdxPlayer]->SetPos(pos);
}
