//=============================================================================
//
// ���b�V���h�[������ [meshdome.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _MESHDOME_H_
#define _MESHDOME_H_

#include "main.h"
#include "object3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// ���b�V���h�[���N���X
//*****************************************************************************
class CMeshdome : public CObject3D
{
public:
	CMeshdome();	//�f�t�H���g�R���X�g���N�^
	CMeshdome(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumXZ, int nNumY, float fRadius, bool bOut);	//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	virtual ~CMeshdome();	//�f�X�g���N�^
	static CMeshdome* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumXZ, int nNumY, float fRadius, bool bOut, CTexture::TEXTURE_TYPE typeTex);	//��������
	virtual HRESULT Init(void);	//����������
	virtual void Uninit(void);	//�I������
	virtual void Update(void);	//�X�V����
	virtual void Draw(void);	//�`�揈��
	float GetRadius(void) { return m_fRadius; }	//���a�̎擾
	void AddRadius(float fRadius) { m_fRadius += fRadius; }		//���a��ǉ�

private:
	void SetVtxBuff(void);	//���_�o�b�t�@�̏����X�V
	void SetVtxBuffPos(void);	//���_�o�b�t�@�̈ʒu�����X�V

	const int m_nNumXZ;	//XZ�����̃|���S���̐�
	const int m_nNumY;	//Y�����̃|���S���̐�
	float m_fRadius;	//�����̔��a
	bool m_bOut;		//�|���S�����O�������ǂ���
};

#endif // !_MESHDOME_H_