//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "sound.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define SOUND_VOLUM			(1.0f)	//�S�̂̃{�����[��

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CSound::PARAM CSound::m_aParam[(int)SOUND_LABEL::ENUM_MAX] = {
	{ "data/SOUND/none.wav", 0 },

	{ "data/SOUND/BGM/title.wav", -1 },
	{ "data/SOUND/BGM/menu.wav", -1 },
	{ "data/SOUND/BGM/game.wav", -1 },
	{ "data/SOUND/BGM/game2.wav", -1 },
	{ "data/SOUND/BGM/game3.wav", -1 },
	{ "data/SOUND/BGM/result.wav", -1 },
	{ "data/SOUND/BGM/find_wolf.wav", -1 },
	{ "data/SOUND/BGM/final_result.wav", -1 },
	{ "data/SOUND/BGM/endroll.wav", -1 },

	{ "data/SOUND/SE/1point.wav", 0 },
	{ "data/SOUND/SE/3point.wav", 0 },
	{ "data/SOUND/SE/point_minus.wav", 0 },
	{ "data/SOUND/SE/point_steal.wav", 0 },
	{ "data/SOUND/SE/balloonbreak.wav", 0 },
	{ "data/SOUND/SE/itemget.wav", 0 },
	{ "data/SOUND/SE/timeup.wav", 0 },
	{ "data/SOUND/SE/slip.wav", 0 },
	{ "data/SOUND/SE/bananathrow.wav", 0 },
	{ "data/SOUND/SE/use_steal_point.wav", 0 },
	{ "data/SOUND/SE/countdown.wav", 0 },
	{ "data/SOUND/SE/start.wav", 0 },
	{ "data/SOUND/SE/player_ok.wav", 0 },
	{ "data/SOUND/SE/decide.wav", 0 },
	{ "data/SOUND/SE/cancel.wav", 0 },
	{ "data/SOUND/SE/pause_open.wav", 0 },
	{ "data/SOUND/SE/cursor.wav", 0 },
	{ "data/SOUND/SE/clash.wav", 0 },
	{ "data/SOUND/SE/fall.wav", 0 },
	{ "data/SOUND/SE/explosion.wav", 0 },
	{ "data/SOUND/SE/shield.wav", 0 },
	{ "data/SOUND/SE/balloonspawn.wav", 0 },
	{ "data/SOUND/SE/drumroll.wav", 0 },
	{ "data/SOUND/SE/drumroll2.wav", 0 },
	{ "data/SOUND/SE/title_chara.wav", 0 },
	{ "data/SOUND/SE/title_logo.wav", 0 },
	{ "data/SOUND/SE/title_car.wav", 0 },
	{ "data/SOUND/SE/game_start.wav", 0 },
	{ "data/SOUND/SE/result_ui.wav", 0 },
	{ "data/SOUND/SE/crown.wav", 0 }
};

//=============================================================================
// �T�E���h�̃f�t�H���g�R���X�g���N�^
//=============================================================================
CSound::CSound()
{
	m_playBGM = CSound::SOUND_LABEL::NONE;
}

//=============================================================================
// �T�E���h�̃f�X�g���N�^
//=============================================================================
CSound::~CSound()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSound::Init(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr))
	{
		// COM���C�u�����̏I������
		CoUninitialize();
		return E_FAIL;
	}

	// �}�X�^�[�{�C�X�̐���
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr))
	{
		if (m_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_pXAudio2->Release();
		}

		// COM���C�u�����̏I������
		CoUninitialize();
		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for (int nCntSound = 0; nCntSound < (int)SOUND_LABEL::ENUM_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD filetype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(m_aParam[nCntSound].filename, GENERIC_READ,
			FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		if (filetype != 'EVAW')
		{
			return S_FALSE;
		}

		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}

		m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));

		// �o�b�t�@�̐ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_aParam[nCntSound].nCntLoop;

		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}

	//���ʒ���
	SetDefaultVolum(SOUND_LABEL::BGM_TITLE				, 1.0f * SOUND_VOLUM);		//�^�C�g��BGM
	SetDefaultVolum(SOUND_LABEL::BGM_MENU				, 1.0f * SOUND_VOLUM);		//���j���[BGM
	SetDefaultVolum(SOUND_LABEL::BGM_GAME				, 1.0f * SOUND_VOLUM);		//�Q�[��BGM
	SetDefaultVolum(SOUND_LABEL::BGM_GAME_02			, 0.8f * SOUND_VOLUM);		//�Q�[��02BGM
	SetDefaultVolum(SOUND_LABEL::BGM_GAME_03			, 1.2f * SOUND_VOLUM);		//�Q�[��03BGM
	SetDefaultVolum(SOUND_LABEL::BGM_RESULT				, 1.5f * SOUND_VOLUM);		//���U���gBGM
	SetDefaultVolum(SOUND_LABEL::BGM_FIND_WOLF			, 1.6f * SOUND_VOLUM);		//�l�T����BGM
	SetDefaultVolum(SOUND_LABEL::BGM_FINAL_RESULT		, 0.8f * SOUND_VOLUM);		//�ŏI���U���gBGM
	SetDefaultVolum(SOUND_LABEL::BGM_CREDIT				, 2.3f * SOUND_VOLUM);		//����ǂ�[��

	SetDefaultVolum(SOUND_LABEL::SE_POINT_1				, 1.8f * SOUND_VOLUM);		//1�|�C���g�l��SE
	SetDefaultVolum(SOUND_LABEL::SE_POINT_3				, 1.4f * SOUND_VOLUM);		//3�|�C���g�l��SE
	SetDefaultVolum(SOUND_LABEL::SE_POINT_MINUS			, 2.4f * SOUND_VOLUM);		//�|�C���g���_SE
	SetDefaultVolum(SOUND_LABEL::SE_POINT_STEAL			, 3.9f * SOUND_VOLUM);		//�|�C���g�D��
	SetDefaultVolum(SOUND_LABEL::SE_BALLOON_BREAK		, 0.4f * SOUND_VOLUM);		//���D�������SE
	SetDefaultVolum(SOUND_LABEL::SE_ITEM_GET			, 1.3f * SOUND_VOLUM);		//�A�C�e���擾SE
	SetDefaultVolum(SOUND_LABEL::SE_TIME_UP				, 1.0f * SOUND_VOLUM);		//�^�C���A�b�vSE
	SetDefaultVolum(SOUND_LABEL::SE_PLAYER_SPIN			, 0.7f * SOUND_VOLUM);		//�X�s��SE
	SetDefaultVolum(SOUND_LABEL::SE_BANANA_THROW		, 1.6f * SOUND_VOLUM);		//�o�i�i�𓊂���SE
	SetDefaultVolum(SOUND_LABEL::SE_USE_POINT_STEAL		, 1.0f * SOUND_VOLUM);		//�|�C���g�D��g�pSE
	SetDefaultVolum(SOUND_LABEL::SE_COUNT_DOWN			, 1.2f * SOUND_VOLUM);		//�J�E���g�_�E��SE
	SetDefaultVolum(SOUND_LABEL::SE_START				, 0.5f * SOUND_VOLUM);		//�X�^�[�gSE
	SetDefaultVolum(SOUND_LABEL::SE_TIME_UP				, 0.8f * SOUND_VOLUM);		//�^�C���A�b�vSE
	SetDefaultVolum(SOUND_LABEL::SE_PLAYER_OK			, 1.0f * SOUND_VOLUM);		//�v���C���[OKSE
	SetDefaultVolum(SOUND_LABEL::SE_DECIDE				, 1.7f * SOUND_VOLUM);		//����SE
	SetDefaultVolum(SOUND_LABEL::SE_CANCEL				, 1.7f * SOUND_VOLUM);		//�L�����Z��SE
	SetDefaultVolum(SOUND_LABEL::SE_PAUSE_OPEN			, 1.6f * SOUND_VOLUM);		//�|�[�Y�J��SE
	SetDefaultVolum(SOUND_LABEL::SE_CURSOR				, 8.0f * SOUND_VOLUM);		//�J�[�\��SE
	SetDefaultVolum(SOUND_LABEL::SE_CRASH				, 4.0f * SOUND_VOLUM);		//�Փ�SE
	SetDefaultVolum(SOUND_LABEL::SE_FALL				, 1.5f * SOUND_VOLUM);		//����SE
	SetDefaultVolum(SOUND_LABEL::SE_EXPLOSION			, 1.4f * SOUND_VOLUM);		//����SE
	SetDefaultVolum(SOUND_LABEL::SE_ITEM_SHIELD_GET		, 1.2f * SOUND_VOLUM);		//���A�C�e���l��SE
	SetDefaultVolum(SOUND_LABEL::SE_BALLOON_SPAWN		, 1.0f * SOUND_VOLUM);		//���D�X�|�[��SE
	SetDefaultVolum(SOUND_LABEL::SE_DRUM_ROLL			, 2.9f * SOUND_VOLUM);		//�h�������[��SE
	SetDefaultVolum(SOUND_LABEL::SE_DRUM_ROLL_END		, 2.7f * SOUND_VOLUM);		//�h�������[���Ō�SE
	SetDefaultVolum(SOUND_LABEL::SE_TITLE_CHAR_CREATE	, 1.5f * SOUND_VOLUM);		//�^�C�g���̕�������SE
	SetDefaultVolum(SOUND_LABEL::SE_TITLE_LOGO_CREATE	, 2.2f * SOUND_VOLUM);		//�^�C�g�����S�̐���SE
	SetDefaultVolum(SOUND_LABEL::SE_TITLE_CAR			, 3.0f * SOUND_VOLUM);		//�^�C�g���̎�SE
	SetDefaultVolum(SOUND_LABEL::SE_ENGINE				, 2.0f * SOUND_VOLUM);		//�Ԃ̃G���W��SE
	SetDefaultVolum(SOUND_LABEL::SE_RESULT_UI			, 5.0f * SOUND_VOLUM);		//���ʔ��\SE
	SetDefaultVolum(SOUND_LABEL::SE_CROWN				, 2.0f * SOUND_VOLUM);		//����SE

	for (int nCntSound = 0; nCntSound < static_cast<int>(SOUND_LABEL::ENUM_MAX); nCntSound++)
	{
		ControllVoice(static_cast<SOUND_LABEL>(nCntSound), m_fDefaultVolum[nCntSound]);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSound::Uninit(void)
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < (int)SOUND_LABEL::ENUM_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);

			// �\�[�X�{�C�X�̔j��
			m_apSourceVoice[nCntSound]->DestroyVoice();

			// �I�[�f�B�I�f�[�^�̊J��
			free(m_apDataAudio[nCntSound]);
		}
	}

	// �}�X�^�[�{�C�X�̔j��
	m_pMasteringVoice->DestroyVoice();

	if (m_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
	}

	// COM���C�u�����̏I������
	CoUninitialize();
}

//=============================================================================
// �Z�O�����g�Đ�(��~)
//=============================================================================
HRESULT CSound::PlaySound(SOUND_LABEL label)
{
	//���t���[�����ɂ��łɍĐ�����Ă���ꍇ�I���i�����ɕ����̉������ʂɗ����ƃG���[���N���邽�߁j
	if (m_abBeginPlay[(int)label]) return S_OK;

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER       buffer;

	// �o�b�t�@�̐ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[(int)label];
	buffer.pAudioData = m_apDataAudio[(int)label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aParam[(int)label].nCntLoop;

	// ��Ԏ擾
	m_apSourceVoice[(int)label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[(int)label]->Stop(0);

		// �N���A
		m_apSourceVoice[(int)label]->FlushSourceBuffers();
	}

	// �o�^
	m_apSourceVoice[(int)label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_apSourceVoice[(int)label]->Start(0);

	//�Đ��J�n���̃t���O��ݒ�
	m_abBeginPlay[(int)label] = true;

	return S_OK;
}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void CSound::StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	m_apSourceVoice[(int)label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[(int)label]->Stop(0);

		// �N���A
		m_apSourceVoice[(int)label]->FlushSourceBuffers();
	}
}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void CSound::StopSound(void)
{
	for (int nCntSound = 0; nCntSound < (int)SOUND_LABEL::ENUM_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);

			// �N���A
			m_apSourceVoice[nCntSound]->FlushSourceBuffers();
		}
	}
}

//=============================================================================
// ���̈ꎞ��~
//=============================================================================
void CSound::PauseSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	m_apSourceVoice[(int)label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
	 // �ꎞ��~
		m_apSourceVoice[(int)label]->Stop(0);
	}
}

//=============================================================================
// ���̍ĊJ
//=============================================================================
void CSound::StartSound(SOUND_LABEL label)
{
	m_apSourceVoice[(int)label]->Start(0);
}

//=============================================================================
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

//=============================================================================
//�Đ���BGM�̐ݒ�
//=============================================================================
void CSound::SetBGM(SOUND_LABEL label) {
	m_playBGM = label;
}

//=============================================================================
//�Đ���BGM�̎擾
//=============================================================================
CSound::SOUND_LABEL CSound::GetBGM(void) {
	return m_playBGM;
}

//=============================================================================
// �Đ��J�n���̃t���O�����ׂă��Z�b�g
//=============================================================================
void CSound::ResetBeginPlay(void) {
	for (int nCnt = 0; nCnt < (int)SOUND_LABEL::ENUM_MAX; nCnt++)
	{
		m_abBeginPlay[nCnt] = false;
	}
}