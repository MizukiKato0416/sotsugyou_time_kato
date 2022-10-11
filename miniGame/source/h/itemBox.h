//=============================================================================
//
// �A�C�e���{�b�N�X���� [itemBox.h]
// Author : ��������
//
//=============================================================================
#ifndef _ITEMBOX_H_
#define _ITEMBOX_H_

#include "objectModel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ITEM_BOX_MOVE_SPEED	(5.0f)		//�A�C�e���̈ړ����x

//*****************************************************************************
//�O���錾
//*****************************************************************************

//*****************************************************************************
// �A�C�e���{�b�N�X�N���X
//*****************************************************************************
class CItemBox : public CObjectModel
{
public:
	CItemBox();	//�f�t�H���g�R���X�g���N�^
	CItemBox(CModel::MODELTYPE typeModel);		//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CItemBox();	//�f�X�g���N�^
	static CItemBox* Create(D3DXVECTOR3 pos);	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	//�����擾����
	static int GetNum(void) { return m_nNum; }
	//�ړ��ʎ擾����
	D3DXVECTOR3 GetMove(void) { return m_move; }
	//�ړ��ʐݒ菈��
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

private:
	bool CollisionPlayer(void);	//�v���C���[�Ƃ̓����蔻��

	static int m_nNum;		//����
	D3DXVECTOR3 m_move;		//�ړ���
};

#endif // !_ITEMBOX_H_