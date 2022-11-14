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
class CTimer;
class CCoverDisplay;

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
		TUTORIAL_1,			//����1
		TUTORIAL_2,			//����2
		WOLF_DECIDE,		//�l�T����
		TUTORIAL_3,			//����3
		WAIT,				//�҂�����
		ANSWER,				//����
		TUTORIAL_4,			//����4
		DEC_WOLF_POINT,		//�l�T�̃|�C���g�}�C�i�X
		ADD_PLAYER_POINT,	//�l�T�ȊO�̃|�C���g���Z
		DEC_PLAYER_POINT,	//�l�T�ȊO�̃|�C���g�}�C�i�X
		ADD_WOLF_POINT,		//�l�T�̃|�C���g���Z
		FINISH,				//�t�B�j�b�V��
		MAX
	};

	//�I����
	enum class SELECT
	{
		PLAYER_1 = 0,
		PLAYER_2,
		PLAYER_3,
		PLAYER_4,
		SELECT_MAX
	};

	void Tutorial1();			//����1����
	void Tutorial2();			//����2����
	void WolfDecide();			//�l�T���菈��
	void Tutorial3();			//����3����
	void Wait();				//�҂���
	void Answer();				//�񓚏���
	void Tutorial4();			//����4����
	void DecWolfPoint();		//�l�T�̃|�C���g�}�C�i�X����
	void AddPlayerPoint();		//�l�T�ȊO�̃|�C���g���Z����
	void DecPlayerPoint();		//�l�T�ȊO�̃|�C���g�}�C�i�X����
	void AddWolfPoint();		//�l�T�̃|�C���g���Z����
	void Finish();				//�I������

	//�I��p�A�C�R��UI�̈ʒu�ݒ菈��
	void SelectIconSetPos(const int nIdxPlayer, const SELECT select);
	//�|�C���gUI�̈ʒu�ݒ菈��
	void PointUiSetPos(const int nIdxPlayer, int nObjectPlayerIndex);

	//�|�C���g���Z����
	bool DecPoint();
	//�|�C���g���Z����(�����F�l�T�Ƀ|�C���g�����Z���邩�ǂ���)
	bool AddPoint(const bool bAddPointWolf);

	//�I���A�C�R���̈ړ�����
	void SelectIconMove();

	CScoreUi *m_apScoreUi[MAX_OBJECT_PLAYER_NUM];		//�X�R�AUI 
	CObject2D *m_pSelectIcon[MAX_OBJECT_PLAYER_NUM];	//�I��p�A�C�R��
	CObject2D *m_pPointUi[MAX_OBJECT_PLAYER_NUM];		//�|�C���gUI 
	CObject2D *m_pTutorial;								//����UI
	CTimer* m_pTimer;									//�Q�[���̃^�C�}�[
	CObject2D* m_pTimerFrame;							//�^�C�}�[�̘g

	CCoverDisplay* m_pWaitBlack;		//�҂����Ԃ̍������
	CObject2D* m_pCircleStencilMask;	//�҂����Ԃ̃X�e���V���}�X�N

	D3DXVECTOR3 m_aPosPlayer2D[MAX_OBJECT_PLAYER_NUM];		//�v���C���[��2D���W
	SELECT m_select[MAX_OBJECT_PLAYER_NUM];					//�ǂ����I������Ă���̂�
	bool m_bSelectFloat[MAX_OBJECT_PLAYER_NUM];				//�I���A�C�R���̕��V�؂�ւ��p
	float m_fSelectMove[MAX_OBJECT_PLAYER_NUM];				//�I���A�C�R���̈ړ���

	PHASE m_phase;						//�t�F�[�Y
	int m_nFrameCounter;				//Frame�J�E���g�p
	bool m_bAddPoint;					//�|�C���g�����Z���ꂽ���ǂ���
};

#endif // !_FIND_WOLF_SCENE_H_