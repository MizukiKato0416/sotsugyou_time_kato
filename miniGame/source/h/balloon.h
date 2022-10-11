//=============================================================================
//
// ���D���� [balloon.h]
// Author : ��������
//
//=============================================================================
#ifndef _BALLOON_H_
#define _BALLOON_H_

#include "objectModel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BALLOON_SIZE				(40.0f)		//���D�̃T�C�Y

//*****************************************************************************
//�O���錾
//*****************************************************************************

//*****************************************************************************
// ���D�N���X
//*****************************************************************************
class CBalloon : public CObjectModel
{
public:
	CBalloon();	//�f�t�H���g�R���X�g���N�^
	CBalloon(CModel::MODELTYPE typeModel);		//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CBalloon();	//�f�X�g���N�^
	static CBalloon* Create(bool bGold, D3DXVECTOR3 pos);	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	//�����擾����
	static int GetNum(void) { return m_nNum; }

private:
	bool CollisionPlayer(void);	//�v���C���[�Ƃ̓����蔻��

	static int m_nNum;	//����
	bool m_bGold;		//���F�ɂ��邩�ǂ���
	D3DXVECTOR3 m_move;	//�ړ���
	bool m_bUp;			//�㏸���Ă��邩�ǂ���
};

#endif // !_BALLOON_H_