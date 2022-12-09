//=============================================================================
//
// �Q�[���V�[��01���� [gameScene01.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include <functional>		//��r�p
#include "gameScene01.h"
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
#include "float_object.h"
#include "score.h"
#include "score_ui.h"
#include "finalResultScene.h"

//�G�t�F�N�g
#include "plane.h"
#include "PresetSetEffect.h"

#include "player_icon.h"
#include "ToScreen.h"
#include "check.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GAME_TIME								 (60)									//�Q�[���̎���
#define GAME_CREATE_ITEMBOX_TIME				 (60)									//�A�C�e���𐶐����n�߂鎞��	

#define FOG_COLOR								 (D3DXCOLOR(0.1f, 0.0f, 0.2f, 1.0f))	//�t�H�O�̐F
#define FOG_COLOR_GAMECLEAR					     (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	//�t�H�O�̐F

#define GAME_STAGE_SIZE							 (700.0f)								//���ā[���̑傫��
#define GAME_PLAYER_ICON_SCALE					 (0.35f)								//�v���C���[�A�C�R���̃X�P�[��

#define GAME_PLAYER_INIT_CREATE_SPACE			 (300.0f)								//�v���C���[�̏��������Ԋu
#define GAME_PLAYER_INIT_CREATE_POS_Z			 (-400.0f)								//�v���C���[�̏��������ʒuZ

#define GAME_BALLOON_CREATE_POS_Y				 (15.0f)								//���D�̈ʒuY
#define GAME_BALLOON_CREATE_DIFFER				 (600.0f)								//���D�̐�������͈͂̔��a
#define GAME_BALLOON_CREATE_DIFFER_WERE_WOLF_MAX (350.0f)								//���D�̐�������R���v���C���[����͈̔͂̔��a�ő�l
#define GAME_BALLOON_CREATE_DIFFER_WERE_WOLF_MIN (300.0f)								//���D�̐�������R���v���C���[����͈̔͂̔��a�ŏ��l
#define GAME_BALLOON_TO_BALLOON_DIFFER			 (250.0f)								//���D���畗�D�܂ł̋���
#define GAME_BALLOON_TO_PLAYER_DIFFER			 (150.0f)								//�v���C���[����ǂꂭ�炢���ꂽ�ʒu�ɐ������邩
#define GAME_BALLOON_INIT_CREATE_SPACE			 (400.0f)								//���D�̏��������Ԋu
#define GAME_BALLOON_INIT_CREATE_POS_Z			 (200.0f)								//���D�̏��������ʒuZ

#define GAME_ITEM_BOX_CREATE_INTERVAL			 (140)									//�A�C�e���{�b�N�X�̐����Ԋu
#define GAME_ITEM_BOX_CREATE_POS_X				 (900.0f)								//�A�C�e���{�b�N�X�̐����ʒuX
#define GAME_ITEM_BOX_CREATE_POS_Z				 (float (rand() % 1001 + -500))			//�A�C�e���{�b�N�X�̐����ʒuZ

#define GAME_FINISH_UI_NUM						 (5)									//�t�B�j�b�V��UI�̐�

#define GAME_NEX_SCENE_COUNT					 (180)									//���̃V�[���܂ł̃J�E���g

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGameScene01::CGameScene01()
{
	m_nCntGameClear = 0;
	m_nCreateItemBoxCounter = 0;
	memset(m_apPlayer, NULL, sizeof(m_apPlayer[MAX_OBJECT_PLAYER_NUM]));
	memset(m_apPlayerIcon, NULL, sizeof(m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM]));
	m_bReady = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameScene01::~CGameScene01()
{

}

//=============================================================================
// �Q�[���V�[���̏���������
//=============================================================================
void CGameScene01::Init(void) {
	//�e�N�X�`���̃��[�h
	CTexture::Load("game01");

	//�ϐ�������
	m_nCreateItemBoxCounter = GAME_ITEM_BOX_CREATE_INTERVAL;
	m_bReady = true;

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
	D3DXVECTOR3 posLightV = D3DXVECTOR3(1000.0f, 2000.0f, -1000.0f);	//���C�g�̎��_�̈ʒu	D3DXVECTOR3(600.0f, 1500.0f, -2000.0f);
	D3DXVECTOR3 posLightR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���C�g�̒����_�̈ʒu
	D3DXVECTOR3 vecLight = -D3DXVECTOR3(posLightV - posLightR);	//���C�g�̃x�N�g��
	D3DXVec3Normalize(&vecLight, &vecLight);	//�x�N�g���𐳋K��
	//���C�g�̃r���[�}�g���b�N�X�𐶐�
	D3DXMatrixLookAtLH(&mtxLightView, &posLightV, &posLightR, &D3DXVECTOR3(0, 0, 1));
	//�V�F�[�_�̃��C�g��ݒ肷��
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
		pRenderer->SetEffectFogColor(FOG_COLOR);
		pRenderer->SetEffectFogRange(800.0f, 4500.0f);
		//�o�b�N�o�b�t�@���t�H�O�̐F�ɍ��킹��
		pRenderer->SetBackBuffColor(FOG_COLOR);
	}

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�
	CObject::SetUpdatePauseLevel(0);

	

	////�v���C���[�̃X�e���V���ɕ`�悳���V���G�b�g
	//CObject2D* pSilhouettePlayer = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, SCREEN_WIDTH, SCREEN_HEIGHT);
	//if (pSilhouettePlayer != nullptr) {
	//	pSilhouettePlayer->SetColor(D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	//	pSilhouettePlayer->SetEnableStencil(true);
	//	pSilhouettePlayer->SetDrawPriority(CObject::DRAW_PRIORITY::UI_BG);
	//}

	//BGM�̍Đ�
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME);
	}
	//�Q�[���V�[���̏���������
	CGameScene::Init();
}

//=============================================================================
//�I�u�W�F�N�g��������
//=============================================================================
void CGameScene01::CreateObject(void)
{
	//�A�C�R����������
	CreateIcon();

	//���̐���
	CMeshwall::Create(D3DXVECTOR3(0.0f, 0.0f, -1500.0f), D3DXVECTOR3(D3DX_PI*0.5f, 0.0f, 0.0f), 4, 4, 1000.0f, 1000.0f, CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);

	//�X�^�W�A���̐���
	CObjectModel::Create(CModel::MODELTYPE::OBJ_STADIUM, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//�~���̕ǂ̐���
	CMeshcylinder* pWall = CWallCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), GAME_STAGE_SIZE, 40.0f, CTexture::TEXTURE_TYPE::MESH_STAGE_WALL, false);
	if (pWall != nullptr) {
		pWall->SetMaterialSpecular(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	pWall = CMeshcylinder::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, GAME_STAGE_SIZE, GAME_STAGE_SIZE + 50.0f, 1, 0.0f, true, CTexture::TEXTURE_TYPE::MESH_STAGE_WALL);
	if (pWall != nullptr) {
		pWall->SetMaterialSpecular(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	pWall = CMeshcylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, GAME_STAGE_SIZE + 50.0f, GAME_STAGE_SIZE + 50.0f, 1, 40.0f, true, CTexture::TEXTURE_TYPE::MESH_STAGE_WALL);
	if (pWall != nullptr) {
		pWall->SetMaterialSpecular(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//���D�𐶐�����
	for (int nCntBalloon = 0; nCntBalloon < BALLOON_MAX_NUM; nCntBalloon++)
	{
		CBalloon::Create(false, D3DXVECTOR3(-GAME_BALLOON_INIT_CREATE_SPACE + GAME_BALLOON_INIT_CREATE_SPACE * nCntBalloon,
			                                GAME_BALLOON_CREATE_POS_Y,
			                                GAME_BALLOON_INIT_CREATE_POS_Z));
	}

	//�v���C���[�̐���
	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		m_apPlayer[nCntPlayer] = CObjectPlayerBalloonCar::Create(D3DXVECTOR3(-GAME_PLAYER_INIT_CREATE_SPACE * (MAX_OBJECT_PLAYER_NUM / 2.5f) + GAME_PLAYER_INIT_CREATE_SPACE * nCntPlayer,
												                 0.0f,
												                 GAME_PLAYER_INIT_CREATE_POS_Z));
		//�V�[���̃v���C���[�̐ݒ�
		SetPlayer(m_apPlayer[nCntPlayer]);

		//�X�V���Ȃ��悤�ɂ���
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(false);
	}
}

//=============================================================================
// �Q�[���V�[���̏I������
//=============================================================================
void CGameScene01::Uninit(void) {
	//�Q�[���V�[���̏I������
	CGameScene::Uninit();
}

//=============================================================================
// �Q�[���V�[���̍X�V����
//=============================================================================
void CGameScene01::Update(void) {
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

	//�Q�[���V�[���̍X�V����
	CGameScene::Update();
}

//=============================================================================
// �Q�[�����̍X�V
//=============================================================================
void CGameScene01::UpdateGame(void) {
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

	//���D�̐���
	CreateBalloon();

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

	//�^�C�}�[����������Ă�����
	if (m_pTimer != nullptr)
	{
		if (m_pTimer->GetScore() <= GAME_CREATE_ITEMBOX_TIME)
		{
			//�A�C�e���{�b�N�X�̐���
			CreateItemBox();
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
void CGameScene01::UpdateGameOver(void) {
	m_nCntGameClear++;

	if (m_nCntGameClear > GAME_NEX_SCENE_COUNT)
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
				int nScore = 40 - (GetRanking(nIdx) - 1)*10;	//�����L���O���擾���ăX�R�A������
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
void CGameScene01::UpdateReady(void){
	//�`�F�b�N�o���Ă��Ȃ�������
	if (!m_bAllCheck)
	{
		if (m_pCheck != nullptr)
		{
			//�S�����`�F�b�N�o������
			if (m_pCheck->GetUninitAll())
			{
				for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
				{
					//�v���C���[�A�C�R���̐�������
					CreatePlayerIcon(nCntPlayer);
				}
				//�S�����`�F�b�N�o������Ԃɂ���
				m_bAllCheck = true;
			}
		}
	}
	else
	{
		if (m_pCheck != nullptr)
		{
			//�J�E���g�_�E��UI����������Ă�����
			if (m_pCheck->GetCountDownUi() != nullptr)
			{
				//�J�E���g�_�E��UI�̏���
				CountDownUi();
			}
		}
	}
}

//=============================================================================
// �Q�[���I�[�o�[
//=============================================================================
void CGameScene01::GameOver(void) {
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

	//�����L���O�ݒ菈��
	SetRanking();
}

//=============================================================================
//���D��������
//=============================================================================
void CGameScene01::CreateBalloon(void)
{
	//���D�̐���0�Ȃ�
	if (CBalloon::GetNum() == 0)
	{
		std::vector<D3DXVECTOR3> playerPos;
		playerPos.clear();

		for (int nCntPlayer = 0; nCntPlayer < CPlayer::GetNum(); nCntPlayer++)
		{
			playerPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}

		CObject* pObject = CObject::GetObjectTopAll();	//�S�I�u�W�F�N�g�̃��X�g�̐擪���擾

		while (pObject != nullptr) {
			CObject* pObjNext = CObject::GetObjectNextAll(pObject);	//���X�g�̎��̃I�u�W�F�N�g�̃|�C���^���擾

			//�I�u�W�F�N�g�^�C�v�̊m�F
			bool bMatchType = false;
			if (pObject->GetObjType() & CObject::OBJTYPE_PLAYER) bMatchType = true;

			if (!bMatchType)
			{
				pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
				continue;
			}

			//�v���C���[�ɃL���X�g
			CObjectPlayer *pPlayer = static_cast<CObjectPlayer*> (pObject);

			//�v���C���[�̈ʒu���擾
			playerPos[pPlayer->GetPlayer()->GetIndex() - 1] = pPlayer->GetPos();

			pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
		}

		D3DXVECTOR3 createBalloonPos[BALLOON_MAX_NUM];

		for (int nCntBalloon = 0; nCntBalloon < BALLOON_MAX_NUM; nCntBalloon++)
		{
			//�ʒu
			D3DXVECTOR3 balloonPos = { 0.0f, GAME_BALLOON_CREATE_POS_Y, 0.0f };
			//���S����̉���
			float fDiffer = 0.0f;
			//�ʒu��ς��邽�߂̌���
			float fRot = 0.0f;

			bool bLoop = true;

			//���Ԃ�Ȃ��Ȃ�܂ŉ�
			while (bLoop)
			{
				//�����������_���Ō��߂�
				fRot = (rand() % 629 + -314) / 100.0f;

				//���_
				D3DXVECTOR3 originPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//�ŏ������l�T���[�h���I���Ȃ�
				if (nCntBalloon == 0 && GetWereWolfMode())
				{
					fDiffer = (rand() % ((int((GAME_BALLOON_CREATE_DIFFER_WERE_WOLF_MAX - GAME_BALLOON_CREATE_DIFFER_WERE_WOLF_MIN) * 100.0f))) +
						                 (int(GAME_BALLOON_CREATE_DIFFER_WERE_WOLF_MIN * 100.0f))) / 100.0f;
					originPos = playerPos[GetWereWolfPlayerIndex() - 1];
				}
				else
				{
					//�����������_���Ō��߂�
					fDiffer = (rand() % (int)(GAME_BALLOON_CREATE_DIFFER) * 100.0f) / 100.0f;
				}

				//���߂��ʒu�ɏo��
				balloonPos.x = originPos.x + sinf(fRot) * fDiffer;
				balloonPos.z = originPos.z + cosf(fRot) * fDiffer;

				//�N���A���������̐�
				int nClearCount = 0;

				//���łɐ�������Ă��镪������
				for (int nCntCreateBalloon = 0; nCntCreateBalloon < nCntBalloon; nCntCreateBalloon++)
				{
					//���������悤�Ƃ��Ă��镗�D���炷�łɐ����������D�܂ł̋����x�N�g�������߂�
					D3DXVECTOR2 differVec = D3DXVECTOR2(balloonPos.x - createBalloonPos[nCntCreateBalloon].x,
						                                balloonPos.z - createBalloonPos[nCntCreateBalloon].z);
					//�����x�N�g�����狗�����Z�o
					float fCreateBalloonDiffer = D3DXVec2Length(&differVec);

					//���D1���ȏ�Ԃ��󂢂Ă�����
					if (fCreateBalloonDiffer > GAME_BALLOON_TO_BALLOON_DIFFER)
					{
						//�N���A�������𑝂₷
						nClearCount++;
					}
					else
					{
						break;
					}
				}

				//�N���A�����������񂵂����ƈ�v���Ă�����
				if (nClearCount == nCntBalloon)
				{
					for (int nCntPlayer = 0; nCntPlayer < CPlayer::GetNum(); nCntPlayer++)
					{
						//���������悤�Ƃ��Ă��镗�D����v���C���[�܂ł̋����x�N�g�������߂�
						D3DXVECTOR2 differPlayerVec = D3DXVECTOR2(balloonPos.x - playerPos[nCntPlayer].x,
														          balloonPos.z - playerPos[nCntPlayer].z);
						//�����x�N�g�����狗�����Z�o
						float fToOlayerDiffer = D3DXVec2Length(&differPlayerVec);

						//���蕪�Ԃ��󂢂Ă�����
						if (fToOlayerDiffer > GAME_BALLOON_TO_PLAYER_DIFFER)
						{
							//�N���A�������𑝂₷
							nClearCount++;
						}
						else
						{
							break;
						}
					}

					//�N���A�����������񂵂����ƈ�v���Ă�����
					if (nClearCount == nCntBalloon + CPlayer::GetNum())
					{
						//���[�v�I��
						bLoop = false;

						//�ŏ������l�T���[�h���I���Ȃ�
						if (nCntBalloon == 0 && GetWereWolfMode())
						{
							//���������悤�Ƃ��Ă��镗�D���璆���܂ł̃x�N�g�������߂�
							D3DXVECTOR2 baloonOriginDifferVec = D3DXVECTOR2(balloonPos.x - 0.0f, balloonPos.z - 0.0f);
							//�����x�N�g�����狗�����Z�o
							float fBaloonOriginDiffer = D3DXVec2Length(&baloonOriginDifferVec);

							//�X�e�[�W����͂ݏo�Ă���
							if (fBaloonOriginDiffer > GAME_BALLOON_CREATE_DIFFER)
							{
								//���[�v������
								bLoop = true;
							}
							else
							{
								bLoop = false;
							}
						}
					}
				}
			}

			//�����ł������D�̈ʒu��ۑ�
			createBalloonPos[nCntBalloon] = balloonPos;

			//�S�[���h���ǂ���
			bool bGold = false;

			//�ŏ�����
			if (nCntBalloon == 0)
			{
				//���ɂ���
				bGold = true;
			}

			//���D�𐶐�����
			CBalloon::Create(bGold, balloonPos);

			//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
			//���D�o���G�t�F�N�g
			CPresetEffect::SetEffect3D(5, D3DXVECTOR3(balloonPos.x, balloonPos.y + 130, balloonPos.z - 90), {}, {});		//�f�J�~
			CPresetEffect::SetEffect3D(6, D3DXVECTOR3(balloonPos.x, balloonPos.y + 140, balloonPos.z - 90), {}, {});		//����Ă�o
			//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

		}

		//�}�l�[�W���[�̎擾
		CManager* pManager = CManager::GetManager();
		//�T�E���h�̎擾
		CSound *pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//���Đ�
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_BALLOON_SPAWN);
	}
}

//=============================================================================
// �A�C�e���{�b�N�X��������
//=============================================================================
void CGameScene01::CreateItemBox(void){
	m_nCreateItemBoxCounter++;
	//���̒l�ɂȂ�����
	if (m_nCreateItemBoxCounter > GAME_ITEM_BOX_CREATE_INTERVAL)
	{
		m_nCreateItemBoxCounter = 0;

		//�����ʒu
		D3DXVECTOR3 itemBoxPos = D3DXVECTOR3(GAME_ITEM_BOX_CREATE_POS_X, GAME_BALLOON_CREATE_POS_Y, 0.0f);
		//�ړ���
		D3DXVECTOR3 itemBoxMove = D3DXVECTOR3(-ITEM_BOX_MOVE_SPEED, 0.0f, 0.0f);

		//2����1�̊m����
		if (rand() % 2 == 0)
		{
			//�t�ɐ���
			itemBoxPos.x *= -1.0f;
			//�t�Ɉړ�������
			itemBoxMove.x *= -1.0f;
		}

		//�����_����Z�ʒu�����߂�
		itemBoxPos.z = GAME_ITEM_BOX_CREATE_POS_Z;

		//�A�C�e���{�b�N�X�𐶐�����
		CItemBox *pItemBox = CItemBox::Create(itemBoxPos);
		pItemBox->SetMove(itemBoxMove);
	}
}

//=============================================================================
//�v���C���[�A�C�R����������
//=============================================================================
void CGameScene01::CreatePlayerIcon(int nCntPlayer){

	//��������Ă�����
	if (m_apPlayerIcon[nCntPlayer] != nullptr)
	{
		return;
	}

	//�v���C���[�̈ʒu�擾
	D3DXVECTOR3 playerPos = m_apPlayer[nCntPlayer]->GetPos();

	playerPos.x += 150.0f;
	playerPos.z -= 100.0f;

	//�A�C�R���̈ʒu
	D3DXVECTOR3 iconPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[���h���W����X�N���[�����W�ɕϊ�
	iconPos = WorldToScreen(playerPos);
	iconPos.z = 0.0f;

	//����
	m_apPlayerIcon[nCntPlayer] = CObjectPlayerIcon::Create(iconPos, D3DXVECTOR3(GAME_PLAYER_ICON_SCALE, GAME_PLAYER_ICON_SCALE, GAME_PLAYER_ICON_SCALE),
		                                             CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_ICON_FRAME_1) + nCntPlayer),
													 CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_NUM_WHITE_1) + nCntPlayer));
}

//=============================================================================
//�J�E���g�_�E��UI�̏���
//=============================================================================
void CGameScene01::CountDownUi(void)
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

			//�L���X�g
			CObjectPlayerBalloonCar *pPlayer = dynamic_cast<CObjectPlayerBalloonCar*>(m_apPlayer[nCntPlayer]);
			if (pPlayer == nullptr) continue;

			//�X�R�AUI����������Ă��Ȃ�������
			if (pPlayer->GetScoreUi() == nullptr)
			{
				//��������
				pPlayer->CreateScore();

				//�A�C�e����UI�̃t���[���𐶐�
				pPlayer->CreateItemUiFrame();
			}
		}

		//��������Ă��Ȃ�������
		if (m_pTimerFrame == nullptr)
		{
			//�^�C�}�[�̐���
			m_pTimerFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 61.0f, 0.0f), CTexture::TEXTURE_TYPE::TIMER_FRAME, 220.0f, 80.0f);
			m_pTimer = CTimer::Create(GAME_TIME, 2, CTexture::TEXTURE_TYPE::NUMBER_003, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 75.0f, 40.0f, 0.0f), 50.0f);
		}
	}
}

//=============================================================================
//�����L���O�ݒ菈��
//=============================================================================
void CGameScene01::SetRanking()
{
	std::vector<int> nSocre(MAX_OBJECT_PLAYER_NUM);
	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//�L���X�g
		CObjectPlayerBalloonCar *pPlayer = dynamic_cast<CObjectPlayerBalloonCar*>(m_apPlayer[nCntPlayer]);
		if (pPlayer == nullptr) continue;

		nSocre[nCntPlayer] = pPlayer->GetScoreUi()->GetScore()->GetScore();
	}
	//�~���Ń\�[�g
	std::sort(nSocre.begin(), nSocre.end(), std::greater<int>());

	//���O�ŏ��ʂ����肵���v���C���[
	int nLastRank = 0;

	for (int nCntScore = 0; nCntScore < MAX_OBJECT_PLAYER_NUM; nCntScore++)
	{
		for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
		{
			//�L���X�g
			CObjectPlayerBalloonCar *pPlayer = dynamic_cast<CObjectPlayerBalloonCar*>(m_apPlayer[nCntPlayer]);
			if (pPlayer == nullptr) continue;

			//�擾�����v���C���[�̃X�R�A�ƈ�v���Ă��Ȃ�������
			if (nSocre[nCntScore] != pPlayer->GetScoreUi()->GetScore()->GetScore())
			{
				continue;
			}

			//��ԍŏ��Ȃ�
			if (nCntScore == 0)
			{
				//�����L���O�ݒ菈��
				CGameScene::SetRanking(nCntScore + 1, nCntPlayer);
				nLastRank = nCntScore + 1;
			}

			//�O�̃X�R�A�ƈ�v���Ă�����
			else if (nSocre[nCntScore] == nSocre[nCntScore - 1])
			{
				//�O�̏��ʂƓ����ɂ���
				CGameScene::SetRanking(nLastRank, nCntPlayer);
			}
			else
			{
				//�����L���O�ݒ菈��
				CGameScene::SetRanking(nCntScore + 1, nCntPlayer);
				nLastRank = nCntScore + 1;
			}
		}
	}
}
