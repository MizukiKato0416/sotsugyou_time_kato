//=============================================================================
//
// �X�R�AUI���� [score_ui.h]
// Author : ��������
//
//=============================================================================
#ifndef _SCORE_UI_H_
#define _SCORE_UI_H_

#include "object.h"
#include "object_player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CObject2D;
class CScore;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScoreUi : public CObject
{
public:
	CScoreUi();		//�f�t�H���g�R���X�g���N�^
	~CScoreUi();		//�f�X�g���N�^
	static CScoreUi* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale, const int nPlayerNum);	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void) {}	//�`�揈��

	//�X�R�A�擾����
	CScore *GetScore(void) { return m_pScore; }

private:
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_scale;		//�X�P�[��

	CObject2D *m_pFrame;		//�t���[���̃|�C���^
	CScore *m_pScore;			//�X�R�A�̃|�C���^

	int m_nPlayerNum;			//�v���C���[�ԍ�
};

#endif // !_SCORE_UI_H_