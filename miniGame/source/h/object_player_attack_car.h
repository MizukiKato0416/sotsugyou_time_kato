//=============================================================================
//
// 衝突ゲーム用車処理 [object_player_attack_car.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _OBJECT_PLAYER_ATTACK_CAR_H_
#define _OBJECT_PLAYER_ATTACK_CAR_H_

#include "object_player.h"
#include "item.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_OBJECT_PLAYER_ATTACK_CAR_NUM	(4)		//プレイヤーの最大数

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CInput;

//*****************************************************************************
// クラス
//*****************************************************************************
class CObjectPlayerAttackCar : public CObjectPlayer
{
public:
	CObjectPlayerAttackCar();	//デフォルトコンストラクタ
	~CObjectPlayerAttackCar();	//デストラクタ

	static CObjectPlayerAttackCar* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//生成処理

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void GameOver(void);	//ゲームオーバー時の処理
	D3DXVECTOR3 GetLastPos(void);	//最後の位置座標の取得
	void SetMove(D3DXVECTOR3 move);	//移動量の設定
	D3DXVECTOR3 GetMove(void);		//移動量の取得
	float GetRadius(void);			//当たり判定の半径の取得

	//バウンド移動量取得処理
	D3DXVECTOR3 GetBoundMove() { return m_boundMove; }
	//バウンド移動量設定処理
	void SetBoundMove(const D3DXVECTOR3 boundMove) { m_boundMove = boundMove; }

	//ディフェンス状態取得処理
	bool GetDefence() { return m_bDefence; }
	//ディフェンス状態設定処理
	void SetDefence(const bool bDefence) { m_bDefence = bDefence; }

	//ディフェンスカウンター取得処理
	int GetDefenceCounter() { return m_nDefenceCounter; }
	//ディフェンスカウンター設定処理
	void SetDefenceCounter(const int nDefenceCounter) { m_nDefenceCounter = nDefenceCounter; }
	//ランキング設定処理
	void SetRanking();								

private:

	void Move(CInput* pInput, float fRotCameraY);	//移動
	void DecMove(void);								//移動量の減少
	void DecBoundMove(void);						//バウンド移動量の減少
	void Attack(void);								//アタック処理
	void Defence(void);								//ディフェンス処理
	void Gravity(void);								//重力処理
	void Collision(D3DXVECTOR3& pos);				//当たり判定
	void CollisionObjectPlayer(void);				//プレイヤーとの当たり判定

	D3DXVECTOR3	m_lastPos;			//最後の位置座標
	D3DXVECTOR3 m_move;				//移動量
	D3DXVECTOR3 m_boundMove;		//バウンド移動量
	float m_fMoveSpeed;				//移動する速さ
	int m_nDefenceCounter;			//ディフェンス状態をカウントする用
	int m_nFallEffectCounter;		//落ちるエフェクトの生成カウンター

	bool m_bAttack;									//アタックしているかどうか
	bool m_bCollOld[MAX_OBJECT_PLAYER_NUM];			//前のフレーム当たったかどうか
	bool m_bDefence;								//ディフェンス状態かどうか
};

#endif // !_OBJECT_PLAYER_ATTACK_CAR_H_