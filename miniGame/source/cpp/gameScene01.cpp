//=============================================================================
//
// ゲームシーン01処理 [gameScene01.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include <functional>		//比較用
#include "gameScene01.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "gameCamera.h"
#include "fade.h"
#include "timer.h"
#include "object2D.h"
#include "object_player_balloon_car.h"
#include "meshwall.h"
#include "wallCylinder.h"
#include "pauseMenu.h"
#include "balloon.h"
#include "itemBox.h"
#include "count_down_ui.h"
#include "finish_ui.h"
#include "player.h"
#include "float_object.h"
#include "score.h"
#include "score_ui.h"
#include "finalResultScene.h"

//エフェクト
#include "plane.h"
#include "PresetSetEffect.h"

#include "player_icon.h"
#include "ToScreen.h"
#include "check.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GAME_TIME								 (60)									//ゲームの時間
#define GAME_CREATE_ITEMBOX_TIME				 (60)									//アイテムを生成し始める時間	

#define FOG_COLOR								 (D3DXCOLOR(0.1f, 0.0f, 0.2f, 1.0f))	//フォグの色
#define FOG_COLOR_GAMECLEAR					     (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	//フォグの色

#define GAME_STAGE_SIZE							 (700.0f)								//すてーじの大きさ
#define GAME_PLAYER_ICON_SCALE					 (0.35f)								//プレイヤーアイコンのスケール

#define GAME_PLAYER_INIT_CREATE_SPACE			 (300.0f)								//プレイヤーの初期生成間隔
#define GAME_PLAYER_INIT_CREATE_POS_Z			 (-400.0f)								//プレイヤーの初期生成位置Z

#define GAME_BALLOON_CREATE_POS_Y				 (15.0f)								//風船の位置Y
#define GAME_BALLOON_CREATE_DIFFER				 (600.0f)								//風船の生成する範囲の半径
#define GAME_BALLOON_CREATE_DIFFER_WERE_WOLF_MAX (350.0f)								//風船の生成する嘘つきプレイヤーからの範囲の半径最大値
#define GAME_BALLOON_CREATE_DIFFER_WERE_WOLF_MIN (300.0f)								//風船の生成する嘘つきプレイヤーからの範囲の半径最小値
#define GAME_BALLOON_TO_BALLOON_DIFFER			 (250.0f)								//風船から風船までの距離
#define GAME_BALLOON_TO_PLAYER_DIFFER			 (150.0f)								//プレイヤーからどれくらい離れた位置に生成するか
#define GAME_BALLOON_INIT_CREATE_SPACE			 (400.0f)								//風船の初期生成間隔
#define GAME_BALLOON_INIT_CREATE_POS_Z			 (200.0f)								//風船の初期生成位置Z

#define GAME_ITEM_BOX_CREATE_INTERVAL			 (140)									//アイテムボックスの生成間隔
#define GAME_ITEM_BOX_CREATE_POS_X				 (900.0f)								//アイテムボックスの生成位置X
#define GAME_ITEM_BOX_CREATE_POS_Z				 (float (rand() % 1001 + -500))			//アイテムボックスの生成位置Z

#define GAME_FINISH_UI_NUM						 (5)									//フィニッシュUIの数

#define GAME_NEX_SCENE_COUNT					 (180)									//次のシーンまでのカウント

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGameScene01::CGameScene01()
{
	m_nCntGameClear = 0;
	m_nCreateItemBoxCounter = 0;
	memset(m_apPlayer, NULL, sizeof(m_apPlayer[MAX_OBJECT_PLAYER_NUM]));
	memset(m_apPlayerIcon, NULL, sizeof(m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM]));
	m_bReady = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameScene01::~CGameScene01()
{

}

//=============================================================================
// ゲームシーンの初期化処理
//=============================================================================
void CGameScene01::Init(void) {
	//テクスチャのロード
	CTexture::Load("game01");

	//変数初期化
	m_nCreateItemBoxCounter = GAME_ITEM_BOX_CREATE_INTERVAL;
	m_bReady = true;

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
	D3DXVECTOR3 posLightV = D3DXVECTOR3(1000.0f, 2000.0f, -1000.0f);	//ライトの視点の位置	D3DXVECTOR3(600.0f, 1500.0f, -2000.0f);
	D3DXVECTOR3 posLightR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//ライトの注視点の位置
	D3DXVECTOR3 vecLight = -D3DXVECTOR3(posLightV - posLightR);	//ライトのベクトル
	D3DXVec3Normalize(&vecLight, &vecLight);	//ベクトルを正規化
	//ライトのビューマトリックスを生成
	D3DXMatrixLookAtLH(&mtxLightView, &posLightV, &posLightR, &D3DXVECTOR3(0, 0, 1));
	//シェーダのライトを設定する
	if (pRenderer != nullptr) {
		pRenderer->SetEffectLightMatrixView(mtxLightView);
		pRenderer->SetEffectLightVector(D3DXVECTOR4(vecLight, 1.0f));
		pRenderer->SetEffectLightMatrixProj(mtxLightProj);
	}

	//------------------------------
	//フォグの初期設定
	//------------------------------
	if (pRenderer != nullptr) {
		pRenderer->SetEffectFogEnable(false);
		pRenderer->SetEffectFogColor(FOG_COLOR);
		pRenderer->SetEffectFogRange(800.0f, 4500.0f);
		//バックバッファをフォグの色に合わせる
		pRenderer->SetBackBuffColor(FOG_COLOR);
	}

	//オブジェクトのポーズが無いように設定
	CObject::SetUpdatePauseLevel(0);

	

	////プレイヤーのステンシルに描画されるシルエット
	//CObject2D* pSilhouettePlayer = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, SCREEN_WIDTH, SCREEN_HEIGHT);
	//if (pSilhouettePlayer != nullptr) {
	//	pSilhouettePlayer->SetColor(D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	//	pSilhouettePlayer->SetEnableStencil(true);
	//	pSilhouettePlayer->SetDrawPriority(CObject::DRAW_PRIORITY::UI_BG);
	//}

	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME);
	}
	//ゲームシーンの初期化処理
	CGameScene::Init();
}

//=============================================================================
//オブジェクト生成処理
//=============================================================================
void CGameScene01::CreateObject(void)
{
	//アイコン生成処理
	CreateIcon();

	//床の生成
	CMeshwall::Create(D3DXVECTOR3(0.0f, 0.0f, -1500.0f), D3DXVECTOR3(D3DX_PI*0.5f, 0.0f, 0.0f), 4, 4, 1000.0f, 1000.0f, CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);

	//スタジアムの生成
	CObjectModel::Create(CModel::MODELTYPE::OBJ_STADIUM, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//円柱の壁の生成
	CMeshcylinder* pWall = CWallCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), GAME_STAGE_SIZE, 40.0f, CTexture::TEXTURE_TYPE::MESH_STAGE_WALL, false);
	if (pWall != nullptr) {
		pWall->SetMaterialSpecular(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	pWall = CMeshcylinder::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, GAME_STAGE_SIZE, GAME_STAGE_SIZE + 50.0f, 1, 0.0f, true, CTexture::TEXTURE_TYPE::MESH_STAGE_WALL);
	if (pWall != nullptr) {
		pWall->SetMaterialSpecular(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	pWall = CMeshcylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, GAME_STAGE_SIZE + 50.0f, GAME_STAGE_SIZE + 50.0f, 1, 40.0f, true, CTexture::TEXTURE_TYPE::MESH_STAGE_WALL);
	if (pWall != nullptr) {
		pWall->SetMaterialSpecular(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//風船を生成する
	for (int nCntBalloon = 0; nCntBalloon < BALLOON_MAX_NUM; nCntBalloon++)
	{
		CBalloon::Create(false, D3DXVECTOR3(-GAME_BALLOON_INIT_CREATE_SPACE + GAME_BALLOON_INIT_CREATE_SPACE * nCntBalloon,
			                                GAME_BALLOON_CREATE_POS_Y,
			                                GAME_BALLOON_INIT_CREATE_POS_Z));
	}

	//プレイヤーの生成
	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		m_apPlayer[nCntPlayer] = CObjectPlayerBalloonCar::Create(D3DXVECTOR3(-GAME_PLAYER_INIT_CREATE_SPACE * (MAX_OBJECT_PLAYER_NUM / 2.5f) + GAME_PLAYER_INIT_CREATE_SPACE * nCntPlayer,
												                 0.0f,
												                 GAME_PLAYER_INIT_CREATE_POS_Z));
		//シーンのプレイヤーの設定
		SetPlayer(m_apPlayer[nCntPlayer]);

		//更新しないようにする
		m_apPlayer[nCntPlayer]->GetPlayer()->SetUpdate(false);
	}
}

//=============================================================================
// ゲームシーンの終了処理
//=============================================================================
void CGameScene01::Uninit(void) {
	//ゲームシーンの終了処理
	CGameScene::Uninit();
}

//=============================================================================
// ゲームシーンの更新処理
//=============================================================================
void CGameScene01::Update(void) {
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

	//ゲームシーンの更新処理
	CGameScene::Update();
}

//=============================================================================
// ゲーム中の更新
//=============================================================================
void CGameScene01::UpdateGame(void) {
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

	//風船の生成
	CreateBalloon();

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

	//タイマーが生成されていたら
	if (m_pTimer != nullptr)
	{
		if (m_pTimer->GetScore() <= GAME_CREATE_ITEMBOX_TIME)
		{
			//アイテムボックスの生成
			CreateItemBox();
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
void CGameScene01::UpdateGameOver(void) {
	m_nCntGameClear++;

	if (m_nCntGameClear > GAME_NEX_SCENE_COUNT)
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
				int nScore = 40 - (GetRanking(nIdx) - 1)*10;	//ランキングを取得してスコアを決定
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
void CGameScene01::UpdateReady(void){
	//チェック出来ていなかったら
	if (!m_bAllCheck)
	{
		if (m_pCheck != nullptr)
		{
			//全員がチェック出来たら
			if (m_pCheck->GetUninitAll())
			{
				for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
				{
					//プレイヤーアイコンの生成処理
					CreatePlayerIcon(nCntPlayer);
				}
				//全員がチェック出来た状態にする
				m_bAllCheck = true;
			}
		}
	}
	else
	{
		if (m_pCheck != nullptr)
		{
			//カウントダウンUIが生成されていたら
			if (m_pCheck->GetCountDownUi() != nullptr)
			{
				//カウントダウンUIの処理
				CountDownUi();
			}
		}
	}
}

//=============================================================================
// ゲームオーバー
//=============================================================================
void CGameScene01::GameOver(void) {
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
	for (int nCntFinish = 0; nCntFinish < GAME_FINISH_UI_NUM; nCntFinish++)
	{
		CFinishUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), nCntFinish + 1, 0.4f);
	}

	//タイマーを停止
	if (m_pTimer != nullptr) {
		m_pTimer->SetStop(true);
	}

	//オブジェクトのポーズが無いように設定（念のため）
	CObject::SetUpdatePauseLevel(0);

	//ランキング設定処理
	SetRanking();
}

//=============================================================================
//風船生成処理
//=============================================================================
void CGameScene01::CreateBalloon(void)
{
	//風船の数が0なら
	if (CBalloon::GetNum() == 0)
	{
		std::vector<D3DXVECTOR3> playerPos;
		playerPos.clear();

		for (int nCntPlayer = 0; nCntPlayer < CPlayer::GetNum(); nCntPlayer++)
		{
			playerPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}

		CObject* pObject = CObject::GetObjectTopAll();	//全オブジェクトのリストの先頭を取得

		while (pObject != nullptr) {
			CObject* pObjNext = CObject::GetObjectNextAll(pObject);	//リストの次のオブジェクトのポインタを取得

			//オブジェクトタイプの確認
			bool bMatchType = false;
			if (pObject->GetObjType() & CObject::OBJTYPE_PLAYER) bMatchType = true;

			if (!bMatchType)
			{
				pObject = pObjNext;	//リストの次のオブジェクトを代入
				continue;
			}

			//プレイヤーにキャスト
			CObjectPlayer *pPlayer = static_cast<CObjectPlayer*> (pObject);

			//プレイヤーの位置を取得
			playerPos[pPlayer->GetPlayer()->GetIndex() - 1] = pPlayer->GetPos();

			pObject = pObjNext;	//リストの次のオブジェクトを代入
		}

		D3DXVECTOR3 createBalloonPos[BALLOON_MAX_NUM];

		for (int nCntBalloon = 0; nCntBalloon < BALLOON_MAX_NUM; nCntBalloon++)
		{
			//位置
			D3DXVECTOR3 balloonPos = { 0.0f, GAME_BALLOON_CREATE_POS_Y, 0.0f };
			//中心からの遠さ
			float fDiffer = 0.0f;
			//位置を変えるための向き
			float fRot = 0.0f;

			bool bLoop = true;

			//かぶらなくなるまで回す
			while (bLoop)
			{
				//向きをランダムで決める
				fRot = (rand() % 629 + -314) / 100.0f;

				//原点
				D3DXVECTOR3 originPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//最初だけ人狼モードがオンなら
				if (nCntBalloon == 0 && GetWereWolfMode())
				{
					fDiffer = (rand() % ((int((GAME_BALLOON_CREATE_DIFFER_WERE_WOLF_MAX - GAME_BALLOON_CREATE_DIFFER_WERE_WOLF_MIN) * 100.0f))) +
						                 (int(GAME_BALLOON_CREATE_DIFFER_WERE_WOLF_MIN * 100.0f))) / 100.0f;
					originPos = playerPos[GetWereWolfPlayerIndex() - 1];
				}
				else
				{
					//遠さをランダムで決める
					fDiffer = (rand() % (int)(GAME_BALLOON_CREATE_DIFFER) * 100.0f) / 100.0f;
				}

				//決めた位置に出す
				balloonPos.x = originPos.x + sinf(fRot) * fDiffer;
				balloonPos.z = originPos.z + cosf(fRot) * fDiffer;

				//クリアした条件の数
				int nClearCount = 0;

				//すでに生成されている分だけ回す
				for (int nCntCreateBalloon = 0; nCntCreateBalloon < nCntBalloon; nCntCreateBalloon++)
				{
					//今生成しようとしている風船からすでに生成した風船までの距離ベクトルを求める
					D3DXVECTOR2 differVec = D3DXVECTOR2(balloonPos.x - createBalloonPos[nCntCreateBalloon].x,
						                                balloonPos.z - createBalloonPos[nCntCreateBalloon].z);
					//距離ベクトルから距離を算出
					float fCreateBalloonDiffer = D3DXVec2Length(&differVec);

					//風船1個分以上間が空いていたら
					if (fCreateBalloonDiffer > GAME_BALLOON_TO_BALLOON_DIFFER)
					{
						//クリアした数を増やす
						nClearCount++;
					}
					else
					{
						break;
					}
				}

				//クリア数が条件を回した数と一致していたら
				if (nClearCount == nCntBalloon)
				{
					for (int nCntPlayer = 0; nCntPlayer < CPlayer::GetNum(); nCntPlayer++)
					{
						//今生成しようとしている風船からプレイヤーまでの距離ベクトルを求める
						D3DXVECTOR2 differPlayerVec = D3DXVECTOR2(balloonPos.x - playerPos[nCntPlayer].x,
														          balloonPos.z - playerPos[nCntPlayer].z);
						//距離ベクトルから距離を算出
						float fToOlayerDiffer = D3DXVec2Length(&differPlayerVec);

						//既定分間が空いていたら
						if (fToOlayerDiffer > GAME_BALLOON_TO_PLAYER_DIFFER)
						{
							//クリアした数を増やす
							nClearCount++;
						}
						else
						{
							break;
						}
					}

					//クリア数が条件を回した数と一致していたら
					if (nClearCount == nCntBalloon + CPlayer::GetNum())
					{
						//ループ終了
						bLoop = false;

						//最初だけ人狼モードがオンなら
						if (nCntBalloon == 0 && GetWereWolfMode())
						{
							//今生成しようとしている風船から中央までのベクトルを求める
							D3DXVECTOR2 baloonOriginDifferVec = D3DXVECTOR2(balloonPos.x - 0.0f, balloonPos.z - 0.0f);
							//距離ベクトルから距離を算出
							float fBaloonOriginDiffer = D3DXVec2Length(&baloonOriginDifferVec);

							//ステージからはみ出てたら
							if (fBaloonOriginDiffer > GAME_BALLOON_CREATE_DIFFER)
							{
								//ループさせる
								bLoop = true;
							}
							else
							{
								bLoop = false;
							}
						}
					}
				}
			}

			//生成できた風船の位置を保存
			createBalloonPos[nCntBalloon] = balloonPos;

			//ゴールドかどうか
			bool bGold = false;

			//最初だけ
			if (nCntBalloon == 0)
			{
				//金にする
				bGold = true;
			}

			//風船を生成する
			CBalloon::Create(bGold, balloonPos);

			//ーーーーーーーーーーーーーーーーーーー
			//風船出現エフェクト
			CPresetEffect::SetEffect3D(5, D3DXVECTOR3(balloonPos.x, balloonPos.y + 130, balloonPos.z - 90), {}, {});		//デカ円
			CPresetEffect::SetEffect3D(6, D3DXVECTOR3(balloonPos.x, balloonPos.y + 140, balloonPos.z - 90), {}, {});		//回ってる塵
			//ーーーーーーーーーーーーーーーーーーー

		}

		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		//サウンドの取得
		CSound *pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_BALLOON_SPAWN);
	}
}

//=============================================================================
// アイテムボックス生成処理
//=============================================================================
void CGameScene01::CreateItemBox(void){
	m_nCreateItemBoxCounter++;
	//一定の値になったら
	if (m_nCreateItemBoxCounter > GAME_ITEM_BOX_CREATE_INTERVAL)
	{
		m_nCreateItemBoxCounter = 0;

		//生成位置
		D3DXVECTOR3 itemBoxPos = D3DXVECTOR3(GAME_ITEM_BOX_CREATE_POS_X, GAME_BALLOON_CREATE_POS_Y, 0.0f);
		//移動量
		D3DXVECTOR3 itemBoxMove = D3DXVECTOR3(-ITEM_BOX_MOVE_SPEED, 0.0f, 0.0f);

		//2分の1の確率で
		if (rand() % 2 == 0)
		{
			//逆に生成
			itemBoxPos.x *= -1.0f;
			//逆に移動させる
			itemBoxMove.x *= -1.0f;
		}

		//ランダムでZ位置を決める
		itemBoxPos.z = GAME_ITEM_BOX_CREATE_POS_Z;

		//アイテムボックスを生成する
		CItemBox *pItemBox = CItemBox::Create(itemBoxPos);
		pItemBox->SetMove(itemBoxMove);
	}
}

//=============================================================================
//プレイヤーアイコン生成処理
//=============================================================================
void CGameScene01::CreatePlayerIcon(int nCntPlayer){

	//生成されていたら
	if (m_apPlayerIcon[nCntPlayer] != nullptr)
	{
		return;
	}

	//プレイヤーの位置取得
	D3DXVECTOR3 playerPos = m_apPlayer[nCntPlayer]->GetPos();

	playerPos.x += 150.0f;
	playerPos.z -= 100.0f;

	//アイコンの位置
	D3DXVECTOR3 iconPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ワールド座標からスクリーン座標に変換
	iconPos = WorldToScreen(playerPos);
	iconPos.z = 0.0f;

	//生成
	m_apPlayerIcon[nCntPlayer] = CObjectPlayerIcon::Create(iconPos, D3DXVECTOR3(GAME_PLAYER_ICON_SCALE, GAME_PLAYER_ICON_SCALE, GAME_PLAYER_ICON_SCALE),
		                                             CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_ICON_FRAME_1) + nCntPlayer),
													 CTexture::TEXTURE_TYPE(int(CTexture::TEXTURE_TYPE::PLAYER_NUM_WHITE_1) + nCntPlayer));
}

//=============================================================================
//カウントダウンUIの処理
//=============================================================================
void CGameScene01::CountDownUi(void)
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

			//キャスト
			CObjectPlayerBalloonCar *pPlayer = dynamic_cast<CObjectPlayerBalloonCar*>(m_apPlayer[nCntPlayer]);
			if (pPlayer == nullptr) continue;

			//スコアUIが生成されていなかったら
			if (pPlayer->GetScoreUi() == nullptr)
			{
				//生成する
				pPlayer->CreateScore();

				//アイテムのUIのフレームを生成
				pPlayer->CreateItemUiFrame();
			}
		}

		//生成されていなかったら
		if (m_pTimerFrame == nullptr)
		{
			//タイマーの生成
			m_pTimerFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 61.0f, 0.0f), CTexture::TEXTURE_TYPE::TIMER_FRAME, 220.0f, 80.0f);
			m_pTimer = CTimer::Create(GAME_TIME, 2, CTexture::TEXTURE_TYPE::NUMBER_003, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 75.0f, 40.0f, 0.0f), 50.0f);
		}
	}
}

//=============================================================================
//ランキング設定処理
//=============================================================================
void CGameScene01::SetRanking()
{
	std::vector<int> nSocre(MAX_OBJECT_PLAYER_NUM);
	for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
	{
		//キャスト
		CObjectPlayerBalloonCar *pPlayer = dynamic_cast<CObjectPlayerBalloonCar*>(m_apPlayer[nCntPlayer]);
		if (pPlayer == nullptr) continue;

		nSocre[nCntPlayer] = pPlayer->GetScoreUi()->GetScore()->GetScore();
	}
	//降順でソート
	std::sort(nSocre.begin(), nSocre.end(), std::greater<int>());

	//直前で順位を決定したプレイヤー
	int nLastRank = 0;

	for (int nCntScore = 0; nCntScore < MAX_OBJECT_PLAYER_NUM; nCntScore++)
	{
		for (int nCntPlayer = 0; nCntPlayer < MAX_OBJECT_PLAYER_NUM; nCntPlayer++)
		{
			//キャスト
			CObjectPlayerBalloonCar *pPlayer = dynamic_cast<CObjectPlayerBalloonCar*>(m_apPlayer[nCntPlayer]);
			if (pPlayer == nullptr) continue;

			//取得したプレイヤーのスコアと一致していなかったら
			if (nSocre[nCntScore] != pPlayer->GetScoreUi()->GetScore()->GetScore())
			{
				continue;
			}

			//一番最初なら
			if (nCntScore == 0)
			{
				//ランキング設定処理
				CGameScene::SetRanking(nCntScore + 1, nCntPlayer);
				nLastRank = nCntScore + 1;
			}

			//前のスコアと一致していたら
			else if (nSocre[nCntScore] == nSocre[nCntScore - 1])
			{
				//前の順位と同じにする
				CGameScene::SetRanking(nLastRank, nCntPlayer);
			}
			else
			{
				//ランキング設定処理
				CGameScene::SetRanking(nCntScore + 1, nCntPlayer);
				nLastRank = nCntScore + 1;
			}
		}
	}
}
