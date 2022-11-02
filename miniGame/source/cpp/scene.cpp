//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "scene.h"
#include "titleScene.h"
#include "selectGameScene.h"
#include "gameScene.h"
#include "gameScene01.h"
#include "gameScene02.h"
#include "resultScene.h"
#include "object.h"	

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CScene::SCENE_TYPE CScene::m_typeScene = CScene::SCENE_TYPE::TITLE;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CScene::CScene()
{
	m_pPlayer = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// �V�[���̏���������
//=============================================================================
void CScene::Init(void) {

}

//=============================================================================
// �V�[���̏I������
//=============================================================================
void CScene::Uninit(void) {
	//�I�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
}

//=============================================================================
// �V�[���̍X�V����
//=============================================================================
void CScene::Update(void) {

}

//=============================================================================
// �V�[���̕ύX
//=============================================================================
void CScene::ChangeScene(CScene*& pScene, SCENE_TYPE typeScene) {
	//���݂̃V�[���̔j��
	if (pScene != nullptr) {
		pScene->Uninit();
		delete pScene;
		pScene = nullptr;
	}

	//�V�����V�[���̐���
	m_typeScene = typeScene;

	switch (typeScene)
	{
	case CScene::SCENE_TYPE::TITLE:
		pScene = new CTitleScene;
		break;

	case CScene::SCENE_TYPE::SELECT_GAME:
		pScene = new CSelectGameScene;
		break;

	case CScene::SCENE_TYPE::GAME_01:
		pScene = new CGameScene01;
		break;

	case CScene::SCENE_TYPE::GAME_02:
		pScene = new CGameScene02;
		break;

	case CScene::SCENE_TYPE::RESULT:
		pScene = new CResultScene;
		break;
	}

	if (pScene != nullptr) pScene->Init();
}