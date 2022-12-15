//=============================================================================
//
// 変化する色処理 [change_color.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "change_color.h"
#include <directxmath.h>

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CChangeColor::CChangeColor()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CChangeColor::~CChangeColor()
{

}

//=============================================================================
// 変化する色の生成処理
//=============================================================================
CChangeColor* CChangeColor::Create(D3DXCOLOR colStart, float fSpeedColorwheel) {
	CChangeColor* pChangeColor;
	pChangeColor = new CChangeColor();
	if (pChangeColor == nullptr) return nullptr;

	//初期化
	pChangeColor->Init();
	pChangeColor->m_col = colStart;
	pChangeColor->m_fSpeedColorwheel = fSpeedColorwheel;

	return pChangeColor;
}

//=============================================================================
// 変化する色の初期化処理
//=============================================================================
void CChangeColor::Init(void) {

}

//=============================================================================
// 変化する色の終了処理
//=============================================================================
void CChangeColor::Uninit(void) {

}

//=============================================================================
// 変化する色の更新処理
//=============================================================================
void CChangeColor::Update(void) {
	//HSLに変換
	D3DXVECTOR4 hsl = ConvertRGBtoHSL(m_col);

	//色相を加算
	hsl.x += m_fSpeedColorwheel;
	if (hsl.x >= 360.f) hsl.x = 0.f;

	//RGBに変換
	m_col = ConvertHSLtoRGB(hsl);
}

//=============================================================================
// RGBからHSLへの変換
//=============================================================================
D3DXVECTOR4 CChangeColor::ConvertRGBtoHSL(D3DXCOLOR rgb) {
	rgb *= 255;
	float fMax = max(max(rgb.r, rgb.g), rgb.b);
	float fMin = min(min(rgb.r, rgb.g), rgb.b);
	D3DXVECTOR4 hsl = { 0, 0, (fMax + fMin) / 2, rgb.a }; 

	if (fMax != fMin) {
		// H(色相)  
		if (fMax == rgb.r) hsl.x = 60 * (rgb.g - rgb.b) / (fMax - fMin);
		if (fMax == rgb.g) hsl.x = 60 * (rgb.b - rgb.r) / (fMax - fMin) + 120;
		if (fMax == rgb.b) hsl.x = 60 * (rgb.r - rgb.g) / (fMax - fMin) + 240;

		// S(彩度)
		if (hsl.z <= 127) {
			hsl.y = (fMax - fMin) / (fMax + fMin);
		}
		else {
			hsl.y = (fMax - fMin) / (510 - fMax - fMin);
		}
		hsl.y *= 100;
	}

	//マイナス時の調整
	if (hsl.x < 0) {
		hsl.x = hsl.x + 360;
	}

	//Lの計算
	hsl.z = (fMax + fMin) / 2 / 255 * 100;

	return hsl;
}

//=============================================================================
// HSLからRGBへの変換
//=============================================================================
D3DXCOLOR CChangeColor::ConvertHSLtoRGB(D3DXVECTOR4 hsl) {
	float fMax, fMin;
	D3DXCOLOR rgb = { 0, 0, 0, hsl.w / 255 };

	if (hsl.x >= 360) {
		hsl.x = 0;
	}

	if (hsl.z <= 49) {
		fMax = 2.55 * (hsl.z + hsl.z * (hsl.y / 100));
		fMin = 2.55 * (hsl.z - hsl.z * (hsl.y / 100));
	}
	else {
		fMax = 2.55 * (hsl.z + (100 - hsl.z) * (hsl.y / 100));
		fMin = 2.55 * (hsl.z - (100 - hsl.z) * (hsl.y / 100));
	}

	if (hsl.x < 60) {
		rgb.r = fMax;
		rgb.g = fMin + (fMax - fMin) * (hsl.x / 60);
		rgb.b = fMin;
	}
	else if (hsl.x >= 60 && hsl.x < 120) {
		rgb.r = fMin + (fMax - fMin) * ((120 - hsl.x) / 60);
		rgb.g = fMax;
		rgb.b = fMin;
	}
	else if (hsl.x >= 120 && hsl.x < 180) {
		rgb.r = fMin;
		rgb.g = fMax;
		rgb.b = fMin + (fMax - fMin) * ((hsl.x - 120) / 60);
	}
	else if (hsl.x >= 180 && hsl.x < 240) {
		rgb.r = fMin;
		rgb.g = fMin + (fMax - fMin) * ((240 - hsl.x) / 60);
		rgb.b = fMax;
	}
	else if (hsl.x >= 240 && hsl.x < 300) {
		rgb.r = fMin + (fMax - fMin) * ((hsl.x - 240) / 60);
		rgb.g = fMin;
		rgb.b = fMax;
	}
	else if (hsl.x >= 300 && hsl.x < 360) {
		rgb.r = fMax;
		rgb.g = fMin;
		rgb.b = fMin + (fMax - fMin) * ((360 - hsl.x) / 60);
	}

	//四捨五入
	rgb.r /= 255;
	rgb.g /= 255;
	rgb.b /= 255;
	return rgb;
}