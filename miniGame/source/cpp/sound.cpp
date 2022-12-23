//=============================================================================
//
// サウンド処理 [sound.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "sound.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define SOUND_VOLUM			(1.0f)	//全体のボリューム

//=============================================================================
//静的メンバ変数宣言
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
// サウンドのデフォルトコンストラクタ
//=============================================================================
CSound::CSound()
{
	m_playBGM = CSound::SOUND_LABEL::NONE;
}

//=============================================================================
// サウンドのデストラクタ
//=============================================================================
CSound::~CSound()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSound::Init(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr))
	{
		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}

	// マスターボイスの生成
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr))
	{
		if (m_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
		}

		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < (int)SOUND_LABEL::ENUM_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD filetype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
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

		// WAVEファイルのチェック
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

		// フォーマットチェック
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

		// オーディオデータ読み込み
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

		// バッファの設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_aParam[nCntSound].nCntLoop;

		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// ファイルをクローズ
		CloseHandle(hFile);
	}

	//音量調整
	SetDefaultVolum(SOUND_LABEL::BGM_TITLE				, 1.0f * SOUND_VOLUM);		//タイトルBGM
	SetDefaultVolum(SOUND_LABEL::BGM_MENU				, 1.0f * SOUND_VOLUM);		//メニューBGM
	SetDefaultVolum(SOUND_LABEL::BGM_GAME				, 1.0f * SOUND_VOLUM);		//ゲームBGM
	SetDefaultVolum(SOUND_LABEL::BGM_GAME_02			, 0.8f * SOUND_VOLUM);		//ゲーム02BGM
	SetDefaultVolum(SOUND_LABEL::BGM_GAME_03			, 1.2f * SOUND_VOLUM);		//ゲーム03BGM
	SetDefaultVolum(SOUND_LABEL::BGM_RESULT				, 1.5f * SOUND_VOLUM);		//リザルトBGM
	SetDefaultVolum(SOUND_LABEL::BGM_FIND_WOLF			, 1.6f * SOUND_VOLUM);		//人狼発見BGM
	SetDefaultVolum(SOUND_LABEL::BGM_FINAL_RESULT		, 0.8f * SOUND_VOLUM);		//最終リザルトBGM
	SetDefaultVolum(SOUND_LABEL::BGM_CREDIT				, 2.3f * SOUND_VOLUM);		//えんどろーる

	SetDefaultVolum(SOUND_LABEL::SE_POINT_1				, 1.8f * SOUND_VOLUM);		//1ポイント獲得SE
	SetDefaultVolum(SOUND_LABEL::SE_POINT_3				, 1.4f * SOUND_VOLUM);		//3ポイント獲得SE
	SetDefaultVolum(SOUND_LABEL::SE_POINT_MINUS			, 2.4f * SOUND_VOLUM);		//ポイント失点SE
	SetDefaultVolum(SOUND_LABEL::SE_POINT_STEAL			, 3.9f * SOUND_VOLUM);		//ポイント奪取
	SetDefaultVolum(SOUND_LABEL::SE_BALLOON_BREAK		, 0.4f * SOUND_VOLUM);		//風船が割れるSE
	SetDefaultVolum(SOUND_LABEL::SE_ITEM_GET			, 1.3f * SOUND_VOLUM);		//アイテム取得SE
	SetDefaultVolum(SOUND_LABEL::SE_TIME_UP				, 1.0f * SOUND_VOLUM);		//タイムアップSE
	SetDefaultVolum(SOUND_LABEL::SE_PLAYER_SPIN			, 0.7f * SOUND_VOLUM);		//スピンSE
	SetDefaultVolum(SOUND_LABEL::SE_BANANA_THROW		, 1.6f * SOUND_VOLUM);		//バナナを投げるSE
	SetDefaultVolum(SOUND_LABEL::SE_USE_POINT_STEAL		, 1.0f * SOUND_VOLUM);		//ポイント奪取使用SE
	SetDefaultVolum(SOUND_LABEL::SE_COUNT_DOWN			, 1.2f * SOUND_VOLUM);		//カウントダウンSE
	SetDefaultVolum(SOUND_LABEL::SE_START				, 0.5f * SOUND_VOLUM);		//スタートSE
	SetDefaultVolum(SOUND_LABEL::SE_TIME_UP				, 0.8f * SOUND_VOLUM);		//タイムアップSE
	SetDefaultVolum(SOUND_LABEL::SE_PLAYER_OK			, 1.0f * SOUND_VOLUM);		//プレイヤーOKSE
	SetDefaultVolum(SOUND_LABEL::SE_DECIDE				, 1.7f * SOUND_VOLUM);		//決定SE
	SetDefaultVolum(SOUND_LABEL::SE_CANCEL				, 1.7f * SOUND_VOLUM);		//キャンセルSE
	SetDefaultVolum(SOUND_LABEL::SE_PAUSE_OPEN			, 1.6f * SOUND_VOLUM);		//ポーズ開くSE
	SetDefaultVolum(SOUND_LABEL::SE_CURSOR				, 8.0f * SOUND_VOLUM);		//カーソルSE
	SetDefaultVolum(SOUND_LABEL::SE_CRASH				, 4.0f * SOUND_VOLUM);		//衝突SE
	SetDefaultVolum(SOUND_LABEL::SE_FALL				, 1.5f * SOUND_VOLUM);		//落下SE
	SetDefaultVolum(SOUND_LABEL::SE_EXPLOSION			, 1.4f * SOUND_VOLUM);		//爆発SE
	SetDefaultVolum(SOUND_LABEL::SE_ITEM_SHIELD_GET		, 1.2f * SOUND_VOLUM);		//盾アイテム獲得SE
	SetDefaultVolum(SOUND_LABEL::SE_BALLOON_SPAWN		, 1.0f * SOUND_VOLUM);		//風船スポーンSE
	SetDefaultVolum(SOUND_LABEL::SE_DRUM_ROLL			, 2.9f * SOUND_VOLUM);		//ドラムロールSE
	SetDefaultVolum(SOUND_LABEL::SE_DRUM_ROLL_END		, 2.7f * SOUND_VOLUM);		//ドラムロール最後SE
	SetDefaultVolum(SOUND_LABEL::SE_TITLE_CHAR_CREATE	, 1.5f * SOUND_VOLUM);		//タイトルの文字生成SE
	SetDefaultVolum(SOUND_LABEL::SE_TITLE_LOGO_CREATE	, 2.2f * SOUND_VOLUM);		//タイトルロゴの生成SE
	SetDefaultVolum(SOUND_LABEL::SE_TITLE_CAR			, 3.0f * SOUND_VOLUM);		//タイトルの車SE
	SetDefaultVolum(SOUND_LABEL::SE_ENGINE				, 2.0f * SOUND_VOLUM);		//車のエンジンSE
	SetDefaultVolum(SOUND_LABEL::SE_RESULT_UI			, 5.0f * SOUND_VOLUM);		//結果発表SE
	SetDefaultVolum(SOUND_LABEL::SE_CROWN				, 2.0f * SOUND_VOLUM);		//王冠SE

	for (int nCntSound = 0; nCntSound < static_cast<int>(SOUND_LABEL::ENUM_MAX); nCntSound++)
	{
		ControllVoice(static_cast<SOUND_LABEL>(nCntSound), m_fDefaultVolum[nCntSound]);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSound::Uninit(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < (int)SOUND_LABEL::ENUM_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);

			// ソースボイスの破棄
			m_apSourceVoice[nCntSound]->DestroyVoice();

			// オーディオデータの開放
			free(m_apDataAudio[nCntSound]);
		}
	}

	// マスターボイスの破棄
	m_pMasteringVoice->DestroyVoice();

	if (m_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
	}

	// COMライブラリの終了処理
	CoUninitialize();
}

//=============================================================================
// セグメント再生(停止)
//=============================================================================
HRESULT CSound::PlaySound(SOUND_LABEL label)
{
	//同フレーム中にすでに再生されている場合終了（同時に複数の音声を大量に流すとエラーが起きるため）
	if (m_abBeginPlay[(int)label]) return S_OK;

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER       buffer;

	// バッファの設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[(int)label];
	buffer.pAudioData = m_apDataAudio[(int)label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aParam[(int)label].nCntLoop;

	// 状態取得
	m_apSourceVoice[(int)label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_apSourceVoice[(int)label]->Stop(0);

		// クリア
		m_apSourceVoice[(int)label]->FlushSourceBuffers();
	}

	// 登録
	m_apSourceVoice[(int)label]->SubmitSourceBuffer(&buffer);

	// 再生
	m_apSourceVoice[(int)label]->Start(0);

	//再生開始時のフラグを設定
	m_abBeginPlay[(int)label] = true;

	return S_OK;
}

//=============================================================================
// セグメント停止
//=============================================================================
void CSound::StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	m_apSourceVoice[(int)label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_apSourceVoice[(int)label]->Stop(0);

		// クリア
		m_apSourceVoice[(int)label]->FlushSourceBuffers();
	}
}

//=============================================================================
// セグメント停止
//=============================================================================
void CSound::StopSound(void)
{
	for (int nCntSound = 0; nCntSound < (int)SOUND_LABEL::ENUM_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);

			// クリア
			m_apSourceVoice[nCntSound]->FlushSourceBuffers();
		}
	}
}

//=============================================================================
// 音の一時停止
//=============================================================================
void CSound::PauseSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	m_apSourceVoice[(int)label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 // 一時停止
		m_apSourceVoice[(int)label]->Stop(0);
	}
}

//=============================================================================
// 音の再開
//=============================================================================
void CSound::StartSound(SOUND_LABEL label)
{
	m_apSourceVoice[(int)label]->Start(0);
}

//=============================================================================
// チャンクのチェック
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
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
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
// チャンクデータの読み込み
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

//=============================================================================
//再生中BGMの設定
//=============================================================================
void CSound::SetBGM(SOUND_LABEL label) {
	m_playBGM = label;
}

//=============================================================================
//再生中BGMの取得
//=============================================================================
CSound::SOUND_LABEL CSound::GetBGM(void) {
	return m_playBGM;
}

//=============================================================================
// 再生開始時のフラグをすべてリセット
//=============================================================================
void CSound::ResetBeginPlay(void) {
	for (int nCnt = 0; nCnt < (int)SOUND_LABEL::ENUM_MAX; nCnt++)
	{
		m_abBeginPlay[nCnt] = false;
	}
}