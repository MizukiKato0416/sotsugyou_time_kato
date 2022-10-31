//=============================================================================
// ����G�t�F�N�g���� [SphereEffect.cpp]
// Author : �����G��
//=============================================================================
#include "SphereEffect.h"
#include "manager.h"

//=============================================================================
// �}�N
//=============================================================================
#define MAX_COLOR_S (1.0f)


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSphereEffect::CSphereEffect() : CSphere::CSphere()
{
	m_bConversion = false;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSphereEffect::~CSphereEffect(void)
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CSphereEffect::Init(
	D3DXVECTOR3 pos,
	float rot,
	float fSize,
	int nTex,
	D3DCOLORVALUE Color, D3DCOLORVALUE AddColor,
	int nLife, int nSynthetic,
	float fAddSize, int Vtx,
	SPHERE_TYPE SphereType,
	D3DXVECTOR2 TexMove,
	D3DXVECTOR2 TexNum,
	int nAnimCounter,
	D3DXVECTOR2 nSplit)
{
	if (SphereType == SPHERE)
	{
		CSphere::Init(pos, rot, fSize, Vtx * 2, Vtx, nTex, nSynthetic, TexNum);
	}
	else if (SphereType == HALF_SPHERE)
	{
		CSphere::Init(pos, rot, fSize, Vtx * 4, Vtx, nTex, nSynthetic, TexNum);
	}
	else
	{
		CSphere::Init(pos, rot, fSize, Vtx * 2, Vtx, nTex, nSynthetic, TexNum);
	}
	m_Color = Color;
	m_AddColor = AddColor;


	if (m_bConversion == false)
	{
		//�J���[�l��255��1.0�\�L�ւ̕ϊ�
		if (m_Color.r > MAX_COLOR_S)
		{
			m_Color.r = m_Color.r / 1000;
		}
		if (m_Color.g > MAX_COLOR_S)
		{
			m_Color.g = m_Color.g / 1000;
		}
		if (m_Color.b > MAX_COLOR_S)
		{
			m_Color.b = m_Color.b / 1000;
		}
		if (m_Color.a > MAX_COLOR_S)
		{
			m_Color.a = m_Color.a / 1000;
		}
		m_bConversion = true;
	}

	//255��1.0�\�L�ւ̕ϊ��Ɏg��
	bool ColorBoolR = false;
	bool ColorBoolG = false;
	bool ColorBoolB = false;
	bool ColorBoolA = false;

	//�J���[�ϓ�
	m_AddColor = AddColor;


	//�J���[���Z�l��255��1.0�\�L�ւ̕ϊ�
	if (m_AddColor.r >= MAX_COLOR_S || m_AddColor.r <= -MAX_COLOR_S)	//��
	{
		if (m_AddColor.r< 0)
		{
			ColorBoolR = true;
			m_AddColor.r *= -1;
		}

		m_AddColor.r = m_AddColor.r / 1000;

		if (ColorBoolR = true)
		{
			m_AddColor.r *= -1;
		}

	}
	if (m_AddColor.g >= MAX_COLOR_S || m_AddColor.g <= -MAX_COLOR_S)	//��
	{
		if (m_AddColor.g < 0)
		{
			ColorBoolG = true;
			m_AddColor.g *= -1;
		}

		m_AddColor.g = m_AddColor.g / 1000;

		if (ColorBoolG = true)
		{
			m_AddColor.g *= -1;
		}

	}
	if (m_AddColor.b >= MAX_COLOR_S || m_AddColor.b <= -MAX_COLOR_S)	//��
	{
		if (m_AddColor.b < 0)
		{
			ColorBoolB = true;
			m_AddColor.b *= -1;
		}

		m_AddColor.b = m_AddColor.b / 1000;

		if (ColorBoolB = true)
		{
			m_AddColor.b *= -1;
		}

	}
	if (m_AddColor.a >= MAX_COLOR_S || m_AddColor.a <= -MAX_COLOR_S)	//�����x
	{
		if (m_AddColor.a < 0)
		{
			ColorBoolA = true;
			m_AddColor.a *= -1;
		}

		m_AddColor.a = m_AddColor.a / 1000;

		if (ColorBoolA = true)
		{
			m_AddColor.a *= -1;
		}
	}



	m_TexMove = TexMove;

	m_fSize = fSize;
	m_fAddSize = fAddSize;
	m_nLife = nLife;

	m_MaxSplit = nSplit;
	m_PatternSize = D3DXVECTOR2(1.0f / m_MaxSplit.x, 1.0f / m_MaxSplit.y);
	m_nAnimCount = nAnimCounter;
	m_nSetAnimCnt = nAnimCounter;


	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CSphereEffect::Uninit()
{
	CSphere::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CSphereEffect::Update()
{
	m_fSize += m_fAddSize;
	if (m_fSize < 0)
	{
		m_bUninit = true;
	}

	//1.0������
	if (m_Color.r >= MAX_COLOR_S)
	{
		m_Color.r = MAX_COLOR_S;
	}
	if (m_Color.g >= MAX_COLOR_S)
	{
		m_Color.g = MAX_COLOR_S;
	}
	if (m_Color.b >= MAX_COLOR_S)
	{
		m_Color.b = MAX_COLOR_S;
	}
	if (m_Color.a >= MAX_COLOR_S)
	{
		m_Color.a = MAX_COLOR_S;
	}

	//�J���[�l��0������肻��
	if (m_Color.r <= 0)
	{
		m_Color.r = 0;
	}
	if (m_Color.g <= 0)
	{
		m_Color.g = 0;
	}
	if (m_Color.b <= 0)
	{
		m_Color.b = 0;
	}
	if (m_Color.a <= 0)
	{
		m_Color.a = 0;
	}


	//�J���[�ύX
	m_Color.r += m_AddColor.r;
	m_Color.g += m_AddColor.g;
	m_Color.b += m_AddColor.b;
	m_Color.a += m_AddColor.a;

	//�J���[��0�ȉ��̎�
	if (m_Color.r < 0)
	{
		m_Color.r = 0;
	}
	if (m_Color.g < 0)
	{
		m_Color.g = 0;
	}
	if (m_Color.b < 0)
	{
		m_Color.b = 0;
	}
	if (m_Color.a < 0)
	{
		m_Color.a = 0;
	}

	//�J���[��255�ȏ�̎�
	if (m_Color.r > MAX_COLOR_S)
	{
		m_Color.r = MAX_COLOR_S;
	}
	if (m_Color.g > MAX_COLOR_S)
	{
		m_Color.g = MAX_COLOR_S;
	}
	if (m_Color.b > MAX_COLOR_S)
	{
		m_Color.b = MAX_COLOR_S;
	}
	if (m_Color.a > MAX_COLOR_S)
	{
		m_Color.a = MAX_COLOR_S;
	}

	//�e�N�X�`���A�j���[�V����
	if (m_nAnimCount >= 0)
	{
		m_nAnimCount--;
		if (m_nAnimCount < 0)
		{
			m_nAnimCount = m_nSetAnimCnt;
			m_nSplit.x++;
			m_nSplit.y++;
		}
		if (m_nSplit > m_MaxSplit)
		{
			m_nSplit.x = 0;
			m_nSplit.y = 0;
		}
	}
	else if(m_nAnimCount <= -1)
	{

	}
	CSphere::SetSize(m_Pos,m_fSize);
	CSphere::SetTexUV(m_TexMove);
	CSphere::SetAnimTexUV(D3DXVECTOR2(m_nSplit.x * m_PatternSize.x, m_nSplit.y * m_PatternSize.y));

	CSphere::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CSphereEffect::Draw()
{
	CSphere::Draw();
}

//=============================================================================
// �쐬
//=============================================================================
CSphereEffect *CSphereEffect::Create(
	D3DXVECTOR3 pos,
	float rot,
	float fSize,
	int nTex,
	D3DCOLORVALUE Color, D3DCOLORVALUE AddColor,
	int nLife, int nSynthetic,
	float fAddSize, int Vtx,
	SPHERE_TYPE SphereType,
	D3DXVECTOR2 TexMove,
	D3DXVECTOR2 TexNum,
	int nAnimCounter,
	D3DXVECTOR2 nSplit)
{
	CSphereEffect *pSphereEffect = new CSphereEffect();

	if (pSphereEffect != NULL)
	{
		pSphereEffect->Init(pos, rot, fSize,
			nTex, Color, AddColor,
			nLife, nSynthetic,
			fAddSize, Vtx,
			SphereType,
			TexMove, TexNum,
			nAnimCounter,
			nSplit);
	}

	return pSphereEffect;

}

