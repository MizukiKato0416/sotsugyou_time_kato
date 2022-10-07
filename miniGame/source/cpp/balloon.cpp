//=============================================================================
//
// 風船処理 [balloon.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "balloon.h"
#include "manager.h"
#include "sound.h"
#include "objectList.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BALLOON_PLAYER_COLL_SIZE	(30.0f)		//当たり判定の時のプレイヤーのサイズ
#define BALLOON_ADD_MOVE			(0.02f)		//風船の加速量
#define BALLOON_MAX_MOVE			(0.2f)		//風船の最大移動量
#define BALLOON_UP_POS				(50.0f)		//風船の上がる位置
#define BALLOON_DOWN_POS			(40.0f)		//風船の下がる位置

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int CBalloon::m_nNum = 0;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CBalloon::CBalloon()
{
	m_nNum++;

	m_bGold = false;
	m_bUp = false;
	m_move = { 0.0f, 0.0f, 0.0f };
}

//=============================================================================
// オーバーロードされたコンストラクタ
//=============================================================================
CBalloon::CBalloon(CModel::MODELTYPE typeModel) : CObjectModel(typeModel, false)
{
	m_nNum++;

	m_bGold = false;
	m_bUp = false;
	m_move = { 0.0f, 0.0f, 0.0f };
}

//=============================================================================
// デストラクタ
//=============================================================================
CBalloon::~CBalloon()
{
	m_nNum--;
}

//=============================================================================
// 生成処理
//=============================================================================
CBalloon* CBalloon::Create(bool bGold, D3DXVECTOR3 pos) {
	
	//デフォルトのモデルを設定
	CModel::MODELTYPE typeModel = CModel::MODELTYPE::OBJ_BALLOON_PINK;
	
	//金色に設定されていたら
	if (bGold)
	{
		typeModel = CModel::MODELTYPE::OBJ_BALLOON_GOLD;
	}

	CBalloon* pBalloon;
	pBalloon = new CBalloon(typeModel);
	if (pBalloon == nullptr) return nullptr;

	pBalloon->SetPos(pos);
	pBalloon->m_bGold = bGold;
	
	pBalloon->Init();

	return pBalloon;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBalloon::Init(void) {
	
	m_move = { 0.0f, 0.0f, 0.0f };
	m_bUp = true;

	//CModel *pModel = GetPtrModel();
	//if (pModel!= nullptr)
	//{
	//	pModel->SetMaterialSpecular(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),0);
	//}

	CObjectModel::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBalloon::Uninit(void) {

	CObjectModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBalloon::Update(void) {
	
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//加速
	if (m_bUp)
	{
		m_move.y += BALLOON_ADD_MOVE;

		if (pos.y > BALLOON_UP_POS)
		{
			m_bUp = false;
		}
	}
	else
	{
		m_move.y -= BALLOON_ADD_MOVE;

		if (pos.y < BALLOON_DOWN_POS)
		{
			m_bUp = true;
		}
	}

	if (m_move.y > BALLOON_MAX_MOVE)
	{
		m_move.y = BALLOON_MAX_MOVE;
	}
	else if (m_move.y < -BALLOON_MAX_MOVE)
	{
		m_move.y = -BALLOON_MAX_MOVE;
	}

	//移動量を設定
	pos += m_move;

	SetPos(pos);

	//プレイヤーとの当たり判定
	if (CollisionPlayer())
	{
		//当たっていたら消す
		Uninit();
		return;
	}

	CObjectModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CBalloon::Draw(void) {
	CObjectModel::Draw();
}

//=============================================================================
//プレイヤーとの当たり判定
//=============================================================================
bool CBalloon::CollisionPlayer(void)
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
		if (fDiffer <= BALLOON_PLAYER_COLL_SIZE + BALLOON_SIZE)
		{
			return true;
		}

		pObject = pObjNext;	//リストの次のオブジェクトを代入
	}

	return false;
}
