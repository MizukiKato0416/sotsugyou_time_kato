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

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFindWolfScene::CFindWolfScene()
{	
	memset(m_apScoreUi, NULL, sizeof(m_apScoreUi[MAX_OBJECT_PLAYER_NUM]));
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
	}

	//------------------------------
	//�I�u�W�F�N�g�̏����ݒ�
	//------------------------------
	//CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::BG_RESULT, SCREEN_WIDTH, SCREEN_HEIGHT);

	//�X�^�W�A���̐���
	CObjectModel::Create(CModel::MODELTYPE::OBJ_ATTACK_CAR_STAGE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		const float fDist = 180.0f;	//�v���C���[���m�̋���
		D3DXVECTOR3 posModel = D3DXVECTOR3(fDist * (-MAX_OBJECT_PLAYER_NUM / 2.0f) + fDist / 2.0f + nIdxPlayer * fDist, 0.0f, 0.0f);	//���[������ׂ�
		CObjectModel* pPlayerModel = CObjectModel::Create(CModel::MODELTYPE::OBJ_CAR, posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		if (pPlayerModel == nullptr) continue;
		CModel* pModel = pPlayerModel->GetPtrModel();

		D3DXVECTOR3 posPlayerIndex = WorldToScreen(posModel);

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
		CObject2D *pPlayerIndexUi = CObject2D::Create(posPlayerIndex + D3DXVECTOR3(0.0f, 100.0f, 0.0f), CTexture::TEXTURE_TYPE::PLAYER_NUM_1,
			                                          201.0f * 0.5f, 181.0f * 0.5f);
		pPlayerIndexUi->SetTexType(static_cast<CTexture::TEXTURE_TYPE>
			                       (static_cast<int> (CTexture::TEXTURE_TYPE::PLAYER_NUM_1) + nIdxPlayer));

		//�X�R�AUI�̐��� 
		m_apScoreUi[nIdxPlayer] = CScoreUi::Create(D3DXVECTOR3(SCREEN_WIDTH / (MAX_OBJECT_PLAYER_NUM + 1) * (nIdxPlayer + 1), 50.0f, 0.0f),
			                                       D3DXVECTOR3(0.5f, 0.5f, 0.5f), nIdxPlayer + 1);
		//�X�R�A�̐ݒ�
		m_apScoreUi[nIdxPlayer]->GetScore()->SetScore(40 - (CGameScene::GetRanking(nIdxPlayer) - 1) * 10);
	}

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
	
}