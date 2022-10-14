//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEXTURE_FILE_PATH (128)	//テクスチャのファイルのパスの長さの最大

//*****************************************************************************
// テクスチャクラス
//*****************************************************************************
class CTexture
{
public:
	enum class TEXTURE_TYPE {
		NONE = 0,

		//UIのテクスチャ
		BG_TITLE,
		TEXT_TITLENAME,
		TEXT_GAMESTART,
		TEXT_TUTORIAL,
		TEXT_CREDIT,
		QUIT_GAME,
		TUTORIAL,
		CREDIT,
		SELECT_ICON,
		COUNT_DOWN_3,
		COUNT_DOWN_2,
		COUNT_DOWN_1,
		COUNT_DOWN_START,
		FINISH,
		
		TIMER_FRAME,

		PAUSE_BG,

		//メッシュのテクスチャ
		MESH_FLOOR_DESERT,		//砂漠
		MESH_STAGE_AUDIENCE,	//観衆
		MESH_BALLOON_GOLD,		//風船金
		MESH_BALLOON_PINK,		//風船ピンク
		MESH_CAR_BLACK,			//黒
		MESH_STAGE_DOOR_WAY,	//ゲート
		MESH_ITEM_BOX,			//アイテム
		MESH_GOLD,				//金
		MESH_CAR_TIRE,			//タイヤ
		MESH_CAR_WHEEL,			//ホイール

		//ナンバーのテクスチャ
		NUMBER_001,
		NUMBER_002,
		NUMBER_003,
		NUMBER_004,
		NUMBER_005,
		NUMBER_006,

		ENUM_MAX
	};

	CTexture();		//デフォルトコンストラクタ
	~CTexture();	//デストラクタ

	static HRESULT Load(void);	//テクスチャデータの読み込み
	static void Unload(void);	//テクスチャデータの解放
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE type);	//テクスチャの取得
	static char* GetPathName(TEXTURE_TYPE type);				//テクスチャのパスの文字列の取得

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[(int)TEXTURE_TYPE::ENUM_MAX];	//テクスチャへのポインタ
	static char m_asFilePath[(int)TEXTURE_TYPE::ENUM_MAX][MAX_TEXTURE_FILE_PATH];	// ファイルのパス
};

#endif // !_TEXTURE_H_