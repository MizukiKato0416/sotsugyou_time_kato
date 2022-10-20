//=============================================================================
//
// �Q�[���V�[��01���� [gameScene01.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _GAME_SCENE01_H_
#define _GAME_SCENE01_H_

#include "gameScene.h"
#include "main.h"
#include "object_player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BALLOON_MAX_NUM		(3)		//���D����x�ɏo����

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObjectPlayerIcon;
class CObjectPlayerBalloonCar;

//*****************************************************************************
// �Q�[���V�[���N���X
//*****************************************************************************
class CGameScene01 : public CGameScene
{
public:
	CGameScene01();	//�f�t�H���g�R���X�g���N�^
	virtual ~CGameScene01();	//�f�X�g���N�^
	void Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void GameOver(void);	//�Q�[���I�[�o�[

private:
	void UpdateGame(void);					//�Q�[�����̍X�V
	void UpdateGameOver(void);				//�Q�[���I�[�o�[���̍X�V

	void CreateBalloon(void);				//���D��������
	void CreateItemBox(void);				//�A�C�e���{�b�N�X��������
	void CreatePlayerIcon(int nCntPlayer);	//�v���C���[�A�C�R����������
	void CountDownUi(void);					//�J�E���g�_�E��UI�̏���

	CObjectPlayerBalloonCar* m_apPlayer[MAX_OBJECT_PLAYER_NUM];			//�v���C���[�̃|�C���^
	CObjectPlayerIcon *m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM];			//�v���C���[�A�C�R���̃|�C���^

	int m_nCntGameClear;					//�Q�[���N���A��̃J�E���g
	int m_nCreateItemBoxCounter;			//�A�C�e���{�b�N�X�̐����J�E���^
};

#endif // !_GAME_SCENE01_H_