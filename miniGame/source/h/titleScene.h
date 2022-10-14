//=============================================================================
//
// タイトルシーン処理 [titleScene.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// タイトルシーンクラス
//*****************************************************************************
class CTitleScene : public CScene
{
public:
	CTitleScene();	//デフォルトコンストラクタ
	virtual ~CTitleScene();	//デストラクタ
	void Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理

private:
	static CObject2D * m_pNext;// オブジェクト2Dの静的ポインター生成
	const float m_fMaxCol;	// 色の最大値
	int m_nFadeTime;	// 遷移する時間
	bool m_bBeginFade;	//シーン遷移開始したかどうか
	bool m_bCol; // 色を変えるかどうか
	bool m_bPushKey; // 押されたかどうか
};

#endif // !_TITLE_SCENE_H_