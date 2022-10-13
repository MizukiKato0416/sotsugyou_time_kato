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
		
		TIMER_FRAME,

		PAUSE_BG,

		//���b�V���̃e�N�X�`��
		MESH_FLOOR_DESERT,		//����
		MESH_STAGE_AUDIENCE,	//�ϏO
		MESH_BALLOON_GOLD,		//���D��
		MESH_BALLOON_PINK,		//���D�s���N
		MESH_CAR_BLACK,			//��
		MESH_STAGE_DOOR_WAY,	//�Q�[�g
		MESH_ITEM_BOX,			//�A�C�e��
		MESH_GOLD,				//��
		MESH_CAR_TIRE,			//�^�C��
		MESH_CAR_WHEEL,			//�z�C�[��

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