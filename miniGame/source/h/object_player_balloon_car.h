//=============================================================================
//
// 風船ゲーム用車処理 [object_player_balloon_car.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _OBJECT_PLAYER_BALLOON_CAR_H_
#define _OBJECT_PLAYER_BALLOON_CAR_H_

#include "object_player.h"
#include "item.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CObject2D;
class CWeapon;
class CInput;
class CScoreUi;

//*****************************************************************************
// クラス
//*****************************************************************************
class CObjectPlayerBalloonCar : public CObjectPlayer
{
public:
	enum class OBJECT_PLAYER_BALLOON_CAR_STATE
	{
		NONE = 0,	//なし
		NORMAL,		//通常
		INVINCIBLE,	//無敵
		SPIN,		//スピン
		MAX
	};

	CObjectPlayerBalloonCar();	//デフォルトコンストラクタ
	~CObjectPlayerBalloonCar();	//デストラクタ

	static CObjectPlayerBalloonCar* Create(D3DXVECTOR3 pos);	//生成処理

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void GameOver(void);	//ゲームオーバー時の処理
	D3DXVECTOR3 GetLastPos(void);	//最後の位置座標の取得
	void SetMove(D3DXVECTOR3 move);	//移動量の設定
	D3DXVECTOR3 GetMove(void);		//移動量の取得
	float GetRadius(void);			//当たり判定の半径の取得

	//状態設定処理
	void SetState(const OBJECT_PLAYER_BALLOON_CAR_STATE state) { m_state = state; }
	//状態取得処理
	OBJECT_PLAYER_BALLOON_CAR_STATE GetState(void) { return m_state; }

	//スコアUI取得処理
	CScoreUi *GetScoreUi(void) { return m_pSocreUi; }
	//スコア生成処理
	void CreateScore();

	//アイテムUIのフレーム生成処理
	void CreateItemUiFrame();

	//ポイント奪う状態かどうか設定処理
	void SetStealPoint(const bool bStealPoint) { m_bStealPoint = bStealPoint; }
	//ポイント奪う状態かどうか取得処理
	bool SetStealPoint(void) { return m_bStealPoint; }

private:
	void Move(CInput* pInput, float fRotCameraY);	//移動
	void DecMove(void);								//移動量の減少
	void DecBoundMove(void);						//バウンド時の移動量の減少
	void Collision(D3DXVECTOR3& pos);				//当たり判定
	void CollisionObjectPlayer(void);				//プレイヤーとの当たり判定
	void StateBound(void);							//バウンド状態の処理
	void StateSpin(void);							//スピン状態の処理
	void StateInvincble(void);						//無敵状態の処理
	void UseItem(void);								//アイテム使用処理
	void ItemUi(void);								//アイテムUi処理
	void StealPoint(void);							//ポイント奪取処理

	D3DXVECTOR3	m_lastPos;	//最後の位置座標
	D3DXVECTOR3 m_move;		//移動量

	float m_fMoveSpeed;							//移動する速さ
	float m_fBoundMoveSpeed;					//跳ね返るときの速さ
	float m_fSpinSpeed;							//スピンのスピード
	OBJECT_PLAYER_BALLOON_CAR_STATE m_state;	//状態
	bool m_bBound;								//バウンドするかどうか
	bool m_bStealPoint;							//ポイントを奪う状態かどうか
		
	int m_nSpinCounter;				//スピンする時間のカウンター
	int m_nInvincbleCounter;		//無敵時間のカウンター
	int m_nStealPointCounter;		//ポイントを奪う時間のカウンター

	CScoreUi *m_pSocreUi;			//スコアのポインタ
	CObject2D *m_pItemUi;			//アイテムのUI
};

#endif // !_OBJECT_PLAYER_BALLOON_CAR_H_