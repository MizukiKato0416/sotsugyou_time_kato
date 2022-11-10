//=============================================================================
//
// アイテムバナナ処理 [item_banana.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "item_banana.h"
#include "manager.h"
#include "sound.h"
#include "object_player_balloon_car.h"
#include "player.h"
#include "wallCylinder.h"
#include "object2D.h"
#include "input.h"
//エフェクト
#include "PresetSetEffect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ITEM_BANANA_SIZE				(50.0f)		//バナナのサイズ半径
#define ITEM_BANANA_ROTATE_SPEED		(0.08f)		//バナナの回転の速さ
#define ITEM_BANANA_MOVE_SPEED			(25.0f)		//バナナの移動の速さ
#define ITEM_BANANA_COLL_HEIGHT			(1000.0f)	//バナナの当たり判定をし始める高さ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CItemBanana::CItemBanana()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// オーバーロードされたコンストラクタ
//=============================================================================
CItemBanana::CItemBanana(CModel::MODELTYPE typeModel) : CItem(typeModel)
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemBanana::~CItemBanana()
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CItemBanana* CItemBanana::Create(D3DXVECTOR3 pos, CObjectPlayerBalloonCar *pPlayer) {
	
	//デフォルトのモデルを設定
	CItemBanana* pItemBanana;
	pItemBanana = new CItemBanana(CModel::MODELTYPE::OBJ_BANANA);
	if (pItemBanana == nullptr) return nullptr;

	pItemBanana->SetPos(pos);
	pItemBanana->m_pPlayer = pPlayer;
	pItemBanana->Init();

	return pItemBanana;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemBanana::Init(void) {

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound *pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//音再生
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_BANANA_THROW);

	//プレイヤーの向き取得
	float fRot = m_pPlayer->GetRot().y;

	//移動量の設定
	m_move.x = sinf(fRot + D3DX_PI) * ITEM_BANANA_MOVE_SPEED;
	m_move.z = cosf(fRot + D3DX_PI) * ITEM_BANANA_MOVE_SPEED;

	CItem::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItemBanana::Uninit(void) {

	CItem::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemBanana::Update(void) {

	//向き取得
	D3DXVECTOR3 rot = GetRot();
	//回転させる
	rot.y += ITEM_BANANA_ROTATE_SPEED;
	//向き設定
	SetRot(rot);


	//位置取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 lastPos = GetPos();
	//移動量を設定
	pos += m_move;

	//壁との当たり判定
	if (CWallCylinder::Collision(&pos, lastPos, ITEM_BANANA_SIZE))
	{
		//当たっていたら消す
		Uninit();
		return;
	}

	//位置設定
	SetPos(pos);

	//プレイヤーとの当たり判定
	if (CollisionPlayer(ITEM_BANANA_SIZE, ITEM_BANANA_COLL_HEIGHT))
	{
		
		//当たっていたら消す
		Uninit();
		return;
	}

	CItem::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CItemBanana::Draw(void) {
	CItem::Draw();
}

//=============================================================================
//プレイヤーにヒットしたときの処理
//=============================================================================
void CItemBanana::HitPlayer(CObjectPlayer * pPlayer)
{
	CObjectPlayerBalloonCar *pBalloonCar = dynamic_cast<CObjectPlayerBalloonCar*>(pPlayer);

	if (pBalloonCar == nullptr)
	{
		return;
	}

	//プレイヤーが通常状態だったら
	if (pBalloonCar->GetState() == CObjectPlayerBalloonCar::OBJECT_PLAYER_BALLOON_CAR_STATE::NORMAL)
	{
		//プレイヤーの状態をスピン状態にする
		pBalloonCar->SetState(CObjectPlayerBalloonCar::OBJECT_PLAYER_BALLOON_CAR_STATE::SPIN);

		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		CInput* pInput = nullptr;
		CInputGamepadX *pPadX = nullptr;
		if (pManager != nullptr) {
			//現在の入力デバイスの取得
			pInput = pManager->GetInputCur();
			pPadX = dynamic_cast<CInputGamepadX*>(pInput);
		}

		if (pPadX != nullptr)
		{
			//振動させる
			pPadX->SetVibration(65535, 65535, 40, pBalloonCar->GetPlayer()->GetIndex() - 1);
		}

		//ーーーーーーーーーーーーーーーーーーー
		//スピン(バナナヒット)
		CPresetEffect::SetEffect3D(8, D3DXVECTOR3(pBalloonCar->GetPos().x, pBalloonCar->GetPos().y + 1, pBalloonCar->GetPos().z), {}, {});		//回るやつ
		//ーーーーーーーーーーーーーーーーーーー

		//サウンドの取得
		CSound *pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_PLAYER_SPIN);
	}
}