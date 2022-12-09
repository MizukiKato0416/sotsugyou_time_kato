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
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����
	void GameOver(void);		//�Q�[���I�[�o�[

private:
	void UpdateGame(void);					//�Q�[�����̍X�V
	void UpdateGameOver(void);				//�Q�[���I�[�o�[���̍X�V
	void UpdateReady(void);					//������Ԓ��̍X�V
	void CreatePlayerIcon(int nCntPlayer);	//�v���C���[�A�C�R����������
	void CountDownUi(void);					//�J�E���g�_�E��UI�̏���
	void UpdateCamera(void);				//�J�����̈ʒu�̍X�V

	CObjplayerStop* m_apPlayer[MAX_OBJECT_PLAYER_NUM];			//�v���C���[�̃|�C���^
	CObjectPlayerIcon *m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM];	//�v���C���[�A�C�R���̃|�C���^
	float m_fDestDist;		//�ڕW�̋���
	int m_nCntGameClear;	//�Q�[���N���A��̃J�E���g
};

#endif // !_GAME_SCENE03_H_