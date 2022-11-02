//---------------------------
// Author:佐藤秀亮
// 平面(plane.cpp)
//---------------------------
#include "manager.h"
#include "renderer.h"

#include "plane.h"
//マクロ定義
#define TEXTURE_FILENAME_3D "data/TEXT/load_EffectTexture.txt"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CPlane::m_pTexture[MAX_TEXTURE] = {};
int CPlane::m_nMaxTex = 0;

CPlane::CPlane() : CScene3D::CScene3D()
{

}

CPlane::~CPlane()
{

}

//初期化処理
HRESULT CPlane::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex)
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//if (pManager == nullptr) return;	//nullの場合終了
										//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	//if (pRenderer == nullptr) return;	//nullの場合終了
										//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//if (pDevice == nullptr) return;		//nullの場合終了

	m_pos = pos;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	m_TexNum = Tex;

	m_size = size;

	VERTEX_3D *pVtx; //頂点情報へのポインタ
					 //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, -size.z);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(Tex.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, Tex.y);
	pVtx[3].tex = D3DXVECTOR2(Tex.x, Tex.y);
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//終了処理
void CPlane::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene3D::Uninit();
}

//更新処理
void CPlane::Update()
{

}

//描画処理
void CPlane::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld; //計算用マトリックス
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;	//nullの場合終了
	//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;	//nullの場合終了
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;		//nullの場合終了

	//エフェクトはZテクスチャに書き込まない
	if (pRenderer->GetDrawZTex()) return;

	//透明な部分を描画しないようにする
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

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	//シェーダにマトリックスを設定
	pRenderer->SetEffectMatrixWorld(mtxWorld);
	SetMatrix(mtxWorld);

	//シェーダにテクスチャを設定
	if (m_nTexType >= 0 && m_nTexType < MAX_TEXTURE) {
		pRenderer->SetEffectTexture(m_pTexture[m_nTexType]);
	}
	else {
		pRenderer->SetEffectTexture(nullptr);
	}

	//頂点定義を設定
	pRenderer->SetVtxDecl3D();

	//モデルが設定したマテリアルの影響を受けないようにマテリアルの設定
	pRenderer->SetEffectMaterialDiffuse(m_Color);
	pRenderer->SetEffectMaterialEmissive(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	pRenderer->SetEffectMaterialSpecular(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	pRenderer->SetEffectMaterialPower(2.0f);
	//輪郭の発光色の設定
	pRenderer->SetEffectGlow(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 0.0f);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	DWORD dwPassFlag = PASS_3D | PASS_TEXTURE;

	//パスの開始
	pRenderer->BeginPassEffect(dwPassFlag);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //開始する始点のインデックス
		2); //描画するプリミティブ数

	pRenderer->EndPassEffect();//エフェクト終了

	//デフォルトに戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//通常合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//=============================================================================
// テクスチャ破棄
//=============================================================================
void CPlane::UninitTexture()
{
	//テクスチャ破棄
	for (int nCnt = 0; nCnt < m_nMaxTex; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// サイズセット
//=============================================================================
void CPlane::SetSize(D3DXVECTOR3 size)
{
	//m_size = size;
	VERTEX_3D *pVtx; //頂点情報へのポインタ
					 //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, -size.z);
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// テクスチャ生成
//=============================================================================
void CPlane::CreateTextureFile()
{
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;	//nullの場合終了
										//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;	//nullの場合終了
										//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;		//nullの場合終了

	//ファイル読み込み
	char aFile[256];
	FILE *pFile = fopen(TEXTURE_FILENAME_3D, "r");

	int nCntTex = 0;

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);

			if (strcmp(&aFile[0], "NUM_TEXTURE") == 0)	//NUM_TEXTUREの文字列
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nMaxTex);//使用するテクスチャ数を読み込む
			}

			if (strcmp(&aFile[0], "TEXTURE_FILENAME") == 0) //TEXTURE_FILENAMEの文字列
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				D3DXCreateTextureFromFile(pDevice, &aFile[0], &m_pTexture[nCntTex]);
				nCntTex++;
			}

			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPTの文字列を見つけたら
			{
				break;
			}

		}
	}
	fclose(pFile);
}

//=============================================================================
//サイズ変更
//=============================================================================
void CPlane::ChangeSize(D3DXVECTOR3 size)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ

				   //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y	, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y	, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y	, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y	, -size.z);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
//平面エフェクト
//=============================================================================
void CPlane::SetPosField(D3DXVECTOR3 pos, D3DXVECTOR3 Size, float Rotate, float Rotate2)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x / 2 + (cosf(Rotate2)) * Size.x, Size.y, pos.z / 2 + (sinf(Rotate))* Size.x);
	pVtx[1].pos = D3DXVECTOR3(pos.x / 2 + (sinf(Rotate))  * Size.x, Size.y, pos.z / 2 - (cosf(Rotate2))* Size.x);
	pVtx[2].pos = D3DXVECTOR3(pos.x / 2 - (sinf(Rotate))  * Size.x, Size.y, pos.z / 2 + (cosf(Rotate2))* Size.x);
	pVtx[3].pos = D3DXVECTOR3(pos.x / 2 - (cosf(Rotate2)) * Size.x, Size.y, pos.z / 2 - (sinf(Rotate))* Size.x);


	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

}

//=============================================================================
//サイズ変更
//=============================================================================
void CPlane::BillboardSize(float size)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-size, size, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size, size, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size, -size, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size, -size, 0.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
//テクスチャ移動
//=============================================================================
void CPlane::TexturMove(D3DXVECTOR2 MoveTex)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ
	m_TexMove += MoveTex;

	if (m_TexMove.x >= 1.0f)
	{
		m_TexMove.x -= 1.0f;
	}
	else if (m_TexMove.x < 0.0f)
	{
		m_TexMove.x += 1.0f;
	}

	if (m_TexMove.y >= 1.0f)
	{
		m_TexMove.y -= 1.0f;
	}
	else if (m_TexMove.y < 0.0f)
	{
		m_TexMove.y += 1.0f;
	}

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(m_TexMove.x				, m_TexMove.y);
	pVtx[1].tex = D3DXVECTOR2(m_TexNum.x + m_TexMove.x	, m_TexMove.y);
	pVtx[2].tex = D3DXVECTOR2(m_TexMove.x				, m_TexNum.y + m_TexMove.y);
	pVtx[3].tex = D3DXVECTOR2(m_TexNum.x + m_TexMove.x	, m_TexNum.y + m_TexMove.y);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
//テクスチャパターン
//=============================================================================
void CPlane::SetTexAnim(D3DXVECTOR2 TexPattern, D3DXVECTOR2 TexAnimSize)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ

	m_nSplit = TexPattern;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + m_TexMove.x					, m_TexNum.y + m_nSplit.y * TexAnimSize.y + m_TexMove.y);
	pVtx[1].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + TexAnimSize.x + m_TexMove.x	, m_TexNum.y + m_nSplit.y * TexAnimSize.y + m_TexMove.y);
	pVtx[2].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + m_TexMove.x					, m_TexNum.y + m_nSplit.y *  + TexAnimSize.y + TexAnimSize.y + m_TexMove.y);
	pVtx[3].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + TexAnimSize.x + m_TexMove.x	, m_TexNum.y + m_nSplit.y *  +TexAnimSize.y + TexAnimSize.y + m_TexMove.y);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

}

//=============================================================================
//座標
//=============================================================================
void CPlane::SetPosBill(D3DXVECTOR3 pos, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3, D3DXVECTOR3 pos4)
{
	VERTEX_3D*pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = pos;
	pVtx[1].pos = pos2;
	pVtx[2].pos = pos3;
	pVtx[3].pos = pos4;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}