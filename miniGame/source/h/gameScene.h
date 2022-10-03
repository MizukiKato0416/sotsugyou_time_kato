//=============================================================================
//
// �Q�[���V�[������ [gameScene.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CStage;
class CTimer;
class CObject2D;
class CPauseMenu;
class CSelectMenu2D;
class CScore;

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
	void UpdateGame(void);			//�Q�[�����̍X�V
	void UpdateGameOver(void);		//�Q�[���I�[�o�[���̍X�V
	void CreateMenuEndGame(void);	//�Q�[���I�����̑I�����j���[�̐���

	bool m_bGameOver;	//�Q�[���I�[�o�[

	CStage* m_pStage;				//�X�e�[�W�ւ̃|�C���^
	CTimer* m_pTimer;				//�Q�[���̃^�C�}�[
	CObject2D* m_pTimerFrame;		//�^�C�}�[�̘g
	int m_nGameScore;				//�Q�[���I�����̃X�R�A
	CPauseMenu* m_pMenuPause;		//�|�[�Y���j���[
	CSelectMenu2D* m_pMenuGameEnd;	//�Q�[���I�����̑I�����j���[

	int m_nCntGameClear;	//�Q�[���N���A��̃J�E���g
};

#endif // !_GAME_SCENE_H_