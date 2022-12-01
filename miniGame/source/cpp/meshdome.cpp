//=============================================================================
//
// メッシュドーム [meshdome.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "meshdome.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMeshdome::CMeshdome() : m_nNumXZ(0), m_nNumY(0)
{

}

//=============================================================================
//オーバーロードされたコンストラクタ
//=============================================================================
CMeshdome::CMeshdome(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumXZ, int nNumY, float fRadius, bool bOut) : m_nNumXZ(nNumXZ), m_nNumY(nNumY)
{
	SetPos(pos);
	SetRot(rot);
	m_fRadius = fRadius;
	m_bOut = bOut;
	SetNumVtx((nNumXZ + 1) * (nNumY + 1));	//(XZ方向のポリゴン数 + 1) * (Y方向のポリゴン数 + 1)
	SetNumIdx((2 * (nNumXZ + 1)) * nNumY + (nNumY - 1) * 2);	//XZ方向で使う頂点数 * Y方向のポリゴン数 + 縮退ポリゴンの数
}


//=============================================================================
// デストラクタ
//=============================================================================
CMeshdome::~CMeshdome()
{

}

//=============================================================================
// メッシュドームの生成処理
//=============================================================================
CMeshdome* CMeshdome::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumXZ, int nNumY, float fRadius, bool bOut, CTexture::TEXTURE_TYPE typeTex) {
	CMeshdome* pMeshdome;
	pMeshdome = new CMeshdome(pos, rot, nNumXZ, nNumY, fRadius, bOut);
	if (pMeshdome == nullptr) return nullptr;

	pMeshdome->SetTexType(typeTex);
	pMeshdome->Init();

	return pMeshdome;
}

//=============================================================================
// メッシュドームの初期化処理
//=============================================================================
HRESULT CMeshdome::Init(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return S_OK;
	//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return S_OK;
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return S_OK;

	//頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9* ppVtxBuff = GetPtrVtxBuff();

	int nNumVtx = GetNumVtx();	//頂点数の取得

	//頂点バッファの生成
	if (*ppVtxBuff == nullptr) {
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumVtx,
			D3DUSAGE_WRITEONLY,
			0,
			D3DPOOL_MANAGED,
			ppVtxBuff,
			nullptr);
	}

	//頂点バッファの設定
	SetVtxBuff();

	//インデックスバッファのの取得
	LPDIRECT3DINDEXBUFFER9* ppIdxBuff = GetPtrIdxBuff();

	int nNumIdx = GetNumIdx();	//インデックス数の取得

	//インデックスバッファの生成
	if (*ppIdxBuff == nullptr) {
		pDevice->CreateIndexBuffer(sizeof(WORD) * nNumIdx,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			ppIdxBuff,
			nullptr);
	}
	//インデックスバッファの設定
	if (*ppIdxBuff != nullptr) {
		WORD *pIdx;	//インデックス情報へのポインタ
		//インデックスバッファをロックし、番号データへのポインタを取得
		(*ppIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);
		//番号データ設定
		for (int nCntIdx = 0; nCntIdx < (m_nNumXZ + 1) * 2 * m_nNumY + (m_nNumY - 1) * 2; nCntIdx++) {
			if (nCntIdx == (m_nNumXZ + 2) * 2 * (1 + nCntIdx / ((m_nNumXZ + 2) * 2)) - 2) {
				pIdx[nCntIdx] = pIdx[nCntIdx - 1];
			}
			else if (nCntIdx == (m_nNumXZ + 2) * 2 * (1 + nCntIdx / ((m_nNumXZ + 2) * 2)) - 1) {
				pIdx[nCntIdx] = (m_nNumXZ + 1) * (2 + nCntIdx / ((m_nNumXZ + 1) * 2 + 2));
			}
			else {
				pIdx[nCntIdx] = (m_nNumXZ + 1 + nCntIdx / 2) - (nCntIdx / ((m_nNumXZ + 2) * 2)) - ((m_nNumXZ + 1)*(nCntIdx % 2));//下　縮退　上 縮退に修正
			}
		}
		//インデックスバッファをアンロックする
		(*ppIdxBuff)->Unlock();
	}

	CObject3D::Init();

	return S_OK;
}

//=============================================================================
// メッシュドームの終了処理
//=============================================================================
void CMeshdome::Uninit(void) {
	CObject3D::Uninit();
}

//=============================================================================
// メッシュドームの更新処理
//=============================================================================
void CMeshdome::Update(void) {
	//頂点バッファの更新
	SetVtxBuffPos();

	CObject3D::Update();
}

//=============================================================================
// メッシュドームの描画処理
//=============================================================================
void CMeshdome::Draw(void) {
	//描画
	CObject3D::Draw();
}

//=============================================================================
// 頂点バッファの情報を更新
//=============================================================================
void CMeshdome::SetVtxBuff(void) {
	//頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9* ppVtxBuff = GetPtrVtxBuff();

	//頂点バッファがなければ終了
	if (*ppVtxBuff == nullptr) return;

	int nNumVtx = GetNumVtx();	//頂点数の取得

	VERTEX_3D *pVtx;	//頂点バッファのポインタ
	//頂点バッファをロック
	(*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
	//頂点の設定
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++) {
		float fRotXZ = ((nCntVtx % (m_nNumXZ + 1)) / (float)m_nNumXZ) * (D3DX_PI * 2);	//XZ平面から見た角度
		float fRotXY = ((nCntVtx / (m_nNumXZ + 1)) / (float)m_nNumY) * (D3DX_PI / 2.0f);//XY平面から見た角度

		//ドームの向きが外向きの場合
		if (m_bOut == true) {
			fRotXY *= -1.0f;
			fRotXZ *= -1.0f;
		}

		//頂点座標の設定
		pVtx[nCntVtx].pos = D3DXVECTOR3(sinf(fRotXZ) * (sinf(fRotXY) * m_fRadius),
			cosf(fRotXY) * m_fRadius,
			cosf(fRotXZ) * (sinf(fRotXY) * m_fRadius));

		//法線ベクトルの設定
		D3DXVECTOR3 vecNor = D3DXVECTOR3(pVtx[nCntVtx].pos.x, 0.0f, pVtx[nCntVtx].pos.z);	//法線方向のベクトル
		D3DXVec3Normalize(&vecNor, &vecNor);	//ベクトルの正規化
		pVtx[nCntVtx].nor = vecNor;	//正規化したベクトルを設定

		//ドームが内向きの場合
		if (!m_bOut) {
			//法線を逆に設定
			pVtx[nCntVtx].nor.x *= -1;
			pVtx[nCntVtx].nor.y *= -1;
			pVtx[nCntVtx].nor.z *= -1;
		}

		pVtx[nCntVtx].tex = D3DXVECTOR2((float)(nCntVtx % (m_nNumXZ + 1)) / m_nNumXZ, (float)(nCntVtx / (m_nNumXZ + 1)) / m_nNumY);	//メッシュ全体で画像１枚分
		//pVtx[nCntVtx].tex = D3DXVECTOR2((float)(nCntVtx % (m_nNumXZ + 1)), (float)(nCntVtx / (m_nNumXZ + 1)));	//メッシュごとに画像一枚分
	}
	//頂点バッファをアンロックする
	(*ppVtxBuff)->Unlock();
}

//=============================================================================
// 頂点バッファの位置情報を更新
//=============================================================================
void CMeshdome::SetVtxBuffPos(void) {
	//頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9* ppVtxBuff = GetPtrVtxBuff();

	//頂点バッファがなければ終了
	if (*ppVtxBuff == nullptr) return;

	int nNumVtx = GetNumVtx();	//頂点数の取得

	VERTEX_3D *pVtx;	//頂点バッファのポインタ
	//頂点バッファをロック
	(*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
	//頂点の設定
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++) {
		float fRotXZ = ((nCntVtx % (m_nNumXZ + 1)) / (float)m_nNumXZ) * (D3DX_PI * 2);	//XZ平面から見た角度
		float fRotXY = ((nCntVtx / (m_nNumXZ + 1)) / (float)m_nNumY) * (D3DX_PI / 2.0f);//XY平面から見た角度

		//ドームの向きが外向きの場合
		if (m_bOut == true) {
			fRotXY *= -1.0f;
			fRotXZ *= -1.0f;
		}

		//頂点座標の設定
		pVtx[nCntVtx].pos = D3DXVECTOR3(sinf(fRotXZ) * (sinf(fRotXY) * m_fRadius),
			cosf(fRotXY) * m_fRadius,
			cosf(fRotXZ) * (sinf(fRotXY) * m_fRadius));

		pVtx[nCntVtx].tex = D3DXVECTOR2((float)(nCntVtx % (m_nNumXZ + 1)) / m_nNumXZ, (float)(nCntVtx / (m_nNumXZ + 1)) / m_nNumY);	//メッシュ全体で画像１枚分
		//pVtx[nCntVtx].tex = D3DXVECTOR2((float)(nCntVtx % (m_nNumXZ + 1)), (float)(nCntVtx / (m_nNumXZ + 1)));	//メッシュごとに画像一枚分
	}
	//頂点バッファをアンロックする
	(*ppVtxBuff)->Unlock();
}