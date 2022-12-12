//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXTURE_FILE_PATH (128)	//�e�N�X�`���̃t�@�C���̃p�X�̒����̍ő�

//*****************************************************************************
// �e�N�X�`���N���X
//*****************************************************************************
class CTexture
{
public:
	enum class TEXTURE_TYPE {
		NONE = 0,

		//UI�̃e�N�X�`��
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


		//���b�V���̃e�N�X�`��
		MESH_FLOOR_DESERT,			//����
		MESH_STAGE_AUDIENCE,		//�ϏO
		MESH_BALLOON_GOLD,			//���D��
		MESH_BALLOON_PINK,			//���D�s���N
		MESH_CAR_BLACK,				//��
		MESH_STAGE_DOOR_WAY,		//�Q�[�g
		MESH_STAGE_WALL,			//�X�e�[�W�̕�
		MESH_ITEM_BOX,				//�A�C�e��
		MESH_GOLD,					//��
		MESH_CAR_TIRE,				//�^�C��
		MESH_CAR_WHEEL,				//�z�C�[��
		MESH_RUBBLE,				//���ꂫ
		MESH_STAGE_02_GROUND,		//�X�e�[�W�̒n��
		MESH_STAGE_02_WALL,			//�X�e�[�W�̕�
		MESH_CLOUD,					//����
		MESH_CLOUD_DOME,			//�h�[���p�̂���
		MESH_STAGE_02_WALL_02,		//�X�e�[�W�̕�2
		MESH_STAGE_02_WALL_03,		//�X�e�[�W�̕�3
		MESH_STAGE_02_GROUND_STONE,	//�X�e�[�W�̏��Ώ�
		MESH_TOWER_PILLAR,			//�^���[�̒�
		MESH_ITEM_SHIELD,			//�A�C�e����
		MESH_FIND_WOLF_TOWER,		//�l�T�����V�[���̂���[
		MESH_FIND_WOLF_FACE_OBJ_01,	//�l�T�����V�[���̊�I�u�W�F�N�g
		MESH_FIND_WOLF_FACE_OBJ_02,	//�l�T�����V�[���̊�I�u�W�F�N�g
		MESH_FIND_WOLF_FACE_OBJ_03,	//�l�T�����V�[���̊�I�u�W�F�N�g
		MESH_SHADOW,				//�e
		MESH_GRASS,					//����
		MESH_WOOD,					//�N��
		MESH_CACTUS_00,				//�T�{�e��00
		MESH_CACTUS_01,				//�T�{�e��01
		MESH_CACTUS_02,				//�T�{�e��02

		//�G�t�F�N�g
		EFFECT_SUN,	//���z

		//�i���o�[�̃e�N�X�`��
		NUMBER_001,
		NUMBER_002,
		NUMBER_003,
		NUMBER_004,
		NUMBER_005,
		NUMBER_006,

		ENUM_MAX
	};

	CTexture();		//�f�t�H���g�R���X�g���N�^
	~CTexture();	//�f�X�g���N�^

	static HRESULT Load(const char* sLoadType);	//�e�N�X�`���f�[�^�̓ǂݍ���
	static HRESULT AllSceneTextureLoad();	//�S�V�[���Ŏg���e�N�X�`���f�[�^�̓ǂݍ���
	static void Unload(bool bAllUnload);	//�e�N�X�`���f�[�^�̉��(����true�Ȃ�S�Ẵe�N�X�`���j��false�Ȃ�ALL�e�N�X�`���ȊO�j��)
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE type);	//�e�N�X�`���̎擾
	static LPDIRECT3DTEXTURE9 GetTexture(char* texPath);		//�e�N�X�`���̎擾
	static char* GetPathName(TEXTURE_TYPE type);				//�e�N�X�`���̃p�X�̕�����̎擾

	//���[�h���I���������ǂ���
	static bool GetLoadFinish() { return m_bLoadFinish; }

private:
	static HRESULT LoadTex(const char* sLoadType);	//�e�N�X�`���f�[�^�̓ǂݍ���

	static LPDIRECT3DTEXTURE9 m_apTexture[(int)TEXTURE_TYPE::ENUM_MAX];	//�e�N�X�`���ւ̃|�C���^
	static char m_asFilePath[(int)TEXTURE_TYPE::ENUM_MAX][MAX_TEXTURE_FILE_PATH];	// �t�@�C���̃p�X
	static bool m_bAllSceneTex[(int)TEXTURE_TYPE::ENUM_MAX];	//�O���̃V�[���Ŏg���e�N�X�`�����ǂ���

	static void CreateTexture(int nIdx);	//�e�N�X�`���̐���

	static bool m_bLoadFinish;		//���[�h�̏I�����Ă��邩�ǂ���
};

#endif // !_TEXTURE_H_