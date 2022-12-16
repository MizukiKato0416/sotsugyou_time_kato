//=============================================================================
//
// クレジットの絵処理 [credit_picture.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _CREDIT_PICTURE_H_
#define _CREDIT_PICTURE_H_

#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CObject2D;
class CTexture;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCreditPicture : public CObject
{
public:
	CCreditPicture();		//デフォルトコンストラクタ
	~CCreditPicture();		//デストラクタ
	static CCreditPicture* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale, const float fRot, const CTexture::TEXTURE_TYPE texType,
	                              const float fMoveY);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void) {}	//描画処理

private:

	bool Move(CObject2D *&pObject2D);	//移動処理

	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_scale;				//スケール
	float m_fRot;						//回転
	float m_fMoveY;						//移動量
	CTexture::TEXTURE_TYPE m_texType;	//テクスチャの種類
	CObject2D *m_pFrame;				//フレーム
	CObject2D *m_pPicture;				//絵
};

#endif // !_CREDIT_PICTURE_H_