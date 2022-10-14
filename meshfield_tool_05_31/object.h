//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : �H������
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "texture.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject
{
public:
	//---------------------------
	// �񋓌^
	//---------------------------
	enum class PRIORITY
	{
		NONE = 0,			// �Ȃ�
		MESH_FIELD,			// ���b�V���t�B�[���h
		PLAYER,				// �v���C���[
		MODEL,				// ���f��
		POLYGON_3D,			// 3D�|���S��
		SHADOW,				// �e
		EFFECT3D,			// �p�[�e�B�N��
		EFFECT2D,			// �p�[�e�B�N��
		UI,					// UI
		FADE,				// �t�F�[�h
		MAX
	};

	enum class OBJTYPE
	{
		NONE = 0,			// �Ȃ�
		POLYGON_3D,			// 3D�|���S��
		FLOOR,				// ��
		EFFECT_3D,			// 3D�G�t�F�N�g
		EFFECT_2D,			// 2D�G�t�F�N�g
		MODEL,				// ���f��
		PLAYER,				// �v���C���[
		UI,					// UI
		SHADOW,				// �e
		MAX
	};

	CObject(PRIORITY priorty = PRIORITY::NONE);	// �f�t�H���g�R���X�g���N�^
	virtual ~CObject();	// �f�t�H���g�f�X�g���N�^
	virtual HRESULT Init(void) = 0;	// ������
	virtual void Uninit(void) = 0;	// �I��
	virtual void Update(void) = 0;	// �X�V
	virtual void Draw(void) = 0;	// �`��
	static void ReleaseAll(void);	// �S�j��
	static void UpdateAll(void);	// �S�X�V
	static void DrawAll(void);		// �S�`��
	D3DXVECTOR3 GetPos(void) { return m_pos; }			// �Q�b�_�[
	D3DXVECTOR3 GetSize(void) { return m_size; }		// �Q�b�_�[
	bool GetDeath(void) { return m_deth; }				// �Q�b�_�[
	D3DXVECTOR3 GetPosOld(void) { return m_pos_old; }	// �Q�b�_�[
	OBJTYPE GetObjType(void) { return m_obj_type; }		// �Q�b�_�[
	static vector<CObject*> GetObject(const int &priority) { return m_object[priority]; }	// �Q�b�_�[
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }				// �Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }			// �Z�b�^�[
	void SetObjType(const OBJTYPE &obj_type) { m_obj_type = obj_type; }	// �Z�b�^�[
	void SetPriority(const int &nPriority);								//�v���C�I���e�B�ݒ菈��
	void SetPosOld(const D3DXVECTOR3 &pos_old) { m_pos_old = pos_old; }	// �Z�b�^�[
private:
	static vector<CObject*> m_object[(int)PRIORITY::MAX];				// �I�u�W�F�N�g
	D3DXVECTOR3	m_pos;		// �ʒu
	D3DXVECTOR3 m_pos_old;	// 1�t���[���O�̈ʒu
	D3DXVECTOR3 m_size;		// �T�C�Y
	OBJTYPE m_obj_type;		// �I�u�W�F�N�g�̎��
	int m_priority;	// �`�揇
	bool m_deth;	// ���S�t���O
protected:
	void Release(void) { m_deth = true; }		// ���S�t���O���Ă�
};

#endif