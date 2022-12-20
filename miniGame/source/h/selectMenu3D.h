//=============================================================================
//
// 3D選択メニュー処理 [selectMenu3D.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _SELECT_MENU_3D_H_
#define _SELECT_MENU_3D_H_

#include "selectMenu.h"
#include "objectModelUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// 3D選択メニュークラス
//*****************************************************************************
class CSelectMenu3D : public CSelectMenu
{
public:

	CSelectMenu3D();		//デフォルトコンストラクタ
	CSelectMenu3D(int nNumSelect, D3DXVECTOR3 posCenter, float fRadiusModel, bool bUseBG);	//オーバーロードされたコンストラクタ
	virtual ~CSelectMenu3D();		//デストラクタ
	static CSelectMenu3D* Create(int nNumSelect, D3DXVECTOR3 posCenter, float fRadius, CModel::MODELTYPE typeModel, float fDistCamera, float fHeightCamera, bool bUseBG, bool bUseShadow);	//生成処理
	virtual HRESULT Init(void);	//初期化処理
	virtual void Uninit(void);	//終了処理
	virtual void Update(void);	//更新処理
	virtual void Draw(void) {}	//描画処理

	virtual void BeginChangeSelect(bool bChangePlus);	//選択の変更が開始されたときの処理
	virtual void EndChangeSelect(void) {}	//選択の変更が終了したときの処理

	CObjectModelUI* GetModelUI(unsigned int nIdx);	//UIモデルオブジェクトのポインタを取得
	virtual void SetIdxCurSelect(int nIdx);			//現在の選択の番号を設定し、その角度にモデルを合わせる
	void SetSpeedRotModel(float fSpeed) { m_fSpeedRotModel = fSpeed; }	//モデル移動時の回転速度の設定
	float GetSpeedRotModel(void) { return m_fSpeedRotModel; }			//モデル移動時の回転速度の取得
	void SetCountRotate(int nCnt) { m_nCntRotate = nCnt; }		//回転するカウントの設定
	int GetCountRotate(void) { return m_nCntRotate; }			//回転するカウントの設定
	void SetSpanRotate(int nSpan) { m_nSpanRotate = nSpan; }	//回転スパンの設定

	void SetRotDest(int nIdxCurSelect) { m_fRotModelDest = D3DX_PI * 2 * ((float)nIdxCurSelect / GetNumSelect()); }	//目標の角度を選択のインデックスから設定

	void SetRoulette(bool bRoulette) { m_bRoulette = bRoulette; }	//ルーレット状態の設定
	bool GetRoulette(void) { return m_bRoulette; }	//ルーレット状態の取得
	void BeginRoulette(int nCntRoulette, float fSpeedRot, float fSpeedRate) { m_bRoulette = true; m_nCntRoulette = nCntRoulette; m_fSpeedRotModel = fSpeedRot; m_fRouletteSpeedRate = fSpeedRate; }	//ルーレットの開始
	int GetCountRoulette(void) { return m_nCntRoulette; }	//ルーレットのカウントの取得


private:
	void CreateModelUI(void);	//モデルの生成
	void RotateMenu(void);		//メニューを回転
	void RouletteMenu(void);	//ルーレットでメニューを回転
	void MoveModel(void);		//モデル移動
	void MoveShadow(void);		//影移動

	const D3DXVECTOR3 m_posCenter;	//メニューの中央の位置
	const float m_fRadiusModel;		//オブジェクトを配置する半径

	std::vector<CObjectModelUI*> m_vpObjModelUI;	//UIモデルオブジェクトのポインタのベクター配列
	CModel::MODELTYPE m_typeModel;					//生成するモデルの種類（全てのモデルはこれが初期のタイプ）
	bool m_bUsePlaneShadow;							//影の使用
	std::vector<CObjectModelUI*> m_vpPlaneShadow;	//UIモデルの影のポインタのベクター配列

	int m_nSpanRotate;		//回転のスパン
	int m_nCntRotate;		//回転するカウント
	float m_fRotModel;		//モデルの配置位置を決める角度
	float m_fRotModelDest;	//モデルの目標角度
	float m_fSpeedRotModel;	//モデル移動時の回転速度

	bool m_bRoulette;			//ルーレットの回転
	int m_nCntRoulette;			//ルーレット回転するカウント
	float m_fRouletteSpeedRate;	//ルーレットの速度の乗算される値

	float m_fDistCamera;	//メニュー用のカメラの距離
	float m_fRotCamera;		//メニュー用のカメラのY角度
	float m_fHeightCamera;	//メニュー用のカメラの位置の高さ
};

#endif // !_SELECT_MENU_3D_H_