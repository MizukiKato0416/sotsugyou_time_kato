//=============================================================================
//
// アイテム盾処理 [item_shield.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _ITEM_SHIELD_H_
#define _ITEM_SHIELD_H_

#include "item.h"
#include "objectModel.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CObjectPlayerAttackCar;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CItemShield : public CItem
{
public:
	CItemShield();	//デフォルトコンストラクタ
	CItemShield(CModel::MODELTYPE typeModel);		//オーバーロードされたコンストラクタ
	virtual ~CItemShield();	//デストラクタ
	static CItemShield* Create(D3DXVECTOR3 pos);	//生成処理
	virtual HRESULT Init(void);				//初期化処理
	virtual void Uninit(void);				//終了処理
	virtual void Update(void);				//更新処理
	virtual void Draw(void);				//描画処理

	//プレイヤーにヒットしたときの処理
	virtual void HitPlayer(CObjectPlayer *pPlayer);

private:
	void Move();		//移動処理
	void Rotate();		//回転処理

	D3DXVECTOR3 m_move;		//移動量
	int m_nCounter;			//カウンター

	CObjectModel *m_pSphereCover;		//球体
};

#endif // !_ITEM_SHIELD_H_