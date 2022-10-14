//=======================================================================
//���f��(x�t�@�C��)�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "x_load.h"
#include "object.h"

//========================================================
//�}�N����`
//========================================================
#define MODEL_MAX_TEXTURE (128)
#define MODEL_VTX		  (8)

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CModel
{
public:
	//�����o�֐�
	CModel();								//�R���X�g���N�^
	~CModel();								//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, string sPas);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModel *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const string &sPas);
	static CModel *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const int &nType);
	void SetParent(CModel *pModel);													//�e�ݒ菈��
	CModel *GetParent(void) { return m_pParent; }									//�e�擾����
	D3DXMATRIX GetMtx(void);														//���[���h�}�g���b�N�X�擾����
	void SetMtx(const D3DXMATRIX &mtx) { m_mtxWorld = mtx; }						//���[���h�}�g���b�N�X�ݒ菈��
	D3DXMATRIX *GetMtxParent(void) { return m_mtxWorldParent; }						//���[���h�}�g���b�N�X�擾����
	void SetMtxParent(D3DXMATRIX *mtx) { m_mtxWorldParent = mtx; }					//���[���h�}�g���b�N�X�ݒ菈��
	D3DXMATRIX *GetMtxPoint(void) { return &m_mtxWorld; }							//���[���h�}�g���b�N�X�擾����
	D3DXVECTOR3 GetSize(void);														//�T�C�Y�擾����
	void SetPos(const D3DXVECTOR3 &pos);											//���f���̈ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void);														//���f���̈ʒu�擾����
	D3DXVECTOR3 GetVtxPos(const int &nCntVtx);										//���f���̒��_�ʒu�擾����
	void SetVtxPos(const int &nCntVtx, const D3DXVECTOR3 &pos);						//���f���̒��_�ʒu�ݒ菈��
	void SetRot(const D3DXVECTOR3 &rot);											//���f���̌����ݒ菈��
	D3DXVECTOR3 GetRot(void);														//���f���̌����擾����
	D3DXMATRIX *GetVtxMtxWorld(void);												//���[���h�}�g���b�N�X�擾����
	void SetVtxMtxWorld(const D3DXVECTOR3 &vtxPos, const int &nCntVtx);				//���[���h�}�g���b�N�X�ݒ菈��
	void SetMtxWorldPos(void);														//���[���h�}�g���b�N�X�̈ʒu�ݒ菈��
	void SetObjParent(const bool bObjeParent) { m_bObjParent = bObjeParent; }		//�I�u�W�F�N�g�Ƃ̐e�q�֌W�ݒ菈��
	bool GetObjParent(void) { return m_bObjParent; }								//�I�u�W�F�N�g�Ƃ̐e�q�֌W�擾����
	void SetDiffuse(const float &alpha) { m_diffuseAlpha = alpha; }					//�J���[�ݒ菈��
	string GetFileName(void) { return m_sFileName; }										//�t�@�C�����擾����

private:
	//�����o�֐�
	void Collision(void);								//�����蔻��

	LPD3DXMESH m_pMesh;									//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;							//�}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD m_nNumMat;									//�}�e���A����
	vector<LPDIRECT3DTEXTURE9> m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;									//�|���S���̈ʒu
	D3DXVECTOR3	m_size;									//�T�C�Y
	D3DXVECTOR3 m_rot;									//����
	D3DXMATRIX m_mtxWorld;								//���[���h�}�g���b�N�X
	D3DXMATRIX *m_mtxWorldParent;						//�e�̃��[���h�}�g���b�N�X
	D3DXVECTOR3 m_vtxMin;								//���f���̒��_�̍ŏ��l
	D3DXVECTOR3 m_vtxMax;								//���f���̒��_�̍ő�l
	CModel *m_pParent;									//�e�̃��f��
	D3DXVECTOR3 m_vtxPos[MODEL_VTX];					//8���_�̈ʒu�ۑ��p�ϐ�
	D3DXVECTOR3 m_vtxRot[MODEL_VTX];					//8���_�̉�]�ۑ��p�ϐ�
	D3DXMATRIX m_vtxMtxWorld[MODEL_VTX];				//8���_�̃��[���h�}�g���b�N�X�ۑ��p�ϐ�
	bool m_bObjParent;									//���f���ȊO�Ƃ̐e�q�֌W�����邩�ǂ���
	float m_diffuseAlpha;								//���f���̃��l
	string m_sFileName;									//�t�@�C����
};

#endif // !_MODEL_H_