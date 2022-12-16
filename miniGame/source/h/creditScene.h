//=============================================================================
//
// �N���W�b�g�V�[������ [creditScene.h]
// Author : ��������
//
//=============================================================================
#ifndef _CREDIT_SCENE_H_
#define _CREDIT_SCENE_H_

#include "scene.h"
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;
class CNextButton;

//*****************************************************************************
// ���U���g�V�[���N���X
//*****************************************************************************
class CCreditScene : public CScene
{
public:
	CCreditScene();				//�f�t�H���g�R���X�g���N�^
	virtual ~CCreditScene();	//�f�X�g���N�^
	void Init(void);			//����������
	void CreateObject(void);	//�I�u�W�F�N�g��������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����

private:
	void Bg();				//�w�i����
	void Fade();			//�J�ڏ���
	void Credit();			//�N���W�b�g����
	void CreatePicture();	//�G��������

	CObject2D *m_pBg;				//�w�i
	CObject2D *m_pCredit;			//�N���W�b�g
	bool m_bCanFade;				//�t�F�[�h�ł��邩�ǂ���
	int m_nFrameCounter;			//Frame�J�E���g�p
};

#endif // !_CREDIT_SCENE_H_