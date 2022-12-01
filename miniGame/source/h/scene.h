//=============================================================================
//
// �V�[������ [scene.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObjectPlayer;

//*****************************************************************************
// �V�[���N���X
//*****************************************************************************
class CScene
{
public:
	//�V�[���̎��
	enum class SCENE_TYPE {
		TITLE = 0,
		SELECT_GAME,
		GAME_01,
		GAME_02,
		GAME_MAX,	//�����_���I���̂��߃Q�[���V�[���̍ő��ݒ�
		RESULT,
		FIND_WOLF,
		FINAL_RESULT,
		ENUM_MAX
	};

	CScene();	//�f�t�H���g�R���X�g���N�^
	virtual ~CScene();	//�f�X�g���N�^
	virtual void Init(void) = 0;	//����������
	virtual void Uninit(void) = 0;	//�I������
	virtual void Update(void) = 0;	//�X�V����
	static void ChangeScene(CScene*& pScene, SCENE_TYPE typeScene);	//�V�[���̕ύX
	static SCENE_TYPE GetSceneType(void) { return m_typeScene; }	//���݂̃V�[���̎擾

	//�v���C���[�̃Z�b�^�[�E�Q�b�^�[
	void SetPlayer(CObjectPlayer* pPlayer) { m_pPlayer = pPlayer; }
	CObjectPlayer* GetPlayer(void) { return m_pPlayer; }
private:
	static SCENE_TYPE m_typeScene;
	CObjectPlayer* m_pPlayer;	//�v���C���[�ւ̃|�C���^

};

#endif // !_SCENE_H_