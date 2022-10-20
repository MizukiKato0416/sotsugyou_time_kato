//=============================================================================
//
// タイトルシーン処理 [titleScene.cpp]
// Author : 鶴間俊樹
// Author : 佐藤瞭平
//
//=============================================================================
#include "titleScene.h"
#include "manager.h"
#include "renderer.h"
#include "titleCamera.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "object2D.h"
#include "selectMenu2D.h"
#include "objectModel.h"

#include "meshwall.h"
#include "object_player.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define FOG_COLOR (D3DXCOLOR(0.9f, 0.5f, 0.0f, 1.0f))	//フォグの色
#define TEXT_FILE_NAME_APPLETYPE "data/TEXT/save_appletype.txt"
#define ESC_POS (D3DXVECTOR3(120.0f, 40.0f, 0.0f))
#define ESC_WIDTH (200.0f)
#define ESC_HEIGHT (40.0f)
#define TITLE_LOGO_POS (D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 100.0f, 0.0f))
#define TITLE_LOGO_WIDTH (800.0f)
#define TITLE_LOGO_HEIGHT (200.0f)
#define NEXT_LOGO_POS (D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 550.0f, 0.0f))
#define NEXT_LOGO_WIDTH (400.0f)
#define NEXT_LOGO_HEIGHT (100.0f)

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CObject2D * CTitleScene::m_pNext = nullptr;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTitleScene::CTitleScene() :m_fMaxCol(1.0f), m_nDivideNum(2), m_nMaxColTime(3)
{	
	m_bPushKey = false;
	m_nFadeTime = 10;
	m_nColorTime = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleScene::~CTitleScene()
{

}

//=============================================================================
// タイトルシーンの初期化処理
//=============================================================================
void CTitleScene::Init(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
#if 0
	//カメラの設定
	if (pManager != nullptr) pManager->SetCamera(CTitleCamera::Create());

	//------------------------------
	//ライトの初期設定
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ライトの射影変換
	//ライトのプロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 200.0f, 1800.0f);

	D3DXMATRIX mtxLightView;   // ライトビュー変換
	D3DXVECTOR3 posLightV = D3DXVECTOR3(0.0f, 1200.0f, -1000.0f);	//ライトの視点の位置
	D3DXVECTOR3 posLightR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//ライトの注視点の位置
	D3DXVECTOR3 vecLight = -D3DXVECTOR3(posLightV - posLightR);		//ライトのベクトル
	D3DXVec3Normalize(&vecLight, &vecLight);	//ベクトルを正規化
	//ライトのビューマトリックスを生成
	D3DXMatrixLookAtLH(&mtxLightView, &posLightV, &D3DXVECTOR3(posLightV + vecLight), &D3DXVECTOR3(0, 1, 0));
	//シェーダのライトを設定
	if (pRenderer != nullptr) {
		pRenderer->SetEffectLightMatrixView(mtxLightView);
		pRenderer->SetEffectLightVector(D3DXVECTOR4(vecLight, 1.0f));
		pRenderer->SetEffectLightMatrixProj(mtxLightProj);
	}

	//------------------------------
	//フォグの初期設定
	//------------------------------
	if (pRenderer != nullptr) {
		pRenderer->SetEffectFogEnable(true);
		pRenderer->SetEffectFogColor(FOG_COLOR);
		pRenderer->SetEffectFogRange(200.0f, 4000.0f);
		//バックバッファをフォグの色に合わせる
		pRenderer->SetBackBuffColor(FOG_COLOR);
	}	
#endif // 0

	//------------------------------
	//UIの生成
	//------------------------------
	// 背景
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / m_nDivideNum, SCREEN_HEIGHT / m_nDivideNum, 0.0f), CTexture::TEXTURE_TYPE::BG_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	// ゲーム終了UI
	CObject2D::Create(ESC_POS, CTexture::TEXTURE_TYPE::QUIT_GAME, ESC_WIDTH, ESC_HEIGHT);
	// タイトルロゴ
	CObject2D::Create(TITLE_LOGO_POS, CTexture::TEXTURE_TYPE::TEXT_TITLENAME, TITLE_LOGO_WIDTH, TITLE_LOGO_HEIGHT);
	// 次に行かせるロゴ
	m_pNext = CObject2D::Create(NEXT_LOGO_POS, CTexture::TEXTURE_TYPE::TEXT_GAMESTART, NEXT_LOGO_WIDTH, NEXT_LOGO_HEIGHT);

	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_TITLE);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_TITLE);
	}

	//オブジェクトのポーズが無いように設定
	CObject::SetUpdatePauseLevel(0);


#ifdef _DEBUG
	//Zバッファテクスチャの表示
	CObject2D* pZBuff = CObject2D::Create(D3DXVECTOR3(70.0f, 120.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, 100.0f, 100.0f);
	if (pZBuff != nullptr) {
		pZBuff->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
		pZBuff->SetUseZBuffTexture(true);
	}
#endif

}

//=============================================================================
// タイトルシーンの終了処理
//=============================================================================
void CTitleScene::Uninit(void) {	

	//シーンの終了処理
	CScene::Uninit();

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//音の停止
	if (pSound != nullptr) {
		pSound->StopSound();
	}
}

//=============================================================================
// タイトルシーンの更新処理
//=============================================================================
void CTitleScene::Update(void) {		
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	CInput* pInput = nullptr;	//入力デバイスへのポインタ
	CFade* pFade = nullptr;		//フェードへのポインタ
	CSound* pSound = nullptr;	//サウンドへのポインタ
	D3DXCOLOR col = m_pNext->GetColor(); // 次に行かせるロゴの色の取得

	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
		//フェードの取得
		pFade = pManager->GetFade();
		//サウンドの取得
		pSound = pManager->GetSound();
	}

	if (pInput == nullptr || pFade == nullptr) return;

	//決定キーを押したとき
	if (pInput->GetTrigger(CInput::CODE::SELECT, 0) && !m_bPushKey) 
	{		
		//フェード中だった場合
		if (pFade->GetFade()) 
		{
			//フェードをスキップ
			pFade->SkipFade();
		}		
		else
		{
			// 押されたとき
			m_bPushKey = true;

			//決定音の再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
		}
	}

	//決定キーが押されたとき
	if (m_bPushKey)
	{		
		// 色の状態を取得
		m_bCol = ChangeColTime(m_bCol);
		// 点滅処理(状態遷移)
		if (m_bCol)
		{
			// α値の変更
			col.a = m_fMaxCol;		
		}
		else
		{
			// α値の変更
			col.a = m_fMaxCol / m_nDivideNum;			
		}		
		// 次に行かせるロゴの色の設定
		m_pNext->SetColor(col);

		// 遷移する時間が0より小さくなっていたら
		if (m_nFadeTime < 0)
		{
			// 0を代入してマイナス値にならないようにする
			m_nFadeTime = 0;	
			//シーン遷移開始			
			if (pFade != nullptr) pFade->SetFade(CScene::SCENE_TYPE::GAME, 0.02f, 60);
		}
		else
		{
			//遷移する時間が0より小さくなっていたら
			m_nFadeTime--;
		}
	}
}

//=============================================================================
// タイトルシーンの色が変わる時間の処理
//=============================================================================
bool CTitleScene::ChangeColTime(bool bCol)
{
	// 色を変える時間を加算
	m_nColorTime++;

	// 時間が最大時間に行ったら
	if (m_nColorTime > m_nMaxColTime)
	{
		// bCol = trueのとき
		if (bCol)
		{
			bCol = false;
		}
		else // それ以外
		{
			bCol = true;
		}
		// 色を変える時間を初期化
		m_nColorTime = 0;
	}

	return bCol;
}