//=============================================================================
//
// ボム処理 [bom.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _BOM_H_
#define _BOM_H_

#include "objectModel.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CBom : public CObjectModel
{
public:
	CBom();	//デフォルトコンストラクタ
	CBom(CModel::MODELTYPE typeModel);		//オーバーロードされたコンストラクタ
	~CBom();	//デストラクタ
	static CBom* Create(D3DXVECTOR3 pos);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

private:
	bool CollisionPlayer(void);	//プレイヤーとの当たり判定
	void ExplosionSound();		//爆発音再生

	D3DXVECTOR3 m_move;		//移動量
};

#endif // !_BOM_H_