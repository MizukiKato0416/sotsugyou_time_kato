//=============================================================================
//
// チェックアイコン処理 [check_icon.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _CHECK_ICON_H_
#define _CHECK_ICON_H_

#include "object.h"
#include "object_player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CObject2D;
class CObjectModelUI;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCheckIcon : public CObject
{
public:
	CCheckIcon();		//デフォルトコンストラクタ
	~CCheckIcon();		//デストラクタ
	static CCheckIcon* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 posModel, const D3DXVECTOR3 scale, const int nPlayerNum);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void) {}	//描画処理

	//確認できたか取得処理
	bool GetCheck() { return m_bCheck; }
	//消すか取得処理
	bool GetUninit() { return m_bUninit; }
	//消すか設定処理
	void SetUninit(const bool bUninit, const int nDelay) { m_bUninit = bUninit, m_nDelay = nDelay; }
	//フレームのポインタ取得処理
	CObject2D *GetFrame(void) { return m_pFrame; }
	//ボタンのポインタ取得処理
	CObject2D *GetButton(void) { return m_pButton; }

private:
	//決定処理
	void Decide();
	//α値減算処理
	void DecAlpha();
	//マテリアル設定処理
	void SetMaterial(CObjectModelUI *pPlayerModel);
	//モデル回転処理
	void RotateModel();
	//モデル選択処理
	void SelectModel();

	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_posModel;					//モデルの初期位置
	D3DXVECTOR3 m_scale;					//スケール
	CObject2D *m_pFrame;					//フレーム
	CObject2D *m_pButton;					//ボタン
	CObjectModelUI *m_pPlayerModel;			//プレイヤーのモデル

	int m_nPlayerNum;			//プレイヤー番号
	int m_nCounter;				//フレームカウント用
	int m_nDelay;				//遅延用

	bool m_bCheck;				//確認できたかどうか
	bool m_bUninit;				//消すかどうか
};

#endif // !_CHECK_ICON_H_