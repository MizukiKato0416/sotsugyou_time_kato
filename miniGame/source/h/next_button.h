//=============================================================================
//
// ���ɐi�ރ{�^��UI���� [next_button.h]
// Author : ��������
//
//=============================================================================
#ifndef _NEXT_BUTTON_H_
#define _NEXT_BUTTON_H_

#include "object2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CNextButton : public CObject2D
{
public:
	CNextButton();	//�f�t�H���g�R���X�g���N�^
	~CNextButton();	//�f�X�g���N�^

	//��������(�ʒu�A�T�C�Y�A�e�N�X�`���A�����Ȃ��Ȃ��Ă��琶�������܂ł̃t���[���A���l���Z��)
	static CNextButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const CTexture::TEXTURE_TYPE texType,
		                       const int nCounter, const float fDecAlpha);
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

private:
	int m_nFrameCounter;		//�t���[���J�E���g�p
	int m_nCounter;				//�����Ȃ��Ȃ��Ă��琶�������܂ł̃t���[��
	float m_fDecAlpha;			//���l���Z��
};

#endif // !_NEXT_BUTTON_H_