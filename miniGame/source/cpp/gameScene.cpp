//=============================================================================
//
// �Q�[���V�[������ [gameScene.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "gameScene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "gameCamera.h"
#include "fade.h"
#include "timer.h"
#include "score.h"
#include "stage.h"
#include "object2D.h"
#include "player.h"
#include "effect.h"
#include "terrain.h"
#include "meshwall.h"
#include "wallCylinder.h"
#include "pauseMenu.h"
#include "balloon.h"
#include "itemBox.h"
#include "item_banana.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GAME_TIME (300)
#define TEXT_FILE_NAME_HISCORE					 "data/TEXT/save_hiscore.txt"
#define TEXT_FILE_NAME_APPLETYPE				 "data/TEXT/save_appletype.txt"
#define FOG_COLOR								 (D3DXCOLOR(0.1f, 0.0f, 0.2f, 1.0f))	//�t�H�O�̐F
#define FOG_COLOR_GAMECLEAR					     (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	//�t�H�O�̐F
#define GAME_STAGE_SIZE							 (700.0f)								//���ā[���̑傫��
#define GAME_BALLOON_CREATE_POS_Y				 (45.0f)								//���D�̈ʒuY
#define GAME_BALLOON_CREATE_DIFFER				 (600.0f)								//���D�̐�������͈͂̔��a
#define GAME_BALLOON_TO_BALLOON_DIFFER			 (250.0f)								//���D���畗�D�܂ł̋���
#define GAME_BALLOON_TO_PLAYER_DIFFER			 (180.0f)								//�v���C���[����ǂꂭ�炢���ꂽ�ʒu�ɐ������邩
#define GAME_BALLOON_INIT_CREATE_SPACE			 (300.0f)								//���D�̏��������Ԋu
#define GAME_PLAYER_INIT_CREATE_SPACE			 (200.0f)								//�v���C���[�̏��������Ԋu
#define GAME_PLAYER_INIT_CREATE_POS_Z			 (-400.0f)								//�v���C���[�̏��������ʒuZ
#define GAME_BALLOON_INIT_CREATE_POS_Z			 (200.0f)								//���D�̏��������ʒuZ

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGameScene::CGameScene()
{
	m_pStage = nullptr;
	m_pTimer = nullptr;
	m_pMenuGameEnd = nullptr;
	m_nGameScore = 0;

	m_nCntGameClear = 0;
	m_nCreateItemBoxCounter = 0;
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
	m_nCreateItemBoxCounter = 0;


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
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 800.0f, 5500.0f);

	D3DXMATRIX mtxLightView;   // ���C�g�r���[�ϊ�
	D3DXVECTOR3 posLight = D3DXVECTOR3(0.0f, 4800.0f, 0.0f);	//���C�g�̈ʒu
	D3DXVECTOR3 vecLight;	//���C�g�̃x�N�g��
	D3DXVec3Normalize(&vecLight, &posLight);
	vecLight *= -1;
	//���C�g�̃r���[�}�g���b�N�X�𐶐�
	D3DXMatrixLookAtLH(&mtxLightView, &posLight, &D3DXVECTOR3(posLight + vecLight), &D3DXVECTOR3(0, 0, 1));
	//�V�F�[�_�̃��C�g��ݒ�
	if (pRenderer != nullptr) {
		pRenderer->SetEffectLightMatrixView(mtxLightView);
		pRenderer->SetEffectLightVector(D3DXVECTOR4(vecLight, 1.0f));
		pRenderer->SetEffectLightMatrixProj(mtxLightProj);
	}

	//���̃r���{�[�h����
	CBillboard* pMoon = CBillboard::Create(D3DXVECTOR3(-800.0f, 1500.0f, -2000.0f), CTexture::TEXTURE_TYPE::MOON, 200.0f, 200.0f);
	if (pMoon != nullptr) pMoon->SetDrawPriority(CObject::DRAW_PRIORITY::BG);

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

	//------------------------------
	//���[�V�������̃��[�h
	//------------------------------

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�
	CObject::SetUpdatePauseLevel(0);

	//�X�e�[�W�̐���
	//if (m_pStage == nullptr) m_pStage = new CStage;
	//if (m_pStage != nullptr) m_pStage->CreateStage(TEXT_FILE_NAME_STAGE_GAME);

	CItemBanana::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f));

	//���̐���
	CMeshwall::Create(D3DXVECTOR3(0.0f, 0.0f, -1500.0f), D3DXVECTOR3(D3DX_PI*0.5f, 0.0f, 0.0f), 4, 4, 1000.0f, 1000.0f, CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);

	//�X�^�W�A���̐���
	CObjectModel::Create(CModel::MODELTYPE::OBJ_STADIUM, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//�~���̕ǂ̐���
	CWallCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), GAME_STAGE_SIZE, 40.0f, CTexture::TEXTURE_TYPE::NONE, false);
	CMeshcylinder::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, GAME_STAGE_SIZE, GAME_STAGE_SIZE + 50.0f, 1, 0.0f, true, CTexture::TEXTURE_TYPE::NONE);

	//���D�𐶐�����
	for (int nCntBalloon = 0; nCntBalloon < BALLOON_MAX_NUM; nCntBalloon++)
	{
		CBalloon::Create(false, D3DXVECTOR3(-GAME_BALLOON_INIT_CREATE_SPACE + GAME_BALLOON_INIT_CREATE_SPACE * nCntBalloon,
			                                GAME_BALLOON_CREATE_POS_Y,
			                                GAME_BALLOON_INIT_CREATE_POS_Z));
	}

	//�v���C���[�̐���
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
	{
		CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(-GAME_PLAYER_INIT_CREATE_SPACE * (MAX_PLAYER_NUM / 2.5f) + GAME_PLAYER_INIT_CREATE_SPACE * nCntPlayer,
			                                           0.0f,
			                                           GAME_PLAYER_INIT_CREATE_POS_Z));
		//�V�[���̃v���C���[�̐ݒ�
		SetPlayer(pPlayer);
	}

	//�^�C�}�[�̐���
	m_pTimerFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 61.0f, 0.0f), CTexture::TEXTURE_TYPE::TIMER_FRAME, 220.0f, 80.0f);
	m_pTimer = CTimer::Create(GAME_TIME, 3, CTexture::TEXTURE_TYPE::NUMBER_003, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 75.0f, 40.0f, 0.0f), 50.0f);

	//BGM�̍Đ�
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME);
	}

#ifdef _DEBUG
	//Z�o�b�t�@�e�N�X�`���̕\��
	CObject2D* pZBuff = CObject2D::Create(D3DXVECTOR3(70.0f, 70.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, 100.0f, 100.0f);
	if (pZBuff != nullptr) {
		pZBuff->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
		pZBuff->SetUseZBuffTexture(true);
	}
#endif

	m_nGameScore = 0;
}

//=============================================================================
// �Q�[���V�[���̏I������
//=============================================================================
void CGameScene::Uninit(void) {
	//�X�e�[�W�̔j��
	if (m_pStage != nullptr) {
		delete m_pStage;
		m_pStage = nullptr;
	}

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
#ifdef _DEBUG
	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	//���݂̓��̓f�o�C�X�̎擾
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;

	//�Q�[���I�[�o�[
	if (pInput->GetTrigger(CInput::CODE::DEBUG_1)) {
		GameOver();
	}

	//�^�C���ǉ�
	if (pInput->GetTrigger(CInput::CODE::DEBUG_3)) {
		if (m_pTimer != nullptr) m_pTimer->AddScore(50);
	}

	//���D�̐���
	CreateBalloon();

	//�A�C�e���{�b�N�X�̐���
	CreateItemBox();
#endif

	//�Q�[���I�[�o�[��
	if (m_bGameOver) {
		UpdateGameOver();
	}
	//�Q�[����
	else
	{
		UpdateGame();
	}
}

//=============================================================================
// �Q�[�����̍X�V
//=============================================================================
void CGameScene::UpdateGame(void) {
	//�|�[�Y���j���[������ꍇ�͍X�V�Ȃ�
	if (m_pMenuPause != nullptr) return;

	//�Q�[���I�����Ă��Ȃ��Ƃ��Ƀ^�C�}�[���O�ɂȂ����ꍇ
	if (m_pTimer != nullptr && !m_bGameOver) {
		if (m_pTimer->GetScore() <= 0) {
			//�Q�[���I��
			GameOver();
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
	if (pInput->GetTrigger(CInput::CODE::PAUSE) && !pFade->GetFade()) {
		//�|�[�Y���j���[�N���X�𐶐�
		m_pMenuPause = CPauseMenu::Create();
		//�T�E���h���Đ�
		pSound->PlaySound(CSound::SOUND_LABEL::TITLE_OPEN);
	}
}

//=============================================================================
// �Q�[���I�[�o�[���̍X�V
//=============================================================================
void CGameScene::UpdateGameOver(void) {
	if (m_pMenuGameEnd == nullptr) return;

	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	//���݂̓��̓f�o�C�X�̎擾
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;
	//�t�F�[�h�̎擾
	CFade* pFade = pManager->GetFade();		//�t�F�[�h�ւ̃|�C���^
	if (pFade == nullptr) return;
	//�T�E���h�̎擾
	CSound* pSound = pManager->GetSound();	//�T�E���h�ւ̃|�C���^
	if (pSound == nullptr) return;

	//�I����
	if (pInput->GetTrigger(CInput::CODE::SELECT)) {
		switch (m_pMenuGameEnd->GetIdxCurSelect())
		{
		case 0:
			//�^�C�g���փV�[���J��
			pFade->SetFade(CScene::SCENE_TYPE::TITLE, 0.02f, 60);
			break;
		case 1:
			//�Q�[�����ăv���C
			pFade->SetFade(CScene::SCENE_TYPE::GAME, 0.02f, 60);
			break;
		}

		//�I�����艹�̍Đ�
		pSound->PlaySound(CSound::SOUND_LABEL::TITLE_START);
	}
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
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::GAMEOVER);

	//�v���C���[�̎擾
	CPlayer* pPlayer = GetPlayer();
	if (pPlayer != nullptr) {
		//�v���C���[�̃Q�[���I�[�o�[���̏���
		pPlayer->GameOver();
	}

	//�Q�[���I�[�o�[�e�L�X�g�̕\��
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 300.0f, 0.0f), CTexture::TEXTURE_TYPE::TEXT_GAMEOVER, 600.0f, 150.0f);

	//�Q�[���I�����j���[�̐���
	CreateMenuEndGame();

	//�^�C�}�[���~
	if (m_pTimer != nullptr) {
		m_pTimer->SetStop(true);
	}

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�i�O�̂��߁j
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
// �Q�[���I�����̑I�����j���[�̐���
//=============================================================================
void CGameScene::CreateMenuEndGame(void) {
	//���łɐ�������Ă���ꍇ�I��
	if (m_pMenuGameEnd != nullptr) return;

	//���j���[�̐���
	m_pMenuGameEnd = CSelectMenu2D::Create(2, true);
	if (m_pMenuGameEnd == nullptr) return;

	//�w�i�̐ݒ�
	m_pMenuGameEnd->SetMenuBG(CTexture::TEXTURE_TYPE::MENU_BG, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 600.0f, 0.0f), 600.0f, 80.0f);
	//���I��
	m_pMenuGameEnd->SetSelectType(CSelectMenu::SELECT_TYPE::HORIZONTAL);
	//�I����UI�̏ڍאݒ�
	m_pMenuGameEnd->SetSelectUI(0, D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 130.0f, 600.0f, 0.0f), 220.0f, 40.0f, CTexture::TEXTURE_TYPE::TEXT_QUIT);
	m_pMenuGameEnd->SetSelectUI(1, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 130.0f, 600.0f, 0.0f), 220.0f, 40.0f, CTexture::TEXTURE_TYPE::TEXT_RETRY);
	//�I�����A�C�R���̐���
	m_pMenuGameEnd->CreateSelectIcon(D3DXVECTOR3(-80.0f, 0.0f, 0.0f), 40.0f, 40.0f, CTexture::TEXTURE_TYPE::SELECT_ICON);
	m_pMenuGameEnd->SetIconPosOffset(1, D3DXVECTOR3(-105.0f, 0.0f, 0.0f));
}

//=============================================================================
//���D��������
//=============================================================================
void CGameScene::CreateBalloon(void)
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
			CPlayer *pPlayer = static_cast<CPlayer*> (pObject);

			//�v���C���[�̈ʒu���擾
			playerPos[pPlayer->GetIndex() - 1] = pPlayer->GetPos();

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
				fDiffer = (rand() % (int)(GAME_BALLOON_CREATE_DIFFER) * 100.0f) / 100.0f;
				//�����������_���Ō��߂�
				fRot = (rand() % 629 + -314) / 100.0f;

				//���߂��ʒu�ɏo��
				balloonPos.x = sinf(fRot) * fDiffer;
				balloonPos.z = cosf(fRot) * fDiffer;

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
						bLoop = false;
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
		}
	}
}

//=============================================================================
// �A�C�e���{�b�N�X��������
//=============================================================================
void CGameScene::CreateItemBox(void){
	
	//�A�C�e������������Ă��Ȃ��Ȃ�
	if (CItemBox::GetNum() == 0)
	{
		m_nCreateItemBoxCounter++;
		//���̒l�ɂȂ�����
		if (m_nCreateItemBoxCounter > 180)
		{
			m_nCreateItemBoxCounter = 0;

			//�����ʒu
			D3DXVECTOR3 itemBoxPos = D3DXVECTOR3(1000.0f, GAME_BALLOON_CREATE_POS_Y, 0.0f);
			//�ړ���
			D3DXVECTOR3 itemBoxMove = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);

			//2����1�̊m����
			if (rand() % 2 == 0)
			{
				//�t�ɐ���
				itemBoxPos.x *= -1.0f;
				//�t�Ɉړ�������
				itemBoxMove.x *= -1.0f;
			}

			//�����_����Z�ʒu�����߂�
			itemBoxPos.z = float (rand() % 801 + -400);

			//�A�C�e���{�b�N�X�𐶐�����
			CItemBox *pItemBox = CItemBox::Create(itemBoxPos);
			pItemBox->SetMove(itemBoxMove);
		}
	}
}