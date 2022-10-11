//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "objectModel.h"
#include "item.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PLAYER_NUM	(4)		//プレイヤーの最大数

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CObject2D;
class CWeapon;
class CInput;

//*****************************************************************************
// プレイヤークラス
//*****************************************************************************
class CPlayer : public CObjectModel
{
public:
	enum class PLAYER_STATE
	{
		NONE = 0,	//なし
		NOMAL,		//通常
		BOUND,		//バウンド
		SPIN,		//スピン
		MAX
	};

	CPlayer();	//デフォルトコンストラクタ
	~CPlayer();	//デストラクタ

	static CPlayer* Create(D3DXVECTOR3 pos);	//生成処理

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void GameOver(void);	//ゲームオーバー時の処理
	void GetCollisionInfo(int nIdxColParts, int* const pNumCol, D3DXVECTOR3** const ppPosColArray, float* const pRadiusCol);	//当たり判定の情報の取得
	D3DXVECTOR3 GetLastPos(void);	//最後の位置座標の取得
	void SetMove(D3DXVECTOR3 move);	//移動量の設定
	D3DXVECTOR3 GetMove(void);		//移動量の取得
	float GetRadius(void);			//当たり判定の半径の取得
	//状態設定処理
	void SetState(const PLAYER_STATE state) { m_state = state; }
	//状態取得処理
	PLAYER_STATE GetState(void) { return m_state; }
	//プレイヤー番号設定処理
	void SetIndex(const int nIndex) { m_nIndex = nIndex; }
	//プレイヤー番号取得処理
	int GetIndex(void) { return m_nIndex; }
	//プレイヤーの総数取得処理
	static int GetNum(void) { return m_nPlayerNum; }
	//アイテムタイプ取得処理
	CItem::ITEM_TYPE GetItemType(void) { return m_itemType; }
	//アイテムタイプ設定処理
	void SetItemType(CItem::ITEM_TYPE itemType) { m_itemType = itemType; }

private:
	void Move(CInput* pInput, float fRotCameraY);	//移動
	void DecMove(void);								//移動量の減少
	void DecBoundMove(void);						//バウンド時の移動量の減少
	void Collision(D3DXVECTOR3& pos);				//当たり判定
	void CollisionPlayer(void);						//プレイヤーとの当たり判定
	void StateBound(void);							//バウンド状態の処理
	void StateSpin(void);							//スピン状態の処理
	void UseItem(void);								//アイテム使用処理

	D3DXVECTOR3	m_lastPos;	//最後の位置座標
	D3DXVECTOR3 m_destRot;	//目標の角度
	D3DXVECTOR3 m_move;		//移動量

	static int m_nPlayerNum;		//プレイヤーの数
	int m_nIndex;					//プレイヤー番号
	int m_nCntGameover;				//ゲームオーバー後のカウント
	float m_fMoveSpeed;				//移動する速さ
	float m_fBoundMoveSpeed;		//跳ね返るときの速さ
	PLAYER_STATE m_state;			//状態
	CItem::ITEM_TYPE m_itemType;	//アイテムの種類
	int m_nSpinCounter;				//スピンする時間のカウンター
};

#endif // !_PLAYER_H_