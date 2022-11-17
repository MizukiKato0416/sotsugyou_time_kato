//=============================================================================
//
// 最終結果カメラ処理 [finalResultCamera.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "finalResultCamera.h"
#include "manager.h"
#include "renderer.h"
#include "gameScene.h"
#include "object_player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_DRAW_DISTANCE		(6000.0f)	//描画可能な最大の距離
#define DEFAULT_CAMERA_DISTANCE (1200.0f)	//視点と注視点の距離
#define DEFAULT_CAMERA_ROT_X	(-15.0f)	//カメラの向きX
#define DEFAULT_CAMERA_POS_Z	(-120.0f)	//カメラの位置Z

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CFinalResultCamera::CFinalResultCamera() : CCamera(MAX_DRAW_DISTANCE)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CFinalResultCamera::~CFinalResultCamera()
{

}

//=============================================================================
// 最終結果カメラの生成処理
//=============================================================================
CFinalResultCamera* CFinalResultCamera::Create(void) {
	CFinalResultCamera* pFinalResultCamera;
	pFinalResultCamera = new CFinalResultCamera();
	if (pFinalResultCamera == nullptr) return nullptr;

	pFinalResultCamera->Init();

	return pFinalResultCamera;
}

//=============================================================================
// 最終結果カメラの初期化処理
//=============================================================================
HRESULT CFinalResultCamera::Init(void) {
	SetPos(D3DXVECTOR3(0.0f, -500.0f, 0.0f));
	SetRot(D3DXVECTOR3(DEFAULT_CAMERA_ROT_X * (D3DX_PI / 180.0f), 0.0f, 0.0f));
	SetLockControll(true);

	//距離の設定
	SetDistance(DEFAULT_CAMERA_DISTANCE);

	//------------------------------------
	//視点と注視点の設定
	//------------------------------------
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fDist = DEFAULT_CAMERA_DISTANCE;

	SetPosR(pos);
	SetPosV(pos + D3DXVECTOR3(sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		sinf(rot.x + D3DX_PI) * fDist,
		cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));

	CCamera::Init();

	return S_OK;
}

//=============================================================================
// 最終結果カメラの終了処理
//=============================================================================
void CFinalResultCamera::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// 最終結果カメラの更新処理
//=============================================================================
void CFinalResultCamera::Update(void) {
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