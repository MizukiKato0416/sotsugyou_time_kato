//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "objectMotion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CObject2D;
class CWeapon;
class CInput;

//*****************************************************************************
// プレイヤークラス
//*****************************************************************************
class CPlayer : public CObjectMotion
{
public:
	//モーションの種類
	enum class MOTION_TYPE {
		NEUTRAL = 0,	//ニュートラルモーション
		WALK,		//歩き
		PUNCH,		//パンチ
		STAMP,		//踏みつけ
		RUSH,		//突進
		ENUM_MAX
	};

	//モーションの区分
	enum class MOTION_CATEGORY {
		NONE = 0,	//その他
		MOVE,		//移動
		ATTACK,		//攻撃
		ENUM_MAX
	};	

	//武器の種類
	enum class WEAPONTYPE {
		PUNCH = 0,
		SWORD,
		KATANA,
		ENUM_MAX
	};

	CPlayer();	//デフォルトコンストラクタ
	~CPlayer();	//デストラクタ

	static CPlayer* Create(D3DXVECTOR3 pos);	//生成処理
	static void LoadMotionInfo(void);	//モーション情報をロード
	static void UnloadMotionInfo(void);	//モーション情報をアンロード

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void GameClear(void);	//ゲームクリア時の処理
	void GameOver(void);	//ゲームオーバー時の処理
	void GetCollisionInfo(int nIdxColParts, int* const pNumCol, D3DXVECTOR3** const ppPosColArray, float* const pRadiusCol);	//当たり判定の情報の取得
	D3DXVECTOR3 GetLastPos(void);	//最後の位置座標の取得
	void SetMove(D3DXVECTOR3 move);	//移動量の設定
	D3DXVECTOR3 GetMove(void);		//移動量の取得
	float GetRadius(void);			//当たり判定の半径の取得

private:
	void Move(CInput* pInput, float fRotCameraY);	//移動
	void DecMove(void);	//移動量の減少
	void Collision(D3DXVECTOR3& pos);	//当たり判定
	MOTION_CATEGORY GetMotionCategory(void);	//モーションの区分の取得

	static int m_nNumParts;	//パーツ数
	static PARTS_INFO* m_pPartsInfoArray;	//パーツ情報の配列のポインタ
	static MOTION_INFO m_aMotionInfo[(int)MOTION_TYPE::ENUM_MAX];	//モーション情報

	D3DXVECTOR3	m_lastPos;	//最後の位置座標
	D3DXVECTOR3 m_destRot;	//目標の角度
	D3DXVECTOR3 m_move;		//移動量

	int m_nCntGameover;		//ゲームオーバー後のカウント
};

#endif // !_PLAYER_H_