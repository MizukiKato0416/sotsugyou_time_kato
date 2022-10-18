//=============================================================================
//
// アイテムボックス処理 [itemBox.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "itemBox.h"
#include "manager.h"
#include "sound.h"
#include "objectList.h"
#include "object_player.h"
#include "sound.h"
#include "gameScene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ITEMBOX_PLAYER_COLL_SIZE	(30.0f)		//プレイヤーの当たり判定の大きさ半径
#define ITEMBOX_SIZE				(50.0f)		//アイテムボックスのサイズ半径
#define ITEMBOX_UNINIT_POS_X		(1200.0f)	//消える位置
#define ITEMBOX_UNINIT_POS_Z		(1200.0f)	//消える位置
#define ITEMBOX_ROTATE_SPEED		(0.02f)		//回転スピード

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int CItemBox::m_nNum = 0;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CItemBox::CItemBox()
{
	m_nNum++;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// オーバーロードされたコンストラクタ
//=============================================================================
CItemBox::CItemBox(CModel::MODELTYPE typeModel) : CObjectModel(typeModel, false)
{
	m_nNum++;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemBox::~CItemBox()
{
	m_nNum--;
}

//=============================================================================
// 生成処理
//=============================================================================
CItemBox* CItemBox::Create(D3DXVECTOR3 pos) {

	//デフォルトのモデルを設定
	CModel::MODELTYPE typeModel = CModel::MODELTYPE::OBJ_ITEM_BOX;

	CItemBox* pItemBox;
	pItemBox = new CItemBox(typeModel);
	if (pItemBox == nullptr) return nullptr;

	pItemBox->SetPos(pos);
	
	pItemBox->Init();

	return pItemBox;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemBox::Init(void) {

	//変数初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CObjectModel::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItemBox::Uninit(void) {

	CObjectModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemBox::Update(void) {

	//ゲームオーバーなら
	if (CManager::GetManager()->GetGameScene()->GetGameOver())
	{
		//消す
		Uninit();
		return;
	}

	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//移動量設定
	pos += m_move;

	//範囲から出たら
	if (pos.x > ITEMBOX_UNINIT_POS_X || pos.x < -ITEMBOX_UNINIT_POS_X ||
		pos.z > ITEMBOX_UNINIT_POS_Z || pos.z < -ITEMBOX_UNINIT_POS_Z)
	{
		//消す
		Uninit();
		return;
	}

	//位置設定
	SetPos(pos);

	//回るようにする
	SetRotSpeed(D3DXVECTOR3(0.0f, ITEMBOX_ROTATE_SPEED, 0.0f));

	//プレイヤーとの当たり判定
	if (CollisionPlayer())
	{
		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		//サウンドの取得
		CSound *pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音再生
		if(pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_ITEM_GET);

		//当たっていたら消す
		Uninit();
		return;
	}

	CObjectModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CItemBox::Draw(void) {
	CObjectModel::Draw();
}

//=============================================================================
//プレイヤーとの当たり判定
//=============================================================================
bool CItemBox::CollisionPlayer(void)
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
		CObjectPlayer *pPlayer = static_cast<CObjectPlayer*> (pObject);

		//プレイヤーの位置を取得
		D3DXVECTOR3 playerPos = pPlayer->GetPos();
		//風船の位置取得
		D3DXVECTOR3 balloonPos = GetPos();

		//二点の距離ベクトル
		D3DXVECTOR2 differVec = D3DXVECTOR2(playerPos.x - balloonPos.x, playerPos.z - balloonPos.z);
		//二点の距離
		float fDiffer = D3DXVec2Length(&differVec);

		//当たっていたら
		if (fDiffer <= ITEMBOX_PLAYER_COLL_SIZE + ITEMBOX_SIZE)
		{
			//何もアイテムを持っていない状態なら
			if (pPlayer->GetItemType() == CItem::ITEM_TYPE::NONE)
			{
				//アイテムの中からランダムで取得させる
				int nRandItem = rand() % int(int(CItem::ITEM_TYPE::MAX) - 1) + 1;

				//アイテムを取得させる
				pPlayer->SetItemType((CItem::ITEM_TYPE)nRandItem);
			}
			return true;
		}

		pObject = pObjNext;	//リストの次のオブジェクトを代入
	}

	return false;
}
