//=============================================================================
//
// ゲームシーン03処理 [gameScene03.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "gameScene03.h"

#include "check.h"
#include "count_down_ui.h"
#include "fade.h"
#include "finalResultScene.h"
#include "finish_ui.h"
#include "float_object.h"
#include "gameCamera03.h"
#include "input.h"
#include "manager.h"
#include "meshwall.h"
#include "object2D.h"
#include "objplayer_stop.h"
#include "pauseMenu.h"
#include "player.h"
#include "player_icon.h"
#include "sound.h"
#include "timer.h"
#include "ToScreen.h"

//エフェクト
#include "plane.h"
#include "PresetSetEffect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GAME_TIME				(60)		//ゲームの時間

#define FOG_COLOR				(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		//フォグの色
#define BACK_BUFF_COLOR			(D3DXCOLOR(0.1f, 0.3f, 0.5f, 1.0f))		//バックバッファーの色

#define PLAYER_ICON_SCALE		(0.35f)		//プレイヤーアイコンのスケール
#define STOP_POS_MIN			(5000.0f)	//ストップできる最低の距離
#define STOP_POS_MAX			(30000.0f)	//矯正ストップされる距離
#define FINISH_UI_NUM			(5)			//フィニッシュUIの数
#define NEXT_SCENE_COUNT		(240)		//次のシーンまでのカウント

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGameScene03::CGameScene03()
{
	m_nCntGameClear = 0;
	memset(m_apPlayer, NULL, sizeof(m_apPlayer[MAX_OBJECT_PLAYER_NUM]));
	memset(m_apPlayerIcon, NULL, sizeof(m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM]));
	m_bReady = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameScene03::~CGameScene03()
{

}

//=============================================================================
// ゲームシーンの初期化処理
//=============================================================================
void CGameScene03::Init(void) {
	//テクスチャのロード
	CTexture::Load("game01");

	//変数初期化
	m_bReady = true;
	m_fDestDist = 100.0f;

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//カメラの設定
	if (pManager != nullptr) pManager->SetCamera(CGameCamera03::Create());

	//------------------------------
	//ライトの初期設定
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ライトの射影変換
	//ライトのプロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 1500.0f, 3000.0f);

	D3DXMATRIX mtxLightView;   // ライトビュー変換
	D3DXVECTOR3 posLightV = D3DXVECTOR3(800.0f, 2000.0f, -800.0f);	//ライトの視点の位置
	D3DXVECTOR3 posLightR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//ライトの注視点の位置
	D3DXVECTOR3 vecLight = -D3DXVECTOR3(posLightV - posLightR);		//ライトのベクトル
	//ベクトルを正規化
	D3DXVec3Normalize(&vecLight, &vecLight);						
	//ライトのビューマトリックスを生成
	D3DXMatrixLookAtLH(&mtxLightView, &posLightV, &posLightR, &D3DXVECTOR3(0, 0, 1));
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

		//フォグの色
		D3DXCOLOR fogColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		//バックバッファーの色
		D3DXCOLOR backBuffColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		//バックバッファをフォグの色に合わせる
		pRenderer->SetBackBuffColor(backBuffColor);
		pRenderer->SetEffectFogColor(fogColor);
		pRenderer->SetEffectFogRange(20.0f, 10000.0f);

	}

	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME_02);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME_02);
	}

	//ゲームシーンの初期化処理
	CGameScene::Init();

	//オブジェクトのポーズが無いように設定
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
// オブジェクト生成処理
//=============================================================================
void CGameScene03::CreateObject(void) {
	//床の生成
	CMeshwall::Create(D3DXVECTOR3(-2000.0f, 0.0f, -0.0f), D3DXVECTOR3(D3DX_PI*0.5f, D3DX_PI*0.5f, 0.0f), 4, 4, 10000.0f, 10000.0f, CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);

	//プレイヤーの生成
	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		m_apPlayer[nCntPlayer] = CObjplayerStop::Create(D3DXVECTOR3(0.0f, 0.0f, nCntPlayer * -150.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));

		//更新しないようにする
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(false);
	}
}

//=============================================================================
// ゲームシーンの終了処理
//=============================================================================
void CGameScene03::Uninit(void) {

	//ゲームシーンの終了処理
	CGameScene::Uninit();
}

//=============================================================================
// ゲームシーンの更新処理
//=============================================================================
void CGameScene03::Update(void) {

#ifdef _DEBUG
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//現在の入力デバイスの取得
	CInput* pInput = pManager->GetInputKeyboard();
	if (pInput == nullptr) return;

	//ゲームオーバー
	if (pInput->GetTrigger(CInput::CODE::DEBUG_1, 0)) {
		GameOver();
	}
#endif


	//ゲームオーバー時
	if (m_bGameOver) {
		UpdateGameOver();
	}
	//準備状態時
	else if (m_bReady) {
		UpdateReady();
	}
	//ゲーム中
	else
	{
		UpdateGame();
	}

	//ゲームシーンの更新処理
	CGameScene::Update();
}

//=============================================================================
// ゲーム中の更新
//=============================================================================
void CGameScene03::UpdateGame(void) {
	//ポーズメニューがある場合は更新なし
	if (m_pMenuPause != nullptr) return;

	//ゲーム終了していないときにタイマーが０になった場合
	if (m_pTimer != nullptr && !m_bGameOver) {
		if (m_pTimer->GetScore() <= 0) {
			//ゲーム終了
			GameOver();
			return;
		}
	}

	if (m_pCheck != nullptr)
	{
		//カウントダウンUIが生成されていたら
		if (m_pCheck->GetCountDownUi() == nullptr)
		{
			//チェックアイコンを消す
			m_pCheck->Uninit();
			m_pCheck = nullptr;
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//生成されていない
		if (m_apPlayerIcon[nCntPlayer] == nullptr) continue;
		//UIが消えていない
		if (m_apPlayerIcon[nCntPlayer]->GetFrame() != nullptr || m_apPlayerIcon[nCntPlayer]->GetPlayerNum() != nullptr) continue;

		//消す
		m_apPlayerIcon[nCntPlayer]->Uninit();
		m_apPlayerIcon[nCntPlayer] = nullptr;
	}

	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//現在の入力デバイスの取得
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;
	//サウンドの取得
	CSound* pSound = pManager->GetSound();
	if (pSound == nullptr) return;
	//フェードの取得
	CFade* pFade = pManager->GetFade();
	if (pFade == nullptr) return;
	//カメラの取得
	CCamera* pCamera = pManager->GetCamera();
	if (pCamera == nullptr) return;

	//ポーズ
	if (pInput->GetTrigger(CInput::CODE::PAUSE, 0) && !pFade->GetFade() && !m_bLockPauseMenu) {
		//ポーズメニューを生成
		CreatePauseMenu();
		//サウンドを再生
		pSound->PlaySound(CSound::SOUND_LABEL::SE_PAUSE_OPEN);
	}

	//カメラの移動
	float fPosPlayerX = 0.0f;	//全プレイヤーの一番距離がある位置
	for (auto pPlayer : m_apPlayer)
	{
		if (pPlayer == nullptr) continue;
		D3DXVECTOR3 posPlayer = pPlayer->GetPos();	//プレイヤーの位置を取得

		//停止可能
		if (posPlayer.x > STOP_POS_MIN) pPlayer->SetCanStop(true);
		//強制停止
		if (posPlayer.x >= STOP_POS_MAX) pPlayer->StopMove();

		//最大の位置を取得
		fPosPlayerX = max(fPosPlayerX, posPlayer.x);
	}

	//カメラの位置更新
	D3DXVECTOR3 posCamera = pCamera->GetPos();
	posCamera.x = fPosPlayerX;
	pCamera->SetPos(posCamera);

	//TODO:ライトの位置も動かす

	//徐々に近づける TODO:カメラを作っていい感じに動くようにする
	pCamera->SetDistance(1000.0f);
}

//=============================================================================
// ゲームオーバー時の更新
//=============================================================================
void CGameScene03::UpdateGameOver(void) {
	m_nCntGameClear++;

	if (m_nCntGameClear > NEXT_SCENE_COUNT)
	{
		m_nCntGameClear = 0;

		CManager* pManager = CManager::GetManager();	//マネージャーの取得
		if (pManager == nullptr) return;
		//フェードの取得
		CFade* pFade = pManager->GetFade();		//フェードへのポインタ
		if (pFade == nullptr) return;

		//リザルトへシーン遷移
		if (GetWereWolfMode()) {
			//人狼モードの場合簡素なリザルト
			pFade->SetFade(CScene::SCENE_TYPE::RESULT, 0.02f, 0);
		}
		//通常モードの場合
		else {
			for (int nIdx = 0; nIdx < MAX_OBJECT_PLAYER_NUM; nIdx++)
			{
				int nScore = 40 - (GetRanking(nIdx) - 1) * 10;	//ランキングを取得してスコアを決定
				//リザルトのスコアを設定
				CFinalResultScene::SetPlayerScore(nScore, nIdx);
			}
			//最終リザルトに遷移
			pFade->SetFade(CScene::SCENE_TYPE::FINAL_RESULT, 0.04f, 0);
		}
	}
}

//=============================================================================
//準備状態中の更新
//=============================================================================
void CGameScene03::UpdateReady(void) {
	//チェック出来ていなかったら
	if (!m_bAllCheck)
	{
		if (m_pCheck == nullptr)
		{
			return;
		}

		if (!m_pCheck->GetUninitAll())
		{
			return;
		}

		//全員がチェック出来たら
		for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
		{
			//プレイヤーアイコンの生成処理
			CreatePlayerIcon(nCntPlayer);
		}
		//全員がチェック出来た状態にする
		m_bAllCheck = true;
	}
	else
	{
		if (m_pCheck == nullptr)
		{
			return;
		}

		if (m_pCheck->GetCountDownUi() == nullptr)
		{
			return;
		}

		//カウントダウンUIが生成されていたら
		//カウントダウンUIの処理
		CountDownUi();
	}
}

//=============================================================================
// ゲームオーバー
//=============================================================================
void CGameScene03::GameOver(void) {
	if (m_bGameOver) return;

	m_bGameOver = true;

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//ゲームオーバー音を再生
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_TIME_UP);


	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//更新しないようにする
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(false);
	}

	//フィニッシュUI生成
	CFinishUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 0, 1.0f);
	for (int nCntFinish = 0; nCntFinish < FINISH_UI_NUM; nCntFinish++)
	{
		CFinishUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), nCntFinish + 1, 0.4f);
	}

	//タイマーを停止
	if (m_pTimer != nullptr) {
		m_pTimer->SetStop(true);
	}

	//ランキング設定処理
	//SetRanking();

	//オブジェクトのポーズが無いように設定（念のため）
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
//プレイヤーアイコン生成処理
//=============================================================================
void CGameScene03::CreatePlayerIcon(int nCntPlayer) {

	//生成されていたら
	if (m_apPlayerIcon[nCntPlayer] != nullptr)
	{
		return;
	}

	//プレイヤーの位置取得
	D3DXVECTOR3 playerPos = m_apPlayer[nCntPlayer]->GetPos();

	if (nCntPlayer < 2)
	{
		playerPos.x += 150.0f;
	}
	else
	{
		playerPos.x -= 150.0f;
	}
	playerPos.z -= 100.0f;

	//アイコンの位置
	D3DXVECTOR3 iconPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ワールド座標からスクリーン座標に変換
	iconPos = WorldToScreen(playerPos);
	iconPos.z = 0.0f;

	int nTexCount = nCntPlayer;

	if (nCntPlayer >= 2)
	{
		nTexCount += 4;
	}

	//生成
	m_apPlayerIcon[nCntPlayer] = CObjectPlayerIcon::Create(iconPos, D3DXVECTOR3(PLAYER_ICON_SCALE, PLAYER_ICON_SCALE, PLAYER_ICON_SCALE),
		CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_ICON_FRAME_1) + nTexCount),
		CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_NUM_WHITE_1) + nCntPlayer));
}

//=============================================================================
//カウントダウンUIの処理
//=============================================================================
void CGameScene03::CountDownUi(void)
{
	//スタート状態ではない場合終了
	if (!m_pCheck->GetCountDownUi()->GetStart()) return;

	//準備状態なら
	if (m_bReady)
	{
		//準備状態を終了する
		m_bReady = false;
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//生成されていたら
		if (m_apPlayer[nCntPlayer] == nullptr)
		{
			continue;
		}

		//更新されている状態なら
		if (m_apPlayer[nCntPlayer]->GetPlayer()->GetUpdate())
		{
			continue;
		}

		//更新されている状態にする
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(true);

		//生成されていたら
		if (m_apPlayerIcon[nCntPlayer] != nullptr)
		{
			//消えるように設定する
			m_apPlayerIcon[nCntPlayer]->SetState(CObjectPlayerIcon::STATE::DEC_ALPHA);
		}
	}
}