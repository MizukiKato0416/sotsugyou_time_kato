//=============================================================================
//
// ゲーム選択シーン処理 [selectGameScene.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "selectGameScene.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "object2D.h"
#include "selectMenu3D.h"
#include "gameScene.h"

#include "titleCamera.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_GAME_NUM ((int)CScene::SCENE_TYPE::GAME_MAX - (int)CScene::SCENE_TYPE::GAME_01)	//ゲームの最大数
#define MENU_SELECT_NUM (MAX_GAME_NUM + 1)	//ランダム分追加

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSelectGameScene::CSelectGameScene()
{
	m_pMenuBG = nullptr;
	m_pMenuGame = nullptr;
	m_nFadeTime = FPS;
	m_bWolfMode = false;
	m_pTutorial = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSelectGameScene::~CSelectGameScene()
{

}

//=============================================================================
// ゲーム選択シーンの初期化処理
//=============================================================================
void CSelectGameScene::Init(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//カメラの設定
	if (pManager != nullptr) pManager->SetCamera(CTitleCamera::Create());	//仮でタイトルカメラ

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
		pRenderer->SetEffectFogEnable(false);
	}

	//------------------------------
	//UIの生成
	//------------------------------
	// 背景
	m_pMenuBG = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::BG_MENU, SCREEN_WIDTH, SCREEN_HEIGHT);

	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_TITLE);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_TITLE);
	}

	//選択メニューの生成
	m_pMenuGame = CSelectMenu3D::Create(MENU_SELECT_NUM, D3DXVECTOR3(0.0f, 0.0f, 200.0f), 300.0f, CModel::MODELTYPE::OBJ_BALLOON_PINK, 800.0f, 300.0f, false);

	if (m_pMenuGame != nullptr) {
		//ゲームごとのモデルの配列
		const CModel::MODELTYPE typeModelGame[MENU_SELECT_NUM] =
		{	
			CModel::MODELTYPE::OBJ_BALLOON_PINK,
			CModel::MODELTYPE::OBJ_CAR,
			CModel::MODELTYPE::OBJ_HATENA,
		};

		//全モデルの設定
		for (int nIdxModel = 0; nIdxModel < MENU_SELECT_NUM; nIdxModel++)
		{
			//メニューのUIオブジェクトの取得
			CObjectModelUI* pObjModelUI = m_pMenuGame->GetModelUI(nIdxModel);
			if (pObjModelUI == nullptr) continue;

			//UIオブジェクトのモデルの取得
			CModel* pModel = pObjModelUI->GetPtrModel();
			if (pModel == nullptr) continue;

			//モデルを設定
			pModel->SetModelType(typeModelGame[nIdxModel]);
			pModel->SetColorGlow(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			pModel->SetPowerGlow(4.0f);
		}
	}

	//ゲーム名の背景
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 600.0f, 0.0f), CTexture::TEXTURE_TYPE::ITEM_UI_FRAME_1 , 500.0f, 180.0f);
	//ゲーム名の生成
	m_pGameName = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 600.0f, 0.0f), CTexture::TEXTURE_TYPE::TEXT_TITLENAME, 400.0f, 150.0f);
	//矢印UIの生成
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 350.f, 600.0f, 0.0f), CTexture::TEXTURE_TYPE::ARROW_LEFT, 100.0f, 100.0f);
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 350.f, 600.0f, 0.0f), CTexture::TEXTURE_TYPE::ARROW_RIGHT, 100.0f, 100.0f);

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
// ゲーム選択シーンの終了処理
//=============================================================================
void CSelectGameScene::Uninit(void) {
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
// ゲーム選択シーンの更新処理
//=============================================================================
void CSelectGameScene::Update(void) {
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	CFade* pFade = nullptr;		//フェードへのポインタ
	CSound* pSound = nullptr;	//サウンドへのポインタ

	if (pManager != nullptr) {
		//フェードの取得
		pFade = pManager->GetFade();
		//サウンドの取得
		pSound = pManager->GetSound();
	}

	if (pFade == nullptr || m_pMenuGame == nullptr) return;

	//入力処理
	UpdateInput();

	//決定キーが押されたとき
	if (m_bSelectGame)
	{
		//ランダム選択中の処理
		if (m_pMenuGame->GetRoulette()) {
			//終了時
			if (m_pMenuGame->GetCountRoulette() == 0 && m_pMenuGame->GetCountRotate() == 0) {
				//選択のロック
				m_pMenuGame->SetLockChangeSelect(true);
				//ルーレット状態の終了
				m_pMenuGame->SetRoulette(false);	
				//決定音の再生
				if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
			}
		}
		// 遷移する時間が0より小さくなっていたら
		else if (m_nFadeTime < 0)
		{
			// 0を代入してマイナス値にならないようにする
			m_nFadeTime = 0;
			//シーン遷移開始			
			if (pFade != nullptr) pFade->SetFade(m_nextScene, 0.02f, 60);
			//選択のロック
			m_pMenuGame->SetLockChangeSelect(true);
		}
		else
		{
			//フェード開始カウント減少
			m_nFadeTime--;
		}
	}
}

//=============================================================================
// 入力処理
//=============================================================================
void CSelectGameScene::UpdateInput(void) {
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	CInput* pInput = pManager->GetInputCur();	//入力デバイスへのポインタ
	CFade* pFade = pManager->GetFade();		//フェードへのポインタ
	CSound* pSound = pManager->GetSound();	//サウンドへのポインタ
	if (pInput == nullptr || pFade == nullptr || m_pMenuGame == nullptr || m_bSelectGame) return;

	//チュートリアル切り替え 移動可能時のみ
	if (pInput->GetTrigger(CInput::CODE::CHECK_Y, 0) && !m_pMenuGame->GetLockChangeSelect()) {
		//フェード中だった場合
		if (pFade->GetFade())
		{
			//フェードをスキップ
			pFade->SkipFade();
		}
		else {
			//チュートリアル切り替え
			ChangeTutorial();			
		}
	}

	//チュートリアル閉じる
	if ((pInput->GetTrigger(CInput::CODE::CHECK_A, 0) || pInput->GetTrigger(CInput::CODE::CHECK_B, 0)) && m_pTutorial != nullptr) {
		//チュートリアル切り替え
		ChangeTutorial();
		return;	//選択が連続にならないように終了
	}

	if (m_pTutorial != nullptr) return;	//チュートリアル生成された場合後の入力はなし

	//嘘つき切り替え
	if (pInput->GetTrigger(CInput::CODE::CHECK_X, 0)) {
		//フェード中だった場合
		if (pFade->GetFade())
		{
			//フェードをスキップ
			pFade->SkipFade();
		}
		else {
			//モード切り替え
			ChangeMode(!m_bWolfMode);
		}
	}

	//決定キーを押したとき
	if (pInput->GetTrigger(CInput::CODE::SELECT, 0))
	{
		//フェード中だった場合
		if (pFade->GetFade())
		{
			//フェードをスキップ
			pFade->SkipFade();
		}
		//選択ロック中ではないとき
		else if(!m_pMenuGame->GetLockChangeSelect())
		{
			//現在の選択肢の番号を取得
			int nIdxCurSelect = m_pMenuGame->GetIdxCurSelect();

			// 押されたフラグ
			m_bSelectGame = true;
			//選択のロック
			m_pMenuGame->SetLockChangeSelect(true);
			//決定音の再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);

			//ランダム選択時
			if (nIdxCurSelect == MAX_GAME_NUM) {
				nIdxCurSelect = rand() % MAX_GAME_NUM;	//ランダムな選択
				//メニューの設定
				m_pMenuGame->SetIdxCurSelect(nIdxCurSelect);	//選択番号の設定
				m_pMenuGame->BeginRoulette(FPS * 3, 0.2f * D3DX_PI, 0.985f);	//ルーレット開始
			}

			//次のシーンの決定
			m_nextScene = (CScene::SCENE_TYPE)(nIdxCurSelect + (int)CScene::SCENE_TYPE::GAME_01);	

			//ゲームモード設定
			CGameScene::SetWereWolfMode(m_bWolfMode);
		}
	}
}

//=============================================================================
// チュートリアル表示の切り替え
//=============================================================================
void CSelectGameScene::ChangeTutorial(void) {
	//チュートリアル生成
	if (m_pTutorial == nullptr) {
		CTexture::TEXTURE_TYPE typeTex;

		switch (m_pMenuGame->GetIdxCurSelect() + (int)CScene::SCENE_TYPE::GAME_01)
		{
			//風船
		case (int)CScene::SCENE_TYPE::GAME_01:
			typeTex = CTexture::TEXTURE_TYPE::TUTORIAL_BALLOON;
			break;
			//超絶
		case (int)CScene::SCENE_TYPE::GAME_02:
			typeTex = CTexture::TEXTURE_TYPE::TUTORIAL_ATTACK;
			break;
			//ランダム(仮)
		case (int)CScene::SCENE_TYPE::GAME_MAX:
			typeTex = CTexture::TEXTURE_TYPE::MESH_CLOUD;
			break;
		default:
			typeTex = CTexture::TEXTURE_TYPE::BG_MENU;
			break;
		}

		//背景変更
		m_pTutorial = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), typeTex, SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.9f);
		//選択画面の移動をロック
		if (m_pMenuGame != nullptr) m_pMenuGame->SetLockChangeSelect(true);
	}
	//通常モードに変更
	else {
		//チュートリアル画面の破棄
		m_pTutorial->Uninit();
		m_pTutorial = nullptr;

		//選択画面の移動ロックを解除
		if (m_pMenuGame != nullptr) m_pMenuGame->SetLockChangeSelect(false);
	}

	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	CSound* pSound = nullptr;	//サウンドへのポインタ

	if (pManager != nullptr) {
		//サウンドの取得
		pSound = pManager->GetSound();
	}

	//変更音の設定
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_GET);
}
//=============================================================================
// 嘘つきモードの切り替え
//=============================================================================
void CSelectGameScene::ChangeMode(bool bWolf) {
	m_bWolfMode = bWolf;

	//嘘つきモードに変更
	if (m_bWolfMode) {
		//背景変更
		if (m_pMenuBG != nullptr) m_pMenuBG->SetTexType(CTexture::TEXTURE_TYPE::BG_MENU_WOLF);
	}
	//通常モードに変更
	else {
		//背景変更
		if (m_pMenuBG != nullptr) m_pMenuBG->SetTexType(CTexture::TEXTURE_TYPE::BG_MENU);
	}

	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	CSound* pSound = nullptr;	//サウンドへのポインタ

	if (pManager != nullptr) {
		//サウンドの取得
		pSound = pManager->GetSound();
	}

	//変更音の設定
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_GET);
}