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
class CObjectPlayer;
class CPauseMenu;
class CCheck;
class CWolfDecide;

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
	void CreatePauseMenu(void);	//ポーズメニューの生成
	void DeletePauseMenu(void);	//ポーズメニューの破棄
	virtual void GameOver(void);	//ゲームオーバー

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

	//ランキング設定処理(0は1P1は2P)
	static void SetRanking(const int nRanking, const int nIndex) { m_aRanking[nIndex] = nRanking; }
	//ランキング取得処理(0は1P1は2P)
	static int GetRanking(const int nIndex) { return m_aRanking[nIndex]; }

	//プレイヤー取得処理
	CObjectPlayer* GetPlayer(const int nCntPlayer) { return m_apPlayer[nCntPlayer]; }

private:
	virtual void UpdateGame(void) = 0;		//ゲーム中の更新
	virtual void UpdateGameOver(void) = 0;	//ゲームオーバー時の更新
	virtual void UpdateReady(void) = 0;		//準備状態中の更新

	static bool m_bWereWolfMode;					//人狼モードにするかどうか
	static int m_nWereWolfPlayerIndex;				//人狼になったプレイヤーのインデックス
	static int m_aRanking[MAX_OBJECT_PLAYER_NUM];	//プレイヤーのランキング

protected:
	void CreateIcon(void);	//アイコン生成処理


	bool m_bGameOver;	//ゲームオーバー
	bool m_bAllCheck;	//全員がチェックできたかどうか
	bool m_bReady;		//準備状態かどうか
	bool m_bLockPauseMenu;	//ポーズメニュー生成のロック

	CTimer* m_pTimer;			//ゲームのタイマー
	CObject2D* m_pTimerFrame;	//タイマーの枠
	CPauseMenu* m_pMenuPause;	//ポーズメニュー
	CCheck *m_pCheck;			//チェッククラスのポインタ
	CWolfDecide *m_pWolfDecide;	//人狼決定クラスのポインタ
	CObjectPlayer* m_apPlayer[MAX_OBJECT_PLAYER_NUM];			//プレイヤーのポインタ
};

#endif // !_GAME_SCENE_H_