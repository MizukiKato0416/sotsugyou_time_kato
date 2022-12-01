//=============================================================================
//
// タイトルカメラ処理 [titleCamera.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "titleCamera.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TITLE_CAMERA_MAX_DRAW_DISTANCE			(4000.0f)	//描画可能な最大の距離
#define TITLE_CAMERA_DEFAULT_CAMERA_DISTANCE	(50.0f)		//視点と注視点の距離
#define TITLE_CAMERA_ROT_X						(40.0f)		//カメラの向きX
#define TITLE_CAMERA_POS_Z						(-550.0f)	//カメラの位置Z
#define TITLE_CAMERA_POS_Y						(20.0f)		//カメラの位置Y

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTitleCamera::CTitleCamera() : CCamera(TITLE_CAMERA_MAX_DRAW_DISTANCE)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleCamera::~CTitleCamera()
{

}

//=============================================================================
// ゲームカメラの生成処理
//=============================================================================
CTitleCamera* CTitleCamera::Create(void) {
	CTitleCamera* pTitleCamera;
	pTitleCamera = new CTitleCamera();
	if (pTitleCamera == nullptr) return nullptr;

	pTitleCamera->Init();

	return pTitleCamera;
}

//=============================================================================
// ゲームカメラの初期化処理
//=============================================================================
HRESULT CTitleCamera::Init(void) {
	SetPos(D3DXVECTOR3(0.0f, TITLE_CAMERA_POS_Y, TITLE_CAMERA_POS_Z));
	SetRot(D3DXVECTOR3(TITLE_CAMERA_ROT_X * (D3DX_PI / 180.0f), D3DX_PI * -0.0f, 0.0f));
	SetLockControll(true);

	//距離の設定
	SetDistance(TITLE_CAMERA_DEFAULT_CAMERA_DISTANCE);

	//------------------------------------
	//視点と注視点の設定
	//------------------------------------
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fDist = TITLE_CAMERA_DEFAULT_CAMERA_DISTANCE;

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
void CTitleCamera::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// ゲームカメラの更新処理
//=============================================================================
void CTitleCamera::Update(void) {
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