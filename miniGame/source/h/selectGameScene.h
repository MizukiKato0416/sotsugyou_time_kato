//=============================================================================
//
// �Q�[���I���V�[������ [selectGameScene.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _SELECT_GAME_SCENE_H_
#define _SELECT_GAME_SCENE_H_

#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SELECT_GAME_SCENE_ALOW_UI_NUM	(2)		//���UI�̐�

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;
class CSelectMenu3D;
class CNextButton;

//*****************************************************************************
// �Q�[���I���V�[���N���X
//*****************************************************************************
class CSelectGameScene : public CScene
{
public:
	CSelectGameScene();	//�f�t�H���g�R���X�g���N�^
	virtual ~CSelectGameScene();	//�f�X�g���N�^
	void Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����

private:
	void UpdateInput(void);				//���͏���
	void ChangeTutorial(void);			//�`���[�g���A���\���̐؂�ւ�
	void ChangeGameTitle();				//�Q�[���^�C�g���̐ؑ�
	void ChangeMode(bool bWolf);		//�R�����[�h�̐؂�ւ�
	void BgMove();						//�w�i�̓����̏���
	void AlowUi();						//���UI�̓�������

	int m_nFadeTime;	//�t�F�[�h�J�n�܂ł̃J�E���g
	bool m_bSelectGame;	//�I���L�[������

	bool m_bWolfMode;									//�R�����[�h
	CObject2D* m_pMenuBG;								//�w�i
	CObject2D* m_pMenuNoneMoveUi;						//�����Ȃ�UI
	CObject2D* m_pAlowUi[SELECT_GAME_SCENE_ALOW_UI_NUM];//���UI
	float m_fAlowUiMove[SELECT_GAME_SCENE_ALOW_UI_NUM];	//���UI�̈ړ���
	bool m_bAlowUiMoveChange[SELECT_GAME_SCENE_ALOW_UI_NUM];//���UI�̈ړ��ʐؑ�
	CSelectMenu3D* m_pMenuGame;							//�J�n����Q�[���̑I�����j���[
	CObject2D* m_pGameName;								//�Q�[����
	CObject2D* m_pTutorial;								//�`���[�g���A�����
	CObject2D *m_pModeUi;								//���[�hUI�̃|�C���^
	CNextButton* m_pNextButton;							//���ւ̃{�^��
	CScene::SCENE_TYPE m_nextScene;						//�J�n����Q�[���V�[���̃^�C�v
};

#endif // !_SELECT_GAME_SCENE_H_