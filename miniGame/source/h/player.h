//=============================================================================
//
// �v���C���[���� [player.h]
// Author : ��������
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X
//*****************************************************************************
class CPlayer : public CObject
{
public:
	CPlayer();		//�f�t�H���g�R���X�g���N�^
	~CPlayer();	//�f�X�g���N�^
	static CPlayer* Create();	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void) {}	//�`�揈��

	//�v���C���[�ԍ��ݒ菈��
	void SetIndex(const int nIndex) { m_nIndex = nIndex; }
	//�v���C���[�ԍ��擾����
	int GetIndex(void) { return m_nIndex; }

	//�v���C���[�̑����擾����
	static int GetNum(void) { return m_nObjectPlayerNum; }

	//�X�V���邩�ǂ����擾����
	bool GetUpdate() { return m_bUpdate; }
	//�X�V���邩�ǂ����ݒ菈��
	void SetUpdate(const bool bUpdate) { m_bUpdate = bUpdate; }


private:
	static int m_nObjectPlayerNum;	//�v���C���[�̐�
	int m_nIndex;					//�v���C���[�ԍ�
	bool m_bUpdate;					//�X�V���������邩�ǂ���
};

#endif // !_PLAYER_H_