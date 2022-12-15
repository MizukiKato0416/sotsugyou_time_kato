//=============================================================================
//
// �`�F�b�N���� [check.h]
// Author : ��������
//
//=============================================================================
#ifndef _CHECK_H_
#define _CHECK_H_

#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CCheckIcon;
class CObject2D;
class CCountDownUi;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCheck : public CObject
{
public:
	enum class STATE
	{
		NONE = 0,
		CHECK,		//�`�F�b�N
		COUNTDOWN,	//�J�E���g�_�E��
		MAX
	};

	CCheck();		//�f�t�H���g�R���X�g���N�^
	~CCheck();		//�f�X�g���N�^
	static CCheck* Create(const int nNumPlayer);	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void) {}	//�`�揈��

	//�`�F�b�N�ł������擾����
	bool GetCheckAll() { return m_bCheckAll; }
	//�S�������ꂽ���擾����
	bool GetUninitAll() { return m_bAllUninit; }

	//�J�E���g�_�E��UI�𐶐����邩�ǂ����擾����
	bool GetCreateCountDownUi() { return m_bCreateCountDownUi; }
	//�J�E���g�_�E��UI�𐶐����邩�ǂ����ݒ菈��
	void SetCreateCountDownUi(const bool bCreateCountDownUi) { m_bCreateCountDownUi = bCreateCountDownUi; }

	//�J�E���g�_�E��UI�擾����
	CCountDownUi *GetCountDownUi() { return m_pCountDownUi; }

	//��Ԏ擾����
	STATE GetState() { return m_state; }

private:
	void DecFrame();		//�t���[������������
	void Check();			//�`�F�b�N����
	void CountDown();		//�J�E���g�_�E������

	std::vector<CCheckIcon*> m_apCheckIcon;				//�`�F�b�N�A�C�R���̃|�C���^
	CObject2D *m_pFrame;								//�w�i�̈Â��Ȃ��Ă邠��
	CObject2D *m_pTutorial;								//����UI
	CCountDownUi *m_pCountDownUi;						//�J�E���g�_�E��UI�̃|�C���^

	int m_nNumPlayer;									//�v���C���[�̐�
	bool m_bCheckAll;									//�S�����`�F�b�N�������ǂ���
	bool m_bAllUninit;									//�S�������ꂽ���ǂ���
	bool m_bCreateCountDownUi;							//�J�E���g�_�E��UI�𐶐����邩�ǂ���
	STATE m_state;										//���
};

#endif // !_CHECK_H_