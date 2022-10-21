//=============================================================================
//
// ゲームシーン02処理 [gameScene02.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _GAME_SCENE02_H_
#define _GAME_SCENE02_H_

#include "gameScene.h"
#include "main.h"
#include "object_player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAME_02_STAGE_SIZE				(700.0f)				//すてーじの大きさ

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObjectPlayerIcon;
class CObjectPlayerAttackCar;

//*****************************************************************************
// ゲームシーンクラス
//*****************************************************************************
class CGameScene02 : public CGameScene
{
public:
	CGameScene02();	//デフォルトコンストラクタ
	virtual ~CGameScene02();	//デストラクタ
	void Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void GameOver(void);	//ゲームオーバー

private:
	void UpdateGame(void);					//ゲーム中の更新
	void UpdateGameOver(void);				//ゲームオーバー時の更新

	void CreatePlayerIcon(int nCntPlayer);	//プレイヤーアイコン生成処理
	void CountDownUi(void);					//カウントダウンUIの処理
	bool Finish(void);						//フィニッシュするか確認処理

	CObjectPlayerAttackCar* m_apPlayer[MAX_OBJECT_PLAYER_NUM];			//プレイヤーのポインタ
	CObjectPlayerIcon *m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM];			//プレイヤーアイコンのポインタ

	int m_nCntGameClear;					//ゲームクリア後のカウント
};

#endif // !_GAME_SCENE01_H_