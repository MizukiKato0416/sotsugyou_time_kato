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
#include "object_player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CTimer;
class CObject2D;
class CPauseMenu;
class CCheck;

//*****************************************************************************
// �Q�[���V�[���N���X
//*****************************************************************************
class CGameScene : public CScene
{
public:
	CGameScene();	//�f�t�H���g�R���X�g���N�^
	virtual ~CGameScene();	//�f�X�g���N�^
	virtual void Init(void);	//����������
	virtual void Uninit(void);	//�I������
	virtual void Update(void);	//�X�V����
	void DeletePauseMenu(void);	//�|�[�Y���j���[�̔j��
	virtual void GameOver(void);	//�Q�[���I�[�o�[

	virtual void UpdateGame(void) = 0;					//�Q�[�����̍X�V
	virtual void UpdateGameOver(void) = 0;				//�Q�[���I�[�o�[���̍X�V

	bool GetGameOver(void) { return m_bGameOver; }		//�Q�[���I�[�o�[��Ԃ̃t���O
	CTimer* GetTimer(void) { return m_pTimer; }			//�^�C�}�[�̎擾

	//�l�T���[�h�ݒ菈��
	static void SetWereWolfMode(const bool bWereWolfMode) { m_bWereWolfMode = bWereWolfMode; }
	//�l�T���[�h�擾����
	static bool GetWereWolfMode(void) { return m_bWereWolfMode; }

	//�l�T�ɂȂ����v���C���[�̃C���f�b�N�X�ݒ菈��(1P��1�A2P��2)
	static void SetWereWolfPlayerIndex(const int nWereWolfPlayerIndex) { m_nWereWolfPlayerIndex = nWereWolfPlayerIndex; }
	//�l�T�ɂȂ����v���C���[�̃C���f�b�N�X�擾����
	static int GetWereWolfPlayerIndex(void) { return m_nWereWolfPlayerIndex; }

private:
	
	static bool m_bWereWolfMode;			//�l�T���[�h�ɂ��邩�ǂ���
	static int m_nWereWolfPlayerIndex;		//�l�T�ɂȂ����v���C���[�̃C���f�b�N�X

protected:

	bool m_bGameOver;	//�Q�[���I�[�o�[
	bool m_bAllCheck;	//�S�����`�F�b�N�ł������ǂ���

	CTimer* m_pTimer;													//�Q�[���̃^�C�}�[
	CObject2D* m_pTimerFrame;											//�^�C�}�[�̘g
	CPauseMenu* m_pMenuPause;											//�|�[�Y���j���[
	CCheck *m_pCheck;													//�`�F�b�N�N���X�̃|�C���^
};

#endif // !_GAME_SCENE_H_