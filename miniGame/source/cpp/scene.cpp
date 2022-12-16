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
#include "gameScene03.h"
#include "resultScene.h"
#include "find_wolf_scene.h"
#include "finalResultScene.h"
#include "creditScene.h"
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
	m_bCreateObject = false;
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
	m_bCreateObject = false;
}

//=============================================================================
// �V�[���̏I������
//=============================================================================
void CScene::Uninit(void) {
	//�I�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
	//�e�N�X�`���̃A�����[�h
	CTexture::Unload(false);
}

//=============================================================================
// �V�[���̍X�V����
//=============================================================================
void CScene::Update(void) {

	//���[�h���I��������
	if (!m_bCreateObject && CTexture::GetLoadFinish())
	{
		//�I�u�W�F�N�g�̐���������
		CreateObject();
		m_bCreateObject = true;
	}
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

	case CScene::SCENE_TYPE::GAME_03:
		pScene = new CGameScene03;
		break;

	case CScene::SCENE_TYPE::RESULT:
		pScene = new CResultScene;
		break;

	case CScene::SCENE_TYPE::FIND_WOLF:
		pScene = new CFindWolfScene;
		break;

	case CScene::SCENE_TYPE::FINAL_RESULT:
		pScene = new CFinalResultScene;
		break;
	case CScene::SCENE_TYPE::CREDIT:
		pScene = new CCreditScene;
		break;
	}

	if (pScene != nullptr) pScene->Init();
}