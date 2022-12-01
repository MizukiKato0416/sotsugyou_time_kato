//=============================================================================
//
// シーン処理 [scene.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObjectPlayer;

//*****************************************************************************
// シーンクラス
//*****************************************************************************
class CScene
{
public:
	//シーンの種類
	enum class SCENE_TYPE {
		TITLE = 0,
		SELECT_GAME,
		GAME_01,
		GAME_02,
		GAME_MAX,	//ランダム選択のためゲームシーンの最大を設定
		RESULT,
		FIND_WOLF,
		FINAL_RESULT,
		ENUM_MAX
	};

	CScene();	//デフォルトコンストラクタ
	virtual ~CScene();	//デストラクタ
	virtual void Init(void) = 0;	//初期化処理
	virtual void Uninit(void) = 0;	//終了処理
	virtual void Update(void) = 0;	//更新処理
	static void ChangeScene(CScene*& pScene, SCENE_TYPE typeScene);	//シーンの変更
	static SCENE_TYPE GetSceneType(void) { return m_typeScene; }	//現在のシーンの取得

	//プレイヤーのセッター・ゲッター
	void SetPlayer(CObjectPlayer* pPlayer) { m_pPlayer = pPlayer; }
	CObjectPlayer* GetPlayer(void) { return m_pPlayer; }
private:
	static SCENE_TYPE m_typeScene;
	CObjectPlayer* m_pPlayer;	//プレイヤーへのポインタ

};

#endif // !_SCENE_H_