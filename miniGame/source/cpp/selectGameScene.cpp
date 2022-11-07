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

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSelectGameScene::CSelectGameScene()
{
	
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
	m_pMenuGame = CSelectMenu3D::Create(MAX_GAME_NUM + 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.0f, CModel::MODELTYPE::OBJ_BALLOON_PINK, 800.0f, 300.0f, false);

	if (m_pMenuGame != nullptr) {
		//ゲームごとのモデルの配列
		const CModel::MODELTYPE typeModelGame[MAX_GAME_NUM + 1] =
		{	
			CModel::MODELTYPE::OBJ_BALLOON_PINK,
			CModel::MODELTYPE::OBJ_CAR,
			CModel::MODELTYPE::OBJ_BANANA,
		};

		//全モデルの設定
		for (int nIdxModel = 0; nIdxModel < MAX_GAME_NUM + 1; nIdxModel++)
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
			// 押されたとき
			m_bPushKey = true;
			//選択のロック
			m_pMenuGame->SetLockChangeSelect(true);
			//決定音の再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
		}
	}

	//決定キーが押されたとき
	if (m_bPushKey)
	{
		// 遷移する時間が0より小さくなっていたら
		if (m_nFadeTime < 0)
		{
			CScene::SCENE_TYPE nextScene = CScene::SCENE_TYPE::TITLE;	//次のシーン
			int nSelectCur = m_pMenuGame->GetIdxCurSelect();
			if (nSelectCur == MAX_GAME_NUM) nSelectCur = rand() % MAX_GAME_NUM;
			nextScene = (CScene::SCENE_TYPE)(nSelectCur + (int)CScene::SCENE_TYPE::GAME_01);

			// 0を代入してマイナス値にならないようにする
			m_nFadeTime = 0;
			//シーン遷移開始			
			if (pFade != nullptr) pFade->SetFade(nextScene, 0.02f, 60);
		}
		else
		{
			//フェード開始カウント減少
			m_nFadeTime--;
		}
	}
}