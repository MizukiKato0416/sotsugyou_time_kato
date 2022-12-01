//=============================================================================
//
// プレイヤーのアイコン処理 [player_icon.h]
// Author : 加藤瑞葵
//
//=============================================================================
#ifndef _PLAYER_ICON_H_
#define _PLAYER_ICON_H_

#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CObjectPlayerIcon : public CObject
{
public:
	enum class STATE
	{
		ADD_ALPHA = 0,	//α値加算
		NONE,			//何もしない
		DEC_ALPHA,		//α値減算
		MAX
	};

	CObjectPlayerIcon();		//デフォルトコンストラクタ
	~CObjectPlayerIcon();	//デストラクタ
	static CObjectPlayerIcon* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale,
		                       const CTexture::TEXTURE_TYPE texTypeFrame, const CTexture::TEXTURE_TYPE texTypePlayerNum);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void) {}	//描画処理

	//状態取得処理
	STATE GetState(void) { return m_state; }
	//状態設定処理
	void SetState(STATE state) { m_state = state; }

	//フレームのポインタ取得処理
	CObject2D *GetFrame(void) { return m_pFrame; }
	//プレイヤー番号のポインタ取得処理
	CObject2D *GetPlayerNum(void) { return m_pPlayerNum; }

private:
	void StateAddAlpha();		//α値加算処理
	void StateNone();			//何もしない処理
	void StateDecAlpha();		//α値減算処理

	D3DXVECTOR3 m_scale;							//スケール
	D3DXVECTOR3 m_pos;								//位置
	STATE m_state;									//状態

	CTexture::TEXTURE_TYPE m_texTypeFrame;			//フレームのテクスチャ
	CObject2D *m_pFrame;							//フレームのポインタ

	CTexture::TEXTURE_TYPE m_texTypePlayerNum;		//プレイヤー番号のテクスチャ
	CObject2D *m_pPlayerNum;						//プレイヤー番号のポインタ

};

#endif // !_PLAYER_ICON_H_