//=============================================================================
//
// 最終結果カメラ処理 [finalResultCamera.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _FINAL_RESULT_CAMERA_H_
#define _FINAL_RESULT_CAMERA_H_

#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// 最終結果カメラクラス
//*****************************************************************************
class CFinalResultCamera : public CCamera
{
public:
	CFinalResultCamera();		//デフォルトコンストラクタ
	~CFinalResultCamera();	//デストラクタ
	static CFinalResultCamera* Create(void);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理

private:

};

#endif // !_FINAL_RESULT_CAMERA_H_