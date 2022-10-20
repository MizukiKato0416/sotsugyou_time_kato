//=============================================================================
//
// 衝突ゲーム用車処理 [object_player_attack_car.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "object_player_attack_car.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "input.h"
#include "PresetSetEffect.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================

//--------------------------------
//移動
//--------------------------------
#define ATTACK_CAR_ADD_MOVE_SPEED			(0.15f)		//加速
#define ATTACK_CAR_DEC_MOVE_SPEED			(0.93f)		//減速
#define ATTACK_CAR_MAX_MOVE_SPEED			(9.0f)		//最大速度
#define ATTACK_CAR_MOVE_ZERO_RANGE			(0.08f)		//移動量を0にする範囲

#define ATTACK_CAR_ROTATE_SPEED			(0.025f)	//回転速度

//--------------------------------
//当たり判定
//--------------------------------
#define COLLISION_RADIUS (40.0f)		//当たり判定の半径	壁とかに使う

//--------------------------------
//その他
//--------------------------------

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObjectPlayerAttackCar::CObjectPlayerAttackCar()
{
	SetObjType(OBJTYPE_PLAYER);						//オブジェクトタイプの設定
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);		//更新順の設定
	SetDrawPriority(DRAW_PRIORITY::CHARA);			//描画順の設定

	m_lastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_destRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fMoveSpeed = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObjectPlayerAttackCar::~CObjectPlayerAttackCar()
{
	
}

//=============================================================================
// プレイヤーの生成処理
//=============================================================================
CObjectPlayerAttackCar* CObjectPlayerAttackCar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot) {
	
	CObjectPlayerAttackCar* pObjectPlayer;
	pObjectPlayer = new CObjectPlayerAttackCar();
	if (pObjectPlayer == nullptr) return nullptr;

	pObjectPlayer->SetPos(pos);
	pObjectPlayer->Init();
	pObjectPlayer->SetRot(rot);

	return pObjectPlayer;
}

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CObjectPlayerAttackCar::Init(void) {

	CObjectPlayer::Init();

	//プレイヤーの初期設定
	CObjectModel::SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	m_destRot.y =  D3DX_PI;	//奥向き
	m_fMoveSpeed = 0.0f;

	return S_OK;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CObjectPlayerAttackCar::Uninit(void) {

	CObjectPlayer::Uninit();
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CObjectPlayerAttackCar::Update(void) {
	//更新しない設定なら
	if (!GetPlayer()->GetUpdate())
	{
		return;
	}

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
	}

	//位置情報のポインタの取得
	D3DXVECTOR3 posObjectPlayer = GetPos();


	//----------------------------
	//カメラの設定
	//----------------------------
	float fRotCameraY = 0.0f;	//カメラの角度
	if (pCamera != nullptr) {
		fRotCameraY = pCamera->GetRot().y;	//カメラの角度を取得
	}

	//移動と回転
	if (pInput != nullptr) {
		Move(pInput, fRotCameraY);
	}

	//----------------------------
	//移動の反映
	//----------------------------
	//最後の位置座標の保存
	m_lastPos = posObjectPlayer;
	//移動
	posObjectPlayer += m_move;
	//位置設定
	SetPos(posObjectPlayer);

	//----------------------------
	//当たり判定
	//----------------------------
	Collision(posObjectPlayer);

	CObjectPlayer::Update();
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CObjectPlayerAttackCar::Draw(void) {
	
	CObjectPlayer::Draw();
}

//=============================================================================
// プレイヤーのゲームオーバー時の処理
//=============================================================================
void CObjectPlayerAttackCar::GameOver(void) {
	
	CObjectPlayer::GameOver();
}

//=============================================================================
// プレイヤーの最後の位置座標の取得
//=============================================================================
D3DXVECTOR3 CObjectPlayerAttackCar::GetLastPos(void) {
	return m_lastPos;
}

//=============================================================================
// プレイヤーの移動量の設定
//=============================================================================
void CObjectPlayerAttackCar::SetMove(D3DXVECTOR3 move) { m_move = move; }

//=============================================================================
// プレイヤーの移動量の取得
//=============================================================================
D3DXVECTOR3 CObjectPlayerAttackCar::GetMove(void) { return m_move; }

//=============================================================================
// プレイヤーの当たり判定の半径の取得
//=============================================================================
float CObjectPlayerAttackCar::GetRadius(void) {
	return COLLISION_RADIUS;
}

//=============================================================================
// 移動
//=============================================================================
void CObjectPlayerAttackCar::Move(CInput* pInput, float fRotCameraY) {
	if (pInput == nullptr) return;

	//上下左右キー入力状態の取得
	const bool bPressUp = pInput->GetPress(CInput::CODE::MOVE_UP, GetPlayer()->GetIndex() - 1);
	const bool bPressDown = pInput->GetPress(CInput::CODE::MOVE_DOWN, GetPlayer()->GetIndex() - 1);
	const bool bPressLeft = pInput->GetPress(CInput::CODE::MOVE_LEFT, GetPlayer()->GetIndex() - 1);
	const bool bPressRight = pInput->GetPress(CInput::CODE::MOVE_RIGHT, GetPlayer()->GetIndex() - 1);

	bool bDiagonalMove = (bPressUp != bPressDown) && (bPressLeft != bPressRight);	//斜め移動
	bool bRotateUp, bRotateDown, bRotateLeft, bRotateRight;	//回転する方向
	bRotateUp = bRotateDown = bRotateLeft = bRotateRight = false;

	D3DXVECTOR3 moveAddSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//追加する移動量
	D3DXVECTOR3 moveMaxSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量の最大

	
	//------------------------
	//移動量の決定
	//------------------------

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
	if (pInput->GetPress(CInput::CODE::ACCELE, GetPlayer()->GetIndex() - 1))
	{
		//加速させる
		m_fMoveSpeed += ATTACK_CAR_ADD_MOVE_SPEED;
		//最大値よりも大きくなったら
		if (m_fMoveSpeed > ATTACK_CAR_MAX_MOVE_SPEED)
		{
			m_fMoveSpeed = ATTACK_CAR_MAX_MOVE_SPEED;
		}
		//---------------------------------
		//煙
		CPresetEffect::SetEffect3D(0, GetPos() , {}, {});
		//---------------------------------
	}
	else if (pInput->GetPress(CInput::CODE::REVERSE, GetPlayer()->GetIndex() - 1))
	{//Bボタンを押したら
		//加速させる
		m_fMoveSpeed -= ATTACK_CAR_ADD_MOVE_SPEED;
		//最大値よりも大きくなったら
		if (m_fMoveSpeed < -ATTACK_CAR_MAX_MOVE_SPEED)
		{
			m_fMoveSpeed = -ATTACK_CAR_MAX_MOVE_SPEED;
		}
	}
	else
	{
		//減速
		DecMove();
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

		D3DXVECTOR3 rotObjectPlayer = CObjectModel::GetRot();//角度の取得
		float fdeltaRot;	//角度の差分
		//現在の角度と目標の角度の差分の計算
		if (m_destRot.y >= 0.0f) {
			if (rotObjectPlayer.y >= 0.0f) {
				fdeltaRot = m_destRot.y - rotObjectPlayer.y;
			}
			else if (rotObjectPlayer.y < 0.0f) {
				if (m_destRot.y - rotObjectPlayer.y >= D3DX_PI) {
					fdeltaRot = -D3DX_PI - rotObjectPlayer.y - D3DX_PI + m_destRot.y;
				}
				else if (m_destRot.y - rotObjectPlayer.y < D3DX_PI) {
					fdeltaRot = m_destRot.y - rotObjectPlayer.y;
				}
			}
		}
		else if (m_destRot.y < 0.0f) {
			if (rotObjectPlayer.y >= 0.0f) {
				if (rotObjectPlayer.y - m_destRot.y >= D3DX_PI) {
					fdeltaRot = D3DX_PI - rotObjectPlayer.y + D3DX_PI + m_destRot.y;
				}
				else if (rotObjectPlayer.y - m_destRot.y < D3DX_PI) {
					fdeltaRot = m_destRot.y - rotObjectPlayer.y;
				}
			}
			else if (rotObjectPlayer.y < 0.0f) {
				fdeltaRot = m_destRot.y - rotObjectPlayer.y;
			}
		}

		//回転の反映
		rotObjectPlayer.y += fdeltaRot * ATTACK_CAR_ROTATE_SPEED * (m_fMoveSpeed / 8.0f);

		//パイ超過時
		if (rotObjectPlayer.y > D3DX_PI) {
			rotObjectPlayer.y = -D3DX_PI;
		}
		else if (rotObjectPlayer.y < -D3DX_PI) {
			rotObjectPlayer.y = D3DX_PI;
		}

		//角度の設定
		CObjectModel::SetRot(rotObjectPlayer);
		//---------------------------------
		//土埃
		CPresetEffect::SetEffect3D(1, GetPos(), {}, {});
		//---------------------------------
	}
}

//=============================================================================
// 移動量の減少
//=============================================================================
void CObjectPlayerAttackCar::DecMove(void) {
	//減速
	m_fMoveSpeed *= ATTACK_CAR_DEC_MOVE_SPEED;

	//既定の値の誤差になったら
	if (m_fMoveSpeed < ATTACK_CAR_MOVE_ZERO_RANGE && m_fMoveSpeed > -ATTACK_CAR_MOVE_ZERO_RANGE)
	{
		//移動量を0にする
		m_fMoveSpeed = 0.0f;
	}
}

//=============================================================================
// 当たり判定
//=============================================================================
void CObjectPlayerAttackCar::Collision(D3DXVECTOR3& pos) {

	//プレイヤーとの当たり判定
	CollisionObjectPlayer();
}

//=============================================================================
//プレイヤーとの当たり判定
//=============================================================================
void CObjectPlayerAttackCar::CollisionObjectPlayer(void)
{
	CObject* pObject = GetObjectTopAll();	//全オブジェクトのリストの先頭を取得

	while (pObject != nullptr) {
		CObject* pObjNext = GetObjectNextAll(pObject);	//リストの次のオブジェクトのポインタを取得

		//オブジェクトタイプの確認
		bool bMatchType = false;
		if (pObject->GetObjType() & OBJTYPE_PLAYER) bMatchType = true;

		if (!bMatchType || pObject == this)
		{
			pObject = pObjNext;	//リストの次のオブジェクトを代入
			continue;
		}

		//プレイヤーにキャスト
		CObjectPlayerAttackCar *pObjectPlayer = static_cast<CObjectPlayerAttackCar*> (pObject);

		//プレイヤーの位置を取得
		D3DXVECTOR3 playerPos = pObjectPlayer->GetPos();
		D3DXVECTOR3 myPos = GetPos();

		//二点の距離ベクトル
		D3DXVECTOR2 differVec = D3DXVECTOR2(playerPos.x - myPos.x, playerPos.z - myPos.z);
		//二点の距離
		float fDiffer = D3DXVec2Length(&differVec);

		//当たっていたら
		if (fDiffer <= COLLISION_RADIUS * 2.0f)
		{
			//自身と対象のオブジェクトの角度を求める
			float fRot = atan2((playerPos.x - myPos.x), (playerPos.z - myPos.z));

			//相手の位置を押し出す
			playerPos.x = myPos.x + (sinf(fRot) * (COLLISION_RADIUS * 2.0f));
			playerPos.z = myPos.z + (cosf(fRot) * (COLLISION_RADIUS * 2.0f));

			//位置設定
			pObjectPlayer->SetPos(playerPos);

		}
		pObject = pObjNext;	//リストの次のオブジェクトを代入
	}
}