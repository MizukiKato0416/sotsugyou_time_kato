//=============================================================================
//
// タイトルシーン処理 [titleScene.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "scene.h"
#include "object_player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
class CMeshwall;
class CObjectModel;

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
	bool ChangeColTime(bool bCol);	// タイトルシーンの色が変わる時間の処理

private:
	void Cloud();				//雲の処理
	void PlayerModel();			//プレイヤーのモデルの処理
	void Camera();				//カメラの処理

	static CObject2D * m_pNext;	// オブジェクト2Dの静的ポインター生成
	const int m_nDivideNum;		// 割る数
	const int m_nMaxColTime;	// 色が変わる時間の最大値
	const float m_fMaxCol;		// 色の最大値
	int m_nFadeTime;			// 遷移する時間	
	int m_nColorTime;			// 色を変える時間	
	bool m_bCol;				// 色を変えるかどうか
	bool m_bPushKey;			// 押されたかどうか

	std::vector<CMeshwall*> m_pCloud;							//雲のポインタ
	CObjectModel *m_pPlayerModel[MAX_OBJECT_PLAYER_NUM];		//プレイヤーのモデル
};

#endif // !_TITLE_SCENE_H_