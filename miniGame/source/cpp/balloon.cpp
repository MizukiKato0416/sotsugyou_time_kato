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
#include "object_player_balloon_car.h"
#include "score.h"
#include "score_ui.h"
#include "gameScene.h"

//エフェクト
#include "PresetSetEffect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BALLOON_PLAYER_COLL_SIZE	(30.0f)		//当たり判定の時のプレイヤーのサイズ
#define BALLOON_ADD_MOVE			(0.02f)		//風船の加速量
#define BALLOON_MAX_MOVE			(0.2f)		//風船の最大移動量
#define BALLOON_UP_POS				(20.0f)		//風船の上がる位置
#define BALLOON_DOWN_POS			(10.0f)		//風船の下がる位置
#define BALLOON_NORMAL_SCORE		(1)			//風船のポイント(通常)
#define BALLOON_GOLD_SCORE			(3)			//風船のポイント(ゴールド)

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

	CModel *pModel = GetPtrModel();
	if (pModel != nullptr)
	{
		for (int nIdxMat = 0; nIdxMat < MAX_MATERIAL; nIdxMat++)
		{
			//指定したマテリアルの色を設定
			pModel->SetMaterialSpecular(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), nIdxMat);
			pModel->SetMaterialPower(8.0f, nIdxMat);
		}
	}

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
	
	//ゲームオーバーなら
	if (CManager::GetManager()->GetGameScene()->GetGameOver())
	{
		//消す
		Uninit();
		return;
	}

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

	//ーーーーーーーーーーーーーーーーーーー
	//金風船のキラキラ
	if (m_bGold)
	{
		CPresetEffect::SetEffect3D(7, D3DXVECTOR3(pos.x, pos.y + 70, pos.z), {}, {});		//落ちる塵
	}
	//ーーーーーーーーーーーーーーーーーーー

	//プレイヤーとの当たり判定
	if (CollisionPlayer())
	{
		//マネージャーの取得
		CManager* pManager = CManager::GetManager();
		//サウンドの取得
		CSound *pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//音再生
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_BALLOON_BREAK);

		//色によって変える
		if (m_bGold)
		{
			//音再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_POINT_3);
		}
		else
		{
			//音再生
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_POINT_1);

		}

		//ーーーーーーーーーーーーーーーーーーー
		//風船取得エフェクト
		CPresetEffect::SetEffect3D(2, D3DXVECTOR3(pos.x,pos.y + 30,pos.z), {}, {});		//衝撃波
		CPresetEffect::SetEffect3D(3, D3DXVECTOR3(pos.x,pos.y + 30,pos.z), {}, {});		//塵
		CPresetEffect::SetEffect3D(4, D3DXVECTOR3(pos.x,pos.y + 30,pos.z), {}, {});		//落ちる塵
		//ーーーーーーーーーーーーーーーーーーー
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
		CObjectPlayerBalloonCar *pPlayer = static_cast<CObjectPlayerBalloonCar*> (pObject);

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
			//色によってスコアを増やす
			if (m_bGold)
			{
				pPlayer->GetScoreUi()->GetScore()->AddScore(BALLOON_GOLD_SCORE);
			}
			else
			{
				pPlayer->GetScoreUi()->GetScore()->AddScore(BALLOON_NORMAL_SCORE);
			}
			return true;
		}

		pObject = pObjNext;	//リストの次のオブジェクトを代入
	}

	return false;
}
