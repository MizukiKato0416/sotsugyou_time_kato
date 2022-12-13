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
#define TITLE_LOGO_CHARA_NUM	(4)		//タイトルロゴの文字

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
	void CreateObject(void);	//オブジェクト生成処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	bool ChangeColTime(bool bCol);	// タイトルシーンの色が変わる時間の処理

private:
	//フェーズ
	enum class PHASE
	{
		NONE = 0,
		CHARACTOR_LOGO,		//文字のロゴ
		THE_FINAL_LOGO,		//ザファイナルのロゴ
		BOUND_LOGO,			//ロゴのバウンド
		STOP_TITLE_LOGO,	//タイトルロゴ停止
		MAX
	};

	void PlayerModel();			//プレイヤーのモデルの処理
	void Camera();				//カメラの処理
	void CharactorLogo();		//文字のロゴの処理
	void TheFinalLogo();		//ザファイナルのロゴの処理
	void BoundLogo();			//ロゴのバウンドの処理
	void StopTitleLogo();		//タイトルロゴ停止
	void ExplosionLogo();		//爆発ロゴの処理
	void CarLogo();				//車ロゴの処理
	bool CreateAllLogo();		//全てのロゴを生成する処理
	void DeleteLogo();			//ロゴ消す処理
	void Decide();				//決定処理
	bool Reset();				//リセット処理


	static CObject2D * m_pNext;	// オブジェクト2Dの静的ポインター生成
	const int m_nDivideNum;		// 割る数
	const int m_nMaxColTime;	// 色が変わる時間の最大値
	const float m_fMaxCol;		// 色の最大値
	int m_nFadeTime;			// 遷移する時間	
	int m_nColorTime;			// 色を変える時間	
	bool m_bCol;				// 色を変えるかどうか
	bool m_bPushKey;			// 押されたかどうか

	CObjectModel *m_pPlayerModel[MAX_OBJECT_PLAYER_NUM];		//プレイヤーのモデル
	CObject2D *m_pTitleLogoChara[TITLE_LOGO_CHARA_NUM];			//タイトルロゴの文字
	CObject2D *m_pTheFinalLogo;									//ザファイナルロゴ
	CObject2D *m_pTitleLogo;									//タイトルロゴ
	CObject2D *m_pExplosionLogo;								//爆発ロゴ
	CObject2D *m_pTitleLogoCar;									//車ロゴ

	int m_nFrameCounter;					//フレームカウンター
	int m_nFrameCounterReset;				//フレームカウンター(リセット用)
	PHASE m_phase;							//フェーズ
	float m_fBoundMove;						//バウンド移動量
	bool m_bExplosionAddSize;				//サイズを大きくするかどうか
	bool m_bCarLogoRight;					//右にいるかどうか
	float m_fCarLogoMove;					//車ロゴの移動量
	bool m_bCreateAllLogo;					//全てのロゴを生成した状態かどうか
};

#endif // !_TITLE_SCENE_H_