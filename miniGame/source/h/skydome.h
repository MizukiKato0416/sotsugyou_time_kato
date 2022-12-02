//=============================================================================
//
// ドームの空の処理 [skydome.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _SKY_DOME_H_
#define _SKY_DOME_H_

#include "main.h"
#include "meshdome.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// ドームの空クラス
//*****************************************************************************
class CSkyDome : public CMeshdome
{
public:
	CSkyDome();	//デフォルトコンストラクタ
	CSkyDome(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumXZ, int nNumY, float fRadius);	//オーバーロードされたコンストラクタ
	~CSkyDome();	//デストラクタ
	static CSkyDome* Create(D3DXVECTOR3 pos, int nNumXZ, int nNumY, float fRadius, float fRotSpeed);	//生成処理
	static void CreateSphere(D3DXVECTOR3 pos, int nNumXZ, int nNumY, float fRadius, float fRotSpeed);	//球状に生成処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

private:

};

#endif // !_SKY_DOME_H_