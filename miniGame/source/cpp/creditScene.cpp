//=============================================================================
//
// クレジットシーン処理 [creditScene.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "creditScene.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
#include "object2D.h"
#include "credit_picture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CREDIT_SCENE_BG_MOVE_SPEED		(D3DXVECTOR2(0.001f, 0.001f))		//背景の移動速度

#define CREDIT_SCENE_CREDIT_SIZE_Y		(7809.0f)		//クレジットサイズY
#define CREDIT_SCENE_CREDIT_MOVE		(3.0f)			//クレジットの移動速度

#define CREDIT_SCENE_FADE_SPEED		(0.005f)		//フェードの速度
#define CREDIT_SCENE_FADE_DELAY		(120)			//フェードするまでの遅延


//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCreditScene::CCreditScene()
{
	m_pBg = nullptr;
	m_pCredit = nullptr;
	m_bCanFade = false;
	m_nFrameCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCreditScene::~CCreditScene()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void CCreditScene::Init(void) {
	//テクスチャのロード
	CTexture::Load("credit");

	//変数初期化
	m_bCanFade = false;
	m_nFrameCounter = 0;

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//------------------------------
	//BGMの再生
	//------------------------------
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_RESULT);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_RESULT);
	}
}

//=============================================================================
//オブジェクト生成処理
//=============================================================================
void CCreditScene::CreateObject(void)
{
	//クレジット生成
	m_pCredit = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, CREDIT_SCENE_CREDIT_SIZE_Y / 2.0f + SCREEN_HEIGHT, 0.0f),
		                          CTexture::TEXTURE_TYPE::CREDIT_CREDIT, SCREEN_WIDTH, CREDIT_SCENE_CREDIT_SIZE_Y);
}

//=============================================================================
// 終了処理
//=============================================================================
void CCreditScene::Uninit(void) {
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
// 更新処理
//=============================================================================
void CCreditScene::Update(void) {
	//ロードが終了していなかったら
	if (!CTexture::GetLoadFinish()) return;

	//シーンの更新処理
	CScene::Update();

	//クレジット処理
	Credit();

	//絵生成処理
	CreatePicture();

	//背景処理
	Bg();

	//遷移処理
	Fade();
}

//=============================================================================
//背景処理
//=============================================================================
void CCreditScene::Bg()
{
	if (m_pBg == nullptr) return;

	//背景を動かす
	//m_pBg->SetMoveTex(CREDIT_SCENE_BG_MOVE_SPEED.x, CREDIT_SCENE_BG_MOVE_SPEED.y);
}

//=============================================================================
//遷移処理
//=============================================================================
void CCreditScene::Fade()
{
	if (!m_bCanFade) return;

	//遷移できる状態なら

	m_nFrameCounter++;
	if (m_nFrameCounter <= CREDIT_SCENE_FADE_DELAY) return;

	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;

	//フェードの取得
	CFade* pFade = pManager->GetFade();		//フェードへのポインタ
	if (pFade == nullptr) return;

	if (pFade->GetChangeFade()) return;
	//タイトルに遷移
	if (pFade != nullptr) pFade->SetFade(CScene::SCENE_TYPE::TITLE, CREDIT_SCENE_FADE_SPEED, 0);
}

//=============================================================================
//クレジット処理
//=============================================================================
void CCreditScene::Credit()
{
	if (m_pCredit == nullptr) return;

	//位置取得
	D3DXVECTOR3 pos = m_pCredit->GetPos();

	if (pos.y == -CREDIT_SCENE_CREDIT_SIZE_Y / 2.0f + SCREEN_HEIGHT) return;

	//移動させる
	pos.y -= CREDIT_SCENE_CREDIT_MOVE;
	if (pos.y <= -CREDIT_SCENE_CREDIT_SIZE_Y / 2.0f + SCREEN_HEIGHT)
	{
		pos.y = -CREDIT_SCENE_CREDIT_SIZE_Y / 2.0f + SCREEN_HEIGHT;
		//フェードできる状態にする
		m_bCanFade = true;
	}

	//位置反映
	m_pCredit->SetPos(pos);
}

//=============================================================================
//絵生成処理
//=============================================================================
void CCreditScene::CreatePicture()
{
	m_nFrameCounter++;

	if (m_nFrameCounter > 60)
	{
		//リセット
		m_nFrameCounter = 0;

		//絵の生成
		CCreditPicture::Create(D3DXVECTOR3(400.0f, SCREEN_HEIGHT, 0.0f), D3DXVECTOR3(0.5f, 0.5f, 0.5f), 0.0f, CTexture::TEXTURE_TYPE::ADD_POINT_10, -3.0f);
	}

}
