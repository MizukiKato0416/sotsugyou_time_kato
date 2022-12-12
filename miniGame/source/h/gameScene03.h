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

#include "change_color.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObjectPlayerIcon;
class CObjplayerStop;

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
	void UpdatePlayerIcon(void);	//�v���C���[�A�C�R���X�V����
	void CountDownUi(void);					//�J�E���g�_�E��UI�̏���
	void LookPlayerPos(void);				//�v���C���[�̈ʒu�̊Ď�
	void UpdateCamera(void);				//�J�����̈ʒu�̍X�V

	CObjectPlayerIcon *m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM];	//�v���C���[�A�C�R���̃|�C���^
	bool m_bDecideDestDist;	//�ڕW�ʒu����
	float m_fDestPos;		//�ڕW�̋���
	float m_fPosPlayerMin;	//�v���C���[�̍ŏ��̈ʒu
	float m_fPosPlayerMax;	//�v���C���[�̍ő�̈ʒu
	int m_nCntGameOver;		//�Q�[���I����̃J�E���g
};

#endif // !_GAME_SCENE03_H_