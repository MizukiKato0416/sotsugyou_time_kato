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
class CCreateBomManager;
class CMeshwall;

//*****************************************************************************
// ゲームシーンクラス
//*****************************************************************************
class CGameScene02 : public CGameScene
{
public:
	CGameScene02();				//デフォルトコンストラクタ
	virtual ~CGameScene02();	//デストラクタ
	void Init(void);			//初期化処理
	void CreateObject(void);	//オブジェクト生成処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理
	void GameOver(void);		//ゲームオーバー

	//生きているプレイヤーの数設定処理
	void SetSavePlayerNum(const int nSavePlayerNum) { m_nSavePlayerNum = nSavePlayerNum; }
	//生きているプレイヤーの数加算処理
	void AddSavePlayerNum(const int nAddNum) { m_nSavePlayerNum += nAddNum; }
	//生きているプレイヤーの数設取得処理
	int GetSavePlayerNum() { return m_nSavePlayerNum; }

private:
	//天候の状態
	enum class WEATHER_STATE
	{
		CLOUDY = 0,		//曇り
		SUNNY,			//晴れ
		MAX
	};

	void UpdateGame(void);					//ゲーム中の更新
	void UpdateGameOver(void);				//ゲームオーバー時の更新
	void UpdateReady(void);					//準備状態中の更新

	void CreatePlayerIcon(int nCntPlayer);	//プレイヤーアイコン生成処理
	void CountDownUi(void);					//カウントダウンUIの処理
	bool Finish(void);						//フィニッシュするか確認処理
	void HurryUp(void);						//急げ処理
	void Cloud(void);						//雲の処理
	void CreateItem();						//アイテム生成処理
	void SetRanking();						//ランキング設定処理

	//CObjectPlayerAttackCar* m_apPlayer[MAX_OBJECT_PLAYER_NUM];			//プレイヤーのポインタ
	CObjectPlayerIcon *m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM];			//プレイヤーアイコンのポインタ
	CCreateBomManager *m_pCreateBomManager;								//ボム生成のポインタ
	std::vector<CMeshwall*> m_pCloud;									//雲のポインタ

	int m_nCntGameClear;					//ゲームクリア後のカウント
	int m_nItemCounter;						//アイテムの生成カウンター
	int m_nSavePlayerNum;					//生きているプレイヤーの数
	bool m_bHurryUp;						//急ぐかどうか
	WEATHER_STATE m_weatherState;			//天候の状態
};

#endif // !_GAME_SCENE01_H_