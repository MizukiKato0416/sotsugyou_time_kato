//=============================================================================
//
// クレジットシーン処理 [creditScene.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _CREDIT_SCENE_H_
#define _CREDIT_SCENE_H_

#include "scene.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
class CNextButton;

//*****************************************************************************
// リザルトシーンクラス
//*****************************************************************************
class CCreditScene : public CScene
{
public:
	CCreditScene();				//デフォルトコンストラクタ
	virtual ~CCreditScene();	//デストラクタ
	void Init(void);			//初期化処理
	void CreateObject(void);	//オブジェクト生成処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理

private:
	enum class PHASE
	{
		NONE = 0,
		BG_CAR_00,	//背景車00
		BG_CAR_01,	//背景車01	
		BG_TITLE,	//背景タイトル	
		BG_00,		//背景00
		BG_01,		//背景01
		MAX
	};

	void BgCar00();										//背景車処理
	void BgCar01();										//背景車処理
	void BgTitle();										//背景タイトル処理
	void Bg00();										//背景処理
	void BgStage();										//背景ステージ処理
	void SceneFade();									//遷移処理
	void Credit();										//クレジット処理
	void CreatePicture();								//絵生成処理
	void SetFade(const int nCnt, const D3DXCOLOR col);	//フェード設定処理
	void Fade();										//フェード処理
	void SkipIcon();									//スキップアイコン処理

	CObject2D *m_pBg;				//背景
	CObject2D *m_pBgStage;			//背景ステージ
	CObject2D *m_pCredit;			//クレジット
	CObject2D *m_pFade;				//フェード用
	CObject2D *m_pSkipIcon;			//スキップアイコン
	bool m_bCanFade;				//フェードできるかどうか
	bool m_bPictureRot;				//傾きを切り替える用
	bool m_bFade;					//フェードしているかどうか
	bool m_bFadeIn;					//フェードアウトフェードイン切り替え
	bool m_bUninitSkipIcon;			//スキップアイコンを消すかどうか
	int m_nFrameCounter;			//Frameカウント用
	int m_nFadeTime;				//フェードの時間
	int m_nSkipIconCounter;			//スキップアイコンの表示時間カウント用
	D3DXCOLOR m_fadeCol;			//フェードの色
	PHASE m_phase;					//フェーズ
};

#endif // !_CREDIT_SCENE_H_