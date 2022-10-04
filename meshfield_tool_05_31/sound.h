//===========================================
//�T�E���h����
//Authore:��������
//===========================================
#ifndef _SOUND_H_
#define _SOUND_H_
#include "main.h"
#include <thread>

//================================================
//�}�N����`
//================================================

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CSound
{
public:
	CSound();				//�R���X�g���N�^
	~CSound();				//�f�X�g���N�^

	//�T�E���h�t�@�C��
	enum class SOUND_LABEL
	{
		AIRPLANE_SE = 0,		//��s�@SE
		BANANA_SE,				//�o�i�iSE
		CANSEL_SE,				//�߂��SE
		PAUSE_BUTTON_SE,		//�|�[�YSE
		DECISION_SE,			//����SE
		FAN_SE,					//��@SE
		GAGE_SE,				//�Q�[�WSE
		GOAL_SE,				//�S�[��SE
		REDBULL_SE,				//���b�h�u��SE
		ROCKET_SE,				//���P�b�gSE
		STAR_RING_SE,			//starringSE
		THORN_SE,				//�Ƃ�SE
		TRAMPOLINE_SE,			//�g�����|����SE
		BREAK_SE,				//�u���[�LSE
		JUMP_SE,				//�W�����vSE
		BAD_SE,					//badSE
		GOOD_SE,				//goodSE
		GREAT_SE,				//greatSE
		PARFECT_SE,				//parfectSE
		ERROR_SE,				//�G���[
		KIYO_BREAK_SE,			//�L���@�u���[�L
		ANGRY_SE,				//�N�������Ƃ�
		DIALOG_SE,				//�_�C�A���O
		ENDROOL_BGM,			//�G���h���[��BGM
		RESULT_BGM,				//���U���gBGM
		GAME_BGM,				//�Q�[��BGM
		TITLE_BGM,				//�^�C�g��BGM
		TROPHY_BGM,				//�g���t�B�[BGM
		MAX,
	};

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	HRESULT Play(const SOUND_LABEL &label);
	void Stop(const SOUND_LABEL &label);
	void Stop(void);
	void ControllVoice(const SOUND_LABEL &label, const float &fVolume) { m_apSourceVoice[(int)label]->SetVolume(fVolume); }	//���ʒ���

private:
	//�p�����[�^�[�\����
	typedef struct
	{
		char *filename;		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;

	//�����o�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunksize, DWORD *pChunkDataPosition);
	HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;										// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;					// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[(int)SOUND_LABEL::MAX] = {};			// �\�[�X�{�C�X
	BYTE *m_apDataAudio[(int)SOUND_LABEL::MAX] = {};							// �I�[�f�B�I�f�[�^
	DWORD m_asizeAudio[(int)SOUND_LABEL::MAX] = {};							// �I�[�f�B�I�f�[�^�T�C�Y

	static PARAM m_aParam[(int)SOUND_LABEL::MAX];								// �e���f�ނ̃p�����[�^
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_SOUND_H_