//=============================================================================
//
// �Q�[���V�[������ [gameScene.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "scene.h"
#include "main.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BALLOON_MAX_NUM		(3)		//���D����x�ɏo����

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CStage;
class CTimer;
class CObject2D;
class CPauseMenu;
class CSelectMenu2D;
class CScore;
class CCountDownUi;
class CPlayerIcon;

//*****************************************************************************
// �Q�[���V�[���N���X
//*****************************************************************************
class CGameScene : public CScene
{
public:
	CGameScene();	//�f�t�H���g�R���X�g���N�^
	virtual ~CGameScene();	//�f�X�g���N�^
	void Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void DeletePauseMenu(void);	//�|�[�Y���j���[�̔j��
	void GameOver(void);	//�Q�[���I�[�o�[

	bool GetGameOver(void) { return m_bGameOver; }		//�Q�[���I�[�o�[��Ԃ̃t���O
	CTimer* GetTimer(void) { return m_pTimer; }	//�^�C�}�[�̎擾

private:
	void UpdateGame(void);					//�Q�[�����̍X�V
	void UpdateGameOver(void);				//�Q�[���I�[�o�[���̍X�V
	void CreateMenuEndGame(void);			//�Q�[���I�����̑I�����j���[�̐���
	void CreateBalloon(void);				//���D��������
	void CreateItemBox(void);				//�A�C�e���{�b�N�X��������
	void CreatePlayerIcon(int nCntPlayer);	//�v���C���[�A�C�R����������
	void CountDownUi(void);					//�J�E���g�_�E��UI�̏���

	bool m_bGameOver;	//�Q�[���I�[�o�[

	CStage* m_pStage;								//�X�e�[�W�ւ̃|�C���^
	CTimer* m_pTimer;								//�Q�[���̃^�C�}�[
	CObject2D* m_pTimerFrame;						//�^�C�}�[�̘g
	int m_nGameScore;								//�Q�[���I�����̃X�R�A
	CPauseMenu* m_pMenuPause;						//�|�[�Y���j���[
	CSelectMenu2D* m_pMenuGameEnd;					//�Q�[���I�����̑I�����j���[
	CCountDownUi *m_pCountDownUi;					//�J�E���g�_�E��UI�̃|�C���^
	CPlayer* m_apPlayer[MAX_PLAYER_NUM];			//�v���C���[�̃|�C���^
	CPlayerIcon *m_apPlayerIcon[MAX_PLAYER_NUM];	//�v���C���[�A�C�R���̃|�C���^

	int m_nCntGameClear;					//�Q�[���N���A��̃J�E���g
	int m_nCreateItemBoxCounter;			//�A�C�e���{�b�N�X�̐����J�E���^�[
};

#endif // !_GAME_SCENE_H_