//=============================================================================
//
// 浮遊物処理 [float_object.cpp]
// Author : 加藤瑞葵
//
//=============================================================================
#include "float_object.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CFloatObject::CFloatObject()
{
	m_move = { 0.0f, 0.0f, 0.0f };
	m_rotateSpeed = { 0.0f, 0.0f, 0.0f };
}

//=============================================================================
// オーバーロードされたコンストラクタ
//=============================================================================
CFloatObject::CFloatObject(CModel::MODELTYPE typeModel) : CObjectModel(typeModel, false)
{
	m_move = { 0.0f, 0.0f, 0.0f };
	m_rotateSpeed = { 0.0f, 0.0f, 0.0f };
}

//=============================================================================
// デストラクタ
//=============================================================================
CFloatObject::~CFloatObject()
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CFloatObject* CFloatObject::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move,
	                               const D3DXVECTOR3 rotateSpeed, const CModel::MODELTYPE modelType) {
	CFloatObject* pFloatObject;
	pFloatObject = new CFloatObject(modelType);
	if (pFloatObject == nullptr) return nullptr;

	pFloatObject->SetPos(pos);
	pFloatObject->SetRot(rot);
	pFloatObject->m_move = move;
	pFloatObject->m_rotateSpeed = rotateSpeed;
	
	pFloatObject->Init();

	return pFloatObject;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFloatObject::Init(void) {

	CObjectModel::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFloatObject::Uninit(void) {

	CObjectModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CFloatObject::Update(void) {
	
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//移動量加算
	pos += m_move;
	//位置設定
	SetPos(pos);

	//向き取得
	D3DXVECTOR3 rot = GetRot();
	//向き加算
	rot += m_rotateSpeed;

	//πと-πをまたいだ時
	if (rot.x > D3DX_PI)
	{
		rot.x -= D3DX_PI * 2.0f;
	}
	else if (rot.x < -D3DX_PI)
	{
		rot.x += D3DX_PI * 2.0f;
	}

	if (rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}

	if (rot.z > D3DX_PI)
	{
		rot.z -= D3DX_PI * 2.0f;
	}
	else if (rot.z < -D3DX_PI)
	{
		rot.z += D3DX_PI * 2.0f;
	}

	//向き設定
	SetRot(rot);

	CObjectModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CFloatObject::Draw(void) {
	CObjectModel::Draw();
}