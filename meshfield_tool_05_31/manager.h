//===========================================
//マネージャ処理
//Author:加藤瑞葵
//===========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "object.h"
#include "camera.h"
#include "light.h"

//前方宣言
class CRenderer;
class CInputKeyboard;
class CInputPadX;
class CInputPadD;
class CInputMouse;
class CTexture;
class CGame01;
class CFade;
class CXload;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CManager
{
public:
	//モードの種類
	enum class MODE
	{
		GAME01 = 0,		//ゲーム01
		MAX
	};

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CManager *GetInstance(void);											//インスタンス取得処理
	static CRenderer *GetRenderer(void);										//レンダラー取得処理
	static CInputKeyboard *GetInputKeyboard(void);								//キーボード取得処理
	static CInputPadX *GetInputPadX(void);										//パッド(X)取得処理
	static CInputPadD *GetInputPadD(void);										//パッド(D)取得処理
	static CInputMouse *GetInputMouse(void);									//マウス取得処理
	static CLight *GetLight(void);												//ライト取得処理
	static CTexture *GetTexture(void);											//テクスチャ取得処理
	static CCamera** GetCamera(void);											//カメラ取得処理
	static CXload *GetXload(void);												//xファイル読み込み取得処理
	static CGame01 *GetGame01(void);											//ゲーム01取得処理
	static void SetMode(MODE mode);												//モード設定
	static MODE GetMode(void);													//モード取得
	static CFade *GetFade(void);												//フェード取得処理
	static HWND GetWindowHandle(void) { return m_hWnd; }						//hwnd取得処理

private:
	//メンバ関数
	CManager();				//コンストラクタ
	~CManager();			//デストラクタ

	static CManager *s_pManager;						//マネージャーのインスタンス
	static CRenderer *m_pRenderer;						//レンダラーのポインタ
	static CInputKeyboard *m_pInputKeyboard;			//キーボードのポインタ
	static CInputPadX *m_pInputPadX;					//パッド(X)のポインタ
	static CInputPadD *m_pInputPadD;					//パッド(D)のポインタ
	static CInputMouse *m_pInputMouse;					//マウスのポインタ
	static CLight *m_apLight[MAX_LIGHT];				//ライトのポインタ
	static CTexture *m_pTexture;						//テクスチャのポインタ
	static CCamera* m_apCamera[MAX_CAMERA];				//カメラのポインタ
	static CXload *m_pXload;							//xファイル読み込みのポインタ
	static CGame01 *m_pGame01;							//ゲーム01のポインタ
	static MODE m_mode;									//モード
	static CFade *m_pFade;								//フェードのポインタ
	static HWND m_hWnd;									//ウィンドウハンドル
};


#endif // !_MANAGER_H_