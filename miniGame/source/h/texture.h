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
		MESH_CLOUD,					//�_
		MESH_STAGE_02_WALL_02,		//�X�e�[�W�̕�2
		MESH_STAGE_02_WALL_03,		//�X�e�[�W�̕�3
		MESH_STAGE_02_GROUND_STONE,	//�X�e�[�W�̏��Ώ�
		MESH_TOWER_PILLAR,			//�^���[�̒�

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

	static HRESULT Load(void);	//�e�N�X�`���f�[�^�̓ǂݍ���
	static void Unload(void);	//�e�N�X�`���f�[�^�̉��
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE type);	//�e�N�X�`���̎擾
	static char* GetPathName(TEXTURE_TYPE type);				//�e�N�X�`���̃p�X�̕�����̎擾

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[(int)TEXTURE_TYPE::ENUM_MAX];	//�e�N�X�`���ւ̃|�C���^
	static char m_asFilePath[(int)TEXTURE_TYPE::ENUM_MAX][MAX_TEXTURE_FILE_PATH];	// �t�@�C���̃p�X
};

#endif // !_TEXTURE_H_