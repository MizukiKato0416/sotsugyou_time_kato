//=============================================================================
//
// �ω�����F���� [change_color.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "change_color.h"
#include <directxmath.h>

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CChangeColor::CChangeColor()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CChangeColor::~CChangeColor()
{

}

//=============================================================================
// �ω�����F�̐�������
//=============================================================================
CChangeColor* CChangeColor::Create(D3DXCOLOR colStart, float fSpeedColorwheel) {
	CChangeColor* pChangeColor;
	pChangeColor = new CChangeColor();
	if (pChangeColor == nullptr) return nullptr;

	//������
	pChangeColor->Init();
	pChangeColor->m_col = colStart;
	pChangeColor->m_fSpeedColorwheel = fSpeedColorwheel;

	return pChangeColor;
}

//=============================================================================
// �ω�����F�̏���������
//=============================================================================
void CChangeColor::Init(void) {

}

//=============================================================================
// �ω�����F�̏I������
//=============================================================================
void CChangeColor::Uninit(void) {

}

//=============================================================================
// �ω�����F�̍X�V����
//=============================================================================
void CChangeColor::Update(void) {
	//HSL�ɕϊ�
	D3DXVECTOR4 hsl = ConvertRGBtoHSL(m_col);

	//�F�������Z
	hsl.x += m_fSpeedColorwheel;
	if (hsl.x >= 360.f) hsl.x = 0.f;

	//RGB�ɕϊ�
	m_col = ConvertHSLtoRGB(hsl);
}

//=============================================================================
// RGB����HSL�ւ̕ϊ�
//=============================================================================
D3DXVECTOR4 CChangeColor::ConvertRGBtoHSL(D3DXCOLOR rgb) {
	rgb *= 255;
	float fMax = max(max(rgb.r, rgb.g), rgb.b);
	float fMin = min(min(rgb.r, rgb.g), rgb.b);
	D3DXVECTOR4 hsl = { 0, 0, (fMax + fMin) / 2, rgb.a }; 

	if (fMax != fMin) {
		// H(�F��)  
		if (fMax == rgb.r) hsl.x = 60 * (rgb.g - rgb.b) / (fMax - fMin);
		if (fMax == rgb.g) hsl.x = 60 * (rgb.b - rgb.r) / (fMax - fMin) + 120;
		if (fMax == rgb.b) hsl.x = 60 * (rgb.r - rgb.g) / (fMax - fMin) + 240;

		// S(�ʓx)
		if (hsl.z <= 127) {
			hsl.y = (fMax - fMin) / (fMax + fMin);
		}
		else {
			hsl.y = (fMax - fMin) / (510 - fMax - fMin);
		}
		hsl.y *= 100;
	}

	//�}�C�i�X���̒���
	if (hsl.x < 0) {
		hsl.x = hsl.x + 360;
	}

	//L�̌v�Z
	hsl.z = (fMax + fMin) / 2 / 255 * 100;

	return hsl;
}

//=============================================================================
// HSL����RGB�ւ̕ϊ�
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

	//�l�̌ܓ�
	rgb.r /= 255;
	rgb.g /= 255;
	rgb.b /= 255;
	return rgb;
}