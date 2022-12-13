//=============================================================================
//
// オブジェクトプレイヤー処理 [object_player.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _OBJECT_PLAYER_H_
#define _OBJECT_PLAYER_H_

#include "objectModel.h"
#include "item.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_OBJECT_PLAYER_NUM	(4)		//プレイヤーの最大数

//--------------------------------
//プレイヤーカラー
//--------------------------------
#define OBJECT_PLAYER_COLOR_1P		(D3DXCOLOR(0.1f, 0.3f, 1.0f, 1.0f))	//1pのカラー
#define OBJECT_PLAYER_COLOR_2P		(D3DXCOLOR(1.0f, 0.2f, 0.0f, 1.0f))	//2pのカラー
#define OBJECT_PLAYER_COLOR_3P		(D3DXCOLOR(0.1f, 0.7f, 0.0f, 1.0f))	//3pのカラー
#define OBJECT_PLAYER_COLOR_4P		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//4pのカラー

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CPlayer;

//*****************************************************************************
// クラス
//*****************************************************************************
class CObjectPlayer : public CObjectModel
{
public:
	CObjectPlayer();	//デフォルトコンストラクタ
	virtual ~CObjectPlayer();	//デストラクタ

	static CObjectPlayer* Create(D3DXVECTOR3 pos);	//生成処理

	virtual HRESULT Init(void);		//初期化処理
	virtual void Uninit(void);		//終了処理
	virtual void Update(void);		//更新処理
	virtual void Draw(void);		//描画処理
	virtual void GameOver(void);	//ゲームオーバー時の処理
	float GetRadius(void);			//当たり判定の半径の取得

	//プレイヤー取得処理
	CPlayer *GetPlayer(void) { return m_pPlayer; }

	//アイテムタイプ取得処理
	CItem::ITEM_TYPE GetItemType(void) { return m_itemType; }
	//アイテムタイプ設定処理
	void SetItemType(CItem::ITEM_TYPE itemType) { m_itemType = itemType; }

protected:
	CItem::ITEM_TYPE m_itemType;	//アイテムの種類

private:

	CPlayer *m_pPlayer;				//プレイヤーのポインタ
};

#endif // !_OBJECT_PLAYER_H_