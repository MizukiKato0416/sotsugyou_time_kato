//=============================================================================
//
// リザルトシーン処理 [resultScene.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _RESULT_SCENE_H_
#define _RESULT_SCENE_H_

#include "scene.h"
#include "main.h"
#include "object_player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
class CObjectModelUI;
class CNextButton;

//*****************************************************************************
// リザルトシーンクラス
//*****************************************************************************
class CResultScene : public CScene
{
public:
	CResultScene();				//デフォルトコンストラクタ
	virtual ~CResultScene();	//デストラクタ
	void Init(void);			//初期化処理
	void CreateObject(void);	//オブジェクト生成処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理

private:
	void PointUI();			//ポイントUIの処理
	void Player();			//プレイヤーの処理
	void NextButton();		//次に進むUI処理
	void Bg();				//背景処理
	void Fade();			//遷移処理
	void FrameCounter();	//フレームカウント処理

	int m_nCntScene;			//シーン開始時からのカウント
	int m_nFrameCounter;		//ポイントUIのカウンター

	CObject2D *m_pBg;											//背景
	CObject2D *m_apPointUi[MAX_OBJECT_PLAYER_NUM];				//ポイント用UI
	CObjectModelUI *m_pPlayerModel[MAX_OBJECT_PLAYER_NUM];		//プレイヤーのモデル
	CNextButton *m_pNextButton;									//次に進むボタンUI

};

#endif // !_RESULT_SCENE_H_