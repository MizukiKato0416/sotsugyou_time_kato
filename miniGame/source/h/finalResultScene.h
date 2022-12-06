//=============================================================================
//
// �ŏI���ʃV�[������ [finalResultScene.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _FINAL_RESULT_SCENE_H_
#define _FINAL_RESULT_SCENE_H_

#include "scene.h"
#include "object_player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;
class CObjectModel;
class CScore;
class CFloatObject;

//*****************************************************************************
// �ŏI���ʃV�[���N���X
//*****************************************************************************
class CFinalResultScene : public CScene
{
public:
	//�t�F�[�Y
	enum class PHASE
	{
		PHASE_FIRST = 0,//�t�F�[�Y�J�n
		RISE_CAMERA,	//�J�����̏㏸�Ɖ�]
		RESULT_TEXT,	//���ʔ��\�̃e�L�X�g�\��
		SHOW_SCORE_UI,	//�X�R�A��UI�\��
		RISE_TOWER,		//�^���[�̏㏸
		WINNER,			//����
		PHASE_FINISH,	//�t�F�[�Y�I��
		ENUM_MAX
	};

	CFinalResultScene();			//�f�t�H���g�R���X�g���N�^
	virtual ~CFinalResultScene();	//�f�X�g���N�^
	void Init(void);				//����������
	void CreateObject(void);		//�I�u�W�F�N�g��������
	void Uninit(void);				//�I������
	void Update(void);				//�X�V����

	static void SetPlayerScore(int nScore, int nIdxPlayer) { m_aPlayerScore[nIdxPlayer] = nScore; }	//�v���C���[�̃X�R�A��ݒ�

private:
	void PhaseFirst();					//�t�F�[�Y�J�n����
	void RiseCamera();					//�J�����̏㏸����
	void ResultText();					//���ʔ��\�̃e�L�X�g�\������
	void ShowScoreUI();					//�X�R�A��UI�\������
	void RiseTower();					//�^���[�̏㏸����
	void Winner();						//����
	void PhaseFinish();					//�t�F�[�Y�I������
	void StopTower(int nIdxPlayer);		//�^���[��~���̏���
	void CloudMove();					//�_�ړ�����
	void CreateBalloon();				//���D��������
	void BalloonMove();					//���D�ړ�����

	PHASE m_phase;		//�t�F�[�Y
	int m_nCntPhase;	//�t�F�[�X�J�E���g
	static int m_aPlayerScore[MAX_OBJECT_PLAYER_NUM];	//�v���C���[�̃X�R�A

	CObjectModel* m_apObjPlayer[MAX_OBJECT_PLAYER_NUM];		//�v���C���[�̃��f���I�u�W�F�N�g
	CObjectModel* m_apResultTower[MAX_OBJECT_PLAYER_NUM];	//�v���C���[�̉��ɂ���^���[�̃��f���I�u�W�F�N�g
	CObject2D* m_pTextResult;	//���ʔ��\�̕\��
	CScore* m_apScoreResult[MAX_OBJECT_PLAYER_NUM];		//�X�R�A�̕\��
	int m_nTopScore;	//�ō��X�R�A
	std::vector<CObjectModel*> m_vObjCrown;	//�����̃��f���̔z��
	int m_nFadeTime;	//�t�F�[�h�J�n�܂ł̃J�E���g
	bool m_bEndScene;	//�I���L�[������

	std::vector<float> m_fDifferCloud;		//�_�������̋���
	std::vector<float> m_fRotCloud;			//�_�������̌���
	std::vector<float> m_fMoveSpeedCloud;	//�_�̈ړ����x
	std::vector<CObjectModel*> m_pCloud;	//�_�̃|�C���^

	std::vector<CFloatObject*> m_pBalloon;	//���D�̃|�C���^
	float m_fBalloonCreateCounter;			//���D�̐����Ԋu�p
	int m_nCrownEffectCounter;				//�����G�t�F�N�g�����J�E���^�[
};

#endif // !_FINAL_RESULT_SCENE_H_