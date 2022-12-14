//=============================================================================
//
// 風船ゲーム用車処理 [object_player_balloon_car.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "object_player_balloon_car.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "input.h"
#include "gameScene.h"

#include "wallCylinder.h"
#include "effect.h"
#include "object2D.h"
#include "billboard.h"
#include "item_banana.h"

#include "PresetSetEffect.h"
#include "PresetDelaySet.h"
#include "score_ui.h"
#include "score.h"
#include "player.h"
#include "gameScene01.h"

//=============================================================================
// マクロ定義
//=============================================================================

//--------------------------------
//移動
//--------------------------------
#define ADD_MOVE_SPEED								(0.15f)			//加速
#define DEC_MOVE_SPEED								(0.93f)			//減速
#define MAX_MOVE_SPEED								(9.0f)			//最大速度
#define MAX_MOVE_SPEED_STEAL_POINT					(9.0f * 1.3f)	//最大速度(ポイント奪取時)
#define MOVE_ZERO_RANGE								(0.08f)			//移動量を0にする範囲
#define ROTATE_SPEED								(0.025f)		//回転速度
#define OBJECT_PLAYER_BALLOON_CAR_BOUND_SPEED		(0.9f)			//バウンドする量

//--------------------------------
//当たり判定
//--------------------------------
#define COLLISION_RADIUS (40.0f)		//当たり判定の半径	壁とかに使う

//--------------------------------
//回転
//--------------------------------
#define OBJECT_PLAYER_BALLOON_CAR_SPIN_COUNT			(90)		//スピンする時間
#define OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED			(0.3f)		//スピンする速さ
#define OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED_DEC		(0.91f)		//スピンする速さ減算値
#define OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED_DEC_COUNT	(60)		//スピンする速さ減速させる時間

//--------------------------------
//無敵
//--------------------------------
#define OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COUNTER	(150)	//無敵時間
#define OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ALPHA	(0.7f)	//無敵時のα値
#define OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD	(0.3f)	//無敵時のカラー加算値

//--------------------------------
//その他
//--------------------------------
#define COLOR_OUTLINE								(D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f))	//モデルの輪郭の色
#define SCORE_UI_POS_Y								(650.0f)							//スコアUIの位置Y

//--------------------------------
//アイテム
//--------------------------------
#define OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_POS_Y		(580.0f)							//アイテムUIの位置Y
#define OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_POS_X		(90.0f)								//アイテムUIの位置X調整値
#define OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_SIZE		(50.0f)								//アイテムUIのサイズ
#define OBJECT_PLAYER_BALLOON_CAR_STEAL_POINT		(2)									//相手から奪うポイントの量
#define OBJECT_PLAYER_BALLOON_CAR_STEAL_POINT_TIME	(60 * 3)							//相手から奪う状態の時間


//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObjectPlayerBalloonCar::CObjectPlayerBalloonCar()
{
	SetObjType(OBJTYPE_PLAYER);						//オブジェクトタイプの設定
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);		//更新順の設定
	SetDrawPriority(DRAW_PRIORITY::CHARA);			//描画順の設定

	m_lastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fMoveSpeed = 0.0f;
	m_fBoundMoveSpeed = 0.0f;
	m_fSpinSpeed = 0.0f;
	m_state = OBJECT_PLAYER_BALLOON_CAR_STATE::NONE;
	m_itemType = CItem::ITEM_TYPE::NONE;
	m_nSpinCounter = 0;
	m_nInvincbleCounter = 0;
	m_nStealPointCounter = 0;
	m_bBound = false;
	m_bStealPoint = false;
	m_pSocreUi = nullptr;
	m_pItemUi = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObjectPlayerBalloonCar::~CObjectPlayerBalloonCar()
{
	
}

//=============================================================================
// プレイヤーの生成処理
//=============================================================================
CObjectPlayerBalloonCar* CObjectPlayerBalloonCar::Create(D3DXVECTOR3 pos) {
	
	CObjectPlayerBalloonCar* pObjectPlayer;
	pObjectPlayer = new CObjectPlayerBalloonCar();
	if (pObjectPlayer == nullptr) return nullptr;

	pObjectPlayer->SetPos(pos);
	pObjectPlayer->Init();

	return pObjectPlayer;
}

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CObjectPlayerBalloonCar::Init(void) {

	CObjectPlayer::Init();

	//プレイヤーの初期設定
	CObjectModel::SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	m_fMoveSpeed = 0.0f;
	m_fBoundMoveSpeed = 0.0f;
	m_state = OBJECT_PLAYER_BALLOON_CAR_STATE::NORMAL;
	m_itemType = CItem::ITEM_TYPE::NONE;
	m_nSpinCounter = 0;
	m_nInvincbleCounter = 0;
	m_bBound = false;
	m_bStealPoint = false;
	m_fSpinSpeed = OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED;
	m_pItemUi = nullptr;
	m_nStealPointCounter = 0;

	return S_OK;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CObjectPlayerBalloonCar::Uninit(void) {

	CObjectPlayer::Uninit();
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CObjectPlayerBalloonCar::Update(void) {
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
		//ゲームシーンの取得
		pGame = pManager->GetGameScene();
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

	//状態分け
	switch (m_state)
	{
	case CObjectPlayerBalloonCar::OBJECT_PLAYER_BALLOON_CAR_STATE::NORMAL:
		//移動と回転
		if (pInput != nullptr && !m_bBound) {
			Move(pInput, fRotCameraY);
		}
		break;
	case CObjectPlayerBalloonCar::OBJECT_PLAYER_BALLOON_CAR_STATE::INVINCIBLE:
		//移動と回転
		if (pInput != nullptr && !m_bBound) {
			Move(pInput, fRotCameraY);
		}

		//無敵処理
		StateInvincble();
		break;
	case CObjectPlayerBalloonCar::OBJECT_PLAYER_BALLOON_CAR_STATE::SPIN:
		//スピン処理
		StateSpin();
		break;
	default:
		break;
	}	

	//バウンド処理
	StateBound();

	//----------------------------
	//移動の反映
	//----------------------------
	//最後の位置座標の保存
	m_lastPos = posObjectPlayer;
	//移動
	posObjectPlayer += m_move;
	//位置設定
	SetPos(posObjectPlayer);

	//L1ボタンを押したら
	if (pInput->GetTrigger(CInput::CODE::USE_ITEM, GetPlayer()->GetIndex() - 1))
	{
		//アイテム使用
		UseItem();
	}

	//ポイント奪取状態
	StealPoint();

	//アイテムUIの処理
	ItemUi();

	//----------------------------
	//当たり判定
	//----------------------------
	Collision(posObjectPlayer);

	CObjectPlayer::Update();
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CObjectPlayerBalloonCar::Draw(void) {
	
	CObjectPlayer::Draw();
}

//=============================================================================
// プレイヤーのゲームオーバー時の処理
//=============================================================================
void CObjectPlayerBalloonCar::GameOver(void) {
	
	CObjectPlayer::GameOver();
}

//=============================================================================
// プレイヤーの最後の位置座標の取得
//=============================================================================
D3DXVECTOR3 CObjectPlayerBalloonCar::GetLastPos(void) {
	return m_lastPos;
}

//=============================================================================
// プレイヤーの移動量の設定
//=============================================================================
void CObjectPlayerBalloonCar::SetMove(D3DXVECTOR3 move) { m_move = move; }

//=============================================================================
// プレイヤーの移動量の取得
//=============================================================================
D3DXVECTOR3 CObjectPlayerBalloonCar::GetMove(void) { return m_move; }

//=============================================================================
// プレイヤーの当たり判定の半径の取得
//=============================================================================
float CObjectPlayerBalloonCar::GetRadius(void) {
	return COLLISION_RADIUS;
}

//=============================================================================
//スコア生成処理
//=============================================================================
void CObjectPlayerBalloonCar::CreateScore()
{
	//スコアUIの生成 
	m_pSocreUi = CScoreUi::Create(D3DXVECTOR3(SCREEN_WIDTH / (MAX_OBJECT_PLAYER_NUM + 1) * GetPlayer()->GetIndex(), SCORE_UI_POS_Y, 0.0f),
		                          D3DXVECTOR3(0.5f, 0.5f, 0.5f), GetPlayer()->GetIndex());
}

//=============================================================================
//アイテムUIのフレーム生成処理
//=============================================================================
void CObjectPlayerBalloonCar::CreateItemUiFrame()
{
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / (MAX_OBJECT_PLAYER_NUM + 1) * GetPlayer()->GetIndex() - OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_POS_X, OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_POS_Y, 0.0f),
		              CTexture::TEXTURE_TYPE((int)CTexture::TEXTURE_TYPE::ITEM_UI_FRAME_1 + GetPlayer()->GetIndex() - 1), OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_SIZE, OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_SIZE);
}

//=============================================================================
// 移動
//=============================================================================
void CObjectPlayerBalloonCar::Move(CInput* pInput, float fRotCameraY) {
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

	//最大速度
	float fMaxSpeed = MAX_MOVE_SPEED;
	//ポイント奪取時
	if (m_bStealPoint) fMaxSpeed = MAX_MOVE_SPEED_STEAL_POINT;

	//Aボタンを押している間向いている方向に進む
	if (pInput->GetPress(CInput::CODE::ACCELE, GetPlayer()->GetIndex() - 1))
	{
		//加速させる
		m_fMoveSpeed += ADD_MOVE_SPEED;
		//最大値よりも大きくなったら
		if (m_fMoveSpeed > fMaxSpeed)
		{
			m_fMoveSpeed = fMaxSpeed;
		}
		//---------------------------------
		//煙
		CPresetEffect::SetEffect3D(0, GetPos() , {}, {});
		//---------------------------------
	}
	else if (pInput->GetPress(CInput::CODE::REVERSE, GetPlayer()->GetIndex() - 1))
	{//Bボタンを押したら
		//加速させる
		m_fMoveSpeed -= ADD_MOVE_SPEED;
		//最大値よりも大きくなったら
		if (m_fMoveSpeed < -fMaxSpeed)
		{
			m_fMoveSpeed = -fMaxSpeed;
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
		float destRotY;	//目標角度

		//キーを押していた方向を目標の角度にする
		//上
		if (bRotateUp) {
			if (bRotateRight) {
				destRotY = D3DX_PI * -0.75f + fRotCameraY;
			}
			else if (bRotateLeft) {
				destRotY = D3DX_PI * 0.75f + fRotCameraY;
			}
			else {
				destRotY = D3DX_PI + fRotCameraY;
			}
		}
		//下
		else if (bRotateDown) {
			if (bRotateRight) {
				destRotY = D3DX_PI * -0.25f + fRotCameraY;
			}
			else if (bRotateLeft) {
				destRotY = D3DX_PI * 0.25f + fRotCameraY;
			}
			else {
				destRotY = 0.0f + fRotCameraY;
			}
		}
		//左右
		else {
			if (bRotateRight) {
				destRotY = D3DX_PI * -0.5f + fRotCameraY;
			}
			else if (bRotateLeft) {
				destRotY = D3DX_PI * 0.5f + fRotCameraY;
			}
		}

		//パイ超過時
		if (destRotY > D3DX_PI) {
			destRotY += -D3DX_PI * 2;
		}
		else if (destRotY < -D3DX_PI) {
			destRotY += D3DX_PI * 2;
		}

		//後進時は逆向き
		if (m_fMoveSpeed < 0.0f) {
			destRotY += D3DX_PI;
			if (destRotY > D3DX_PI) {
				destRotY += -D3DX_PI * 2;
			}
		}

		D3DXVECTOR3 rotObjectPlayer = CObjectModel::GetRot();//角度の取得
		float fdeltaRot;	//角度の差分
		//現在の角度と目標の角度の差分の計算
		if (destRotY >= 0.0f) {
			if (rotObjectPlayer.y >= 0.0f) {
				fdeltaRot = destRotY - rotObjectPlayer.y;
			}
			else if (rotObjectPlayer.y < 0.0f) {
				if (destRotY - rotObjectPlayer.y >= D3DX_PI) {
					fdeltaRot = -D3DX_PI - rotObjectPlayer.y - D3DX_PI + destRotY;
				}
				else if (destRotY - rotObjectPlayer.y < D3DX_PI) {
					fdeltaRot = destRotY - rotObjectPlayer.y;
				}
			}
		}
		else if (destRotY < 0.0f) {
			if (rotObjectPlayer.y >= 0.0f) {
				if (rotObjectPlayer.y - destRotY >= D3DX_PI) {
					fdeltaRot = D3DX_PI - rotObjectPlayer.y + D3DX_PI + destRotY;
				}
				else if (rotObjectPlayer.y - destRotY < D3DX_PI) {
					fdeltaRot = destRotY - rotObjectPlayer.y;
				}
			}
			else if (rotObjectPlayer.y < 0.0f) {
				fdeltaRot = destRotY - rotObjectPlayer.y;
			}
		}

		//回転の反映
		rotObjectPlayer.y += fdeltaRot * ROTATE_SPEED * (fabsf(m_fMoveSpeed) / 8.0f);

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
void CObjectPlayerBalloonCar::DecMove(void) {
	int n = GetPlayer()->GetIndex() - 1;
	//減速
	m_fMoveSpeed *= DEC_MOVE_SPEED;

	//既定の値の誤差になったら
	if (m_fMoveSpeed < MOVE_ZERO_RANGE && m_fMoveSpeed > -MOVE_ZERO_RANGE)
	{
		//移動量を0にする
		m_fMoveSpeed = 0.0f;
	}
}

//=============================================================================
// 移動量の減少
//=============================================================================
void CObjectPlayerBalloonCar::DecBoundMove(void) {
	//減速
	m_fBoundMoveSpeed *= DEC_MOVE_SPEED;

	//既定の値の誤差になったら
	if (m_fBoundMoveSpeed < MOVE_ZERO_RANGE && m_fBoundMoveSpeed > -MOVE_ZERO_RANGE)
	{
		//移動量を0にする
		m_fBoundMoveSpeed = 0.0f;
		m_fMoveSpeed = 0.0f;

		//状態を通常にする
		m_bBound = false;
	}
}

//=============================================================================
// 当たり判定
//=============================================================================
void CObjectPlayerBalloonCar::Collision(D3DXVECTOR3& pos) {

	//プレイヤーとの当たり判定
	CollisionObjectPlayer();

	//壁との当たり判定
	if (CWallCylinder::Collision(&pos, m_lastPos, COLLISION_RADIUS))
	{
		//位置設定
		SetPos(pos);

		if (m_state == OBJECT_PLAYER_BALLOON_CAR_STATE::SPIN)
		{
			//return;
		}

		if (m_bBound)
		{
			return;
		}

		//状態をBOUNDに設定
		m_bBound = true;

		//バウンド時の初速を設定
		m_fBoundMoveSpeed = m_fMoveSpeed * OBJECT_PLAYER_BALLOON_CAR_BOUND_SPEED;
		//最小値の範囲より小さくなったら
		if (m_fBoundMoveSpeed < MOVE_ZERO_RANGE && m_fBoundMoveSpeed > -MOVE_ZERO_RANGE)
		{
			//移動量を0にする
			m_fBoundMoveSpeed = 0.0f;
			m_fMoveSpeed = 0.0f;

			//状態を通常にする
			m_bBound = false;
		}
	}
}

//=============================================================================
//プレイヤーとの当たり判定
//=============================================================================
void CObjectPlayerBalloonCar::CollisionObjectPlayer(void)
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
		CObjectPlayerBalloonCar *pObjectPlayer = static_cast<CObjectPlayerBalloonCar*> (pObject);

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
			float fRot = atan2((myPos.x - playerPos.x), (myPos.z - playerPos.z));

			//自身の位置を押し出す
			myPos.x = playerPos.x + (sinf(fRot) * (COLLISION_RADIUS * 2.0f));
			myPos.z = playerPos.z + (cosf(fRot) * (COLLISION_RADIUS * 2.0f));

			//位置設定
			SetPos(myPos);

			if (!m_bStealPoint) return;

			//ポイントを奪う状態なら
			//相手のポイントを奪う

			int nAddScore = OBJECT_PLAYER_BALLOON_CAR_STEAL_POINT;
			if (pObjectPlayer->GetScoreUi()->GetScore()->GetScore() <= OBJECT_PLAYER_BALLOON_CAR_STEAL_POINT)
			{
				nAddScore = pObjectPlayer->GetScoreUi()->GetScore()->GetScore();
			}
			m_pSocreUi->GetScore()->AddScore(nAddScore);

			//マネージャーの取得
			CManager* pManager = CManager::GetManager();
			//サウンドの取得
			CSound* pSound = nullptr;
			if (pManager != nullptr) pSound = pManager->GetSound();
			//音を再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_POINT_STEAL);

			//スコアが最大値を超えたら
			if (GetScoreUi()->GetScore()->GetScore() > BALLOON_SCORE_MAX)
			{
				//超えないようにする
				GetScoreUi()->GetScore()->SetScore(BALLOON_SCORE_MAX);
			}

			pObjectPlayer->GetScoreUi()->GetScore()->AddScore(-nAddScore);
			m_bStealPoint = false;
			m_nStealPointCounter = 0;
		}
		pObject = pObjNext;	//リストの次のオブジェクトを代入
	}
}

//=============================================================================
//バウンド状態の処理
//=============================================================================
void CObjectPlayerBalloonCar::StateBound(void)
{
	if (m_bBound)
	{
		//向いている方向と逆の方向に跳ね返す
		m_move.x = sinf(GetRot().y) * m_fBoundMoveSpeed;
		m_move.z = cosf(GetRot().y) * m_fBoundMoveSpeed;

		//移動量の減少
		DecBoundMove();
	}
}

//=============================================================================
//スピン状態の処理
//=============================================================================
void CObjectPlayerBalloonCar::StateSpin(void)
{
	//カウンター加算
	m_nSpinCounter++;
	//既定の値より大きくなったら
	if (m_nSpinCounter > OBJECT_PLAYER_BALLOON_CAR_SPIN_COUNT)
	{
		m_nSpinCounter = 0;
		//状態を無敵にする
		m_state = OBJECT_PLAYER_BALLOON_CAR_STATE::INVINCIBLE;
	}
	else
	{
		//向き取得
		D3DXVECTOR3 rot = GetRot();

		if (m_nSpinCounter > OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED_DEC_COUNT)
		{
			//減速させる
			m_fSpinSpeed *= OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED_DEC;
		}
		else
		{
			m_fSpinSpeed = OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED;
		}

		//回転させる
		rot.y += m_fSpinSpeed;

		//向き設定
		SetRot(rot);
	}
}

//=============================================================================
//無敵状態の処理
//=============================================================================
void CObjectPlayerBalloonCar::StateInvincble(void)
{
	//最初だけ
	if (m_nInvincbleCounter == 0)
	{
		//モデル取得
		CModel *pModel = GetPtrModel();
		if (pModel != nullptr)
		{
			//マテリアル数取得
			int nNumMat = CModel::GetNumMat(pModel->GetModelType());

			for (int nCntMat = 0; nCntMat < nNumMat; nCntMat++)
			{
				//カラー取得
				D3DXCOLOR col = pModel->GetMaterialDiffuse(nCntMat);

				//薄くする
				col.a = OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ALPHA;
				//色を加算
				col.r += OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD;
				col.g += OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD;
				col.b += OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD;

				//色設定
				pModel->SetMaterialDiffuse(col, nCntMat);
			}
		}
	}

	m_nInvincbleCounter++;
	if (m_nInvincbleCounter > OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COUNTER)
	{
		m_nInvincbleCounter = 0;

		//モデル取得
		CModel *pModel = GetPtrModel();
		if (pModel != nullptr)
		{
			//マテリアル数取得
			int nNumMat = CModel::GetNumMat(pModel->GetModelType());

			for (int nCntMat = 0; nCntMat < nNumMat; nCntMat++)
			{
				//カラー取得
				D3DXCOLOR col = pModel->GetMaterialDiffuse(nCntMat);

				//元に戻す
				col.a = 1.0f;
				//色を減算
				col.r -= OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD;
				col.g -= OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD;
				col.b -= OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD;

				//色設定
				pModel->SetMaterialDiffuse(col, nCntMat);
			}
		}

		//通常状態にする
		m_state = OBJECT_PLAYER_BALLOON_CAR_STATE::NORMAL;
	}
}

//=============================================================================
//アイテム使用処理
//=============================================================================
void CObjectPlayerBalloonCar::UseItem(void)
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;

	//アイテムを持っている状態なら
	if (m_itemType == CItem::ITEM_TYPE::NONE || m_state == OBJECT_PLAYER_BALLOON_CAR_STATE::SPIN)
	{
		return;
	}

	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//アイテムを生成する
	switch (m_itemType)
	{
	case CItem::ITEM_TYPE::BANANA:
		//バナナの生成
		CItemBanana::Create(pos, this);
		break;
	case CItem::ITEM_TYPE::STEAL_POINT:
		//ポイントを奪う状態にする
		m_bStealPoint = true;
		m_itemType = CItem::ITEM_TYPE::NONE;
		m_nStealPointCounter = 0;

		if (pManager != nullptr) pSound = pManager->GetSound();
		//音を再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_USE_POINT_STEAL);
		break;
	default:
		break;
	}

	//アイテムUIを消す
	if (m_pItemUi != nullptr)
	{
		m_pItemUi->Uninit();
		m_pItemUi = nullptr;
	}
}

//=============================================================================
//アイテムUi処理
//=============================================================================
void CObjectPlayerBalloonCar::ItemUi(void)
{
	//アイテムを持っていない状態またはアイテムUIが生成されているなら
	if (m_itemType == CItem::ITEM_TYPE::NONE || m_pItemUi != nullptr)
	{
		return;
	}
	
	//アイテムのUI生成
	m_pItemUi = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / (MAX_OBJECT_PLAYER_NUM + 1) * GetPlayer()->GetIndex() - OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_POS_X, OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_POS_Y, 0.0f),
		                          CTexture::TEXTURE_TYPE::NONE, OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_SIZE, OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_SIZE);

	//テクスチャを変更
	switch (m_itemType)
	{
	case CItem::ITEM_TYPE::BANANA:
		m_pItemUi->SetTexType(CTexture::TEXTURE_TYPE::ITEM_BANANA);
		break;
	case CItem::ITEM_TYPE::STEAL_POINT:
		m_pItemUi->SetTexType(CTexture::TEXTURE_TYPE::ITEM_GASOLINE);
		break;
	default:
		break;
	}
}

//=============================================================================
//ポイント奪取処理
//=============================================================================
void CObjectPlayerBalloonCar::StealPoint()
{
	if (!m_bStealPoint) return;

	//ポイントを奪う状態なら
	m_nStealPointCounter++;

	//エフェクト
	CPresetDelaySet::Create(4, GetPos(), {}, {});

	if (m_nStealPointCounter <= OBJECT_PLAYER_BALLOON_CAR_STEAL_POINT_TIME) return;

	//時間外なら
	m_bStealPoint = false;
	m_nStealPointCounter = 0;
}
