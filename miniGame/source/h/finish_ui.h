//=============================================================================
//
// �t�B�j�b�V��UI���� [finish_ui.h]
// Author : ��������
//
//=============================================================================
#ifndef _FINISH_UI_H_
#define _FINISH_UI_H_

#include "object2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************

//*****************************************************************************
// �t�B�j�b�V��UI�N���X
//*****************************************************************************
class CFinishUi : public CObject2D
{
public:
	enum class STATE
	{
		DEC_SIZE = 0,	//�T�C�Y���Z
		NONE,			//�Ȃ�
		ADD_SIZE,		//�T�C�Y���Z
		MAX
	};


	CFinishUi();		//�f�t�H���g�R���X�g���N�^
	~CFinishUi();	//�f�X�g���N�^
	static CFinishUi* Create(const D3DXVECTOR3 pos, const int nDelay, const float fMaxAlpha);	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

private:
	void StateDecSize();	//�T�C�Y���Z����
	void StateNone();		//�������Ȃ�����
	bool StateAddSize();	//�T�C�Y���Z����

	STATE m_state;			//���
	int m_nFrameCounter;	//�t���[���J�E���g�p
	int m_nDelay;			//��������܂ł̒x��
	int m_nDelayCounter;	//��������܂ł̒x���̂��߂̃J�E���^�[
	float m_fMaxAlpha;		//���l�ő�l
};

#endif // !_FINISH_UI_H_