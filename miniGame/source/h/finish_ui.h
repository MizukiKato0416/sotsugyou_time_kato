//=============================================================================
//
// フィニッシュUI処理 [finish_ui.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _FINISH_UI_H_
#define _FINISH_UI_H_

#include "object2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************

//*****************************************************************************
// フィニッシュUIクラス
//*****************************************************************************
class CFinishUi : public CObject2D
{
public:
	enum class STATE
	{
		DEC_SIZE = 0,	//サイズ減算
		NONE,			//なし
		ADD_SIZE,		//サイズ加算
		MAX
	};


	CFinishUi();		//デフォルトコンストラクタ
	~CFinishUi();	//デストラクタ
	static CFinishUi* Create(const D3DXVECTOR3 pos, const int nDelay, const float fMaxAlpha);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

private:
	void StateDecSize();	//サイズ減算処理
	void StateNone();		//何もしない処理
	bool StateAddSize();	//サイズ加算処理

	STATE m_state;			//状態
	int m_nFrameCounter;	//フレームカウント用
	int m_nDelay;			//生成するまでの遅延
	int m_nDelayCounter;	//生成するまでの遅延のためのカウンター
	float m_fMaxAlpha;		//α値最大値
};

#endif // !_FINISH_UI_H_