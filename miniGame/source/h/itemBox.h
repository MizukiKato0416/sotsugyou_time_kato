//=============================================================================
//
// アイテムボックス処理 [itemBox.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _ITEMBOX_H_
#define _ITEMBOX_H_

#include "objectModel.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ITEM_BOX_MOVE_SPEED	(5.0f)		//アイテムの移動速度

//*****************************************************************************
//前方宣言
//*****************************************************************************

//*****************************************************************************
// アイテムボックスクラス
//*****************************************************************************
class CItemBox : public CObjectModel
{
public:
	CItemBox();	//デフォルトコンストラクタ
	CItemBox(CModel::MODELTYPE typeModel);		//オーバーロードされたコンストラクタ
	~CItemBox();	//デストラクタ
	static CItemBox* Create(D3DXVECTOR3 pos);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	//総数取得処理
	static int GetNum(void) { return m_nNum; }
	//移動量取得処理
	D3DXVECTOR3 GetMove(void) { return m_move; }
	//移動量設定処理
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

private:
	bool CollisionPlayer(void);	//プレイヤーとの当たり判定

	static int m_nNum;		//総数
	D3DXVECTOR3 m_move;		//移動量
};

#endif // !_ITEMBOX_H_