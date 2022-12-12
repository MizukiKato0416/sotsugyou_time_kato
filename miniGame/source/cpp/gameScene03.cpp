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

#define FOG_COLOR				(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		//�t�H�O�̐F
#define BACK_BUFF_COLOR			(D3DXCOLOR(0.1f, 0.3f, 0.5f, 1.0f))		//�o�b�N�o�b�t�@�[�̐F

#define PLAYER_ICON_SCALE		(0.18f)		//�v���C���[�A�C�R���̃X�P�[��
#define STOP_POS_MIN			(4000.0f)	//�X�g�b�v�ł���Œ�̋���
#define STOP_POS_MAX			(10000.0f)	//�����X�g�b�v����鋗��	10.0f��1m
#define FINISH_UI_NUM			(5)			//�t�B�j�b�V��UI�̐�
#define NEXT_SCENE_COUNT		(240)		//���̃V�[���܂ł̃J�E���g

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
	CTexture::Load("game01");

	//�ϐ�������
	m_bReady = true;
	m_fDestPos = 100.0f;

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

	//------------------------------
	//���C�g�̏����ݒ�
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ���C�g�̎ˉe�ϊ�
	//���C�g�̃v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 1500.0f, 3000.0f);

	D3DXMATRIX mtxLightView;   // ���C�g�r���[�ϊ�
	D3DXVECTOR3 posLightV = D3DXVECTOR3(800.0f, 2000.0f, -800.0f);	//���C�g�̎��_�̈ʒu
	D3DXVECTOR3 posLightR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���C�g�̒����_�̈ʒu
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

		//�t�H�O�̐F
		D3DXCOLOR fogColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		//�o�b�N�o�b�t�@�[�̐F
		D3DXCOLOR backBuffColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		//�o�b�N�o�b�t�@���t�H�O�̐F�ɍ��킹��
		pRenderer->SetBackBuffColor(backBuffColor);
		pRenderer->SetEffectFogColor(fogColor);
		pRenderer->SetEffectFogRange(3000.0f, 50000.0f);

	}

	//BGM�̍Đ�
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME_02);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME_02);
	}

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

	//���̐���
	CMeshwall::Create(D3DXVECTOR3(-2000.0f, 0.0f, -0.0f), D3DXVECTOR3(D3DX_PI*0.5f, D3DX_PI*0.5f, 0.0f), 4, 4, 10000.0f, 10000.0f, CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);

	//�v���C���[�̐���
	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		m_apPlayer[nCntPlayer] = CObjplayerStop::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f + nCntPlayer * -300.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));

		//�X�V���Ȃ��悤�ɂ���
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(false);
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		CObjectModel::Create(CModel::MODELTYPE::OBJ_BALLOON_PINK, D3DXVECTOR3(1000.0f * nCnt, 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	}
}

//=============================================================================
// �Q�[���V�[���̏I������
//=============================================================================
void CGameScene03::Uninit(void) {

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
}

//=============================================================================
// �v���C���[�̈ʒu�̊Ď�
//=============================================================================
void CGameScene03::LookPlayerPos(void) {
	//�J�����̈ړ�
	bool bStopPlayerAll = true;	//�S�Ẵv���C���[����~�ς�
	m_fPosPlayerMin = STOP_POS_MAX;
	m_fPosPlayerMax = 0.0f;
	//�S�Ẵv���C���[�̈ʒu���擾
	for (auto pPlayer : m_apPlayer)
	{
		if (pPlayer == nullptr) continue;

		if (!pPlayer->GetStopMove()) bStopPlayerAll = false;

		D3DXVECTOR3 posPlayer = pPlayer->GetPos();	//�v���C���[�̈ʒu���擾

		//��~�\
		if (posPlayer.x > STOP_POS_MIN) pPlayer->SetCanStop(true);
		//������~
		if (posPlayer.x >= STOP_POS_MAX) pPlayer->StopMove();

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

	//TODO:���C�g�̈ʒu��������
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

	//�t�F�[�h�����
	if (m_nCntGameOver == 10)
	{
		//pFade->SetFade((CScene::SCENE_TYPE)-1, 0.02f, 0);
	}

	//�X�R�AUI�̕\��
	for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
	{
		//�����^�C�~���O
		if (m_nCntGameOver == 120 + nCnt * 30 && m_apPlayer[nCnt] != nullptr) {
			float fSpace = 200.0f;
			float fPosX = SCREEN_WIDTH / 2.0f - fSpace * 2 + fSpace / 2 + nCnt * fSpace;	//�v���C���[�̃��f���̈ʒu���X�N���[�����W�ɕϊ����Ă����W���擾
			//�X�R�A�̐���
			CScore* pDist = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_004, D3DXVECTOR3(fPosX + 3 / 2.0f * 30.0f, 600.0f, 0.0f), 30.0f);
			if (pDist != nullptr) pDist->SetScore(m_apPlayer[nCnt]->GetPos().x / 10.0f);

			//�X�R�A�̔w�i�̐ݒ�
			CObject2D* pScoreBG = CObject2D::Create(D3DXVECTOR3(fPosX, 600.0f + 30.0f / 2, 0.0f),
				(CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_TYPE::ITEM_UI_FRAME_1 + nCnt), 100.0f, 40.0f);
			if (pScoreBG != nullptr) pScoreBG->SetDrawPriority(CObject::DRAW_PRIORITY::UI_BG);

			//���̍Đ�
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);
		}
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
	}
	//�ڕW�ʒu���肵�Ă��Ȃ��ꍇ
	else if (!m_bDecideDestDist) {
		//�ڕW�ʒu�̌���
		if (true) {
			m_bDecideDestDist = true;
			m_fDestPos = (rand() % 46 + 40) * 100.0f;	//4500.0f ~ 8500.0f
			CScore* pDist = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_003, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 50.0f, 0.0f), 50.0f);
			if (pDist != nullptr) pDist->SetScore((int)(m_fDestPos / 10.0f));
		}
	}
	else
	{
		if (m_pCheck == nullptr)
		{
			return;
		}

		if (m_pCheck->GetCountDownUi() == nullptr)
		{
			return;
		}

		//�J�E���g�_�E��UI����������Ă�����
		//�J�E���g�_�E��UI�̏���
		CountDownUi();
	}
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
	//�J�����̎擾
	CCamera* pCamera = nullptr;
	if (pManager != nullptr) pCamera = pManager->GetCamera();

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

	//TODO:�����L���O�ݒ菈��
	//SetRanking();

	//�J�������S�̂����n����悤�ȋ����܂ŉ�����֐����Ă�
	CGameCamera03* pCamera03 = dynamic_cast<CGameCamera03*>(pCamera);
	if (pCamera03 != nullptr) pCamera03->OverLook(m_fPosPlayerMin, m_fPosPlayerMax);

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
	playerPos.x -= 100.0f;
	playerPos.y -= 10.0f;

	//�A�C�R���̈ʒu
	D3DXVECTOR3 iconPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[���h���W����X�N���[�����W�ɕϊ�
	iconPos = WorldToScreen(playerPos);
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
		playerPos.x -= 300.0f;
		playerPos.z -= 100.0f;

		//�A�C�R���̈ʒu
		D3DXVECTOR3 iconPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//���[���h���W����X�N���[�����W�ɕϊ�
		iconPos = WorldToScreen(playerPos);
		iconPos.z = 0.0f;

		m_apPlayerIcon[nCnt]->SetPos(iconPos);
	}
}

//=============================================================================
//�J�E���g�_�E��UI�̏���
//=============================================================================
void CGameScene03::CountDownUi(void)
{
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