//=============================================================================
// ���ʃG�t�F�N�g���� [FieldEffect.cpp]
// Author : �����G��
//=============================================================================
#include "FieldEffect.h"
#include "manager.h"
#include "renderer.h"
#include "control.h"

#include "straight3d.h"
#include "PresetSetEffect.h"

//=============================================================================
// �}�N
//=============================================================================
#define MAX_COLOR_FI (1.0f)


CFieldEffect::CFieldEffect() : CPlane::CPlane()
{

}

CFieldEffect::~CFieldEffect()
{

}

//����������
HRESULT CFieldEffect::Init(D3DXVECTOR3 size,
	D3DXVECTOR3 pos,
	D3DCOLORVALUE FieldColor,
	D3DCOLORVALUE FieldAddColor,
	float Rotate,
	int nTime,
	float MaxSize,
	float AddSize,
	int nSynsetic,
	int nDensity,
	float fDistance,
	D3DCOLORVALUE ParticleColor,
	D3DCOLORVALUE ParticleAddColor,
	int nParticleTex,
	int nParticleLife,
	int nParticleSynthetic,
	float ParticleMove3d,
	float ParticleAddSize,
	float ParticleSize,
	int ParticleTime,
	float ActiveAddSize,
	int FieldTime,
	bool FieldCreate,
	int CreatePreset,
	int AnimPatternType,
	int FiledLife)
{
	CPlane::Init(size, pos, D3DXVECTOR2(1.0f, 1.0f));

	nLife = FiledLife;

	EffectTime = START;

	m_size = sqrtf(size.x * size.x + size.z * size.z);
	SizeY = pos.y;
	fRotate = 0;
	fAddRotate = Rotate;
	//SetPosField(pos, D3DXVECTOR3(m_size, SizeY, {}), fRotate, fRotate);

	m_Color = FieldColor;
	m_FieldAddColor = FieldAddColor;

	m_MaxSize = MaxSize;
	m_AddSize = AddSize;
	m_nTime = nTime;
	m_nSynsetic = nSynsetic;

	m_nDensity = nDensity;
	m_fDistance = fDistance;
	m_ParticleColor = ParticleColor;
	m_ParticleAddColor = ParticleAddColor;
	m_nParticleTex = nParticleTex;
	m_nParticleLife = nParticleLife;
	m_nParticleSynthetic = nParticleSynthetic;
	m_ParticleMove3d = ParticleMove3d;
	m_ParticleAddSize = ParticleAddSize;
	m_ParticleSize = ParticleSize;

	Time = (int)(rand() % ParticleTime) + 1;
	nParticleTime = ParticleTime;
	m_ActiveAddSize = ActiveAddSize;

	m_FieldTime = FieldTime;
	m_FieldCreate = FieldCreate;
	m_CreatePreset = CreatePreset;
	m_FieldTimedelta = FieldTime - 5;
	m_AnimPatternType = AnimPatternType;

	if (m_bConversion == false)
	{
		//�J���[�l��255��1.0�\�L�ւ̕ϊ�
		if (m_Color.r > MAX_COLOR_FI)
		{
			m_Color.r = m_Color.r / 1000;
		}
		if (m_Color.g > MAX_COLOR_FI)
		{
			m_Color.g = m_Color.g / 1000;
		}
		if (m_Color.b > MAX_COLOR_FI)
		{
			m_Color.b = m_Color.b / 1000;
		}
		if (m_Color.a > MAX_COLOR_FI)
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
	m_FieldAddColor = FieldAddColor;

	//�J���[���Z�l��255��1.0�\�L�ւ̕ϊ�
	if (m_FieldAddColor.r >= MAX_COLOR_FI || m_FieldAddColor.r <= -MAX_COLOR_FI)	//��
	{
		if (m_FieldAddColor.r< 0)
		{
			ColorBoolR = true;
			m_FieldAddColor.r *= -1;
		}

		m_FieldAddColor.r = m_FieldAddColor.r / 1000;

		if (ColorBoolR = true)
		{
			m_FieldAddColor.r *= -1;
		}

	}
	if (m_FieldAddColor.g >= MAX_COLOR_FI || m_FieldAddColor.g <= -MAX_COLOR_FI)	//��
	{
		if (m_FieldAddColor.g < 0)
		{
			ColorBoolG = true;
			m_FieldAddColor.g *= -1;
		}

		m_FieldAddColor.g = m_FieldAddColor.g / 1000;

		if (ColorBoolG = true)
		{
			m_FieldAddColor.g *= -1;
		}

	}
	if (m_FieldAddColor.b >= MAX_COLOR_FI || m_FieldAddColor.b <= -MAX_COLOR_FI)	//��
	{
		if (m_FieldAddColor.b < 0)
		{
			ColorBoolB = true;
			m_FieldAddColor.b *= -1;
		}

		m_FieldAddColor.b = m_FieldAddColor.b / 1000;

		if (ColorBoolB = true)
		{
			m_FieldAddColor.b *= -1;
		}

	}
	if (m_FieldAddColor.a >= MAX_COLOR_FI || m_FieldAddColor.a <= -MAX_COLOR_FI)	//�����x
	{
		if (m_FieldAddColor.a < 0)
		{
			ColorBoolA = true;
			m_FieldAddColor.a *= -1;
		}

		m_FieldAddColor.a = m_FieldAddColor.a / 1000;

		if (ColorBoolA = true)
		{
			m_FieldAddColor.a *= -1;
		}
	}


	bUninit = false;
	return S_OK;
}

//�I������
void CFieldEffect::Uninit()
{
	CPlane::Uninit();
}

//�X�V����
void CFieldEffect::Update()
{

	float fAngle;
	float fAngle2;


	//1.0������
	if (m_Color.r >= MAX_COLOR_FI)
	{
		m_Color.r = MAX_COLOR_FI;
	}
	if (m_Color.g >= MAX_COLOR_FI)
	{
		m_Color.g = MAX_COLOR_FI;
	}
	if (m_Color.b >= MAX_COLOR_FI)
	{
		m_Color.b = MAX_COLOR_FI;
	}
	if (m_Color.a >= MAX_COLOR_FI)
	{
		m_Color.a = MAX_COLOR_FI;
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
	m_Color.r += m_FieldAddColor.r;
	m_Color.g += m_FieldAddColor.g;
	m_Color.b += m_FieldAddColor.b;
	m_Color.a += m_FieldAddColor.a;

	float moveMin = m_ParticleMove3d * -1 / 1.5f;
	int Life = m_nParticleLife ;
	float Size = m_ParticleAddSize / 1.5f;
	float AddR = fAddRotate * 30;
	//�t�B�[���h�̓���
	switch (EffectTime)
	{
	case(START)://�W�J��
		m_size += m_AddSize;
		fRotate += AddR;

		if (m_size > m_MaxSize)
		{
			EffectTime = ACTIVE;


			for (int i = 0; i < m_nDensity + 20; i++)
			{
				fAngle = CIRCLE;
				fAngle2 = CIRCLE;

				CStraight3D::Create(
					D3DXVECTOR3(
						m_fDistance  * sinf(fAngle) * cosf(fAngle2),
						m_fDistance / 2 * cosf(fAngle),
						m_fDistance  * sinf(fAngle) * sinf(fAngle2)
					),

					D3DXVECTOR3(m_ParticleSize, m_ParticleSize, 0.0f),
					D3DXVECTOR3(m_ParticleAddSize, m_ParticleAddSize, 0.0f),
					D3DXVECTOR3(moveMin, 0.0f, 0.0f),
					m_ParticleColor,
					m_ParticleAddColor,
					m_nParticleTex,
					m_nParticleLife,
					CStraight3D::TARGET,
					m_pos,
					m_nParticleSynthetic,0,
					(CStraight3D::RAND_PATTEN)0,
					(CStraight3D::POS_PATTERN)0,
					D3DXVECTOR2(0.0f, 0.0f),
					D3DXVECTOR2(1.0f, 1.0f),
					0,
					D3DXVECTOR2(1.0f,1.0f),
					(CBillEffect::ANIMPATTERN)m_AnimPatternType);
			}

		}
		break;
	case(ACTIVE):	//������
		fRotate += fAddRotate;

		Time--;
		m_size += m_ActiveAddSize;
		if (m_size < 0)
		{
			m_size = 0;
		}

		if (Time <= 0)
		{
			for (int i = 0; i < m_nDensity; i++)
			{
				fAngle = CIRCLE;
				fAngle2 = CIRCLE;

				CStraight3D::Create(
					m_pos,
					D3DXVECTOR3(m_ParticleSize, m_ParticleSize, 0.0f),
					D3DXVECTOR3(m_ParticleAddSize, m_ParticleAddSize, 0.0f),
					D3DXVECTOR3(m_ParticleMove3d, 0.0f, 0.0f),
					m_ParticleColor,
					m_ParticleAddColor,
					m_nParticleTex,
					m_nParticleLife,
					CStraight3D::TARGET,
					m_pos,
					m_nParticleSynthetic,
					m_fDistance,
					(CStraight3D::RAND_PATTEN)0,
					(CStraight3D::POS_PATTERN)2,
					D3DXVECTOR2(0.0f,0.0f),
					D3DXVECTOR2(1.0f, 1.0f),
					0,
					D3DXVECTOR2(1.0f, 1.0f),
					(CBillEffect::ANIMPATTERN)m_AnimPatternType);
				Time = (int)(rand() % nParticleTime) + 1;
			}
		}

		if (m_FieldCreate == true)
		{
			m_FieldTimedelta++;
			if (m_FieldTimedelta >= m_FieldTime)
			{
				CPresetEffect::SetEffect3D(m_CreatePreset, D3DXVECTOR3(0.0f, 0.0f, 0.0f), {}, {});
				m_FieldTimedelta = 0;
			}
		}

		m_nTime--;
		if (m_nTime < 0)
		{
			EffectTime = END;
		}
		break;
	case(END):	//�I��
		m_size -= m_AddSize;

		if (m_size < 10)
		{
			bUninit = true;

			for (int i = 0; i < m_nDensity + 10; i++)
			{
				fAngle = CIRCLE;
				fAngle2 = CIRCLE;

				CStraight3D::Create(
					m_pos,
					D3DXVECTOR3(m_ParticleSize, m_ParticleSize, 0.0f),
					D3DXVECTOR3(Size, Size, 0.0f),
					D3DXVECTOR3(moveMin / 2 , 0.0f, 0.0f),
					m_ParticleColor,
					m_ParticleAddColor,
					m_nParticleTex,
					Life,
					CStraight3D::TARGET,
					m_pos,
					m_nParticleSynthetic,
					m_fDistance,
					(CStraight3D::RAND_PATTEN)0,
					(CStraight3D::POS_PATTERN)2,
					D3DXVECTOR2(0.0f, 0.0f),
					D3DXVECTOR2(1.0f, 1.0f),
					0,
					D3DXVECTOR2(1.0f, 1.0f),
					(CBillEffect::ANIMPATTERN)m_AnimPatternType);
			}

		}
		break;
	default:

		break;
	}

	nLife--;
	if (nLife < 0)
	{
		bUninit = true;
	}

	//SetPosField(m_pos, D3DXVECTOR3(m_size, SizeY, {}), fRotate, -fRotate);
	SetPosBill(
		D3DXVECTOR3(m_pos.x - m_pos.x + (cosf(-fRotate)) * m_size, SizeY - SizeY, m_pos.z - m_pos.z + (sinf(fRotate))* m_size),
		D3DXVECTOR3(m_pos.x - m_pos.x + (sinf(fRotate))  * m_size, SizeY - SizeY, m_pos.z - m_pos.z - (cosf(-fRotate))* m_size),
		D3DXVECTOR3(m_pos.x - m_pos.x - (sinf(fRotate))  * m_size, SizeY - SizeY, m_pos.z - m_pos.z + (cosf(-fRotate))* m_size),
		D3DXVECTOR3(m_pos.x - m_pos.x - (cosf(-fRotate)) * m_size, SizeY - SizeY, m_pos.z - m_pos.z - (sinf(fRotate))* m_size));

	if (bUninit == true)
	{
		Uninit();
	}
}

//�`�揈��
void CFieldEffect::Draw()
{
	////�}�l�[�W���[�̎擾
	//CManager* pManager = CManager::GetManager();
	//if (pManager == nullptr) return;	//null�̏ꍇ�I��
	//									//�����_���[�̎擾
	//CRenderer* pRenderer = pManager->GetRenderer();
	//if (pRenderer == nullptr) return;	//null�̏ꍇ�I��
	//									//�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//if (pDevice == nullptr) return;		//null�̏ꍇ�I��

	////Z�e�X�g�֌W
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	////�A���t�@�e�X�g�֌W
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);


	//if (m_nSynsetic == 0)
	//{
	//	//���Z�����֌W
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//}
	//else if (m_nSynsetic == 1)
	//{
	//	//���Z�����̐ݒ�
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//}
	////����ȊO�̐��l�͉��Z������
	//else
	//{
	//	//���Z�����֌W
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//}
	////���C���e�B���O�𖳎�����
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	////�J�����O�I�t
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CPlane::Draw();
	//�J�����O�I��
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	////Z�e�X�g�֌W
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	////�A���t�@�e�X�g�֌W
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	////�ʏ퍇���ɖ߂�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	////���C���e�B���O��L���ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	////�ʒu�ɂ���Ă͉f��Ȃ��悤�ɂ���
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//�쐬
CFieldEffect *CFieldEffect::Create(D3DXVECTOR3 size,
	D3DXVECTOR3 pos,
	D3DCOLORVALUE FieldColor,
	D3DCOLORVALUE FieldAddColor,
	float Rotate,
	int nTime,
	float MaxSize,
	float AddSize,
	int nSynsetic,
	int nDensity,
	float fDistance,
	D3DCOLORVALUE ParticleColor,
	D3DCOLORVALUE ParticleAddColor,
	int nParticleTex,
	int nParticleLife,
	int nParticleSynthetic,
	float ParticleMove3d,
	float ParticleAddSize,
	float ParticleSize,
	int ParticleTime,
	float ActiveAddSize,
	int FieldTime,
	bool FieldCreate,
	int CreatePreset,
	int AnimPatternType,
	int FiledLife)
{
	CFieldEffect *pFieldEffect;
	pFieldEffect = new CFieldEffect();
	if (pFieldEffect != NULL)
	{
		pFieldEffect->Init(size,
			pos,
			FieldColor,
			FieldAddColor,
			Rotate,
			nTime,
			MaxSize,
			AddSize,
			nSynsetic,
			nDensity,
			fDistance,
			ParticleColor,
			ParticleAddColor,
			nParticleTex,
			nParticleLife,
			nParticleSynthetic,
			ParticleMove3d,
			ParticleAddSize,
			ParticleSize,
			ParticleTime,
			ActiveAddSize,
			FieldTime,
			FieldCreate,
			CreatePreset,
			AnimPatternType,
			FiledLife);

		pFieldEffect->SetTexture(nParticleTex);
	}

	return pFieldEffect;
}
