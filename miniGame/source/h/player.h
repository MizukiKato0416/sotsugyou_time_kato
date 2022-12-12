//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"
#include "object_player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CModel;

//*****************************************************************************
// クラス
//*****************************************************************************
class CPlayer : public CObject
{
public:
	CPlayer();		//デフォルトコンストラクタ
	~CPlayer();	//デストラクタ
	static CPlayer* Create();	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void) {}	//描画処理

	//プレイヤー番号設定処理
	void SetIndex(const int nIndex) { m_nIndex = nIndex; }
	//プレイヤー番号取得処理
	int GetIndex(void) { return m_nIndex; }

	//プレイヤーの総数取得処理
	static int GetNum(void) { return m_nObjectPlayerNum; }

	//更新するかどうか取得処理
	bool GetUpdate() { return m_bUpdate; }
	//更新するかどうか設定処理
	void SetUpdate(const bool bUpdate) { m_bUpdate = bUpdate; }

	//モデルタイプ設定処理
	static void SetModelType(const int nCntPlayer, const CModel::MODELTYPE modelType) { m_aModelType[nCntPlayer] = modelType; }
	//モデルタイプ取得処理
	static CModel::MODELTYPE GetModelType(const int nCntPlayer) { return m_aModelType[nCntPlayer]; }

private:
	static CModel::MODELTYPE m_aModelType[MAX_OBJECT_PLAYER_NUM];	//プレイヤーのモデルタイプ
	static int m_nObjectPlayerNum;	//プレイヤーの数
	int m_nIndex;					//プレイヤー番号
	bool m_bUpdate;					//更新処理をするかどうか
};

#endif // !_PLAYER_H_