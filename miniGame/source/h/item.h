//=============================================================================
//
// アイテム処理 [item.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "objectModel.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CObjectPlayer;
class CObject2D;

//*****************************************************************************
// アイテムクラス
//*****************************************************************************
class CItem : public CObjectModel
{
public:
	//アイテムの種類
	enum class ITEM_TYPE
	{
		NONE = 0,
		BANANA,
		STEAL_POINT,
		BALLOON_GAME_MAX,

		SHIELD = 0,
		ATTACK_GAME_MAX
	};

	CItem();	//デフォルトコンストラクタ
	CItem(CModel::MODELTYPE typeModel);		//オーバーロードされたコンストラクタ
	virtual ~CItem();	//デストラクタ
	virtual HRESULT Init(void);				//初期化処理
	virtual void Uninit(void);				//終了処理
	virtual void Update(void);				//更新処理
	virtual void Draw(void);				//描画処理

	//プレイヤーにヒットしたときの処理
	virtual void HitPlayer(CObjectPlayer *pPlayer);

private:
	int m_nPlayerIndex;		//このアイテムを持っているプレイヤーのインデックス

protected:
	bool CollisionPlayer(const float fMySize, const float fHeight);	//プレイヤーとの当たり判定
	CObjectPlayer *m_pPlayer;					                    //発射したプレイヤーのポインタ
};

#endif // !_ITEM_H_