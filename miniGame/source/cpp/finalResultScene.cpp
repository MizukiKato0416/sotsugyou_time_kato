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

#include "object_player.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFinalResultScene::CFinalResultScene()
{
	m_nFadeTime = FPS;
	m_pTextResult = nullptr;
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
	}

	//------------------------------
	//UI�̐���
	//------------------------------


	//------------------------------
	//���f���̐���
	//------------------------------
	const float fDistPlayer = 400.0f;	//�v���C���[�̃��f���Ԃ̋���
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++) {
		D3DXVECTOR3 posPlayer = D3DXVECTOR3(-fDistPlayer * (MAX_OBJECT_PLAYER_NUM / 2.0f) + fDistPlayer / 2.0f + fDistPlayer * nIdxPlayer, 0.0f, 0.0f);	//�v���C���[�̈ʒu
		//�v���C���[�̃��f���̐���
		m_apObjPlayer[nIdxPlayer] = CObjectModel::Create(CModel::MODELTYPE::OBJ_CAR, posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
		//�v���C���[�̐F��ݒ�
		if (m_apObjPlayer[nIdxPlayer] != nullptr) {
			CModel* pModelPlayer = m_apObjPlayer[nIdxPlayer]->GetPtrModel();
			if (pModelPlayer != nullptr) {
				D3DXCOLOR colPlayer = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);

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

				pModelPlayer->SetMaterialDiffuse(colPlayer, 0);
			}
		}
		//�^���[�̐���
		m_apResultTower[nIdxPlayer] = CObjectModel::Create(CModel::MODELTYPE::OBJ_RESULT_TOWER, posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	}


	//BGM�̍Đ�
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_TITLE);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_TITLE);
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
	const float fMoveMaxY = 2.0f, fMoveMinY = 0.2f;	//�㏸�̑��x�i�ő�A�Œ�j
	float fMoveY = powf((float)m_nCntPhase, 2.f) * 0.00005f;	//�㏸��
	if (fMoveY > fMoveMaxY) fMoveY = fMoveMaxY;

	//0�܂ŏ㏸������
	if (posCamera.y < 0.0f) {
		//����������
		if (posCamera.y > -200.0f) {
			fMoveY = -posCamera.y * 0.01f;
			if (fMoveY < fMoveMinY) fMoveY = fMoveMinY;
		}
		//�ʒu�㏸
		posCamera.y += fMoveY;	
		//0�ɋ߂Â����ꍇ���߂���
		if (posCamera.y > 0.0f) {
			posCamera.y = 0.0f;
		}
		//�ʒu�̐ݒ�
		pCamera->SetPos(posCamera);	
	}

	//��]
	D3DXVECTOR3 rotCamera = pCamera->GetRot();	//�J�����̊p�x�擾
	float fRotCameraLastY = rotCamera.y;	//��]������O�̊p�x

	float fRotSpeed = 0.01f;	//��]���x

	//�ڕW�n�_�܂ŃJ�������o�����ꍇ�A���ʃM���M���Ō���
	if (posCamera.y >= 0.0f && rotCamera.y < 0.0f && rotCamera.y >= -0.2f) {
		fRotSpeed = -rotCamera.y * 0.05f;
		if (fRotSpeed < 0.001f) fRotSpeed = 0.001f;
	}

	rotCamera.y += fRotSpeed;	//��]
	//���ߕ��̒���
	if (rotCamera.y > D3DX_PI) {
		rotCamera.y -= D3DX_PI * 2.0f;
	}

	//��]�̏I��
	if (posCamera.y >= 0.0f && rotCamera.y >= 0.0f && fRotCameraLastY <= 0.0f) {
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
		m_pTextResult = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 200.0f, 0.0f), CTexture::TEXTURE_TYPE::TEXT_TITLENAME_BALLOON, 400.0f, 100.0f);
	}

	//�t�F�[�Y�؂�ւ�
	if (m_nCntPhase > 300) {
		//�t�F�[�Y�̕ύX
		m_phase = PHASE::SHOW_SCORE_UI;

		//���ʔ��\�e�L�X�g�̔j��
		if (m_pTextResult != nullptr) {
			m_pTextResult->Uninit();
			m_pTextResult = nullptr;
		}


		//�J�E���g���Z�b�g
		m_nCntPhase = 0;
	}
}

//=============================================================================
// �X�R�A��UI�\������
//=============================================================================
void CFinalResultScene::ShowScoreUI() {
	m_nCntPhase++;

	if (m_nCntPhase == 120) {
		//�X�R�AUI�̕\��
		for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
		{
			m_apScoreResult[nCnt] = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_001, D3DXVECTOR3(300.0f + nCnt * 300.0f, 600.0f, 0.0f), 30.0f);
		}
	}

	//�t�F�[�Y�؂�ւ�
	if (m_nCntPhase > 120) {
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