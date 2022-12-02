//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "scene.h"
#include "titleScene.h"
#include "selectGameScene.h"
#include "gameScene.h"
#include "gameScene01.h"
#include "gameScene02.h"
#include "resultScene.h"
#include "find_wolf_scene.h"
#include "finalResultScene.h"
#include "object.h"	

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CScene::SCENE_TYPE CScene::m_typeScene = CScene::SCENE_TYPE::TITLE;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CScene::CScene()
{
	m_pPlayer = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// シーンの初期化処理
//=============================================================================
void CScene::Init(void) {

}

//=============================================================================
// シーンの終了処理
//=============================================================================
void CScene::Uninit(void) {
	//オブジェクトの破棄
	CObject::ReleaseAll();
	//テクスチャのアンロード
	CTexture::Unload();
}

//=============================================================================
// シーンの更新処理
//=============================================================================
void CScene::Update(void) {

}

//=============================================================================
// シーンの変更
//=============================================================================
void CScene::ChangeScene(CScene*& pScene, SCENE_TYPE typeScene) {
	//現在のシーンの破棄
	if (pScene != nullptr) {
		pScene->Uninit();
		delete pScene;
		pScene = nullptr;
	}

	//新しいシーンの生成
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

	case CScene::SCENE_TYPE::FIND_WOLF:
		pScene = new CFindWolfScene;
		break;

	case CScene::SCENE_TYPE::FINAL_RESULT:
		pScene = new CFinalResultScene;
		break;
	}

	if (pScene != nullptr) pScene->Init();
}