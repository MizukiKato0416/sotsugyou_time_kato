//=============================================================================
//
// ゲームカメラ03処理 [gameCamera03.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "gameCamera03.h"
#include "gameScene.h"
#include "manager.h"
#include "object_player.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_DRAW_DISTANCE		(50000.0f)	//描画可能な最大の距離
#define DEFAULT_CAMERA_DISTANCE (1500.0f)	//視点と注視点の距離
#define DEFAULT_CAMERA_ROT_X	(-20.0f)	//カメラの向きX
#define DEFAULT_CAMERA_POS	(D3DXVECTOR3(0.0f, 50.0f, 0.0f))

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGameCamera03::CGameCamera03() : CCamera(MAX_DRAW_DISTANCE)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CGameCamera03::~CGameCamera03()
{

}

//=============================================================================
// ゲームカメラの生成処理
//=============================================================================
CGameCamera03* CGameCamera03::Create(void) {
	CGameCamera03* pGameCamera;
	pGameCamera = new CGameCamera03();
	if (pGameCamera == nullptr) return nullptr;

	pGameCamera->Init();

	return pGameCamera;
}

//=============================================================================
// ゲームカメラの初期化処理
//=============================================================================
HRESULT CGameCamera03::Init(void) {
	SetPos(DEFAULT_CAMERA_POS);
	SetRot(D3DXVECTOR3(DEFAULT_CAMERA_ROT_X * (D3DX_PI / 180.0f), D3DX_PI * -0.0f, 0.0f));
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
// ゲームカメラの終了処理
//=============================================================================
void CGameCamera03::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// ゲームカメラの更新処理
//=============================================================================
void CGameCamera03::Update(void) {
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