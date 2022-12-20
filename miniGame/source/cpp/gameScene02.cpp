//=============================================================================
//
// ゲームシーン02処理 [gameScene02.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "gameScene02.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "gameCamera.h"
#include "fade.h"
#include "timer.h"
#include "object2D.h"
#include "object_player_attack_car.h"
#include "pauseMenu.h"
#include "count_down_ui.h"
#include "finish_ui.h"
#include "player.h"
#include "create_bom_manager.h"
#include "meshwall.h"
#include "float_object.h"
#include "player_icon.h"
#include "ToScreen.h"
#include "check.h"
#include "item_shield.h"
#include "finalResultScene.h"


//エフェクト
#include "plane.h"
#include "PresetSetEffect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GAME_02_TIME							(60)								//ゲームの時間
#define GAME_02_HURRY_UP_TIME					(20)								//ハリーアップの時間

#define GAME_02_FOG_COLOR_SUNNY					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	//フォグの色晴れ
#define GAME_02_FOG_COLOR_CLOUDY				(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))	//フォグの色曇り
#define GAME_02_BACK_BUFF_COLOR_SUNNY			(D3DXCOLOR(0.1f, 0.3f, 0.5f, 1.0f))	//バックバッファーの色晴れ
#define GAME_02_BACK_BUFF_COLOR_CLOUDY			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))	//バックバッファーの色曇り

#define GAME_02_PLAYER_ICON_SCALE				(0.35f)								//プレイヤーアイコンのスケール

#define GAME_02_PLAYER_INIT_CREATE_SPACE		(300.0f)							//プレイヤーの初期生成間隔
#define GAME_02_PLAYER_INIT_CREATE_POS_Z		(-400.0f)							//プレイヤーの初期生成位置Z

#define GAME_02_FINISH_UI_NUM		(5)			//フィニッシュUIの数

#define GAME_02_NEX_SCENE_COUNT		(240)		//次のシーンまでのカウント

#define GAME_02_BOM_CREATE_COUNT	(30)		//ボムを生成する間隔
#define GAME_02_BOM_NUM				(1)			//ボムを生成する個数

#define GAME_02_CLOUD_NUM					(1)											//雲の数
#define GAME_02_CLOUD_POS					(D3DXVECTOR3(0.0f, -1500.0f, -6000.0f))		//雲の位置
#define GAME_02_CLOUD_SIZE					(12000.0f)									//雲のサイズ
#define GAME_02_CLOUD_MESH_NUM				(8)											//メッシュを敷き詰める数
#define GAME_02_CLOUD_MOVE_SPEED			(0.00035f)									//テクスチャを動かす速さ
#define GAME_02_CLOUD_MOVE_SPEED_INTERVAL	(0.00025f)									//次の雲のテクスチャを動かす速さの間隔
#define GAME_02_CLOUD_COLOR					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			//雲の色

#define GAME_02_ITEM_SPAWN_COUNT			(60 * 6)						//アイテムの生成間隔
#define GAME_02_ITEM_SPAWN_DIFFER_MAX		(GAME_02_STAGE_SIZE - 100.0f)	//ステージ中央からどれだけ離れた位置にアイテムを生成するか最大値
#define GAME_02_ITEM_SPAWN_POS_Y			(1000.0f)						//アイテムの生成位置Y


//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGameScene02::CGameScene02()
{
	m_nCntGameClear = 0;
	memset(m_apPlayer, NULL, sizeof(m_apPlayer[MAX_OBJECT_PLAYER_NUM]));
	memset(m_apPlayerIcon, NULL, sizeof(m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM]));
	m_bHurryUp = false;
	m_bReady = false;
	m_pCreateBomManager = nullptr;
	m_pCloud.clear();
	m_weatherState = WEATHER_STATE::CLOUDY;
	m_nSavePlayerNum = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameScene02::~CGameScene02()
{

}

//=============================================================================
// ゲームシーンの初期化処理
//=============================================================================
void CGameScene02::Init(void) {
	//テクスチャのロード
	CTexture::Load("game02");

	//変数初期化
	m_bHurryUp = false;
	m_pCreateBomManager = nullptr;
	m_weatherState = WEATHER_STATE::CLOUDY;
	m_bReady = true;
	m_nSavePlayerNum = MAX_OBJECT_PLAYER_NUM;

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//カメラの設定
	if (pManager != nullptr) pManager->SetCamera(CGameCamera::Create());

	//------------------------------
	//ライトの初期設定
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ライトの射影変換
	//ライトのプロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 1500.0f, 3000.0f);

	D3DXMATRIX mtxLightView;   // ライトビュー変換
	D3DXVECTOR3 posLightV = D3DXVECTOR3(800.0f, 2000.0f, -800.0f);	//ライトの視点の位置	D3DXVECTOR3(600.0f, 1500.0f, -2000.0f);
	D3DXVECTOR3 posLightR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//ライトの注視点の位置
	D3DXVECTOR3 vecLight = -D3DXVECTOR3(posLightV - posLightR);	//ライトのベクトル
	D3DXVec3Normalize(&vecLight, &vecLight);	//ベクトルを正規化
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

		//ランダムで状態を指定
		m_weatherState = WEATHER_STATE(rand() % (int)WEATHER_STATE::MAX);

		switch (m_weatherState)
		{
		case CGameScene02::WEATHER_STATE::CLOUDY:
			fogColor = GAME_02_FOG_COLOR_CLOUDY;
			backBuffColor = GAME_02_BACK_BUFF_COLOR_CLOUDY;
			break;
		case CGameScene02::WEATHER_STATE::SUNNY:
			fogColor = GAME_02_FOG_COLOR_SUNNY;
			backBuffColor = GAME_02_BACK_BUFF_COLOR_SUNNY;
			break;
		default:
			break;
		}

		//バックバッファをフォグの色に合わせる
		pRenderer->SetBackBuffColor(backBuffColor);
		pRenderer->SetEffectFogColor(fogColor);
		pRenderer->SetEffectFogRange(20.0f, 10000.0f);
		
	}

	//オブジェクトのポーズが無いように設定
	CObject::SetUpdatePauseLevel(0);

	
	
	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME_02);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME_02);
	}

	//ゲームシーンの初期化処理
	CGameScene::Init();
}

//=============================================================================
//オブジェクト生成処理
//=============================================================================
void CGameScene02::CreateObject(void)
{
	//アイコン生成処理
	CreateIcon();

	//スタジアムの生成
	CObjectModel::Create(CModel::MODELTYPE::OBJ_ATTACK_CAR_STAGE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//門の生成
	CFloatObject::Create(D3DXVECTOR3(1800.0f, -200.0f, 1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(-0.001f, -0.003f, 0.002f), CModel::MODELTYPE::OBJ_BROKEN_GATE);

	//塔の生成
	CFloatObject::Create(D3DXVECTOR3(-1900.0f, -700.0f, 2500.0f), D3DXVECTOR3(-0.3f, 0.0f, -0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0f, 0.004f, 0.0f), CModel::MODELTYPE::OBJ_BROKEN_TOWER);

	//車の生成
	CFloatObject::Create(D3DXVECTOR3(-1900.0f, -500.0f, 2500.0f), D3DXVECTOR3(0.1f, 0.0f, -0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0030f, -0.004f, 0.0f), CModel::MODELTYPE::OBJ_CAR);

	CFloatObject::Create(D3DXVECTOR3(1300.0f, -800.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.001f, -0.001f, 0.0014f), CModel::MODELTYPE::OBJ_CAR);

	//がれきの生成
	//奥のがれき
	CFloatObject::Create(D3DXVECTOR3(-1000.0f, -500.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.001f, -0.002f, 0.005f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_02);

	CFloatObject::Create(D3DXVECTOR3(-300.0f, -500.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0f, 0.001f, -0.003f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_03);

	CFloatObject::Create(D3DXVECTOR3(300.0f, -500.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0005f, 0.002f, 0.009f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_04);

	CFloatObject::Create(D3DXVECTOR3(1000.0f, -500.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(-0.0005f, -0.001f, -0.001f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_05);

	CFloatObject::Create(D3DXVECTOR3(1500.0f, -500.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0025f, 0.0f, 0.001f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_06);

	//手前のがれき
	CFloatObject::Create(D3DXVECTOR3(-1000.0f, -800.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0005f, -0.001f, 0.0f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_01);

	CFloatObject::Create(D3DXVECTOR3(1000.0f, -800.0f, -300.0f), D3DXVECTOR3(1.0f, -0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(-0.0001f, 0.0008f, 0.0f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_06); 

	CFloatObject::Create(D3DXVECTOR3(1200.0f, -500.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 1.2f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(-0.0008f, 0.0008f, 0.0f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_03);

	CFloatObject::Create(D3DXVECTOR3(-1400.0f, -500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.3f, -1.2f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                 D3DXVECTOR3(0.0016f, -0.0005f, -0.001f), CModel::MODELTYPE::OBJ_BROKEN_TOWER_FRAGMENT_05);

	//雲の生成
	for (int nCntCloud = 0; nCntCloud < GAME_02_CLOUD_NUM; nCntCloud++)
	{
		m_pCloud.push_back(CMeshwall::Create(GAME_02_CLOUD_POS, D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f),
			                                 GAME_02_CLOUD_MESH_NUM, GAME_02_CLOUD_MESH_NUM, GAME_02_CLOUD_SIZE, GAME_02_CLOUD_SIZE,
			                                 CTexture::TEXTURE_TYPE::MESH_CLOUD));
		//加算合成をする
		m_pCloud[nCntCloud]->SetAlphaBlend(true);
		//描画順の設定
		m_pCloud[nCntCloud]->SetDrawPriority(CObject::DRAW_PRIORITY::CLEAR);
		//ライトをオフにする
		m_pCloud[nCntCloud]->SetLight(false);
		//色の設定
		m_pCloud[nCntCloud]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	}

	//プレイヤーの生成
	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, D3DX_PI / 2.0f * nCntPlayer + D3DX_PI / 4.0f, 0.0f);

		if (rot.y > D3DX_PI)
		{
			rot.y -= D3DX_PI * 2.0f;
		}
		else if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2.0f;
		}

		m_apPlayer[nCntPlayer] = CObjectPlayerAttackCar::Create(D3DXVECTOR3(sinf(D3DX_PI / 2.0f * nCntPlayer + D3DX_PI / 4.0f) * 500.0f,
			                                                                0.0f, 
			                                                                cosf(D3DX_PI / 2.0f * nCntPlayer + D3DX_PI / 4.0f) * 500.0f), rot);
		//シーンのプレイヤーの設定
		SetPlayer(m_apPlayer[nCntPlayer]);

		//更新しないようにする
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(false);
	}
}

//=============================================================================
// ゲームシーンの終了処理
//=============================================================================
void CGameScene02::Uninit(void) {

	//ゲームシーンの終了処理
	CGameScene::Uninit();
}

//=============================================================================
// ゲームシーンの更新処理
//=============================================================================
void CGameScene02::Update(void) {
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

	//タイム追加
	if (pInput->GetTrigger(CInput::CODE::DEBUG_3, 0)) {
		if (m_pTimer != nullptr) m_pTimer->AddScore(50);
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

	//雲の処理
	Cloud();

	//ゲームシーンの更新処理
	CGameScene::Update();
}

//=============================================================================
// ゲーム中の更新
//=============================================================================
void CGameScene02::UpdateGame(void) {
	//ポーズメニューがある場合は更新なし
	if (m_pMenuPause != nullptr) return;

	//終了するか確認処理
	if (Finish())
	{
		return;
	}

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
		//生成されていたら
		if (m_apPlayerIcon[nCntPlayer] != nullptr)
		{
			//UIが消えていたら
			if (m_apPlayerIcon[nCntPlayer]->GetFrame() == nullptr && m_apPlayerIcon[nCntPlayer]->GetPlayerNum() == nullptr)
			{
				//消す
				m_apPlayerIcon[nCntPlayer]->Uninit();
				m_apPlayerIcon[nCntPlayer] = nullptr;
			}
		}
	}

	//タイマーが生成されていたら
	if (m_pTimer != nullptr)
	{
		if (m_pTimer->GetScore() == GAME_02_HURRY_UP_TIME)
		{
			//急ぐ状態でないなら
			if (!m_bHurryUp)
			{
				//急ぐ状態にする
				m_bHurryUp = true;
				//急ぐ処理
				HurryUp();
			}
		}
	}

	//アイテムの生成
	CreateItem();

	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//現在の入力デバイスの取得
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;
	//サウンドの取得
	CSound* pSound = pManager->GetSound();	//サウンドへのポインタ
	if (pSound == nullptr) return;
	//フェードの取得
	CFade* pFade = pManager->GetFade();	//フェードのポインタ
	if (pFade == nullptr) return;

	//ポーズ
	if (pInput->GetTrigger(CInput::CODE::PAUSE, 0) && !pFade->GetFade() && !m_bLockPauseMenu) {
		//ポーズメニューを生成
		CreatePauseMenu();
		//サウンドを再生
		pSound->PlaySound(CSound::SOUND_LABEL::SE_PAUSE_OPEN);
	}
}

//=============================================================================
// ゲームオーバー時の更新
//=============================================================================
void CGameScene02::UpdateGameOver(void) {
	m_nCntGameClear++;

	if (m_nCntGameClear > GAME_02_NEX_SCENE_COUNT)
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
			pFade->SetFade(CScene::SCENE_TYPE::RESULT, 40, 0);
		}
		//通常モードの場合
		else {
			for (int nIdx = 0; nIdx < MAX_OBJECT_PLAYER_NUM; nIdx++)
			{
				int nScore = 40 - (GetRanking(nIdx) - 1)*10;	//ランキングを取得してスコアを決定
				//リザルトのスコアを設定
				CFinalResultScene::SetPlayerScore(nScore, nIdx);
			}
			//最終リザルトに遷移
			pFade->SetFade(CScene::SCENE_TYPE::FINAL_RESULT, 40, 0);
		}
	}
}

//=============================================================================
//準備状態中の更新
//=============================================================================
void CGameScene02::UpdateReady(void) {
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
void CGameScene02::GameOver(void) {
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
	for (int nCntFinish = 0; nCntFinish < GAME_02_FINISH_UI_NUM; nCntFinish++)
	{
		CFinishUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), nCntFinish + 1, 0.4f);
	}

	//タイマーを停止
	if (m_pTimer != nullptr) {
		m_pTimer->SetStop(true);
	}

	//ボムを消す
	if (m_pCreateBomManager != nullptr)
	{
		m_pCreateBomManager->Uninit();
		m_pCreateBomManager = nullptr;
	}

	//ランキング設定処理
	SetRanking();

	//オブジェクトのポーズが無いように設定（念のため）
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
//プレイヤーアイコン生成処理
//=============================================================================
void CGameScene02::CreatePlayerIcon(int nCntPlayer){

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
	m_apPlayerIcon[nCntPlayer] = CObjectPlayerIcon::Create(iconPos, D3DXVECTOR3(GAME_02_PLAYER_ICON_SCALE, GAME_02_PLAYER_ICON_SCALE, GAME_02_PLAYER_ICON_SCALE),
		                                                   CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_ICON_FRAME_1) + nTexCount),
													       CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_NUM_WHITE_1) + nCntPlayer));
}

//=============================================================================
//カウントダウンUIの処理
//=============================================================================
void CGameScene02::CountDownUi(void)
{
	//スタート状態なら
	if (m_pCheck->GetCountDownUi()->GetStart())
	{
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

		//生成されていなかったら
		if (m_pTimerFrame == nullptr)
		{
			//タイマーの生成
			m_pTimerFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 61.0f, 0.0f), CTexture::TEXTURE_TYPE::TIMER_FRAME, 220.0f, 80.0f);
			m_pTimer = CTimer::Create(GAME_02_TIME, 2, CTexture::TEXTURE_TYPE::NUMBER_003, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 75.0f, 40.0f, 0.0f), 50.0f);
		}
	}
}

//=============================================================================
//フィニッシュするか確認処理
//=============================================================================
bool CGameScene02::Finish(void)
{
	//ゲームオーバー状態なら
	if (m_bGameOver)
	{
		return false;
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//生成されてなかったら
		if (m_apPlayer[nCntPlayer] == nullptr)
		{
			continue;
		}

		//生き残っている人が2人以上いたら
		if (GetSavePlayerNum() > 1)
		{
			continue;
		}

		//ゲーム終了
		GameOver();
	}
	return false;
}

//=============================================================================
//急げ処理
//=============================================================================
void CGameScene02::HurryUp(void)
{
	//ボム生成処理
	if (m_pCreateBomManager == nullptr)
	{
		m_pCreateBomManager = CCreateBomManager::Create(GAME_02_BOM_CREATE_COUNT, GAME_02_BOM_NUM);
	}
}

//=============================================================================
//雲の処理
//=============================================================================
void CGameScene02::Cloud(void)
{
	for (int nCntCloud = 0; nCntCloud < GAME_02_CLOUD_NUM; nCntCloud++)
	{
		if (m_pCloud[nCntCloud] == nullptr)
		{
			continue;
		}

		//テクスチャ座標移動処理
		m_pCloud[nCntCloud]->SetMoveTex(GAME_02_CLOUD_MOVE_SPEED + GAME_02_CLOUD_MOVE_SPEED_INTERVAL * nCntCloud, 0.0f);
	}
}

//=============================================================================
//アイテム生成処理
//=============================================================================
void CGameScene02::CreateItem()
{
	m_nItemCounter++;

	if (m_nItemCounter > GAME_02_ITEM_SPAWN_COUNT)
	{
		m_nItemCounter = 0;

		//向きをランダムで決める
		float fRot = (rand() % 629 + -314) / 100.0f;
		//遠さをランダムで決める
		float fDiffer = (rand() % (int)(GAME_02_ITEM_SPAWN_DIFFER_MAX) * 100.0f) / 100.0f;

		//出す位置
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, GAME_02_ITEM_SPAWN_POS_Y, 0.0f);

		//決めた位置に出す
		pos.x = sinf(fRot) * fDiffer;
		pos.z = cosf(fRot) * fDiffer;

		//アイテムの生成
		CItemShield::Create(pos);
	}
}

//=============================================================================
//ランキング設定処理
//=============================================================================
void CGameScene02::SetRanking()
{
	for (int nCntSavePlayer = 0; nCntSavePlayer < MAX_OBJECT_PLAYER_NUM; nCntSavePlayer++)
	{
		//残った人をランキング1位にする
		if (GetRanking(nCntSavePlayer) != 0)
		{
			continue;
		}

		//ランキング設定処理
		CGameScene::SetRanking(1, nCntSavePlayer);
	}
}
