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
class CPlayerIcon : public CObject
{
public:
	CPlayerIcon();		//デフォルトコンストラクタ
	~CPlayerIcon();	//デストラクタ
	static CPlayerIcon* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale,
		                       const CTexture::TEXTURE_TYPE texTypeFrame, const CTexture::TEXTURE_TYPE texTypePlayerNum);	//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void) {}	//描画処理

private:
	D3DXVECTOR3 m_scale;								//スケール
	CTexture::TEXTURE_TYPE m_texTypeFrame;				//フレームのテクスチャ
	CTexture::TEXTURE_TYPE m_texTypePlayerNum;			//プレイヤー番号のテクスチャ
};

#endif // !_PLAYER_ICON_H_