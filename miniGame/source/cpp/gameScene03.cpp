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

#define LIGHT_POS_VIEW_V		(D3DXVECTOR3(2000.0f, 4000.0f, -600.0f))	//ライトの視点位置
#define LIGHT_POS_VIEW_R		(D3DXVECTOR3(0.0f, 0.0f, -600.0f))			//ライトの注視点位置

#define FOG_COLOR				(D3DXCOLOR(0.0f, 0.7f, 1.0f, 1.0f))			//フォグの色
#define BACK_BUFF_COLOR			(FOG_COLOR)			//バックバッファーの色

#define PLAYER_ICON_SCALE		(0.18f)		//プレイヤーアイコンのスケール
#define STOP_POS_MIN			(400)		//ストップできる最低の距離
#define STOP_POS_MAX			(999)		//強制ストップされる距離
#define FINISH_UI_NUM			(5)			//フィニッシュUIの数
#define NEXT_SCENE_COUNT		(600)		//次のシーンまでのカウント

#define MIN_SPEED_PLAYER		(25)		//プレイヤーの最低速度
#define MAX_SPEED_PLAYER		(35)		//プレイヤーの最大速度

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGameScene03::CGameScene03()
{
	m_nCntGameOver = 0;
	memset(m_apPlayer, NULL, sizeof(m_apPlayer[MAX_OBJECT_PLAYER_NUM]));
	memset(m_apPlayerIcon, NULL, sizeof(m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM]));
	m_bReady = false;

	m_fPosPlayerMin = STOP_POS_MAX;
	m_fPosPlayerMax = 0.0f;

	m_fPlayerSpeedMax = MAX_SPEED_PLAYER;
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
	CTexture::Load("game03");

	//変数初期化
	m_bReady = true;
	m_fDestPos = 0.0f;
	m_bEndShowDest = false;
	m_bPerfectScore = false;

	//カウントダウンを停止する
	m_bStopCountdown = true;

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

	if (pRenderer != nullptr) {
		//陰描画無効
		//pRenderer->SetEnableShadow(false);
	}

	//------------------------------
	//ライトの初期設定
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ライトの射影変換
	//ライトのプロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 3500.0f, 7000.0f);

	D3DXMATRIX mtxLightView;   // ライトビュー変換
	D3DXVECTOR3 posLightV = LIGHT_POS_VIEW_V;	//ライトの視点の位置
	D3DXVECTOR3 posLightR = LIGHT_POS_VIEW_R;	//ライトの注視点の位置
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
		//バックバッファをフォグの色に合わせる
		pRenderer->SetBackBuffColor(BACK_BUFF_COLOR);
		pRenderer->SetEffectFogColor(FOG_COLOR);
		pRenderer->SetEffectFogRange(2000.0f, 40000.0f);

	}

	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME_02);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME_02);
	}

	//プレイヤーの最大速度を設定
	m_fPlayerSpeedMax = rand() % (MAX_SPEED_PLAYER - MIN_SPEED_PLAYER + 1) + MIN_SPEED_PLAYER;

	//オブジェクトのポーズが無いように設定
	CObject::SetUpdatePauseLevel(0);

	//ゲームシーンの初期化処理
	CGameScene::Init();
}

//=============================================================================
// オブジェクト生成処理
//=============================================================================
void CGameScene03::CreateObject(void) {
	//アイコン生成処理
	CreateIcon();
	//カウントダウン生成不可能
	if (m_pCheck != nullptr) m_pCheck->SetCreateCountDownUi(false);

	//床の生成
	CMeshwall::Create(D3DXVECTOR3(-10000.0f, -5.0f, -0.0f), D3DXVECTOR3(D3DX_PI*0.5f, D3DX_PI*0.5f, 0.0f), 6, 6, 10000.0f, 10000.0f, CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);
	//道路
	CObjectModel::Create(CModel::MODELTYPE::OBJ_ROAD, D3DXVECTOR3(3000.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), false);

	//開始ゲート
	CObjectModel::Create(CModel::MODELTYPE::OBJ_STARTGATE, D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//プレイヤーの生成
		m_apPlayer[nCntPlayer] = CObjplayerStop::Create(D3DXVECTOR3(-300.0f, 0.0f, 500.0f + nCntPlayer * -300.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), m_fPlayerSpeedMax);
		//更新しないようにする
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(false);
	}

	//看板
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		CObjectModel::Create((CModel::MODELTYPE)(int(CModel::MODELTYPE::OBJ_MARK_100m) + nCnt), D3DXVECTOR3(GAME03_ONE_METER * 100 * (nCnt + 1), 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	}

	//ビル
	for (int nCnt = 0; nCnt < 200; nCnt++)
	{
		CModel::MODELTYPE type = CModel::MODELTYPE(rand() % 4 + int(CModel::MODELTYPE::OBJ_BUILDING_00));
		CObjectModel::Create(type, D3DXVECTOR3(1000.0f * nCnt, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	}

	//コーン
	CObjectModel::Create(CModel::MODELTYPE::OBJ_CORN, D3DXVECTOR3(STOP_POS_MAX * GAME03_ONE_METER + 80.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), false);
}

//=============================================================================
// ゲームシーンの終了処理
//=============================================================================
void CGameScene03::Uninit(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();

	if (pRenderer != nullptr) {
		//陰描画有効
		//pRenderer->SetEnableShadow(true);
	}

	//目標位置表示UIの破棄
	if (m_pTomare != nullptr) {
		m_pTomare->Uninit();
		m_pTomare = nullptr;
	}
	if (m_pTomareDist != nullptr) {
		m_pTomareDist->Uninit();
		m_pTomareDist = nullptr;
	}

	//ゲームシーンの終了処理
	CGameScene::Uninit();
}

//=============================================================================
// ゲームシーンの更新処理
//=============================================================================
void CGameScene03::Update(void) {
	//ロードが終了していなかったら
	if (!CTexture::GetLoadFinish()) return;

	//シーンの更新処理
	CScene::Update();

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

		//目標位置の決定
		m_fDestPos = (rand() % 45 + 45) * 10.0f * GAME03_ONE_METER;	//450~890m
		m_nCntShowDist = 0;
		//目指せUIの生成
		m_pTomare = CObject2D::Create(D3DXVECTOR3(900.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::TOMARE, 500.0f, 150.0f);	//目指せUI
		if (m_pTomare != nullptr) {
			m_pTomare->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		//目指せUIの数字の生成
		m_pTomareDist = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_004, D3DXVECTOR3(900.0f - 250.0f, SCREEN_HEIGHT / 2.0f - 75.0f, 0.0f), 150.0f);
		if (m_pTomareDist != nullptr) {
			m_pTomareDist->SetScore((int)(m_fDestPos / GAME03_ONE_METER));
			m_pTomareDist->SetNumberColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
	else
	{
		if (!m_bEndShowDest) {
			//目標距離の表示
			ShowDestDist();
		}
		else {
			//カウントダウンUIの処理
			CountDownUi();
		}
	}
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


	//ポーズ
	if (pInput->GetTrigger(CInput::CODE::PAUSE, 0) && !pFade->GetFade() && !m_bLockPauseMenu) {
		//ポーズメニューを生成
		CreatePauseMenu();
		//サウンドを再生
		pSound->PlaySound(CSound::SOUND_LABEL::SE_PAUSE_OPEN);
	}

	//プレイヤーの位置の監視
	LookPlayerPos();

	//カメラの更新
	UpdateCamera();
	//ライトの更新
	UpdateLight();
}

//=============================================================================
// ゲームオーバー時の更新
//=============================================================================
void CGameScene03::UpdateGameOver(void) {
	m_nCntGameOver++;

	//アイコンの位置調整
	UpdatePlayerIcon();

	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//フェードの取得
	CFade* pFade = pManager->GetFade();		//フェードへのポインタ
	if (pFade == nullptr) return;
	//サウンドの取得
	CSound* pSound = pManager->GetSound();
	if (pSound == nullptr) return;
	//カメラの取得
	CCamera* pCamera = pManager->GetCamera();
	if (pCamera == nullptr) return;

	CGameCamera03* pCamera03 = dynamic_cast<CGameCamera03*>(pCamera);
	//カメラを目標位置まで動かす関数を呼ぶ
	if (m_nCntGameOver == 90) {
		if (pCamera03 != nullptr) pCamera03->SetDestPos(m_fDestPos, 120);
	}

	//カメラが全体を見渡せるような距離まで下がる関数を呼ぶ
	if (m_nCntGameOver == 290)
	{
		if (pCamera03 != nullptr) pCamera03->OverLook(min(m_fPosPlayerMin, m_fDestPos), max(m_fPosPlayerMax, m_fDestPos), 100);
	}

	float afPosUI[MAX_OBJECT_PLAYER_NUM];	//UIの位置
	for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
	{
		if (m_apPlayer[nCnt] == nullptr) continue;
		const float fSpace = 200.0f;	//UIの間隔
		afPosUI[nCnt] = SCREEN_WIDTH / 2.0f - fSpace * 2 + fSpace / 2 + nCnt * fSpace;	//画面真ん中を中心で配置

		//スコアUIの表示
		if (m_nCntGameOver == 300 + nCnt * 30) {
			int nShowScore = m_apPlayer[nCnt]->GetPos().x / GAME03_ONE_METER;	//表示スコア
			m_bPerfectScore = nShowScore == int(m_fDestPos / GAME03_ONE_METER);	//スコア一致

			//スコア表示
			CScore* pDistScore = nullptr;	//スコアのポインタ
			//一致時かどうかで演出変更
			if (m_bPerfectScore) {
				//スコアの生成
				pDistScore = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_006, D3DXVECTOR3(afPosUI[nCnt] + 3 / 2.0f * 30.0f, 600.0f, 0.0f), 30.0f);
				if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DRUM_ROLL_END);	//TODO:完璧なスコアのときの音
			}
			else {
				//スコアの生成
				pDistScore = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_004, D3DXVECTOR3(afPosUI[nCnt] + 3 / 2.0f * 30.0f, 600.0f, 0.0f), 30.0f);
				if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);	//TODO:通常時の音
			}

			if (pDistScore != nullptr) {
				pDistScore->SetScore(nShowScore);	//スコアの設定
			}

			//スコアの背景の設定
			CObject2D* pScoreBG = CObject2D::Create(D3DXVECTOR3(afPosUI[nCnt], 600.0f + 30.0f / 2, 0.0f),
				(CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_TYPE::ITEM_UI_FRAME_1 + nCnt), 100.0f, 40.0f);
			if (pScoreBG != nullptr) pScoreBG->SetDrawPriority(CObject::DRAW_PRIORITY::UI_BG);


		}
	}

	//TODO:スコアの上にWinテキストを乗せる　ランキング一位の場合
	if (m_nCntGameOver == 450) {
		
		for (int nIdx = 0; nIdx < MAX_OBJECT_PLAYER_NUM; nIdx++)
		{
			if (GetRanking(nIdx) != 1) continue;	//ランキング１位以外除外
			//Winテキストの生成
			CObject2D::Create(D3DXVECTOR3(afPosUI[nIdx] + 40.0f, 600.0f + 30.0f / 2 - 20.0f, 0.0f),
				CTexture::TEXTURE_TYPE::WINNER, 100.0f, 40.0f);
		}
		//サウンド再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);
	}

	//次シーン
	if (m_nCntGameOver > NEXT_SCENE_COUNT)
	{
		m_nCntGameOver = 0;

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
	//ライトの更新
	UpdateLight();
}

//=============================================================================
// プレイヤーの位置の監視
//=============================================================================
void CGameScene03::LookPlayerPos(void) {
	//カメラの移動
	bool bStopPlayerAll = true;	//全てのプレイヤーが停止済み
	m_fPosPlayerMin = STOP_POS_MAX * GAME03_ONE_METER;
	m_fPosPlayerMax = 0.0f;
	//全てのプレイヤーの位置を取得
	for (auto pPlayer : m_apPlayer)
	{
		CObjplayerStop* pStopPlayer = dynamic_cast<CObjplayerStop*>(pPlayer);	//このゲームシーンで使うプレイヤーのクラスにダイナミックキャスト
		if (pStopPlayer == nullptr) continue;

		if (!pStopPlayer->GetStopMove()) bStopPlayerAll = false;

		D3DXVECTOR3 posPlayer = pStopPlayer->GetPos();	//プレイヤーの位置を取得

		//停止可能
		if (posPlayer.x > STOP_POS_MIN * GAME03_ONE_METER) pStopPlayer->SetCanStop(true);
		//強制停止
		if (posPlayer.x >= STOP_POS_MAX * GAME03_ONE_METER) {
			//停止
			pStopPlayer->StopMove();
			//位置調整
			posPlayer.x = STOP_POS_MAX * GAME03_ONE_METER;
			pStopPlayer->SetPos(posPlayer);
		}

		//最小の位置を取得
		m_fPosPlayerMin = min(m_fPosPlayerMin, posPlayer.x);
		//最大の位置を取得
		m_fPosPlayerMax = max(m_fPosPlayerMax, posPlayer.x);
	}

	//全てのプレイヤーが停止していた場合
	if (bStopPlayerAll) {
		//ゲーム終了
		GameOver();
		return;
	}

}

//=============================================================================
// カメラの位置の更新
//=============================================================================
void CGameScene03::UpdateCamera(void) {
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//カメラの取得
	CCamera* pCamera = pManager->GetCamera();
	if (pCamera == nullptr) return;

	//カメラの位置更新
	D3DXVECTOR3 posCamera = pCamera->GetPos();
	if (m_fPosPlayerMax > 300.0f) posCamera.x = m_fPosPlayerMax - 300.0f;
	pCamera->SetPos(posCamera);
}

//=============================================================================
// ライトの位置の更新
//=============================================================================
void CGameScene03::UpdateLight(void) {
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;
	//カメラの取得
	CCamera* pCamera = pManager->GetCamera();
	if (pCamera == nullptr) return;

	D3DXMATRIX mtxLightProj;   // ライトの射影変換
	//ライトのプロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 3500.0f, 7000.0f);

	D3DXVECTOR3 posCamera = pCamera->GetPos();
	D3DXMATRIX mtxLightView;   // ライトビュー変換
	D3DXVECTOR3 posLightV = posCamera + LIGHT_POS_VIEW_V;	//ライトの視点の位置
	D3DXVECTOR3 posLightR = posCamera + LIGHT_POS_VIEW_R;	//ライトの注視点の位置
	//ライトのビューマトリックスを生成
	D3DXMatrixLookAtLH(&mtxLightView, &posLightV, &posLightR, &D3DXVECTOR3(0, 0, 1));

	//シェーダのライトを設定
	pRenderer->SetEffectLightMatrixView(mtxLightView);
	pRenderer->SetEffectLightMatrixProj(mtxLightProj);
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

	//ランキングの決定
	DecideRanking();

	//目標位置に目印を置く
	CObjectModel::Create(CModel::MODELTYPE::OBJ_STOP_SIGN, D3DXVECTOR3(m_fDestPos, 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//プレイヤーアイコンの生成処理
		CreatePlayerIcon(nCntPlayer);
	}

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
	//playerPos.x -= 100.0f;
	//playerPos.y -= 10.0f;

	//アイコンの位置
	D3DXVECTOR3 iconPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ワールド座標からスクリーン座標に変換
	iconPos = WorldToScreen(playerPos);
	iconPos.x -= 70.0f;
	iconPos.z = 0.0f;

	//生成
	m_apPlayerIcon[nCntPlayer] = CObjectPlayerIcon::Create(iconPos, D3DXVECTOR3(PLAYER_ICON_SCALE, PLAYER_ICON_SCALE, PLAYER_ICON_SCALE),
		CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_ICON_FRAME_1) + nCntPlayer + 4),
		CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_NUM_WHITE_1) + nCntPlayer));
}

//=============================================================================
// プレイヤーアイコン更新処理
//=============================================================================
void CGameScene03::UpdatePlayerIcon(void) {
	for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
	{
		if (m_apPlayerIcon[nCnt] == nullptr) continue;

		//プレイヤーの位置取得
		D3DXVECTOR3 playerPos = m_apPlayer[nCnt]->GetPos();
		//playerPos.y += 300.0f;

		//アイコンの位置
		D3DXVECTOR3 iconPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//ワールド座標からスクリーン座標に変換
		iconPos = WorldToScreen(playerPos);
		iconPos.y -= 30.0f;
		iconPos.z = 0.0f;

		m_apPlayerIcon[nCnt]->SetPos(iconPos);
	}
}

//=============================================================================
// 目標位置表示
//=============================================================================
void CGameScene03::ShowDestDist(void) {
	if (m_pTomare == nullptr || m_pTomareDist == nullptr) return;

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	m_nCntShowDist++;

	//UI表示
	if (m_nCntShowDist == 60) {
		m_pTomare->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pTomareDist->SetNumberColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//サウンドを再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);
	}

	D3DXCOLOR colUI;	//UIの色
	//色が消えていく
	if (m_nCntShowDist > 180) {
		//透明度を下げる
		colUI = m_pTomare->GetColor();
		colUI.a -= 0.05f;
		//色の変更
		m_pTomare->SetColor(colUI);
		m_pTomareDist->SetNumberColor(colUI);
	}

	//目標位置表示の終了
	if (colUI.a <= 0.0f && m_nCntShowDist > 180) {
		m_bEndShowDest = true;
		//目標位置表示UIの破棄
		m_pTomare->Uninit();
		m_pTomare = nullptr;
		m_pTomareDist->Uninit();
		m_pTomareDist = nullptr;

		//目標位置の背景の生成
		CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 50.0f, 0.0f),
			CTexture::TEXTURE_TYPE::FRAME_DEST, 280.0f, 80.0f);
		//画面上部に目標位置のUIを生成
		CScore* pDistScore = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_004, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 150.0f / 2.0f + 15.0f, 30.0f, 0.0f), 50.0f);
		if (pDistScore != nullptr) pDistScore->SetScore((int)(m_fDestPos / GAME03_ONE_METER));
		//カウントダウン生成可能
		if (m_pCheck != nullptr) m_pCheck->SetCreateCountDownUi(true);
	}
}

//=============================================================================
// カウントダウンUIの処理
//=============================================================================
void CGameScene03::CountDownUi(void)
{
	if (m_pCheck == nullptr) return;
	if (m_pCheck->GetCountDownUi() == nullptr) return;
	
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

//=============================================================================
// プレイヤーの位置からランキングを決定してシーンのランキングに設定する
//=============================================================================
void CGameScene03::DecideRanking(void) {
	std::vector<float> distPlayer(MAX_OBJECT_PLAYER_NUM);	//プレイヤーの進んだ距離
	std::vector<float> sortPlayer(MAX_OBJECT_PLAYER_NUM);	//プレイヤーの進んだ距離のソート

	//全てのプレイヤーの位置を取得
	for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
	{
		CObjplayerStop* pStopPlayer = dynamic_cast<CObjplayerStop*>(m_apPlayer[nCnt]);	//このゲームシーンで使うプレイヤーのクラスにダイナミックキャスト
		if (pStopPlayer == nullptr) continue;

		D3DXVECTOR3 posPlayer = pStopPlayer->GetPos();	//プレイヤーの位置を取得
		sortPlayer[nCnt] = distPlayer[nCnt] = fabs(posPlayer.x - m_fDestPos);	//プレイヤーと目標の位置の差分を取得
	}

	//昇順にソート
	std::sort(sortPlayer.begin(), sortPlayer.end());

	//ランキングを設定
	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		for (int nCntSort = 0; nCntSort < MAX_OBJECT_PLAYER_NUM; nCntSort++)
		{
			if (distPlayer[nCntPlayer] == sortPlayer[nCntSort]) {
				int nRank = nCntSort + 1;
				//ランキング設定
				SetRanking(nRank, nCntPlayer);
				break;
			}
		}
	}
}