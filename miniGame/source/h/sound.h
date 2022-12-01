//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�N���X
//*****************************************************************************
class CSound
{
public:
	enum class SOUND_LABEL {
		NONE = 0,
		BGM_TITLE,				//�^�C�g��BGM
		BGM_MENU,				//���j���[BGM
		BGM_GAME,				//�Q�[��BGM
		BGM_GAME_02,			//�Q�[��02BGM
		BGM_RESULT,				//���U���gBGM
		BGM_FINAL_RESULT,		//�ŏI���U���gBGM

		SE_POINT_1,				//1�|�C���g�l��SE
		SE_POINT_3,				//3�|�C���g�l��SE
		SE_BALLOON_BREAK,		//���D�������SE
		SE_ITEM_GET,			//�A�C�e���擾SE
		SE_TIME_UP,				//�^�C���A�b�vSE
		SE_PLAYER_SPIN,			//�X�s��SE
		SE_BANANA_THROW,		//�o�i�i�𓊂���SE
		SE_COUNT_DOWN,			//�J�E���g�_�E��SE
		SE_START,				//�X�^�[�gSE
		SE_PLAYER_OK,			//�v���C���[OKSE
		SE_DECIDE,				//����SE
		SE_CANCEL,				//�L�����Z��SE
		SE_PAUSE_OPEN,			//�|�[�Y�J��SE
		SE_CURSOR,				//�J�[�\��SE
		SE_CRASH,				//�Փ�SE
		SE_FALL,				//����SE
		SE_EXPLOSION,			//����SE
		SE_ITEM_SHIELD_GET,		//���A�C�e���l��SE
		SE_BALLOON_SPAWN,		//���D�X�|�[��SE
		SE_DRUM_ROLL,			//�h�������[��SE
		SE_DRUM_ROLL_END,		//�h�������[���Ō�SE
		SE_TITLE_CHAR_CREATE,	//�^�C�g���̕�������SE
		SE_TITLE_LOGO_CREATE,	//�^�C�g�����S�̐���SE
		SE_TITLE_CAR,			//�^�C�g���̎Ԓʉ�SE

		ENUM_MAX
	};

	CSound();	//�f�t�H���g�R���X�g���N�^
	~CSound();	//�f�X�g���N�^
	HRESULT Init(HWND hWnd);	//����������
	void Uninit(void);			//�I������
	HRESULT PlaySound(SOUND_LABEL label);	//���̍Đ�
	void StopSound(SOUND_LABEL label);		//���̒�~
	void StopSound(void);					//���̒�~
	void PauseSound(SOUND_LABEL label);		//���̈ꎞ��~
	void StartSound(SOUND_LABEL label);		//���̍ĊJ

	void SetBGM(SOUND_LABEL label);			//�Đ���BGM�̐ݒ�
	SOUND_LABEL GetBGM(void);				//�Đ���BGM�̎擾
	void ResetBeginPlay(void);	//�Đ��J�n���̃t���O�����ׂă��Z�b�g
	void ControllVoice(const SOUND_LABEL &label, const float &fVolume) { m_apSourceVoice[(int)label]->SetVolume(fVolume); }	//���ʒ���

private:
	// �p�����[�^�\���̒�`
	typedef struct
	{
		char *filename;		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;

	//�����o�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	
	//�����o�ϐ�
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[(int)SOUND_LABEL::ENUM_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[(int)SOUND_LABEL::ENUM_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[(int)SOUND_LABEL::ENUM_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y
	static PARAM m_aParam[(int)SOUND_LABEL::ENUM_MAX];						//�t�@�C�����ƃ��[�v

	SOUND_LABEL m_playBGM;	//�Đ�����BGM
	bool m_abBeginPlay[(int)SOUND_LABEL::ENUM_MAX];	//�P�t���[�����Ƃ̍Đ��J�n�����ǂ����̔���
};

#endif // !_SOUND_H_
