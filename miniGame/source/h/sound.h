//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドクラス
//*****************************************************************************
class CSound
{
public:
	enum class SOUND_LABEL {
		NONE = 0,
		BGM_TITLE,				//タイトルBGM
		BGM_MENU,				//メニューBGM
		BGM_GAME,				//ゲームBGM
		BGM_GAME_02,			//ゲーム02BGM
		BGM_GAME_03,			//ゲーム03BGM
		BGM_RESULT,				//リザルトBGM
		BGM_FIND_WOLF,			//人狼発見BGM
		BGM_FINAL_RESULT,		//最終リザルトBGM
		BGM_CREDIT,				//クレジットBGM

		SE_POINT_1,				//1ポイント獲得SE
		SE_POINT_3,				//3ポイント獲得SE
		SE_POINT_MINUS,			//ポイント失点SE
		SE_POINT_STEAL,			//ポイント奪取
		SE_BALLOON_BREAK,		//風船が割れるSE
		SE_ITEM_GET,			//アイテム取得SE
		SE_TIME_UP,				//タイムアップSE
		SE_PLAYER_SPIN,			//スピンSE
		SE_BANANA_THROW,		//バナナを投げるSE
		SE_USE_POINT_STEAL,		//ポイント奪取使用SE
		SE_COUNT_DOWN,			//カウントダウンSE
		SE_START,				//スタートSE
		SE_PLAYER_OK,			//プレイヤーOKSE
		SE_DECIDE,				//決定SE
		SE_CANCEL,				//キャンセルSE
		SE_PAUSE_OPEN,			//ポーズ開くSE
		SE_CURSOR,				//カーソルSE
		SE_CRASH,				//衝突SE
		SE_CRASHSTOP,			//衝突停止SE
		SE_FALL,				//落下SE
		SE_EXPLOSION,			//爆発SE
		SE_ITEM_SHIELD_GET,		//盾アイテム獲得SE
		SE_BALLOON_SPAWN,		//風船スポーンSE
		SE_DRUM_ROLL,			//ドラムロールSE
		SE_DRUM_ROLL_END,		//ドラムロール最後SE
		SE_TITLE_CHAR_CREATE,	//タイトルの文字生成SE
		SE_TITLE_LOGO_CREATE,	//タイトルロゴの生成SE
		SE_TITLE_CAR,			//タイトルの車通過SE
		SE_ENGINE,				//車のエンジンSE
		SE_RESULT_UI,			//結果発表UISE
		SE_CROWN,				//王冠SE

		ENUM_MAX
	};

	CSound();	//デフォルトコンストラクタ
	~CSound();	//デストラクタ
	HRESULT Init(HWND hWnd);	//初期化処理
	void Uninit(void);			//終了処理
	HRESULT PlaySound(SOUND_LABEL label);	//音の再生
	void StopSound(SOUND_LABEL label);		//音の停止
	void StopSound(void);					//音の停止
	void PauseSound(SOUND_LABEL label);		//音の一時停止
	void StartSound(SOUND_LABEL label);		//音の再開

	void SetBGM(SOUND_LABEL label);			//再生中BGMの設定
	SOUND_LABEL GetBGM(void);				//再生中BGMの取得
	void ResetBeginPlay(void);	//再生開始時のフラグをすべてリセット
	void ControllVoice(const SOUND_LABEL &label, const float fVolume) { m_apSourceVoice[(int)label]->SetVolume(fVolume); }	//音量調整

	//デフォルトのボリューム設定処理
	void SetDefaultVolum(const SOUND_LABEL &label, const float fDefaultVolum) { m_afDefaultVolum[(int)label] = fDefaultVolum; }
	//デフォルトのボリューム取得処理
	float GetDefaultVolum(const SOUND_LABEL &label) { return m_afDefaultVolum[(int)label]; }

private:
	// パラメータ構造体定義
	typedef struct
	{
		char *filename;		// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;

	//メンバ関数
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	
	//メンバ変数
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[(int)SOUND_LABEL::ENUM_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[(int)SOUND_LABEL::ENUM_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[(int)SOUND_LABEL::ENUM_MAX] = {};					// オーディオデータサイズ
	static PARAM m_aParam[(int)SOUND_LABEL::ENUM_MAX];						//ファイル名とループ

	SOUND_LABEL m_playBGM;	//再生中のBGM
	bool m_abBeginPlay[(int)SOUND_LABEL::ENUM_MAX];			//１フレームごとの再生開始時かどうかの判定
	float m_afDefaultVolum[(int)SOUND_LABEL::ENUM_MAX];		//デフォルトのボリューム
};

#endif // !_SOUND_H_
