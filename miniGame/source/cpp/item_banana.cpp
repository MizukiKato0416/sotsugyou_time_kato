//=============================================================================
//
// アイテムバナナ処理 [item_banana.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "item_banana.h"
#include "manager.h"
#include "sound.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ITEM_BANANA_SIZE				(30.0f)		//バナナのサイズ半径

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CItemBanana::CItemBanana()
{
	
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
CItemBanana* CItemBanana::Create(D3DXVECTOR3 pos) {
	
	//デフォルトのモデルを設定
	CItemBanana* pItemBanana;
	pItemBanana = new CItemBanana(CModel::MODELTYPE::OBJ_BANANA);
	if (pItemBanana == nullptr) return nullptr;

	pItemBanana->SetPos(pos);
	
	pItemBanana->Init();

	return pItemBanana;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemBanana::Init(void) {

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

	//プレイヤーとの当たり判定
	if (CollisionPlayer(ITEM_BANANA_SIZE))
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