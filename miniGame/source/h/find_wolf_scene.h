//=============================================================================
//
// �l�T���菈�� [find_wolf_scene.h]
// Author : ��������
//
//=============================================================================
#ifndef _FIND_WOLF_SCENE_H_
#define _FIND_WOLF_SCENE_H_

#include "scene.h"
#include "object_player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;
class CScoreUi;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CFindWolfScene : public CScene
{
public:
	CFindWolfScene();	        //�f�t�H���g�R���X�g���N�^
	virtual ~CFindWolfScene();	//�f�X�g���N�^
	void Init(void);	    //����������
	void Uninit(void);	    //�I������
	void Update(void);	    //�X�V����

private:
	//�t�F�[�Y
	enum class PHASE
	{
		NONE = 0,
		TUTORIAL_1,		//����1
		TUTORIAL_2,		//����2
		WOLF_DECIDE,	//�l�T����
		TUTORIAL_3,		//����3
		WAIT,			//�҂�����
		ANSWER,			//����
		TUTORIAL_4,		//����4
		MAX
	};

	void Tutorial1();	//����1����
	void Tutorial2();	//����2����
	void WolfDecide();	//�l�T���菈��
	void Tutorial3();	//����3����
	void Wait();		//�҂���
	void Answer();		//�񓚏���
	void Tutorial4();	//����4����

	CScoreUi *m_apScoreUi[MAX_OBJECT_PLAYER_NUM];	//�X�R�AUI 
	CObject2D *m_pTutorial;							//����UI

	PHASE m_phase;									//�t�F�[�Y
};

#endif // !_FIND_WOLF_SCENE_H_