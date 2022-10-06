//=============================================================================
//
// ゲームカメラ処理 [gameCamera.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "gameCamera.h"
#include "manager.h"
#include "renderer.h"
#include "gameScene.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_DRAW_DISTANCE		(5000.0f)	//描画可能な最大の距離
#define DEFAULT_CAMERA_DISTANCE (1200.0f)	//視点と注視点の距離
#define DEFAULT_CAMERA_ROT_X	(-40.0f)	//カメラの向きX
#define DEFAULT_CAMERA_POS_Z	(-220.0f)	//カメラの位置Z

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGameCamera::CGameCamera() : CCamera(MAX_DRAW_DISTANCE)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CGameCamera::~CGameCamera()
{

}

//=============================================================================
// ゲームカメラの生成処理
//=============================================================================
CGameCamera* CGameCamera::Create(void) {
	CGameCamera* pGameCamera;
	pGameCamera = new CGameCamera();
	if (pGameCamera == nullptr) return nullptr;

	pGameCamera->Init();

	return pGameCamera;
}

//=============================================================================
// ゲームカメラの初期化処理
//=============================================================================
HRESULT CGameCamera::Init(void) {
	SetPos(D3DXVECTOR3(0.0f, 0.0f, DEFAULT_CAMERA_POS_Z));
	SetRot(D3DXVECTOR3(DEFAULT_CAMERA_ROT_X * (D3DX_PI / 180.0f), D3DX_PI * -0.0f, 0.0f));
	SetLockControll(true);

	//距離の設定
	SetDistance(DEFAULT_CAMERA_DISTANCE);

	CCamera::Init();

	return S_OK;
}

//=============================================================================
// ゲームカメラの終了処理
//=============================================================================
void CGameCamera::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// ゲームカメラの更新処理
//=============================================================================
void CGameCamera::Update(void) {
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