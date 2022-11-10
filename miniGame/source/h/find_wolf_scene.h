//=============================================================================
//
// 人狼決定処理 [find_wolf_scene.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _FIND_WOLF_SCENE_H_
#define _FIND_WOLF_SCENE_H_

#include "scene.h"
#include "object_player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
class CScoreUi;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CFindWolfScene : public CScene
{
public:
	CFindWolfScene();	        //デフォルトコンストラクタ
	virtual ~CFindWolfScene();	//デストラクタ
	void Init(void);	    //初期化処理
	void Uninit(void);	    //終了処理
	void Update(void);	    //更新処理

private:
	//フェーズ
	enum class PHASE
	{
		NONE = 0,
		TUTORIAL_1,		//説明1
		TUTORIAL_2,		//説明2
		WOLF_DECIDE,	//人狼決定
		TUTORIAL_3,		//説明3
		WAIT,			//待ち時間
		ANSWER,			//答え
		TUTORIAL_4,		//説明4
		MAX
	};

	void Tutorial1();	//説明1処理
	void Tutorial2();	//説明2処理
	void WolfDecide();	//人狼決定処理
	void Tutorial3();	//説明3処理
	void Wait();		//待つ処理
	void Answer();		//回答処理
	void Tutorial4();	//説明4処理

	CScoreUi *m_apScoreUi[MAX_OBJECT_PLAYER_NUM];	//スコアUI 
	CObject2D *m_pTutorial;							//説明UI

	PHASE m_phase;									//フェーズ
};

#endif // !_FIND_WOLF_SCENE_H_