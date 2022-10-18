//=============================================================================
//
// スコアUI処理 [score_ui.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _SCORE_UI_H_
#define _SCORE_UI_H_

#include "object.h"
#include "object_player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CObject2D;
class CScore;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScoreUi : public CObject
{
public:
	CScoreUi();		//デフォルトコンストラクタ
	~CScoreUi();		//デストラクタ
	static CScoreUi* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale, const int nPlayerNum);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void) {}	//描画処理

	//スコア取得処理
	CScore *GetScore(void) { return m_pScore; }

private:
	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_scale;		//スケール

	CObject2D *m_pFrame;		//フレームのポインタ
	CScore *m_pScore;			//スコアのポインタ

	int m_nPlayerNum;			//プレイヤー番号
};

#endif // !_SCORE_UI_H_