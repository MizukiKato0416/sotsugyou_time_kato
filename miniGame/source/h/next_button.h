//=============================================================================
//
// 次に進むボタンUI処理 [next_button.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _NEXT_BUTTON_H_
#define _NEXT_BUTTON_H_

#include "object2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CNextButton : public CObject2D
{
public:
	CNextButton();	//デフォルトコンストラクタ
	~CNextButton();	//デストラクタ

	//生成処理(位置、サイズ、テクスチャ、見えなくなってから生成されるまでのフレーム、α値減算量)
	static CNextButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const CTexture::TEXTURE_TYPE texType,
		                       const int nCounter, const float fDecAlpha);
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

private:
	int m_nFrameCounter;		//フレームカウント用
	int m_nCounter;				//見えなくなってから生成されるまでのフレーム
	float m_fDecAlpha;			//α値減算量
};

#endif // !_NEXT_BUTTON_H_