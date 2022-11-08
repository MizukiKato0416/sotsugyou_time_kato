//=============================================================================
//
// �l�T���菈�� [wolf_decide.h]
// Author : ��������
//
//=============================================================================
#ifndef _WOLF_DECIDE_H_
#define _WOLF_DECIDE_H_

#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CWolfDecide : public CObject
{
public:
	//�t�F�[�Y
	enum class PHASE
	{
		NONE = 0,
		SHAKE_TUTORIAL,		//�U������
		SHAKE,				//�U��
		GAME_START,			//�Q�[���X�^�[�g
		UNINIT,				//�I��
		MAX
	};


	CWolfDecide();		//�f�t�H���g�R���X�g���N�^
	~CWolfDecide();		//�f�X�g���N�^
	static CWolfDecide* Create();	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void) {}	//�`�揈��

	//�t�F�[�Y�擾����
	PHASE GetPhase() { return m_phase; }

private:
	void ShakeTutorial();	//�U����������
	void Shake();			//�U������
	void GameStart();		//�Q�[���X�^�[�g����


	CObject2D *m_pBg;			//�w�i
	CObject2D *m_pTutorialUI;	//����UI
	CObject2D *m_pShakeUI;		//�U��UI
	
	int m_nShakeUiCounter;		//�U��UI�_�ŃJ�E���^�[
	PHASE m_phase;				//�t�F�[�Y
};

#endif // !_WOLF_DECIDE_H_