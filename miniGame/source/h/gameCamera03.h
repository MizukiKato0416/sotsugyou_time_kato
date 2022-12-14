//=============================================================================
//
// ゲームカメラ03処理 [gameCamera03.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _GAMECAMERA03_H_
#define _GAMECAMERA03_H_

#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// ゲームカメラ03クラス
//*****************************************************************************
class CGameCamera03 : public CCamera
{
public:
	CGameCamera03();		//デフォルトコンストラクタ
	~CGameCamera03();	//デストラクタ
	static CGameCamera03* Create(void);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理

	void SetDestPos(float fDestPos, int nFrameMove);	//目標位置を決める
	void OverLook(float fMinPos, float fMaxPos, int nFrameMove);		//見渡す

private:
	bool m_bMove;
	D3DXVECTOR3 m_destPos;	//カメラの目標位置
	float m_fSpeedMoveDest;	//カメラの目標位置への移動速度
	float m_fDestDist;		//カメラの目標距離
	float m_fSpeedDist;		//カメラの目標距離への移動速度
};

#endif // !_GAMECAMERA03_H_