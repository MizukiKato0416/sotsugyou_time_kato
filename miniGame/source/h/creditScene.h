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
	enum class PHASE
	{
		NONE = 0,
		BG_CAR_00,	//�w�i��00
		BG_CAR_01,	//�w�i��01	
		BG_TITLE,	//�w�i�^�C�g��	
		BG_00,		//�w�i00
		BG_01,		//�w�i01
		MAX
	};

	void BgCar00();										//�w�i�ԏ���
	void BgCar01();										//�w�i�ԏ���
	void BgTitle();										//�w�i�^�C�g������
	void Bg00();										//�w�i����
	void BgStage();										//�w�i�X�e�[�W����
	void SceneFade();									//�J�ڏ���
	void Credit();										//�N���W�b�g����
	void CreatePicture();								//�G��������
	void SetFade(const int nCnt, const D3DXCOLOR col);	//�t�F�[�h�ݒ菈��
	void Fade();										//�t�F�[�h����
	void SkipIcon();									//�X�L�b�v�A�C�R������

	CObject2D *m_pBg;				//�w�i
	CObject2D *m_pBgStage;			//�w�i�X�e�[�W
	CObject2D *m_pCredit;			//�N���W�b�g
	CObject2D *m_pFade;				//�t�F�[�h�p
	CObject2D *m_pSkipIcon;			//�X�L�b�v�A�C�R��
	bool m_bCanFade;				//�t�F�[�h�ł��邩�ǂ���
	bool m_bPictureRot;				//�X����؂�ւ���p
	bool m_bFade;					//�t�F�[�h���Ă��邩�ǂ���
	bool m_bFadeIn;					//�t�F�[�h�A�E�g�t�F�[�h�C���؂�ւ�
	bool m_bUninitSkipIcon;			//�X�L�b�v�A�C�R�����������ǂ���
	int m_nFrameCounter;			//Frame�J�E���g�p
	int m_nFadeTime;				//�t�F�[�h�̎���
	int m_nSkipIconCounter;			//�X�L�b�v�A�C�R���̕\�����ԃJ�E���g�p
	D3DXCOLOR m_fadeCol;			//�t�F�[�h�̐F
	PHASE m_phase;					//�t�F�[�Y
};

#endif // !_CREDIT_SCENE_H_