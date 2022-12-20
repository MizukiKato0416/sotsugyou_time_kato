//=============================================================================
//
// �Q�[���V�[��02���� [gameScene02.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "gameScene02.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "gameCamera.h"
#include "fade.h"
#include "timer.h"
#include "object2D.h"
#include "object_player_attack_car.h"
#include "pauseMenu.h"
#include "count_down_ui.h"
#include "finish_ui.h"
#include "player.h"
#include "create_bom_manager.h"
#include "meshwall.h"
#include "float_object.h"
#include "player_icon.h"
#include "ToScreen.h"
#include "check.h"
#include "item_shield.h"
#include "finalResultScene.h"


//�G�t�F�N�g
#include "plane.h"
#include "PresetSetEffect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GAME_02_TIME							(60)								//�Q�[���̎���
#define GAME_02_HURRY_UP_TIME					(20)								//�n���[�A�b�v�̎���

#define GAME_02_FOG_COLOR_SUNNY					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	//�t�H�O�̐F����
#define GAME_02_FOG_COLOR_CLOUDY				(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))	//�t�H�O�̐F�܂�
#define GAME_02_BACK_BUFF_COLOR_SUNNY			(D3DXCOLOR(0.1f, 0.3f, 0.5f, 1.0f))	//�o�b�N�o�b�t�@�[�̐F����
#define GAME_02_BACK_BUFF_COLOR_CLOUDY			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))	//�o�b�N�o�b�t�@�[�̐F�܂�

#define GAME_02_PLAYER_ICON_SCALE				(0.35f)								//�v���C���[�A�C�R���̃X�P�[��

#define GAME_02_PLAYER_INIT_CREATE_SPACE		(300.0f)							//�v���C���[�̏��������Ԋu
#define GAME_02_PLAYER_INIT_CREATE_POS_Z		(-400.0f)							//�v���C���[�̏��������ʒuZ

#define GAME_02_FINISH_UI_NUM		(5)			//�t�B�j�b�V��UI�̐�

#define GAME_02_NEX_SCENE_COUNT		(240)		//���̃V�[���܂ł̃J�E���g

#define GAME_02_BOM_CREATE_COUNT	(30)		//�{���𐶐�����Ԋu
#define GAME_02_BOM_NUM				(1)			//�{���𐶐������

#define GAME_02_CLOUD_NUM					(1)											//�_�̐�
#define GAME_02_CLOUD_POS					(D3DXVECTOR3(0.0f, -1500.0f, -6000.0f))		//�_�̈ʒu
#define GAME_02_CLOUD_SIZE					(12000.0f)									//�_�̃T�C�Y
#define GAME_02_CLOUD_MESH_NUM				(8)											//���b�V����~���l�߂鐔
#define GAME_02_CLOUD_MOVE_SPEED			(0.00035f)									//�e�N�X�`���𓮂�������
#define GAME_02_CLOUD_MOVE_SPEED_INTERVAL	(0.00025f)									//���̉_�̃e�N�X�`���𓮂��������̊Ԋu
#define GAME_02_CLOUD_COLOR					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			//�_�̐F

#define GAME_02_ITEM_SPAWN_COUNT			(60 * 6)						//�A�C�e���̐����Ԋu
#define GAME_02_ITEM_SPAWN_DIFFER_MAX		(GAME_02_STAGE_SIZE - 100.0f)	//�X�e�[�W��������ǂꂾ�����ꂽ�ʒu�ɃA�C�e���𐶐����邩�ő�l
#define GAME_02_ITEM_SPAWN_POS_Y			(1000.0f)						//�A�C�e���̐����ʒuY


//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGameScene02::CGameScene02()
{
	m_nCntGameClear = 0;
	memset(m_apPlayer, NULL, sizeof(m_apPlayer[MAX_OBJECT_PLAYER_NUM]));
	memset(m_apPlayerIcon, NULL, sizeof(m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM]));
	m_bHurryUp = false;
	m_bReady = false;
	m_pCreateBomManager = nullptr;
	m_pCloud.clear();
	m_weatherState = WEATHER_STATE::CLOUDY;
	m_nSavePlayerNum = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameScene02::~CGameScene02()
{

}

//=============================================================================
// �Q�[���V�[���̏���������
//=============================================================================
void CGameScene02::Init(void) {
	//�e�N�X�`���̃��[�h
	CTexture::Load("game02");

	//�ϐ�������
	m_bHurryUp = false;
	m_pCreateBomManager = nullptr;
	m_weatherState = WEATHER_STATE::CLOUDY;
	m_bReady = true;
	m_nSavePlayerNum = MAX_OBJECT_PLAYER_NUM;

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�����_���[�̎擾
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//�J�����̐ݒ�
	if (pManager != nullptr) pManager->SetCamera(CGameCamera::Create());

	//------------------------------
	//���C�g�̏����ݒ�
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ���C�g�̎ˉe�ϊ�
	//���C�g�̃v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 1500.0f, 3000.0f);

	D3DXMATRIX mtxLightView;   // ���C�g�r���[�ϊ�
	D3DXVECTOR3 posLightV = D3DXVECTOR3(800.0f, 2000.0f, -800.0f);	//���C�g�̎��_�̈ʒu	D3DXVECTOR3(600.0f, 1500.0f, -2000.0f);
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
		pRenderer->SetEffectFogEnable(true);

		//�t�H�O�̐F
		D3DXCOLOR fogColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		//�o�b�N�o�b�t�@�[�̐F
		D3DXCOLOR backBuffColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		//�����_���ŏ�Ԃ��w��
		m_weatherState = WEATHER_STATE(rand() % (int)WEATHER_STATE::MAX);

		switch (m_weatherState)
		{
		case CGameScene02::WEATHER_STATE::CLOUDY:
			fogColor = GAME_02_FOG_COLOR_CLOUDY;
			backBuffColor = GAME_02_BACK_BUFF_COLOR_CLOUDY;
			break;
		case CGameScene02::WEATHER_STATE::SUNNY:
			fogColor = GAME_02_FOG_COLOR_SUNNY;
			backBuffColor = GAME_02_BACK_BUFF_COLOR_SUNNY;
			break;
		default:
			break;
		}

		//�o�b�N�o�b�t�@���t�H�O�̐F�ɍ��킹��
		pRenderer->SetBackBuffColor(backBuffColor);
		pRenderer->SetEffectFogColor(fogColor);
		pRenderer->SetEffectFogRange(20.0f, 10000.0f);
		
	}

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�
	CObject::SetUpdatePauseLevel(0);

	
	
	//BGM�̍Đ�
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME_02);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME_02);
	}

	//�Q�[���V�[���̏���������
	CGameScene::Init();
}

//=============================================================================
//�I�u�W�F�N�g��������
//=============================================================================
void CGameScene02::CreateObject(void)
{
	//�A�C�R����������
	CreateIcon();

	//�X�^�W�A���̐���
	CObjectModel::Create(CModel::MODELTYPE::OBJ_ATTACK_CAR_STAGE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//��̐���
	CFloatObject::Create(D3DXVECTOR3(1800.0f, -200.0f, 1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(-0.001f, -0.003f, 0.002f), CModel::MODELTYPE::OBJ_BROKEN_GATE);

	//���̐���
	CFloatObject::Create(D3DXVECTOR3(-1900.0f, -700.0f, 2500.0f), D3DXVECTOR3(-0.3f, 0.0f, -0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0f, 0.004f, 0.0f), CModel::MODELTYPE::OBJ_BROKEN_TOWER);

	//�Ԃ̐���
	CFloatObject::Create(D3DXVECTOR3(-1900.0f, -500.0f, 2500.0f), D3DXVECTOR3(0.1f, 0.0f, -0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0030f, -0.004f, 0.0f), CModel::MODELTYPE::OBJ_CAR);

	CFloatObject::Create(D3DXVECTOR3(1300.0f, -800.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.001f, -0.001f, 0.0014f), CModel::MODELTYPE::OBJ_CAR);

	//���ꂫ�̐���
	//���̂��ꂫ
	CFloatObject::Create(D3DXVECTOR3(-1000.0f, -500.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.001f, -0.002f, 0.005f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_02);

	CFloatObject::Create(D3DXVECTOR3(-300.0f, -500.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0f, 0.001f, -0.003f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_03);

	CFloatObject::Create(D3DXVECTOR3(300.0f, -500.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0005f, 0.002f, 0.009f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_04);

	CFloatObject::Create(D3DXVECTOR3(1000.0f, -500.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(-0.0005f, -0.001f, -0.001f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_05);

	CFloatObject::Create(D3DXVECTOR3(1500.0f, -500.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0025f, 0.0f, 0.001f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_06);

	//��O�̂��ꂫ
	CFloatObject::Create(D3DXVECTOR3(-1000.0f, -800.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0005f, -0.001f, 0.0f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_01);

	CFloatObject::Create(D3DXVECTOR3(1000.0f, -800.0f, -300.0f), D3DXVECTOR3(1.0f, -0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(-0.0001f, 0.0008f, 0.0f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_06); 

	CFloatObject::Create(D3DXVECTOR3(1200.0f, -500.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 1.2f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(-0.0008f, 0.0008f, 0.0f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_03);

	CFloatObject::Create(D3DXVECTOR3(-1400.0f, -500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.3f, -1.2f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0016f, -0.0005f, -0.001f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_05);

	//�_�̐���
	for (int nCntCloud = 0; nCntCloud < GAME_02_CLOUD_NUM; nCntCloud++)
	{
		m_pCloud.push_back(CMeshwall::Create(GAME_02_CLOUD_POS, D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f),
			                                 GAME_02_CLOUD_MESH_NUM, GAME_02_CLOUD_MESH_NUM, GAME_02_CLOUD_SIZE, GAME_02_CLOUD_SIZE,
			                                 CTexture::TEXTURE_TYPE::MESH_CLOUD));
		//���Z����������
		m_pCloud[nCntCloud]->SetAlphaBlend(true);
		//�`�揇�̐ݒ�
		m_pCloud[nCntCloud]->SetDrawPriority(CObject::DRAW_PRIORITY::CLEAR);
		//���C�g���I�t�ɂ���
		m_pCloud[nCntCloud]->SetLight(false);
		//�F�̐ݒ�
		m_pCloud[nCntCloud]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	}

	//�v���C���[�̐���
	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, D3DX_PI / 2.0f * nCntPlayer + D3DX_PI / 4.0f, 0.0f);

		if (rot.y > D3DX_PI)
		{
			rot.y -= D3DX_PI * 2.0f;
		}
		else if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2.0f;
		}

		m_apPlayer[nCntPlayer] = CObjectPlayerAttackCar::Create(D3DXVECTOR3(sinf(D3DX_PI / 2.0f * nCntPlayer + D3DX_PI / 4.0f) * 500.0f,
			                                                                0.0f, 
			                                                                cosf(D3DX_PI / 2.0f * nCntPlayer + D3DX_PI / 4.0f) * 500.0f), rot);
		//�V�[���̃v���C���[�̐ݒ�
		SetPlayer(m_apPlayer[nCntPlayer]);

		//�X�V���Ȃ��悤�ɂ���
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(false);
	}
}

//=============================================================================
// �Q�[���V�[���̏I������
//=============================================================================
void CGameScene02::Uninit(void) {

	//�Q�[���V�[���̏I������
	CGameScene::Uninit();
}

//=============================================================================
// �Q�[���V�[���̍X�V����
//=============================================================================
void CGameScene02::Update(void) {
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

	//�^�C���ǉ�
	if (pInput->GetTrigger(CInput::CODE::DEBUG_3, 0)) {
		if (m_pTimer != nullptr) m_pTimer->AddScore(50);
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

	//�_�̏���
	Cloud();

	//�Q�[���V�[���̍X�V����
	CGameScene::Update();
}

//=============================================================================
// �Q�[�����̍X�V
//=============================================================================
void CGameScene02::UpdateGame(void) {
	//�|�[�Y���j���[������ꍇ�͍X�V�Ȃ�
	if (m_pMenuPause != nullptr) return;

	//�I�����邩�m�F����
	if (Finish())
	{
		return;
	}

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
		//��������Ă�����
		if (m_apPlayerIcon[nCntPlayer] != nullptr)
		{
			//UI�������Ă�����
			if (m_apPlayerIcon[nCntPlayer]->GetFrame() == nullptr && m_apPlayerIcon[nCntPlayer]->GetPlayerNum() == nullptr)
			{
				//����
				m_apPlayerIcon[nCntPlayer]->Uninit();
				m_apPlayerIcon[nCntPlayer] = nullptr;
			}
		}
	}

	//�^�C�}�[����������Ă�����
	if (m_pTimer != nullptr)
	{
		if (m_pTimer->GetScore() == GAME_02_HURRY_UP_TIME)
		{
			//�}����ԂłȂ��Ȃ�
			if (!m_bHurryUp)
			{
				//�}����Ԃɂ���
				m_bHurryUp = true;
				//�}������
				HurryUp();
			}
		}
	}

	//�A�C�e���̐���
	CreateItem();

	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	//���݂̓��̓f�o�C�X�̎擾
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;
	//�T�E���h�̎擾
	CSound* pSound = pManager->GetSound();	//�T�E���h�ւ̃|�C���^
	if (pSound == nullptr) return;
	//�t�F�[�h�̎擾
	CFade* pFade = pManager->GetFade();	//�t�F�[�h�̃|�C���^
	if (pFade == nullptr) return;

	//�|�[�Y
	if (pInput->GetTrigger(CInput::CODE::PAUSE, 0) && !pFade->GetFade() && !m_bLockPauseMenu) {
		//�|�[�Y���j���[�𐶐�
		CreatePauseMenu();
		//�T�E���h���Đ�
		pSound->PlaySound(CSound::SOUND_LABEL::SE_PAUSE_OPEN);
	}
}

//=============================================================================
// �Q�[���I�[�o�[���̍X�V
//=============================================================================
void CGameScene02::UpdateGameOver(void) {
	m_nCntGameClear++;

	if (m_nCntGameClear > GAME_02_NEX_SCENE_COUNT)
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
			pFade->SetFade(CScene::SCENE_TYPE::RESULT, 40, 0);
		}
		//�ʏ탂�[�h�̏ꍇ
		else {
			for (int nIdx = 0; nIdx < MAX_OBJECT_PLAYER_NUM; nIdx++)
			{
				int nScore = 40 - (GetRanking(nIdx) - 1)*10;	//�����L���O���擾���ăX�R�A������
				//���U���g�̃X�R�A��ݒ�
				CFinalResultScene::SetPlayerScore(nScore, nIdx);
			}
			//�ŏI���U���g�ɑJ��
			pFade->SetFade(CScene::SCENE_TYPE::FINAL_RESULT, 40, 0);
		}
	}
}

//=============================================================================
//������Ԓ��̍X�V
//=============================================================================
void CGameScene02::UpdateReady(void) {
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
void CGameScene02::GameOver(void) {
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
	for (int nCntFinish = 0; nCntFinish < GAME_02_FINISH_UI_NUM; nCntFinish++)
	{
		CFinishUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), nCntFinish + 1, 0.4f);
	}

	//�^�C�}�[���~
	if (m_pTimer != nullptr) {
		m_pTimer->SetStop(true);
	}

	//�{��������
	if (m_pCreateBomManager != nullptr)
	{
		m_pCreateBomManager->Uninit();
		m_pCreateBomManager = nullptr;
	}

	//�����L���O�ݒ菈��
	SetRanking();

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�i�O�̂��߁j
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
//�v���C���[�A�C�R����������
//=============================================================================
void CGameScene02::CreatePlayerIcon(int nCntPlayer){

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
	m_apPlayerIcon[nCntPlayer] = CObjectPlayerIcon::Create(iconPos, D3DXVECTOR3(GAME_02_PLAYER_ICON_SCALE, GAME_02_PLAYER_ICON_SCALE, GAME_02_PLAYER_ICON_SCALE),
		                                                   CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_ICON_FRAME_1) + nTexCount),
													       CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_NUM_WHITE_1) + nCntPlayer));
}

//=============================================================================
//�J�E���g�_�E��UI�̏���
//=============================================================================
void CGameScene02::CountDownUi(void)
{
	//�X�^�[�g��ԂȂ�
	if (m_pCheck->GetCountDownUi()->GetStart())
	{
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

		//��������Ă��Ȃ�������
		if (m_pTimerFrame == nullptr)
		{
			//�^�C�}�[�̐���
			m_pTimerFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 61.0f, 0.0f), CTexture::TEXTURE_TYPE::TIMER_FRAME, 220.0f, 80.0f);
			m_pTimer = CTimer::Create(GAME_02_TIME, 2, CTexture::TEXTURE_TYPE::NUMBER_003, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 75.0f, 40.0f, 0.0f), 50.0f);
		}
	}
}

//=============================================================================
//�t�B�j�b�V�����邩�m�F����
//=============================================================================
bool CGameScene02::Finish(void)
{
	//�Q�[���I�[�o�[��ԂȂ�
	if (m_bGameOver)
	{
		return false;
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//��������ĂȂ�������
		if (m_apPlayer[nCntPlayer] == nullptr)
		{
			continue;
		}

		//�����c���Ă���l��2�l�ȏア����
		if (GetSavePlayerNum() > 1)
		{
			continue;
		}

		//�Q�[���I��
		GameOver();
	}
	return false;
}

//=============================================================================
//�}������
//=============================================================================
void CGameScene02::HurryUp(void)
{
	//�{����������
	if (m_pCreateBomManager == nullptr)
	{
		m_pCreateBomManager = CCreateBomManager::Create(GAME_02_BOM_CREATE_COUNT, GAME_02_BOM_NUM);
	}
}

//=============================================================================
//�_�̏���
//=============================================================================
void CGameScene02::Cloud(void)
{
	for (int nCntCloud = 0; nCntCloud < GAME_02_CLOUD_NUM; nCntCloud++)
	{
		if (m_pCloud[nCntCloud] == nullptr)
		{
			continue;
		}

		//�e�N�X�`�����W�ړ�����
		m_pCloud[nCntCloud]->SetMoveTex(GAME_02_CLOUD_MOVE_SPEED + GAME_02_CLOUD_MOVE_SPEED_INTERVAL * nCntCloud, 0.0f);
	}
}

//=============================================================================
//�A�C�e����������
//=============================================================================
void CGameScene02::CreateItem()
{
	m_nItemCounter++;

	if (m_nItemCounter > GAME_02_ITEM_SPAWN_COUNT)
	{
		m_nItemCounter = 0;

		//�����������_���Ō��߂�
		float fRot = (rand() % 629 + -314) / 100.0f;
		//�����������_���Ō��߂�
		float fDiffer = (rand() % (int)(GAME_02_ITEM_SPAWN_DIFFER_MAX) * 100.0f) / 100.0f;

		//�o���ʒu
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, GAME_02_ITEM_SPAWN_POS_Y, 0.0f);

		//���߂��ʒu�ɏo��
		pos.x = sinf(fRot) * fDiffer;
		pos.z = cosf(fRot) * fDiffer;

		//�A�C�e���̐���
		CItemShield::Create(pos);
	}
}

//=============================================================================
//�����L���O�ݒ菈��
//=============================================================================
void CGameScene02::SetRanking()
{
	for (int nCntSavePlayer = 0; nCntSavePlayer < MAX_OBJECT_PLAYER_NUM; nCntSavePlayer++)
	{
		//�c�����l�������L���O1�ʂɂ���
		if (GetRanking(nCntSavePlayer) != 0)
		{
			continue;
		}

		//�����L���O�ݒ菈��
		CGameScene::SetRanking(1, nCntSavePlayer);
	}
}
