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
#define GAME03_ONE_METER (20.0f)		//game03の１ｍ分の距離

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObjectPlayerIcon;
class CObject2D;
class CScore;

//*****************************************************************************
// ゲームシーンクラス
//*****************************************************************************
class CGameScene03 : public CGameScene
{
public:
	CGameScene03();				//デフォルトコンストラクタ
	virtual ~CGameScene03();	//デストラクタ
	void Init(void);			//初期化処理
	void CreateObject(void);	//オブジェクト生成処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理
	void GameOver(void);		//ゲームオーバー

private:
	void UpdateGame(void);					//ゲーム中の更新
	void UpdateGameOver(void);				//ゲームオーバー時の更新
	void UpdateReady(void);					//準備状態中の更新
	void CreatePlayerIcon(int nCntPlayer);	//プレイヤーアイコン生成処理
	void UpdatePlayerIcon(void);			//プレイヤーアイコン更新処理
	void ShowDestDist(void);				//目標位置表示
	void CountDownUi(void);					//カウントダウンUIの処理
	void LookPlayerPos(void);				//プレイヤーの位置の監視
	void UpdateCamera(void);				//カメラの位置の更新
	//void UpdateLight(void);					//ライトの位置の更新
	void DecideRanking(void);				//プレイヤーの位置からランキングを決定してシーンのランキングに設定する

	CObjectPlayerIcon *m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM];	//プレイヤーアイコンのポインタ
	float m_fPlayerSpeedMax;//プレイヤーの最大速度
	float m_fDestPos;		//目標の距離
	bool m_bEndShowDest;	//目標位置表示済みかどうか
	int m_nCntShowDist;		//目標位置表示カウンター
	CObject2D* m_pTomare;	//００ｍを止まれUI
	CScore* m_pTomareDist;	//止まれUIの距離部分の数字
	float m_fPosPlayerMin;	//プレイヤーの最小の位置
	float m_fPosPlayerMax;	//プレイヤーの最大の位置
	int m_nCntGameOver;		//ゲーム終了後のカウント
};

#endif // !_GAME_SCENE03_H_