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

private:

	void Move(CInput* pInput, float fRotCameraY);	//移動
	void DecMove(void);								//移動量の減少
	void Collision(D3DXVECTOR3& pos);				//当たり判定
	void CollisionObjectPlayer(void);				//プレイヤーとの当たり判定

	D3DXVECTOR3	m_lastPos;	//最後の位置座標
	D3DXVECTOR3 m_destRot;	//目標の角度
	D3DXVECTOR3 m_move;		//移動量

	float m_fMoveSpeed;				//移動する速さ
};

#endif // !_OBJECT_PLAYER_ATTACK_CAR_H_