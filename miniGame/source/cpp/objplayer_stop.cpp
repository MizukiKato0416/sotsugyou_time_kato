//=============================================================================
//
// 止まる車処理 [objplayer_stop.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "objplayer_stop.h"

#include "billboard.h"
#include "camera.h"
#include "effect.h"
#include "gameScene.h"
#include "gameScene03.h"
#include "input.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"
#include "renderer.h"
#include "score_ui.h"
#include "score.h"
#include "sound.h"

//エフェクト
#include "PresetSetEffect.h"
#include "PresetDelaySet.h"


//=============================================================================
// マクロ定義
//=============================================================================

//--------------------------------
//移動
//--------------------------------
#define ADD_MOVE_SPEED	(0.5f)			//加速

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObjplayerStop::CObjplayerStop() : m_fSpeedMax(30.0f)
{
	SetObjType(OBJTYPE_PLAYER);						//オブジェクトタイプの設定
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);		//更新順の設定
	SetDrawPriority(DRAW_PRIORITY::CHARA);			//描画順の設定

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_itemType = CItem::ITEM_TYPE::NONE;
}

//=============================================================================
// オーバーロードされたコンストラクタ
//=============================================================================
CObjplayerStop::CObjplayerStop(float fSpeedMax) : m_fSpeedMax(fSpeedMax)
{
	SetObjType(OBJTYPE_PLAYER);						//オブジェクトタイプの設定
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);		//更新順の設定
	SetDrawPriority(DRAW_PRIORITY::CHARA);			//描画順の設定

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_itemType = CItem::ITEM_TYPE::NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObjplayerStop::~CObjplayerStop()
{

}

//=============================================================================
// プレイヤーの生成処理
//=============================================================================
CObjplayerStop* CObjplayerStop::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeedMax) {

	CObjplayerStop* pObjectPlayer;
	pObjectPlayer = new CObjplayerStop(fSpeedMax);
	if (pObjectPlayer == nullptr) return nullptr;

	pObjectPlayer->Init();
	pObjectPlayer->SetPos(pos);
	pObjectPlayer->SetRot(rot);

	return pObjectPlayer;
}

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CObjplayerStop::Init(void) {

	CObjectPlayer::Init();

	//プレイヤーの初期設定
	m_itemType = CItem::ITEM_TYPE::NONE;

	m_move = D3DXVECTOR3(0.f, 0.f, 0.f);

	return S_OK;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CObjplayerStop::Uninit(void) {

	CObjectPlayer::Uninit();
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CObjplayerStop::Update(void) {
	//更新しない設定なら
	if (!GetPlayer()->GetUpdate())
	{
		return;
	}

	//移動
	if (!m_bStopMove) Move();

	CObjectPlayer::Update();
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CObjplayerStop::Draw(void) {

	CObjectPlayer::Draw();
}

//=============================================================================
// プレイヤーのゲームオーバー時の処理
//=============================================================================
void CObjplayerStop::GameOver(void) {

	CObjectPlayer::GameOver();
}

//=============================================================================
// 移動
//=============================================================================
void CObjplayerStop::Move(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();

	CInput* pInput = nullptr;
	CSound *pSound = nullptr;

	if (pManager != nullptr) {
		//現在の入力デバイスの取得
		pInput = pManager->GetInputCur();
		//サウンドの取得
		pSound = pManager->GetSound();
	}

	//位置情報のポインタの取得
	D3DXVECTOR3 posObjectPlayer = GetPos();
	//移動
	posObjectPlayer += m_move;
	//位置設定
	SetPos(posObjectPlayer);

	bool bWolf = CGameScene::GetWereWolfPlayerIndex() == GetPlayer()->GetIndex();		//人狼のプレイヤー
	bool bVibArea = int(posObjectPlayer.x + 20) % int(GAME03_ONE_METER * 100) < 50;		//バイブ有効エリア 100mごとの位置の-20から+30のエリア

	//人狼時の処理
	if (CGameScene::GetWereWolfMode() && bWolf && bVibArea) {
		CInputGamepadX* pPadX = dynamic_cast<CInputGamepadX*>(pInput);	//Xパッドの取得

		if (pPadX != nullptr)
		{
			//振動させる
			pPadX->SetVibration(2000, 2000, 20, GetPlayer()->GetIndex() - 1);
		}
	}

	//加速
	if (m_move.x < m_fSpeedMax) {
		m_move.x += ADD_MOVE_SPEED;
		if (m_move.x > m_fSpeedMax) m_move.x = m_fSpeedMax;
	}
	//Aボタンを押したら
	else if (pInput->GetTrigger(CInput::CODE::CHECK_A, GetPlayer()->GetIndex() - 1) && m_bCanStop) {
		//停止処理
		StopMove(false);
	}
	//土埃
	CPresetEffect::SetEffect3D(1, GetPos(), {}, {});
}

//=============================================================================
// 移動量の減少
//=============================================================================
void CObjplayerStop::StopMove(bool bForced) {
	m_bStopMove = true;

	//停止
	m_move = D3DXVECTOR3(0.f, 0.f, 0.f);

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//音再生
	if (pSound != nullptr) {
		//強制的に止まったかどうか
		if (bForced) {
			pSound->PlaySound(CSound::SOUND_LABEL::SE_CRASHSTOP);
		}
		else {
			pSound->PlaySound(CSound::SOUND_LABEL::SE_CRASH);
		}
	}
}