//=============================================================================
//
// �A�C�e�������� [item_shield.h]
// Author : ��������
//
//=============================================================================
#ifndef _ITEM_SHIELD_H_
#define _ITEM_SHIELD_H_

#include "item.h"
#include "objectModel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CObjectPlayerAttackCar;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CItemShield : public CItem
{
public:
	CItemShield();	//�f�t�H���g�R���X�g���N�^
	CItemShield(CModel::MODELTYPE typeModel);		//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	virtual ~CItemShield();	//�f�X�g���N�^
	static CItemShield* Create(D3DXVECTOR3 pos);	//��������
	virtual HRESULT Init(void);				//����������
	virtual void Uninit(void);				//�I������
	virtual void Update(void);				//�X�V����
	virtual void Draw(void);				//�`�揈��

	//�v���C���[�Ƀq�b�g�����Ƃ��̏���
	virtual void HitPlayer(CObjectPlayer *pPlayer);

private:
	void Move();		//�ړ�����
	void Rotate();		//��]����

	D3DXVECTOR3 m_move;		//�ړ���
	int m_nCounter;			//�J�E���^�[

	CObjectModel *m_pSphereCover;		//����
};

#endif // !_ITEM_SHIELD_H_