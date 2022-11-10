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
class CTimer;

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
		TUTORIAL_1,			//説明1
		TUTORIAL_2,			//説明2
		WOLF_DECIDE,		//人狼決定
		TUTORIAL_3,			//説明3
		WAIT,				//待ち時間
		ANSWER,				//答え
		TUTORIAL_4,			//説明4
		DEC_WOLF_POINT,		//人狼のポイントマイナス
		ADD_PLAYER_POINT,	//人狼以外のポイント加算
		DEC_PLAYER_POINT,	//人狼以外のポイントマイナス
		ADD_WOLF_POINT,		//人狼のポイント加算
		MAX
	};

	//選択肢
	enum class SELECT
	{
		PLAYER_1 = 0,
		PLAYER_2,
		PLAYER_3,
		PLAYER_4,
		SELECT_MAX
	};

	void Tutorial1();			//説明1処理
	void Tutorial2();			//説明2処理
	void WolfDecide();			//人狼決定処理
	void Tutorial3();			//説明3処理
	void Wait();				//待つ処理
	void Answer();				//回答処理
	void Tutorial4();			//説明4処理
	void DecWolfPoint();		//人狼のポイントマイナス処理
	void AddPlayerPoint();		//人狼以外のポイント加算処理
	void DecPlayerPoint();		//人狼以外のポイントマイナス処理
	void AddWolfPoint();		//人狼のポイント加算処理



	//選択用アイコンUIの位置設定処理
	void SelectIconSetPos(const int nIdxPlayer, const SELECT select);

	CScoreUi *m_apScoreUi[MAX_OBJECT_PLAYER_NUM];		//スコアUI 
	CObject2D *m_pSelectIcon[MAX_OBJECT_PLAYER_NUM];	//選択用アイコン
	CObject2D *m_pTutorial;								//説明UI
	CTimer* m_pTimer;									//ゲームのタイマー
	CObject2D* m_pTimerFrame;							//タイマーの枠

	D3DXVECTOR3 m_aPosPlayer2D[MAX_OBJECT_PLAYER_NUM];		//プレイヤーの2D座標
	SELECT m_select[MAX_OBJECT_PLAYER_NUM];	//どこが選択されているのか

	PHASE m_phase;						//フェーズ
	int m_nFrameCounter;				//Frameカウント用
};

#endif // !_FIND_WOLF_SCENE_H_