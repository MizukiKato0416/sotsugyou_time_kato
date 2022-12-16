//=============================================================================
//
// �Q�[���V�[��03���� [gameScene03.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "gameScene03.h"

#include "check.h"
#include "count_down_ui.h"
#include "fade.h"
#include "finalResultScene.h"
#include "finish_ui.h"
#include "float_object.h"
#include "gameCamera03.h"
#include "input.h"
#include "manager.h"
#include "meshwall.h"
#include "object2D.h"
#include "objplayer_stop.h"
#include "pauseMenu.h"
#include "player.h"
#include "player_icon.h"
#include "sound.h"
#include "timer.h"
#include "ToScreen.h"

//�G�t�F�N�g
#include "plane.h"
#include "PresetSetEffect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GAME_TIME				(60)		//�Q�[���̎���

#define LIGHT_POS_VIEW_V		(D3DXVECTOR3(2000.0f, 4000.0f, -600.0f))	//���C�g�̎��_�ʒu
#define LIGHT_POS_VIEW_R		(D3DXVECTOR3(0.0f, 0.0f, -600.0f))			//���C�g�̒����_�ʒu

#define FOG_COLOR				(D3DXCOLOR(0.0f, 0.7f, 1.0f, 1.0f))			//�t�H�O�̐F
#define BACK_BUFF_COLOR			(FOG_COLOR)			//�o�b�N�o�b�t�@�[�̐F

#define PLAYER_ICON_SCALE		(0.18f)		//�v���C���[�A�C�R���̃X�P�[��
#define STOP_POS_MIN			(400)		//�X�g�b�v�ł���Œ�̋���
#define STOP_POS_MAX			(999)		//�����X�g�b�v����鋗��
#define FINISH_UI_NUM			(5)			//�t�B�j�b�V��UI�̐�
#define NEXT_SCENE_COUNT		(600)		//���̃V�[���܂ł̃J�E���g

#define MIN_SPEED_PLAYER		(25)		//�v���C���[�̍Œᑬ�x
#define MAX_SPEED_PLAYER		(35)		//�v���C���[�̍ő呬�x

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGameScene03::CGameScene03()
{
	m_nCntGameOver = 0;
	memset(m_apPlayer, NULL, sizeof(m_apPlayer[MAX_OBJECT_PLAYER_NUM]));
	memset(m_apPlayerIcon, NULL, sizeof(m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM]));
	m_bReady = false;

	m_fPosPlayerMin = STOP_POS_MAX;
	m_fPosPlayerMax = 0.0f;

	m_fPlayerSpeedMax = MAX_SPEED_PLAYER;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameScene03::~CGameScene03()
{

}

//=============================================================================
// �Q�[���V�[���̏���������
//=============================================================================
void CGameScene03::Init(void) {
	//�e�N�X�`���̃��[�h
	CTexture::Load("game03");

	//�ϐ�������
	m_bReady = true;
	m_fDestPos = 0.0f;
	m_bEndShowDest = false;
	m_bPerfectScore = false;

	//�J�E���g�_�E�����~����
	m_bStopCountdown = true;

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�����_���[�̎擾
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//�J�����̐ݒ�
	if (pManager != nullptr) pManager->SetCamera(CGameCamera03::Create());

	if (pRenderer != nullptr) {
		//�A�`�斳��
		//pRenderer->SetEnableShadow(false);
	}

	//------------------------------
	//���C�g�̏����ݒ�
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ���C�g�̎ˉe�ϊ�
	//���C�g�̃v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 3500.0f, 7000.0f);

	D3DXMATRIX mtxLightView;   // ���C�g�r���[�ϊ�
	D3DXVECTOR3 posLightV = LIGHT_POS_VIEW_V;	//���C�g�̎��_�̈ʒu
	D3DXVECTOR3 posLightR = LIGHT_POS_VIEW_R;	//���C�g�̒����_�̈ʒu
	D3DXVECTOR3 vecLight = -D3DXVECTOR3(posLightV - posLightR);		//���C�g�̃x�N�g��
	//�x�N�g���𐳋K��
	D3DXVec3Normalize(&vecLight, &vecLight);
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
		pRenderer->SetEffectFogEnable(true);
		//�o�b�N�o�b�t�@���t�H�O�̐F�ɍ��킹��
		pRenderer->SetBackBuffColor(BACK_BUFF_COLOR);
		pRenderer->SetEffectFogColor(FOG_COLOR);
		pRenderer->SetEffectFogRange(2000.0f, 40000.0f);

	}

	//BGM�̍Đ�
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME_02);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME_02);
	}

	//�v���C���[�̍ő呬�x��ݒ�
	m_fPlayerSpeedMax = rand() % (MAX_SPEED_PLAYER - MIN_SPEED_PLAYER + 1) + MIN_SPEED_PLAYER;

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�
	CObject::SetUpdatePauseLevel(0);

	//�Q�[���V�[���̏���������
	CGameScene::Init();
}

//=============================================================================
// �I�u�W�F�N�g��������
//=============================================================================
void CGameScene03::CreateObject(void) {
	//�A�C�R����������
	CreateIcon();
	//�J�E���g�_�E�������s�\
	if (m_pCheck != nullptr) m_pCheck->SetCreateCountDownUi(false);

	//���̐���
	CMeshwall::Create(D3DXVECTOR3(-10000.0f, -5.0f, -0.0f), D3DXVECTOR3(D3DX_PI*0.5f, D3DX_PI*0.5f, 0.0f), 6, 6, 10000.0f, 10000.0f, CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);
	//���H
	CObjectModel::Create(CModel::MODELTYPE::OBJ_ROAD, D3DXVECTOR3(3000.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), false);

	//�J�n�Q�[�g
	CObjectModel::Create(CModel::MODELTYPE::OBJ_STARTGATE, D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//�v���C���[�̐���
		m_apPlayer[nCntPlayer] = CObjplayerStop::Create(D3DXVECTOR3(-300.0f, 0.0f, 500.0f + nCntPlayer * -300.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), m_fPlayerSpeedMax);
		//�X�V���Ȃ��悤�ɂ���
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(false);
	}

	//�Ŕ�
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		CObjectModel::Create((CModel::MODELTYPE)(int(CModel::MODELTYPE::OBJ_MARK_100m) + nCnt), D3DXVECTOR3(GAME03_ONE_METER * 100 * (nCnt + 1), 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	}

	//�r��
	for (int nCnt = 0; nCnt < 200; nCnt++)
	{
		CModel::MODELTYPE type = CModel::MODELTYPE(rand() % 4 + int(CModel::MODELTYPE::OBJ_BUILDING_00));
		CObjectModel::Create(type, D3DXVECTOR3(1000.0f * nCnt, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	}

	//�R�[��
	CObjectModel::Create(CModel::MODELTYPE::OBJ_CORN, D3DXVECTOR3(STOP_POS_MAX * GAME03_ONE_METER + 80.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), false);
}

//=============================================================================
// �Q�[���V�[���̏I������
//=============================================================================
void CGameScene03::Uninit(void) {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�����_���[�̎擾
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();

	if (pRenderer != nullptr) {
		//�A�`��L��
		//pRenderer->SetEnableShadow(true);
	}

	//�ڕW�ʒu�\��UI�̔j��
	if (m_pTomare != nullptr) {
		m_pTomare->Uninit();
		m_pTomare = nullptr;
	}
	if (m_pTomareDist != nullptr) {
		m_pTomareDist->Uninit();
		m_pTomareDist = nullptr;
	}

	//�Q�[���V�[���̏I������
	CGameScene::Uninit();
}

//=============================================================================
// �Q�[���V�[���̍X�V����
//=============================================================================
void CGameScene03::Update(void) {
	//���[�h���I�����Ă��Ȃ�������
	if (!CTexture::GetLoadFinish()) return;

	//�V�[���̍X�V����
	CScene::Update();

#ifdef _DEBUG
	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	//���݂̓��̓f�o�C�X�̎擾
	CInput* pInput = pManager->GetInputKeyboard();
	if (pInput == nullptr) return;

	//�Q�[���I�[�o�[
	if (pInput->GetTrigger(CInput::CODE::DEBUG_1, 0)) {
		GameOver();
	}
#endif


	//�Q�[���I�[�o�[��
	if (m_bGameOver) {
		UpdateGameOver();
	}
	//������Ԏ�
	else if (m_bReady) {
		UpdateReady();
	}
	//�Q�[����
	else
	{
		UpdateGame();
	}

	//�Q�[���V�[���̍X�V����
	CGameScene::Update();
}

//=============================================================================
//������Ԓ��̍X�V
//=============================================================================
void CGameScene03::UpdateReady(void) {
	//�`�F�b�N�o���Ă��Ȃ�������
	if (!m_bAllCheck)
	{
		if (m_pCheck == nullptr)
		{
			return;
		}

		if (!m_pCheck->GetUninitAll())
		{
			return;
		}

		//�S�����`�F�b�N�o������
		for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
		{
			//�v���C���[�A�C�R���̐�������
			CreatePlayerIcon(nCntPlayer);
		}
		//�S�����`�F�b�N�o������Ԃɂ���
		m_bAllCheck = true;

		//�ڕW�ʒu�̌���
		m_fDestPos = (rand() % 45 + 45) * 10.0f * GAME03_ONE_METER;	//450~890m
		m_nCntShowDist = 0;
		//�ڎw��UI�̐���
		m_pTomare = CObject2D::Create(D3DXVECTOR3(900.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::TOMARE, 500.0f, 150.0f);	//�ڎw��UI
		if (m_pTomare != nullptr) {
			m_pTomare->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		//�ڎw��UI�̐����̐���
		m_pTomareDist = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_004, D3DXVECTOR3(900.0f - 250.0f, SCREEN_HEIGHT / 2.0f - 75.0f, 0.0f), 150.0f);
		if (m_pTomareDist != nullptr) {
			m_pTomareDist->SetScore((int)(m_fDestPos / GAME03_ONE_METER));
			m_pTomareDist->SetNumberColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
	else
	{
		if (!m_bEndShowDest) {
			//�ڕW�����̕\��
			ShowDestDist();
		}
		else {
			//�J�E���g�_�E��UI�̏���
			CountDownUi();
		}
	}
}

//=============================================================================
// �Q�[�����̍X�V
//=============================================================================
void CGameScene03::UpdateGame(void) {
	//�|�[�Y���j���[������ꍇ�͍X�V�Ȃ�
	if (m_pMenuPause != nullptr) return;

	//�Q�[���I�����Ă��Ȃ��Ƃ��Ƀ^�C�}�[���O�ɂȂ����ꍇ
	if (m_pTimer != nullptr && !m_bGameOver) {
		if (m_pTimer->GetScore() <= 0) {
			//�Q�[���I��
			GameOver();
			return;
		}
	}

	if (m_pCheck != nullptr)
	{
		//�J�E���g�_�E��UI����������Ă�����
		if (m_pCheck->GetCountDownUi() == nullptr)
		{
			//�`�F�b�N�A�C�R��������
			m_pCheck->Uninit();
			m_pCheck = nullptr;
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//��������Ă��Ȃ�
		if (m_apPlayerIcon[nCntPlayer] == nullptr) continue;
		//UI�������Ă��Ȃ�
		if (m_apPlayerIcon[nCntPlayer]->GetFrame() != nullptr || m_apPlayerIcon[nCntPlayer]->GetPlayerNum() != nullptr) continue;

		//����
		m_apPlayerIcon[nCntPlayer]->Uninit();
		m_apPlayerIcon[nCntPlayer] = nullptr;
	}

	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	//���݂̓��̓f�o�C�X�̎擾
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;
	//�T�E���h�̎擾
	CSound* pSound = pManager->GetSound();
	if (pSound == nullptr) return;
	//�t�F�[�h�̎擾
	CFade* pFade = pManager->GetFade();
	if (pFade == nullptr) return;


	//�|�[�Y
	if (pInput->GetTrigger(CInput::CODE::PAUSE, 0) && !pFade->GetFade() && !m_bLockPauseMenu) {
		//�|�[�Y���j���[�𐶐�
		CreatePauseMenu();
		//�T�E���h���Đ�
		pSound->PlaySound(CSound::SOUND_LABEL::SE_PAUSE_OPEN);
	}

	//�v���C���[�̈ʒu�̊Ď�
	LookPlayerPos();

	//�J�����̍X�V
	UpdateCamera();
	//���C�g�̍X�V
	UpdateLight();
}

//=============================================================================
// �Q�[���I�[�o�[���̍X�V
//=============================================================================
void CGameScene03::UpdateGameOver(void) {
	m_nCntGameOver++;

	//�A�C�R���̈ʒu����
	UpdatePlayerIcon();

	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	//�t�F�[�h�̎擾
	CFade* pFade = pManager->GetFade();		//�t�F�[�h�ւ̃|�C���^
	if (pFade == nullptr) return;
	//�T�E���h�̎擾
	CSound* pSound = pManager->GetSound();
	if (pSound == nullptr) return;
	//�J�����̎擾
	CCamera* pCamera = pManager->GetCamera();
	if (pCamera == nullptr) return;

	CGameCamera03* pCamera03 = dynamic_cast<CGameCamera03*>(pCamera);
	//�J������ڕW�ʒu�܂œ������֐����Ă�
	if (m_nCntGameOver == 90) {
		if (pCamera03 != nullptr) pCamera03->SetDestPos(m_fDestPos, 120);
	}

	//�J�������S�̂����n����悤�ȋ����܂ŉ�����֐����Ă�
	if (m_nCntGameOver == 290)
	{
		if (pCamera03 != nullptr) pCamera03->OverLook(min(m_fPosPlayerMin, m_fDestPos), max(m_fPosPlayerMax, m_fDestPos), 100);
	}

	float afPosUI[MAX_OBJECT_PLAYER_NUM];	//UI�̈ʒu
	for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
	{
		if (m_apPlayer[nCnt] == nullptr) continue;
		const float fSpace = 200.0f;	//UI�̊Ԋu
		afPosUI[nCnt] = SCREEN_WIDTH / 2.0f - fSpace * 2 + fSpace / 2 + nCnt * fSpace;	//��ʐ^�񒆂𒆐S�Ŕz�u

		//�X�R�AUI�̕\��
		if (m_nCntGameOver == 300 + nCnt * 30) {
			int nShowScore = m_apPlayer[nCnt]->GetPos().x / GAME03_ONE_METER;	//�\���X�R�A
			m_bPerfectScore = nShowScore == int(m_fDestPos / GAME03_ONE_METER);	//�X�R�A��v

			//�X�R�A�\��
			CScore* pDistScore = nullptr;	//�X�R�A�̃|�C���^
			//��v�����ǂ����ŉ��o�ύX
			if (m_bPerfectScore) {
				//�X�R�A�̐���
				pDistScore = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_006, D3DXVECTOR3(afPosUI[nCnt] + 3 / 2.0f * 30.0f, 600.0f, 0.0f), 30.0f);
				if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DRUM_ROLL_END);	//TODO:�����ȃX�R�A�̂Ƃ��̉�
			}
			else {
				//�X�R�A�̐���
				pDistScore = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_004, D3DXVECTOR3(afPosUI[nCnt] + 3 / 2.0f * 30.0f, 600.0f, 0.0f), 30.0f);
				if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);	//TODO:�ʏ펞�̉�
			}

			if (pDistScore != nullptr) {
				pDistScore->SetScore(nShowScore);	//�X�R�A�̐ݒ�
			}

			//�X�R�A�̔w�i�̐ݒ�
			CObject2D* pScoreBG = CObject2D::Create(D3DXVECTOR3(afPosUI[nCnt], 600.0f + 30.0f / 2, 0.0f),
				(CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_TYPE::ITEM_UI_FRAME_1 + nCnt), 100.0f, 40.0f);
			if (pScoreBG != nullptr) pScoreBG->SetDrawPriority(CObject::DRAW_PRIORITY::UI_BG);


		}
	}

	//TODO:�X�R�A�̏��Win�e�L�X�g���悹��@�����L���O��ʂ̏ꍇ
	if (m_nCntGameOver == 450) {
		
		for (int nIdx = 0; nIdx < MAX_OBJECT_PLAYER_NUM; nIdx++)
		{
			if (GetRanking(nIdx) != 1) continue;	//�����L���O�P�ʈȊO���O
			//Win�e�L�X�g�̐���
			CObject2D::Create(D3DXVECTOR3(afPosUI[nIdx] + 40.0f, 600.0f + 30.0f / 2 - 20.0f, 0.0f),
				CTexture::TEXTURE_TYPE::WINNER, 100.0f, 40.0f);
		}
		//�T�E���h�Đ�
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);
	}

	//���V�[��
	if (m_nCntGameOver > NEXT_SCENE_COUNT)
	{
		m_nCntGameOver = 0;

		//���U���g�փV�[���J��
		if (GetWereWolfMode()) {
			//�l�T���[�h�̏ꍇ�ȑf�ȃ��U���g
			pFade->SetFade(CScene::SCENE_TYPE::RESULT, 0.02f, 0);
		}
		//�ʏ탂�[�h�̏ꍇ
		else {
			for (int nIdx = 0; nIdx < MAX_OBJECT_PLAYER_NUM; nIdx++)
			{
				int nScore = 40 - (GetRanking(nIdx) - 1) * 10;	//�����L���O���擾���ăX�R�A������
				//���U���g�̃X�R�A��ݒ�
				CFinalResultScene::SetPlayerScore(nScore, nIdx);
			}
			//�ŏI���U���g�ɑJ��
			pFade->SetFade(CScene::SCENE_TYPE::FINAL_RESULT, 0.04f, 0);
		}
	}
	//���C�g�̍X�V
	UpdateLight();
}

//=============================================================================
// �v���C���[�̈ʒu�̊Ď�
//=============================================================================
void CGameScene03::LookPlayerPos(void) {
	//�J�����̈ړ�
	bool bStopPlayerAll = true;	//�S�Ẵv���C���[����~�ς�
	m_fPosPlayerMin = STOP_POS_MAX * GAME03_ONE_METER;
	m_fPosPlayerMax = 0.0f;
	//�S�Ẵv���C���[�̈ʒu���擾
	for (auto pPlayer : m_apPlayer)
	{
		CObjplayerStop* pStopPlayer = dynamic_cast<CObjplayerStop*>(pPlayer);	//���̃Q�[���V�[���Ŏg���v���C���[�̃N���X�Ƀ_�C�i�~�b�N�L���X�g
		if (pStopPlayer == nullptr) continue;

		if (!pStopPlayer->GetStopMove()) bStopPlayerAll = false;

		D3DXVECTOR3 posPlayer = pStopPlayer->GetPos();	//�v���C���[�̈ʒu���擾

		//��~�\
		if (posPlayer.x > STOP_POS_MIN * GAME03_ONE_METER) pStopPlayer->SetCanStop(true);
		//������~
		if (posPlayer.x >= STOP_POS_MAX * GAME03_ONE_METER) {
			//��~
			pStopPlayer->StopMove();
			//�ʒu����
			posPlayer.x = STOP_POS_MAX * GAME03_ONE_METER;
			pStopPlayer->SetPos(posPlayer);
		}

		//�ŏ��̈ʒu���擾
		m_fPosPlayerMin = min(m_fPosPlayerMin, posPlayer.x);
		//�ő�̈ʒu���擾
		m_fPosPlayerMax = max(m_fPosPlayerMax, posPlayer.x);
	}

	//�S�Ẵv���C���[����~���Ă����ꍇ
	if (bStopPlayerAll) {
		//�Q�[���I��
		GameOver();
		return;
	}

}

//=============================================================================
// �J�����̈ʒu�̍X�V
//=============================================================================
void CGameScene03::UpdateCamera(void) {
	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	//�J�����̎擾
	CCamera* pCamera = pManager->GetCamera();
	if (pCamera == nullptr) return;

	//�J�����̈ʒu�X�V
	D3DXVECTOR3 posCamera = pCamera->GetPos();
	if (m_fPosPlayerMax > 300.0f) posCamera.x = m_fPosPlayerMax - 300.0f;
	pCamera->SetPos(posCamera);
}

//=============================================================================
// ���C�g�̈ʒu�̍X�V
//=============================================================================
void CGameScene03::UpdateLight(void) {
	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	//�����_���[�̎擾
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;
	//�J�����̎擾
	CCamera* pCamera = pManager->GetCamera();
	if (pCamera == nullptr) return;

	D3DXMATRIX mtxLightProj;   // ���C�g�̎ˉe�ϊ�
	//���C�g�̃v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 3500.0f, 7000.0f);

	D3DXVECTOR3 posCamera = pCamera->GetPos();
	D3DXMATRIX mtxLightView;   // ���C�g�r���[�ϊ�
	D3DXVECTOR3 posLightV = posCamera + LIGHT_POS_VIEW_V;	//���C�g�̎��_�̈ʒu
	D3DXVECTOR3 posLightR = posCamera + LIGHT_POS_VIEW_R;	//���C�g�̒����_�̈ʒu
	//���C�g�̃r���[�}�g���b�N�X�𐶐�
	D3DXMatrixLookAtLH(&mtxLightView, &posLightV, &posLightR, &D3DXVECTOR3(0, 0, 1));

	//�V�F�[�_�̃��C�g��ݒ�
	pRenderer->SetEffectLightMatrixView(mtxLightView);
	pRenderer->SetEffectLightMatrixProj(mtxLightProj);
}

//=============================================================================
// �Q�[���I�[�o�[
//=============================================================================
void CGameScene03::GameOver(void) {
	if (m_bGameOver) return;

	m_bGameOver = true;

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//�Q�[���I�[�o�[�����Đ�
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_TIME_UP);

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//�X�V���Ȃ��悤�ɂ���
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(false);
	}

	//�t�B�j�b�V��UI����
	CFinishUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 0, 1.0f);
	for (int nCntFinish = 0; nCntFinish < FINISH_UI_NUM; nCntFinish++)
	{
		CFinishUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), nCntFinish + 1, 0.4f);
	}

	//�^�C�}�[���~
	if (m_pTimer != nullptr) {
		m_pTimer->SetStop(true);
	}

	//�����L���O�̌���
	DecideRanking();

	//�ڕW�ʒu�ɖڈ��u��
	CObjectModel::Create(CModel::MODELTYPE::OBJ_STOP_SIGN, D3DXVECTOR3(m_fDestPos, 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//�v���C���[�A�C�R���̐�������
		CreatePlayerIcon(nCntPlayer);
	}

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�i�O�̂��߁j
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
//�v���C���[�A�C�R����������
//=============================================================================
void CGameScene03::CreatePlayerIcon(int nCntPlayer) {

	//��������Ă�����
	if (m_apPlayerIcon[nCntPlayer] != nullptr)
	{
		return;
	}

	//�v���C���[�̈ʒu�擾
	D3DXVECTOR3 playerPos = m_apPlayer[nCntPlayer]->GetPos();
	//playerPos.x -= 100.0f;
	//playerPos.y -= 10.0f;

	//�A�C�R���̈ʒu
	D3DXVECTOR3 iconPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[���h���W����X�N���[�����W�ɕϊ�
	iconPos = WorldToScreen(playerPos);
	iconPos.x -= 70.0f;
	iconPos.z = 0.0f;

	//����
	m_apPlayerIcon[nCntPlayer] = CObjectPlayerIcon::Create(iconPos, D3DXVECTOR3(PLAYER_ICON_SCALE, PLAYER_ICON_SCALE, PLAYER_ICON_SCALE),
		CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_ICON_FRAME_1) + nCntPlayer + 4),
		CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_NUM_WHITE_1) + nCntPlayer));
}

//=============================================================================
// �v���C���[�A�C�R���X�V����
//=============================================================================
void CGameScene03::UpdatePlayerIcon(void) {
	for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
	{
		if (m_apPlayerIcon[nCnt] == nullptr) continue;

		//�v���C���[�̈ʒu�擾
		D3DXVECTOR3 playerPos = m_apPlayer[nCnt]->GetPos();
		//playerPos.y += 300.0f;

		//�A�C�R���̈ʒu
		D3DXVECTOR3 iconPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//���[���h���W����X�N���[�����W�ɕϊ�
		iconPos = WorldToScreen(playerPos);
		iconPos.y -= 30.0f;
		iconPos.z = 0.0f;

		m_apPlayerIcon[nCnt]->SetPos(iconPos);
	}
}

//=============================================================================
// �ڕW�ʒu�\��
//=============================================================================
void CGameScene03::ShowDestDist(void) {
	if (m_pTomare == nullptr || m_pTomareDist == nullptr) return;

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	m_nCntShowDist++;

	//UI�\��
	if (m_nCntShowDist == 60) {
		m_pTomare->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pTomareDist->SetNumberColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//�T�E���h���Đ�
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);
	}

	D3DXCOLOR colUI;	//UI�̐F
	//�F�������Ă���
	if (m_nCntShowDist > 180) {
		//�����x��������
		colUI = m_pTomare->GetColor();
		colUI.a -= 0.05f;
		//�F�̕ύX
		m_pTomare->SetColor(colUI);
		m_pTomareDist->SetNumberColor(colUI);
	}

	//�ڕW�ʒu�\���̏I��
	if (colUI.a <= 0.0f && m_nCntShowDist > 180) {
		m_bEndShowDest = true;
		//�ڕW�ʒu�\��UI�̔j��
		m_pTomare->Uninit();
		m_pTomare = nullptr;
		m_pTomareDist->Uninit();
		m_pTomareDist = nullptr;

		//�ڕW�ʒu�̔w�i�̐���
		CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 50.0f, 0.0f),
			CTexture::TEXTURE_TYPE::FRAME_DEST, 280.0f, 80.0f);
		//��ʏ㕔�ɖڕW�ʒu��UI�𐶐�
		CScore* pDistScore = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_004, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 150.0f / 2.0f + 15.0f, 30.0f, 0.0f), 50.0f);
		if (pDistScore != nullptr) pDistScore->SetScore((int)(m_fDestPos / GAME03_ONE_METER));
		//�J�E���g�_�E�������\
		if (m_pCheck != nullptr) m_pCheck->SetCreateCountDownUi(true);
	}
}

//=============================================================================
// �J�E���g�_�E��UI�̏���
//=============================================================================
void CGameScene03::CountDownUi(void)
{
	if (m_pCheck == nullptr) return;
	if (m_pCheck->GetCountDownUi() == nullptr) return;
	
	//�X�^�[�g��Ԃł͂Ȃ��ꍇ�I��
	if (!m_pCheck->GetCountDownUi()->GetStart()) return;

	//������ԂȂ�
	if (m_bReady)
	{
		//������Ԃ��I������
		m_bReady = false;
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//��������Ă�����
		if (m_apPlayer[nCntPlayer] == nullptr)
		{
			continue;
		}

		//�X�V����Ă����ԂȂ�
		if (m_apPlayer[nCntPlayer]->GetPlayer()->GetUpdate())
		{
			continue;
		}

		//�X�V����Ă����Ԃɂ���
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(true);

		//��������Ă�����
		if (m_apPlayerIcon[nCntPlayer] != nullptr)
		{
			//������悤�ɐݒ肷��
			m_apPlayerIcon[nCntPlayer]->SetState(CObjectPlayerIcon::STATE::DEC_ALPHA);
		}
	}
}

//=============================================================================
// �v���C���[�̈ʒu���烉���L���O�����肵�ăV�[���̃����L���O�ɐݒ肷��
//=============================================================================
void CGameScene03::DecideRanking(void) {
	std::vector<float> distPlayer(MAX_OBJECT_PLAYER_NUM);	//�v���C���[�̐i�񂾋���
	std::vector<float> sortPlayer(MAX_OBJECT_PLAYER_NUM);	//�v���C���[�̐i�񂾋����̃\�[�g

	//�S�Ẵv���C���[�̈ʒu���擾
	for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
	{
		CObjplayerStop* pStopPlayer = dynamic_cast<CObjplayerStop*>(m_apPlayer[nCnt]);	//���̃Q�[���V�[���Ŏg���v���C���[�̃N���X�Ƀ_�C�i�~�b�N�L���X�g
		if (pStopPlayer == nullptr) continue;

		D3DXVECTOR3 posPlayer = pStopPlayer->GetPos();	//�v���C���[�̈ʒu���擾
		sortPlayer[nCnt] = distPlayer[nCnt] = fabs(posPlayer.x - m_fDestPos);	//�v���C���[�ƖڕW�̈ʒu�̍������擾
	}

	//�����Ƀ\�[�g
	std::sort(sortPlayer.begin(), sortPlayer.end());

	//�����L���O��ݒ�
	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		for (int nCntSort = 0; nCntSort < MAX_OBJECT_PLAYER_NUM; nCntSort++)
		{
			if (distPlayer[nCntPlayer] == sortPlayer[nCntSort]) {
				int nRank = nCntSort + 1;
				//�����L���O�ݒ�
				SetRanking(nRank, nCntPlayer);
				break;
			}
		}
	}
}