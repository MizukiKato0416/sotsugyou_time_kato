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
	m_nFadeTime = FPS;
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
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::MESH_FLOOR_DESERT, SCREEN_WIDTH, SCREEN_HEIGHT);

	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_TITLE);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_TITLE);
	}

	//選択メニューの生成
	m_pMenuGame = CSelectMenu3D::Create(MENU_SELECT_NUM, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.0f, CModel::MODELTYPE::OBJ_BALLOON_PINK, 800.0f, 300.0f, false);

	if (m_pMenuGame != nullptr) {
		//ゲームごとのモデルの配列
		const CModel::MODELTYPE typeModelGame[MENU_SELECT_NUM] =
		{	
			CModel::MODELTYPE::OBJ_BALLOON_PINK,
			CModel::MODELTYPE::OBJ_CAR,
			CModel::MODELTYPE::OBJ_BANANA,
		};

		//全モデルの設定
		for (int nIdxModel = 0; nIdxModel < MENU_SELECT_NUM; nIdxModel++)
		{
			//メニューのUIオブジェクトの取得
			CObjectModelUI* pObjModelUI = m_pMenuGame->GetModelUI(nIdxModel);
			if (pObjModelUI != nullptr) {
				//UIオブジェクトのモデルの取得
				CModel* pModel = pObjModelUI->GetPtrModel();
				if (pModel != nullptr) {
					//モデルを設定
					pModel->SetModelType(typeModelGame[nIdxModel]);
				}
			}
		}
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
	CInput* pInput = nullptr;	//入力デバイスへのポインタ
	CFade* pFade = nullptr;		//フェードへのポインタ
	CSound* pSound = nullptr;	//サウンドへのポインタ

	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
		//フェードの取得
		pFade = pManager->GetFade();
		//サウンドの取得
		pSound = pManager->GetSound();
	}

	if (pInput == nullptr || pFade == nullptr || m_pMenuGame == nullptr) return;

	//現在の選択肢の番号
	int nIdxCurSelect = m_pMenuGame->GetIdxCurSelect();

	//決定キーを押したとき
	if (pInput->GetTrigger(CInput::CODE::SELECT, 0) && !m_bPushKey)
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
			// 押されたフラグ
			m_bPushKey = true;
			//選択のロック
			m_pMenuGame->SetLockChangeSelect(true);
			//決定音の再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);

			//ランダム選択時
			if (nIdxCurSelect == MAX_GAME_NUM) {
				nIdxCurSelect = rand() % MAX_GAME_NUM;	//ランダムな選択
				//メニューの設定
				m_pMenuGame->SetIdxCurSelect(nIdxCurSelect);	//選択番号の設定
				m_pMenuGame->BeginRoulette(FPS * 5, 0.2f * D3DX_PI, 0.99f);	//ルーレット開始
			}

			m_nextScene = (CScene::SCENE_TYPE)(nIdxCurSelect + (int)CScene::SCENE_TYPE::GAME_01);	//次のシーンの決定
		}
	}

	//決定キーが押されたとき
	if (m_bPushKey)
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