//=============================================================================
//
// 2Dゲージ処理 [gauge2D.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _GAUGE_2D_H_
#define _GAUGE_2D_H_

#include "gauge.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// 2Dゲージクラス
//*****************************************************************************
class CGauge2D : public CGauge
{
public:

	CGauge2D();		//デフォルトコンストラクタ
	CGauge2D(int nMaxValue, bool bVertical);	//オーバーロードされたコンストラクタ
	virtual ~CGauge2D();		//デストラクタ
	static CGauge2D* Create(int nMaxValue, bool bVertical, int nValue, int nDrawLifeMax, bool bExtend);	//生成処理
	virtual HRESULT Init(void);	//初期化処理
	virtual void Uninit(void);	//終了処理
	virtual void Update(void);	//更新処理
	virtual void CreateGauge(CTexture::TEXTURE_TYPE typeTex, D3DXVECTOR3 pos, float fWidth, float fHeight);			//ゲージを生成
	virtual void CreateGaugeBG(CTexture::TEXTURE_TYPE typeTex, D3DXVECTOR3 pos, float fWidth, float fHeight);		//ゲージの背景を生成
	virtual void CreateGaugeFrame(CTexture::TEXTURE_TYPE typeTex, D3DXVECTOR3 pos, float fWidth, float fHeight);	//ゲージの枠を生成

private:

};

#endif // !_GAUGE_2D_H_