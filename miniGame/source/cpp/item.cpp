//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "item.h"
#include "manager.h"
#include "sound.h"
#include "objectList.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ITEM_PLAYER_COLL_SIZE	(30.0f)		//プレイヤーの当たり判定の大きさ半径

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CItem::CItem()
{
	
}

//=============================================================================
// オーバーロードされたコンストラクタ
//=============================================================================
CItem::CItem(CModel::MODELTYPE typeModel) : CObjectModel(typeModel, false)
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CItem::~CItem()
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CItem* CItem::Create(D3DXVECTOR3 pos) {
	
	//デフォルトのモデルを設定
	CModel::MODELTYPE typeModel = CModel::MODELTYPE::OBJ_ITEM_BOX;

	CItem* pItem;
	pItem = new CItem(typeModel);
	if (pItem == nullptr) return nullptr;

	pItem->SetPos(pos);
	
	pItem->Init();

	return pItem;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItem::Init(void) {

	CObjectModel::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItem::Uninit(void) {

	CObjectModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItem::Update(void) {

	CObjectModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CItem::Draw(void) {
	CObjectModel::Draw();
}

//=============================================================================
//プレイヤーとの当たり判定
//=============================================================================
bool CItem::CollisionPlayer(CPlayer *&pReturnPlayer, const float fMySize)
{
	CObject* pObject = GetObjectTopAll();	//全オブジェクトのリストの先頭を取得
	D3DXVECTOR3 posBullet = GetPos();	//弾の位置

	while (pObject != nullptr) {
		CObject* pObjNext = GetObjectNextAll(pObject);	//リストの次のオブジェクトのポインタを取得

		//オブジェクトタイプの確認
		bool bMatchType = false;
		if (pObject->GetObjType() & OBJTYPE_PLAYER) bMatchType = true;

		if (!bMatchType)
		{
			pObject = pObjNext;	//リストの次のオブジェクトを代入
			continue;
		}

		//プレイヤーにキャスト
		CPlayer *pPlayer = static_cast<CPlayer*> (pObject);

		//プレイヤーの位置を取得
		D3DXVECTOR3 playerPos = pPlayer->GetPos();
		//風船の位置取得
		D3DXVECTOR3 balloonPos = GetPos();

		//二点の距離ベクトル
		D3DXVECTOR2 differVec = D3DXVECTOR2(playerPos.x - balloonPos.x, playerPos.z - balloonPos.z);
		//二点の距離
		float fDiffer = D3DXVec2Length(&differVec);

		//当たっていたら
		if (fDiffer <= ITEM_PLAYER_COLL_SIZE + fMySize)
		{
			pReturnPlayer = pPlayer;
			return true;
		}

		pObject = pObjNext;	//リストの次のオブジェクトを代入
	}

	return false;
}
