//=============================================================================
//
// ���U���g�V�[������ [resultScene.h]
// Author : ��������
//
//=============================================================================
#ifndef _RESULT_SCENE_H_
#define _RESULT_SCENE_H_

#include "scene.h"
#include "main.h"
#include "object_player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;
class CObjectModelUI;
class CNextButton;

//*****************************************************************************
// ���U���g�V�[���N���X
//*****************************************************************************
class CResultScene : public CScene
{
public:
	CResultScene();				//�f�t�H���g�R���X�g���N�^
	virtual ~CResultScene();	//�f�X�g���N�^
	void Init(void);			//����������
	void CreateObject(void);	//�I�u�W�F�N�g��������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����

private:
	void PointUI();			//�|�C���gUI�̏���
	void Player();			//�v���C���[�̏���
	void NextButton();		//���ɐi��UI����
	void Bg();				//�w�i����
	void Fade();			//�J�ڏ���
	void FrameCounter();	//�t���[���J�E���g����

	int m_nCntScene;			//�V�[���J�n������̃J�E���g
	int m_nFrameCounter;		//�|�C���gUI�̃J�E���^�[

	CObject2D *m_pBg;											//�w�i
	CObject2D *m_apPointUi[MAX_OBJECT_PLAYER_NUM];				//�|�C���g�pUI
	CObjectModelUI *m_pPlayerModel[MAX_OBJECT_PLAYER_NUM];		//�v���C���[�̃��f��
	CNextButton *m_pNextButton;									//���ɐi�ރ{�^��UI

};

#endif // !_RESULT_SCENE_H_