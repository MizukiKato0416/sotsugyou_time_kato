//=============================================================================
//
// カウントダウンUI処理 [count_down_ui.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _COUNT_DOWN_UI_H_
#define _COUNT_DOWN_UI_H_

#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// カウントダウンクラス
//*****************************************************************************
class CCountDownUi : public CObject
{
public:
	CCountDownUi();		//デフォルトコンストラクタ
	~CCountDownUi();	//デストラクタ
	static CCountDownUi* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void) {}	//描画処理

	//スタートしているかどうか取得処理
	bool GetStart() { return m_bStart; }
	//スタートしているかどうか設定処理
	void GetStart(const bool bStart) { m_bStart = bStart; }

	//カウントダウンUI取得処理
	CObject2D *GetCountUi() { return m_pCountUi; }

private:
	CObject2D *m_pCountUi;	//カウント用UIのポインタ
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_scale;	//スケール
	int m_nCounter;			//Frameカウント用
	bool m_bStart;			//スタートしているかどうか
};

#endif // !_COUNT_DOWN_UI_H_