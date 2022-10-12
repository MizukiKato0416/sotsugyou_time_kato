//=============================================================================
//
// �J�E���g�_�E��UI���� [count_down_ui.h]
// Author : ��������
//
//=============================================================================
#ifndef _COUNT_DOWN_UI_H_
#define _COUNT_DOWN_UI_H_

#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// �J�E���g�_�E���N���X
//*****************************************************************************
class CCountDownUi : public CObject
{
public:
	CCountDownUi();		//�f�t�H���g�R���X�g���N�^
	~CCountDownUi();	//�f�X�g���N�^
	static CCountDownUi* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void) {}	//�`�揈��

private:
	CObject2D *m_pCountUi;	//�J�E���g�pUI�̃|�C���^
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_scale;	//�X�P�[��
	int m_nCounter;			//Frame�J�E���g�p
};

#endif // !_COUNT_DOWN_UI_H_