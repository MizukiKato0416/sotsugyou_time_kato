//=============================================================================
//
// 浮遊物処理 [float_object.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _FLOAT_OBJECT_H_
#define _FLOAT_OBJECT_H_

#include "objectModel.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************

//*****************************************************************************
// 風船クラス
//*****************************************************************************
class CFloatObject : public CObjectModel
{
public:
	CFloatObject();	//デフォルトコンストラクタ
	CFloatObject(CModel::MODELTYPE typeModel);		//オーバーロードされたコンストラクタ
	~CFloatObject();	//デストラクタ
	static CFloatObject* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move, const D3DXVECTOR3 rotateSpeed,
		                        const CModel::MODELTYPE modelType);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

private:

	D3DXVECTOR3 m_move;			//移動量
	D3DXVECTOR3 m_rotateSpeed;	//回転速度
};

#endif // !_FLOAT_OBJECT_H_