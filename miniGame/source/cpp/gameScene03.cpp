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

#define PLAYER_ICON_SCALE		(0.35f)		//�v���C���[�A�C�R���̃X�P�[��
#define STOP_POS_MIN			(5000.0f)	//�X�g�b�v�ł���Œ�̋���
#define STOP_POS_MAX			(30000.0f)	//�����X�g�b�v����鋗��
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
	m_nCntGameClear = 0;
	memset(m_apPlayer, NULL, sizeof(m_apPlayer[MAX_OBJECT_PLAYER_NUM]));
	memset(m_apPlayerIcon, NULL, sizeof(m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM]));
	m_bReady = false;
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
	m_fDestDist = 100.0f;

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
		pRenderer->SetEffectFogRange(20.0f, 10000.0f);

	}

	//BGM�̍Đ�
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME_02);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME_02);
	}

	//�Q�[���V�[���̏���������
	CGameScene::Init();

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
// �I�u�W�F�N�g��������
//=============================================================================
void CGameScene03::CreateObject(void) {
	//���̐���
	CMeshwall::Create(D3DXVECTOR3(-2000.0f, 0.0f, -0.0f), D3DXVECTOR3(D3DX_PI*0.5f, D3DX_PI*0.5f, 0.0f), 4, 4, 10000.0f, 10000.0f, CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);

	//�v���C���[�̐���
	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		m_apPlayer[nCntPlayer] = CObjplayerStop::Create(D3DXVECTOR3(0.0f, 0.0f, nCntPlayer * -150.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));

		//�X�V���Ȃ��悤�ɂ���
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(false);
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
	//�J�����̎擾
	CCamera* pCamera = pManager->GetCamera();
	if (pCamera == nullptr) return;

	//�|�[�Y
	if (pInput->GetTrigger(CInput::CODE::PAUSE, 0) && !pFade->GetFade() && !m_bLockPauseMenu) {
		//�|�[�Y���j���[�𐶐�
		CreatePauseMenu();
		//�T�E���h���Đ�
		pSound->PlaySound(CSound::SOUND_LABEL::SE_PAUSE_OPEN);
	}

	//�J�����̈ړ�
	float fPosPlayerX = 0.0f;	//�S�v���C���[�̈�ԋ���������ʒu
	for (auto pPlayer : m_apPlayer)
	{
		if (pPlayer == nullptr) continue;
		D3DXVECTOR3 posPlayer = pPlayer->GetPos();	//�v���C���[�̈ʒu���擾

		//��~�\
		if (posPlayer.x > STOP_POS_MIN) pPlayer->SetCanStop(true);
		//������~
		if (posPlayer.x >= STOP_POS_MAX) pPlayer->StopMove();

		//�ő�̈ʒu���擾
		fPosPlayerX = max(fPosPlayerX, posPlayer.x);
	}

	//�J�����̈ʒu�X�V
	D3DXVECTOR3 posCamera = pCamera->GetPos();
	posCamera.x = fPosPlayerX;
	pCamera->SetPos(posCamera);

	//TODO:���C�g�̈ʒu��������

	//���X�ɋ߂Â��� TODO:�J����������Ă��������ɓ����悤�ɂ���
	pCamera->SetDistance(1000.0f);
}

//=============================================================================
// �Q�[���I�[�o�[���̍X�V
//=============================================================================
void CGameScene03::UpdateGameOver(void) {
	m_nCntGameClear++;

	if (m_nCntGameClear > NEXT_SCENE_COUNT)
	{
		m_nCntGameClear = 0;

		CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
		if (pManager == nullptr) return;
		//�t�F�[�h�̎擾
		CFade* pFade = pManager->GetFade();		//�t�F�[�h�ւ̃|�C���^
		if (pFade == nullptr) return;

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

	//�����L���O�ݒ菈��
	//SetRanking();

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

	if (nCntPlayer < 2)
	{
		playerPos.x += 150.0f;
	}
	else
	{
		playerPos.x -= 150.0f;
	}
	playerPos.z -= 100.0f;

	//�A�C�R���̈ʒu
	D3DXVECTOR3 iconPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[���h���W����X�N���[�����W�ɕϊ�
	iconPos = WorldToScreen(playerPos);
	iconPos.z = 0.0f;

	int nTexCount = nCntPlayer;

	if (nCntPlayer >= 2)
	{
		nTexCount += 4;
	}

	//����
	m_apPlayerIcon[nCntPlayer] = CObjectPlayerIcon::Create(iconPos, D3DXVECTOR3(PLAYER_ICON_SCALE, PLAYER_ICON_SCALE, PLAYER_ICON_SCALE),
		CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_ICON_FRAME_1) + nTexCount),
		CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_NUM_WHITE_1) + nCntPlayer));
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