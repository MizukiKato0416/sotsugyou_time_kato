//=============================================================================
//
// �{������ [bom.cpp]
// Author : ��������
//
//=============================================================================
#include "bom.h"
#include "manager.h"
#include "sound.h"
#include "objectList.h"
#include "object_player_attack_car.h"
#include "sound.h"
#include "gameScene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BOM_PLAYER_COLL_SIZE	(30.0f)		//�v���C���[�̓����蔻��̑傫�����a
#define BOM_SIZE				(80.0f)		//�{���̃T�C�Y���a
#define BOM_GRAVITY				(0.1f)		//�{���̏d��
#define BOM_COLL_POS_Y			(20.0f)		//�����蔻������n�߂鍂��
#define BOM_COLL_PLAYER_BOUND	(150.0f)	//�v���C���[���΂���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CBom::CBom()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
//=============================================================================
CBom::CBom(CModel::MODELTYPE typeModel) : CObjectModel(typeModel, false)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBom::~CBom()
{
	
}

//=============================================================================
// ��������
//=============================================================================
CBom* CBom::Create(D3DXVECTOR3 pos) {

	//�f�t�H���g�̃��f����ݒ�
	CModel::MODELTYPE typeModel = CModel::MODELTYPE::OBJ_BOM;

	CBom* pBom;
	pBom = new CBom(typeModel);
	if (pBom == nullptr) return nullptr;

	pBom->SetPos(pos);
	
	pBom->Init();

	return pBom;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBom::Init(void) {

	//�ϐ�������
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CObjectModel::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBom::Uninit(void) {

	CObjectModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBom::Update(void) {

	//�Q�[���I�[�o�[�Ȃ�
	if (CManager::GetManager()->GetGameScene()->GetGameOver())
	{
		//����
		Uninit();
		return;
	}

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�d�͐ݒ�
	m_move.y -= BOM_GRAVITY;

	//�ړ��ʐݒ�
	pos += m_move;

	//�n�ʂɂ�����
	if (pos.y <= 0.0f)
	{
		//�������Đ�
		ExplosionSound();
		//����
		Uninit();
		return;
	}

	//�ʒu�ݒ�
	SetPos(pos);

	//�v���C���[�Ƃ̓����蔻��
	if (CollisionPlayer())
	{
		//�������Đ�
		ExplosionSound();
		//����
		Uninit();
		return;
	}

	CObjectModel::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBom::Draw(void) {
	CObjectModel::Draw();
}

//=============================================================================
//�v���C���[�Ƃ̓����蔻��
//=============================================================================
bool CBom::CollisionPlayer(void)
{
	CObject* pObject = GetObjectTopAll();	//�S�I�u�W�F�N�g�̃��X�g�̐擪���擾

	while (pObject != nullptr) {
		CObject* pObjNext = GetObjectNextAll(pObject);	//���X�g�̎��̃I�u�W�F�N�g�̃|�C���^���擾

		//�I�u�W�F�N�g�^�C�v�̊m�F
		bool bMatchType = false;
		if (pObject->GetObjType() & OBJTYPE_PLAYER) bMatchType = true;

		if (!bMatchType || GetPos().y > BOM_COLL_POS_Y)
		{
			pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
			continue;
		}

		//�v���C���[�ɃL���X�g
		CObjectPlayerAttackCar *pPlayer = static_cast<CObjectPlayerAttackCar*> (pObject);

		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 playerPos = pPlayer->GetPos();
		//���D�̈ʒu�擾
		D3DXVECTOR3 balloonPos = GetPos();

		//��_�̋����x�N�g��
		D3DXVECTOR2 differVec = D3DXVECTOR2(playerPos.x - balloonPos.x, playerPos.z - balloonPos.z);
		//��_�̋���
		float fDiffer = D3DXVec2Length(&differVec);

		//�������Ă�����
		if (fDiffer <= BOM_PLAYER_COLL_SIZE + BOM_SIZE)
		{
			float fRot = 0.0f;
			//�����������_���Ō��߂�
			fRot = (rand() % 629 + -314) / 100.0f;

			//����̃o�E���h�ړ��ʎ擾
			D3DXVECTOR3 move = pPlayer->GetBoundMove();
			//���˕Ԃ�����
			move.x += sinf(fRot) * BOM_COLL_PLAYER_BOUND;
			move.z += cosf(fRot) * BOM_COLL_PLAYER_BOUND;
			//����̃o�E���h�ړ��ʐݒ�
			pPlayer->SetBoundMove(move);
			return true;
		}

		pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
	}

	return false;
}

//=============================================================================
//�������Đ�
//=============================================================================
void CBom::ExplosionSound()
{
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�T�E���h�̎擾
	CSound *pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//���Đ�
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_EXPLOSION);
}
