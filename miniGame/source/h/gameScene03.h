//=============================================================================
//
// �Q�[���V�[��03���� [gameScene03.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _GAME_SCENE03_H_
#define _GAME_SCENE03_H_

#include "gameScene.h"
#include "main.h"
#include "object_player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAME03_ONE_METER (20.0f)		//game03�̂P�����̋���

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObjectPlayerIcon;
class CObject2D;
class CScore;

//*****************************************************************************
// �Q�[���V�[���N���X
//*****************************************************************************
class CGameScene03 : public CGameScene
{
public:
	CGameScene03();				//�f�t�H���g�R���X�g���N�^
	virtual ~CGameScene03();	//�f�X�g���N�^
	void Init(void);			//����������
	void CreateObject(void);	//�I�u�W�F�N�g��������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����
	void GameOver(void);		//�Q�[���I�[�o�[

private:
	void UpdateGame(void);					//�Q�[�����̍X�V
	void UpdateGameOver(void);				//�Q�[���I�[�o�[���̍X�V
	void UpdateReady(void);					//������Ԓ��̍X�V
	void CreatePlayerIcon(int nCntPlayer);	//�v���C���[�A�C�R����������
	void UpdatePlayerIcon(void);			//�v���C���[�A�C�R���X�V����
	void ShowDestDist(void);				//�ڕW�ʒu�\��
	void CountDownUi(void);					//�J�E���g�_�E��UI�̏���
	void LookPlayerPos(void);				//�v���C���[�̈ʒu�̊Ď�
	void UpdateCamera(void);				//�J�����̈ʒu�̍X�V
	//void UpdateLight(void);					//���C�g�̈ʒu�̍X�V
	void DecideRanking(void);				//�v���C���[�̈ʒu���烉���L���O�����肵�ăV�[���̃����L���O�ɐݒ肷��

	CObjectPlayerIcon *m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM];	//�v���C���[�A�C�R���̃|�C���^
	float m_fPlayerSpeedMax;//�v���C���[�̍ő呬�x
	float m_fDestPos;		//�ڕW�̋���
	bool m_bEndShowDest;	//�ڕW�ʒu�\���ς݂��ǂ���
	int m_nCntShowDist;		//�ڕW�ʒu�\���J�E���^�[
	CObject2D* m_pTomare;	//�O�O�����~�܂�UI
	CScore* m_pTomareDist;	//�~�܂�UI�̋��������̐���
	float m_fPosPlayerMin;	//�v���C���[�̍ŏ��̈ʒu
	float m_fPosPlayerMax;	//�v���C���[�̍ő�̈ʒu
	int m_nCntGameOver;		//�Q�[���I����̃J�E���g
};

#endif // !_GAME_SCENE03_H_