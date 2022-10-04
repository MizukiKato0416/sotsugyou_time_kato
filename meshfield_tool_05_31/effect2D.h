//===========================================
//�p�[�e�B�N������
//Author:��������
//===========================================
#ifndef _EFFECT2D_H_
#define _EFFECT2D_H_
#include "object2D.h"

//�O���錾

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEffect2D : public CObject2D
{
public:
	//�G�t�F�N�g�̎��
	enum class EFFECT2D_TYPE
	{
		NONE = 0,
		MAX
	};

	CEffect2D(CObject::PRIORITY Priority = CObject::PRIORITY::EFFECT2D);		//�R���X�g���N�^
	~CEffect2D();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect2D *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXCOLOR &col, const EFFECT2D_TYPE &type);

	//���Z�����ݒ菈��
	void SetAlphaBlendSubtraction(const bool &bAlphaBlendSubtraction) { m_bAlphaBlendSubtraction = bAlphaBlendSubtraction; }

private:
	EFFECT2D_TYPE m_type;			//�G�t�F�N�g�̎��
	bool m_bAlphaBlendSubtraction;	//���Z�������邩�ǂ���
};

#endif // !_EFFECT3D_H_