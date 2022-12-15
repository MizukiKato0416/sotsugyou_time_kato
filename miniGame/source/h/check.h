//=============================================================================
//
// チェック処理 [check.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _CHECK_H_
#define _CHECK_H_

#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CCheckIcon;
class CObject2D;
class CCountDownUi;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCheck : public CObject
{
public:
	enum class STATE
	{
		NONE = 0,
		CHECK,		//チェック
		COUNTDOWN,	//カウントダウン
		MAX
	};

	CCheck();		//デフォルトコンストラクタ
	~CCheck();		//デストラクタ
	static CCheck* Create(const int nNumPlayer);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void) {}	//描画処理

	//チェックできたか取得処理
	bool GetCheckAll() { return m_bCheckAll; }
	//全部消されたか取得処理
	bool GetUninitAll() { return m_bAllUninit; }

	//カウントダウンUIを生成するかどうか取得処理
	bool GetCreateCountDownUi() { return m_bCreateCountDownUi; }
	//カウントダウンUIを生成するかどうか設定処理
	void SetCreateCountDownUi(const bool bCreateCountDownUi) { m_bCreateCountDownUi = bCreateCountDownUi; }

	//カウントダウンUI取得処理
	CCountDownUi *GetCountDownUi() { return m_pCountDownUi; }

	//状態取得処理
	STATE GetState() { return m_state; }

private:
	void DecFrame();		//フレームを消す処理
	void Check();			//チェック処理
	void CountDown();		//カウントダウン処理

	std::vector<CCheckIcon*> m_apCheckIcon;				//チェックアイコンのポインタ
	CObject2D *m_pFrame;								//背景の暗くなってるあれ
	CObject2D *m_pTutorial;								//説明UI
	CCountDownUi *m_pCountDownUi;						//カウントダウンUIのポインタ

	int m_nNumPlayer;									//プレイヤーの数
	bool m_bCheckAll;									//全員がチェックしたかどうか
	bool m_bAllUninit;									//全部消されたかどうか
	bool m_bCreateCountDownUi;							//カウントダウンUIを生成するかどうか
	STATE m_state;										//状態
};

#endif // !_CHECK_H_