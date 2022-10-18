//=============================================================================
//
// �A�C�e���o�i�i���� [item_banana.cpp]
// Author : ��������
//
//=============================================================================
#include "item_banana.h"
#include "manager.h"
#include "sound.h"
#include "object_player.h"
#include "wallCylinder.h"
#include "object2D.h"
//�G�t�F�N�g
#include "PresetSetEffect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ITEM_BANANA_SIZE				(50.0f)		//�o�i�i�̃T�C�Y���a
#define ITEM_BANANA_ROTATE_SPEED		(0.08f)		//�o�i�i�̉�]�̑���
#define ITEM_BANANA_MOVE_SPEED			(25.0f)		//�o�i�i�̈ړ��̑���

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
CItemBanana* CItemBanana::Create(D3DXVECTOR3 pos, CObjectPlayer *pPlayer) {
	
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

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�T�E���h�̎擾
	CSound *pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//���Đ�
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_BANANA_THROW);

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
		//�}�l�[�W���[�̎擾
		CManager* pManager = CManager::GetManager();
		//�T�E���h�̎擾
		CSound *pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//���Đ�
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_SPIN);

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
void CItemBanana::HitPlayer(CObjectPlayer * pPlayer)
{
	//�v���C���[���ʏ��Ԃ�������
	if (pPlayer->GetState() == CObjectPlayer::OBJECT_PLAYER_STATE::NORMAL)
	{
		//�v���C���[�̏�Ԃ��X�s����Ԃɂ���
		pPlayer->SetState(CObjectPlayer::OBJECT_PLAYER_STATE::SPIN);

		//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
		//�X�s��(�o�i�i�q�b�g)
		CPresetEffect::SetEffect3D(8, D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y + 10, pPlayer->GetPos().z), {}, {});		//�����
		//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	}
}