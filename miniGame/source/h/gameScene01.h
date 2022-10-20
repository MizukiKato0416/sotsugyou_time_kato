//=============================================================================
//
// ゲームシーン01処理 [gameScene01.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _GAME_SCENE01_H_
#define _GAME_SCENE01_H_

#include "gameScene.h"
#include "main.h"
#include "object_player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BALLOON_MAX_NUM		(3)		//風船を一度に出す量

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObjectPlayerIcon;
class CObjectPlayerBalloonCar;

//*****************************************************************************
// ゲームシーンクラス
//*****************************************************************************
class CGameScene01 : public CGameScene
{
public:
	CGameScene01();	//デフォルトコンストラクタ
	virtual ~CGameScene01();	//デストラクタ
	void Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void GameOver(void);	//ゲームオーバー

private:
	void UpdateGame(void);					//ゲーム中の更新
	void UpdateGameOver(void);				//ゲームオーバー時の更新

	void CreateBalloon(void);				//風船生成処理
	void CreateItemBox(void);				//アイテムボックス生成処理
	void CreatePlayerIcon(int nCntPlayer);	//プレイヤーアイコン生成処理
	void CountDownUi(void);					//カウントダウンUIの処理

	CObjectPlayerBalloonCar* m_apPlayer[MAX_OBJECT_PLAYER_NUM];			//プレイヤーのポインタ
	CObjectPlayerIcon *m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM];			//プレイヤーアイコンのポインタ

	int m_nCntGameClear;					//ゲームクリア後のカウント
	int m_nCreateItemBoxCounter;			//アイテムボックスの生成カウンタ
};

#endif // !_GAME_SCENE01_H_