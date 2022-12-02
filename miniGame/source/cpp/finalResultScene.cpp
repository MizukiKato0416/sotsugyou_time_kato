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
#include "finalResultCamera.h"
#include "fade.h"
#include "object2D.h"
#include "objectModel.h"
#include "score.h"
#include "gameScene.h"
#include "object_player.h"
#include "meshwall.h"
#include "ToScreen.h"
#include "next_button.h"
#include "float_object.h"
#include "skydome.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FINAL_RESULT_SCENE_NEXT_BUTTON_POS			(D3DXVECTOR3(1150.0f, 670.0f, 0.0f))	//次に進むボタンの位置
#define FINAL_RESULT_SCENE_NEXT_BUTTON_SIZE			(D3DXVECTOR3(70.0f, 70.0f, 0.0f))		//次に進むボタンのサイズ
#define FINAL_RESULT_SCENE_NEXT_BUTTON_COUNTER		(15)									//次に進むボタンの見えるようになるまでのカウンター
#define FINAL_RESULT_SCENE_NEXT_BUTTON_DEC_ALPHA	(0.015f)								//次に進むボタンのα値減算量

#define FINAL_RESULT_SCENE_RESULT_UI_SIZE_X			(618.0f * 1.5f)		//結果発表UIのサイズX
#define FINAL_RESULT_SCENE_RESULT_UI_SIZE_Y			(182.0f * 1.5f)		//結果発表UIのサイズY
#define FINAL_RESULT_SCENE_RESULT_UI_INIT_SIZE_X	(618.0f * 5.0f)		//結果発表UIの初期サイズX
#define FINAL_RESULT_SCENE_RESULT_UI_INIT_SIZE_Y	(182.0f * 5.0f)		//結果発表UIの初期サイズY
#define FINAL_RESULT_SCENE_RESULT_UI_ADD_SIZE		(0.94f)				//結果発表UIの初期サイズ加算量
#define FINAL_RESULT_SCENE_RESULT_UI_ADD_ALPHA		(0.1f)				//結果発表UIのα値加算量

#define FINAL_RESULT_SCENE_CLOUD_NUM_Y		(12)									//雲の縦の総数
#define FINAL_RESULT_SCENE_CLOUD_NUM_X		(10)									//雲の横の総数
#define FINAL_RESULT_SCENE_CLOUD_DIFFER		(float(rand() % 18401 + 1600))			//雲の距離
#define FINAL_RESULT_SCENE_CLOUD_ROT		(float(rand() % 629 + -314) / 100.0f)	//雲の生成方向
#define FINAL_RESULT_SCENE_CLOUD_MIN_POS_Y	(-5000.0f)								//雲の生成位置Y最小値
#define FINAL_RESULT_SCENE_CLOUD_POS_Y		(800.0f)								//雲の生成間隔
#define FINAL_RESULT_SCENE_CLOUD_POS_Y_RAND	(float(rand() % 1001 + -500))			//雲の生成位置Yランダム値
#define FINAL_RESULT_SCENE_CLOUD_MOVE_SPEED	(-(float(rand() % 6 + 2) / 10000.0f))	//雲の移動速度

#define FINAL_RESULT_SCENE_BALLOON_CREATE_POS			(-4000.0f)							//風船の生成位置
#define FINAL_RESULT_SCENE_BALLOON_CREATE_POS_Y_RAND	(float(rand() % 1001 + -500))		//風船の生成位置Yランダム値
#define FINAL_RESULT_SCENE_BALLOON_DIFFER				(float(rand() % 2801 + 1200))		//風船の距離
#define FINAL_RESULT_SCENE_BALLOON_MOVE_SPEED			(float(rand() % 8 + 3))				//風船の移動速度
#define FINAL_RESULT_SCENE_BALLOON_CREATE_INTERVAL		(5)									//風船の生成間隔
#define FINAL_RESULT_SCENE_BALLOON_CREATE_NUM			(3)									//風船の1回での生成量
#define FINAL_RESULT_SCENE_BALLOON_UNINIT_POS_Y			(2000.0f)							//風船の消す位置

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int CFinalResultScene::m_aPlayerScore[MAX_OBJECT_PLAYER_NUM] = { 70, 30, 20, 10 };

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CFinalResultScene::CFinalResultScene()
{
	m_nFadeTime = FPS;
	m_pTextResult = nullptr;
	m_fDifferCloud.clear();
	m_fRotCloud.clear();
	m_fMoveSpeedCloud.clear();
	m_pCloud.clear();
	m_pBalloon.clear();
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
		//バックバッファをフォグの色に合わせる
		pRenderer->SetBackBuffColor(D3DXCOLOR(0.1f, 0.7f, 1.0f, 1.0f));
	}

	//------------------------------
	//UIの生成
	//------------------------------


	//------------------------------
	//モデルの生成
	//------------------------------
	//雲の総数
	int nNumCloud = 0;
	//雲の生成
	for (int nCntCloudY = 0; nCntCloudY < FINAL_RESULT_SCENE_CLOUD_NUM_Y; nCntCloudY++)
	{
		for (int nCntCloudX = 0; nCntCloudX < FINAL_RESULT_SCENE_CLOUD_NUM_X; nCntCloudX++, nNumCloud++)
		{
			//中心からの距離の設定
			m_fDifferCloud.push_back(FINAL_RESULT_SCENE_CLOUD_DIFFER);
			//向きをランダムで決める
			m_fRotCloud.push_back(FINAL_RESULT_SCENE_CLOUD_ROT);

			//生成位置の設定
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, FINAL_RESULT_SCENE_CLOUD_MIN_POS_Y + (FINAL_RESULT_SCENE_CLOUD_POS_Y * nCntCloudY), 0.0f);
			pos.y += FINAL_RESULT_SCENE_CLOUD_POS_Y_RAND;
			pos.x += cosf(m_fRotCloud[nNumCloud]) * m_fDifferCloud[nNumCloud];
			pos.z += sinf(m_fRotCloud[nNumCloud]) * m_fDifferCloud[nNumCloud];

			//向きの設定
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, D3DX_PI / 2.0f - m_fRotCloud[nNumCloud], 0.0f);

			//雲の向きをランダムで裏返す
			if (rand() % 2 == 0) rot.y += D3DX_PI;

			//モデルの種類
			int nModelNum = static_cast<int>(CModel::MODELTYPE::OBJ_RESULT_CLOUD_02) + 1 - static_cast<int>(CModel::MODELTYPE::OBJ_RESULT_CLOUD_00);

			//モデルをランダムで設定
			int nModel = (rand() % nModelNum) + static_cast<int>(CModel::MODELTYPE::OBJ_RESULT_CLOUD_00);

			m_pCloud.push_back(CObjectModel::Create(static_cast<CModel::MODELTYPE>(nModel), pos, rot, false));

			//移動速度を設定
			m_fMoveSpeedCloud.push_back(FINAL_RESULT_SCENE_CLOUD_MOVE_SPEED);
		}
	}


	//プレイヤーのモデルの生成
	const float fDistPlayer = 400.0f;	//プレイヤーのモデル間の距離
	for (int nIdxPlayer = 0; nIdxPlayer < MAX_OBJECT_PLAYER_NUM; nIdxPlayer++) {
		D3DXVECTOR3 posPlayer = D3DXVECTOR3(-fDistPlayer * (MAX_OBJECT_PLAYER_NUM / 2.0f) + fDistPlayer / 2.0f + fDistPlayer * nIdxPlayer, 0.0f, 0.0f);	//プレイヤーの位置
		//プレイヤーのモデルの生成
		m_apObjPlayer[nIdxPlayer] = CObjectModel::Create(CModel::MODELTYPE::OBJ_CAR, posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
		//プレイヤーの色を設定
		if (m_apObjPlayer[nIdxPlayer] == nullptr) continue;	//ループ飛ばす
		//タワーの生成
		m_apResultTower[nIdxPlayer] = CObjectModel::Create(CModel::MODELTYPE::OBJ_RESULT_TOWER, posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	
		//モデルの設定
		CModel* pModelPlayer = m_apObjPlayer[nIdxPlayer]->GetPtrModel();
		if (pModelPlayer == nullptr) continue;	//ループ飛ばす
		D3DXCOLOR colPlayer = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);	//プレイヤーの色

		switch (nIdxPlayer)
		{
		case 0:
			colPlayer = OBJECT_PLAYER_COLOR_1P;
			break;
		case 1:
			colPlayer = OBJECT_PLAYER_COLOR_2P;
			break;
		case 2:
			colPlayer = OBJECT_PLAYER_COLOR_3P;
			break;
		case 3:
			colPlayer = OBJECT_PLAYER_COLOR_4P;
			break;
		}

		//マテリアルの色の設定
		pModelPlayer->SetMaterialDiffuse(colPlayer, 0);
		//スペキュラーの設定
		pModelPlayer->SetMaterialSpecular(colPlayer / 2.0f + D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), 0);
		pModelPlayer->SetMaterialPower(2.0f, 0);
	}


	//BGMの再生
	if (pSound != nullptr) {
		pSound->PlaySound(CSound::SOUND_LABEL::BGM_FINAL_RESULT);
		pSound->SetBGM(CSound::SOUND_LABEL::BGM_FINAL_RESULT);
	}

	m_phase = PHASE::PHASE_FIRST;	//何もしないフェーズ

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

	//雲の移動処理
	CloudMove();

	//風船生成処理
	CreateBalloon();

	//風船の移動処理
	BalloonMove();

	//フェーズごとの更新処理
	switch (m_phase)
	{
	case CFinalResultScene::PHASE::PHASE_FIRST:
		PhaseFirst();
		break;
	case CFinalResultScene::PHASE::RISE_CAMERA:
		RiseCamera();
		break;
	case CFinalResultScene::PHASE::RESULT_TEXT:
		ResultText();
		break;
	case CFinalResultScene::PHASE::SHOW_SCORE_UI:
		ShowScoreUI();
		break;
	case CFinalResultScene::PHASE::RISE_TOWER:
		RiseTower();
		break;
	case CFinalResultScene::PHASE::WINNER:
		Winner();
		break;
	case CFinalResultScene::PHASE::PHASE_FINISH:
		PhaseFinish();
		break;
	}
}

//=============================================================================
// フェーズ開始処理
//=============================================================================
void CFinalResultScene::PhaseFirst() {
	//フェーズのカウント加算
	m_nCntPhase++;
	//次のフェーズに移行
	if (m_nCntPhase >= 60) {
		m_nCntPhase = 0;
		m_phase = PHASE::RISE_CAMERA;
	}
}

//=============================================================================
// カメラの上昇処理
//=============================================================================
void CFinalResultScene::RiseCamera() {
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	CCamera* pCamera = pManager->GetCamera();	//カメラへのポインタ
	if (pCamera == nullptr) return;

	//フェーズのカウント加算
	m_nCntPhase++;

	//上昇
	D3DXVECTOR3 posCamera = pCamera->GetPos();	//カメラの位置取得
	const float fMoveMaxY = 1.6f;	//上昇の速度（最大）
	float fMoveY = powf((float)m_nCntPhase, 2.f) * 0.001f;	//上昇量
	//最大値で調整
	if (fMoveY > fMoveMaxY) fMoveY = fMoveMaxY;

	const float fSlowHeight = -100.0f;	//減速する高さ
	//減速させる
	if (posCamera.y > fSlowHeight) {
		fMoveY = -posCamera.y * (fMoveMaxY / -fSlowHeight);
	}

	//0まで上昇させる
	if (posCamera.y < 0.0f) {

		//位置上昇
		posCamera.y += fMoveY;	
		//0に近づいた場合調節する
		if (posCamera.y > -0.01f) {
			posCamera.y = 0.0f;
		}
		//位置の設定
		pCamera->SetPos(posCamera);	
	}

	//回転
	D3DXVECTOR3 rotCamera = pCamera->GetRot();	//カメラの角度取得
	float fRotCameraLastY = rotCamera.y;	//回転させる前の角度

	float fRotSpeed = 0.013f;	//回転速度
	float fSlowRot = -0.2f;		//減速する角度

	//減速している時点で、正面ギリギリで減速
	if (posCamera.y > fSlowHeight && rotCamera.y < 0.0f && rotCamera.y >= fSlowRot) {
		fRotSpeed = -rotCamera.y * (fRotSpeed / -fSlowRot);
		if (fRotSpeed < 0.001f) fRotSpeed = 0.001f;
	}

	rotCamera.y += fRotSpeed;	//回転
	//超過分の調整
	if (rotCamera.y > D3DX_PI) {
		rotCamera.y -= D3DX_PI * 2.0f;
	}

	//回転の終了
	if (posCamera.y > fSlowHeight && rotCamera.y >= 0.0f && fRotCameraLastY <= 0.0f) {
		//常に正面を向かせる
		rotCamera.y = 0.0f;
		//フェーズの変更
		m_phase = PHASE::RESULT_TEXT;
		//カウントリセット
		m_nCntPhase = 0;
	}

	//角度の反映
	pCamera->SetRot(rotCamera);
}

//=============================================================================
// 結果発表のテキスト表示処理
//=============================================================================
void CFinalResultScene::ResultText() {
	m_nCntPhase++;

	if (m_nCntPhase == 120) {
		//結果発表テキストの表示
		m_pTextResult = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
			                              CTexture::TEXTURE_TYPE::FINAL_RESULT_UI,
			                              FINAL_RESULT_SCENE_RESULT_UI_INIT_SIZE_X, FINAL_RESULT_SCENE_RESULT_UI_INIT_SIZE_Y);
		m_pTextResult->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		CManager* pManager = CManager::GetManager();	//マネージャーの取得
		if (pManager == nullptr) return;
		//サウンドの取得
		CSound* pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音を再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_RESULT_UI);
	}

	if (m_pTextResult == nullptr) return;

	//生成されいたら

	

	//サイズ取得
	D3DXVECTOR3 size = m_pTextResult->GetSize();
	//サイズを大きくする
	size *= FINAL_RESULT_SCENE_RESULT_UI_ADD_SIZE;
	if (size.x < FINAL_RESULT_SCENE_RESULT_UI_SIZE_X) size.x = FINAL_RESULT_SCENE_RESULT_UI_SIZE_X;
	if (size.y < FINAL_RESULT_SCENE_RESULT_UI_SIZE_Y) size.y = FINAL_RESULT_SCENE_RESULT_UI_SIZE_Y;
	//サイズ設定
	m_pTextResult->SetSize(size);

	//フェーズ切り替え
	if (m_nCntPhase > 300) {

		//カラー取得
		D3DXCOLOR col = m_pTextResult->GetColor();
		//α値減算
		col.a -= FINAL_RESULT_SCENE_RESULT_UI_ADD_ALPHA;
		//カラー設定
		m_pTextResult->SetColor(col);

		if (col.a < 0.0f)
		{
			//フェーズの変更
			m_phase = PHASE::SHOW_SCORE_UI;

			//結果発表テキストの破棄
			m_pTextResult->Uninit();
			m_pTextResult = nullptr;
			//カウントリセット
			m_nCntPhase = 0;
			return;
		}
	}
	else
	{
		//カラー取得
		D3DXCOLOR col = m_pTextResult->GetColor();
		//α値加算
		col.a += FINAL_RESULT_SCENE_RESULT_UI_ADD_ALPHA;
		if (col.a > 1.0f) col.a = 1.0f;
		//カラー設定
		m_pTextResult->SetColor(col);
	}
}

//=============================================================================
// スコアのUI表示処理
//=============================================================================
void CFinalResultScene::ShowScoreUI() {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	m_nCntPhase++;

	bool bWolfMode = CGameScene::GetWereWolfMode();	//人狼モードのフラグ

	//スコアUIの表示
	for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
	{
		//生成タイミング
		if (m_nCntPhase == 120 + nCnt * 30 || (!bWolfMode && m_nCntPhase == 1)) {
			float fPosX = WorldToScreen(m_apObjPlayer[nCnt]->GetPos()).x;	//プレイヤーのモデルの位置をスクリーン座標に変換してｘ座標を取得
			//スコアの生成
			m_apScoreResult[nCnt] = CScore::Create(3, CTexture::TEXTURE_TYPE::NUMBER_004, D3DXVECTOR3(fPosX + 3 / 2.0f * 30.0f, 600.0f, 0.0f), 30.0f);

			//通常モードの場合非表示
			if (m_apScoreResult[nCnt] != nullptr && !CGameScene::GetWereWolfMode()) {
				m_apScoreResult[nCnt]->SetNumberColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			}
			//人狼モード
			else {
				//スコアの背景の設定
				CObject2D* pScoreBG = CObject2D::Create(D3DXVECTOR3(fPosX, 600.0f + 30.0f / 2, 0.0f), 
					(CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_TYPE::ITEM_UI_FRAME_1 + nCnt), 100.0f, 40.0f);
				if (pScoreBG != nullptr) pScoreBG->SetDrawPriority(CObject::DRAW_PRIORITY::UI_BG);
				//音の再生
				if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);
			}
		}
	}

	//フェーズ切り替え
	if (m_nCntPhase > 270 || (!bWolfMode && m_nCntPhase == 120)) {
		//フェーズの変更
		m_phase = PHASE::RISE_TOWER;
		//カウントリセット
		m_nCntPhase = 0;
	}
}

//=============================================================================
// タワーの上昇処理
//=============================================================================
void CFinalResultScene::RiseTower() {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//カメラの取得
	CCamera* pCamera = nullptr;
	if (pManager != nullptr) pCamera = pManager->GetCamera();

	bool bNextPhase = true;	//次のフェーズへ移行

	m_nCntPhase++;

	const float fSpeedRise = 2.0f;	//上昇速度

	for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
	{
		//スコアが無い場合終了
		if (m_apScoreResult[nCnt] == nullptr) continue;

		//スコアがすでに上限の場合終了
		if (m_apScoreResult[nCnt]->GetScore() >= m_aPlayerScore[nCnt]) {
			//スコアが０の場合後の処理が通らないので、停止時の処理を最初に行う
			if (m_nCntPhase == 1 && m_apScoreResult[nCnt]->GetScore() == 0) {
				//タワー停止時の処理
				StopTower(nCnt);
			}
			continue;
		}

		//まだ終わっていない場合フェーズ移行しない
		bNextPhase = false;

		//塔とプレイヤーを上昇
		if (m_apObjPlayer[nCnt] != nullptr) {
			D3DXVECTOR3 posPlayer = m_apObjPlayer[nCnt]->GetPos();
			posPlayer.y += fSpeedRise;
			m_apObjPlayer[nCnt]->SetPos(posPlayer);
		}
		if (m_apResultTower[nCnt] != nullptr) {
			D3DXVECTOR3 posTower = m_apResultTower[nCnt]->GetPos();
			posTower.y += fSpeedRise;
			m_apResultTower[nCnt]->SetPos(posTower);
		}

		//スコアUIの値の上昇
		const int nSpanAddScore = 6;
		if(m_nCntPhase % nSpanAddScore == 0) m_apScoreResult[nCnt]->AddScore(1);	//数フレーム毎に一度増える
		//最大スコアの更新
		m_nTopScore = max(m_nTopScore, m_apScoreResult[nCnt]->GetScore());

		//スコア分上昇した場合ストップ
		if (m_apScoreResult[nCnt]->GetScore() >= m_aPlayerScore[nCnt]) {
			//タワー停止時の処理
			StopTower(nCnt);
		}
	}

	//次のフェーズへ移行
	if (bNextPhase) {
		//フェーズの変更
		m_phase = PHASE::WINNER;
		//カウントリセット
		m_nCntPhase = 0;
	}
	else if (pCamera != nullptr) {
		D3DXVECTOR3 posCamera = pCamera->GetPos();
		posCamera.y += fSpeedRise;
		//カメラの移動
		pCamera->SetPos(posCamera);
	}
}

//タワー停止時の処理
void CFinalResultScene::StopTower(int nIdxPlayer) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();

	//音の再生
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);
	//エフェクト

	//順位のテクスチャ出してもいいかも

	//人狼モードの場合スコアの色を変更
	if (m_apScoreResult[nIdxPlayer] != nullptr && CGameScene::GetWereWolfMode()) m_apScoreResult[nIdxPlayer]->SetNumberColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
}

//=============================================================================
// 雲移動処理
//=============================================================================
void CFinalResultScene::CloudMove()
{
	//雲の総数取得
	int nCloudNum = m_pCloud.size();

	for (int nCntCloud = 0; nCntCloud < nCloudNum; nCntCloud++)
	{
		//位置取得
		D3DXVECTOR3 pos = m_pCloud[nCntCloud]->GetPos();
		//生成している方向をずらす
		m_fRotCloud[nCntCloud] += m_fMoveSpeedCloud[nCntCloud];
		if (m_fRotCloud[nCntCloud] > D3DX_PI) m_fRotCloud[nCntCloud] -= D3DX_PI * 2.0f;

		//位置を計算
		pos.x = cosf(m_fRotCloud[nCntCloud]) * m_fDifferCloud[nCntCloud];
		pos.z = sinf(m_fRotCloud[nCntCloud]) * m_fDifferCloud[nCntCloud];

		//位置設定
		m_pCloud[nCntCloud]->SetPos(pos);

		//向き取得
		D3DXVECTOR3 rot = m_pCloud[nCntCloud]->GetRot();
		//向きをずらす
		rot.y -= m_fMoveSpeedCloud[nCntCloud];
		if (rot.y < -D3DX_PI) rot.y += D3DX_PI * 2.0f;
		//向き設定
		m_pCloud[nCntCloud]->SetRot(rot);
	}
}

//=============================================================================
// 勝利
//=============================================================================
void CFinalResultScene::Winner() {
	m_nCntPhase++;

	const int nTimeCreateCrown = 180;
	const float fposCrownFirst = 500.0f;	//王冠の初期位置（プレイヤーの位置からの差分）

	if (m_nCntPhase == nTimeCreateCrown) {
		//王冠降りてきたり
		for (int nCnt = 0; nCnt < MAX_OBJECT_PLAYER_NUM; nCnt++)
		{
			if (m_apScoreResult[nCnt] == nullptr || m_apObjPlayer[nCnt] == nullptr) continue;
			if (m_apScoreResult[nCnt]->GetScore() != m_nTopScore) continue;

			D3DXVECTOR3 posPlayer = m_apObjPlayer[nCnt]->GetPos();	//プレイヤーの位置を取得
			posPlayer.y += fposCrownFirst;	//差分を追加
			//王冠を生成
			CObjectModel* pObjCrown = CObjectModel::Create(CModel::MODELTYPE::OBJ_RESULT_CROWN, posPlayer, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
			//オブジェクトの設定
			if (pObjCrown == nullptr) continue;	//ループ飛ばす
			m_vObjCrown.push_back(pObjCrown);	//リストに格納
			pObjCrown->SetRotSpeed(D3DXVECTOR3(0.0f, 0.05f, 0.0f));	//回転させる
			//モデルの設定
			CModel* pModel = pObjCrown->GetPtrModel();
			if (pModel == nullptr) continue;	//ループ飛ばす
			for (int i = 0; i < 3; i++)
			{
				pModel->SetMaterialSpecular(D3DXCOLOR(0.98f, 0.98f, 0.98f, 1.f), i);
				pModel->SetMaterialPower(8.0f, i);
			}
		}
		//紙吹雪降ってきたり

	}

	//王冠の移動
	const float fposCrownDest = 100.0f;	//王冠の目標の位置（プレイヤーの位置からの差分）
	const int nTimeFallCrown = 60;	//王冠が落ちている時間

	//王冠生成後から数秒王冠が落下
	if (m_nCntPhase > nTimeCreateCrown && m_nCntPhase < nTimeCreateCrown + nTimeFallCrown) {
		for (auto& pCrown : m_vObjCrown)
		{
			if (pCrown == nullptr) continue;
			D3DXVECTOR3 posCrown = pCrown->GetPos();
			posCrown.y -= (fposCrownFirst - fposCrownDest) / nTimeFallCrown;
			//位置の設定
			pCrown->SetPos(posCrown);
		}
	}

	//フェーズ終了
	if (m_nCntPhase == 180 + nTimeFallCrown) {
		//フェーズの変更
		m_phase = PHASE::PHASE_FINISH;
		//カウントリセット
		m_nCntPhase = 0;

		//次へボタンの生成
		CNextButton::Create(FINAL_RESULT_SCENE_NEXT_BUTTON_POS, FINAL_RESULT_SCENE_NEXT_BUTTON_SIZE,
		                    CTexture::TEXTURE_TYPE::CHECK_ICON_BUTTON_3, FINAL_RESULT_SCENE_NEXT_BUTTON_COUNTER,
		                    FINAL_RESULT_SCENE_NEXT_BUTTON_DEC_ALPHA);
	}
}

//=============================================================================
// フェーズ終了処理
//=============================================================================
void CFinalResultScene::PhaseFinish() {
	CManager* pManager = CManager::GetManager();	//マネージャーの取得
	if (pManager == nullptr) return;
	CInput* pInput = pManager->GetInputCur();	//入力デバイスへのポインタ
	CFade* pFade = pManager->GetFade();			//フェードへのポインタ
	CSound* pSound = pManager->GetSound();		//サウンドへのポインタ

	//nullの場合終了
	if (pFade == nullptr) return;

	//決定キーが押されたとき
	if (m_bEndScene)
	{
		// 遷移する時間が0より小さくなっていたら
		if (m_nFadeTime < 0)
		{
			//シーン遷移開始			
			pFade->SetFade(CScene::SCENE_TYPE::SELECT_GAME, 0.02f, 60);
			//pFade->SetFade(CScene::SCENE_TYPE::FINAL_RESULT, 0.02f, 60);
		}
		else
		{
			//フェード開始カウント減少
			m_nFadeTime--;
		}

		//入力処理を受け付けず終了
		return;
	}


	//nullの場合終了
	if (pInput == nullptr) return;

	//決定キーを押したとき
	if (pInput->GetTrigger(CInput::CODE::SELECT, 0))
	{
		// 押されたフラグ
		m_bEndScene = true;
		//決定音の再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_DECIDE);
	}
}

//=============================================================================
//風船生成処理
//=============================================================================
void CFinalResultScene::CreateBalloon()
{
	m_fBalloonCreateCounter++;
	if (m_fBalloonCreateCounter <= FINAL_RESULT_SCENE_BALLOON_CREATE_INTERVAL) return;

	for (int nCntBalloon = 0; nCntBalloon < FINAL_RESULT_SCENE_BALLOON_CREATE_NUM; nCntBalloon++)
	{
		//生成する場所の設定
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, FINAL_RESULT_SCENE_BALLOON_CREATE_POS, 0.0f);
		//生成場所の設定

		//中心からの距離の設定
		float fDiffer = FINAL_RESULT_SCENE_BALLOON_DIFFER;
		//向きをランダムで決める
		float fRot = FINAL_RESULT_SCENE_CLOUD_ROT;

		//生成位置の設定
		pos.y += FINAL_RESULT_SCENE_BALLOON_CREATE_POS_Y_RAND;
		pos.x += cosf(fRot) * fDiffer;
		pos.z += sinf(fRot) * fDiffer;

		//移動量を設定
		float fMoveSpeed = FINAL_RESULT_SCENE_BALLOON_MOVE_SPEED;

		//モデルの種類
		int nModelNum = static_cast<int>(CModel::MODELTYPE::OBJ_RESULT_BALLOON_02) + 1 - static_cast<int>(CModel::MODELTYPE::OBJ_RESULT_BALLOON_00);

		//モデルをランダムで設定
		int nModel = (rand() % nModelNum) + static_cast<int>(CModel::MODELTYPE::OBJ_RESULT_BALLOON_00);


		//風船の生成
		CFloatObject* pBallon = CFloatObject::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, fMoveSpeed, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), static_cast<CModel::MODELTYPE>(nModel));
		//風船の設定
		if (pBallon != nullptr) {
			//スペキュラーの設定
			CModel *pModel = pBallon->GetPtrModel();
			if (pModel != nullptr)
			{
				const D3DXCOLOR colSpecular = D3DXCOLOR(0.98f, 0.98f, 0.98f, 1.0f);	//スペキュラーの色
				for (int nIdxMat = 0; nIdxMat < MAX_MATERIAL; nIdxMat++)
				{
					pModel->SetMaterialSpecular(colSpecular, nIdxMat);
					pModel->SetMaterialPower(12.0f, nIdxMat);
				}
			}
			//リストに風船を追加
			m_pBalloon.push_back(pBallon);
		}
	}
	
	//初期化
	m_fBalloonCreateCounter = 0;
}

//=============================================================================
//風船移動処理
//=============================================================================
void CFinalResultScene::BalloonMove()
{
	//風船の総数取得
	int nNum = m_pBalloon.size();

	for (int nCntBalloon = 0; nCntBalloon < nNum; nCntBalloon++)
	{
		//位置取得
		D3DXVECTOR3 pos = m_pBalloon[nCntBalloon]->GetPos();

		if (pos.y < FINAL_RESULT_SCENE_BALLOON_UNINIT_POS_Y) continue;
		//上限になったら
		//消す
		m_pBalloon[nCntBalloon]->Uninit();
		m_pBalloon[nCntBalloon] = nullptr;
		m_pBalloon.erase(m_pBalloon.begin() + nCntBalloon);

		//総数を減らす
		nNum--;
		nCntBalloon--;
	}
}