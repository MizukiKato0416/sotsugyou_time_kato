//=============================================================================
//
// アイテム盾処理 [item_shield.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "item_shield.h"
#include "manager.h"
#include "sound.h"
#include "object_player_attack_car.h"
#include "player.h"
#include "input.h"
//エフェクト
#include "PresetSetEffect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ITEM_SHIELD_SIZE				(50.0f)		//盾のサイズ半径
#define ITEM_SHIELD_GRAVITY				(0.12f)		//盾の重力
#define ITEM_SHIELD_DELETE_COUNT		(360)		//盾の消えるまでの時間
#define ITEM_SHIELD_COLL_HEIGHT			(30.0f)		//当たり判定をし始める高さ
#define ITEM_SHIELD_ROTATE_SPEED		(0.08f)		//回転速度

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CItemShield::CItemShield()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_pSphereCover = nullptr;
}

//=============================================================================
// オーバーロードされたコンストラクタ
//=============================================================================
CItemShield::CItemShield(CModel::MODELTYPE typeModel) : CItem(typeModel)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_pSphereCover = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemShield::~CItemShield()
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CItemShield* CItemShield::Create(D3DXVECTOR3 pos) {
	
	//デフォルトのモデルを設定
	CItemShield* pItemShield;
	pItemShield = new CItemShield(CModel::MODELTYPE::OBJ_ITEM_SHIELD);
	if (pItemShield == nullptr) return nullptr;

	pItemShield->SetPos(pos);
	pItemShield->Init();

	return pItemShield;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemShield::Init(void) {

	//球体の生成
	m_pSphereCover = CObjectModel::Create(CModel::MODELTYPE::OBJ_SPHERE_COVER, GetPos() , D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	if (m_pSphereCover != nullptr) {
		m_pSphereCover->SetDrawPriority(CObject::DRAW_PRIORITY::CLEAR);
		m_pSphereCover->SetDrawZTex(false);
		CModel* pModel = m_pSphereCover->GetPtrModel();
		if (pModel != nullptr) {
			pModel->SetColorGlow(D3DXCOLOR(0.0f, 1.0f, 0.8f, 1.0f));
			pModel->SetPowerGlow(1.5f);
		}
	}


	//変数初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;

	CItem::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItemShield::Uninit(void) {

	//消す
	if (m_pSphereCover != nullptr)
	{
		m_pSphereCover->Uninit();
		m_pSphereCover = nullptr;
	}

	CItem::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemShield::Update(void) {

	m_nCounter++;
	if (m_nCounter > ITEM_SHIELD_DELETE_COUNT)
	{
		m_nCounter = 0;
		//消す
		//Uninit();
		return;
	}

	//移動処理
	Move();

	//回転処理
	Rotate();

	//プレイヤーとの当たり判定
	if (CollisionPlayer(ITEM_SHIELD_SIZE, ITEM_SHIELD_COLL_HEIGHT))
	{
		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		//サウンドの取得
		CSound *pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_SHIELD_GET);

		//当たっていたら消す
		Uninit();
		return;
	}

	CItem::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CItemShield::Draw(void) {
	CItem::Draw();
}

//=============================================================================
// 移動処理
//=============================================================================
void CItemShield::Move(void) {

	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//重力加算
	m_move.y -= ITEM_SHIELD_GRAVITY;
	//位置加算
	pos += m_move;

	//地面についたら
	if (pos.y < 0.0f)
	{
		//止める
		pos.y = 0.0f;
	}

	//位置設定
	SetPos(pos);

	//球体が生成されていたら
	if (m_pSphereCover != nullptr)
	{
		//位置をアイテムに合わせる
		m_pSphereCover->SetPos(pos);
	}
}

//=============================================================================
// 回転処理 
//=============================================================================
void CItemShield::Rotate(void) {

	//向き取得
	D3DXVECTOR3 rot = GetRot();
	//加算
	rot.y += ITEM_SHIELD_ROTATE_SPEED;

	//πを超えたとき
	if (rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	else if(rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}

	//向き設定
	SetRot(rot);
}

//=============================================================================
//プレイヤーにヒットしたときの処理
//=============================================================================
void CItemShield::HitPlayer(CObjectPlayer * pPlayer)
{
	//プレイヤーにキャスト
	CObjectPlayerAttackCar *pAttackCar = dynamic_cast<CObjectPlayerAttackCar*>(pPlayer);
	if (pAttackCar == nullptr)
	{
		return;
	}

	//ディフェンス状態でないなら
	if (!pAttackCar->GetDefence())
	{
		//ディフェンス状態にする
		pAttackCar->SetDefence(true);
	}
	//ディフェンスカウンターをリセット
	pAttackCar->SetDefenceCounter(0);
}