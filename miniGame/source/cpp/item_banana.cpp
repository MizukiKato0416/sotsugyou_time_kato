//=============================================================================
//
// �A�C�e���o�i�i���� [item_banana.cpp]
// Author : ��������
//
//=============================================================================
#include "item_banana.h"
#include "manager.h"
#include "sound.h"
#include "player.h"
#include "wallCylinder.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ITEM_BANANA_SIZE				(30.0f)		//�o�i�i�̃T�C�Y���a
#define ITEM_BANANA_ROTATE_SPEED		(0.05f)		//�o�i�i�̉�]�̑���
#define ITEM_BANANA_MOVE_SPEED			(5.0f)		//�o�i�i�̈ړ��̑���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CItemBanana::CItemBanana()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
//=============================================================================
CItemBanana::CItemBanana(CModel::MODELTYPE typeModel) : CItem(typeModel)
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemBanana::~CItemBanana()
{
	
}

//=============================================================================
// ��������
//=============================================================================
CItemBanana* CItemBanana::Create(D3DXVECTOR3 pos, CPlayer *pPlayer) {
	
	//�f�t�H���g�̃��f����ݒ�
	CItemBanana* pItemBanana;
	pItemBanana = new CItemBanana(CModel::MODELTYPE::OBJ_BANANA);
	if (pItemBanana == nullptr) return nullptr;

	pItemBanana->SetPos(pos);
	pItemBanana->m_pPlayer = pPlayer;
	pItemBanana->Init();

	return pItemBanana;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItemBanana::Init(void) {

	//�v���C���[�̌����擾
	float fRot = m_pPlayer->GetRot().y;

	//�ړ��ʂ̐ݒ�
	m_move.x = sinf(fRot + D3DX_PI) * ITEM_BANANA_MOVE_SPEED;
	m_move.z = cosf(fRot + D3DX_PI) * ITEM_BANANA_MOVE_SPEED;

	CItem::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CItemBanana::Uninit(void) {

	CItem::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemBanana::Update(void) {

	//�����擾
	D3DXVECTOR3 rot = GetRot();
	//��]������
	rot.y += ITEM_BANANA_ROTATE_SPEED;
	//�����ݒ�
	SetRot(rot);


	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 lastPos = GetPos();
	//�ړ��ʂ�ݒ�
	pos += m_move;

	//�ǂƂ̓����蔻��
	if (CWallCylinder::Collision(&pos, lastPos, ITEM_BANANA_SIZE))
	{
		//�������Ă��������
		Uninit();
		return;
	}

	//�ʒu�ݒ�
	SetPos(pos);

	//�v���C���[�Ƃ̓����蔻��
	if (CollisionPlayer(ITEM_BANANA_SIZE))
	{
		//�������Ă��������
		Uninit();
		return;
	}

	CItem::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CItemBanana::Draw(void) {
	CItem::Draw();
}

//=============================================================================
//�v���C���[�Ƀq�b�g�����Ƃ��̏���
//=============================================================================
void CItemBanana::HitPlayer(CPlayer * pPlayer)
{
	//�v���C���[���X�s����Ԃ���Ȃ�������
	if (pPlayer->GetState() != CPlayer::PLAYER_STATE::SPIN)
	{
		//�v���C���[�̏�Ԃ��X�s����Ԃɂ���
		pPlayer->SetState(CPlayer::PLAYER_STATE::SPIN);
	}
}