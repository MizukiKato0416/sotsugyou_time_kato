//=============================================================================
// �e��(����)���� [BulletHoll.cpp]
// Author : �����G��
//=============================================================================
#include "BulletHoll.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �}�N��
//=============================================================================
#define MAX_COLOR_BH (1.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletHoll::CBulletHoll() : CBillEffect()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletHoll::~CBulletHoll()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CBulletHoll::Init(D3DXVECTOR3 size,
	D3DXVECTOR3 Addsize,
	D3DXVECTOR3 pos,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nLife,
	int nTex,
	D3DXVECTOR2 TexMove,
	D3DXVECTOR2 TexNum,
	int nAnimCounter,
	D3DXVECTOR2 nSplit,
	D3DXVECTOR3 rot,
	int Synthetic,
	ANIMPATTERN AnimPattern,
	float Distance,
	HEIGHT_TYPE Type)
{
	CBillEffect::Init(size, Addsize, color, Mincolor, nTex, nLife, TexNum, TexMove, nAnimCounter, nSplit, AnimPattern);
	m_nSynthenic = Synthetic;
	m_Rot = rot;

	int fDistance = (int)Distance;
	float fRandDistance = float(rand() % fDistance) - float(rand() % fDistance);
	float fRandDistance2 = float(rand() % fDistance) - float(rand() % fDistance);
	m_MinSize = Addsize;
	m_Height_Type = Type;
	m_Size += m_MinSize;

	m_pos = D3DXVECTOR3(pos.x + cosf(CIRCLE) *  fRandDistance, m_Size.y / 2, pos.z + cosf(CIRCLE) * fRandDistance2);

	//�H�H�H�H
	//m_pos1 = D3DXVECTOR3(
	//	pos.x + size.x * (cosf(m_Rot.y)),
	//	pos.y /*+ size.x / 2*/,
	//	pos.z + size.x * (sinf(-m_Rot.y)));
	//m_pos2 = D3DXVECTOR3(
	//	pos.x + (sinf(-m_Rot.y))  * size.x,
	//	pos.y /*- size.x / 2*/,
	//	pos.z - (cosf(m_Rot.y))* size.x);
	//m_pos3 = D3DXVECTOR3(
	//	pos.x - (sinf(-m_Rot.y))  * size.x,
	//	pos.y /*- size.x / 2*/,
	//	pos.z + (cosf(m_Rot.y))* size.x);
	//m_pos4 = D3DXVECTOR3(
	//	pos.x - (cosf(m_Rot.y)) * size.x,
	//	pos.y /*- size.x / 2*/,
	//	pos.z - (sinf(-m_Rot.y))* size.x);

	if (m_Height_Type == TYPE_NOMAL)
	{
		m_pos1 = D3DXVECTOR3(
			m_pos.x - (cosf(-m_Rot.y) * m_Size.x / 2),
			m_pos.y + m_Size.y / 2,
			m_pos.z - (sinf(-m_Rot.y) * m_Size.x / 2));
		m_pos2 = D3DXVECTOR3(
			m_pos.x + (cosf(-m_Rot.y)) * m_Size.x / 2,
			m_pos.y + m_Size.y / 2,
			m_pos.z + (sinf(-m_Rot.y)) * m_Size.x / 2);
		m_pos3 = D3DXVECTOR3(
			m_pos.x - (cosf(-m_Rot.y) * m_Size.x / 2),
			m_pos.y - m_Size.y / 2,
			m_pos.z - (sinf(-m_Rot.y) * m_Size.x / 2));
		m_pos4 = D3DXVECTOR3(
			m_pos.x + (cosf(-m_Rot.y)) * m_Size.x / 2,
			m_pos.y - m_Size.y / 2,
			m_pos.z + (sinf(-m_Rot.y)) * m_Size.x / 2);

	}
	else if (m_Height_Type == TYPE_CYCLE)
	{
		m_pos1 = D3DXVECTOR3(
			m_pos.x - (cosf(-m_Rot.y) * m_Size.x / 2),
			m_pos.y + m_Size.y / 2,
			m_pos.z - (sinf(-m_Rot.y) * m_Size.x / 2));
		m_pos2 = D3DXVECTOR3(
			m_pos.x + (cosf(-m_Rot.y)) * m_Size.x / 2,
			m_pos.y + m_Size.y / 2,
			m_pos.z + (sinf(-m_Rot.y)) * m_Size.x / 2);
		m_pos3 = D3DXVECTOR3(
			m_pos.x - (cosf(-m_Rot.y) * m_Size.x / 2),
			m_pos.y - m_Size.y / 2,
			m_pos.z - (sinf(-m_Rot.y) * m_Size.x / 2));
		m_pos4 = D3DXVECTOR3(
			m_pos.x + (cosf(-m_Rot.y)) * m_Size.x / 2,
			m_pos.y - m_Size.y / 2,
			m_pos.z + (sinf(-m_Rot.y)) * m_Size.x / 2);

	}
	else  //�O�Ɠ�����O
	{
		m_pos1 = D3DXVECTOR3(
			m_pos.x - (cosf(-m_Rot.y) * m_Size.x / 2),
			m_pos.y + m_Size.y / 2,
			m_pos.z - (sinf(-m_Rot.y) * m_Size.x / 2));
		m_pos2 = D3DXVECTOR3(
			m_pos.x + (cosf(-m_Rot.y)) * m_Size.x / 2,
			m_pos.y + m_Size.y / 2,
			m_pos.z + (sinf(-m_Rot.y)) * m_Size.x / 2);
		m_pos3 = D3DXVECTOR3(
			m_pos.x - (cosf(-m_Rot.y) * m_Size.x / 2),
			m_pos.y - m_Size.y / 2,
			m_pos.z - (sinf(-m_Rot.y) * m_Size.x / 2));
		m_pos4 = D3DXVECTOR3(
			m_pos.x + (cosf(-m_Rot.y)) * m_Size.x / 2,
			m_pos.y - m_Size.y / 2,
			m_pos.z + (sinf(-m_Rot.y)) * m_Size.x / 2);
	}

	if (m_bConversion == false)
	{
		//�J���[�l��255��1.0�\�L�ւ̕ϊ�
		if (m_Color.r > MAX_COLOR_BH)
		{
			m_Color.r = m_Color.r / 1000;
		}
		if (m_Color.g > MAX_COLOR_BH)
		{
			m_Color.g = m_Color.g / 1000;
		}
		if (m_Color.b > MAX_COLOR_BH)
		{
			m_Color.b = m_Color.b / 1000;
		}
		if (m_Color.a > MAX_COLOR_BH)
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


	//�H�H�H
	//m_pos1 = D3DXVECTOR3(
	//	pos.x + size.x,
	//	pos.y /*+ size.x / 2*/,
	//	pos.z + size.x);
	//m_pos2 = D3DXVECTOR3(
	//	pos.x + size.x,
	//	pos.y /*- size.x / 2*/,
	//	pos.z - size.x);
	//m_pos3 = D3DXVECTOR3(
	//	pos.x - size.x,
	//	pos.y /*- size.x / 2*/,
	//	pos.z + size.x);
	//m_pos4 = D3DXVECTOR3(
	//	pos.x - size.x,
	//	pos.y /*- size.x / 2*/,
	//	pos.z - size.x);
	//CScene3d::SetRot(m_Rot);


	CPlane::SetPosBill(m_pos1 - m_pos, m_pos2 - m_pos, m_pos3 - m_pos, m_pos4 - m_pos);
	return S_OK;

}

//=============================================================================
// �I��
//=============================================================================
void CBulletHoll::Uninit()
{
	CBillEffect::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CBulletHoll::Update()
{
	m_Size += m_MinSize;

	if (m_Height_Type == TYPE_NOMAL)
	{
		m_pos1 = D3DXVECTOR3(
			m_pos.x - (cosf(-m_Rot.y) * m_Size.x / 2),
			m_pos.y + m_Size.y / 2,
			m_pos.z - (sinf(-m_Rot.y) * m_Size.x / 2));
		m_pos2 = D3DXVECTOR3(
			m_pos.x + (cosf(-m_Rot.y)) * m_Size.x / 2,
			m_pos.y + m_Size.y / 2,
			m_pos.z + (sinf(-m_Rot.y)) * m_Size.x / 2);
		m_pos3 = D3DXVECTOR3(
			m_pos.x - (cosf(-m_Rot.y) * m_Size.x / 2),
			m_pos.y - m_Size.y / 2,
			m_pos.z - (sinf(-m_Rot.y) * m_Size.x / 2));
		m_pos4 = D3DXVECTOR3(
			m_pos.x + (cosf(-m_Rot.y)) * m_Size.x / 2,
			m_pos.y - m_Size.y / 2,
			m_pos.z + (sinf(-m_Rot.y)) * m_Size.x / 2);

	}
	else if (m_Height_Type == TYPE_CYCLE)
	{
		m_pos1 = D3DXVECTOR3(
			m_pos.x - (cosf(-m_Rot.y) * m_Size.x / 2),
			m_pos.y + m_Size.y / 2,
			m_pos.z - (sinf(-m_Rot.y) * m_Size.x / 2));
		m_pos2 = D3DXVECTOR3(
			m_pos.x + (cosf(-m_Rot.y)) * m_Size.x / 2,
			m_pos.y + m_Size.y / 2,
			m_pos.z + (sinf(-m_Rot.y)) * m_Size.x / 2);
		m_pos3 = D3DXVECTOR3(
			m_pos.x - (cosf(-m_Rot.y) * m_Size.x / 2),
			m_pos.y - m_Size.y / 2,
			m_pos.z - (sinf(-m_Rot.y) * m_Size.x / 2));
		m_pos4 = D3DXVECTOR3(
			m_pos.x + (cosf(-m_Rot.y)) * m_Size.x / 2,
			m_pos.y - m_Size.y / 2,
			m_pos.z + (sinf(-m_Rot.y)) * m_Size.x / 2);

	}
	else  //�O�Ɠ�����O
	{
		m_pos1 = D3DXVECTOR3(
			m_pos.x - (cosf(-m_Rot.y) * m_Size.x / 2),
			m_pos.y + m_Size.y / 2,
			m_pos.z - (sinf(-m_Rot.y) * m_Size.x / 2));
		m_pos2 = D3DXVECTOR3(
			m_pos.x + (cosf(-m_Rot.y)) * m_Size.x / 2,
			m_pos.y + m_Size.y / 2,
			m_pos.z + (sinf(-m_Rot.y)) * m_Size.x / 2);
		m_pos3 = D3DXVECTOR3(
			m_pos.x - (cosf(-m_Rot.y) * m_Size.x / 2),
			m_pos.y - m_Size.y / 2,
			m_pos.z - (sinf(-m_Rot.y) * m_Size.x / 2));
		m_pos4 = D3DXVECTOR3(
			m_pos.x + (cosf(-m_Rot.y)) * m_Size.x / 2,
			m_pos.y - m_Size.y / 2,
			m_pos.z + (sinf(-m_Rot.y)) * m_Size.x / 2);
	}

	CPlane::SetPosBill(m_pos1 - m_pos, m_pos2 - m_pos, m_pos3 - m_pos, m_pos4 - m_pos);
	CBillEffect::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CBulletHoll::Draw()
{
	CPlane::Draw();
}

//=============================================================================
// �쐬
//=============================================================================
CBulletHoll *CBulletHoll::Create(D3DXVECTOR3 size,
	D3DXVECTOR3 Addsize,
	D3DXVECTOR3 pos,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nLife,
	int nTex,
	D3DXVECTOR2 TexMove,
	D3DXVECTOR2 TexNum,
	int nAnimCounter,
	D3DXVECTOR2 nSplit,
	D3DXVECTOR3 rot,
	int Synthetic,
	ANIMPATTERN AnimPattern,
	float Distance,
	HEIGHT_TYPE Type)
{
	CBulletHoll *pBulletHoll = new CBulletHoll();

	if (pBulletHoll != NULL)
	{
		pBulletHoll->Init(size, Addsize, pos, color, Mincolor, nLife, nTex, TexMove, TexNum, nAnimCounter, nSplit,
			rot, Synthetic, AnimPattern, Distance, Type);
	}

	return pBulletHoll;

}