//=============================================================================
//
// 変化する色処理 [change_color.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _CHANGE_COLOR_H_
#define _CHANGE_COLOR_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 変化する色クラス
//*****************************************************************************
class CChangeColor
{
public:
	CChangeColor();	//デフォルトコンストラクタ
	virtual ~CChangeColor();	//デストラクタ

	static CChangeColor* Create(D3DXCOLOR colStart, float fSpeedColorwheel);	//生成処理

	virtual void Init(void);		//初期化処理
	virtual void Uninit(void);		//終了処理
	virtual void Update(void);		//更新処理

	D3DXCOLOR GetColor(void)				{ return m_col; }					//色の取得
	void SetSpeedColorwheel(float fSpeed)	{ m_fSpeedColorwheel = fSpeed; }	//カラーホイールが変化するスピードの設定

private:
	//RGBとHSLの変換 参考；https://www.petitmonte.com/javascript/rgb_hsl_convert.html
	D3DXVECTOR4 ConvertRGBtoHSL(D3DXCOLOR rgb);	//RGBからHSLへの変換
	D3DXCOLOR ConvertHSLtoRGB(D3DXVECTOR4 hsl);	//HSLからRGBへの変換

	D3DXCOLOR m_col;			//色
	float m_fSpeedColorwheel;	//カラーホイールが変化するスピード
};

#endif // !_CHANGE_COLOR_H_