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
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	bool ChangeColTime(bool bCol);	// �^�C�g���V�[���̐F���ς�鎞�Ԃ̏���

private:
	void Cloud();				//�_�̏���
	void PlayerModel();			//�v���C���[�̃��f���̏���
	void Camera();				//�J�����̏���

	static CObject2D * m_pNext;	// �I�u�W�F�N�g2D�̐ÓI�|�C���^�[����
	const int m_nDivideNum;		// ���鐔
	const int m_nMaxColTime;	// �F���ς�鎞�Ԃ̍ő�l
	const float m_fMaxCol;		// �F�̍ő�l
	int m_nFadeTime;			// �J�ڂ��鎞��	
	int m_nColorTime;			// �F��ς��鎞��	
	bool m_bCol;				// �F��ς��邩�ǂ���
	bool m_bPushKey;			// �����ꂽ���ǂ���

	std::vector<CMeshwall*> m_pCloud;							//�_�̃|�C���^
	CObjectModel *m_pPlayerModel[MAX_OBJECT_PLAYER_NUM];		//�v���C���[�̃��f��
};

#endif // !_TITLE_SCENE_H_