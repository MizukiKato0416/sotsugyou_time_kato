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
#include "default_camera.h"
#include "coverDisplay.h"
#include "next_button.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_GAME_NUM ((int)CScene::SCENE_TYPE::GAME_MAX - (int)CScene::SCENE_TYPE::GAME_01)	//ゲームの最大数
#define MENU_SELECT_NUM (MAX_GAME_NUM + 1)	//ランダム分追加

#define MENU_BG_MOVE_SPEED		(D3DXVECTOR2(0.001f, 0.001f))		//背景の移動速度

#define MENU_NEXT_BUTTON_POS			(D3DXVECTOR3(1240.0f, 680.0f, 0.0f))	//次に進むボタンの位置
#define MENU_NEXT_BUTTON_SIZE			(D3DXVECTOR3(70.0f, 70.0f, 0.0f))		//次に進むボタンのサイズ
#define MENU_NEXT_BUTTON_COUNTER		(15)									//次に進むボタンの見えるようになるまでのカウンター
#define MENU_NEXT_BUTTON_DEC_ALPHA		(0.015f)								//次に進むボタンのα値減算量

#define MENU_DECIDE_UI_SIZE_X			(514.0f * 0.4f)		//決定UIのサイズX
#define MENU_DECIDE_UI_SIZE_Y			(216.0f * 0.4f)		//決定UIのサイズY
#define MENU_DECIDE_UI_POS				(20.0f)				//決定UIの位置調整値

#define MENU_ALOW_UI_SIZE				(320.0f * 0.28f)	//矢印UIのサイズ
#define MENU_ALOW_UI_INIT_POS_X			(270.0f)			//矢印UIの位置調整値X
#define MENU_ALOW_UI_INIT_POS_Y			(630.0f)			//矢印UIの位置Y
#define MENU_ALOW_UI_POS_MIN			(267.0f)			//矢印UIの位置最小値
#define MENU_ALOW_UI_POS_MAX			(273.0f)			//矢印UIの位置最大値
#define MENU_ALOW_UI_MOVE_MAX			(0.5f)				//矢印UIの移動量最大値
#define MENU_ALOW_UI_MOVE				(0.05f)				//矢印UIの移動量

#define MENU_GAME_TITLE_UI_SIZE_X		(1697.0f * 0.2f)	//ゲームタイトルUIのサイズX
#define MENU_GAME_TITLE_UI_SIZE_Y		(631.0f * 0.2f)		//ゲームタイトルUIのサイズY

#define MENU_GAME_MODE_UI_SIZE_X		(480.0f * 0.7f)		//モードUIのサイズX
#define MENU_GAME_MODE_UI_SIZE_Y		(220.0f * 0.7f)		//モードUIのサイズY

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
	m_nFadeTime = 0;
	m_bWolfMode = false;
	m_pTutorial = nullptr;
	m_pModeUi = nullptr;
	m_pMenuNoneMoveUi = nullptr;
	memset(m_pAlowUi, NULL, sizeof(m_pAlowUi[SELECT_GAME_SCENE_ALOW_UI_NUM]));
	memset(m_fAlowUiMove, 0, sizeof(m_fAlowUiMove[SELECT_GAME_SCENE_ALOW_UI_NUM]));
	memset(m_bAlowUiMoveChange, false, sizeof(m_bAlowUiMoveChange[SELECT_GAME_SCENE_ALOW_UI_NUM]));
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
	//テクスチャのロード
	CTexture::Load("select");

	//変数初期化
	memset(m_fAlowUiMove, 0, sizeof(m_fAlowUiMove[SELECT_GAME_SCENE_ALOW_UI_NUM]));
	m_bAlowUiMoveChange[0] = false;
	m_bAlowUiMoveChange[1] = true;
	m_nFadeTime = 30;

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//カメラの設定
	if (pManager != nullptr) pManager->SetCamera(CDefaultCamera::Create());	//仮でデフォルトカメラ

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

	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_MENU);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_MENU);
	}

	//オブジェクトのポーズが無いように設定
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
//オブジェクト生成処理
//=============================================================================
void CSelectGameScene::CreateObject(void)
{
	//------------------------------
	//UIの生成
	//------------------------------
	// 背景
	m_pMenuBG = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::BG_MENU, SCREEN_WIDTH, SCREEN_HEIGHT);

	//ステージの生成
	CObjectModelUI *pModel = CObjectModelUI::Create(CModel::MODELTYPE::OBJ_MENU_STAGE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	if (pModel != nullptr)
	{
		pModel->SetViewCamera(D3DXVECTOR3(0.0f, 200.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//背景
	m_pMenuNoneMoveUi = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::MENU_NONE_MOVE_UI,
		                                  SCREEN_WIDTH, SCREEN_HEIGHT);

	//選択メニューの生成
	m_pMenuGame = CSelectMenu3D::Create(MENU_SELECT_NUM, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 250.0f, CModel::MODELTYPE::OBJ_BALLOON_PINK, 800.0f, 200.0f, false, true);

	if (m_pMenuGame != nullptr) {
		//ゲームごとのモデルの配列
		const CModel::MODELTYPE typeModelGame[MENU_SELECT_NUM] =
		{
			CModel::MODELTYPE::OBJ_BALLOON_PINK,
			CModel::MODELTYPE::OBJ_CAR,
			CModel::MODELTYPE::OBJ_BOM,
			CModel::MODELTYPE::OBJ_HATENA,
		};

		//全モデルの設定
		for (int nIdxModel = 0; nIdxModel < MENU_SELECT_NUM; nIdxModel++)
		{
			//メニューのUIオブジェクトの取得
			CObjectModelUI* pObjModelUI = m_pMenuGame->GetModelUI(nIdxModel);
			if (pObjModelUI == nullptr) continue;

			//ステンシル有効
			//pObjModelUI->SetEnableStencil(true);

			//回転速度の設定
			pObjModelUI->SetRotSpeed(D3DXVECTOR3(0.0f, 0.02f, 0.0f));

			//UIオブジェクトのモデルの取得
			CModel* pModel = pObjModelUI->GetPtrModel();
			if (pModel == nullptr) continue;

			//モデルを設定
			pModel->SetModelType(typeModelGame[nIdxModel]);

			const D3DXCOLOR colSpecular = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);	//スペキュラーの色
																				//マテリアルの設定
			for (int nCnt = 0; nCnt < MAX_MATERIAL; nCnt++)
			{
				pModel->SetMaterialSpecular(colSpecular, nCnt);
				pModel->SetMaterialPower(6.0f, nCnt);
			}
		}
	}

	//ゲーム名の生成
	m_pGameName = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, MENU_ALOW_UI_INIT_POS_Y, 0.0f), CTexture::TEXTURE_TYPE::TEXT_TITLENAME_BALLOON,
		MENU_GAME_TITLE_UI_SIZE_X, MENU_GAME_TITLE_UI_SIZE_Y);
	//矢印UIの生成
	m_pAlowUi[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - MENU_ALOW_UI_INIT_POS_X, MENU_ALOW_UI_INIT_POS_Y, 0.0f),
		CTexture::TEXTURE_TYPE::ARROW_LEFT, MENU_ALOW_UI_SIZE, MENU_ALOW_UI_SIZE);
	m_pAlowUi[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + MENU_ALOW_UI_INIT_POS_X, MENU_ALOW_UI_INIT_POS_Y, 0.0f),
		CTexture::TEXTURE_TYPE::ARROW_RIGHT, MENU_ALOW_UI_SIZE, MENU_ALOW_UI_SIZE);

	//モードUIの生成
	m_pModeUi = CObject2D::Create(D3DXVECTOR3(MENU_GAME_MODE_UI_SIZE_X / 2.0f, MENU_GAME_MODE_UI_SIZE_Y / 2.0f, 0.0f),
		CTexture::TEXTURE_TYPE::MENU_MODE_NORMAL, MENU_GAME_MODE_UI_SIZE_X, MENU_GAME_MODE_UI_SIZE_Y);
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
	//ロードが終了していなかったら
	if (!CTexture::GetLoadFinish()) return;

	//シーンの更新処理
	CScene::Update();

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
				//ゲームタイトルの切替
				ChangeGameTitle();
			}
		}
		// 遷移する時間が0より小さくなっていたら
		else if (m_nFadeTime < 0)
		{
			// 0を代入してマイナス値にならないようにする
			m_nFadeTime = 0;

			//遷移の時間設定
			float fDecAlpha = 0.04f;
			int nStopCount = 30;
			if (m_nextScene == SCENE_TYPE::TITLE)
			{
				fDecAlpha = 0.1f;
				nStopCount = 10;
			}

			//シーン遷移開始			
			if (pFade != nullptr) pFade->SetFade(m_nextScene, fDecAlpha, nStopCount);
			//選択のロック
			m_pMenuGame->SetLockChangeSelect(true);
		}
		else
		{
			//フェード開始カウント減少
			m_nFadeTime--;
		}
	}
	else {
		//ゲームタイトルの切替
		ChangeGameTitle();
	}

	//背景の動きの処理
	BgMove();

	//矢印UIの処理
	AlowUi();
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
	if ((pInput->GetTrigger(CInput::CODE::SELECT, 0) || pInput->GetTrigger(CInput::CODE::BACK, 0)) && m_pTutorial != nullptr) {
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
	//戻るキー押下
	else if (pInput->GetTrigger(CInput::CODE::BACK, 0)) {
		// 押されたフラグ
		m_bSelectGame = true;
		//選択のロック
		m_pMenuGame->SetLockChangeSelect(true);
		//決定音の再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_CANCEL);

		//次のシーンの決定
		m_nextScene = CScene::SCENE_TYPE::TITLE;

		//シーン遷移が始まるまでの時間を設定
		m_nFadeTime = 0;
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
			if (m_bWolfMode) {
				typeTex = CTexture::TEXTURE_TYPE::TUTORIAL_BALLOON_WOLF;
			}
			else {
				typeTex = CTexture::TEXTURE_TYPE::TUTORIAL_BALLOON;
			}
			break;
			//超絶
		case (int)CScene::SCENE_TYPE::GAME_02:
			if (m_bWolfMode) {
				typeTex = CTexture::TEXTURE_TYPE::TUTORIAL_ATTACK_WOLF;
			}
			else {
				typeTex = CTexture::TEXTURE_TYPE::TUTORIAL_ATTACK;
			}
			break;
			//ランダム(仮)
		case (int)CScene::SCENE_TYPE::GAME_MAX:
			typeTex = CTexture::TEXTURE_TYPE::TUTORIAL_RANDOM;
			break;
		default:
			typeTex = CTexture::TEXTURE_TYPE::BG_MENU;
			break;
		}

		//背景変更
		m_pTutorial = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), typeTex, SCREEN_WIDTH * 1.0f, SCREEN_HEIGHT * 1.0f);
		//次へUIの生成
		m_pNextButton = CNextButton::Create(MENU_NEXT_BUTTON_POS, MENU_NEXT_BUTTON_SIZE,
			                                CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_3, MENU_NEXT_BUTTON_COUNTER,
			                                MENU_NEXT_BUTTON_DEC_ALPHA);

		//選択画面の移動をロック
		if (m_pMenuGame != nullptr) m_pMenuGame->SetLockChangeSelect(true);
	}
	//通常モードに変更
	else {
		//チュートリアル画面の破棄
		m_pTutorial->Uninit();
		m_pTutorial = nullptr;

		m_pNextButton->Uninit();
		m_pNextButton = nullptr;

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
//ゲームタイトルの切替
//=============================================================================
void CSelectGameScene::ChangeGameTitle()
{
	//現在選ばれているゲームによってタイトルの名前を変える
	switch (m_pMenuGame->GetIdxCurSelect() + (int)CScene::SCENE_TYPE::GAME_01)
	{
		//バルーン
	case (int)CScene::SCENE_TYPE::GAME_01:
		if (m_pGameName->GetTexType() == CTexture::TEXTURE_TYPE::TEXT_TITLENAME_BALLOON && !m_pMenuGame->GetRoulette()) return;
		m_pGameName->SetTexType(CTexture::TEXTURE_TYPE::TEXT_TITLENAME_BALLOON);
		break;
		//ぶっ飛び
	case (int)CScene::SCENE_TYPE::GAME_02:
		if (m_pGameName->GetTexType() == CTexture::TEXTURE_TYPE::TEXT_TITLENAME_ATTACK && !m_pMenuGame->GetRoulette()) return;
		m_pGameName->SetTexType(CTexture::TEXTURE_TYPE::TEXT_TITLENAME_ATTACK);
		break;
		//ストップ
	case (int)CScene::SCENE_TYPE::GAME_03:
		if (m_pGameName->GetTexType() == CTexture::TEXTURE_TYPE::TEXT_GAMESTART && !m_pMenuGame->GetRoulette()) return;
		m_pGameName->SetTexType(CTexture::TEXTURE_TYPE::TEXT_GAMESTART);
		break;
		//ランダム
	case (int)CScene::SCENE_TYPE::GAME_MAX:
		if (m_pGameName->GetTexType() == CTexture::TEXTURE_TYPE::TEXT_TITLENAME_RANDOM) return;
		m_pGameName->SetTexType(CTexture::TEXTURE_TYPE::TEXT_TITLENAME_RANDOM);
		break;
	default:
		break;
	}
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
		if (m_pMenuNoneMoveUi != nullptr) m_pMenuNoneMoveUi->SetTexType(CTexture::TEXTURE_TYPE::MENU_NONE_MOVE_UI_WOLF);
		if (m_pModeUi != nullptr) m_pModeUi->SetTexType(CTexture::TEXTURE_TYPE::MENU_MODE_WOLF);
	}
	//通常モードに変更
	else {
		//背景変更
		if (m_pMenuBG != nullptr) m_pMenuBG->SetTexType(CTexture::TEXTURE_TYPE::BG_MENU);
		if (m_pMenuNoneMoveUi != nullptr) m_pMenuNoneMoveUi->SetTexType(CTexture::TEXTURE_TYPE::MENU_NONE_MOVE_UI);
		if (m_pModeUi != nullptr) m_pModeUi->SetTexType(CTexture::TEXTURE_TYPE::MENU_MODE_NORMAL);
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
//背景の動きの処理
//=============================================================================
void CSelectGameScene::BgMove(){
	if (m_pMenuBG == nullptr) return;

	//背景を動かす
	m_pMenuBG->SetMoveTex(MENU_BG_MOVE_SPEED.x, MENU_BG_MOVE_SPEED.y);
}

//=============================================================================
//矢印UIの動き処理
//=============================================================================
void CSelectGameScene::AlowUi()
{
	for (int nCntAlow = 0; nCntAlow < SELECT_GAME_SCENE_ALOW_UI_NUM; nCntAlow++)
	{
		if (m_pAlowUi[nCntAlow] == nullptr) continue;

		//位置取得
		D3DXVECTOR3 pos = m_pAlowUi[nCntAlow]->GetPos();

		//移動量加算
		if(m_bAlowUiMoveChange[nCntAlow]) m_fAlowUiMove[nCntAlow] += MENU_ALOW_UI_MOVE;
		else m_fAlowUiMove[nCntAlow] -= MENU_ALOW_UI_MOVE;
		
		//移動量最大値を超えたら
		if (m_fAlowUiMove[nCntAlow] > MENU_ALOW_UI_MOVE_MAX) m_fAlowUiMove[nCntAlow] = MENU_ALOW_UI_MOVE_MAX;
		else if (m_fAlowUiMove[nCntAlow] < -MENU_ALOW_UI_MOVE_MAX) m_fAlowUiMove[nCntAlow] = -MENU_ALOW_UI_MOVE_MAX;

		//位置に加算
		pos.x += m_fAlowUiMove[nCntAlow];

		//位置反映
		m_pAlowUi[nCntAlow]->SetPos(pos);

		float fPosMax = SCREEN_WIDTH / 2.0f - MENU_ALOW_UI_POS_MIN;
		float fPosMin = SCREEN_WIDTH / 2.0f - MENU_ALOW_UI_POS_MAX;
		if (nCntAlow == 1)
		{
			fPosMax = SCREEN_WIDTH / 2.0f + MENU_ALOW_UI_POS_MAX;
			fPosMin = SCREEN_WIDTH / 2.0f + MENU_ALOW_UI_POS_MIN;
		}

		if (pos.x <= fPosMin)
		{
			if (!m_bAlowUiMoveChange[nCntAlow]) m_bAlowUiMoveChange[nCntAlow] = true;
		}
		else if (pos.x >= fPosMax)
		{
			if (m_bAlowUiMoveChange[nCntAlow]) m_bAlowUiMoveChange[nCntAlow] = false;
		}
	}
}
