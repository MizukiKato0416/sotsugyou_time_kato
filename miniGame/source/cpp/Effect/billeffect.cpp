//=============================================================================
// 3Dエフェクト処理 [BillEffect.cpp]
// Author : 佐藤秀亮
//=============================================================================
#include "billEffect.h"
#include "manager.h"
#include "renderer.h"

#include "control.h"
//=============================================================================
// マク
//=============================================================================
#define MAX_COLOR (1.0f)


//=============================================================================
// コンストラクタ
//=============================================================================
CBillEffect::CBillEffect() : CPlane::CPlane()
{
	m_Color = {};
	m_MinColor = {};
	m_bConversion = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBillEffect::~CBillEffect()
{
	
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CBillEffect::Init(D3DXVECTOR3 Size,
	D3DXVECTOR3 MinSize,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nTex, int nLife,
	D3DXVECTOR2 TexNum,
	D3DXVECTOR2 TexMove,
	int nAnimCounter,
	D3DXVECTOR2 nSplit,
	ANIMPATTERN AnimPattern)
{
	CPlane::Init(Size, D3DXVECTOR3(0.0f, 0.0f, 0.0f), TexNum);
	SetTexture(nTex);


	m_Size = Size;			//大きさ
	m_MinSize = MinSize;	//大きさ変動

	m_TexSize = TexMove;

	//カラー
	m_Color = color;

	m_MaxSplit = nSplit;
	m_PatternSize = D3DXVECTOR2(1.0f / m_MaxSplit.x, 1.0f / m_MaxSplit.y);
	m_nAnimCount = nAnimCounter;
	m_nSetAnimCnt = nAnimCounter;
	m_AnimPattern = AnimPattern;

	if (m_MaxSplit.x <= 0)
	{
		m_MaxSplit.x = 1;
	}
	if (m_MaxSplit.y <= 0)
	{
		m_MaxSplit.y = 1;
	}

	float SplitU = float(rand() % (int)m_MaxSplit.x) + 1;
	float SplitV = float(rand() % (int)m_MaxSplit.y) + 1;


	if (m_AnimPattern == ANIMPATTERN_RAND)
	{
		m_nSplit.x = SplitU;
		m_nSplit.y = SplitV;
	}
	if (m_bConversion == false)
	{
		//カラー値の255→1.0表記への変換
		if (m_Color.r > MAX_COLOR)
		{
			m_Color.r = m_Color.r / 1000;
		}
		if (m_Color.g > MAX_COLOR)
		{
			m_Color.g = m_Color.g / 1000;
		}
		if (m_Color.b > MAX_COLOR)
		{
			m_Color.b = m_Color.b / 1000;
		}
		if (m_Color.a > MAX_COLOR)
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
	m_MinColor = Mincolor;


	//カラー減算値の255→1.0表記への変換
	if (m_MinColor.r >= MAX_COLOR || m_MinColor.r <= -MAX_COLOR)	//赤
	{
		if (m_MinColor.r< 0)
		{
			ColorBoolR = true;
			m_MinColor.r *= -1;
		}

		m_MinColor.r = m_MinColor.r / 1000;

		if (ColorBoolR = true)
		{
			m_MinColor.r *= -1;
		}

	}
	if (m_MinColor.g >= MAX_COLOR || m_MinColor.g <= -MAX_COLOR)	//緑
	{
		if (m_MinColor.g < 0)
		{
			ColorBoolG = true;
			m_MinColor.g *= -1;
		}

		m_MinColor.g = m_MinColor.g / 1000;

		if (ColorBoolG = true)
		{
			m_MinColor.g *= -1;
		}

	}
	if (m_MinColor.b >= MAX_COLOR || m_MinColor.b <= -MAX_COLOR)	//青
	{
		if (m_MinColor.b < 0)
		{
			ColorBoolB = true;
			m_MinColor.b *= -1;
		}

		m_MinColor.b = m_MinColor.b / 1000;

		if (ColorBoolB = true)
		{
			m_MinColor.b *= -1;
		}

	}
	if (m_MinColor.a >= MAX_COLOR || m_MinColor.a <= -MAX_COLOR)	//透明度
	{
		if (m_MinColor.a < 0)
		{
			ColorBoolA = true;
			m_MinColor.a *= -1;
		}

		m_MinColor.a = m_MinColor.a / 1000;

		if (ColorBoolA = true)
		{
			m_MinColor.a *= -1;
		}
	}


	m_nLife = nLife;
	m_bUninit = false;

	CPlane::TexturMove(m_TexSize);
	CPlane::SetTexAnim(m_nSplit, m_PatternSize);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CBillEffect::Uninit()
{
	CPlane::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CBillEffect::Update()
{


	//1.0を上回る
	if (m_Color.r >= MAX_COLOR)
	{
		m_Color.r = MAX_COLOR;
	}
	if (m_Color.g >= MAX_COLOR)
	{
		m_Color.g = MAX_COLOR;
	}
	if (m_Color.b >= MAX_COLOR)
	{
		m_Color.b = MAX_COLOR;
	}
	if (m_Color.a >= MAX_COLOR)
	{
		m_Color.a = MAX_COLOR;
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

	//カラー変更
	m_Color.r += m_MinColor.r;
	m_Color.g += m_MinColor.g;
	m_Color.b += m_MinColor.b;
	m_Color.a += m_MinColor.a;


	switch (m_AnimPattern)
	{
	case(ANIMPATTERN_NOMAL):
		//テクスチャアニメーション
		if (m_nAnimCount >= 0)
		{
			m_nAnimCount--;
			if (m_nAnimCount < 0)
			{
				m_nAnimCount = m_nSetAnimCnt;
				m_nSplit.x++;
				m_nSplit.y++;
			}
			if (m_MaxSplit > m_MaxSplit)
			{
				m_nSplit.x = 0;
				m_nSplit.y = 0;
			}
		}
		break;
	case(ANIMPATTERN_RAND):
		////テクスチャアニメーション
		//if (m_nAnimCount >= 0)
		//{
		//	m_nAnimCount--;
		//	if (m_nAnimCount < 0)
		//	{
		//		m_nAnimCount = m_nSetAnimCnt;
		//		m_nSplit.x++;
		//		m_nSplit.y++;
		//	}
		//	if (m_MaxSplit > m_MaxSplit)
		//	{
		//		m_nSplit.x = 0;
		//		m_nSplit.y = 0;
		//	}
		//}

		break;
	default:
		//テクスチャアニメーション
		if (m_nAnimCount >= 0)
		{
			m_nAnimCount--;
			if (m_nAnimCount < 0)
			{
				m_nAnimCount = m_nSetAnimCnt;
				m_nSplit.x++;
				m_nSplit.y++;
			}
			if (m_MaxSplit > m_MaxSplit)
			{
				m_nSplit.x = 0;
				m_nSplit.y = 0;
			}
		}
		break;
	}

	//それぞれ適応
	CPlane::TexturMove(m_TexSize);
	CPlane::SetTexAnim(m_nSplit, m_PatternSize);

	//寿命減少
	m_nLife--;
	if (m_nLife <= 0)
	{
		m_bUninit = true;
	}

	//抹消
	if (m_bUninit == true)
	{
		Uninit();
	}
}

//=============================================================================
// 描画
//=============================================================================
void CBillEffect::Draw()
{
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld; //計算用マトリックス
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;	//nullの場合終了
										//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;	//nullの場合終了
										//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;		//nullの場合終了


	//Zテスト関係
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//アルファテスト関係
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	if (m_nSynthenic == 0)
	{
		//加算合成関係
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (m_nSynthenic == 1)
	{
		//減算合成の設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (m_nSynthenic == 2)
	{
		//合成使用無し
	}
	//それ以外の数値は加算合成に
	else
	{
		//加算合成関係
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&mtxWorld, NULL, &mtxView); //逆行列を求める

	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	SetMatrix(mtxWorld);

	pRenderer->SetEffectMatrixWorld(mtxWorld);

	CPlane::Draw();

	//Zテスト関係
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテスト関係
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//通常合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// ポリゴンテクスチャセット
//=============================================================================
void CBillEffect::SetTexture(int nTex)
{
	m_nTexType = nTex;
}
