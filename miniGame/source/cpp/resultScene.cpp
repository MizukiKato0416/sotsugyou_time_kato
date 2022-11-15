//=============================================================================
//
// ���U���g�V�[������ [resultScene.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "resultScene.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
#include "object2D.h"
#include "objectModelUI.h"
#include "object_player.h"
#include "ToScreen.h"
#include "gameCamera.h"
#include "gameScene.h"
#include "next_button.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define RESULT_SCENE_POINT_UI_SIZE		(D3DXVECTOR3(325.0f * 0.5f, 128.0f* 0.5f, 0.0f))	//�|�C���gUI�̃T�C�Y
#define RESULT_SCENE_POINT_UI_ADD_ALPHA	(0.08f)												//�|�C���gUI�̃��l���Z�l
#define RESULT_SCENE_POINT_UI_ADD_POS_Y	(3.0f)												//�|�C���gUI�̈ʒu���Z�l
#define RESULT_SCENE_POINT_UI_COUNTER	(150)												//�|�C���gUI�̌�����悤�ɂȂ�܂ł̃J�E���g

#define RESULT_SCENE_CHANGE_SCENE_COUNTER		(180)			//�V�[���J�ڂ��ł���悤�ɂȂ�܂ł̃J�E���^�[
#define RESULT_SCENE_CHANGE_SCENE_COUNTER_WOLF	(210)			//�V�[���J�ڂ��ł���悤�ɂȂ�܂ł̃J�E���^�[�l�T���[�h

#define RESULT_SCENE_PLAYER_INIT_POS_Z		(950.0f)	//�v���C���[�̏����ʒuZ
#define RESULT_SCENE_PLAYER_MOVE			(25.0f)		//�v���C���[�̈ړ���
#define RESULT_SCENE_PLAYER_ROTATE_SPEED	(0.05f)		//�v���C���[�̉�]���x

#define RESULT_SCENE_NEXT_BUTTON_POS			(D3DXVECTOR3(1150.0f, 670.0f, 0.0f))	//���ɐi�ރ{�^���̈ʒu
#define RESULT_SCENE_NEXT_BUTTON_SIZE			(D3DXVECTOR3(70.0f, 70.0f, 0.0f))		//���ɐi�ރ{�^���̃T�C�Y
#define RESULT_SCENE_NEXT_BUTTON_COUNTER		(15)									//���ɐi�ރ{�^���̌�����悤�ɂȂ�܂ł̃J�E���^�[
#define RESULT_SCENE_NEXT_BUTTON_DEC_ALPHA		(0.015f)								//���ɐi�ރ{�^���̃��l���Z��

#define RESULT_SCENE_RESULT_UI_SIZE_X			(1230.0f * 0.7f)	//���ʔ��\UI�̃T�C�YX
#define RESULT_SCENE_RESULT_UI_SIZE_Y			(184.0f * 0.7f)		//���ʔ��\UI�̃T�C�YY
#define RESULT_SCENE_RESULT_UI_POS_Y			(100.0f)			//���ʔ��\UI�̈ʒuY

#define RESULT_SCENE_RANKING_UI_SIZE_X			(150.0f)			//����UI�̃T�C�Y
#define RESULT_SCENE_RANKING_UI_SIZE_Y			(150.0f)			//����UI�̃T�C�Y
#define RESULT_SCENE_RANKING_UI_POS_Y			(200.0f)			//����UI�̈ʒu�����l

#define RESULT_SCENE_BG_MOVE_SPEED		(D3DXVECTOR2(0.001f, 0.001f))		//�w�i�̈ړ����x


//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CResultScene::CResultScene()
{
	m_pBg = nullptr;
	memset(m_apPointUi, NULL, sizeof(m_apPointUi[MAX_OBJECT_PLAYER_NUM]));
	memset(m_pPlayerModel, NULL, sizeof(m_pPlayerModel[MAX_OBJECT_PLAYER_NUM]));
	m_nFrameCounter = 0;
	m_pNexButton = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResultScene::~CResultScene()
{

}

//=============================================================================
// ����������
//=============================================================================
void CResultScene::Init(void) {

	//�ϐ�������
	m_nFrameCounter = 0;
	m_pNexButton = nullptr;


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
	}

	//------------------------------
	//�I�u�W�F�N�g�̏����ݒ�
	//------------------------------
	m_pBg = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::BG_RESULT, SCREEN_WIDTH, SCREEN_HEIGHT);

	//------------------------------
	//�����L���O�\��
	//------------------------------
	int aPlayerRank[MAX_OBJECT_PLAYER_NUM];	//�v���C���[�̃����N�̔z�� �C���f�b�N�X�̓v���C���[�̃C���f�b�N�X�ƑΉ�

	//�v���C���[�����N�̎擾
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		aPlayerRank[nIdxPlayer] = CGameScene::GetRanking(nIdxPlayer);
	}

	//�v���C���[�̕\�����̐ݒ�
	int aOrderPlayer[MAX_OBJECT_PLAYER_NUM];
	memset(aOrderPlayer, -1, sizeof(aOrderPlayer));
	int nCurRank = 1;	//���݂̃����N
	int nIdxOrder = 0;	//���Ԃ̃C���f�b�N�X

	while (nCurRank <= MAX_OBJECT_PLAYER_NUM)
	{
		bool bDecision = false;	//���Ԃ̌���

		for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
		{
			if (aOrderPlayer[nIdxPlayer] != -1) continue;	//���Ԃ����肳��Ă����ꍇ���O

			//�����N����v���Ă����ꍇ
			if (aPlayerRank[nIdxPlayer] == nCurRank) {
				aOrderPlayer[nIdxPlayer] = nIdxOrder;	//���Ԃ̐ݒ�
				nIdxOrder++;	//���Ԃ̉��Z
				bDecision = true;	//���Ԃ̌���
				break;
			}
		}
		//�����N����v���Ȃ������ꍇ
		if (!bDecision) {
			nCurRank++;	//�����N�̉��Z
		}
	}

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		//aOrderPlayer[nIdxPlayer] = nIdxPlayer;


		const float fDist = 180.0f;	//�v���C���[���m�̋���
		D3DXVECTOR3 posModel = D3DXVECTOR3(fDist * (-MAX_OBJECT_PLAYER_NUM / 2.0f) + fDist / 2.0f + (aOrderPlayer[nIdxPlayer]) * fDist, 0.0f, RESULT_SCENE_PLAYER_INIT_POS_Z);	//���[����1�ʂ���ׂ�
		m_pPlayerModel[nIdxPlayer] = CObjectModelUI::Create(CModel::MODELTYPE::OBJ_CAR, posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		if (m_pPlayerModel == nullptr) continue;
		m_pPlayerModel[nIdxPlayer]->SetViewCamera(D3DXVECTOR3(0.0f, 400.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		CModel* pModel = m_pPlayerModel[nIdxPlayer]->GetPtrModel();

		//�����L���O��UI����
		D3DXVECTOR3 posRankUI = WorldToScreen(D3DXVECTOR3(posModel.x, posModel.y, 0.0f), m_pPlayerModel[nIdxPlayer]->GetViewMatrix());
		CObject2D* pRankUI = CObject2D::Create(posRankUI + D3DXVECTOR3(0.0f, RESULT_SCENE_RANKING_UI_POS_Y, 0.0f),
			                                   CTexture::TEXTURE_TYPE::PLAYER_NUM_1, RESULT_SCENE_RANKING_UI_SIZE_X, RESULT_SCENE_RANKING_UI_SIZE_Y);

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


		//����UI�̃e�N�X�`���ݒ�
		if (pRankUI == nullptr) continue;
		pRankUI->SetTexType(static_cast<CTexture::TEXTURE_TYPE>(static_cast<int> (CTexture::TEXTURE_TYPE::RANKING_1) + (aPlayerRank[nIdxPlayer] - 1)));

		//�l�T���[�h�łȂ�������
		if (!CGameScene::GetWereWolfMode()) continue;

		//�|�C���gUI�𐶐�
		m_apPointUi[nIdxPlayer] = CObject2D::Create(posRankUI - D3DXVECTOR3(0.0f, 100.0f, 0.0f), CTexture::TEXTURE_TYPE::ADD_POINT_40, 
			                                        RESULT_SCENE_POINT_UI_SIZE.x, RESULT_SCENE_POINT_UI_SIZE.y);
		m_apPointUi[nIdxPlayer]->SetTexType(static_cast<CTexture::TEXTURE_TYPE>
			                               (static_cast<int> (CTexture::TEXTURE_TYPE::ADD_POINT_40) + (aPlayerRank[nIdxPlayer] - 1)));
		m_apPointUi[nIdxPlayer]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	//���ʔ��\UI�̐���
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, RESULT_SCENE_RESULT_UI_POS_Y, 0.0f), CTexture::TEXTURE_TYPE::RESULT_UI,
		              RESULT_SCENE_RESULT_UI_SIZE_X, RESULT_SCENE_RESULT_UI_SIZE_Y);

	//------------------------------
	//BGM�̍Đ�
	//------------------------------
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME);
	}
}

//=============================================================================
// �I������
//=============================================================================
void CResultScene::Uninit(void) {
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
void CResultScene::Update(void) {

	//�t���[���J�E���g����
	FrameCounter();

	//���ɐi�ރ{�^��UI�̏���
	NextButton();

	//�w�i����
	Bg();

	//�v���C���[�̏���
	Player();

	//�|�C���gUI�̏���
	PointUI();

	//�J�ڏ���
	Fade();
}

//=============================================================================
//�|�C���gUI�̏���
//=============================================================================
void CResultScene::PointUI()
{
	//�l�T���[�h�łȂ�������
	if (!CGameScene::GetWereWolfMode())
	{
		return;
	}

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		//��������Ă��Ȃ�������
		if (m_apPointUi[nIdxPlayer] == nullptr) continue;

		//����̒l�ɂȂ��Ă��Ȃ�������
		if (m_nFrameCounter <= RESULT_SCENE_POINT_UI_COUNTER) continue;

		//�����Ȃ��Ă��Ȃ���ԂȂ�
		if (m_apPointUi[nIdxPlayer]->GetColor().a == 1.0f) continue;

		//�J���[�擾
		D3DXCOLOR col = m_apPointUi[nIdxPlayer]->GetColor();
		//�Z������
		col.a += RESULT_SCENE_POINT_UI_ADD_ALPHA;
		if (col.a > 1.0f)
		{
			col.a = 1.0f;

			//�}�l�[�W���[�̎擾
			CManager* pManager = CManager::GetManager();
			//�T�E���h�̎擾
			CSound* pSound = nullptr;
			if (pManager != nullptr) pSound = pManager->GetSound();
			//�����Đ�
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_POINT_1);
		}
		//�J���[�ݒ�
		m_apPointUi[nIdxPlayer]->SetColor(col);

		//�ʒu�擾
		D3DXVECTOR3 pos = m_apPointUi[nIdxPlayer]->GetPos();
		//������
		pos.y -= RESULT_SCENE_POINT_UI_ADD_POS_Y;
		//�ʒu�ݒ�
		m_apPointUi[nIdxPlayer]->SetPos(pos);
	}
}

//=============================================================================
//�v���C���[�̏���
//=============================================================================
void CResultScene::Player()
{
	int aPlayerRank[MAX_OBJECT_PLAYER_NUM];	//�v���C���[�̃����N�̔z�� �C���f�b�N�X�̓v���C���[�̃C���f�b�N�X�ƑΉ�

	//�v���C���[�����N�̎擾
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		aPlayerRank[nIdxPlayer] = CGameScene::GetRanking(nIdxPlayer);
	}
	//�v���C���[�̕\�����̐ݒ�
	int aOrderPlayer[MAX_OBJECT_PLAYER_NUM];
	memset(aOrderPlayer, -1, sizeof(aOrderPlayer));
	int nCurRank = 1;	//���݂̃����N
	int nIdxOrder = 0;	//���Ԃ̃C���f�b�N�X

	while (nCurRank <= MAX_OBJECT_PLAYER_NUM)
	{
		bool bDecision = false;	//���Ԃ̌���

		for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
		{
			if (aOrderPlayer[nIdxPlayer] != -1) continue;	//���Ԃ����肳��Ă����ꍇ���O

			//�����N����v���Ă����ꍇ
			if (aPlayerRank[nIdxPlayer] == nCurRank) {
				aOrderPlayer[nIdxPlayer] = nIdxOrder;	//���Ԃ̐ݒ�
				nIdxOrder++;	//���Ԃ̉��Z
				bDecision = true;	//���Ԃ̌���
				break;
			}
		}
		//�����N����v���Ȃ������ꍇ
		if (!bDecision) {
			nCurRank++;	//�����N�̉��Z
		}
	}

	for (int nIdxPlayer = MAX_OBJECT_PLAYER_NUM - 1; nIdxPlayer >= 0; nIdxPlayer--)
	{
		for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
		{
			if (aOrderPlayer[nCntPlayer] != nIdxPlayer) continue;

			if (m_pPlayerModel[nCntPlayer] == nullptr) continue;

			//��������Ă�����

			//�ʒu�擾
			D3DXVECTOR3 pos = m_pPlayerModel[nCntPlayer]->GetPos();

			//�ʒuZ��0�Ȃ�
			if (pos.z == 0.0f)
			{
				m_pPlayerModel[nCntPlayer]->SetRotSpeed(D3DXVECTOR3(RESULT_SCENE_PLAYER_ROTATE_SPEED, RESULT_SCENE_PLAYER_ROTATE_SPEED, RESULT_SCENE_PLAYER_ROTATE_SPEED));
				continue;
			}

			//�ړ�������
			pos.z -= RESULT_SCENE_PLAYER_MOVE;
			//0��菬����������0�ɂ���
			if (pos.z < 0.0f) pos.z = 0.0f;
			//�ʒu�ݒ�
			m_pPlayerModel[nCntPlayer]->SetPos(pos);
			return;
		}
	}
}

//=============================================================================
//���ɐi��UI����
//=============================================================================
void CResultScene::NextButton()
{
	int nChangeSceneCounter = RESULT_SCENE_CHANGE_SCENE_COUNTER;

	//�l�T���[�h�Ȃ�
	if (CGameScene::GetWereWolfMode()) nChangeSceneCounter = RESULT_SCENE_CHANGE_SCENE_COUNTER_WOLF;

	//����̒l�ɂȂ��Ă��Ȃ�������
	if (m_nFrameCounter < nChangeSceneCounter) return;

	if (m_pNexButton != nullptr) return;

	//����UI�̐���
	m_pNexButton = CNextButton::Create(RESULT_SCENE_NEXT_BUTTON_POS, RESULT_SCENE_NEXT_BUTTON_SIZE,
		                               CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_3, RESULT_SCENE_NEXT_BUTTON_COUNTER,
		                               RESULT_SCENE_NEXT_BUTTON_DEC_ALPHA);
}

//=============================================================================
//�w�i����
//=============================================================================
void CResultScene::Bg()
{
	if (m_pBg == nullptr) return;

	//�w�i�𓮂���
	m_pBg->SetMoveTex(RESULT_SCENE_BG_MOVE_SPEED.x, RESULT_SCENE_BG_MOVE_SPEED.y);
}

//=============================================================================
//�J�ڏ���
//=============================================================================
void CResultScene::Fade()
{
	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	//���݂̓��̓f�o�C�X�̎擾
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;

	if (pInput->GetTrigger(CInput::CODE::SELECT, 0)) {
		//�t�F�[�h�̎擾
		CFade* pFade = pManager->GetFade();		//�t�F�[�h�ւ̃|�C���^
		if (pFade == nullptr) return;

		if (pFade->GetChangeFade()) return;

		//�V�[���J�ڂ���܂ł̃J�E���g
		float fChangeSceneCount = RESULT_SCENE_CHANGE_SCENE_COUNTER;
		//�J�ڐ�
		CScene::SCENE_TYPE sceneType = CScene::SCENE_TYPE::SELECT_GAME;

		//�l�T���[�h�Ȃ�
		if (CGameScene::GetWereWolfMode())
		{
			fChangeSceneCount = RESULT_SCENE_CHANGE_SCENE_COUNTER_WOLF;
			sceneType = CScene::SCENE_TYPE::FIND_WOLF;
		}

		if (m_nFrameCounter < fChangeSceneCount) return;
		if (pFade != nullptr) pFade->SetFade(sceneType, 0.02f, 60);

		//�T�E���h�̎擾
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//�����Đ�
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_OK);
	}
}

//=============================================================================
//�t���[���J�E���g����
//=============================================================================
void CResultScene::FrameCounter()
{
	m_nFrameCounter++;

	//����̒l�ȉ���������
	if (m_nFrameCounter <= RESULT_SCENE_CHANGE_SCENE_COUNTER_WOLF) return;

	m_nFrameCounter = RESULT_SCENE_CHANGE_SCENE_COUNTER_WOLF;
}
