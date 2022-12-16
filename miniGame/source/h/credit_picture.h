//=============================================================================
//
// �N���W�b�g�̊G���� [credit_picture.h]
// Author : ��������
//
//=============================================================================
#ifndef _CREDIT_PICTURE_H_
#define _CREDIT_PICTURE_H_

#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CObject2D;
class CTexture;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCreditPicture : public CObject
{
public:
	CCreditPicture();		//�f�t�H���g�R���X�g���N�^
	~CCreditPicture();		//�f�X�g���N�^
	static CCreditPicture* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale, const float fRot, const CTexture::TEXTURE_TYPE texType,
	                              const float fMoveY);	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void) {}	//�`�揈��

private:

	bool Move(CObject2D *&pObject2D);	//�ړ�����

	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_scale;				//�X�P�[��
	float m_fRot;						//��]
	float m_fMoveY;						//�ړ���
	CTexture::TEXTURE_TYPE m_texType;	//�e�N�X�`���̎��
	CObject2D *m_pFrame;				//�t���[��
	CObject2D *m_pPicture;				//�G
};

#endif // !_CREDIT_PICTURE_H_