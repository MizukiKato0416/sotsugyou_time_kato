//=============================================================================
//
// 止まる車処理 [objplayer_stop.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _OBJPLAYER_STOP_H_
#define _OBJPLAYER_STOP_H_

#include "object_player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************

//*****************************************************************************
// 止まる車クラス
//*****************************************************************************
class CObjplayerStop : public CObjectPlayer
{
public:
	CObjplayerStop();	//デフォルトコンストラクタ
	CObjplayerStop(float fSpeedMax);	//オーバーロードされたコンストラクタ
	~CObjplayerStop();	//デストラクタ

	static CObjplayerStop* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeedMax);	//生成処理

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void GameOver(void);	//ゲームオーバー時の処理

	void SetCanStop(bool bCan) { m_bCanStop = bCan; }	//停止可能設定
	void StopMove(void);								//移動停止
	bool GetStopMove(void) { return m_bStopMove; }		//停止状態の取得

private:
	//メンバ関数
	void Move(void);		//移動

	//メンバ変数
	const float m_fSpeedMax;		//最大速度
	D3DXVECTOR3 m_move;		//移動量
	bool m_bCanStop;		//停止可能
	bool m_bStopMove;		//停止済みかどうか
};

#endif // !_OBJPLAYER_STOP_H_