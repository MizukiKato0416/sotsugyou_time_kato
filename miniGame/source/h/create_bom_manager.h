//=============================================================================
//
// ボム生成処理 [create_bom_manager.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _CREATE_BOM_MANAGER_H_
#define _CREATE_BOM_MANAGER_H_

#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCreateBomManager : public CObject
{
public:
	CCreateBomManager();		//デフォルトコンストラクタ
	~CCreateBomManager();		//デストラクタ

	//何フレームに何個生成するか
	static CCreateBomManager* Create(const int nFrame, const int nNumBom);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void) {}	//描画処理

private:
	int m_nFrameCounter;		//Frameカウント用
	int m_nFrame;				//何フレーム毎にボムをだすか
	int m_nNumBom;				//ボムを出す個数
};

#endif // !_CREATE_BOM_MANAGER_H_