//=============================================================================
//
// ���V������ [float_object.h]
// Author : ��������
//
//=============================================================================
#ifndef _FLOAT_OBJECT_H_
#define _FLOAT_OBJECT_H_

#include "objectModel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************

//*****************************************************************************
// ���D�N���X
//*****************************************************************************
class CFloatObject : public CObjectModel
{
public:
	CFloatObject();	//�f�t�H���g�R���X�g���N�^
	CFloatObject(CModel::MODELTYPE typeModel);		//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CFloatObject();	//�f�X�g���N�^
	static CFloatObject* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move, const D3DXVECTOR3 rotateSpeed,
		                        const CModel::MODELTYPE modelType);	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

private:

	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_rotateSpeed;	//��]���x
};

#endif // !_FLOAT_OBJECT_H_