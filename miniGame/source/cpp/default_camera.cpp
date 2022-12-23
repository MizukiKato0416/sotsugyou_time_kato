//=============================================================================
//
// デフォルトカメラ処理 [default_camera.cpp]
// Author : 
//
//=============================================================================
#include "default_camera.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_DRAW_DISTANCE (2000.0f)		//描画可能な最大の距離

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
// デフォルトカメラの生成処理
//=============================================================================
CDefaultCamera* CDefaultCamera::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fDist) {
	CDefaultCamera* pDefaultCamera;
	pDefaultCamera = new CDefaultCamera();
	if (pDefaultCamera == nullptr) return nullptr;

	//注視点と向きの設定
	pDefaultCamera->SetPos(pos);
	pDefaultCamera->SetRot(rot);
	//距離の設定
	pDefaultCamera->SetDistance(fDist);
	//初期化処理
	pDefaultCamera->Init();

	return pDefaultCamera;
}

//=============================================================================
// デフォルトカメラの初期化処理
//=============================================================================
HRESULT CDefaultCamera::Init(void) {
	//------------------------------------
	//視点と注視点の設定
	//------------------------------------
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fDist = GetDistance();

	SetPosR(pos);
	SetPosV(pos + D3DXVECTOR3(sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		sinf(rot.x + D3DX_PI) * fDist,
		cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));

	CCamera::Init();

	return S_OK;
}

//=============================================================================
// デフォルトカメラの終了処理
//=============================================================================
void CDefaultCamera::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// デフォルトカメラの更新処理
//=============================================================================
void CDefaultCamera::Update(void) {
	CCamera::Update();

	//------------------------------------
	//視点と注視点の設定
	//------------------------------------
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fDist = GetDistance();

	SetPosR(pos);
	SetPosV(D3DXVECTOR3(pos.x + sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		pos.y + sinf(rot.x + D3DX_PI) * fDist,
		pos.z + cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));	//視点が中心の場合から変更したときに移動がないようにX回転にPIを足している
}