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
#define MAX_DRAW_DISTANCE			(50000.0f)							//描画可能な最大の距離
#define DEFAULT_CAMERA_DISTANCE		(1500.0f)							//視点と注視点の距離
#define DEFAULT_CAMERA_ROT_X		(-10.0f)							//カメラの向きX
#define DEFAULT_CAMERA_POS			(D3DXVECTOR3(0.0f, 50.0f, 0.0f))	//カメラの初期位置

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGameCamera03::CGameCamera03() : CCamera(MAX_DRAW_DISTANCE)
{
	m_bMove = false;
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
	m_destPos = DEFAULT_CAMERA_POS;
	m_fDestDist = DEFAULT_CAMERA_DISTANCE;
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

	D3DXVECTOR3 posCamera = GetPos();	//位置の取得
	float fDist = GetDistance();		//距離の取得

	if (m_bMove) {
		//目標位置まで移動
		posCamera.x += m_fSpeedMoveDest;
		if (m_fSpeedMoveDest > 0.0f) {
			if (posCamera.x > m_destPos.x) posCamera.x = m_destPos.x;
		}
		else if (m_fSpeedMoveDest < 0.0f) {
			if (posCamera.x < m_destPos.x) posCamera.x = m_destPos.x;
		}
		//位置の設定
		SetPos(posCamera);


		//目標距離まで移動
		if (fDist < m_fDestDist) {
			fDist += m_fSpeedDist;
			if (fDist > m_fDestDist) fDist = m_fDestDist;
		}

		//距離の更新
		SetDistance(fDist);
	}

	//------------------------------------
	//視点と注視点の設定
	//------------------------------------
	D3DXVECTOR3 rot = GetRot();

	SetPosR(posCamera);
	SetPosV(posCamera + D3DXVECTOR3(sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		sinf(rot.x + D3DX_PI) * fDist,
		cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));
}

//=============================================================================
// 目標位置を決める
//=============================================================================
void CGameCamera03::SetDestPos(float fDestPos, int nFrameMove) {
	m_bMove = true;
	m_destPos.x = fDestPos;
	m_fSpeedMoveDest = (m_destPos.x - GetPos().x) / nFrameMove;
}

//=============================================================================
// 見渡す
//=============================================================================
void CGameCamera03::OverLook(float fMinPos, float fMaxPos, int nFrameMove) {
	m_bMove = true;

	float fDistMinToMax = fMaxPos - fMinPos;	//最低位置から最大位置への距離

	//目標のX位置を中心にする
	m_destPos.x = fMinPos + fDistMinToMax / 2.0f;
	m_fSpeedMoveDest = (m_destPos.x - GetPos().x) / nFrameMove;

	m_fDestDist = fDistMinToMax * 1.2f;	//だいたいこのくらい
	m_fSpeedDist = (m_fDestDist - GetDistance()) / nFrameMove;
}