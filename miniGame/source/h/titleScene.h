//=============================================================================
//
// �^�C�g���V�[������ [titleScene.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "scene.h"
#include "object_player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_LOGO_CHARA_NUM	(4)		//�^�C�g�����S�̕���

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;
class CMeshwall;
class CObjectModel;

//*****************************************************************************
// �^�C�g���V�[���N���X
//*****************************************************************************
class CTitleScene : public CScene
{
public:
	CTitleScene();	//�f�t�H���g�R���X�g���N�^
	virtual ~CTitleScene();	//�f�X�g���N�^
	void Init(void);	//����������
	void CreateObject(void);	//�I�u�W�F�N�g��������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	bool ChangeColTime(bool bCol);	// �^�C�g���V�[���̐F���ς�鎞�Ԃ̏���

private:
	//�t�F�[�Y
	enum class PHASE
	{
		NONE = 0,
		CHARACTOR_LOGO,		//�����̃��S
		THE_FINAL_LOGO,		//�U�t�@�C�i���̃��S
		BOUND_LOGO,			//���S�̃o�E���h
		STOP_TITLE_LOGO,	//�^�C�g�����S��~
		MAX
	};

	void PlayerModel();			//�v���C���[�̃��f���̏���
	void Camera();				//�J�����̏���
	void CharactorLogo();		//�����̃��S�̏���
	void TheFinalLogo();		//�U�t�@�C�i���̃��S�̏���
	void BoundLogo();			//���S�̃o�E���h�̏���
	void StopTitleLogo();		//�^�C�g�����S��~
	void ExplosionLogo();		//�������S�̏���
	void CarLogo();				//�ԃ��S�̏���
	bool CreateAllLogo();		//�S�Ẵ��S�𐶐����鏈��
	void DeleteLogo();			//���S��������
	void Decide();				//���菈��
	bool Reset();				//���Z�b�g����


	static CObject2D * m_pNext;	// �I�u�W�F�N�g2D�̐ÓI�|�C���^�[����
	const int m_nDivideNum;		// ���鐔
	const int m_nMaxColTime;	// �F���ς�鎞�Ԃ̍ő�l
	const float m_fMaxCol;		// �F�̍ő�l
	int m_nFadeTime;			// �J�ڂ��鎞��	
	int m_nColorTime;			// �F��ς��鎞��	
	bool m_bCol;				// �F��ς��邩�ǂ���
	bool m_bPushKey;			// �����ꂽ���ǂ���

	CObjectModel *m_pPlayerModel[MAX_OBJECT_PLAYER_NUM];		//�v���C���[�̃��f��
	CObject2D *m_pTitleLogoChara[TITLE_LOGO_CHARA_NUM];			//�^�C�g�����S�̕���
	CObject2D *m_pTheFinalLogo;									//�U�t�@�C�i�����S
	CObject2D *m_pTitleLogo;									//�^�C�g�����S
	CObject2D *m_pExplosionLogo;								//�������S
	CObject2D *m_pTitleLogoCar;									//�ԃ��S

	int m_nFrameCounter;					//�t���[���J�E���^�[
	int m_nFrameCounterReset;				//�t���[���J�E���^�[(���Z�b�g�p)
	PHASE m_phase;							//�t�F�[�Y
	float m_fBoundMove;						//�o�E���h�ړ���
	bool m_bExplosionAddSize;				//�T�C�Y��傫�����邩�ǂ���
	bool m_bCarLogoRight;					//�E�ɂ��邩�ǂ���
	float m_fCarLogoMove;					//�ԃ��S�̈ړ���
	bool m_bCreateAllLogo;					//�S�Ẵ��S�𐶐�������Ԃ��ǂ���
};

#endif // !_TITLE_SCENE_H_