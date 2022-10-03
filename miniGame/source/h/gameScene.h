//=============================================================================
//
// ゲームシーン処理 [gameScene.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CStage;
class CTimer;
class CObject2D;
class CPauseMenu;
class CSelectMenu2D;
class CScore;

//*****************************************************************************
// ゲームシーンクラス
//*****************************************************************************
class CGameScene : public CScene
{
public:
	CGameScene();	//デフォルトコンストラクタ
	virtual ~CGameScene();	//デストラクタ
	void Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void DeletePauseMenu(void);	//ポーズメニューの破棄
	void GameOver(void);	//ゲームオーバー

	bool GetGameOver(void) { return m_bGameOver; }		//ゲームオーバー状態のフラグ
	CTimer* GetTimer(void) { return m_pTimer; }	//タイマーの取得

private:
	void UpdateGame(void);			//ゲーム中の更新
	void UpdateGameOver(void);		//ゲームオーバー時の更新
	void CreateMenuEndGame(void);	//ゲーム終了時の選択メニューの生成

	bool m_bGameOver;	//ゲームオーバー

	CStage* m_pStage;				//ステージへのポインタ
	CTimer* m_pTimer;				//ゲームのタイマー
	CObject2D* m_pTimerFrame;		//タイマーの枠
	int m_nGameScore;				//ゲーム終了時のスコア
	CPauseMenu* m_pMenuPause;		//ポーズメニュー
	CSelectMenu2D* m_pMenuGameEnd;	//ゲーム終了時の選択メニュー

	int m_nCntGameClear;	//ゲームクリア後のカウント
};

#endif // !_GAME_SCENE_H_