//================================================
//�T�E���h����
//Authore:��������
//================================================
#include "sound.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
CSound::PARAM CSound::m_aParam[(int)SOUND_LABEL::MAX] =
{
	{ "data/SOUND/SE/Airplane.wav", 0 },		//��s�@SE
	{ "data/SOUND/SE/banana.wav", 0 },			//�o�i�iSE
	{ "data/SOUND/SE/cancel.wav", 0 },			//�߂��SE
	{ "data/SOUND/SE/pause.wav", 0 },			//�|�[�YSE
	{ "data/SOUND/SE/enter.wav", 0 },			//����SE
	{ "data/SOUND/SE/fan.wav", 0 },				//��@SE
	{ "data/SOUND/SE/gage.wav", -1 },			//�Q�[�WSE
	{ "data/SOUND/SE/goal.wav", 0 },			//�S�[��SE
	{ "data/SOUND/SE/redbull.wav", 0 },			//���b�h�u��SE
	{ "data/SOUND/SE/rocket.wav", 0 },			//���P�b�gSE
	{ "data/SOUND/SE/star.wav", 0 },			//starringSE
	{ "data/SOUND/SE/thorn.wav", 0 },			//�Ƃ�SE
	{ "data/SOUND/SE/trampoline.wav", 0 },		//�g�����|����SE
	{ "data/SOUND/SE/break.wav", 0 },			//�u���[�LSE
	{ "data/SOUND/SE/Jump.wav", 0 },			//�W�����vSE
	{ "data/SOUND/SE/bad.wav", 0 },				//badSE
	{ "data/SOUND/SE/good.wav", 0 },			//goodSE
	{ "data/SOUND/SE/great.wav", 0 },			//greatSE
	{ "data/SOUND/SE/perfect.wav", 0 },			//parfectSE
	{ "data/SOUND/SE/error.wav", -1 },			//�G���[SE
	{ "data/SOUND/SE/kiyo_break.wav", 0 },		//�L���@�u���[�L
	{ "data/SOUND/SE/angry.wav", 0 },			//�N������
	{ "data/SOUND/SE/dialog.wav", 0 },			//�_�C�A���O
	{ "data/SOUND/BGM/endroll.wav", -1 },		//�G���h���[��BGM
	{ "data/SOUND/BGM/result.wav", -1 },		//���U���gBGM
	{ "data/SOUND/BGM/game.wav", -1 },			//�Q�[��BGM
	{ "data/SOUND/BGM/title.wav", -1 },			//�^�C�g��BGM
	{ "data/SOUND/BGM/trophy.wav", -1 },		//�g���t�B�[BGM
};

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CSound::CSound()
{
	
}

//================================================
//�f�X�g���N�^
//================================================
CSound::~CSound()
{

}

//================================================
//����������
//================================================
HRESULT CSound::Init(void)
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
	for (int nCntSound = 0; nCntSound < (int)SOUND_LABEL::MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunksize = 0;
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
		hr = CheckChunk(hFile, 'FFIR', &dwChunksize, &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		hr = ReadChunk(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		if (filetype != 'EVAW')
		{
			return S_FALSE;
		}

		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunksize, &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		hr = ReadChunk(hFile, &wfx, dwChunksize, dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &m_asizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_asizeAudio[nCntSound]);
		hr = ReadChunk(hFile, m_apDataAudio[nCntSound], m_asizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}

		m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));

		// �o�b�t�@�̐ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_asizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_aParam[nCntSound].nCntLoop;

		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}

	return S_OK;
}

//================================================
//�I������
//================================================
void CSound::Uninit(void)
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < (int)SOUND_LABEL::MAX; nCntSound++)
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
HRESULT CSound::Play(const SOUND_LABEL &label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER       buffer;

	// �o�b�t�@�̐ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_asizeAudio[(int)label];
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

	return S_OK;
}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void CSound::Stop(const SOUND_LABEL &label)
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
void CSound::Stop(void)
{
	for (int nCntSound = 0; nCntSound < (int)SOUND_LABEL::MAX; nCntSound++)
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
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunksize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDatasize;
	DWORD dwRIFFDatasize = 0;
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

		if (ReadFile(hFile, &dwChunkDatasize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDatasize = dwChunkDatasize;
			dwChunkDatasize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDatasize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunksize = dwChunkDatasize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDatasize;
		if (dwBytesRead >= dwRIFFDatasize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT CSound::ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
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