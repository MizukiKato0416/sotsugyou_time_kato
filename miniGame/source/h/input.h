//=============================================================================
//
// 入力処理 [input.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PAD_CONNECT_NUM	(4)		//ゲームパッド接続数

//*****************************************************************************
// インプットクラス
//*****************************************************************************
class CInput
{
public:
	enum class CODE {
		//システム
		SELECT = 0,
		BACK,
		PAUSE,
		//移動
		MOVE_UP,	//上
		MOVE_DOWN,	//下
		MOVE_LEFT,	//左
		MOVE_RIGHT,	//右
		MOVE_RISE,	//上昇
		MOVE_FALL,	//下降
		//回転
		ROTATE_UP,		//上
		ROTATE_DOWN,	//下
		ROTATE_LEFT,	//左
		ROTATE_RIGHT,	//右
		//選択
		SELECT_UP,
		SELECT_DOWN,
		SELECT_LEFT,
		SELECT_RIGHT,
		//アクション
		ACCELE,			//アクセル
		REVERSE,		//バック
		USE_ITEM,		//アイテムの使用
		CAR_ATTACK,		//アタック
		CAR_DEFENSE,	//チート用ディフェンス
		//チェック
		CHECK_X,		//Xボタン
		CHECK_B,		//Bボタン
		CHECK_A,		//Aボタン
		CHECK_Y,		//Yボタン

#ifdef _DEBUG
		//デバッグ用
		DEBUG_0,
		DEBUG_1,
		DEBUG_2,
		DEBUG_3,
#endif

		CODE_MAX
	};

	CInput();			//デフォルトコンストラクタ
	virtual ~CInput();	//デストラクタ
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//初期化処理
	virtual void Uninit(void);		//終了処理
	virtual void Update(void) = 0;		//更新処理
	virtual bool GetPress(CODE code, int nIdx) = 0;		//入力判定（プレス）
	virtual bool GetTrigger(CODE code, int nIdx) = 0;	//入力判定（トリガー）

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;
	static LPDIRECTINPUT8 m_pInput;
};

//*****************************************************************************
// キーボードクラス
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(CODE code, int nIdx);	//入力判定（プレス）
	bool GetTrigger(CODE code, int nIdx);	//入力判定（トリガー）

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:
	BYTE m_aKeyState[256];
	BYTE m_aKeyStateTrigger[256];
};

//*****************************************************************************
// ゲームパッドクラス(Xinput)
//*****************************************************************************
class CInputGamepadX : public CInput
{
public:
	//トリガーの左右
	enum class TRIGGER_TYPE {
		RIGHT = 0,
		LEFT,
		ENUM_MAX
	};

	//スティックの上下左右
	enum class STICK_TYPE {
		MOVE_UP = 0,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		ENUM_MAX
	};

	CInputGamepadX();	//デフォルトコンストラクタ
	~CInputGamepadX();	//デストラクタ
	void Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	bool GetPress(CODE code, int nIdx);	//入力判定（プレス）
	bool GetTrigger(CODE code, int nIdx);	//入力判定（トリガー）

	bool GetConnectGamepad(int nIdx);	//ゲームパッド接続の判定
	bool GetButtonPress(int nButton, int nIdx);		//ボタンのプレス判定
	bool GetButtonTrigger(int nButton, int nIdx);		//ボタンのトリガー判定
	bool GetTriggerPress(TRIGGER_TYPE type, int nIdx);		//トリガーのプレス判定
	bool GetTriggerTrigger(TRIGGER_TYPE type, int nIdx);	//トリガーのトリガー判定
	bool GetLeftStick(STICK_TYPE type, int nIdx);			//左スティックの判定
	bool GetRightStick(STICK_TYPE type, int nIdx);			//右スティックの判定
	void SetVibration(int nLeftValue, int nRightValue, int nCntVibration, int nIdx);	//バイブレーションの設定

private:
	XINPUT_STATE m_aState[MAX_PAD_CONNECT_NUM];		//コントローラーの状態
	XINPUT_STATE m_aStateLast[MAX_PAD_CONNECT_NUM];	//コントローラーのひとつ前の状態（トリガー判定用）
	XINPUT_VIBRATION m_aVibrationState[MAX_PAD_CONNECT_NUM];	//バイブレーション
	bool m_abConnect[MAX_PAD_CONNECT_NUM];		//接続確認
	int m_aCntVibration[MAX_PAD_CONNECT_NUM];	//バイブレーション用のカウンター
	bool m_abVibration[MAX_PAD_CONNECT_NUM];	//バイブレーションが実行中かどうか
};

#endif // !_INPUT_H_