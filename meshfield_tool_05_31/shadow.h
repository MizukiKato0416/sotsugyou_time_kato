//===========================================
//�e����
//Author:��������
//===========================================
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "object3D.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CShadow : public CObject3D
{
public:
	CShadow(CObject::PRIORITY Priority = CObject::PRIORITY::SHADOW);		//�R���X�g���N�^
	~CShadow();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CShadow *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, CObject *pObject);

	bool GetDraw(void) { return m_bDraw; }						//�`��擾����
	void SetDraw(const bool &bDraw) { m_bDraw = bDraw; }		//�`��ݒ菈��

private:
	void Collision(void);			//�����蔻��

	CObject *m_pObject;		//�Ώۂ̃I�u�W�F�N�g�̃|�C���^
	bool m_bDraw;			//�`�悷�邩�ǂ���
	D3DXVECTOR3 m_size;		//�T�C�Y
};

#endif // !_SHADOW_H_