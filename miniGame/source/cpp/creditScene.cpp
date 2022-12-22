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
#define CREDIT_SCENE_BG_MOVE_SPEED			(0.28f)			//背景の移動速度
#define CREDIT_SCENE_BG_SIZE_Y				(1516.0f)		//背景のサイズY
#define CREDIT_SCENE_BG_STAGE_MOVE_SPEED	(0.12f)			//背景ステージの移動量
#define CREDIT_SCENE_BG_CAR_CHANGE_COUNTER	(150)			//背景車を変えるまでの時間
#define CREDIT_SCENE_BG_CAR_SPEED			(1.0f)			//背景車の移動速度
#define CREDIT_SCENE_BG_TITLE_DEC_SIZE		(0.0002f)		//背景タイトルのサイズ縮小値
#define CREDIT_SCENE_BG_TITLE_SIZE			(1.05f)			//背景タイトルのサイズ
#define CREDIT_SCENE_BG_FADE_SPEED			(40)			//背景のフェードの時間

#define CREDIT_SCENE_CREDIT_SIZE_Y		(7809.0f)		//クレジットサイズY
#define CREDIT_SCENE_CREDIT_MOVE		(1.4f)			//クレジットの移動速度

#define CREDIT_SCENE_FADE_SPEED		(140)			//フェードの速度
#define CREDIT_SCENE_FADE_DELAY		(300)			//フェードするまでの遅延

#define CREDIT_SCENE_PICTURE_CREATE_POS				(D3DXVECTOR3(350.0f, 1000.0f, 0.0f))		//絵の生成位置
#define CREDIT_SCENE_PICTURE_CREATE_SCALE			(D3DXVECTOR3(0.35f, 0.35f, 0.35f))			//絵の大きさ
#define CREDIT_SCENE_PICTURE_SPEED					(1.2f)										//絵の移動速度
#define CREDIT_SCENE_PICTURE_ROT					(0.1f)										//絵の向き
#define CREDIT_SCENE_PICTURE_CREATE_INTERVAL		(600)										//絵の生成間隔
#define CREDIT_SCENE_PICTURE_INIT_CREATE_INTERVAL	(360)										//絵の最初の生成間隔
#define CREDIT_SCENE_PICTURE_LAST_CREATE			(4900)										//絵の生成を止めるまでの時間

#define CREDIT_SCENE_SKIP_ICON_SIZE_X				(408.0f * 0.4f)				//スキップアイコンのサイズX
#define CREDIT_SCENE_SKIP_ICON_SIZE_Y				(94.0f * 0.4f)				//スキップアイコンのサイズY
#define CREDIT_SCENE_SKIP_UNINIT_COUNT				(180)						//スキップアイコンが消えるまでの時間
#define CREDIT_SCENE_SKIP_DEC_ALPH					(0.07f)						//スキップアイコンのα値減少値


//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCreditScene::CCreditScene()
{
	m_pBg = nullptr;
	m_pBgStage = nullptr;
	m_pCredit = nullptr;
	m_pFade = nullptr;
	m_pSkipIcon = nullptr;
	m_bCanFade = false;
	m_bPictureRot = false;
	m_bFade = false;
	m_bFadeIn = false;
	m_bUninitSkipIcon = false;
	m_nFrameCounter = 0;
	m_nSkipIconCounter = 0;
	m_phase = PHASE::NONE;
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
	m_nSkipIconCounter = 0;
	m_bPictureRot = false;
	m_phase = PHASE::BG_CAR_00;
	m_pFade = nullptr;
	m_bFade = false;
	m_bFadeIn = true;
	m_pBgStage = nullptr;
	m_pSkipIcon = nullptr;
	m_bUninitSkipIcon = false;
}

//=============================================================================
//オブジェクト生成処理
//=============================================================================
void CCreditScene::CreateObject(void)
{
	//背景
	m_pBg = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                      CTexture::TEXTURE_TYPE::BG_CREDIT_CAR_00, SCREEN_WIDTH * 1.3f, SCREEN_HEIGHT * 1.3f);
	m_pBg->SetDrawPriority(CObject::DRAW_PRIORITY::BG);

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//------------------------------
	//BGMの再生
	//------------------------------
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_CREDIT);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_CREDIT);
	}
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

	//フェーズによる処理分け
	switch (m_phase)
	{
	case CCreditScene::PHASE::BG_CAR_00:
		//背景車処理
		BgCar00();
		break;
	case CCreditScene::PHASE::BG_CAR_01:
		//背景車処理
		BgCar01();
		break;
	case CCreditScene::PHASE::BG_TITLE:
		//背景タイトル処理
		BgTitle();
		break;
	case CCreditScene::PHASE::BG_00:
		//クレジット処理
		Credit();
		//絵生成処理
		CreatePicture();
		//背景処理
		Bg00();
		break;
	case CCreditScene::PHASE::BG_01:
		//クレジット処理
		Credit();
		//絵生成処理
		CreatePicture();
		//背景ステージ処理
		BgStage();
		break;
	default:
		break;
	}

	//スキップアイコン処理
	SkipIcon();

	//フェード処理
	Fade();

	//遷移処理
	SceneFade();
}

//=============================================================================
//背景車処理
//=============================================================================
void CCreditScene::BgCar00()
{
	if (m_pBg == nullptr) return;

	m_nFrameCounter++;
	if (m_nFrameCounter > CREDIT_SCENE_BG_CAR_CHANGE_COUNTER)
	{
		m_nFrameCounter = 0;

		//テクスチャを変える
		m_pBg->SetTexType(CTexture::TEXTURE_TYPE::BG_CREDIT_CAR_01);
		//位置変える
		m_pBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
		//フェーズを変える
		m_phase = PHASE::BG_CAR_01;
		return;
	}

	//位置取得
	D3DXVECTOR3 pos = m_pBg->GetPos();
	//移動させる
	pos.x += CREDIT_SCENE_BG_CAR_SPEED;
	//位置反映
	m_pBg->SetPos(pos);
}

//=============================================================================
//背景車処理
//=============================================================================
void CCreditScene::BgCar01()
{
	if (m_pBg == nullptr) return;

	m_nFrameCounter++;
	if (m_nFrameCounter > CREDIT_SCENE_BG_CAR_CHANGE_COUNTER)
	{
		m_nFrameCounter = 0;

		//テクスチャを変える
		m_pBg->SetTexType(CTexture::TEXTURE_TYPE::BG_CREDIT_TITLE);
		//位置変える
		m_pBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
		//サイズを変える
		m_pBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH * CREDIT_SCENE_BG_TITLE_SIZE, SCREEN_HEIGHT * CREDIT_SCENE_BG_TITLE_SIZE, 0.0f));

		//フェーズを変える
		m_phase = PHASE::BG_TITLE;
		return;
	}

	//位置取得
	D3DXVECTOR3 pos = m_pBg->GetPos();
	//移動させる
	pos.x -= CREDIT_SCENE_BG_CAR_SPEED;
	//位置反映
	m_pBg->SetPos(pos);
}

//=============================================================================
//背景タイトル処理
//=============================================================================
void CCreditScene::BgTitle()
{
	if (m_pBg == nullptr) return;

	m_nFrameCounter++;
	if (m_nFrameCounter > CREDIT_SCENE_BG_CAR_CHANGE_COUNTER)
	{
		//フェードする状態にする
		SetFade(CREDIT_SCENE_BG_FADE_SPEED, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		//フェードアウトになったら
		if (!m_bFadeIn)
		{
			m_nFrameCounter = CREDIT_SCENE_PICTURE_INIT_CREATE_INTERVAL;
			//消す
			m_pBg->Uninit();
			m_pBg = nullptr;

			//背景
			m_pBg = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT + (SCREEN_HEIGHT - (CREDIT_SCENE_BG_SIZE_Y / 2.0f)), 0.0f),
				                      CTexture::TEXTURE_TYPE::BG_CREDIT_01, SCREEN_WIDTH, CREDIT_SCENE_BG_SIZE_Y);
			m_pBg->SetDrawPriority(CObject::DRAW_PRIORITY::BG);

			//クレジット生成
			m_pCredit = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, CREDIT_SCENE_CREDIT_SIZE_Y / 2.0f + SCREEN_HEIGHT, 0.0f),
				                          CTexture::TEXTURE_TYPE::CREDIT_CREDIT, SCREEN_WIDTH, CREDIT_SCENE_CREDIT_SIZE_Y);
			m_pCredit->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);

			//フェーズを変える
			m_phase = PHASE::BG_00;
			return;
		}
	}

	//サイズ取得
	D3DXVECTOR3 size = m_pBg->GetSize();
	//小さくする
	size.x -= SCREEN_WIDTH * CREDIT_SCENE_BG_TITLE_DEC_SIZE;
	size.y -= SCREEN_HEIGHT * CREDIT_SCENE_BG_TITLE_DEC_SIZE;
	//位置反映
	m_pBg->SetSize(size);
}

//=============================================================================
//背景処理
//=============================================================================
void CCreditScene::Bg00()
{
	if (m_pBg == nullptr) return;
	//位置取得
	D3DXVECTOR3 pos = m_pBg->GetPos();

	//移動させる
	pos.y -= CREDIT_SCENE_BG_MOVE_SPEED;
	//止める
	if (pos.y < 0.0f - ((CREDIT_SCENE_BG_SIZE_Y / 2.0f) - SCREEN_HEIGHT) + 5.0f)
	{
		//フェードする状態にする
		SetFade(CREDIT_SCENE_BG_FADE_SPEED, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		//フェードアウトになったら
		if (!m_bFadeIn)
		{
			//背景を変更
			m_pBg->SetTexType(CTexture::TEXTURE_TYPE::BG_CREDIT_02);
			//サイズと位置変更
			m_pBg->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
			m_pBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
			//フェーズを変える
			m_phase = PHASE::BG_01;

			//背景ステージを生成
			m_pBgStage = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                                   CTexture::TEXTURE_TYPE::BG_CREDIT_03, SCREEN_WIDTH, SCREEN_HEIGHT);
			return;
		}
	}
	//位置反映
	m_pBg->SetPos(pos);
}

//=============================================================================
//背景ステージ処理
//=============================================================================
void CCreditScene::BgStage()
{
	if (m_pBgStage == nullptr) return;
	//位置取得
	D3DXVECTOR3 pos = m_pBgStage->GetPos();
	//移動させる
	pos.y += CREDIT_SCENE_BG_STAGE_MOVE_SPEED;
	//位置反映
	m_pBgStage->SetPos(pos);
}

//=============================================================================
//遷移処理
//=============================================================================
void CCreditScene::SceneFade()
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
	if (pFade != nullptr) pFade->SetFade(CScene::SCENE_TYPE::SELECT_GAME, CREDIT_SCENE_FADE_SPEED, 30, 0);
}

//=============================================================================
//フェード処理
//=============================================================================
void CCreditScene::Fade()
{
	if (!m_bFade) return;

	//フェードの生成
	if (m_pFade == nullptr)
	{
		m_pFade = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE,
			                        SCREEN_WIDTH, SCREEN_HEIGHT);
		m_pFade->SetColor(m_fadeCol);
		m_pFade->SetDrawPriority(CObject::DRAW_PRIORITY::UI);
	}

	//カラー取得
	D3DXCOLOR fadeCol = m_pFade->GetColor();

	//フェードする量を設定
	float AddCol = 1.0f / m_nFadeTime;


	if (m_bFadeIn)
	{
		//α値を濃くする
		fadeCol.a += AddCol;
		if (fadeCol.a >= 1.0f)
		{
			fadeCol.a = 1.0f;
			//フェードアウトにする
			m_bFadeIn = false;
		}
	}
	else
	{
		//α値を薄くする
		fadeCol.a -= AddCol;
		if (fadeCol.a <= 0.0f)
		{
			fadeCol.a = 0.0f;
			//フェードインにする
			m_bFadeIn = true;
			//フェードを終了する
			m_bFade = false;
			//消す
			m_pFade->Uninit();
			m_pFade = nullptr;
			return;
		}
	}
	//カラー設定
	m_pFade->SetColor(fadeCol);
}

//=============================================================================
//スキップアイコン処理
//=============================================================================
void CCreditScene::SkipIcon()
{
	//フェードできる状態なら
	if (m_bCanFade) return;

	//消す状態だったら
	if (m_bUninitSkipIcon)
	{
		if (m_pSkipIcon == nullptr) return;

		//カラー取得
		D3DXCOLOR col = m_pSkipIcon->GetColor();
		//薄くする
		col.a -= CREDIT_SCENE_SKIP_DEC_ALPH;
		//見えなくなったら
		if (col.a <= 0.0f)
		{
			//消す
			m_pSkipIcon->Uninit();
			m_pSkipIcon = nullptr;

			//消さない状態にする
			m_bUninitSkipIcon = false;
			return;
		}
		//カラー設定
		m_pSkipIcon->SetColor(col);
	}
	else
	{//消す状態じゃなかったら
		CManager* pManager = CManager::GetManager();	//マネージャーの取得
		if (pManager == nullptr) return;
		//現在の入力デバイスの取得
		CInput* pInput = pManager->GetInputCur();
		if (pInput == nullptr) return;

		if (pInput->GetTrigger(CInput::CODE::SELECT, 0)) {
			
			//スキップアイコンが生成されていなかったら
			if (m_pSkipIcon == nullptr)
			{
				//スキップアイコンの生成
				m_pSkipIcon = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - CREDIT_SCENE_SKIP_ICON_SIZE_X / 2.0f,
					                                        SCREEN_HEIGHT - CREDIT_SCENE_SKIP_ICON_SIZE_Y / 2.0f, 0.0f),
					                            CTexture::TEXTURE_TYPE::CREDIT_SKIP_ICON, CREDIT_SCENE_SKIP_ICON_SIZE_X, CREDIT_SCENE_SKIP_ICON_SIZE_Y);
				m_pSkipIcon->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
			}
			else
			{
				//フェードの取得
				CFade* pFade = pManager->GetFade();		//フェードへのポインタ
				if (pFade == nullptr) return;

				if (pFade->GetChangeFade()) return;
				//タイトルに遷移
				if (pFade != nullptr) pFade->SetFade(CScene::SCENE_TYPE::SELECT_GAME, CREDIT_SCENE_FADE_SPEED, 30, 0);
				return;
			}
		}

		//スキップアイコンが生成されていなかったら
		if (m_pSkipIcon == nullptr) return;

		m_nSkipIconCounter++;
		if (m_nSkipIconCounter > CREDIT_SCENE_SKIP_UNINIT_COUNT)
		{
			m_nSkipIconCounter = 0;
			//消す状態にする
			m_bUninitSkipIcon = true;
			return;
		}
	}
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
		//リセット
		m_nFrameCounter = 0;
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

	if (m_nFrameCounter % CREDIT_SCENE_PICTURE_CREATE_INTERVAL == 0 && m_nFrameCounter < CREDIT_SCENE_PICTURE_LAST_CREATE)
	{
		//向きの設定
		float fRot = CREDIT_SCENE_PICTURE_ROT;
		//向きを逆にする
		if (m_bPictureRot) fRot *= -1.0f;

		//絵の生成
		CCreditPicture::Create(CREDIT_SCENE_PICTURE_CREATE_POS, CREDIT_SCENE_PICTURE_CREATE_SCALE, fRot,
			                   CTexture::TEXTURE_TYPE::CREDIT_PICTURE_00, -CREDIT_SCENE_PICTURE_SPEED);

		//向きの切り替え
		if (m_bPictureRot) m_bPictureRot = false;
		else m_bPictureRot = true;
	}
}

//=============================================================================
//フェード設定処理
//=============================================================================
void CCreditScene::SetFade(const int nCnt, const D3DXCOLOR col)
{
	if (m_bFade) return;

	//設定
	m_nFadeTime = nCnt;
	m_fadeCol = col;

	//フェードするようにする
	m_bFade = true;
}
