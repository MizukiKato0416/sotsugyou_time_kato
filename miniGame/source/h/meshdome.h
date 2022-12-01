//=============================================================================
//
// メッシュドーム処理 [meshdome.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _MESHDOME_H_
#define _MESHDOME_H_

#include "main.h"
#include "object3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// メッシュドームクラス
//*****************************************************************************
class CMeshdome : public CObject3D
{
public:
	CMeshdome();	//デフォルトコンストラクタ
	CMeshdome(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumXZ, int nNumY, float fRadius, bool bOut);	//オーバーロードされたコンストラクタ
	virtual ~CMeshdome();	//デストラクタ
	static CMeshdome* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumXZ, int nNumY, float fRadius, bool bOut, CTexture::TEXTURE_TYPE typeTex);	//生成処理
	virtual HRESULT Init(void);	//初期化処理
	virtual void Uninit(void);	//終了処理
	virtual void Update(void);	//更新処理
	virtual void Draw(void);	//描画処理
	float GetRadius(void) { return m_fRadius; }	//半径の取得
	void AddRadius(float fRadius) { m_fRadius += fRadius; }		//半径を追加

private:
	void SetVtxBuff(void);	//頂点バッファの情報を更新
	void SetVtxBuffPos(void);	//頂点バッファの位置情報を更新

	const int m_nNumXZ;	//XZ方向のポリゴンの数
	const int m_nNumY;	//Y方向のポリゴンの数
	float m_fRadius;	//半球の半径
	bool m_bOut;		//ポリゴンが外向きかどうか
};

#endif // !_MESHDOME_H_