//=============================================================================
//
// ゲーム選択シーン処理 [selectGameScene.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _SELECT_GAME_SCENE_H_
#define _SELECT_GAME_SCENE_H_

#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
class CSelectMenu3D;
class CNextButton;

//*****************************************************************************
// ゲーム選択シーンクラス
//*****************************************************************************
class CSelectGameScene : public CScene
{
public:
	CSelectGameScene();	//デフォルトコンストラクタ
	virtual ~CSelectGameScene();	//デストラクタ
	void Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理

private:
	void UpdateInput(void);	//入力処理
	void ChangeTutorial(void);	//チュートリアル表示の切り替え
	void ChangeGameTitle();		//ゲームタイトルの切替
	void ChangeMode(bool bWolf);	//嘘つきモードの切り替え
	void BgMove();					//背景の動きの処理

	int m_nFadeTime;	//フェード開始までのカウント
	bool m_bSelectGame;	//選択キー押下時

	bool m_bWolfMode;	//嘘つきモード
	CObject2D* m_pMenuBG;		//背景
	CSelectMenu3D* m_pMenuGame;	//開始するゲームの選択メニュー
	CObject2D* m_pGameName;		//ゲーム名
	CObject2D* m_pTutorial;		//チュートリアル画面
	CNextButton* m_pNextButton;	//次へのボタン
	CScene::SCENE_TYPE m_nextScene;	//開始するゲームシーンのタイプ
};

#endif // !_SELECT_GAME_SCENE_H_