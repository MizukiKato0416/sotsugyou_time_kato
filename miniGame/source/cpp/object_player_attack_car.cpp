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
#include "gameScene02.h"
#include "gameScene.h"

#include "PresetDelaySet.h"
//=============================================================================
// マクロ定義
//=============================================================================

//--------------------------------
//移動
//--------------------------------
#define ATTACK_CAR_ADD_MOVE_SPEED			(0.1f)		//加速
#define ATTACK_CAR_DEC_MOVE_SPEED			(0.93f)		//減速
#define ATTACK_CAR_MAX_MOVE_SPEED			(7.0f)		//最大速度
#define ATTACK_CAR_MOVE_ZERO_RANGE			(0.08f)		//移動量を0にする範囲
#define ATTACK_CAR_ATTACK_MOVE_SPEED		(40.0f)		//アタック時の移動量

#define ATTACK_CAR_ROTATE_SPEED				(0.025f)	//回転速度

//--------------------------------
//当たり判定
//--------------------------------
#define COLLISION_RADIUS	(40.0f)		//当たり判定の半径	壁とかに使う

//--------------------------------
//バウンド
//--------------------------------
#define ATTACK_CAR_NORMAL_MY_BOUND			(1.8f)		//相手に当たったとき自身が跳ね返る量の倍率
#define ATTACK_CAR_NORMAL_MY_BOUND_WOLF		(0.6f)		//相手に当たったとき自身が跳ね返る量の倍率(人狼)
#define ATTACK_CAR_NORMAL_ENEMY_BOUND		(3.0f)		//相手に当たったとき相手が跳ね返る量の倍率
#define ATTACK_CAR_NORMAL_ENEMY_BOUND_WOLF	(1.5f)		//相手に当たったとき相手が跳ね返る量の倍率(人狼)
#define ATTACK_CAR_ATTACK_MY_BOUND			(1.0f)		//アタック状態の時に相手に当たったとき自身が跳ね返る量の倍率
#define ATTACK_CAR_ATTACK_MY_BOUND_WOLF		(0.5f)		//アタック状態の時に相手に当たったとき自身が跳ね返る量の倍率(人狼)
#define ATTACK_CAR_ATTACK_ENEMY_BOUND		(1.5f)		//アタック状態の時に相手に当たったとき相手が跳ね返る量の倍率
#define ATTACK_CAR_ATTACK_ENEMY_BOUND_WOLF	(0.7f)		//アタック状態の時に相手に当たったとき相手が跳ね返る量の倍率(人狼)
#define ATTACK_CAR_BOUND_DEC				(0.9f)		//バウンドの移動量減少量
#define ATTACK_CAR_BOUND_MIN_SPEED			(2.0f)		//バウンドするのに必要な最小移動量

//--------------------------------
//その他
//--------------------------------
#define ATTACK_CAR_GRAVITY				(0.5f)		//重力
#define ATTACK_CAR_DEFENCE_COUNT		(300)		//ディフェンス状態の時間

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObjectPlayerAttackCar::CObjectPlayerAttackCar()
{
	SetObjType(OBJTYPE_PLAYER);						//オブジェクトタイプの設定
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);		//更新順の設定
	SetDrawPriority(DRAW_PRIORITY::CHARA);			//描画順の設定

	m_lastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_boundMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fMoveSpeed = 0.0f;
	m_bAttack = false;
	memset(m_bCollOld, false, sizeof(m_bCollOld[MAX_OBJECT_PLAYER_NUM]));

	m_nDefenceCounter = 0;
	m_bDefence = false;
	m_nFallEffectCounter = 0;

	m_pChangeColor = nullptr;
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
	m_fMoveSpeed = 0.0f;
	m_boundMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bAttack = false;
	memset(m_bCollOld, FALSE, sizeof(m_bCollOld[MAX_OBJECT_PLAYER_NUM]));
	m_nDefenceCounter = 0;
	m_bDefence = false;
	m_nFallEffectCounter = 0;

	return S_OK;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CObjectPlayerAttackCar::Uninit(void) {
	//変更する色のクラスの破棄
	if (m_pChangeColor != nullptr) {
		m_pChangeColor->Uninit();
		delete m_pChangeColor;
		m_pChangeColor = nullptr;
	}

	CObjectPlayer::Uninit();
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CObjectPlayerAttackCar::Update(void) {

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();

	CInput* pInput = nullptr;
	CSound *pSound = nullptr;
	CCamera* pCamera = nullptr;
	CGameScene* pGame = nullptr;

	//----------------------------
	//ディフェンス時
	//----------------------------
	if (m_bDefence) {
		CModel* pModel = GetPtrModel();	//モデルの取得
		//色の変更
		if (m_pChangeColor != nullptr && pModel != nullptr) {
			m_pChangeColor->Update();
			D3DXCOLOR col = m_pChangeColor->GetColor();
			pModel->SetMaterialDiffuse(col, 0);
		}
	}

	//----------------------------
	//カメラの設定
	//----------------------------
	float fRotCameraY = 0.0f;	//カメラの角度
	if (pCamera != nullptr) {
		fRotCameraY = pCamera->GetRot().y;	//カメラの角度を取得
	}

	//更新しない設定なら
	if (!GetPlayer()->GetUpdate())
	{
		//減速
		DecBoundMove();

		//減速
		DecMove();

		//移動量設定
		m_move.x = sinf(GetRot().y + D3DX_PI) * m_fMoveSpeed;
		m_move.z = cosf(GetRot().y + D3DX_PI) * m_fMoveSpeed;

		//重力処理
		Gravity();

		//----------------------------
		//移動の反映
		//----------------------------
		//位置情報のポインタの取得
		D3DXVECTOR3 posObjectPlayer = GetPos();
		//最後の位置座標の保存
		m_lastPos = posObjectPlayer;
		//移動
		posObjectPlayer += m_move + m_boundMove;
		//位置設定
		SetPos(posObjectPlayer);

		if (GetPos().y > -1000.0f && GetPos().y < -200.0f)
		{
			m_nFallEffectCounter++;

			if (m_nFallEffectCounter == 5)
			{
				//m_nFallEffectCounter = 0;
				//落下エフェクト
				CPresetDelaySet::Create(3, GetPos(),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f, fRotCameraY,0.0f));
			}
		}

		CObjectPlayer::Update();

		return;
	}

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

	

	//落ちていなかったら
	if (GetPos().y >= 0.0f)
	{
		//移動と回転
		if (pInput != nullptr) {
			Move(pInput, fRotCameraY);
		}
	}

	//重力処理
	Gravity();

	//----------------------------
	//移動の反映
	//----------------------------
	//最後の位置座標の保存
	m_lastPos = posObjectPlayer;
	//移動
	posObjectPlayer += m_move + m_boundMove;
	//位置設定
	SetPos(posObjectPlayer);

	//ディフェンス状態処理
	Defence();

	//----------------------------
	//当たり判定
	//----------------------------
	Collision(posObjectPlayer);

	if (GetPos().y > -1000.0f && GetPos().y < -200.0f)
	{
		m_nFallEffectCounter++;

		if (m_nFallEffectCounter == 5)
		{
			//m_nFallEffectCounter = 0;
			//落下エフェクト
			CPresetDelaySet::Create(3, GetPos(),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, fRotCameraY, 0.0f));

		}
	}

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

	if (!m_bAttack)
	{
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
			CPresetEffect::SetEffect3D(0, GetPos(), {}, {});
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
	}
	else
	{
		//減速
		DecMove();
	}

	//減速
	DecBoundMove();

	//アタック処理
	Attack();

	//移動量設定
	m_move.x = sinf(GetRot().y + D3DX_PI) * m_fMoveSpeed;
	m_move.z = cosf(GetRot().y + D3DX_PI) * m_fMoveSpeed;

	//アタック状態なら
	if (m_bAttack)
	{
		return;
	}

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
		rotObjectPlayer.y += fdeltaRot * ATTACK_CAR_ROTATE_SPEED * (fabsf(m_fMoveSpeed) / 8.0f);

		//パイ超過時
		if (rotObjectPlayer.y > D3DX_PI) {
			rotObjectPlayer.y -= D3DX_PI * 2;
		}
		else if (rotObjectPlayer.y < -D3DX_PI) {
			rotObjectPlayer.y += D3DX_PI * 2;
		}

		//角度の設定
		CObjectModel::SetRot(rotObjectPlayer);
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

		//アタックしている状態なら
		if (m_bAttack && m_boundMove.x == 0.0f && m_boundMove.y == 0.0f && m_boundMove.z == 0.0f)
		{
			//アタックしていない状態にする
			m_bAttack = false;
		}
	}
}

//=============================================================================
//バウンド移動量の減少
//=============================================================================
void CObjectPlayerAttackCar::DecBoundMove(void)
{
	//減速
	m_boundMove *= ATTACK_CAR_BOUND_DEC;

	//既定の値の誤差になったら
	if (m_boundMove.x < ATTACK_CAR_MOVE_ZERO_RANGE && m_boundMove.x > -ATTACK_CAR_MOVE_ZERO_RANGE,
		m_boundMove.z < ATTACK_CAR_MOVE_ZERO_RANGE && m_boundMove.z > -ATTACK_CAR_MOVE_ZERO_RANGE)
	{
		//移動量を0にする
		m_boundMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
//アタック処理
//=============================================================================
void CObjectPlayerAttackCar::Attack(void)
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
	}

	//ボタンを押したら
	if (pInput->GetTrigger(CInput::CODE::CAR_ATTACK, GetPlayer()->GetIndex() - 1))
	{
		//アタックしている状態なら
		if (m_bAttack)
		{
			return;
		}

		//アタックしている状態にする
		m_bAttack = true;
		//移動量設定
		m_fMoveSpeed = ATTACK_CAR_ATTACK_MOVE_SPEED;
	}
}

//=============================================================================
//アタック処理
//=============================================================================
void CObjectPlayerAttackCar::Defence(void)
{
	//ディフェンス状態でないとき
	if (!m_bDefence)
	{
		return;
	}

	m_nDefenceCounter++;

	//一定時間たったら
	if (m_nDefenceCounter > ATTACK_CAR_DEFENCE_COUNT)
	{
		//ディフェンス状態をやめる
		m_nDefenceCounter = 0;
		m_bDefence = false;
		//変更する色のクラスの破棄
		if (m_pChangeColor != nullptr) {
			m_pChangeColor->Uninit();
			delete m_pChangeColor;
			m_pChangeColor = nullptr;
		}
		//デフォルトの色に戻す
		SetMaterialDefault();
	}

}

//=============================================================================
//重力処理
//=============================================================================
void CObjectPlayerAttackCar::Gravity(void)
{
	//重力加算
	m_move.y -= ATTACK_CAR_GRAVITY;

	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//高さを0にする
	pos.y = 0.0f;

	//ステージの中心からプレイヤーまでの距離を算出
	float fDiffer = D3DXVec3Length(&pos);

	//ステージ外に出たら
	if (fDiffer - GetRadius() > GAME_02_STAGE_SIZE)
	{
		//ランキング設定処理
		SetRanking();

		return;
	}

	//重力を0にする
	m_move.y = 0.0f;
}

//=============================================================================
// 当たり判定
//=============================================================================
void CObjectPlayerAttackCar::Collision(D3DXVECTOR3& pos) {

	//落ちているなら
	if (GetPos().y < 0.0f)
	{
		return;
	}

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

		//落ちていたら
		if (playerPos.y < 0.0f)
		{
			pObject = pObjNext;	//リストの次のオブジェクトを代入
			continue;
		}

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

			//移動量がマイナスなら
			if (m_fMoveSpeed < 0)
			{
				//逆向きにする
				fRot += D3DX_PI;
			}

			//移動量が少なかったら
			if (m_fMoveSpeed < ATTACK_CAR_BOUND_MIN_SPEED && m_fMoveSpeed > -ATTACK_CAR_BOUND_MIN_SPEED)
			{
				return;
			}

			//バウンドする量
			float fBoundPlayer = ATTACK_CAR_NORMAL_MY_BOUND;
			float fBoundEnemy = ATTACK_CAR_NORMAL_ENEMY_BOUND;

			//アタック状態なら
			if (m_bAttack)
			{
				fBoundPlayer = ATTACK_CAR_ATTACK_MY_BOUND;
				fBoundEnemy = ATTACK_CAR_ATTACK_ENEMY_BOUND;
			}


			//ディフェンスしている状態なら
			if (m_bDefence)
			{
				fBoundPlayer = ATTACK_CAR_NORMAL_MY_BOUND_WOLF;

				//アタック状態なら
				if (m_bAttack)
				{
					fBoundPlayer = ATTACK_CAR_ATTACK_MY_BOUND_WOLF;
				}
			}
			else
			{
				//アタック状態なら
				if (m_bAttack)
				{
					fBoundPlayer = ATTACK_CAR_ATTACK_MY_BOUND;
				}
			}

			//相手がディフェンスしている状態なら
			if (pObjectPlayer->m_bDefence)
			{
				fBoundEnemy = ATTACK_CAR_NORMAL_ENEMY_BOUND_WOLF;

				//アタック状態なら
				if (m_bAttack)
				{
					fBoundEnemy = ATTACK_CAR_ATTACK_ENEMY_BOUND_WOLF;
				}
			}
			else
			{
				//アタック状態なら
				if (m_bAttack)
				{
					fBoundEnemy = ATTACK_CAR_ATTACK_ENEMY_BOUND;
				}
			}

			//相手のバウンド移動量取得
			D3DXVECTOR3 move = pObjectPlayer->GetBoundMove();

			float fMoveSpeed = m_fMoveSpeed;
			//自分が人狼だったら且つアタック状態なら
			if (CGameScene::GetWereWolfMode() && CGameScene::GetWereWolfPlayerIndex() == GetPlayer()->GetIndex() && m_bAttack)
			{
				//相手を飛ばす量を常に最大にする
				fMoveSpeed = ATTACK_CAR_ATTACK_MOVE_SPEED /* * 1.1f*/;
			}

			//跳ね返させる
			move.x += sinf(fRot) * fMoveSpeed * fBoundEnemy;
			move.z += cosf(fRot) * fMoveSpeed * fBoundEnemy;
			//相手のバウンド移動量設定
			pObjectPlayer->SetBoundMove(move);

			//自身も跳ね返させる
			m_boundMove.x += sinf(fRot + D3DX_PI) * m_fMoveSpeed * fBoundPlayer;
			m_boundMove.z += cosf(fRot + D3DX_PI) * m_fMoveSpeed * fBoundPlayer;

			m_fMoveSpeed = 0.0f;

			//前のフレーム当たっていなかったら
			if (!m_bCollOld[pObjectPlayer->GetPlayer()->GetIndex() - 1])
			{
				//マネージャーの取得
				CManager* pManager = CManager::GetManager();
				//サウンドの取得
				CSound* pSound = nullptr;
				if (pManager != nullptr) pSound = pManager->GetSound();
				//サウンドを再生
				pSound->PlaySound(CSound::SOUND_LABEL::SE_CRASH);
			}

			//当たった状態にする
			m_bCollOld[pObjectPlayer->GetPlayer()->GetIndex() - 1] = true;

			//衝突エフェクト
			CPresetDelaySet::Create(1, playerPos, {}, {});

			//マネージャーの取得
			CManager* pManager = CManager::GetManager();
			CInput* pInput = nullptr;
			CInputGamepadX *pPadX = nullptr;
			if (pManager != nullptr) {
				//現在の入力デバイスの取得
				pInput = pManager->GetInputCur();
				pPadX = dynamic_cast<CInputGamepadX*>(pInput);
			}

			if (pPadX != nullptr)
			{
				//振動させる
				pPadX->SetVibration(65535, 65535, 15, GetPlayer()->GetIndex() - 1);
				pPadX->SetVibration(65535, 65535, 15, pObjectPlayer->GetPlayer()->GetIndex() - 1);
			}

			return;
		}
		else
		{
			//当たっていない状態にする
			m_bCollOld[pObjectPlayer->GetPlayer()->GetIndex() - 1] = false;
		}
		pObject = pObjNext;	//リストの次のオブジェクトを代入
	}
}

//=============================================================================
//ランキング設定処理
//=============================================================================
void CObjectPlayerAttackCar::SetRanking()
{
	//ランキングが設定されていたら
	if (CGameScene::GetRanking(GetPlayer()->GetIndex() - 1) != 0)
	{
		return;
	}

	//マネージャーの取得
	CManager *pManager = CManager::GetManager();
	if (pManager == nullptr) {
		return;
	}

	//ゲームシーンの取得
	CGameScene *pGameScene = pManager->GetGameScene();
	if (pGameScene == nullptr) {
		return;
	}

	//キャスト
	CGameScene02 *pGameScene02 = dynamic_cast<CGameScene02*>(pGameScene);
	if (pGameScene02 == nullptr) {
		return;
	}

	//ランキング設定
	CGameScene::SetRanking(pGameScene02->GetSavePlayerNum(), GetPlayer()->GetIndex() - 1);
	//生き残った人数を減らす
	pGameScene02->AddSavePlayerNum(-1);

	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//サウンドを再生
	pSound->PlaySound(CSound::SOUND_LABEL::SE_FALL);
}

//ディフェンス状態設定処理
void CObjectPlayerAttackCar::SetDefence(const bool bDefence) {
	m_bDefence = bDefence;

	//変化する色のクラスを生成
	if (m_pChangeColor == nullptr) {
		m_pChangeColor = CChangeColor::Create(D3DXCOLOR(1.0f, 0.5f, 0.3f, 1.0f), 2.5f);
	}

	CModel* pModel = GetPtrModel();
	if (pModel != nullptr) {
		pModel->SetMaterialSpecular(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), 0);	//スペキュラーを薄める
	}
}