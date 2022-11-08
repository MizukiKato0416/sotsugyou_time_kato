//=============================================================================
//
// 人狼決定処理 [wolf_decide.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _WOLF_DECIDE_H_
#define _WOLF_DECIDE_H_

#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CWolfDecide : public CObject
{
public:
	//フェーズ
	enum class PHASE
	{
		NONE = 0,
		SHAKE_TUTORIAL,		//振動説明
		SHAKE,				//振動
		GAME_START,			//ゲームスタート
		UNINIT,				//終了
		MAX
	};


	CWolfDecide();		//デフォルトコンストラクタ
	~CWolfDecide();		//デストラクタ
	static CWolfDecide* Create();	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void) {}	//描画処理

	//フェーズ取得処理
	PHASE GetPhase() { return m_phase; }

private:
	void ShakeTutorial();	//振動説明処理
	void Shake();			//振動処理
	void GameStart();		//ゲームスタート処理


	CObject2D *m_pBg;			//背景
	CObject2D *m_pTutorialUI;	//説明UI
	CObject2D *m_pShakeUI;		//振動UI
	
	int m_nShakeUiCounter;		//振動UI点滅カウンター
	PHASE m_phase;				//フェーズ
};

#endif // !_WOLF_DECIDE_H_