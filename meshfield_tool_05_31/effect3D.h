//===========================================
//�p�[�e�B�N������
//Author:��������
//===========================================
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_
#include "billboard.h"

//�O���錾
class CControl;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEffect3D : public CBillboard
{
public:
	//�G�t�F�N�g�̎��
	enum class EFFECT3D_TYPE
	{
		NONE = 0,
		TRAJECTORY_PLAYER,		//�v���C���[�̋O��
		SMOKE,					//��
		WIND,					//��
		MAX
	};

	CEffect3D(CObject::PRIORITY Priority = CObject::PRIORITY::EFFECT3D);		//�R���X�g���N�^
	~CEffect3D();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect3D *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXCOLOR &col, const EFFECT3D_TYPE &type);

	//���Z�����ݒ菈��
	void SetAlphaBlendSubtraction(const bool &bAlphaBlendSubtraction) { m_bAlphaBlendSubtraction = bAlphaBlendSubtraction; }
	//�����ݒ菈��
	void SetRot(const D3DXVECTOR3 &rot) { CBillboard::SetRot(rot); }
	//�����擾����
	D3DXVECTOR3 GetRot(void) { return CBillboard::GetRot(); }

private:
	EFFECT3D_TYPE m_type;			//�G�t�F�N�g�̎��
	CControl *m_pControl;			//�R���g���[���N���X�̃|�C���^
	bool m_bAlphaBlendSubtraction;	//���Z�������邩�ǂ���
};

#endif // !_EFFECT3D_H_