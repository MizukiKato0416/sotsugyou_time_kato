//=============================================================================
//
// 3D�I�u�W�F�N�g���� [object3D.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// 3D�I�u�W�F�N�g�N���X
//*****************************************************************************
class CObject3D : public CObject
{
public:
	CObject3D();	//�f�t�H���g�R���X�g���N�^
	virtual ~CObject3D();	//�f�X�g���N�^
	virtual HRESULT Init(void);	//����������
	virtual void Uninit(void);	//�I������
	virtual void Update(void);	//�X�V����
	virtual void Draw(void);	//�`�揈��

	void SetPos(D3DXVECTOR3 pos);	//�ʒu���W�̐ݒ�
	D3DXVECTOR3 GetPos(void);		//�ʒu���W�̎擾
	void SetRot(D3DXVECTOR3 rot);	//�p�x�̐ݒ�
	D3DXVECTOR3 GetRot(void);		//�p�x�̎擾
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }		//���[���h�}�g���b�N�X�̎擾
	LPDIRECT3DVERTEXBUFFER9* GetPtrVtxBuff(void);	//���_�o�b�t�@�̃|�C���^�̃|�C���^���擾
	LPDIRECT3DINDEXBUFFER9* GetPtrIdxBuff(void);	//�C���f�b�N�X�o�b�t�@�̃|�C���^�̃|�C���^���擾
	void SetNumVtx(int nNumVtx);	//���_���̐ݒ�
	int GetNumVtx(void);			//���_���̎擾
	void SetNumIdx(int nNumVtx);	//�C���f�b�N�X���̐ݒ�
	int GetNumIdx(void);			//�C���f�b�N�X���̎擾

	void SetMaterialDiffuse(D3DXCOLOR col) { m_mat.MatD3D.Diffuse = col; }			//�}�e���A���̐F�̐ݒ�
	D3DXCOLOR GetMaterialDiffuse(void) { return m_mat.MatD3D.Diffuse; }				//�}�e���A���̐F�̎擾
	void SetMaterialDiffuseAlpha(float fAlpha) { m_mat.MatD3D.Diffuse.a = fAlpha; }	//�}�e���A���̃A���t�@�l��ݒ�
	float GetMaterialDiffuseAlpha(void) { return m_mat.MatD3D.Diffuse.a; }			//�}�e���A���̃A���t�@�l���擾
	void SetMaterialSpecular(D3DXCOLOR col) { m_mat.MatD3D.Specular = col; }		//�}�e���A���̃X�y�L�����[�F�̐ݒ�
	void SetMaterialEmissive(D3DXCOLOR col) { m_mat.MatD3D.Emissive = col; }		//�}�e���A���̔����F�̐ݒ�
	void SetMaterialPower(float fPower) { m_mat.MatD3D.Power = fPower; }			//�}�e���A���̔��˂̎����̐ݒ�
	void SetColorGlow(D3DXCOLOR col) { m_colGlow = col; }	//�֊s�̔����F�̐ݒ�
	void SetPowerGlow(float fPower) { m_powGlow = fPower; }	//�֊s�̋��x�̐ݒ�

	void SetMoveTex(float fMoveTexU, float fMoveTexV);		//�e�N�X�`���ړ��ݒ菈��

	//���Z�����ݒ菈��
	void SetAlphaBlend(const bool bAlphaBlend) { m_bAlphaBlend = bAlphaBlend; }
	//���Z�����擾����
	bool GetAlphaBlend() { return m_bAlphaBlend; }

	//���C�g�ݒ菈��
	void SetLight(const bool bEnableLight) { m_bEnableLight = bEnableLight; }
	//���C�g�擾����
	bool GetLight() { return m_bEnableLight; }

private:
	D3DXVECTOR3	m_pos;	//�|���S���̒��S���W
	D3DXVECTOR3 m_rot;	//�|���S���̊p�x
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	int m_nNumVtx;	//���_��
	int m_nNumIdx;	//�C���f�b�N�X��

	D3DXMATERIAL m_mat;		//�|���S���̃}�e���A��
	D3DXCOLOR m_colGlow;	//�֊s�̔����F�̐F
	float m_powGlow;	//�֊s�̋��x

	bool m_bAlphaBlend;		//���Z�������邩�ǂ���
	bool m_bEnableLight;	//���C�g�g�����ǂ���
};

#endif // !_OBJECT3D_H_