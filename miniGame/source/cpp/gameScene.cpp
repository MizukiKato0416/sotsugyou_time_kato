//=============================================================================
//
// ゲームシーン処理 [gameScene.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "gameScene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "gameCamera.h"
#include "fade.h"
#include "timer.h"
#include "score.h"
#include "stage.h"
#include "object2D.h"
#include "player.h"
#include "effect.h"
#include "terrain.h"
#include "meshwall.h"
#include "wallCylinder.h"
#include "pauseMenu.h"
#include "balloon.h"
#include "itemBox.h"
#include "item_banana.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GAME_TIME (300)
#define TEXT_FILE_NAME_HISCORE					 "data/TEXT/save_hiscore.txt"
#define TEXT_FILE_NAME_APPLETYPE				 "data/TEXT/save_appletype.txt"
#define FOG_COLOR								 (D3DXCOLOR(0.1f, 0.0f, 0.2f, 1.0f))	//フォグの色
#define FOG_COLOR_GAMECLEAR					     (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	//フォグの色
#define GAME_STAGE_SIZE							 (700.0f)								//すてーじの大きさ
#define GAME_BALLOON_CREATE_POS_Y				 (45.0f)								//風船の位置Y
#define GAME_BALLOON_CREATE_DIFFER				 (600.0f)								//風船の生成する範囲の半径
#define GAME_BALLOON_TO_BALLOON_DIFFER			 (250.0f)								//風船から風船までの距離
#define GAME_BALLOON_TO_PLAYER_DIFFER			 (180.0f)								//プレイヤーからどれくらい離れた位置に生成するか
#define GAME_BALLOON_INIT_CREATE_SPACE			 (300.0f)								//風船の初期生成間隔
#define GAME_PLAYER_INIT_CREATE_SPACE			 (200.0f)								//プレイヤーの初期生成間隔
#define GAME_PLAYER_INIT_CREATE_POS_Z			 (-400.0f)								//プレイヤーの初期生成位置Z
#define GAME_BALLOON_INIT_CREATE_POS_Z			 (200.0f)								//風船の初期生成位置Z

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGameScene::CGameScene()
{
	m_pStage = nullptr;
	m_pTimer = nullptr;
	m_pMenuGameEnd = nullptr;
	m_nGameScore = 0;

	m_nCntGameClear = 0;
	m_nCreateItemBoxCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameScene::~CGameScene()
{

}

//=============================================================================
// ゲームシーンの初期化処理
//=============================================================================
void CGameScene::Init(void) {

	//変数初期化
	m_nCreateItemBoxCounter = 0;


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
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 800.0f, 5500.0f);

	D3DXMATRIX mtxLightView;   // ライトビュー変換
	D3DXVECTOR3 posLight = D3DXVECTOR3(0.0f, 4800.0f, 0.0f);	//ライトの位置
	D3DXVECTOR3 vecLight;	//ライトのベクトル
	D3DXVec3Normalize(&vecLight, &posLight);
	vecLight *= -1;
	//ライトのビューマトリックスを生成
	D3DXMatrixLookAtLH(&mtxLightView, &posLight, &D3DXVECTOR3(posLight + vecLight), &D3DXVECTOR3(0, 0, 1));
	//シェーダのライトを設定
	if (pRenderer != nullptr) {
		pRenderer->SetEffectLightMatrixView(mtxLightView);
		pRenderer->SetEffectLightVector(D3DXVECTOR4(vecLight, 1.0f));
		pRenderer->SetEffectLightMatrixProj(mtxLightProj);
	}

	//月のビルボード生成
	CBillboard* pMoon = CBillboard::Create(D3DXVECTOR3(-800.0f, 1500.0f, -2000.0f), CTexture::TEXTURE_TYPE::MOON, 200.0f, 200.0f);
	if (pMoon != nullptr) pMoon->SetDrawPriority(CObject::DRAW_PRIORITY::BG);

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

	//------------------------------
	//モーション情報のロード
	//------------------------------

	//オブジェクトのポーズが無いように設定
	CObject::SetUpdatePauseLevel(0);

	//ステージの生成
	//if (m_pStage == nullptr) m_pStage = new CStage;
	//if (m_pStage != nullptr) m_pStage->CreateStage(TEXT_FILE_NAME_STAGE_GAME);

	CItemBanana::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f));

	//床の生成
	CMeshwall::Create(D3DXVECTOR3(0.0f, 0.0f, -1500.0f), D3DXVECTOR3(D3DX_PI*0.5f, 0.0f, 0.0f), 4, 4, 1000.0f, 1000.0f, CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT);

	//スタジアムの生成
	CObjectModel::Create(CModel::MODELTYPE::OBJ_STADIUM, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

	//円柱の壁の生成
	CWallCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), GAME_STAGE_SIZE, 40.0f, CTexture::TEXTURE_TYPE::NONE, false);
	CMeshcylinder::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, GAME_STAGE_SIZE, GAME_STAGE_SIZE + 50.0f, 1, 0.0f, true, CTexture::TEXTURE_TYPE::NONE);

	//風船を生成する
	for (int nCntBalloon = 0; nCntBalloon < BALLOON_MAX_NUM; nCntBalloon++)
	{
		CBalloon::Create(false, D3DXVECTOR3(-GAME_BALLOON_INIT_CREATE_SPACE + GAME_BALLOON_INIT_CREATE_SPACE * nCntBalloon,
			                                GAME_BALLOON_CREATE_POS_Y,
			                                GAME_BALLOON_INIT_CREATE_POS_Z));
	}

	//プレイヤーの生成
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
	{
		CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(-GAME_PLAYER_INIT_CREATE_SPACE * (MAX_PLAYER_NUM / 2.5f) + GAME_PLAYER_INIT_CREATE_SPACE * nCntPlayer,
			                                           0.0f,
			                                           GAME_PLAYER_INIT_CREATE_POS_Z));
		//シーンのプレイヤーの設定
		SetPlayer(pPlayer);
	}

	//タイマーの生成
	m_pTimerFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 61.0f, 0.0f), CTexture::TEXTURE_TYPE::TIMER_FRAME, 220.0f, 80.0f);
	m_pTimer = CTimer::Create(GAME_TIME, 3, CTexture::TEXTURE_TYPE::NUMBER_003, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 75.0f, 40.0f, 0.0f), 50.0f);

	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME);
	}

#ifdef _DEBUG
	//Zバッファテクスチャの表示
	CObject2D* pZBuff = CObject2D::Create(D3DXVECTOR3(70.0f, 70.0f, 0.0f), CTexture::TEXTURE_TYPE::NONE, 100.0f, 100.0f);
	if (pZBuff != nullptr) {
		pZBuff->SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
		pZBuff->SetUseZBuffTexture(true);
	}
#endif

	m_nGameScore = 0;
}

//=============================================================================
// ゲームシーンの終了処理
//=============================================================================
void CGameScene::Uninit(void) {
	//ステージの破棄
	if (m_pStage != nullptr) {
		delete m_pStage;
		m_pStage = nullptr;
	}

	//シーンのプレイヤーの設定
	SetPlayer(nullptr);

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
// ゲームシーンの更新処理
//=============================================================================
void CGameScene::Update(void) {
#ifdef _DEBUG
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//現在の入力デバイスの取得
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;

	//ゲームオーバー
	if (pInput->GetTrigger(CInput::CODE::DEBUG_1)) {
		GameOver();
	}

	//タイム追加
	if (pInput->GetTrigger(CInput::CODE::DEBUG_3)) {
		if (m_pTimer != nullptr) m_pTimer->AddScore(50);
	}

	//風船の生成
	CreateBalloon();

	//アイテムボックスの生成
	CreateItemBox();
#endif

	//ゲームオーバー時
	if (m_bGameOver) {
		UpdateGameOver();
	}
	//ゲーム中
	else
	{
		UpdateGame();
	}
}

//=============================================================================
// ゲーム中の更新
//=============================================================================
void CGameScene::UpdateGame(void) {
	//ポーズメニューがある場合は更新なし
	if (m_pMenuPause != nullptr) return;

	//ゲーム終了していないときにタイマーが０になった場合
	if (m_pTimer != nullptr && !m_bGameOver) {
		if (m_pTimer->GetScore() <= 0) {
			//ゲーム終了
			GameOver();
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
	if (pInput->GetTrigger(CInput::CODE::PAUSE) && !pFade->GetFade()) {
		//ポーズメニュークラスを生成
		m_pMenuPause = CPauseMenu::Create();
		//サウンドを再生
		pSound->PlaySound(CSound::SOUND_LABEL::TITLE_OPEN);
	}
}

//=============================================================================
// ゲームオーバー時の更新
//=============================================================================
void CGameScene::UpdateGameOver(void) {
	if (m_pMenuGameEnd == nullptr) return;

	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//現在の入力デバイスの取得
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;
	//フェードの取得
	CFade* pFade = pManager->GetFade();		//フェードへのポインタ
	if (pFade == nullptr) return;
	//サウンドの取得
	CSound* pSound = pManager->GetSound();	//サウンドへのポインタ
	if (pSound == nullptr) return;

	//選択時
	if (pInput->GetTrigger(CInput::CODE::SELECT)) {
		switch (m_pMenuGameEnd->GetIdxCurSelect())
		{
		case 0:
			//タイトルへシーン遷移
			pFade->SetFade(CScene::SCENE_TYPE::TITLE, 0.02f, 60);
			break;
		case 1:
			//ゲームを再プレイ
			pFade->SetFade(CScene::SCENE_TYPE::GAME, 0.02f, 60);
			break;
		}

		//選択決定音の再生
		pSound->PlaySound(CSound::SOUND_LABEL::TITLE_START);
	}
}

//=============================================================================
// ポーズメニューの破棄
//=============================================================================
void CGameScene::DeletePauseMenu(void) {
	//ポーズメニューの破棄
	if (m_pMenuPause != nullptr) {
		m_pMenuPause->Uninit();
		m_pMenuPause = nullptr;
	}
}

//=============================================================================
// ゲームオーバー
//=============================================================================
void CGameScene::GameOver(void) {
	if (m_bGameOver) return;

	m_bGameOver = true;

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//ゲームオーバー音を再生
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::GAMEOVER);

	//プレイヤーの取得
	CPlayer* pPlayer = GetPlayer();
	if (pPlayer != nullptr) {
		//プレイヤーのゲームオーバー時の処理
		pPlayer->GameOver();
	}

	//ゲームオーバーテキストの表示
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 300.0f, 0.0f), CTexture::TEXTURE_TYPE::TEXT_GAMEOVER, 600.0f, 150.0f);

	//ゲーム終了メニューの生成
	CreateMenuEndGame();

	//タイマーを停止
	if (m_pTimer != nullptr) {
		m_pTimer->SetStop(true);
	}

	//オブジェクトのポーズが無いように設定（念のため）
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
// ゲーム終了時の選択メニューの生成
//=============================================================================
void CGameScene::CreateMenuEndGame(void) {
	//すでに生成されている場合終了
	if (m_pMenuGameEnd != nullptr) return;

	//メニューの生成
	m_pMenuGameEnd = CSelectMenu2D::Create(2, true);
	if (m_pMenuGameEnd == nullptr) return;

	//背景の設定
	m_pMenuGameEnd->SetMenuBG(CTexture::TEXTURE_TYPE::MENU_BG, D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 600.0f, 0.0f), 600.0f, 80.0f);
	//横選択
	m_pMenuGameEnd->SetSelectType(CSelectMenu::SELECT_TYPE::HORIZONTAL);
	//選択肢UIの詳細設定
	m_pMenuGameEnd->SetSelectUI(0, D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 130.0f, 600.0f, 0.0f), 220.0f, 40.0f, CTexture::TEXTURE_TYPE::TEXT_QUIT);
	m_pMenuGameEnd->SetSelectUI(1, D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 130.0f, 600.0f, 0.0f), 220.0f, 40.0f, CTexture::TEXTURE_TYPE::TEXT_RETRY);
	//選択肢アイコンの生成
	m_pMenuGameEnd->CreateSelectIcon(D3DXVECTOR3(-80.0f, 0.0f, 0.0f), 40.0f, 40.0f, CTexture::TEXTURE_TYPE::SELECT_ICON);
	m_pMenuGameEnd->SetIconPosOffset(1, D3DXVECTOR3(-105.0f, 0.0f, 0.0f));
}

//=============================================================================
//風船生成処理
//=============================================================================
void CGameScene::CreateBalloon(void)
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
			CPlayer *pPlayer = static_cast<CPlayer*> (pObject);

			//プレイヤーの位置を取得
			playerPos[pPlayer->GetIndex() - 1] = pPlayer->GetPos();

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
				//遠さをランダムで決める
				fDiffer = (rand() % (int)(GAME_BALLOON_CREATE_DIFFER) * 100.0f) / 100.0f;
				//向きをランダムで決める
				fRot = (rand() % 629 + -314) / 100.0f;

				//決めた位置に出す
				balloonPos.x = sinf(fRot) * fDiffer;
				balloonPos.z = cosf(fRot) * fDiffer;

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
						bLoop = false;
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
		}
	}
}

//=============================================================================
// アイテムボックス生成処理
//=============================================================================
void CGameScene::CreateItemBox(void){
	
	//アイテムが生成されていないなら
	if (CItemBox::GetNum() == 0)
	{
		m_nCreateItemBoxCounter++;
		//一定の値になったら
		if (m_nCreateItemBoxCounter > 180)
		{
			m_nCreateItemBoxCounter = 0;

			//生成位置
			D3DXVECTOR3 itemBoxPos = D3DXVECTOR3(1000.0f, GAME_BALLOON_CREATE_POS_Y, 0.0f);
			//移動量
			D3DXVECTOR3 itemBoxMove = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);

			//2分の1の確率で
			if (rand() % 2 == 0)
			{
				//逆に生成
				itemBoxPos.x *= -1.0f;
				//逆に移動させる
				itemBoxMove.x *= -1.0f;
			}

			//ランダムでZ位置を決める
			itemBoxPos.z = float (rand() % 801 + -400);

			//アイテムボックスを生成する
			CItemBox *pItemBox = CItemBox::Create(itemBoxPos);
			pItemBox->SetMove(itemBoxMove);
		}
	}
}