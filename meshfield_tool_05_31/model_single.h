//===========================================
//���f���P�̂��o������
//Author:��������
//===========================================
#ifndef _MODEL_SINGLE_H_
#define _MODEL_SINGLE_H_
#include "object.h"
#include "x_load.h"

//�O���錾
class CModel;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CModelSingle : public CObject
{
public:
	//�����o�֐�
	CModelSingle(CObject::PRIORITY Priority = CObject::PRIORITY::MODEL);	//�R���X�g���N�^
	~CModelSingle();														//�f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModelSingle *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const string &sPas, CModel *pParent, const bool &Collision);
	static CModelSingle *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const int &nType, CModel *pParent, const bool &Collision);
	static bool SimpleCollision(CObject *pObject);										//��]��������_���ȓ����蔻��
	static bool Collision(CObject *pObject);											//y������]�����Ă��������蔻��
	static int CollisionAny(CObject *pObject);											//�����̏Փ˔���
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; CObject::SetPos(m_pos); }		//�ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void) { return m_pos; }											//�ʒu�擾����
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }								//��]�ݒ菈��
	D3DXVECTOR3 GetRot(void) { return m_rot; }											//��]�擾����
	void SetMtxWorld(void);																//���[���h�}�g���b�N�X�ݒ菈��
	bool GetColl(void) { return m_bCollision; }											//�����蔻��擾����
	void SetColl(bool bColl) { m_bCollision = bColl; }									//�����蔻��ݒ菈��
	CModel *GetModel(void) { return m_pModel; }											//���f���擾����

private:
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3	m_size;					//�T�C�Y
	D3DXVECTOR3 m_rot;					//����
	D3DXVECTOR3 m_move;					//�ړ���
	CModel *m_pModel;					//���f���̃|�C���^
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	CModel *m_pParent;					//�e���f���ւ̃|�C���^
	//CXload::X_TYPE m_type;			//�o�����f���̎��
	bool m_bCollision;					//�����蔻������邩�ǂ���
	int m_nType;						//���
};

#endif // !_MODEL_SINGLE_H_