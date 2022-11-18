//=============================================================================
//
// 最終結果シーン処理 [finalResultScene.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _FINAL_RESULT_SCENE_H_
#define _FINAL_RESULT_SCENE_H_

#include "scene.h"
#include "object_player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
class CObjectModel;
class CScore;

//*****************************************************************************
// 最終結果シーンクラス
//*****************************************************************************
class CFinalResultScene : public CScene
{
public:
	//フェーズ
	enum class PHASE
	{
		PHASE_FIRST = 0,//フェーズ開始
		RISE_CAMERA,	//カメラの上昇と回転
		RESULT_TEXT,	//結果発表のテキスト表示
		SHOW_SCORE_UI,	//スコアのUI表示
		RISE_TOWER,		//タワーの上昇
		WINNER,			//勝利
		PHASE_FINISH,	//フェーズ終了
		ENUM_MAX
	};

	CFinalResultScene();	//デフォルトコンストラクタ
	virtual ~CFinalResultScene();	//デストラクタ
	void Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理

	static void SetPlayerScore(int nScore, int nIdxPlayer) { m_aPlayerScore[nIdxPlayer] = nScore; }	//プレイヤーのスコアを設定

private:
	void PhaseFirst();	//フェーズ開始処理
	void RiseCamera();	//カメラの上昇処理
	void ResultText();	//結果発表のテキスト表示処理
	void ShowScoreUI();	//スコアのUI表示処理
	void RiseTower();	//タワーの上昇処理
	void Winner();			//勝利
	void PhaseFinish();	//フェーズ終了処理

	void StopTower(int nIdxPlayer);	//タワー停止時の処理

	PHASE m_phase;		//フェーズ
	int m_nCntPhase;	//フェースカウント
	static int m_aPlayerScore[MAX_OBJECT_PLAYER_NUM];	//プレイヤーのスコア

	CObjectModel* m_apObjPlayer[MAX_OBJECT_PLAYER_NUM];		//プレイヤーのモデルオブジェクト
	CObjectModel* m_apResultTower[MAX_OBJECT_PLAYER_NUM];	//プレイヤーの下にあるタワーのモデルオブジェクト
	CObject2D* m_pTextResult;	//結果発表の表示
	CScore* m_apScoreResult[MAX_OBJECT_PLAYER_NUM];		//スコアの表示
	int m_nTopScore;	//最高スコア
	std::vector<CObjectModel*> m_vObjCrown;	//王冠のモデルの配列
	int m_nFadeTime;	//フェード開始までのカウント
	bool m_bEndScene;	//選択キー押下時

};

#endif // !_FINAL_RESULT_SCENE_H_