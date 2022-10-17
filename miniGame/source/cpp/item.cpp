//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : ��������
//
//=============================================================================
#include "item.h"
#include "manager.h"
#include "sound.h"
#include "objectList.h"
#include "player.h"

//�G�t�F�N�g
#include "PresetSetEffect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ITEM_PLAYER_COLL_SIZE	(30.0f)		//�v���C���[�̓����蔻��̑傫�����a

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CItem::CItem()
{
	m_pPlayer = nullptr;
}

//=============================================================================
// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
//=============================================================================
CItem::CItem(CModel::MODELTYPE typeModel) : CObjectModel(typeModel, false)
{
	m_pPlayer = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItem::~CItem()
{
	
}

//=============================================================================
// ��������
//=============================================================================
CItem* CItem::Create(D3DXVECTOR3 pos, const CPlayer *pPlayer) {
	
	//�f�t�H���g�̃��f����ݒ�
	CModel::MODELTYPE typeModel = CModel::MODELTYPE::OBJ_ITEM_BOX;

	CItem* pItem;
	pItem = new CItem(typeModel);
	if (pItem == nullptr) return nullptr;

	pItem->SetPos(pos);
	
	pItem->Init();

	return pItem;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItem::Init(void) {

	//�����A�C�e���������Ă��Ȃ���Ԃɂ���
	m_pPlayer->SetItemType(ITEM_TYPE::NONE);

	CObjectModel::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CItem::Uninit(void) {

	CObjectModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CItem::Update(void) {

	CObjectModel::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CItem::Draw(void) {
	CObjectModel::Draw();
}

//=============================================================================
//�v���C���[�Ƀq�b�g�����Ƃ��̏���
//=============================================================================
void CItem::HitPlayer(CPlayer * pPlayer)
{
}

//=============================================================================
//�v���C���[�Ƃ̓����蔻��
//=============================================================================
bool CItem::CollisionPlayer(const float fMySize)
{
	CObject* pObject = GetObjectTopAll();	//�S�I�u�W�F�N�g�̃��X�g�̐擪���擾
	D3DXVECTOR3 posBullet = GetPos();	//�e�̈ʒu

	while (pObject != nullptr) {
		CObject* pObjNext = GetObjectNextAll(pObject);	//���X�g�̎��̃I�u�W�F�N�g�̃|�C���^���擾

		//�v���C���[�ɃL���X�g
		CPlayer *pPlayer = static_cast<CPlayer*> (pObject);

		//�I�u�W�F�N�g�^�C�v�̊m�F
		bool bMatchType = false;
		if ((pObject->GetObjType() & OBJTYPE_PLAYER) && m_pPlayer != pPlayer) bMatchType = true;

		if (!bMatchType || pPlayer == nullptr)
		{
			pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
			continue;
		}

		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 playerPos = pPlayer->GetPos();
		//���D�̈ʒu�擾
		D3DXVECTOR3 balloonPos = GetPos();

		//��_�̋����x�N�g��
		D3DXVECTOR2 differVec = D3DXVECTOR2(playerPos.x - balloonPos.x, playerPos.z - balloonPos.z);
		//��_�̋���
		float fDiffer = D3DXVec2Length(&differVec);

		//�������Ă�����
		if (fDiffer <= ITEM_PLAYER_COLL_SIZE + fMySize)
		{
			//�q�b�g������
			HitPlayer(pPlayer);

			//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
			//�X�s��(�o�i�i�q�b�g)
			CPresetEffect::SetEffect3D(8, D3DXVECTOR3(GetPos().x, GetPos().y + 10, GetPos().z), {}, {});		//�����
			//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

			return true;
		}

		pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
	}

	return false;
}
