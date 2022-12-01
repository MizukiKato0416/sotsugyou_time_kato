//=============================================================================
//
// 人狼決定シーンカメラ処理 [find_wolf_camera.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "find_wolf_camera.h"
#include "manager.h"
#include "renderer.h"
#include "gameScene.h"
#include "object_player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FIND_WOLF_CAMERA_MAX_DRAW_DISTANCE		(4000.0f)	//描画可能な最大の距離
#define FIND_WOLF_CAMERA_DEFAULT_CAMERA_DISTANCE (600.0f)	//視点と注視点の距離
#define FIND_WOLF_CAMERA_DEFAULT_CAMERA_ROT_X	(-30.0f)	//カメラの向きX
#define FIND_WOLF_CAMERA_DEFAULT_CAMERA_POS_Z	(30.0f)	//カメラの位置Z

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CFindWolfCamera::CFindWolfCamera() : CCamera(FIND_WOLF_CAMERA_MAX_DRAW_DISTANCE)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CFindWolfCamera::~CFindWolfCamera()
{

}

//=============================================================================
// ゲームカメラの生成処理
//=============================================================================
CFindWolfCamera* CFindWolfCamera::Create(void) {
	CFindWolfCamera* pFindWolfCamera;
	pFindWolfCamera = new CFindWolfCamera();
	if (pFindWolfCamera == nullptr) return nullptr;

	pFindWolfCamera->Init();

	return pFindWolfCamera;
}

//=============================================================================
// ゲームカメラの初期化処理
//=============================================================================
HRESULT CFindWolfCamera::Init(void) {
	SetPos(D3DXVECTOR3(0.0f, 0.0f, FIND_WOLF_CAMERA_DEFAULT_CAMERA_POS_Z));
	SetRot(D3DXVECTOR3(FIND_WOLF_CAMERA_DEFAULT_CAMERA_ROT_X * (D3DX_PI / 180.0f), D3DX_PI * -0.0f, 0.0f));
	SetLockControll(true);

	//距離の設定
	SetDistance(FIND_WOLF_CAMERA_DEFAULT_CAMERA_DISTANCE);

	//------------------------------------
	//視点と注視点の設定
	//------------------------------------
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fDist = FIND_WOLF_CAMERA_DEFAULT_CAMERA_DISTANCE;

	SetPosR(pos);
	SetPosV(pos + D3DXVECTOR3(sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		sinf(rot.x + D3DX_PI) * fDist,
		cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));

	CCamera::Init();

	return S_OK;
}

//=============================================================================
// ゲームカメラの終了処理
//=============================================================================
void CFindWolfCamera::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// ゲームカメラの更新処理
//=============================================================================
void CFindWolfCamera::Update(void) {
	CCamera::Update();

	D3DXVECTOR3 posCamera = GetPos();
	//位置の設定
	SetPos(posCamera);

	//------------------------------------
	//視点と注視点の設定
	//------------------------------------
	D3DXVECTOR3 rot = GetRot();
	float fDist = GetDistance();

	SetPosR(posCamera);
	SetPosV(posCamera + D3DXVECTOR3(sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		sinf(rot.x + D3DX_PI) * fDist,
		cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));
}