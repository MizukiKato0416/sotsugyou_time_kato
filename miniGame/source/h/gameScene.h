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
#define BALLOON_MAX_NUM		(3)		//風船を一度に出す量

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CStage;
class CTimer;
class CObject2D;
class CPauseMenu;
class CSelectMenu2D;
class CScore;
class CCountDownUi;
class CObjectPlayerIcon;
class CCheck;
class CObjectPlayerBalloonCar;

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
	void UpdateGame(void);					//ゲーム中の更新
	void UpdateGameOver(void);				//ゲームオーバー時の更新
	void CreateMenuEndGame(void);			//ゲーム終了時の選択メニューの生成
	void CreateBalloon(void);				//風船生成処理
	void CreateItemBox(void);				//アイテムボックス生成処理
	void CreatePlayerIcon(int nCntPlayer);	//プレイヤーアイコン生成処理
	void CountDownUi(void);					//カウントダウンUIの処理

	bool m_bGameOver;	//ゲームオーバー
	bool m_bAllCheck;	//全員がチェックできたかどうか

	CStage* m_pStage;													//ステージへのポインタ
	CTimer* m_pTimer;													//ゲームのタイマー
	CObject2D* m_pTimerFrame;											//タイマーの枠
	int m_nGameScore;													//ゲーム終了時のスコア
	CPauseMenu* m_pMenuPause;											//ポーズメニュー
	CSelectMenu2D* m_pMenuGameEnd;										//ゲーム終了時の選択メニュー
	CObjectPlayerBalloonCar* m_apPlayer[MAX_OBJECT_PLAYER_NUM];			//プレイヤーのポインタ
	CObjectPlayerIcon *m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM];			//プレイヤーアイコンのポインタ
	CCheck *m_pCheck;													//チェッククラスのポインタ

	int m_nCntGameClear;					//ゲームクリア後のカウント
	int m_nCreateItemBoxCounter;			//アイテムボックスの生成カウンター
};

#endif // !_GAME_SCENE_H_