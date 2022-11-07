//=============================================================================
//
// リザルトシーン処理 [resultScene.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "resultScene.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
#include "object2D.h"
#include "objectModelUI.h"
#include "object_player.h"
#include "ToScreen.h"

#include "gameCamera.h"
#include "gameScene.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CResultScene::CResultScene()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CResultScene::~CResultScene()
{

}

//=============================================================================
// ゲームシーンの初期化処理
//=============================================================================
void CResultScene::Init(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//レンダラーの取得
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//カメラの設定
	if (pManager != nullptr) pManager->SetCamera(CGameCamera::Create());	//なにか一つカメラが無いと描画されないのでとりあえずゲームカメラ

	//------------------------------
	//ライトの初期設定
	//------------------------------
	D3DXMATRIX mtxLightProj;   // ライトの射影変換
	//ライトのプロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(&mtxLightProj, D3DXToRadian(45.0f), 1.0f, 100.0f, 3000.0f);

	D3DXMATRIX mtxLightView;   // ライトビュー変換
	D3DXVECTOR3 posLightV = D3DXVECTOR3(200.0f, 2000.0f, -200.0f);	//ライトの視点の位置
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
		pRenderer->SetEffectFogEnable(false);
	}

	//------------------------------
	//オブジェクトの初期設定
	//------------------------------
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::BG_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);


	//------------------------------
	//ランキング表示
	//------------------------------
	int aPlayerRank[MAX_OBJECT_PLAYER_NUM];	//プレイヤーのランクの配列 インデックスはプレイヤーのインデックスと対応

	//プレイヤーランクの取得
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		aPlayerRank[nIdxPlayer] = CGameScene::GetRanking(nIdxPlayer);
	}

	//プレイヤーの表示順の設定
	int aOrderPlayer[MAX_OBJECT_PLAYER_NUM];
	memset(aOrderPlayer, 0, sizeof(aOrderPlayer));
	int nCurRank = 1;	//現在のランク
	int nIdxOrder = 0;	//順番のインデックス

	while (nCurRank > MAX_OBJECT_PLAYER_NUM)
	{
		for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
		{
			if (aOrderPlayer[nIdxOrder]);	//順番が決定されていた場合除外

			//ランクが一致していた場合
			if (aPlayerRank[nIdxPlayer] == nCurRank) {
				aOrderPlayer[nIdxPlayer] = nIdxOrder;	//順番の設定
				nIdxOrder++;
				break;
			}

			//ランクが一致しなかった場合
			if (nIdxPlayer == MAX_OBJECT_PLAYER_NUM - 1) {
				nCurRank++;
			}
		}
	}

	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++)
	{
		const float fDist = 180.0f;	//プレイヤー同士の距離
		D3DXVECTOR3 posModel = D3DXVECTOR3(fDist * (-MAX_OBJECT_PLAYER_NUM / 2.0f) + fDist / 2.0f + (aOrderPlayer[nIdxPlayer]) * fDist, 0.0f, 0.0f);	//左端から1位を並べる
		CObjectModelUI* pPlayerModel = CObjectModelUI::Create(CModel::MODELTYPE::OBJ_CAR, posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		if (pPlayerModel == nullptr) continue;
		pPlayerModel->SetViewCamera(D3DXVECTOR3(0.0f, 400.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		CModel* pModel = pPlayerModel->GetPtrModel();

		D3DXVECTOR3 posRankUI = WorldToScreen(posModel, pPlayerModel->GetViewMatrix());
		CObject2D::Create(posRankUI + D3DXVECTOR3(0.0f, 100.0f, 0.0f), CTexture::TEXTURE_TYPE::PLAYER_NUM_1, 100.0f, 50.0f);

		if (pModel == nullptr) continue;
		D3DXCOLOR colModel;
		switch (nIdxPlayer)
		{
		case 0:
			colModel = OBJECT_PLAYER_COLOR_1P;
			break;
		case 1:
			colModel = OBJECT_PLAYER_COLOR_2P;
			break;
		case 2:
			colModel = OBJECT_PLAYER_COLOR_3P;
			break;
		case 3:
			colModel = OBJECT_PLAYER_COLOR_4P;
			break;
		default:
			colModel = OBJECT_PLAYER_COLOR_1P;
			break;
		}
		pModel->SetMaterialDiffuse(colModel, 0);
	}

	//------------------------------
	//BGMの再生
	//------------------------------
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_GAME);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_GAME);
	}
}

//=============================================================================
// ゲームシーンの終了処理
//=============================================================================
void CResultScene::Uninit(void) {
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
void CResultScene::Update(void) {
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	//現在の入力デバイスの取得
	CInput* pInput = pManager->GetInputCur();
	if (pInput == nullptr) return;

	if (pInput->GetTrigger(CInput::CODE::SELECT, 0)) {
		//フェードの取得
		CFade* pFade = pManager->GetFade();		//フェードへのポインタ
		if (pFade == nullptr) return;
		if (pFade != nullptr) pFade->SetFade(CScene::SCENE_TYPE::TITLE, 0.02f, 60);
	}

}