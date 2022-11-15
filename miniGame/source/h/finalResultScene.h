//=============================================================================
//
// �ŏI���ʃV�[������ [finalResultScene.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _FINAL_RESULT_SCENE_H_
#define _FINAL_RESULT_SCENE_H_

#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;
class CObjectModel;

//*****************************************************************************
// �ŏI���ʃV�[���N���X
//*****************************************************************************
class CFinalResultScene : public CScene
{
public:
	CFinalResultScene();	//�f�t�H���g�R���X�g���N�^
	virtual ~CFinalResultScene();	//�f�X�g���N�^
	void Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����

private:
	void UpdateInput(void);	//���͏���

	CObjectModel* m_apObjPlayer[4];		//�v���C���[�̃��f���I�u�W�F�N�g
	CObjectModel* m_apResultTower[4];	//�v���C���[�̉��ɂ���^���[�̃��f���I�u�W�F�N�g
	int m_nFadeTime;	//�t�F�[�h�J�n�܂ł̃J�E���g
	bool m_bSelectGame;	//�I���L�[������

};

#endif // !_FINAL_RESULT_SCENE_H_