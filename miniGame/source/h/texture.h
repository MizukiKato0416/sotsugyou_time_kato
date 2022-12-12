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
		BG_RESULT,
		BG_MENU,
		BG_MENU_WOLF,
		BG_FIND_WOLF,

		ARROW_RIGHT,
		ARROW_LEFT,

		TEXT_TITLENAME_BALLOON,
		TEXT_TITLENAME_ATTACK,
		TEXT_TITLENAME_RANDOM,
		TEXT_GAMESTART,
		QUIT_GAME,
		TUTORIAL_BALLOON,
		TUTORIAL_BALLOON_WOLF,
		TUTORIAL_ATTACK,
		TUTORIAL_ATTACK_WOLF,
		TUTORIAL_RANDOM,
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

		RANKING_1,
		RANKING_2,
		RANKING_3,
		RANKING_4,

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
		CHECK_ICON_SELECT,
		CHECK_ICON_SELECT_NOT,
		
		WOLF_SELECT_ICON_1,
		WOLF_SELECT_ICON_2,
		WOLF_SELECT_ICON_3,
		WOLF_SELECT_ICON_4,
		WOLF_POINT_UI_1,
		WOLF_POINT_UI_2,
		WOLF_POINT_UI_3,
		WOLF_POINT_UI_4,
		WOLF_POINT_UI_FREE,

		ADD_POINT_40,
		ADD_POINT_30,
		ADD_POINT_20,
		ADD_POINT_10,

		SCORE_FRAME_1,
		SCORE_FRAME_2,
		SCORE_FRAME_3,
		SCORE_FRAME_4,

		ITEM_BANANA,
		ITEM_GASOLINE,
		ITEM_UI_FRAME_1,
		ITEM_UI_FRAME_2,
		ITEM_UI_FRAME_3,
		ITEM_UI_FRAME_4,

		TIMER_FRAME,

		PAUSE_BG,
		PAUSE_FRAME,
		PAUSE_CONTINUE,
		PAUSE_RESTART,
		PAUSE_MENU,

		WOLF_SHAKE_TUTORIAL,
		WOLF_SHAKE,
		WOLF_SHAKE_START,
		WOLF_ANSWER_1,
		WOLF_ANSWER_2,
		WOLF_ANSWER_3,
		WOLF_ANSWER_4,
		WOLF_FIND_TUTORIAL_1,
		WOLF_FIND_TUTORIAL_2,
		WOLF_FIND_TUTORIAL_3,
		WOLF_FIND_TUTORIAL_4,

		CIRCLE,

		RESULT_UI,
		FINAL_RESULT_UI,

		MENU_GAME_TITLE_FRAME_UI,
		MENU_DECIDE_UI,
		MENU_BACK_UI,
		MENU_MODE_NORMAL,
		MENU_MODE_WOLF,
		MENU_NONE_MOVE_UI,
		MENU_NONE_MOVE_UI_WOLF,

		TITLE_LOGO,
		TITLE_LOGO_CHARACTOR_00,
		TITLE_LOGO_CHARACTOR_01,
		TITLE_LOGO_CHARACTOR_02,
		TITLE_LOGO_CHARACTOR_03,
		TITLE_LOGO_THE_FINAL,
		TITLE_LOGO_EXPLOSION,
		TITLE_LOGO_CAR,

		NOW_LOADING,


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
		MESH_CLOUD,					//くも
		MESH_CLOUD_DOME,			//ドーム用のくも
		MESH_STAGE_02_WALL_02,		//ステージの壁2
		MESH_STAGE_02_WALL_03,		//ステージの壁3
		MESH_STAGE_02_GROUND_STONE,	//ステージの床石畳
		MESH_TOWER_PILLAR,			//タワーの柱
		MESH_ITEM_SHIELD,			//アイテム盾
		MESH_FIND_WOLF_TOWER,		//人狼発見シーンのたわー
		MESH_FIND_WOLF_FACE_OBJ_01,	//人狼発見シーンの顔オブジェクト
		MESH_FIND_WOLF_FACE_OBJ_02,	//人狼発見シーンの顔オブジェクト
		MESH_FIND_WOLF_FACE_OBJ_03,	//人狼発見シーンの顔オブジェクト
		MESH_SHADOW,				//影
		MESH_GRASS,					//草原
		MESH_WOOD,					//年輪
		MESH_CACTUS_00,				//サボテン00
		MESH_CACTUS_01,				//サボテン01
		MESH_CACTUS_02,				//サボテン02

		//エフェクト
		EFFECT_SUN,	//太陽

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

	static HRESULT Load(const char* sLoadType);	//テクスチャデータの読み込み
	static HRESULT AllSceneTextureLoad();	//全シーンで使うテクスチャデータの読み込み
	static void Unload(bool bAllUnload);	//テクスチャデータの解放(引数trueなら全てのテクスチャ破棄falseならALLテクスチャ以外破棄)
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE type);	//テクスチャの取得
	static LPDIRECT3DTEXTURE9 GetTexture(char* texPath);		//テクスチャの取得
	static char* GetPathName(TEXTURE_TYPE type);				//テクスチャのパスの文字列の取得

	//ロードが終了したかどうか
	static bool GetLoadFinish() { return m_bLoadFinish; }

private:
	static HRESULT LoadTex(const char* sLoadType);	//テクスチャデータの読み込み

	static LPDIRECT3DTEXTURE9 m_apTexture[(int)TEXTURE_TYPE::ENUM_MAX];	//テクスチャへのポインタ
	static char m_asFilePath[(int)TEXTURE_TYPE::ENUM_MAX][MAX_TEXTURE_FILE_PATH];	// ファイルのパス
	static bool m_bAllSceneTex[(int)TEXTURE_TYPE::ENUM_MAX];	//前部のシーンで使うテクスチャかどうか

	static void CreateTexture(int nIdx);	//テクスチャの生成

	static bool m_bLoadFinish;		//ロードの終了しているかどうか
};

#endif // !_TEXTURE_H_