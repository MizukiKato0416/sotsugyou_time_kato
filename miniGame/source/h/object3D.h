//=============================================================================
//
// 3Dオブジェクト処理 [object3D.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 3Dオブジェクトクラス
//*****************************************************************************
class CObject3D : public CObject
{
public:
	CObject3D();	//デフォルトコンストラクタ
	virtual ~CObject3D();	//デストラクタ
	virtual HRESULT Init(void);	//初期化処理
	virtual void Uninit(void);	//終了処理
	virtual void Update(void);	//更新処理
	virtual void Draw(void);	//描画処理

	void SetPos(D3DXVECTOR3 pos);	//位置座標の設定
	D3DXVECTOR3 GetPos(void);		//位置座標の取得
	void SetRot(D3DXVECTOR3 rot);	//角度の設定
	D3DXVECTOR3 GetRot(void);		//角度の取得
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }		//ワールドマトリックスの取得
	LPDIRECT3DVERTEXBUFFER9* GetPtrVtxBuff(void);	//頂点バッファのポインタのポインタを取得
	LPDIRECT3DINDEXBUFFER9* GetPtrIdxBuff(void);	//インデックスバッファのポインタのポインタを取得
	void SetNumVtx(int nNumVtx);	//頂点数の設定
	int GetNumVtx(void);			//頂点数の取得
	void SetNumIdx(int nNumVtx);	//インデックス数の設定
	int GetNumIdx(void);			//インデックス数の取得

	void SetMaterialDiffuse(D3DXCOLOR col) { m_mat.MatD3D.Diffuse = col; }			//マテリアルの色の設定
	D3DXCOLOR GetMaterialDiffuse(void) { return m_mat.MatD3D.Diffuse; }				//マテリアルの色の取得
	void SetMaterialDiffuseAlpha(float fAlpha) { m_mat.MatD3D.Diffuse.a = fAlpha; }	//マテリアルのアルファ値を設定
	float GetMaterialDiffuseAlpha(void) { return m_mat.MatD3D.Diffuse.a; }			//マテリアルのアルファ値を取得
	void SetMaterialSpecular(D3DXCOLOR col) { m_mat.MatD3D.Specular = col; }		//マテリアルのスペキュラー色の設定
	void SetMaterialEmissive(D3DXCOLOR col) { m_mat.MatD3D.Emissive = col; }		//マテリアルの発光色の設定
	void SetMaterialPower(float fPower) { m_mat.MatD3D.Power = fPower; }			//マテリアルの反射の質感の設定
	void SetColorGlow(D3DXCOLOR col) { m_colGlow = col; }	//輪郭の発光色の設定
	void SetPowerGlow(float fPower) { m_powGlow = fPower; }	//輪郭の強度の設定

	void SetMoveTex(float fMoveTexU, float fMoveTexV);		//テクスチャ移動設定処理

	//加算合成設定処理
	void SetAlphaBlend(const bool bAlphaBlend) { m_bAlphaBlend = bAlphaBlend; }
	//加算合成取得処理
	bool GetAlphaBlend() { return m_bAlphaBlend; }

	//ライト設定処理
	void SetLight(const bool bEnableLight) { m_bEnableLight = bEnableLight; }
	//ライト取得処理
	bool GetLight() { return m_bEnableLight; }

private:
	D3DXVECTOR3	m_pos;	//ポリゴンの中心座標
	D3DXVECTOR3 m_rot;	//ポリゴンの角度
	D3DXMATRIX m_mtxWorld;//ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; //インデックスバッファへのポインタ
	int m_nNumVtx;	//頂点数
	int m_nNumIdx;	//インデックス数

	D3DXMATERIAL m_mat;		//ポリゴンのマテリアル
	D3DXCOLOR m_colGlow;	//輪郭の発光色の色
	float m_powGlow;	//輪郭の強度

	bool m_bAlphaBlend;		//加算合成するかどうか
	bool m_bEnableLight;	//ライト使うかどうか
};

#endif // !_OBJECT3D_H_