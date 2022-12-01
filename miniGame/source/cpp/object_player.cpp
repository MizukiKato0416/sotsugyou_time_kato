//=============================================================================
//
// �I�u�W�F�N�g�v���C���[���� [object_player.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "object_player.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "input.h"
#include "gameScene.h"

#include "wallCylinder.h"
#include "effect.h"
#include "object2D.h"
#include "billboard.h"
#include "item_banana.h"

#include "PresetSetEffect.h"
#include "score_ui.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================

//--------------------------------
//�����蔻��
//--------------------------------
#define COLLISION_RADIUS (40.0f)		//�����蔻��̔��a	�ǂƂ��Ɏg��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObjectPlayer::CObjectPlayer() : CObjectModel(CModel::MODELTYPE::OBJ_CAR, false)
{
	SetObjType(OBJTYPE_PLAYER);						//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);		//�X�V���̐ݒ�
	SetDrawPriority(DRAW_PRIORITY::CHARA);			//�`�揇�̐ݒ�
	m_itemType = CItem::ITEM_TYPE::NONE;

	//SetDrawStencilZ(true);
	m_pPlayer = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectPlayer::~CObjectPlayer()
{
	
}

//=============================================================================
// �v���C���[�̐�������
//=============================================================================
CObjectPlayer* CObjectPlayer::Create(D3DXVECTOR3 pos) {
	CObjectPlayer* pObjectPlayer;
	pObjectPlayer = new CObjectPlayer();
	if (pObjectPlayer == nullptr) return nullptr;

	pObjectPlayer->SetPos(pos);
	pObjectPlayer->Init();

	return pObjectPlayer;
}

//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CObjectPlayer::Init(void) {
	//�v���C���[�̏����ݒ�
	CObjectModel::SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();

	CObjectModel::Init();

	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create();


	//�v���C���[�ԍ��ɂ���ĐF��ς���
	switch (m_pPlayer->GetIndex())
	{
	case 1:
		col = OBJECT_PLAYER_COLOR_1P;
		break;
	case 2:
		col = OBJECT_PLAYER_COLOR_2P;
		break;
	case 3:
		col = OBJECT_PLAYER_COLOR_3P;
		break;
	case 4:
		col = OBJECT_PLAYER_COLOR_4P;
		break;
	default:
		break;
	}

	//���f���擾
	CModel *pModel = GetPtrModel();
	if (pModel!= nullptr)
	{
		//�w�肵���}�e���A���̐F��ݒ�
		pModel->SetMaterialDiffuse(col, 0);
		pModel->SetMaterialSpecular(col / 2.0f + D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), 0);
		pModel->SetMaterialPower(2.0f, 0);

	}

	return S_OK;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CObjectPlayer::Uninit(void) {
	//�I������
	CObjectModel::Uninit();
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void CObjectPlayer::Update(void) {
	//�X�V���Ȃ��ݒ�Ȃ�
	if (!m_pPlayer->GetUpdate())
	{
		return;
	}

	//----------------------------
	//���f���̍X�V
	//----------------------------
	CObjectModel::Update();
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CObjectPlayer::Draw(void) {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;
	//�����_���[�̎擾
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;

	CObjectModel::Draw();
}

//=============================================================================
// �v���C���[�̃Q�[���I�[�o�[���̏���
//=============================================================================
void CObjectPlayer::GameOver(void) {
	
}

//=============================================================================
// �v���C���[�̓����蔻��̔��a�̎擾
//=============================================================================
float CObjectPlayer::GetRadius(void) {
	return COLLISION_RADIUS;
}