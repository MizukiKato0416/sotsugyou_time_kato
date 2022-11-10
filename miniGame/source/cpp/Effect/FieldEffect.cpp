//=============================================================================
// 平面エフェクト処理 [FieldEffect.cpp]
// Author : 佐藤秀亮
//=============================================================================
#include "FieldEffect.h"
#include "manager.h"
#include "renderer.h"
#include "control.h"

#include "straight3d.h"
#include "PresetSetEffect.h"

//=============================================================================
// マク
//=============================================================================
#define MAX_COLOR_FI (1.0f)


CFieldEffect::CFieldEffect() : CPlane::CPlane()
{

}

CFieldEffect::~CFieldEffect()
{

}

//初期化処理
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
		//カラー値の255→1.0表記への変換
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

	//255→1.0表記への変換に使う
	bool ColorBoolR = false;
	bool ColorBoolG = false;
	bool ColorBoolB = false;
	bool ColorBoolA = false;

	//カラー変動
	m_FieldAddColor = FieldAddColor;

	//カラー減算値の255→1.0表記への変換
	if (m_FieldAddColor.r >= MAX_COLOR_FI || m_FieldAddColor.r <= -MAX_COLOR_FI)	//赤
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
	if (m_FieldAddColor.g >= MAX_COLOR_FI || m_FieldAddColor.g <= -MAX_COLOR_FI)	//緑
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
	if (m_FieldAddColor.b >= MAX_COLOR_FI || m_FieldAddColor.b <= -MAX_COLOR_FI)	//青
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
	if (m_FieldAddColor.a >= MAX_COLOR_FI || m_FieldAddColor.a <= -MAX_COLOR_FI)	//透明度
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

//終了処理
void CFieldEffect::Uninit()
{
	CPlane::Uninit();
}

//更新処理
void CFieldEffect::Update()
{

	float fAngle;
	float fAngle2;


	//1.0を上回る
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

	//カラー値が0を下回りそう
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

	//カラーの変動
	m_Color.r += m_FieldAddColor.r;
	m_Color.g += m_FieldAddColor.g;
	m_Color.b += m_FieldAddColor.b;
	m_Color.a += m_FieldAddColor.a;

	float moveMin = m_ParticleMove3d * -1 / 1.5f;
	int Life = m_nParticleLife ;
	float Size = m_ParticleAddSize / 1.5f;
	float AddR = fAddRotate * 30;
	//フィールドの動き
	switch (EffectTime)
	{
	case(START)://展開中
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
	case(ACTIVE):	//動き中
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
	case(END):	//終了
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

//描画処理
void CFieldEffect::Draw()
{
	////マネージャーの取得
	//CManager* pManager = CManager::GetManager();
	//if (pManager == nullptr) return;	//nullの場合終了
	//									//レンダラーの取得
	//CRenderer* pRenderer = pManager->GetRenderer();
	//if (pRenderer == nullptr) return;	//nullの場合終了
	//									//デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//if (pDevice == nullptr) return;		//nullの場合終了

	////Zテスト関係
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	////アルファテスト関係
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);


	//if (m_nSynsetic == 0)
	//{
	//	//加算合成関係
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//}
	//else if (m_nSynsetic == 1)
	//{
	//	//減算合成の設定
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//}
	////それ以外の数値は加算合成に
	//else
	//{
	//	//加算合成関係
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//}
	////ラインティングを無視する
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	////カリングオフ
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CPlane::Draw();
	//カリングオン
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	////Zテスト関係
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	////アルファテスト関係
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	////通常合成に戻す
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	////ラインティングを有効にする
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	////位置によっては映らないようにする
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//作成
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
