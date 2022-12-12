//=============================================================================
//
// �ω�����F���� [change_color.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _CHANGE_COLOR_H_
#define _CHANGE_COLOR_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �ω�����F�N���X
//*****************************************************************************
class CChangeColor
{
public:
	CChangeColor();	//�f�t�H���g�R���X�g���N�^
	virtual ~CChangeColor();	//�f�X�g���N�^

	static CChangeColor* Create(D3DXCOLOR colStart, float fSpeedColorwheel);	//��������

	virtual void Init(void);		//����������
	virtual void Uninit(void);		//�I������
	virtual void Update(void);		//�X�V����

	D3DXCOLOR GetColor(void)				{ return m_col; }					//�F�̎擾
	void SetSpeedColorwheel(float fSpeed)	{ m_fSpeedColorwheel = fSpeed; }	//�J���[�z�C�[�����ω�����X�s�[�h�̐ݒ�

private:
	D3DXCOLOR m_col;			//�F
	float m_fSpeedColorwheel;	//�J���[�z�C�[�����ω�����X�s�[�h
};

#endif // !_CHANGE_COLOR_H_