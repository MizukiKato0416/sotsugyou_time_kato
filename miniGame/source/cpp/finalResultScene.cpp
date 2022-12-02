//=============================================================================
//
// �ŏI���ʃV�[������ [finalResultScene.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "finalResultScene.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "finalResultCamera.h"
#include "fade.h"
#include "object2D.h"
#include "objectModel.h"
#include "score.h"
#include "gameScene.h"
#include "object_player.h"
#include "meshwall.h"
#include "ToScreen.h"
#include "next_button.h"
#include "float_object.h"
#include "skydome.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FINAL_RESULT_SCENE_NEXT_BUTTON_POS			(D3DXVECTOR3(1150.0f, 670.0f, 0.0f))	//���ɐi�ރ{�^���̈ʒu
#define FINAL_RESULT_SCENE_NEXT_BUTTON_SIZE			(D3DXVECTOR3(70.0f, 70.0f, 0.0f))		//���ɐi�ރ{�^���̃T�C�Y
#define FINAL_RESULT_SCENE_NEXT_BUTTON_COUNTER		(15)									//���ɐi�ރ{�^���̌�����悤�ɂȂ�܂ł̃J�E���^�[
#define FINAL_RESULT_SCENE_NEXT_BUTTON_DEC_ALPHA	(0.015f)								//���ɐi�ރ{�^���̃��l���Z��

#define FINAL_RESULT_SCENE_RESULT_UI_SIZE_X			(618.0f * 1.5f)		//���ʔ��\UI�̃T�C�YX
#define FINAL_RESULT_SCENE_RESULT_UI_SIZE_Y			(182.0f * 1.5f)		//���ʔ��\UI�̃T�C�YY
#define FINAL_RESULT_SCENE_RESULT_UI_INIT_SIZE_X	(618.0f * 5.0f)		//���ʔ��\UI�̏����T�C�YX
#define FINAL_RESULT_SCENE_RESULT_UI_INIT_SIZE_Y	(182.0f * 5.0f)		//���ʔ��\UI�̏����T�C�YY
#define FINAL_RESULT_SCENE_RESULT_UI_ADD_SIZE		(0.94f)				//���ʔ��\UI�̏����T�C�Y���Z��
#define FINAL_RESULT_SCENE_RESULT_UI_ADD_ALPHA		(0.1f)				//���ʔ��\UI�̃��l���Z��

#define FINAL_RESULT_SCENE_CLOUD_NUM_Y		(12)									//�_�̏c�̑���
#define FINAL_RESULT_SCENE_CLOUD_NUM_X		(10)									//�_�̉��̑���
#define FINAL_RESULT_SCENE_CLOUD_DIFFER		(float(rand() % 18401 + 1600))			//�_�̋���
#define FINAL_RESULT_SCENE_CLOUD_ROT		(float(rand() % 629 + -314) / 100.0f)	//�_�̐�������
#define FINAL_RESULT_SCENE_CLOUD_MIN_POS_Y	(-5000.0f)								//�_�̐����ʒuY�ŏ��l
#define FINAL_RESULT_SCENE_CLOUD_POS_Y		(800.0f)								//�_�̐����Ԋu
#define FINAL_RESULT_SCENE_CLOUD_POS_Y_RAND	(float(rand() % 1001 + -500))			//�_�̐����ʒuY�����_���l
#define FINAL_RESULT_SCENE_CLOUD_MOVE_SPEED	(-(float(rand() % 6 + 2) / 10000.0f))	//�_�̈ړ����x

#define FINAL_RESULT_SCENE_BALLOON_CREATE_POS			(-4000.0f)							//���D�̐����ʒu
#define FINAL_RESULT_SCENE_BALLOON_CREATE_POS_Y_RAND	(float(rand() % 1001 + -500))		//���D�̐����ʒuY�����_���l
#define FINAL_RESULT_SCENE_BALLOON_DIFFER				(float(rand() % 2801 + 1200))		//���D�̋���
#define FINAL_RESULT_SCENE_BALLOON_MOVE_SPEED			(float(rand() % 8 + 3))				//���D�̈ړ����x
#define FINAL_RESULT_SCENE_BALLOON_CREATE_INTERVAL		(5)									//���D�̐����Ԋu
#define FINAL_RESULT_SCENE_BALLOON_CREATE_NUM			(3)									//���D��1��ł̐�����
#define FINAL_RESULT_SCENE_BALLOON_UNINIT_POS_Y			(2000.0f)							//���D�̏����ʒu

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CFinalResultScene::m_aPlayerScore[MAX_OBJECT_PLAYER_NUM] = { 70, 30, 20, 10 };

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFinalResultScene::CFinalResultScene()
{
	m_nFadeTime = FPS;
	m_pTextResult = nullptr;
	m_fDifferCloud.clear();
	m_fRotCloud.clear();
	m_fMoveSpeedCloud.clear();
	m_pCloud.clear();
	m_pBalloon.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFinalResultScene::~CFinalResultScene()
{

}

//=============================================================================
// �ŏI���ʃV�[���̏���������
//=============================================================================
void CFinalResultScene::Init(void) {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�����_���[�̎擾
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//�J�����̐ݒ�
	if (pManager != nullptr) pManager->SetCamera(CFinalResultCamera::Create());

	//------------------------------
	//���C�g�̏����ݒ�
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ���C�g�̎ˉe�ϊ�
	//���C�g�̃v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 200.0f, 1800.0f);

	D3DXMATRIX mtxLightView;   // ���C�g�r���[�ϊ�
	D3DXVECTOR3 posLightV = D3DXVECTOR3(0.0f, 1200.0f, -1000.0f);	//���C�g�̎��_�̈ʒu
	D3DXVECTOR3 posLightR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���C�g�̒����_�̈ʒu
	D3DXVECTOR3 vecLight = -D3DXVECTOR3(posLightV - posLightR);		//���C�g�̃x�N�g��
	D3DXVec3Normalize(&vecLight, &vecLight);	//�x�N�g���𐳋K��
	//���C�g�̃r���[�}�g���b�N�X�𐶐�
	D3DXMatrixLookAtLH(&mtxLightView, &posLightV, &D3DXVECTOR3(posLightV + vecLight), &D3DXVECTOR3(0, 1, 0));
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
		//�o�b�N�o�b�t�@���t�H�O�̐F�ɍ��킹��
		pRenderer->SetBackBuffColor(D3DXCOLOR(0.1f, 0.7f, 1.0f, 1.0f));
	}

	//------------------------------
	//UI�̐���
	//------------------------------


	//------------------------------
	//���f���̐���
	//------------------------------
	//�_�̑���
	int nNumCloud = 0;
	//�_�̐���
	for (int nCntCloudY = 0; nCntCloudY < FINAL_RESULT_SCENE_CLOUD_NUM_Y; nCntCloudY++)
	{
		for (int nCntCloudX = 0; nCntCloudX < FINAL_RESULT_SCENE_CLOUD_NUM_X; nCntCloudX++, nNumCloud++)
		{
			//���S����̋����̐ݒ�
			m_fDifferCloud.push_back(FINAL_RESULT_SCENE_CLOUD_DIFFER);
			//�����������_���Ō��߂�
			m_fRotCloud.push_back(FINAL_RESULT_SCENE_CLOUD_ROT);

			//�����ʒu�̐ݒ�
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, FINAL_RESULT_SCENE_CLOUD_MIN_POS_Y + (FINAL_RESULT_SCENE_CLOUD_POS_Y * nCntCloudY), 0.0f);
			pos.y += FINAL_RESULT_SCENE_CLOUD_POS_Y_RAND;
			pos.x += cosf(m_fRotCloud[nNumCloud]) * m_fDifferCloud[nNumCloud];
			pos.z += sinf(m_fRotCloud[nNumCloud]) * m_fDifferCloud[nNumCloud];

			//�����̐ݒ�
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, D3DX_PI / 2.0f - m_fRotCloud[nNumCloud], 0.0f);

			//�_�̌����������_���ŗ��Ԃ�
			if (rand() % 2 == 0) rot.y += D3DX_PI;

			//���f���̎��
			int nModelNum = static_cast<int>(CModel::MODELTYPE::OBJ_RESULT_CLOUD_02) + 1 - static_cast<int>(CModel::MODELTYPE::OBJ_RESULT_CLOUD_00);

			//���f���������_���Őݒ�
			int nModel = (rand() % nModelNum) + static_cast<int>(CModel::MODELTYPE::OBJ_RESULT_CLOUD_00);

			m_pCloud.push_back(CObjectModel::Create(static_cast<CModel::MODELTYPE>(nModel), pos, rot, false));

			//�ړ����x��ݒ�
			m_fMoveSpeedCloud.push_back(FINAL_RESULT_SCENE_CLOUD_MOVE_SPEED);
		}
	}


	//�v���C���[�̃��f���̐���
	const float fDistPlayer = 400.0f;	//�v���C���[�̃��f���Ԃ̋���
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++) {
		D3DXVECTOR3 posPlayer = D3DXVECTOR3(-fDistPlayer * (MAX_OBJECT_PLAYER_NUM / 2.0f) + fDistPlayer / 2.0f + fDistPlayer * nIdxPlayer, 0.0f, 0.0f);	//�v���C���[�̈ʒu
		//�v���C���[�̃��f���̐���
		m_apObjPlayer[nIdxPlayer] = CObjectModel::Create(CModel::MODELTYPE::OBJ_CAR, posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
		//�v���C���[�̐F��ݒ�
		if (m_apObjPlayer[nIdxPlayer] == nullptr) continue;	//���[�v��΂�
		//�^���[�̐���
		m_apResultTower[nIdxPlayer] = CObjectModel::Create(CModel::MODELTYPE::OBJ_RESULT_TOWER, posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	
		//���f���̐ݒ�
		CModel* pModelPlayer = m_apObjPlayer[nIdxPlayer]->GetPtrModel();
		if (pModelPlayer == nullptr) continue;	//���[�v��΂�
		D3DXCOLOR colPlayer = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);	//�v���C���[�̐F

		switch (nIdxPlayer)
		{
		case 0:
			colPlayer = OBJECT_PLAYER_COLOR_1P;
			break;
		case 1:
			colPlayer = OBJECT_PLAYER_COLOR_2P;
			break;
		case 2:
			colPlayer = OBJECT_PLAYER_COLOR_3P;
			break;
		case 3:
			colPlayer = OBJECT_PLAYER_COLOR_4P;
			break;
		}

		//�}�e���A���̐F�̐ݒ�
		pModelPlayer->SetMaterialDiffuse(colPlayer, 0);
		//�X�y�L�����[�̐ݒ�
		pModelPlayer->SetMaterialSpecular(colPlayer / 2.0f + D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), 0);
		pModelPlayer->SetMaterialPower(2.0f, 0);
	}


	//BGM�̍Đ�
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_FINAL_RESULT);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_FINAL_RESULT);
	}

	m_phase = PHASE::PHASE_FIRST;	//�������Ȃ��t�F�[�Y

	//�I�u�W�F�N�g�̃|�[�Y�������悤�ɐݒ�
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
// �ŏI���ʃV�[���̏I������
//=============================================================================
void CFinalResultScene::Uninit(void) {
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
// �ŏI���ʃV�[���̍X�V����
//=============================================================================
void CFinalResultScene::Update(void) {

	//�_�̈ړ�����
	CloudMove();

	//���D��������
	CreateBalloon();

	//���D�̈ړ�����
	BalloonMove();

	//�t�F�[�Y���Ƃ̍X�V����
	switch (m_phase)
	{
	case CFinalResultScene::PHASE::PHASE_FIRST:
		PhaseFirst();
		break;
	case CFinalResultScene::PHASE::RISE_CAMERA:
		RiseCamera();
		break;
	case CFinalResultScene::PHASE::RESULT_TEXT:
		ResultText();
		break;
	case CFinalResultScene::PHASE::SHOW_SCORE_UI:
		ShowScoreUI();
		break;
	case CFinalResultScene::PHASE::RISE_TOWER:
		RiseTower();
		break;
	case CFinalResultScene::PHASE::WINNER:
		Winner();
		break;
	case CFinalResultScene::PHASE::PHASE_FINISH:
		PhaseFinish();
		break;
	}
}

//=============================================================================
// �t�F�[�Y�J�n����
//=============================================================================
void CFinalResultScene::PhaseFirst() {
	//�t�F�[�Y�̃J�E���g���Z
	m_nCntPhase++;
	//���̃t�F�[�Y�Ɉڍs
	if (m_nCntPhase >= 60) {
		m_nCntPhase = 0;
		m_phase = PHASE::RISE_CAMERA;
	}
}

//=============================================================================
// �J�����̏㏸����
//=============================================================================
void CFinalResultScene::RiseCamera() {
	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	CCamera* pCamera = pManager->GetCamera();	//�J�����ւ̃|�C���^
	if (pCamera == nullptr) return;

	//�t�F�[�Y�̃J�E���g���Z
	m_nCntPhase++;

	//�㏸
	D3DXVECTOR3 posCamera = pCamera->GetPos();	//�J�����̈ʒu�擾
	const float fMoveMaxY = 1.6f;	//�㏸�̑��x�i�ő�j
	float fMoveY = powf((float)m_nCntPhase, 2.f) * 0.001f;	//�㏸��
	//�ő�l�Œ���
	if (fMoveY > fMoveMaxY) fMoveY = fMoveMaxY;

	const float fSlowHeight = -100.0f;	//�������鍂��
	//����������
	if (posCamera.y > fSlowHeight) {
		fMoveY = -posCamera.y * (fMoveMaxY / -fSlowHeight);
	}

	//0�܂ŏ㏸������
	if (posCamera.y < 0.0f) {

		//�ʒu�㏸
		posCamera.y += fMoveY;	
		//0�ɋ߂Â����ꍇ���߂���
		if (posCamera.y > -0.01f) {
			posCamera.y = 0.0f;
		}
		//�ʒu�̐ݒ�
		pCamera->SetPos(posCamera);	
	}

	//��]
	D3DXVECTOR3 rotCamera = pCamera->GetRot();	//�J�����̊p�x�擾
	float fRotCameraLastY = rotCamera.y;	//��]������O�̊p�x

	float fRotSpeed = 0.013f;	//��]���x
	float fSlowRot = -0.2f;		//��������p�x

	//�������Ă��鎞�_�ŁA���ʃM���M���Ō���
	if (posCamera.y > fSlowHeight && rotCamera.y < 0.0f && rotCamera.y >= fSlowRot) {
		fRotSpeed = -rotCamera.y * (fRotSpeed / -fSlowRot);
		if (fRotSpeed < 0.001f) fRotSpeed = 0.001f;
	}

	rotCamera.y += fRotSpeed;	//��]
	//���ߕ��̒���
	if (rotCamera.y > D3DX_PI) {
		rotCamera.y -= D3DX_PI * 2.0f;
	}

	//��]�̏I��
	if (posCamera.y > fSlowHeight && rotCamera.y >= 0.0f && fRotCameraLastY <= 0.0f) {
		//��ɐ��ʂ���������
		rotCamera.y = 0.0f;
		//�t�F�[�Y�̕ύX
		m_phase = PHASE::RESULT_TEXT;
		//�J�E���g���Z�b�g
		m_nCntPhase = 0;
	}

	//�p�x�̔��f
	pCamera->SetRot(rotCamera);
}

//=============================================================================
// ���ʔ��\�̃e�L�X�g�\������
//=============================================================================
void CFinalResultScene::ResultText() {
	m_nCntPhase++;

	if (m_nCntPhase == 120) {
		//���ʔ��\�e�L�X�g�̕\��
		m_pTextResult = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
			                              CTexture::TEXTURE_TYPE::FINAL_RESULT_UI,
			                              FINAL_RESULT_SCENE_RESULT_UI_INIT_SIZE_X, FINAL_RESULT_SCENE_RESULT_UI_INIT_SIZE_Y);
		m_pTextResult->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
		if (pManager == nullptr) return;
		//�T�E���h�̎擾
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//�����Đ�
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_RESULT_UI);
	}

	if (m_pTextResult == nullptr) return;

	//�������ꂢ����

	

	//�T�C�Y�擾
	D3DXVECTOR3 size = m_pTextResult->GetSize();
	//�T�C�Y��傫������
	size *= FINAL_RESULT_SCENE_RESULT_UI_ADD_SIZE;
	if (size.x < FINAL_RESULT_SCENE_RESULT_UI_SIZE_X) size.x = FINAL_RESULT_SCENE_RESULT_UI_SIZE_X;
	if (size.y < FINAL_RESULT_SCENE_RESULT_UI_SIZE_Y) size.y = FINAL_RESULT_SCENE_RESULT_UI_SIZE_Y;
	//�T�C�Y�ݒ�
	m_pTextResult->SetSize(size);

	//�t�F�[�Y�؂�ւ�
	if (m_nCntPhase > 300) {

		//�J���[�擾
		D3DXCOLOR col = m_pTextResult->GetColor();
		//���l���Z
		col.a -= FINAL_RESULT_SCENE_RESULT_UI_ADD_ALPHA;
		//�J���[�ݒ�
		m_pTextResult->SetColor(col);

		if (col.a < 0.0f)
		{
			//�t�F�[�Y�̕ύX
			m_phase = PHASE::SHOW_SCORE_UI;

			//���ʔ��\�e�L�X�g�̔j��
			m_pTextResult->Uninit();
			m_pTextResult = nullptr;
			//�J�E���g���Z�b�g
			m_nCntPhase = 0;
			return;
		}
	}
	else
	{
		//�J���[�擾
		D3DXCOLOR col = m_pTextResult->GetColor();
		//���l���Z
		col.a += FINAL_RESULT_SCENE_RESULT_UI_ADD_ALPHA;
		if (col.a > 1.0f) col.a = 1.0f;
		//�J���[�ݒ�
		m_pTextResult->SetColor(col);
	}
}

//=============================================================================
// �X�R�A��UI�\������
//=============================================================================
void CFinalResultScene::ShowScoreUI() {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	m_nCntPhase++;

	bool bWolfMode = CGameScene::GetWereWolfMode();	//�l�T���[�h�̃t���O

	//�X�R�AUI�̕\��
	for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
	{
		//�����^�C�~���O
		if (m_nCntPhase == 120 + nCnt * 30 || (!bWolfMode && m_nCntPhase == 1)) {
			float fPosX = WorldToScreen(m_apObjPlayer[nCnt]->GetPos()).x;	//�v���C���[�̃��f���̈ʒu���X�N���[�����W�ɕϊ����Ă����W���擾
			//�X�R�A�̐���
			m_apScoreResult[nCnt] = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_004, D3DXVECTOR3(fPosX + 3 / 2.0f * 30.0f, 600.0f, 0.0f), 30.0f);

			//�ʏ탂�[�h�̏ꍇ��\��
			if (m_apScoreResult[nCnt] != nullptr && !CGameScene::GetWereWolfMode()) {
				m_apScoreResult[nCnt]->SetNumberColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			}
			//�l�T���[�h
			else {
				//�X�R�A�̔w�i�̐ݒ�
				CObject2D* pScoreBG = CObject2D::Create(D3DXVECTOR3(fPosX, 600.0f + 30.0f / 2, 0.0f), 
					(CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_TYPE::ITEM_UI_FRAME_1 + nCnt), 100.0f, 40.0f);
				if (pScoreBG != nullptr) pScoreBG->SetDrawPriority(CObject::DRAW_PRIORITY::UI_BG);
				//���̍Đ�
				if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);
			}
		}
	}

	//�t�F�[�Y�؂�ւ�
	if (m_nCntPhase > 270 || (!bWolfMode && m_nCntPhase == 120)) {
		//�t�F�[�Y�̕ύX
		m_phase = PHASE::RISE_TOWER;
		//�J�E���g���Z�b�g
		m_nCntPhase = 0;
	}
}

//=============================================================================
// �^���[�̏㏸����
//=============================================================================
void CFinalResultScene::RiseTower() {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�J�����̎擾
	CCamera* pCamera = nullptr;
	if (pManager != nullptr) pCamera = pManager->GetCamera();

	bool bNextPhase = true;	//���̃t�F�[�Y�ֈڍs

	m_nCntPhase++;

	const float fSpeedRise = 2.0f;	//�㏸���x

	for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
	{
		//�X�R�A�������ꍇ�I��
		if (m_apScoreResult[nCnt] == nullptr) continue;

		//�X�R�A�����łɏ���̏ꍇ�I��
		if (m_apScoreResult[nCnt]->GetScore() >= m_aPlayerScore[nCnt]) {
			//�X�R�A���O�̏ꍇ��̏������ʂ�Ȃ��̂ŁA��~���̏������ŏ��ɍs��
			if (m_nCntPhase == 1 && m_apScoreResult[nCnt]->GetScore() == 0) {
				//�^���[��~���̏���
				StopTower(nCnt);
			}
			continue;
		}

		//�܂��I����Ă��Ȃ��ꍇ�t�F�[�Y�ڍs���Ȃ�
		bNextPhase = false;

		//���ƃv���C���[���㏸
		if (m_apObjPlayer[nCnt] != nullptr) {
			D3DXVECTOR3 posPlayer = m_apObjPlayer[nCnt]->GetPos();
			posPlayer.y += fSpeedRise;
			m_apObjPlayer[nCnt]->SetPos(posPlayer);
		}
		if (m_apResultTower[nCnt] != nullptr) {
			D3DXVECTOR3 posTower = m_apResultTower[nCnt]->GetPos();
			posTower.y += fSpeedRise;
			m_apResultTower[nCnt]->SetPos(posTower);
		}

		//�X�R�AUI�̒l�̏㏸
		const int nSpanAddScore = 6;
		if(m_nCntPhase % nSpanAddScore == 0) m_apScoreResult[nCnt]->AddScore(1);	//���t���[�����Ɉ�x������
		//�ő�X�R�A�̍X�V
		m_nTopScore = max(m_nTopScore, m_apScoreResult[nCnt]->GetScore());

		//�X�R�A���㏸�����ꍇ�X�g�b�v
		if (m_apScoreResult[nCnt]->GetScore() >= m_aPlayerScore[nCnt]) {
			//�^���[��~���̏���
			StopTower(nCnt);
		}
	}

	//���̃t�F�[�Y�ֈڍs
	if (bNextPhase) {
		//�t�F�[�Y�̕ύX
		m_phase = PHASE::WINNER;
		//�J�E���g���Z�b�g
		m_nCntPhase = 0;
	}
	else if (pCamera != nullptr) {
		D3DXVECTOR3 posCamera = pCamera->GetPos();
		posCamera.y += fSpeedRise;
		//�J�����̈ړ�
		pCamera->SetPos(posCamera);
	}
}

//�^���[��~���̏���
void CFinalResultScene::StopTower(int nIdxPlayer) {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//���̍Đ�
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);
	//�G�t�F�N�g

	//���ʂ̃e�N�X�`���o���Ă���������

	//�l�T���[�h�̏ꍇ�X�R�A�̐F��ύX
	if (m_apScoreResult[nIdxPlayer] != nullptr && CGameScene::GetWereWolfMode()) m_apScoreResult[nIdxPlayer]->SetNumberColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
}

//=============================================================================
// �_�ړ�����
//=============================================================================
void CFinalResultScene::CloudMove()
{
	//�_�̑����擾
	int nCloudNum = m_pCloud.size();

	for (int nCntCloud = 0; nCntCloud < nCloudNum; nCntCloud++)
	{
		//�ʒu�擾
		D3DXVECTOR3 pos = m_pCloud[nCntCloud]->GetPos();
		//�������Ă�����������炷
		m_fRotCloud[nCntCloud] += m_fMoveSpeedCloud[nCntCloud];
		if (m_fRotCloud[nCntCloud] > D3DX_PI) m_fRotCloud[nCntCloud] -= D3DX_PI * 2.0f;

		//�ʒu���v�Z
		pos.x = cosf(m_fRotCloud[nCntCloud]) * m_fDifferCloud[nCntCloud];
		pos.z = sinf(m_fRotCloud[nCntCloud]) * m_fDifferCloud[nCntCloud];

		//�ʒu�ݒ�
		m_pCloud[nCntCloud]->SetPos(pos);

		//�����擾
		D3DXVECTOR3 rot = m_pCloud[nCntCloud]->GetRot();
		//���������炷
		rot.y -= m_fMoveSpeedCloud[nCntCloud];
		if (rot.y < -D3DX_PI) rot.y += D3DX_PI * 2.0f;
		//�����ݒ�
		m_pCloud[nCntCloud]->SetRot(rot);
	}
}

//=============================================================================
// ����
//=============================================================================
void CFinalResultScene::Winner() {
	m_nCntPhase++;

	const int nTimeCreateCrown = 180;
	const float fposCrownFirst = 500.0f;	//�����̏����ʒu�i�v���C���[�̈ʒu����̍����j

	if (m_nCntPhase == nTimeCreateCrown) {
		//�����~��Ă�����
		for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
		{
			if (m_apScoreResult[nCnt] == nullptr || m_apObjPlayer[nCnt] == nullptr) continue;
			if (m_apScoreResult[nCnt]->GetScore() != m_nTopScore) continue;

			D3DXVECTOR3 posPlayer = m_apObjPlayer[nCnt]->GetPos();	//�v���C���[�̈ʒu���擾
			posPlayer.y += fposCrownFirst;	//������ǉ�
			//�����𐶐�
			CObjectModel* pObjCrown = CObjectModel::Create(CModel::MODELTYPE::OBJ_RESULT_CROWN, posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
			//�I�u�W�F�N�g�̐ݒ�
			if (pObjCrown == nullptr) continue;	//���[�v��΂�
			m_vObjCrown.push_back(pObjCrown);	//���X�g�Ɋi�[
			pObjCrown->SetRotSpeed(D3DXVECTOR3(0.0f, 0.05f, 0.0f));	//��]������
			//���f���̐ݒ�
			CModel* pModel = pObjCrown->GetPtrModel();
			if (pModel == nullptr) continue;	//���[�v��΂�
			for (int i = 0; i < 3; i++)
			{
				pModel->SetMaterialSpecular(D3DXCOLOR(0.98f, 0.98f, 0.98f, 1.f), i);
				pModel->SetMaterialPower(8.0f, i);
			}
		}
		//������~���Ă�����

	}

	//�����̈ړ�
	const float fposCrownDest = 100.0f;	//�����̖ڕW�̈ʒu�i�v���C���[�̈ʒu����̍����j
	const int nTimeFallCrown = 60;	//�����������Ă��鎞��

	//���������ォ�琔�b����������
	if (m_nCntPhase > nTimeCreateCrown && m_nCntPhase < nTimeCreateCrown + nTimeFallCrown) {
		for (auto& pCrown : m_vObjCrown)
		{
			if (pCrown == nullptr) continue;
			D3DXVECTOR3 posCrown = pCrown->GetPos();
			posCrown.y -= (fposCrownFirst - fposCrownDest) / nTimeFallCrown;
			//�ʒu�̐ݒ�
			pCrown->SetPos(posCrown);
		}
	}

	//�t�F�[�Y�I��
	if (m_nCntPhase == 180 + nTimeFallCrown) {
		//�t�F�[�Y�̕ύX
		m_phase = PHASE::PHASE_FINISH;
		//�J�E���g���Z�b�g
		m_nCntPhase = 0;

		//���փ{�^���̐���
		CNextButton::Create(FINAL_RESULT_SCENE_NEXT_BUTTON_POS, FINAL_RESULT_SCENE_NEXT_BUTTON_SIZE,
		                    CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_3, FINAL_RESULT_SCENE_NEXT_BUTTON_COUNTER,
		                    FINAL_RESULT_SCENE_NEXT_BUTTON_DEC_ALPHA);
	}
}

//=============================================================================
// �t�F�[�Y�I������
//=============================================================================
void CFinalResultScene::PhaseFinish() {
	CManager* pManager = CManager::GetManager();	//�}�l�[�W���[�̎擾
	if (pManager == nullptr) return;
	CInput* pInput = pManager->GetInputCur();	//���̓f�o�C�X�ւ̃|�C���^
	CFade* pFade = pManager->GetFade();			//�t�F�[�h�ւ̃|�C���^
	CSound* pSound = pManager->GetSound();		//�T�E���h�ւ̃|�C���^

	//null�̏ꍇ�I��
	if (pFade == nullptr) return;

	//����L�[�������ꂽ�Ƃ�
	if (m_bEndScene)
	{
		// �J�ڂ��鎞�Ԃ�0��菬�����Ȃ��Ă�����
		if (m_nFadeTime < 0)
		{
			//�V�[���J�ڊJ�n			
			pFade->SetFade(CScene::SCENE_TYPE::SELECT_GAME, 0.02f, 60);
			//pFade->SetFade(CScene::SCENE_TYPE::FINAL_RESULT, 0.02f, 60);
		}
		else
		{
			//�t�F�[�h�J�n�J�E���g����
			m_nFadeTime--;
		}

		//���͏������󂯕t�����I��
		return;
	}


	//null�̏ꍇ�I��
	if (pInput == nullptr) return;

	//����L�[���������Ƃ�
	if (pInput->GetTrigger(CInput::CODE::SELECT, 0))
	{
		// �����ꂽ�t���O
		m_bEndScene = true;
		//���艹�̍Đ�
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
	}
}

//=============================================================================
//���D��������
//=============================================================================
void CFinalResultScene::CreateBalloon()
{
	m_fBalloonCreateCounter++;
	if (m_fBalloonCreateCounter <= FINAL_RESULT_SCENE_BALLOON_CREATE_INTERVAL) return;

	for (int nCntBalloon = 0; nCntBalloon < FINAL_RESULT_SCENE_BALLOON_CREATE_NUM; nCntBalloon++)
	{
		//��������ꏊ�̐ݒ�
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, FINAL_RESULT_SCENE_BALLOON_CREATE_POS, 0.0f);
		//�����ꏊ�̐ݒ�

		//���S����̋����̐ݒ�
		float fDiffer = FINAL_RESULT_SCENE_BALLOON_DIFFER;
		//�����������_���Ō��߂�
		float fRot = FINAL_RESULT_SCENE_CLOUD_ROT;

		//�����ʒu�̐ݒ�
		pos.y += FINAL_RESULT_SCENE_BALLOON_CREATE_POS_Y_RAND;
		pos.x += cosf(fRot) * fDiffer;
		pos.z += sinf(fRot) * fDiffer;

		//�ړ��ʂ�ݒ�
		float fMoveSpeed = FINAL_RESULT_SCENE_BALLOON_MOVE_SPEED;

		//���f���̎��
		int nModelNum = static_cast<int>(CModel::MODELTYPE::OBJ_RESULT_BALLOON_02) + 1 - static_cast<int>(CModel::MODELTYPE::OBJ_RESULT_BALLOON_00);

		//���f���������_���Őݒ�
		int nModel = (rand() % nModelNum) + static_cast<int>(CModel::MODELTYPE::OBJ_RESULT_BALLOON_00);


		//���D�̐���
		CFloatObject* pBallon = CFloatObject::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, fMoveSpeed, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), static_cast<CModel::MODELTYPE>(nModel));
		//���D�̐ݒ�
		if (pBallon != nullptr) {
			//�X�y�L�����[�̐ݒ�
			CModel *pModel = pBallon->GetPtrModel();
			if (pModel != nullptr)
			{
				const D3DXCOLOR colSpecular = D3DXCOLOR(0.98f, 0.98f, 0.98f, 1.0f);	//�X�y�L�����[�̐F
				for (int nIdxMat = 0; nIdxMat < MAX_MATERIAL; nIdxMat++)
				{
					pModel->SetMaterialSpecular(colSpecular, nIdxMat);
					pModel->SetMaterialPower(12.0f, nIdxMat);
				}
			}
			//���X�g�ɕ��D��ǉ�
			m_pBalloon.push_back(pBallon);
		}
	}
	
	//������
	m_fBalloonCreateCounter = 0;
}

//=============================================================================
//���D�ړ�����
//=============================================================================
void CFinalResultScene::BalloonMove()
{
	//���D�̑����擾
	int nNum = m_pBalloon.size();

	for (int nCntBalloon = 0; nCntBalloon < nNum; nCntBalloon++)
	{
		//�ʒu�擾
		D3DXVECTOR3 pos = m_pBalloon[nCntBalloon]->GetPos();

		if (pos.y < FINAL_RESULT_SCENE_BALLOON_UNINIT_POS_Y) continue;
		//����ɂȂ�����
		//����
		m_pBalloon[nCntBalloon]->Uninit();
		m_pBalloon[nCntBalloon] = nullptr;
		m_pBalloon.erase(m_pBalloon.begin() + nCntBalloon);

		//���������炷
		nNum--;
		nCntBalloon--;
	}
}