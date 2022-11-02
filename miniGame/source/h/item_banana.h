//=============================================================================
//
// アイテムバナナ処理 [item_banana.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _ITEM_BANANA_H_
#define _ITEM_BANANA_H_

#include "item.h"
#include "objectModel.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CObjectPlayerBalloonCar;

//*****************************************************************************
// アイテムバナナクラス
//*****************************************************************************
class CItemBanana : public CItem
{
public:
	CItemBanana();	//デフォルトコンストラクタ
	CItemBanana(CModel::MODELTYPE typeModel);		//オーバーロードされたコンストラクタ
	virtual ~CItemBanana();	//デストラクタ
	static CItemBanana* Create(D3DXVECTOR3 pos, CObjectPlayerBalloonCar *pPlayer);	//生成処理
	virtual HRESULT Init(void);				//初期化処理
	virtual void Uninit(void);				//終了処理
	virtual void Update(void);				//更新処理
	virtual void Draw(void);				//描画処理

	//プレイヤーにヒットしたときの処理
	virtual void HitPlayer(CObjectPlayerBalloonCar *pPlayer);

private:
	D3DXVECTOR3 m_move;		//移動量

};

#endif // !_ITEM_BANANA_H_