//=============================================================================
//
// �A�C�e�������� [item_shield.cpp]
// Author : ��������
//
//=============================================================================
#include "item_shield.h"
#include "manager.h"
#include "sound.h"
#include "object_player_attack_car.h"
#include "player.h"
#include "input.h"
//�G�t�F�N�g
#include "PresetSetEffect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ITEM_SHIELD_SIZE				(50.0f)		//���̃T�C�Y���a
#define ITEM_SHIELD_GRAVITY				(0.12f)		//���̏d��
#define ITEM_SHIELD_DELETE_COUNT		(360)		//���̏�����܂ł̎���
#define ITEM_SHIELD_COLL_HEIGHT			(30.0f)		//�����蔻������n�߂鍂��
#define ITEM_SHIELD_ROTATE_SPEED		(0.08f)		//��]���x

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CItemShield::CItemShield()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_pSphereCover = nullptr;
}

//=============================================================================
// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
//=============================================================================
CItemShield::CItemShield(CModel::MODELTYPE typeModel) : CItem(typeModel)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_pSphereCover = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemShield::~CItemShield()
{
	
}

//=============================================================================
// ��������
//=============================================================================
CItemShield* CItemShield::Create(D3DXVECTOR3 pos) {
	
	//�f�t�H���g�̃��f����ݒ�
	CItemShield* pItemShield;
	pItemShield = new CItemShield(CModel::MODELTYPE::OBJ_ITEM_SHIELD);
	if (pItemShield == nullptr) return nullptr;

	pItemShield->SetPos(pos);
	pItemShield->Init();

	return pItemShield;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItemShield::Init(void) {

	//���̂̐���
	m_pSphereCover = CObjectModel::Create(CModel::MODELTYPE::OBJ_SPHERE_COVER, GetPos() , D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	if (m_pSphereCover != nullptr) {
		m_pSphereCover->SetDrawPriority(CObject::DRAW_PRIORITY::CLEAR);
		m_pSphereCover->SetDrawZTex(false);
		CModel* pModel = m_pSphereCover->GetPtrModel();
		if (pModel != nullptr) {
			pModel->SetColorGlow(D3DXCOLOR(0.0f, 1.0f, 0.8f, 1.0f));
			pModel->SetPowerGlow(1.5f);
		}
	}


	//�ϐ�������
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;

	CItem::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CItemShield::Uninit(void) {

	//����
	if (m_pSphereCover != nullptr)
	{
		m_pSphereCover->Uninit();
		m_pSphereCover = nullptr;
	}

	CItem::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemShield::Update(void) {

	m_nCounter++;
	if (m_nCounter > ITEM_SHIELD_DELETE_COUNT)
	{
		m_nCounter = 0;
		//����
		//Uninit();
		return;
	}

	//�ړ�����
	Move();

	//��]����
	Rotate();

	//�v���C���[�Ƃ̓����蔻��
	if (CollisionPlayer(ITEM_SHIELD_SIZE, ITEM_SHIELD_COLL_HEIGHT))
	{
		//�}�l�[�W���[�̎擾
		CManager* pManager = CManager::GetManager();
		//�T�E���h�̎擾
		CSound *pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//���Đ�
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);

		//�������Ă��������
		Uninit();
		return;
	}

	CItem::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CItemShield::Draw(void) {
	CItem::Draw();
}

//=============================================================================
// �ړ�����
//=============================================================================
void CItemShield::Move(void) {

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�d�͉��Z
	m_move.y -= ITEM_SHIELD_GRAVITY;
	//�ʒu���Z
	pos += m_move;

	//�n�ʂɂ�����
	if (pos.y < 0.0f)
	{
		//�~�߂�
		pos.y = 0.0f;
	}

	//�ʒu�ݒ�
	SetPos(pos);

	//���̂���������Ă�����
	if (m_pSphereCover != nullptr)
	{
		//�ʒu���A�C�e���ɍ��킹��
		m_pSphereCover->SetPos(pos);
	}
}

//=============================================================================
// ��]���� 
//=============================================================================
void CItemShield::Rotate(void) {

	//�����擾
	D3DXVECTOR3 rot = GetRot();
	//���Z
	rot.y += ITEM_SHIELD_ROTATE_SPEED;

	//�΂𒴂����Ƃ�
	if (rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	else if(rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}

	//�����ݒ�
	SetRot(rot);
}

//=============================================================================
//�v���C���[�Ƀq�b�g�����Ƃ��̏���
//=============================================================================
void CItemShield::HitPlayer(CObjectPlayer * pPlayer)
{
	//�v���C���[�ɃL���X�g
	CObjectPlayerAttackCar *pAttackCar = dynamic_cast<CObjectPlayerAttackCar*>(pPlayer);
	if (pAttackCar == nullptr)
	{
		return;
	}

	//�f�B�t�F���X��ԂłȂ��Ȃ�
	if (!pAttackCar->GetDefence())
	{
		//�f�B�t�F���X��Ԃɂ���
		pAttackCar->SetDefence(true);
	}
	//�f�B�t�F���X�J�E���^�[�����Z�b�g
	pAttackCar->SetDefenceCounter(0);
}