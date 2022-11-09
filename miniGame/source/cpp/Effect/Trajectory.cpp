 //=============================================================================
// �O�Տ��� [Trajectory.cpp]
// Author : �����G��
//=============================================================================
#include "Trajectory.h"
#include "manager.h"

//=============================================================================
// �}�N��
//=============================================================================
#define MAX_COLOR_TR (1.0f)


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTrajectory::CTrajectory() : CPlane()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTrajectory::~CTrajectory(void)
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CTrajectory::Init(D3DXVECTOR3 Vtxpos1,
	D3DXVECTOR3 Vtxpos2,
	D3DXVECTOR3 VtxOldpos1,
	D3DXVECTOR3 VtxOldpos2,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	D3DCOLORVALUE Trajectcolor,
	D3DCOLORVALUE TrajectMincolor,
	D3DXVECTOR3 Size,
	D3DXVECTOR3 MinSize,
	int nTex, int nLife,
	int Synthetic)
{
	CPlane::Init(Size, Vtxpos1, D3DXVECTOR2(1.0f, 1.0f));

	m_nSynthenic = Synthetic;

	m_pos1 = Vtxpos1;
	m_pos2 = Vtxpos2;
	m_pos3 = VtxOldpos1;
	m_pos4 = VtxOldpos2;

	m_nLife = nLife;
	m_Color = color;

	if (m_bConversion == false)
	{
		//�J���[�l��255��1.0�\�L�ւ̕ϊ�
		if (m_Color.r > MAX_COLOR_TR)
		{
			m_Color.r = m_Color.r / 1000;
		}
		if (m_Color.g > MAX_COLOR_TR)
		{
			m_Color.g = m_Color.g / 1000;
		}
		if (m_Color.b > MAX_COLOR_TR)
		{
			m_Color.b = m_Color.b / 1000;
		}
		if (m_Color.a > MAX_COLOR_TR)
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
	m_TrajectAddColor = Mincolor;

	//�J���[���Z�l��255��1.0�\�L�ւ̕ϊ�
	if (m_TrajectAddColor.r >= MAX_COLOR_TR || m_TrajectAddColor.r <= -MAX_COLOR_TR)	//��
	{
		if (m_TrajectAddColor.r< 0)
		{
			ColorBoolR = true;
			m_TrajectAddColor.r *= -1;
		}

		m_TrajectAddColor.r = m_TrajectAddColor.r / 1000;

		if (ColorBoolR = true)
		{
			m_TrajectAddColor.r *= -1;
		}

	}
	if (m_TrajectAddColor.g >= MAX_COLOR_TR || m_TrajectAddColor.g <= -MAX_COLOR_TR)	//��
	{
		if (m_TrajectAddColor.g < 0)
		{
			ColorBoolG = true;
			m_TrajectAddColor.g *= -1;
		}

		m_TrajectAddColor.g = m_TrajectAddColor.g / 1000;

		if (ColorBoolG = true)
		{
			m_TrajectAddColor.g *= -1;
		}

	}
	if (m_TrajectAddColor.b >= MAX_COLOR_TR || m_TrajectAddColor.b <= -MAX_COLOR_TR)	//��
	{
		if (m_TrajectAddColor.b < 0)
		{
			ColorBoolB = true;
			m_TrajectAddColor.b *= -1;
		}

		m_TrajectAddColor.b = m_TrajectAddColor.b / 1000;

		if (ColorBoolB = true)
		{
			m_TrajectAddColor.b *= -1;
		}

	}
	if (m_TrajectAddColor.a >= MAX_COLOR_TR || m_TrajectAddColor.a <= -MAX_COLOR_TR)	//�����x
	{
		if (m_TrajectAddColor.a < 0)
		{
			ColorBoolA = true;
			m_TrajectAddColor.a *= -1;
		}

		m_TrajectAddColor.a = m_TrajectAddColor.a / 1000;

		if (ColorBoolA = true)
		{
			m_TrajectAddColor.a *= -1;
		}
	}
	SetPosBill(m_pos1, m_pos2, m_pos3, m_pos4);

	bUninit = false;
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CTrajectory::Uninit(void)
{

	//1.0������
	if (m_Color.r >= MAX_COLOR_TR)
	{
		m_Color.r = MAX_COLOR_TR;
	}
	if (m_Color.g >= MAX_COLOR_TR)
	{
		m_Color.g = MAX_COLOR_TR;
	}
	if (m_Color.b >= MAX_COLOR_TR)
	{
		m_Color.b = MAX_COLOR_TR;
	}
	if (m_Color.a >= MAX_COLOR_TR)
	{
		m_Color.a = MAX_COLOR_TR;
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

	//�J���[�̕ϓ�
	m_Color.r += m_TrajectAddColor.r;
	m_Color.g += m_TrajectAddColor.g;
	m_Color.b += m_TrajectAddColor.b;
	m_Color.a += m_TrajectAddColor.a;

	m_nLife--;
	if (m_nLife < 0)
	{
		bUninit = true;
	}

	SetPosBill(m_pos1, m_pos2, m_pos3, m_pos4);


	CPlane::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CTrajectory::Update(void)
{
	CPlane::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CTrajectory::Draw(void)
{
	CPlane::Draw();
}

//=============================================================================
// �쐬
//=============================================================================
CTrajectory *CTrajectory::Create(D3DXVECTOR3 Vtxpos1, D3DXVECTOR3 Vtxpos2, D3DXVECTOR3 VtxOldpos1, D3DXVECTOR3 VtxOldpos2, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DCOLORVALUE Trajectcolor, D3DCOLORVALUE TrajectMincolor, D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, int nTex, int nLife,
	int Synthetic)
{
	CTrajectory *pTrajectory = NULL;
	pTrajectory = new CTrajectory();	//�������m��

	//NULL�`�F�b�N
	if (pTrajectory != NULL)
	{
		pTrajectory->Init(Vtxpos1, Vtxpos2, VtxOldpos1, VtxOldpos2, color, Mincolor, Trajectcolor, TrajectMincolor, Size, MinSize, nTex, nLife, Synthetic);
	}

	return pTrajectory;
}
