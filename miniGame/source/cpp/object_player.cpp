//=============================================================================
//
// オブジェクトプレイヤー処理 [object_player.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "object_player.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "input.h"
#include "gameScene.h"

#include "wallCylinder.h"
#include "effect.h"
#include "object2D.h"
#include "billboard.h"
#include "item_banana.h"

#include "PresetSetEffect.h"
#include "score_ui.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================

//--------------------------------
//当たり判定
//--------------------------------
#define COLLISION_RADIUS (40.0f)		//当たり判定の半径	壁とかに使う

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CObjectPlayer::CObjectPlayer() : CObjectModel(CModel::MODELTYPE::OBJ_CAR, false)
{
	SetObjType(OBJTYPE_PLAYER);						//オブジェクトタイプの設定
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);		//更新順の設定
	SetDrawPriority(DRAW_PRIORITY::CHARA);			//描画順の設定
	m_itemType = CItem::ITEM_TYPE::NONE;

	//SetDrawStencilZ(true);
	m_pPlayer = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObjectPlayer::~CObjectPlayer()
{
	
}

//=============================================================================
// プレイヤーの生成処理
//=============================================================================
CObjectPlayer* CObjectPlayer::Create(D3DXVECTOR3 pos) {
	CObjectPlayer* pObjectPlayer;
	pObjectPlayer = new CObjectPlayer();
	if (pObjectPlayer == nullptr) return nullptr;

	pObjectPlayer->SetPos(pos);
	pObjectPlayer->Init();

	return pObjectPlayer;
}

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CObjectPlayer::Init(void) {
	//プレイヤーの初期設定
	CObjectModel::SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//マネージャーの取得
	CManager* pManager = CManager::GetManager();

	CObjectModel::Init();

	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create();


	//プレイヤー番号によって色を変える
	switch (m_pPlayer->GetIndex())
	{
	case 1:
		col = OBJECT_PLAYER_COLOR_1P;
		break;
	case 2:
		col = OBJECT_PLAYER_COLOR_2P;
		break;
	case 3:
		col = OBJECT_PLAYER_COLOR_3P;
		break;
	case 4:
		col = OBJECT_PLAYER_COLOR_4P;
		break;
	default:
		break;
	}

	//モデル取得
	CModel *pModel = GetPtrModel();
	if (pModel!= nullptr)
	{
		//指定したマテリアルの色を設定
		pModel->SetMaterialDiffuse(col, 0);
		pModel->SetMaterialSpecular(col / 2.0f + D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f), 0);
		pModel->SetMaterialPower(2.0f, 0);

	}

	return S_OK;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CObjectPlayer::Uninit(void) {
	//終了処理
	CObjectModel::Uninit();
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CObjectPlayer::Update(void) {
	//更新しない設定なら
	if (!m_pPlayer->GetUpdate())
	{
		return;
	}

	//----------------------------
	//モデルの更新
	//----------------------------
	CObjectModel::Update();
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CObjectPlayer::Draw(void) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;
	//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;

	CObjectModel::Draw();
}

//=============================================================================
// プレイヤーのゲームオーバー時の処理
//=============================================================================
void CObjectPlayer::GameOver(void) {
	
}

//=============================================================================
// プレイヤーの当たり判定の半径の取得
//=============================================================================
float CObjectPlayer::GetRadius(void) {
	return COLLISION_RADIUS;
}