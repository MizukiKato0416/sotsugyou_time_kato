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
class CObjectPlayerBalloonCar;
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
		MAX
	};

	CItem();	//デフォルトコンストラクタ
	CItem(CModel::MODELTYPE typeModel);		//オーバーロードされたコンストラクタ
	virtual ~CItem();	//デストラクタ
	static CItem* Create(D3DXVECTOR3 pos, const CObjectPlayerBalloonCar *pPlayer);	//生成処理
	virtual HRESULT Init(void);				//初期化処理
	virtual void Uninit(void);				//終了処理
	virtual void Update(void);				//更新処理
	virtual void Draw(void);				//描画処理

	//プレイヤーにヒットしたときの処理
	virtual void HitPlayer(CObjectPlayerBalloonCar *pPlayer);

private:
	int m_nPlayerIndex;		//このアイテムを持っているプレイヤーのインデックス

protected:
	//第一引数プレイヤーのポインタが帰る
	bool CollisionPlayer(const float fMySize);	//プレイヤーとの当たり判定
	CObjectPlayerBalloonCar *m_pPlayer;							//発射したプレイヤーのポインタ
};

#endif // !_ITEM_H_