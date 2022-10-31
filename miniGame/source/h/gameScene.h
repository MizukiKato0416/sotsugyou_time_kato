//=============================================================================
//
// ゲームシーン処理 [gameScene.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "scene.h"
#include "main.h"
#include "object_player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CTimer;
class CObject2D;
class CPauseMenu;
class CCheck;

//*****************************************************************************
// ゲームシーンクラス
//*****************************************************************************
class CGameScene : public CScene
{
public:
	CGameScene();	//デフォルトコンストラクタ
	virtual ~CGameScene();	//デストラクタ
	virtual void Init(void);	//初期化処理
	virtual void Uninit(void);	//終了処理
	virtual void Update(void);	//更新処理
	void DeletePauseMenu(void);	//ポーズメニューの破棄
	virtual void GameOver(void);	//ゲームオーバー

	virtual void UpdateGame(void) = 0;					//ゲーム中の更新
	virtual void UpdateGameOver(void) = 0;				//ゲームオーバー時の更新

	bool GetGameOver(void) { return m_bGameOver; }		//ゲームオーバー状態のフラグ
	CTimer* GetTimer(void) { return m_pTimer; }			//タイマーの取得

	//人狼モード設定処理
	static void SetWereWolfMode(const bool bWereWolfMode) { m_bWereWolfMode = bWereWolfMode; }
	//人狼モード取得処理
	static bool GetWereWolfMode(void) { return m_bWereWolfMode; }

	//人狼になったプレイヤーのインデックス設定処理(1Pは1、2Pは2)
	static void SetWereWolfPlayerIndex(const int nWereWolfPlayerIndex) { m_nWereWolfPlayerIndex = nWereWolfPlayerIndex; }
	//人狼になったプレイヤーのインデックス取得処理
	static int GetWereWolfPlayerIndex(void) { return m_nWereWolfPlayerIndex; }

private:
	
	static bool m_bWereWolfMode;			//人狼モードにするかどうか
	static int m_nWereWolfPlayerIndex;		//人狼になったプレイヤーのインデックス

protected:

	bool m_bGameOver;	//ゲームオーバー
	bool m_bAllCheck;	//全員がチェックできたかどうか

	CTimer* m_pTimer;													//ゲームのタイマー
	CObject2D* m_pTimerFrame;											//タイマーの枠
	CPauseMenu* m_pMenuPause;											//ポーズメニュー
	CCheck *m_pCheck;													//チェッククラスのポインタ
};

#endif // !_GAME_SCENE_H_