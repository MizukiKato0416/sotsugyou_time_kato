//=============================================================================
//
// 人狼決定処理 [find_wolf_scene.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _FIND_WOLF_SCENE_H_
#define _FIND_WOLF_SCENE_H_

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
class CFindWolf : public CScene
{
public:
	CFindWolf();	        //デフォルトコンストラクタ
	virtual ~CFindWolf();	//デストラクタ
	void Init(void);	    //初期化処理
	void Uninit(void);	    //終了処理
	void Update(void);	    //更新処理

private:

};

#endif // !_FIND_WOLF_SCENE_H_