//=============================================================================
//
// ゲームシーン03処理 [gameScene03.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _GAME_SCENE03_H_
#define _GAME_SCENE03_H_

#include "gameScene.h"
#include "main.h"
#include "object_player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObjectPlayerIcon;
class CObjplayerStop;

//*****************************************************************************
// ゲームシーンクラス
//*****************************************************************************
class CGameScene03 : public CGameScene
{
public:
	CGameScene03();				//デフォルトコンストラクタ
	virtual ~CGameScene03();	//デストラクタ
	void Init(void);			//初期化処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理
	void GameOver(void);		//ゲームオーバー

private:
	void UpdateGame(void);					//ゲーム中の更新
	void UpdateGameOver(void);				//ゲームオーバー時の更新
	void UpdateReady(void);					//準備状態中の更新
	void CreatePlayerIcon(int nCntPlayer);	//プレイヤーアイコン生成処理
	void CountDownUi(void);					//カウントダウンUIの処理
	void UpdateCamera(void);				//カメラの位置の更新

	CObjplayerStop* m_apPlayer[MAX_OBJECT_PLAYER_NUM];			//プレイヤーのポインタ
	CObjectPlayerIcon *m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM];	//プレイヤーアイコンのポインタ
	float m_fDestDist;		//目標の距離
	int m_nCntGameClear;	//ゲームクリア後のカウント
};

#endif // !_GAME_SCENE03_H_