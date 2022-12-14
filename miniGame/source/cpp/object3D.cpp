//=============================================================================
//
// 3Dオブジェクト処理 [object3D.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "object3D.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObject3D::CObject3D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_nNumVtx = 0;
	m_nNumIdx = 0;

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_mat.MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_mat.MatD3D.Power = 1.0f;
	m_colGlow = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_powGlow = 2.0f;

	m_bAlphaBlend = false;
	m_bEnableLight = true;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject3D::~CObject3D()
{

}

//=============================================================================
// 3Dオブジェクトの初期化処理
//=============================================================================
HRESULT CObject3D::Init(void) {

	//変数初期化
	m_bAlphaBlend = false;
	m_bEnableLight = true;

	return S_OK;
}

//=============================================================================
// 3Dオブジェクトの終了処理
//=============================================================================
void CObject3D::Uninit(void) {
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr) {
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	//インデックスバッファの破棄
	if (m_pIdxBuff != nullptr) {
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 3Dオブジェクトの更新処理
//=============================================================================
void CObject3D::Update(void) {
	m_pos += m_move;
	m_rot += m_rotate;
}

//=============================================================================
// 3Dオブジェクトの描画処理
//=============================================================================
void CObject3D::Draw(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;	//nullの場合終了
	//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;	//nullの場合終了
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;		//nullの場合終了

	//テクスチャの取得
	LPDIRECT3DTEXTURE9 pTexture = CTexture::GetTexture(GetTexType());

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//シェーダにマトリックスを設定
	pRenderer->SetEffectMatrixWorld(m_mtxWorld);

	//シェーダにテクスチャを設定
	pRenderer->SetEffectTexture(pTexture);

	//アルファテスト　有効／無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//アルファ値の参照値
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

	//加算合成を設定する状態なら
	if (m_bAlphaBlend)
	{
		//αブレンディングを加算合成に設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);
	//頂点定義を設定
	pRenderer->SetVtxDecl3D();	

	//ライトの状態取得
	DWORD dwEnableLight = 0;
	pDevice->GetRenderState(D3DRS_LIGHTING, &dwEnableLight);

	DWORD dwPassFlag = PASS_3D;

	//テクスチャがある場合フラグを追加
	if (pTexture != nullptr) dwPassFlag |= PASS_TEXTURE;	
	//ライトがある場合フラグを追加
	if (dwEnableLight && m_bEnableLight) dwPassFlag |= PASS_LIGHT;	

	//モデルが設定したマテリアルの影響を受けないようにマテリアルの設定
	pRenderer->SetEffectMaterialDiffuse(m_mat.MatD3D.Diffuse);
	pRenderer->SetEffectMaterialEmissive(m_mat.MatD3D.Emissive);
	pRenderer->SetEffectMaterialSpecular(m_mat.MatD3D.Specular);
	pRenderer->SetEffectMaterialPower(m_mat.MatD3D.Power);
	//輪郭の発光色の設定
	pRenderer->SetEffectGlow(m_colGlow, m_powGlow);

	//パスの開始
	pRenderer->BeginPassEffect(dwPassFlag);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_nNumVtx,	//使用する頂点数
		0,	//ここの値が最初のインデックス
		m_nNumIdx - 2);	//三角形の数

	pRenderer->EndPassEffect();//エフェクト終了
	
	//加算合成を設定する状態なら
	if (m_bAlphaBlend)
	{
		//aブレンディングを通常に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	//アルファテスト　有効／無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//アルファ値の参照値
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//=============================================================================
// 位置座標の設定
//=============================================================================
void CObject3D::SetPos(D3DXVECTOR3 pos) {
	m_pos = pos;
}

//=============================================================================
// 位置座標の取得
//=============================================================================
D3DXVECTOR3 CObject3D::GetPos(void) {
	return m_pos;
}

//=============================================================================
// 角度の設定
//=============================================================================
void CObject3D::SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

//=============================================================================
// 角度の取得
//=============================================================================
D3DXVECTOR3 CObject3D::GetRot(void) { return m_rot; }

//=============================================================================
// 頂点バッファのポインタのポインタを取得
//=============================================================================
LPDIRECT3DVERTEXBUFFER9* CObject3D::GetPtrVtxBuff(void) {
	return &m_pVtxBuff;
}

//=============================================================================
// インデックスバッファのポインタのポインタを取得
//=============================================================================
LPDIRECT3DINDEXBUFFER9* CObject3D::GetPtrIdxBuff(void) {
	return &m_pIdxBuff;
}

//=============================================================================
//頂点数の設定
//=============================================================================
void CObject3D::SetNumVtx(int nNumVtx) {
	m_nNumVtx = nNumVtx;
}

//=============================================================================
//頂点数の取得
//=============================================================================
int CObject3D::GetNumVtx(void) {
	return m_nNumVtx;
}

//=============================================================================
//インデックス数の設定
//=============================================================================
void CObject3D::SetNumIdx(int nNumIdx) {
	m_nNumIdx = nNumIdx;
}

//=============================================================================
//インデックス数の取得
//=============================================================================
int CObject3D::GetNumIdx(void) {
	return m_nNumIdx;
}

//=============================================================================
//テクスチャ移動設定処理
//=============================================================================
void CObject3D::SetMoveTex(float fMoveTexU, float fMoveTexV)
{
	VERTEX_3D *pVtx;	// 頂点情報
	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		pVtx[nCntVtx].tex += D3DXVECTOR2(fMoveTexU, fMoveTexV);

		if (pVtx[nCntVtx].tex.x < -100.0f)
		{
			pVtx[nCntVtx].tex.x += 200.0f;
		}
		else if (pVtx[nCntVtx].tex.x > 100.0f)
		{
			pVtx[nCntVtx].tex.x -= 200.0f;
		}

		if (pVtx[nCntVtx].tex.y < -100.0f)
		{
			pVtx[nCntVtx].tex.y += 200.0f;
		}
		else if (pVtx[nCntVtx].tex.y > 100.0f)
		{
			pVtx[nCntVtx].tex.y -= 200.0f;
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
