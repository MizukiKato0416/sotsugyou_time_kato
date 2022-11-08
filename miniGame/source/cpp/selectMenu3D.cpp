//=============================================================================
//
// 3D選択メニュー処理 [selectMenu3D.cpp]
// Author : 鶴間俊樹
//
//=============================================================================
#include "selectMenu3D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define DEFAULT_ROTATE_SPAN (30)	//デフォルトの回転スパン 0禁止

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSelectMenu3D::CSelectMenu3D() : m_posCenter(D3DXVECTOR3()), m_fRadiusModel(0.0f)
{

}

//=============================================================================
// オーバーロードされたコンストラクタ
//=============================================================================
CSelectMenu3D::CSelectMenu3D(int nNumSelect, D3DXVECTOR3 posCenter, float fRadiusModel, CModel::MODELTYPE typeModel, float fDistCamera, float fHeightCamera, bool bUseBG)
	: CSelectMenu(nNumSelect,bUseBG), m_posCenter(posCenter), m_fRadiusModel(fRadiusModel)
{
	m_fRotModel = 0.0f;
	m_typeModel = typeModel;
	m_nCntRotate = 0;
	m_nSpanRotate = DEFAULT_ROTATE_SPAN;

	m_fDistCamera = fDistCamera;
	m_fRotCamera = 0.0f;
	m_fHeightCamera = fHeightCamera;
	//左右の入力にする
	SetSelectType(SELECT_TYPE::HORIZONTAL);

	CreateModelUI();
}

//=============================================================================
// デストラクタ
//=============================================================================
CSelectMenu3D::~CSelectMenu3D()
{

}

//=============================================================================
// 3D選択メニューの生成処理
//=============================================================================
CSelectMenu3D* CSelectMenu3D::Create(int nNumSelect, D3DXVECTOR3 posCenter, float fRadius, CModel::MODELTYPE typeModel, float fDistCamera, float fHeightCamera, bool bUseBG) {
	CSelectMenu3D* pSelectMenu3D;
	pSelectMenu3D = new CSelectMenu3D(nNumSelect, posCenter, fRadius, typeModel, fDistCamera, fHeightCamera, bUseBG);
	if (pSelectMenu3D == nullptr) return nullptr;

	pSelectMenu3D->Init();

	return pSelectMenu3D;
}

//=============================================================================
// 3D選択メニューの初期化処理
//=============================================================================
HRESULT CSelectMenu3D::Init(void) {
	m_fRotModel = 0.0f;
	m_fSpeedRotModel = 0.0f;
	m_fRotCamera = 0.0f;
	m_nCntRotate = 0;

	CSelectMenu::Init();

	return S_OK;
}

//=============================================================================
// 3D選択メニューの終了処理
//=============================================================================
void CSelectMenu3D::Uninit(void) {
	int nNumSelect = GetNumSelect();

	//UIモデルの破棄
	if (m_ppObjModelUIArray != nullptr) {
		for (int nCntModel = 0; nCntModel < nNumSelect; nCntModel++)
		{
			if (m_ppObjModelUIArray[nCntModel] == nullptr) continue;
			m_ppObjModelUIArray[nCntModel]->Uninit();
			m_ppObjModelUIArray[nCntModel] = nullptr;
		}
		m_ppObjModelUIArray = nullptr;
	}

	CSelectMenu::Uninit();
}

//=============================================================================
// 3D選択メニューの更新処理
//=============================================================================
void CSelectMenu3D::Update(void) {
	//モデルの位置を移動
	MoveModel();

	CSelectMenu::Update();
}

//=============================================================================
// UIモデルの生成
//=============================================================================
void CSelectMenu3D::CreateModelUI(void) {
	//すでに生成済みの場合終了
	if (m_ppObjModelUIArray != nullptr) return;

	//選択肢の数の取得
	int nNumSelect = GetNumSelect();
	m_ppObjModelUIArray = new CObjectModelUI*[nNumSelect];

	//生成できなかった場合終了
	if (m_ppObjModelUIArray == nullptr) return;

	//UIモデルを映すカメラを設定
	D3DXMATRIX mtxView;	//ビューマトリックス
	D3DXVECTOR3 posR, posV;	//視点と注視点

	posR = m_posCenter;
	posV = D3DXVECTOR3(m_posCenter.x, m_posCenter.y + m_fHeightCamera, m_posCenter.z - m_fDistCamera);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&mtxView,
		&posV,
		&posR,
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	for (int nCntModel = 0; nCntModel < nNumSelect; nCntModel++)
	{
		D3DXVECTOR3 posModel;	//UIモデルを配置する位置
		posModel = m_posCenter +
			D3DXVECTOR3(sinf(D3DX_PI * 2.0f * (1.0f - (float)nCntModel / nNumSelect) + D3DX_PI) * m_fRadiusModel, //1.0- で左回りの配置	+PIで手前側に１番目のオブジェクトが来るように
				0.0f,
				cosf(D3DX_PI * 2.0f * (1.0f - (float)nCntModel / nNumSelect) + D3DX_PI) * m_fRadiusModel);
		//UIモデルの生成
		m_ppObjModelUIArray[nCntModel] = CObjectModelUI::Create(m_typeModel, posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		if (m_ppObjModelUIArray[nCntModel] == nullptr) continue;
		//UIモデルのビューマトリックスと視点を設定
		m_ppObjModelUIArray[nCntModel]->SetViewMatrix(mtxView);
		m_ppObjModelUIArray[nCntModel]->SetViewPos(posV);
	}
}

//=============================================================================
// モデルの移動
//=============================================================================
void CSelectMenu3D::MoveModel(void) {
	//モデルのダブルポインタがnullの場合
	if (m_ppObjModelUIArray == nullptr) {
		//選択の変更の制限を解除する
		SetLockChangeSelect(false);
	}

	//カウント0以下の場合終了
	if (m_nCntRotate <= 0) return;

	//カウンターを減算
	m_nCntRotate--;

	//回転を加算
	m_fRotModel += m_fSpeedRotModel;
	//超過分調整
	if (m_fRotModel > D3DX_PI * 2) m_fRotModel -= D3DX_PI * 2;

	//選択の遷移が完了時
	if (m_nCntRotate <= 0) {
		//選択の変更の制限を解除する
		SetLockChangeSelect(false);
		//終了時の処理
		EndChangeSelect();

		//目標角度を設定する　（floatの誤差を避けるため）
		m_fRotModel = m_fRotModelDest;
	}

	int nNumSelect = GetNumSelect();	//選択肢の数を取得

	//UIモデルの位置を変更
	for (int nCntModel = 0; nCntModel < nNumSelect; nCntModel++)
	{
		//UIモデルを配置する位置
		D3DXVECTOR3 posModel = m_posCenter +
			D3DXVECTOR3(sinf(D3DX_PI * 2.0f * (1.0f - (float)nCntModel / nNumSelect) + D3DX_PI + m_fRotModel) * m_fRadiusModel, //1.0- で左回りの配置	+PIで手前側に１番目のオブジェクトが来るように
				0.0f,
				cosf(D3DX_PI * 2.0f * (1.0f - (float)nCntModel / nNumSelect) + D3DX_PI + m_fRotModel) * m_fRadiusModel);
		//UIモデルの位置を設定
		if (m_ppObjModelUIArray[nCntModel] != nullptr) m_ppObjModelUIArray[nCntModel]->SetPos(posModel);
	}
}

//=============================================================================
// 選択の変更が開始されたときの処理
//=============================================================================
void CSelectMenu3D::BeginChangeSelect(bool bChangePlus) {
	//選択の変更を制限する
	SetLockChangeSelect(true);

	int nIdxCurSelect = GetIdxCurSelect();	//現在の選択の番号を取得
	SetRotDest(nIdxCurSelect);

	float fRotDelta;	//目標角度への差分

	//選択肢をプラスした場合の回転する差分を計算
	if (m_fRotModelDest > m_fRotModel) {
		fRotDelta = m_fRotModelDest - m_fRotModel;
	}
	else {
		fRotDelta = D3DX_PI * 2 - (m_fRotModel - m_fRotModelDest);
	}

	//選択肢をマイナスした場合　マイナスにして反時計周り
	if (!bChangePlus) fRotDelta -= D3DX_PI * 2;

	if (m_nSpanRotate == 0) m_nSpanRotate = DEFAULT_ROTATE_SPAN;	//0除算対策
	//カウントの設定
	m_nCntRotate = m_nSpanRotate;

	//回転速度を設定
	SetSpeedRotModel(fRotDelta / m_nCntRotate);
}

//=============================================================================
// UIモデルオブジェクトのポインタを取得
//=============================================================================
CObjectModelUI* CSelectMenu3D::GetModelUI(int nIdx) {
	if (m_ppObjModelUIArray == nullptr || nIdx < 0 || nIdx >= GetNumSelect()) return nullptr;	//配列から取得できない場合null
	return m_ppObjModelUIArray[nIdx];
}