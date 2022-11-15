//=============================================================================
//
// 最終結果シーン処理 [finalResultScene.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "finalResultScene.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "object2D.h"
#include "objectModel.h"
#include "finalResultCamera.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CFinalResultScene::CFinalResultScene()
{
	m_nFadeTime = FPS;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFinalResultScene::~CFinalResultScene()
{

}

//=============================================================================
// 最終結果シーンの初期化処理
//=============================================================================
void CFinalResultScene::Init(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//カメラの設定
	if (pManager != nullptr) pManager->SetCamera(CFinalResultCamera::Create());

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


	//------------------------------
	//モデルの生成
	//------------------------------
	const float fDistPlayer = 400.0f;	//プレイヤーのモデル間の距離
	for (int nIdxPlayer = 0; nIdxPlayer < 4; nIdxPlayer++) {
		D3DXVECTOR3 posPlayer = D3DXVECTOR3(-fDistPlayer * (4 / 2.0f) + fDistPlayer / 2.0f + fDistPlayer * nIdxPlayer, 0.0f, 0.0f);	//プレイヤーの位置

		//プレイヤーのモデルの生成
		m_apObjPlayer[nIdxPlayer] = CObjectModel::Create(CModel::MODELTYPE::OBJ_CAR, posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		m_apResultTower[nIdxPlayer] = CObjectModel::Create(CModel::MODELTYPE::OBJ_RESULT_TOWER, posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	}


	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_TITLE);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_TITLE);
	}

	//オブジェクトのポーズが無いように設定
	CObject::SetUpdatePauseLevel(0);
}

//=============================================================================
// 最終結果シーンの終了処理
//=============================================================================
void CFinalResultScene::Uninit(void) {
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
// 最終結果シーンの更新処理
//=============================================================================
void CFinalResultScene::Update(void) {
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	CFade* pFade = nullptr;		//フェードへのポインタ
	CSound* pSound = nullptr;	//サウンドへのポインタ

	if (pManager != nullptr) {
		//フェードの取得
		pFade = pManager->GetFade();
		//サウンドの取得
		pSound = pManager->GetSound();
	}

	if (pFade == nullptr) return;

	//入力処理
	UpdateInput();

	//決定キーが押されたとき
	if (m_bSelectGame)
	{
		// 遷移する時間が0より小さくなっていたら
		if (m_nFadeTime < 0)
		{
			//シーン遷移開始			
			if (pFade != nullptr) pFade->SetFade(CScene::SCENE_TYPE::SELECT_GAME, 0.02f, 60);
		}
		else
		{
			//フェード開始カウント減少
			m_nFadeTime--;
		}
	}
}

//=============================================================================
// 最終結果シーンの入力処理
//=============================================================================
void CFinalResultScene::UpdateInput(void) {
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	CInput* pInput = pManager->GetInputCur();	//入力デバイスへのポインタ
	CFade* pFade = pManager->GetFade();			//フェードへのポインタ
	CSound* pSound = pManager->GetSound();		//サウンドへのポインタ
	if (pInput == nullptr || pFade == nullptr ||  m_bSelectGame) return;

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
		else
		{
			// 押されたフラグ
			m_bSelectGame = true;
			//決定音の再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
		}
	}
}
