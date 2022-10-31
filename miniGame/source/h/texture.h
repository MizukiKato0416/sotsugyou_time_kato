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
		PLAYER_NUM_1,
		PLAYER_NUM_2,
		PLAYER_NUM_3,
		PLAYER_NUM_4,
		PLAYER_NUM_WHITE_1,
		PLAYER_NUM_WHITE_2,
		PLAYER_NUM_WHITE_3,
		PLAYER_NUM_WHITE_4,
		PLAYER_ICON_FRAME_1,
		PLAYER_ICON_FRAME_2,
		PLAYER_ICON_FRAME_3,
		PLAYER_ICON_FRAME_4,
		PLAYER_ICON_FRAME_1_REVERSE,
		PLAYER_ICON_FRAME_2_REVERSE,
		PLAYER_ICON_FRAME_3_REVERSE,
		PLAYER_ICON_FRAME_4_REVERSE,


		CHECK_BG,

		CHECK_ICON_FRAME_1,
		CHECK_ICON_FRAME_2,
		CHECK_ICON_FRAME_3,
		CHECK_ICON_FRAME_4,
		CHECK_ICON_BUTTON_1,
		CHECK_ICON_BUTTON_2,
		CHECK_ICON_BUTTON_3,
		CHECK_ICON_BUTTON_4,
		CHECK_ICON_OK_1,
		CHECK_ICON_OK_2,
		CHECK_ICON_OK_3,
		CHECK_ICON_OK_4,
		
		SCORE_FRAME_1,
		SCORE_FRAME_2,
		SCORE_FRAME_3,
		SCORE_FRAME_4,

		ITEM_BANANA,
		ITEM_UI_FRAME_1,
		ITEM_UI_FRAME_2,
		ITEM_UI_FRAME_3,
		ITEM_UI_FRAME_4,

		TIMER_FRAME,

		PAUSE_BG,
		PAUSE_FRAME,
		PAUSE_TITLE,
		PAUSE_RESTATE,
		PAUSE_CONTINUE,

		//メッシュのテクスチャ
		MESH_FLOOR_DESERT,			//砂漠
		MESH_STAGE_AUDIENCE,		//観衆
		MESH_BALLOON_GOLD,			//風船金
		MESH_BALLOON_PINK,			//風船ピンク
		MESH_CAR_BLACK,				//黒
		MESH_STAGE_DOOR_WAY,		//ゲート
		MESH_STAGE_WALL,			//ステージの壁
		MESH_ITEM_BOX,				//アイテム
		MESH_GOLD,					//金
		MESH_CAR_TIRE,				//タイヤ
		MESH_CAR_WHEEL,				//ホイール
		MESH_RUBBLE,				//がれき
		MESH_STAGE_02_GROUND,		//ステージの地面
		MESH_STAGE_02_WALL,			//ステージの壁
		MESH_CLOUD,					//雲
		MESH_STAGE_02_WALL_02,		//ステージの壁2
		MESH_STAGE_02_WALL_03,		//ステージの壁3
		MESH_STAGE_02_GROUND_STONE,	//ステージの床石畳
		MESH_TOWER_PILLAR,			//タワーの柱

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