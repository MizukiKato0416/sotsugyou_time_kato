//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "input.h"
#include "gameScene.h"

#include "wallCylinder.h"
#include "effect.h"
#include "particle.h"
#include "particleEffect.h"
#include "object2D.h"
#include "billboard.h"

//=============================================================================
// マクロ定義
//=============================================================================
//--------------------------------
//ファイル名
//--------------------------------
#define TEXT_FILE_NAME_LOAD_MOTION "data/MOTION/motion_player.txt"

//--------------------------------
//移動
//--------------------------------
#define ADD_MOVE_SPEED (1.0f)	//加速
#define DEC_MOVE_SPEED (0.3f)	//減速
#define MAX_MOVE_SPEED (15.0f)	//歩行速度
#define ROTATE_SPEED (0.05f)	//回転速度

//--------------------------------
//当たり判定
//--------------------------------
#define COLLISION_RADIUS (70.0f)		//当たり判定の半径	壁とかに使う
#define NUM_COLLISION (10)				//当たり判定の数

//--------------------------------
//ゲームオーバー時
//--------------------------------
#define FINISH_TIME_CHANGE_COLOR_GAMEOVER (120)	//ゲームオーバー後の色変更にかかる時間
#define START_CHANGE_COLOR_CLEAR (180)	//ゲームオーバー後の透明色へ変更する開始時間
#define FINISH_TIME_CLEAR (60)			//ゲームオーバー後の透明色への変更にかかる時間

//--------------------------------
//その他
//--------------------------------
#define COLOR_OUTLINE (D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f))	//モデルの輪郭の色

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CPlayer::CPlayer() : CObjectModel(CModel::MODELTYPE::OBJ_CAR, false)
{
	SetObjType(OBJTYPE_PLAYER);	//オブジェクトタイプの設定
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);	//更新順の設定
	SetDrawPriority(DRAW_PRIORITY::CHARA);	//描画順の設定

	m_lastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_destRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nCntGameover = 0;
	m_fMoveSpeed = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// プレイヤーの生成処理
//=============================================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos) {
	CPlayer* pPlayer;
	pPlayer = new CPlayer();
	if (pPlayer == nullptr) return nullptr;

	pPlayer->SetPos(pos);
	pPlayer->Init();

	return pPlayer;
}

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CPlayer::Init(void) {
	//プレイヤーの初期設定
	CObjectModel::SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	m_destRot.y =  D3DX_PI;	//奥向き
	m_fMoveSpeed = 0.0f;


	//マネージャーの取得
	CManager* pManager = CManager::GetManager();

	CObjectModel::Init();

	return S_OK;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CPlayer::Uninit(void) {
	//終了処理
	CObjectModel::Uninit();
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CPlayer::Update(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();

	CInput* pInput = nullptr;
	CSound *pSound = nullptr;
	CCamera* pCamera = nullptr;
	CGameScene* pGame = nullptr;

	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
		//サウンドの取得
		pSound = pManager->GetSound();
		//カメラの取得
		pCamera = pManager->GetCamera();
		//ゲームシーンの取得
		pGame = pManager->GetGameScene();
	}

	//位置情報のポインタの取得
	D3DXVECTOR3 posPlayer = GetPos();


	//----------------------------
	//カメラの設定
	//----------------------------
	float fRotCameraY = 0.0f;	//カメラの角度
	if (pCamera != nullptr) {
		fRotCameraY = pCamera->GetRot().y;	//カメラの角度を取得
	}

	//----------------------------
	//移動
	//----------------------------

	//移動と回転
	if (pInput != nullptr) {
		Move(pInput, fRotCameraY);
	}

	//減速
	DecMove();

	//----------------------------
	//移動の反映
	//----------------------------
	//最後の位置座標の保存
	m_lastPos = posPlayer;
	//移動
	posPlayer += m_move;
	//位置設定
	SetPos(posPlayer);

	//----------------------------
	//当たり判定
	//----------------------------
	Collision(posPlayer);

	//----------------------------
	//モーションの更新
	//----------------------------
	CObjectModel::Update();
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CPlayer::Draw(void) {
	if (m_nCntGameover >= START_CHANGE_COLOR_CLEAR + FINISH_TIME_CLEAR) return;	//フェード完了時は描画しない 影や透過の影響をなくすため

	CObjectModel::Draw();
}

//=============================================================================
// プレイヤーのゲームオーバー時の処理
//=============================================================================
void CPlayer::GameOver(void) {
	
	
}

//=============================================================================
// プレイヤーの当たり判定の情報の取得
//=============================================================================
void CPlayer::GetCollisionInfo(int nIdxColParts, int* const pNumCol, D3DXVECTOR3** const ppPosColArray, float* const pRadiusCol) {
	
}

//=============================================================================
// プレイヤーの最後の位置座標の取得
//=============================================================================
D3DXVECTOR3 CPlayer::GetLastPos(void) {
	return m_lastPos;
}

//=============================================================================
// プレイヤーの移動量の設定
//=============================================================================
void CPlayer::SetMove(D3DXVECTOR3 move) { m_move = move; }

//=============================================================================
// プレイヤーの移動量の取得
//=============================================================================
D3DXVECTOR3 CPlayer::GetMove(void) { return m_move; }

//=============================================================================
// プレイヤーの当たり判定の半径の取得
//=============================================================================
float CPlayer::GetRadius(void) {
	return COLLISION_RADIUS;
}

//=============================================================================
// 移動
//=============================================================================
void CPlayer::Move(CInput* pInput, float fRotCameraY) {
	if (pInput == nullptr) return;

	//上下左右キー入力状態の取得
	const bool bPressUp = pInput->GetPress(CInput::CODE::MOVE_UP);
	const bool bPressDown = pInput->GetPress(CInput::CODE::MOVE_DOWN);
	const bool bPressLeft = pInput->GetPress(CInput::CODE::MOVE_LEFT);
	const bool bPressRight = pInput->GetPress(CInput::CODE::MOVE_RIGHT);

	bool bDiagonalMove = (bPressUp != bPressDown) && (bPressLeft != bPressRight);	//斜め移動
	bool bRotateUp, bRotateDown, bRotateLeft, bRotateRight;	//回転する方向
	bRotateUp = bRotateDown = bRotateLeft = bRotateRight = false;

	D3DXVECTOR3 moveAddSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//追加する移動量
	D3DXVECTOR3 moveMaxSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量の最大

	//------------------------
	//移動速度の最大を計算
	//------------------------
	float fMaxSpeed;	//移動速度の最大
	//地上
	//if (pInput->GetPress(CInput::CODE::DASH)) {
	//	fMaxSpeed = MAX_MOVE_SPEED_DASH;
	//}
	//else {
	fMaxSpeed = MAX_MOVE_SPEED;
	//}


	//------------------------
	//移動量の決定
	//------------------------
	////前後移動のどちらかのみ押されている場合
	//if (bPressUp != bPressDown) {
	//	if (bPressUp) {
	//		moveAddSpeed.z = ADD_MOVE_SPEED;
	//		moveMaxSpeed.z = fMaxSpeed;
	//		bRotateUp = true;
	//	}
	//	else if (bPressDown) {
	//		moveAddSpeed.z = -ADD_MOVE_SPEED;
	//		moveMaxSpeed.z = -fMaxSpeed;
	//		bRotateDown = true;
	//	}
	//	//斜め移動
	//	if (bDiagonalMove) {
	//		moveAddSpeed.z *= 0.7f;
	//		moveMaxSpeed.z *= 0.7f;
	//	}
	//}
	////左右移動のどちらかのみ押されている場合
	//if (bPressLeft != bPressRight) {
	//	if (bPressLeft) {
	//		moveAddSpeed.x = -ADD_MOVE_SPEED;
	//		moveMaxSpeed.x = -fMaxSpeed;
	//		bRotateLeft = true;
	//	}
	//	else if (bPressRight) {
	//		moveAddSpeed.x = ADD_MOVE_SPEED;
	//		moveMaxSpeed.x = fMaxSpeed;
	//		bRotateRight = true;
	//	}
	//	//斜め移動
	//	if (bDiagonalMove) {
	//		moveAddSpeed.x *= 0.7f;
	//		moveMaxSpeed.x *= 0.7f;
	//	}
	//}

	//前後移動のどちらかのみ押されている場合
	if (bPressUp != bPressDown) {
		if (bPressUp) {
			bRotateUp = true;
		}
		else if (bPressDown) {
			bRotateDown = true;
		}
	}
	//左右移動のどちらかのみ押されている場合
	if (bPressLeft != bPressRight) {
		if (bPressLeft) {
			bRotateLeft = true;
		}
		else if (bPressRight) {
			bRotateRight = true;
		}
	}


	//Aボタンを押している間向いている方向に進む
	if (pInput->GetPress(CInput::CODE::ACCELE))
	{
		//加速させる
		m_fMoveSpeed += ADD_MOVE_SPEED;
		//最大値よりも大きくなったら
		if (m_fMoveSpeed > 8.0f)
		{
			m_fMoveSpeed = 8.0f;
		}
	}
	else if (pInput->GetPress(CInput::CODE::REVERSE))
	{//Bボタンを押したら
		//加速させる
		m_fMoveSpeed -= ADD_MOVE_SPEED;
		//最大値よりも大きくなったら
		if (m_fMoveSpeed < -8.0f)
		{
			m_fMoveSpeed = -8.0f;
		}
	}

	m_move.x = sinf(GetRot().y + D3DX_PI) * m_fMoveSpeed;
	m_move.z = cosf(GetRot().y + D3DX_PI) * m_fMoveSpeed;

	//------------------------
	//カメラの角度に合わせて移動量の最大量を設定
	//------------------------
	D3DXVECTOR3 moveMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動の最大量
	moveMax.x += moveMaxSpeed.x * sinf(fRotCameraY + 0.5f * D3DX_PI);
	moveMax.x += moveMaxSpeed.z * sinf(fRotCameraY);

	moveMax.z += moveMaxSpeed.x * -sinf(fRotCameraY);
	moveMax.z += moveMaxSpeed.z * cosf(fRotCameraY);

	//------------------------
	//加速
	//------------------------
	//X方向の移動量が最大量未満の場合
	if ((moveMax.x > 0 && m_move.x < moveMax.x) || (moveMax.x < 0 && m_move.x > moveMax.x)) {
		//カメラの角度に合わせて移動量を追加
		m_move.x += moveAddSpeed.x * sinf(fRotCameraY + 0.5f * D3DX_PI);
		m_move.x += moveAddSpeed.z * sinf(fRotCameraY);
		//加速時に移動量が最大を超えた場合
		if (moveMax.x > 0) {
			if (m_move.x > moveMax.x) {
				m_move.x = moveMax.x;
			}
		}
		else if (moveMax.x < 0) {
			if (m_move.x < moveMax.x) {
				m_move.x = moveMax.x;
			}
		}
	}
	//Z方向の移動量が最大量未満の場合
	if ((moveMax.z > 0 && m_move.z < moveMax.z) || (moveMax.z < 0 && m_move.z > moveMax.z)) {
		//カメラの角度に合わせて移動量を追加
		m_move.z += moveAddSpeed.x * -sinf(fRotCameraY);
		m_move.z += moveAddSpeed.z * cosf(fRotCameraY);
		//加速時に移動量が最大を超えた場合
		if (moveMax.z > 0) {
			if (m_move.z > moveMax.z) {
				m_move.z = moveMax.z;
			}
		}
		else if (moveMax.z < 0) {
			if (m_move.z < moveMax.z) {
				m_move.z = moveMax.z;
			}
		}
	}

	//------------------------
	//回転方向の決定
	//------------------------		
	bool bInputMove = false;	//移動キーを押しているかどうか
	bInputMove = bRotateUp || bRotateDown || bRotateLeft || bRotateRight;	//どれかが押されている場合
	//移動キー押下中
	if (bInputMove) {
		//キーを押していた方向を目標の角度にする
		//上
		if (bRotateUp) {
			if (bRotateRight) {
				m_destRot.y = D3DX_PI * -0.75f + fRotCameraY;
			}
			else if (bRotateLeft) {
				m_destRot.y = D3DX_PI * 0.75f + fRotCameraY;
			}
			else {
				m_destRot.y = D3DX_PI + fRotCameraY;
			}
		}
		//下
		else if (bRotateDown) {
			if (bRotateRight) {
				m_destRot.y = D3DX_PI * -0.25f + fRotCameraY;
			}
			else if (bRotateLeft) {
				m_destRot.y = D3DX_PI * 0.25f + fRotCameraY;
			}
			else {
				m_destRot.y = 0.0f + fRotCameraY;
			}
		}
		//左右
		else {
			if (bRotateRight) {
				m_destRot.y = D3DX_PI * -0.5f + fRotCameraY;
			}
			else if (bRotateLeft) {
				m_destRot.y = D3DX_PI * 0.5f + fRotCameraY;
			}
		}

		//パイ超過時
		if (m_destRot.y > D3DX_PI) {
			m_destRot.y = -D3DX_PI * 2 + m_destRot.y;
		}
		else if (m_destRot.y < -D3DX_PI) {
			m_destRot.y = D3DX_PI * 2 + m_destRot.y;
		}

		D3DXVECTOR3 rotPlayer = CObjectModel::GetRot();//角度の取得
		float fdeltaRot;	//角度の差分
		//現在の角度と目標の角度の差分の計算
		if (m_destRot.y >= 0.0f) {
			if (rotPlayer.y >= 0.0f) {
				fdeltaRot = m_destRot.y - rotPlayer.y;
			}
			else if (rotPlayer.y < 0.0f) {
				if (m_destRot.y - rotPlayer.y >= D3DX_PI) {
					fdeltaRot = -D3DX_PI - rotPlayer.y - D3DX_PI + m_destRot.y;
				}
				else if (m_destRot.y - rotPlayer.y < D3DX_PI) {
					fdeltaRot = m_destRot.y - rotPlayer.y;
				}
			}
		}
		else if (m_destRot.y < 0.0f) {
			if (rotPlayer.y >= 0.0f) {
				if (rotPlayer.y - m_destRot.y >= D3DX_PI) {
					fdeltaRot = D3DX_PI - rotPlayer.y + D3DX_PI + m_destRot.y;
				}
				else if (rotPlayer.y - m_destRot.y < D3DX_PI) {
					fdeltaRot = m_destRot.y - rotPlayer.y;
				}
			}
			else if (rotPlayer.y < 0.0f) {
				fdeltaRot = m_destRot.y - rotPlayer.y;
			}
		}

		//回転の反映
		rotPlayer.y += fdeltaRot * ROTATE_SPEED * (m_fMoveSpeed / 8.0f);

		//パイ超過時
		if (rotPlayer.y > D3DX_PI) {
			rotPlayer.y = -D3DX_PI;
		}
		else if (rotPlayer.y < -D3DX_PI) {
			rotPlayer.y = D3DX_PI;
		}

		//角度の設定
		CObjectModel::SetRot(rotPlayer);
	}
}

//=============================================================================
// 移動量の減少
//=============================================================================
void CPlayer::DecMove(void) {
	D3DXVECTOR2 vecMoveDec = D3DXVECTOR2(-m_move.x, -m_move.z);	//移動量ベクトルの逆
	D3DXVec2Normalize(&vecMoveDec, &vecMoveDec);	//正規化
	vecMoveDec *= DEC_MOVE_SPEED;	//移動量の加算

	//減速
	//m_move.x += vecMoveDec.x;
	//m_move.z += vecMoveDec.y;

	m_fMoveSpeed *= 0.95f;

	if (m_fMoveSpeed < 0.1f && m_fMoveSpeed > 0.1f)
	{
		m_fMoveSpeed = 0.0f;
	}

	////X方向の移動量の停止
	//if (vecMoveDec.x > 0.0f) {
	//	if (m_move.x > 0.0f) {
	//		m_move.x = 0.0f;
	//	}
	//}
	//else if (vecMoveDec.x < 0.0f) {
	//	if (m_move.x < 0.0f) {
	//		m_move.x = 0.0f;
	//	}
	//}
	////Z方向の移動量の停止
	//if (vecMoveDec.y > 0.0f) {
	//	if (m_move.z > 0.0f) {
	//		m_move.z = 0.0f;
	//	}
	//}
	//else if (vecMoveDec.x < 0.0f) {
	//	if (m_move.z < 0.0f) {
	//		m_move.z = 0.0f;
	//	}
	//}
}

//=============================================================================
// 当たり判定
//=============================================================================
void CPlayer::Collision(D3DXVECTOR3& pos) {
	//壁との当たり判定
	CWallCylinder::Collision(&pos, m_lastPos, COLLISION_RADIUS);
}