//=============================================================================
//
// テクスチャ処理 [texture.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include <thread>
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXT_FILE_NAME_TEXTURE "data/TEXT/load_texture.txt"
#define MAX_LOAD_TEXT (128)		//一度にファイルから読み込むテキストのバイト数

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[(int)TEXTURE_TYPE::ENUM_MAX] = {};
char CTexture::m_asFilePath[(int)TEXTURE_TYPE::ENUM_MAX][MAX_TEXTURE_FILE_PATH] = {};
bool CTexture::m_bAllSceneTex[(int)TEXTURE_TYPE::ENUM_MAX] = {};
bool CTexture::m_bLoadFinish = false;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

////=============================================================================
//// テクスチャのロード
////=============================================================================
//HRESULT CTexture::Load(const char* sLoadType) {
//	//-------------------------------------
//	//ファイルの読み込み
//	//-------------------------------------
//	FILE *pFile;		//ファイルへのポインタ
//	char sLoadText[MAX_LOAD_TEXT];//一行ずつ読み込むファイルのテキスト
//	char *pLoadText;	//ファイルのテキストを分割した文字列
//
//	bool bLoadTexture[(int)TEXTURE_TYPE::ENUM_MAX];	//テクスチャ読み込みフラグ
//	memset(&bLoadTexture, 0, sizeof(bLoadTexture));	//falseで初期化
//
//	//ファイルを開く
//	fopen_s(&pFile, TEXT_FILE_NAME_TEXTURE, "r");
//	if (pFile == nullptr) return S_OK;	//ロード終了
//
//	for (int nIdxType = 1; //次に読み込むテクスチャの種類	0にNONEがあるため1から
//		fgets(sLoadText, MAX_LOAD_TEXT, pFile) != nullptr && nIdxType < (int)TEXTURE_TYPE::ENUM_MAX;) //一行ごとに文字列を取得
//	{
//		char *pText = nullptr;	//読み込み位置の保存
//
//		pLoadText = strtok_s(sLoadText, " \t\n", &pText);	//文字列の分割（空白 タブ 改行）
//		//テキストがない
//		if (pLoadText == nullptr) continue;
//		//コメント
//		if (strstr(pLoadText, "//") != nullptr) continue;
//
//		//ディレクトリ名のコピー 安全なためおそらく必要ないif
//		/*if (strlen(pLoadText) < MAX_TEXTURE_FILE_PATH) {
//		strcpy_s(m_asFilePath[nIdxType], pLoadText);
//		}*/
//		strcpy_s(m_asFilePath[nIdxType], pLoadText);
//
//
//		//文字列の分割（空白 タブ 改行 = ,）
//		pLoadText = strtok_s(nullptr, " ,=\t\n", &pText);
//
//		while (pLoadText != nullptr)
//		//while (strcmp(pLoadText, "\0") != 0)	strtok_sを正しく使えていなかったので勘違いかも
//		{
//			//読み込みのタイプと一致していた場合終了
//			bLoadTexture[nIdxType] = strcmp(pLoadText, sLoadType) == 0 || strcmp(pLoadText, "all") == 0;
//			if (bLoadTexture[nIdxType]) break;
//
//			//文字列の分割（空白 タブ 改行 = ,）
//			pLoadText = strtok_s(nullptr, " ,=\t\n", &pText);
//		}
//
//		//読み込むインデックスの加算
//		nIdxType++;
//	}
//	//ファイルを閉じる
//	fclose(pFile);
//
//	//0にNONEがあるため1から
//	for (int nCnt = 1; nCnt < (int)TEXTURE_TYPE::ENUM_MAX; nCnt++)
//	{
//		//すでにテクスチャが生成されていた場合破棄
//		if (m_apTexture[nCnt] != nullptr) {
//			m_apTexture[nCnt]->Release();
//			m_apTexture[nCnt] = nullptr;
//		}
//
//		//読み込みフラグが立っていない場合
//		if (!bLoadTexture[nCnt]) continue;
//
//		//テクスチャの生成
//		CreateTexture(nCnt);
//	}
//
//	return S_OK;
//}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CTexture::CreateTexture(int nIdx) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;
	//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;

	D3DXCreateTextureFromFile(pDevice,
		m_asFilePath[nIdx],	// テクスチャパス
		&m_apTexture[nIdx]);
}

//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CTexture::Unload(bool bAllUnload) {
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < (int)TEXTURE_TYPE::ENUM_MAX; nCnt++)
	{
		if (m_bAllSceneTex[nCnt] && !bAllUnload) continue;

		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
	}
}

//=============================================================================
// テクスチャの取得
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE type) {
	if (type < (TEXTURE_TYPE)0 || type >= TEXTURE_TYPE::ENUM_MAX) return nullptr;
	return m_apTexture[(int)type];
}

//=============================================================================
// テクスチャの取得
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(char* texPath) {
	for (int nCnt = 0; nCnt < (int)TEXTURE_TYPE::ENUM_MAX; nCnt++)
	{
		//テクスチャのパスと一致していた場合
		if (strcmp(m_asFilePath[nCnt], texPath) == 0) {
			return m_apTexture[nCnt];
		}
	}
	return nullptr;
}

//=============================================================================
// テクスチャのパスの取得
//=============================================================================
char* CTexture::GetPathName(TEXTURE_TYPE type) {
	if (type < (TEXTURE_TYPE)0 || type >= TEXTURE_TYPE::ENUM_MAX) return nullptr;
	return m_asFilePath[(int)type];
}


//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CTexture::Load(const char* sLoadType) {
	//ロード中にする
	m_bLoadFinish = false;

	//スレッド分けする
	std::thread thread(LoadTex, sLoadType);

#ifdef _DEBUG
	thread.join();
#else
	thread.detach();
#endif // !_DEBUG

	return S_OK;
}

//=============================================================================
//全シーンで使うテクスチャデータの読み込み
//=============================================================================
HRESULT CTexture::AllSceneTextureLoad()
{
	//-------------------------------------
	//ファイルの読み込み
	//-------------------------------------
	FILE *pFile;		//ファイルへのポインタ
	char sLoadText[MAX_LOAD_TEXT];//一行ずつ読み込むファイルのテキスト
	char *pLoadText;	//ファイルのテキストを分割した文字列

	bool bLoadTexture[(int)TEXTURE_TYPE::ENUM_MAX];	//テクスチャ読み込みフラグ
	memset(&bLoadTexture, 0, sizeof(bLoadTexture));	//falseで初期化

	//ファイルを開く
	fopen_s(&pFile, TEXT_FILE_NAME_TEXTURE, "r");
	if (pFile == nullptr) return S_OK;	//ロード終了

	for (int nIdxType = 1; //次に読み込むテクスチャの種類	0にNONEがあるため1から
		fgets(sLoadText, MAX_LOAD_TEXT, pFile) != nullptr && nIdxType < (int)TEXTURE_TYPE::ENUM_MAX;) //一行ごとに文字列を取得
	{
		char *pText = nullptr;	//読み込み位置の保存

		pLoadText = strtok_s(sLoadText, " \t\n", &pText);	//文字列の分割（空白 タブ 改行）
		//テキストがない
		if (pLoadText == nullptr) continue;
		//コメント
		if (strstr(pLoadText, "//") != nullptr) continue;

		//ディレクトリ名のコピー 安全なためおそらく必要ないif
		/*if (strlen(pLoadText) < MAX_TEXTURE_FILE_PATH) {
		strcpy_s(m_asFilePath[nIdxType], pLoadText);
		}*/
		strcpy_s(m_asFilePath[nIdxType], pLoadText);


		//文字列の分割（空白 タブ 改行 = ,）
		pLoadText = strtok_s(nullptr, " ,=\t\n", &pText);

		while (pLoadText != nullptr)
		//while (strcmp(pLoadText, "\0") != 0)	strtok_sを正しく使えていなかったので勘違いかも
		{
			//読み込みのタイプと一致していた場合終了
			bLoadTexture[nIdxType] = strcmp(pLoadText, "all") == 0;

			if (bLoadTexture[nIdxType])
			{
				//ここで読み込んだテクスチャは破棄しないようにする
				m_bAllSceneTex[nIdxType] = true;
				break;
			}

			//文字列の分割（空白 タブ 改行 = ,）
			pLoadText = strtok_s(nullptr, " ,=\t\n", &pText);
		}

		//読み込むインデックスの加算
		nIdxType++;
	}
	//ファイルを閉じる
	fclose(pFile);

	//0にNONEがあるため1から
	for (int nCnt = 1; nCnt < (int)TEXTURE_TYPE::ENUM_MAX; nCnt++)
	{
		//すでにテクスチャが生成されていた場合破棄
		if (m_apTexture[nCnt] != nullptr) {
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}

		//読み込みフラグが立っていない場合
		if (!bLoadTexture[nCnt]) continue;

		//テクスチャの生成
		CreateTexture(nCnt);
	}
	return S_OK;
}

//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CTexture::LoadTex(const char * sLoadType)
{
	//-------------------------------------
	//ファイルの読み込み
	//-------------------------------------
	FILE *pFile;		//ファイルへのポインタ
	char sLoadText[MAX_LOAD_TEXT];//一行ずつ読み込むファイルのテキスト
	char *pLoadText;	//ファイルのテキストを分割した文字列

	bool bLoadTexture[(int)TEXTURE_TYPE::ENUM_MAX];	//テクスチャ読み込みフラグ
	memset(&bLoadTexture, 0, sizeof(bLoadTexture));	//falseで初期化

	//ファイルを開く
	fopen_s(&pFile, TEXT_FILE_NAME_TEXTURE, "r");
	if (pFile == nullptr) return S_OK;	//ロード終了

	for (int nIdxType = 1; //次に読み込むテクスチャの種類	0にNONEがあるため1から
		fgets(sLoadText, MAX_LOAD_TEXT, pFile) != nullptr && nIdxType < (int)TEXTURE_TYPE::ENUM_MAX;) //一行ごとに文字列を取得
	{
		char *pText = nullptr;	//読み込み位置の保存

		pLoadText = strtok_s(sLoadText, " \t\n", &pText);	//文字列の分割（空白 タブ 改行）
		//テキストがない
		if (pLoadText == nullptr) continue;
		//コメント
		if (strstr(pLoadText, "//") != nullptr) continue;

		//ディレクトリ名のコピー 安全なためおそらく必要ないif
		/*if (strlen(pLoadText) < MAX_TEXTURE_FILE_PATH) {
		strcpy_s(m_asFilePath[nIdxType], pLoadText);
		}*/
		strcpy_s(m_asFilePath[nIdxType], pLoadText);


		//文字列の分割（空白 タブ 改行 = ,）
		pLoadText = strtok_s(nullptr, " ,=\t\n", &pText);

		while (pLoadText != nullptr)
		//while (strcmp(pLoadText, "\0") != 0)	strtok_sを正しく使えていなかったので勘違いかも
		{
			//読み込みのタイプと一致していた場合終了
			bLoadTexture[nIdxType] = strcmp(pLoadText, sLoadType) == 0;
			if (bLoadTexture[nIdxType]) break;

			//文字列の分割（空白 タブ 改行 = ,）
			pLoadText = strtok_s(nullptr, " ,=\t\n", &pText);
		}

		//読み込むインデックスの加算
		nIdxType++;
	}
	//ファイルを閉じる
	fclose(pFile);

	//0にNONEがあるため1から
	for (int nCnt = 1; nCnt < (int)TEXTURE_TYPE::ENUM_MAX; nCnt++)
	{
		if (m_bAllSceneTex[nCnt]) continue;

		//すでにテクスチャが生成されていた場合破棄
		if (m_apTexture[nCnt] != nullptr) {
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}

		//読み込みフラグが立っていない場合
		if (!bLoadTexture[nCnt]) continue;

		//テクスチャの生成
		CreateTexture(nCnt);
	}

	//ロード中でなくする
	m_bLoadFinish = true;

	return S_OK;
}