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
#include "item_banana.h"

//=============================================================================
// マクロ定義
//=============================================================================
//--------------------------------
//ファイル名
//--------------------------------
#define TEXT_FILE_NAME_LOAD_MOTION "data/MOTION/motion_player.txt"

//--------------------------------
//プレイヤーカラー
//--------------------------------
#define PLAYER_COLOR_1P		(D3DXCOLOR(0.1f, 0.3f, 1.0f, 1.0f))	//1pのカラー
#define PLAYER_COLOR_2P		(D3DXCOLOR(1.0f, 0.2f, 0.0f, 1.0f))	//2pのカラー
#define PLAYER_COLOR_3P		(D3DXCOLOR(0.1f, 0.7f, 0.0f, 1.0f))	//3pのカラー
#define PLAYER_COLOR_4P		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//4pのカラー

//--------------------------------
//移動
//--------------------------------
#define ADD_MOVE_SPEED (1.0f)	//加速
#define DEC_MOVE_SPEED (0.3f)	//減速
#define MAX_MOVE_SPEED (15.0f)	//歩行速度
#define ROTATE_SPEED (0.1f)		//回転速度

//--------------------------------
//当たり判定
//--------------------------------
#define COLLISION_RADIUS (40.0f)		//当たり判定の半径	壁とかに使う

//--------------------------------
//回転
//--------------------------------
#define PLAYER_SPIN_COUNT	(180)								//スピンする時間
#define PLAYER_SPIN_SPEED	(0.08f)								//スピンする速さ

//--------------------------------
//その他
//--------------------------------
#define COLOR_OUTLINE		(D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f))	//モデルの輪郭の色

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int CPlayer::m_nPlayerNum = 0;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CPlayer::CPlayer() : CObjectModel(CModel::MODELTYPE::OBJ_CAR, false)
{
	//総数を加算
	m_nPlayerNum++;

	SetObjType(OBJTYPE_PLAYER);	//オブジェクトタイプの設定
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);	//更新順の設定
	SetDrawPriority(DRAW_PRIORITY::CHARA);	//描画順の設定

	m_lastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_destRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nIndex = m_nPlayerNum;
	m_nCntGameover = 0;
	m_fMoveSpeed = 0.0f;
	m_fBoundMoveSpeed = 0.0f;
	m_state = PLAYER_STATE::NONE;
	m_itemType = CItem::ITEM_TYPE::NONE;
	m_nSpinCounter = 0;
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
	m_fBoundMoveSpeed = 0.0f;
	m_state = PLAYER_STATE::NOMAL;
	m_itemType = CItem::ITEM_TYPE::NONE;
	m_nSpinCounter = 0;

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();

	CObjectModel::Init();

	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//プレイヤー番号によって色を変える
	switch (m_nIndex)
	{
	case 1:
		col = PLAYER_COLOR_1P;
		break;
	case 2:
		col = PLAYER_COLOR_2P;
		break;
	case 3:
		col = PLAYER_COLOR_3P;
		break;
	case 4:
		col = PLAYER_COLOR_4P;
		break;
	default:
		break;
	}

	//モデル取得
	CModel *pModel = GetPtrModel();
	if (pModel!= nullptr)
	{
		//指定したマテリアルの色を設定
		pModel->SetMaterialDiffuse(col,0);
	}

	return S_OK;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CPlayer::Uninit(void) {
	m_nPlayerNum--;

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
	CInputGamepadX *pPadX = static_cast<CInputGamepadX*>(pInput);


	//位置情報のポインタの取得
	D3DXVECTOR3 posPlayer = GetPos();


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
	case CPlayer::PLAYER_STATE::NOMAL:
		//----------------------------
		//移動
		//----------------------------

		//移動と回転
		if (pInput != nullptr) {
			Move(pInput, fRotCameraY);
		}

		break;
	case CPlayer::PLAYER_STATE::BOUND:
		//バウンド状態処理
		StateBound();
		break;
	case CPlayer::PLAYER_STATE::SPIN:
		//スピン処理
		StateSpin();
		break;
	default:
		break;
	}	

	//----------------------------
	//移動の反映
	//----------------------------
	//最後の位置座標の保存
	m_lastPos = posPlayer;
	//移動
	posPlayer += m_move;
	//位置設定
	SetPos(posPlayer);



	//L1ボタンを押したら
	if (pPadX->GetTrigger(CInput::CODE::USE_ITEM, m_nIndex - 1))
	{
		//アイテム使用
		UseItem();
	}

	//----------------------------
	//当たり判定
	//----------------------------
	Collision(posPlayer);

	//----------------------------
	//モデルの更新
	//----------------------------
	CObjectModel::Update();
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CPlayer::Draw(void) {
	
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

	CInputGamepadX *pPadX = static_cast<CInputGamepadX*>(pInput);

	//上下左右キー入力状態の取得
	const bool bPressUp = pPadX->GetPress(CInput::CODE::MOVE_UP, m_nIndex - 1);
	const bool bPressDown = pPadX->GetPress(CInput::CODE::MOVE_DOWN, m_nIndex - 1);
	const bool bPressLeft = pPadX->GetPress(CInput::CODE::MOVE_LEFT, m_nIndex - 1);
	const bool bPressRight = pPadX->GetPress(CInput::CODE::MOVE_RIGHT, m_nIndex - 1);

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
	if (pPadX->GetPress(CInput::CODE::ACCELE, m_nIndex - 1))
	{
		//加速させる
		m_fMoveSpeed += ADD_MOVE_SPEED;
		//最大値よりも大きくなったら
		if (m_fMoveSpeed > MAX_MOVE_SPEED)
		{
			m_fMoveSpeed = MAX_MOVE_SPEED;
		}
	}
	else if (pPadX->GetPress(CInput::CODE::REVERSE, m_nIndex - 1))
	{//Bボタンを押したら
		//加速させる
		m_fMoveSpeed -= ADD_MOVE_SPEED;
		//最大値よりも大きくなったら
		if (m_fMoveSpeed < -MAX_MOVE_SPEED)
		{
			m_fMoveSpeed = -MAX_MOVE_SPEED;
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
void CPlayer::DecBoundMove(void) {
	//減速
	m_fBoundMoveSpeed *= DEC_MOVE_SPEED;

	//既定の値の誤差になったら
	if (m_fBoundMoveSpeed < MOVE_ZERO_RANGE && m_fBoundMoveSpeed > -MOVE_ZERO_RANGE)
	{
		//移動量を0にする
		m_fBoundMoveSpeed = 0.0f;
		m_fMoveSpeed = 0.0f;

		//状態を通常にする
		m_state = PLAYER_STATE::NOMAL;
	}
}

//=============================================================================
// 当たり判定
//=============================================================================
void CPlayer::Collision(D3DXVECTOR3& pos) {

	//プレイヤーとの当たり判定
	CollisionPlayer();

	//壁との当たり判定
	if (CWallCylinder::Collision(&pos, m_lastPos, COLLISION_RADIUS))
	{
		//位置設定
		SetPos(pos);

		if (m_state == PLAYER_STATE::BOUND)
		{
			return;
		}

		//状態をBOUNDに設定
		m_state = PLAYER_STATE::BOUND;

		//バウンド時の初速を設定
		m_fBoundMoveSpeed = m_fMoveSpeed * PLAYER_BOUND_SPEED;
		//最小値の範囲より小さくなったら
		if (m_fBoundMoveSpeed < MOVE_ZERO_RANGE && m_fBoundMoveSpeed > -MOVE_ZERO_RANGE)
		{
			//移動量を0にする
			m_fBoundMoveSpeed = 0.0f;
			m_fMoveSpeed = 0.0f;

			//状態を通常にする
			m_state = PLAYER_STATE::NOMAL;
		}
	}
}

//=============================================================================
//プレイヤーとの当たり判定
//=============================================================================
void CPlayer::CollisionPlayer(void)
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
		CPlayer *pPlayer = static_cast<CPlayer*> (pObject);

		//プレイヤーの位置を取得
		D3DXVECTOR3 playerPos = pPlayer->GetPos();
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

			if (m_state == PLAYER_STATE::BOUND)
			{
				return;
			}

			//状態をBOUNDに設定
			m_state = PLAYER_STATE::BOUND;

			//バウンド時の初速を設定
			m_fBoundMoveSpeed = m_fMoveSpeed * PLAYER_BOUND_SPEED;
			//最小値の範囲より小さくなったら
			if (m_fBoundMoveSpeed < MOVE_ZERO_RANGE && m_fBoundMoveSpeed > -MOVE_ZERO_RANGE)
			{
				//移動量を0にする
				m_fBoundMoveSpeed = 0.0f;
				m_fMoveSpeed = 0.0f;

				//状態を通常にする
				m_state = PLAYER_STATE::NOMAL;
			}
		}
		pObject = pObjNext;	//リストの次のオブジェクトを代入
	}
}

//=============================================================================
//バウンド状態の処理
//=============================================================================
void CPlayer::StateBound(void)
{
	//向いている方向と逆の方向に跳ね返す
	m_move.x = sinf(GetRot().y) * m_fBoundMoveSpeed;
	m_move.z = cosf(GetRot().y) * m_fBoundMoveSpeed;

	//移動量の減少
	DecBoundMove();
}

//=============================================================================
//スピン状態の処理
//=============================================================================
void CPlayer::StateSpin(void)
{
	//カウンター加算
	m_nSpinCounter++;
	//既定の値より大きくなったら
	if (m_nSpinCounter > PLAYER_SPIN_COUNT)
	{
		m_nSpinCounter = 0;
		//状態を通常にする
		m_state = PLAYER_STATE::NOMAL;
	}
	else
	{
		//向き取得
		D3DXVECTOR3 rot = GetRot();

		//回転させる
		rot.y += PLAYER_SPIN_SPEED;

		//向き設定
		SetRot(rot);
	}
}

//=============================================================================
//アイテム使用処理
//=============================================================================
void CPlayer::UseItem(void)
{
	//アイテムを持っている状態なら
	if (m_itemType == CItem::ITEM_TYPE::NONE || m_state == PLAYER_STATE::SPIN)
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
	default:
		break;
	}
}
