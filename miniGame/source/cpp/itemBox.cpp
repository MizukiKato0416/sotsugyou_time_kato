//=============================================================================
//
// �A�C�e���{�b�N�X���� [itemBox.cpp]
// Author : ��������
//
//=============================================================================
#include "itemBox.h"
#include "manager.h"
#include "sound.h"
#include "objectList.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ITEMBOX_PLAYER_COLL_SIZE	(30.0f)		//�v���C���[�̓����蔻��̑傫�����a
#define ITEMBOX_SIZE				(50.0f)		//�A�C�e���{�b�N�X�̃T�C�Y���a
#define ITEMBOX_UNINIT_POS_X		(1200.0f)	//������ʒu
#define ITEMBOX_UNINIT_POS_Z		(1200.0f)	//������ʒu

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CItemBox::m_nNum = 0;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CItemBox::CItemBox()
{
	m_nNum++;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
//=============================================================================
CItemBox::CItemBox(CModel::MODELTYPE typeModel) : CObjectModel(typeModel, false)
{
	m_nNum++;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemBox::~CItemBox()
{
	m_nNum--;
}

//=============================================================================
// ��������
//=============================================================================
CItemBox* CItemBox::Create(D3DXVECTOR3 pos) {

	//�f�t�H���g�̃��f����ݒ�
	CModel::MODELTYPE typeModel = CModel::MODELTYPE::OBJ_ITEM_BOX;

	CItemBox* pItemBox;
	pItemBox = new CItemBox(typeModel);
	if (pItemBox == nullptr) return nullptr;

	pItemBox->SetPos(pos);
	
	pItemBox->Init();

	return pItemBox;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItemBox::Init(void) {

	//�ϐ�������
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CObjectModel::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CItemBox::Uninit(void) {

	CObjectModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemBox::Update(void) {

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�ړ��ʐݒ�
	pos += m_move;

	//�͈͂���o����
	if (pos.x > ITEMBOX_UNINIT_POS_X || pos.x < -ITEMBOX_UNINIT_POS_X ||
		pos.z > ITEMBOX_UNINIT_POS_Z || pos.z < -ITEMBOX_UNINIT_POS_Z)
	{
		//����
		Uninit();
		return;
	}

	//�ʒu�ݒ�
	SetPos(pos);

	//���悤�ɂ���
	SetRotSpeed(D3DXVECTOR3(0.0f, 0.01f, 0.0f));

	//�v���C���[�Ƃ̓����蔻��
	if (CollisionPlayer())
	{
		//�������Ă��������
		Uninit();
		return;
	}

	CObjectModel::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CItemBox::Draw(void) {
	CObjectModel::Draw();
}

//=============================================================================
//�v���C���[�Ƃ̓����蔻��
//=============================================================================
bool CItemBox::CollisionPlayer(void)
{
	CObject* pObject = GetObjectTopAll();	//�S�I�u�W�F�N�g�̃��X�g�̐擪���擾
	D3DXVECTOR3 posBullet = GetPos();	//�e�̈ʒu

	while (pObject != nullptr) {
		CObject* pObjNext = GetObjectNextAll(pObject);	//���X�g�̎��̃I�u�W�F�N�g�̃|�C���^���擾

		//�I�u�W�F�N�g�^�C�v�̊m�F
		bool bMatchType = false;
		if (pObject->GetObjType() & OBJTYPE_PLAYER) bMatchType = true;

		if (!bMatchType)
		{
			pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
			continue;
		}

		//�v���C���[�ɃL���X�g
		CPlayer *pPlayer = static_cast<CPlayer*> (pObject);

		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 playerPos = pPlayer->GetPos();
		//���D�̈ʒu�擾
		D3DXVECTOR3 balloonPos = GetPos();

		//��_�̋����x�N�g��
		D3DXVECTOR2 differVec = D3DXVECTOR2(playerPos.x - balloonPos.x, playerPos.z - balloonPos.z);
		//��_�̋���
		float fDiffer = D3DXVec2Length(&differVec);

		//�������Ă�����
		if (fDiffer <= ITEMBOX_PLAYER_COLL_SIZE + ITEMBOX_SIZE)
		{
			//�����A�C�e���������Ă��Ȃ���ԂȂ�
			if (pPlayer->GetItemType() == CItem::ITEM_TYPE::NONE)
			{
				//�A�C�e���̒����烉���_���Ŏ擾������
				int nRandItem = rand() % int(int(CItem::ITEM_TYPE::MAX) - 1) + 1;

				//�A�C�e�����擾������
				pPlayer->SetItemType((CItem::ITEM_TYPE)nRandItem);
			}
			return true;
		}

		pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
	}

	return false;
}