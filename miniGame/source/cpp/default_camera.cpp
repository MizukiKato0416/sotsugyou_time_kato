//=============================================================================
//
// デフォルトカメラ処理 [default_camera.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "default_camera.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_DRAW_DISTANCE (2000.0f)		//描画可能な最大の距離
#define DEFAULT_CAMERA_DISTANCE (1000.0f)	//視点と注視点の距離

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CDefaultCamera::CDefaultCamera() : CCamera(MAX_DRAW_DISTANCE)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CDefaultCamera::~CDefaultCamera()
{

}

//=============================================================================
// タイトルカメラの生成処理
//=============================================================================
CDefaultCamera* CDefaultCamera::Create(void) {
	CDefaultCamera* pDefaultCamera;
	pDefaultCamera = new CDefaultCamera();
	if (pDefaultCamera == nullptr) return nullptr;

	pDefaultCamera->Init();

	return pDefaultCamera;
}

//=============================================================================
// タイトルカメラの初期化処理
//=============================================================================
HRESULT CDefaultCamera::Init(void) {
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetRot(D3DXVECTOR3(D3DX_PI * -0.1f, D3DX_PI * 0.0f, 0.0f));
	//距離の設定
	SetDistance(DEFAULT_CAMERA_DISTANCE);

	CCamera::Init();

	//カメラのコントロール不可
	SetLockControll(true);

	return S_OK;
}

//=============================================================================
// タイトルカメラの終了処理
//=============================================================================
void CDefaultCamera::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// タイトルカメラの更新処理
//=============================================================================
void CDefaultCamera::Update(void) {
	CCamera::Update();

	D3DXVECTOR3 rot = GetRot();
	//回転させる
	rot.y += 0.005f;
	if (rot.y > D3DX_PI) {
		rot.y -= D3DX_PI * 2;
	}
	SetRot(rot);

	//------------------------------------
	//視点と注視点の設定
	//------------------------------------
	D3DXVECTOR3 pos = GetPos();
	float fDist = GetDistance();

	SetPosR(pos);
	SetPosV(D3DXVECTOR3(pos.x + sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		pos.y + sinf(rot.x + D3DX_PI) * fDist,
		pos.z + cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));	//視点が中心の場合から変更したときに移動がないようにX回転にPIを足している
}