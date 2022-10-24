//=============================================================================
//
// ボム処理 [bom.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "bom.h"
#include "manager.h"
#include "sound.h"
#include "objectList.h"
#include "object_player_attack_car.h"
#include "sound.h"
#include "gameScene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BOM_PLAYER_COLL_SIZE	(30.0f)		//プレイヤーの当たり判定の大きさ半径
#define BOM_SIZE				(80.0f)		//ボムのサイズ半径
#define BOM_GRAVITY				(0.1f)		//ボムの重力
#define BOM_COLL_POS_Y			(20.0f)		//当たり判定をし始める高さ
#define BOM_COLL_PLAYER_BOUND	(150.0f)	//プレイヤーを飛ばす量

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CBom::CBom()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// オーバーロードされたコンストラクタ
//=============================================================================
CBom::CBom(CModel::MODELTYPE typeModel) : CObjectModel(typeModel, false)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CBom::~CBom()
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CBom* CBom::Create(D3DXVECTOR3 pos) {

	//デフォルトのモデルを設定
	CModel::MODELTYPE typeModel = CModel::MODELTYPE::OBJ_BOM;

	CBom* pBom;
	pBom = new CBom(typeModel);
	if (pBom == nullptr) return nullptr;

	pBom->SetPos(pos);
	
	pBom->Init();

	return pBom;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBom::Init(void) {

	//変数初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CObjectModel::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBom::Uninit(void) {

	CObjectModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBom::Update(void) {

	//ゲームオーバーなら
	if (CManager::GetManager()->GetGameScene()->GetGameOver())
	{
		//消す
		Uninit();
		return;
	}

	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//重力設定
	m_move.y -= BOM_GRAVITY;

	//移動量設定
	pos += m_move;

	//地面についたら
	if (pos.y <= 0.0f)
	{
		//爆発音再生
		ExplosionSound();
		//消す
		Uninit();
		return;
	}

	//位置設定
	SetPos(pos);

	//プレイヤーとの当たり判定
	if (CollisionPlayer())
	{
		//爆発音再生
		ExplosionSound();
		//消す
		Uninit();
		return;
	}

	CObjectModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CBom::Draw(void) {
	CObjectModel::Draw();
}

//=============================================================================
//プレイヤーとの当たり判定
//=============================================================================
bool CBom::CollisionPlayer(void)
{
	CObject* pObject = GetObjectTopAll();	//全オブジェクトのリストの先頭を取得

	while (pObject != nullptr) {
		CObject* pObjNext = GetObjectNextAll(pObject);	//リストの次のオブジェクトのポインタを取得

		//オブジェクトタイプの確認
		bool bMatchType = false;
		if (pObject->GetObjType() & OBJTYPE_PLAYER) bMatchType = true;

		if (!bMatchType || GetPos().y > BOM_COLL_POS_Y)
		{
			pObject = pObjNext;	//リストの次のオブジェクトを代入
			continue;
		}

		//プレイヤーにキャスト
		CObjectPlayerAttackCar *pPlayer = static_cast<CObjectPlayerAttackCar*> (pObject);

		//プレイヤーの位置を取得
		D3DXVECTOR3 playerPos = pPlayer->GetPos();
		//風船の位置取得
		D3DXVECTOR3 balloonPos = GetPos();

		//二点の距離ベクトル
		D3DXVECTOR2 differVec = D3DXVECTOR2(playerPos.x - balloonPos.x, playerPos.z - balloonPos.z);
		//二点の距離
		float fDiffer = D3DXVec2Length(&differVec);

		//当たっていたら
		if (fDiffer <= BOM_PLAYER_COLL_SIZE + BOM_SIZE)
		{
			float fRot = 0.0f;
			//向きをランダムで決める
			fRot = (rand() % 629 + -314) / 100.0f;

			//相手のバウンド移動量取得
			D3DXVECTOR3 move = pPlayer->GetBoundMove();
			//跳ね返させる
			move.x += sinf(fRot) * BOM_COLL_PLAYER_BOUND;
			move.z += cosf(fRot) * BOM_COLL_PLAYER_BOUND;
			//相手のバウンド移動量設定
			pPlayer->SetBoundMove(move);
			return true;
		}

		pObject = pObjNext;	//リストの次のオブジェクトを代入
	}

	return false;
}

//=============================================================================
//爆発音再生
//=============================================================================
void CBom::ExplosionSound()
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	//サウンドの取得
	CSound *pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//音再生
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_EXPLOSION);
}
