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
CSelectMenu3D::CSelectMenu3D(int nNumSelect, D3DXVECTOR3 posCenter, float fRadiusModel, bool bUseBG)
	: CSelectMenu(nNumSelect, bUseBG), m_posCenter(posCenter), m_fRadiusModel(fRadiusModel)
{
	m_fRotModel = 0.0f;
	m_nCntRotate = 0;
	m_nSpanRotate = DEFAULT_ROTATE_SPAN;

	m_fRotCamera = 0.0f;
	//左右の入力にする
	SetSelectType(SELECT_TYPE::HORIZONTAL);

	//配列のサイズ数を設定する
	m_vpObjModelUI.resize(nNumSelect);
	m_vpPlaneShadow.resize(nNumSelect);
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
CSelectMenu3D* CSelectMenu3D::Create(int nNumSelect, D3DXVECTOR3 posCenter, float fRadius, CModel::MODELTYPE typeModel, float fDistCamera, float fHeightCamera, bool bUseBG, bool bUseShadow) {
	CSelectMenu3D* pSelectMenu3D;
	pSelectMenu3D = new CSelectMenu3D(nNumSelect, posCenter, fRadius, bUseBG);
	if (pSelectMenu3D == nullptr) return nullptr;

	pSelectMenu3D->Init();
	//メニューの情報の設定
	pSelectMenu3D->m_typeModel = typeModel;
	pSelectMenu3D->m_fDistCamera = fDistCamera;
	pSelectMenu3D->m_fHeightCamera = fHeightCamera;
	pSelectMenu3D->m_bUsePlaneShadow = bUseShadow;

	//モデルの生成
	pSelectMenu3D->CreateModelUI();

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
	for (auto& pObjModel : m_vpObjModelUI)
	{
		if (pObjModel == nullptr) continue;
		pObjModel->Uninit();
		pObjModel = nullptr;
	}
	//UI影の破棄
	for (auto& pObjShadow : m_vpPlaneShadow)
	{
		if (pObjShadow == nullptr) continue;
		pObjShadow->Uninit();
		pObjShadow = nullptr;
	}

	CSelectMenu::Uninit();
}

//=============================================================================
// 3D選択メニューの更新処理
//=============================================================================
void CSelectMenu3D::Update(void) {
	if (m_bRoulette) {
		RouletteMenu();
	}
	else {
		RotateMenu();
	}
	//モデルの位置更新
	MoveModel();
	//影の位置更新
	MoveShadow();

	CSelectMenu::Update();
}

//=============================================================================
// UIモデルの生成
//=============================================================================
void CSelectMenu3D::CreateModelUI(void) {
	//選択肢の数の取得
	int nNumSelect = GetNumSelect();

	//UIモデルを映すカメラを設定
	D3DXMATRIX mtxView;	//ビューマトリックス
	D3DXVECTOR3 posR, posV;	//視点と注視点

	posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posV = D3DXVECTOR3(0.0f, m_fHeightCamera, -m_fDistCamera);

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
		m_vpObjModelUI[nCntModel] = CObjectModelUI::Create(m_typeModel, posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		if (m_vpObjModelUI[nCntModel] == nullptr) continue;
		//UIモデルのビューマトリックスと視点を設定
		m_vpObjModelUI[nCntModel]->SetViewMatrix(mtxView);
		m_vpObjModelUI[nCntModel]->SetViewPos(posV);

		//影の使用がない場合スキップ
		if (!m_bUsePlaneShadow) continue;
		//影の生成
		
		//UI影の生成
		m_vpPlaneShadow[nCntModel] = CObjectModelUI::Create(CModel::MODELTYPE::OBJ_SHADOW , posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		if (m_vpPlaneShadow[nCntModel] == nullptr) continue;
		//UI影のビューマトリックスと視点を設定
		m_vpPlaneShadow[nCntModel]->SetViewMatrix(mtxView);
		m_vpPlaneShadow[nCntModel]->SetViewPos(posV);
	}
}

//=============================================================================
// メニューを回転
//=============================================================================
void CSelectMenu3D::RotateMenu(void) {
	//カウント0以下の場合終了
	if (m_nCntRotate <= 0) return;

	//カウンターを減算
	m_nCntRotate--;

	//回転を加算
	m_fRotModel += m_fSpeedRotModel;
	//超過分調整
	if (m_fRotModel > D3DX_PI * 2) m_fRotModel -= D3DX_PI * 2;
	if (m_fRotModel < 0) m_fRotModel += D3DX_PI * 2;

	//選択の遷移が完了時
	if (m_nCntRotate <= 0) {
		//選択の変更の制限を解除する
		SetLockChangeSelect(false);
		//終了時の処理
		EndChangeSelect();

		//目標角度を設定する　（floatの誤差を避けるため）
		m_fRotModel = m_fRotModelDest;
	}
}

//=============================================================================
// ルーレットでメニューを回転
//=============================================================================
void CSelectMenu3D::RouletteMenu(void) {
	//回転を加算
	m_fRotModel += m_fSpeedRotModel;
	//超過分調整
	if (m_fRotModel > D3DX_PI * 2) m_fRotModel -= D3DX_PI * 2;
	if (m_fRotModel < 0) m_fRotModel += D3DX_PI * 2;

	//ルーレットカウンターを減算
	if (m_nCntRoulette > 0) {
		m_nCntRoulette--;
		if (m_nCntRoulette == 0) {
			//目標角度を設定
			SetRotDest(GetIdxCurSelect());

			//現在のスピードを維持したまま指定位置まで回転できるフレーム数計算
			float fRotDelta;	//目標角度への差分
			//回転する差分を計算（ルーレットはプラス回転のみ）
			if (m_fRotModelDest > m_fRotModel) {
				fRotDelta = m_fRotModelDest - m_fRotModel;
			}
			else {
				fRotDelta = D3DX_PI * 2 - (m_fRotModel - m_fRotModelDest);
			}
			//カウントを設定
			m_nCntRotate = (int)(fRotDelta / m_fSpeedRotModel);
		}
		else {
			//回転量をへらす
			m_fSpeedRotModel *= m_fRouletteSpeedRate;
		}
	}
	//ルーレット終了後　目標位置まで移動
	else {
		//カウンターを減算
		if (m_nCntRotate > 0) {
			m_nCntRotate--;
			if (m_nCntRotate == 0) {
				//目標角度を設定する　（floatの誤差を避けるため）
				m_fRotModel = m_fRotModelDest;
			}
		}
	}
}

//=============================================================================
// モデル移動
//=============================================================================
void CSelectMenu3D::MoveModel(void) {
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
		if (m_vpObjModelUI[nCntModel] != nullptr) m_vpObjModelUI[nCntModel]->SetPos(posModel);
	}
}

//=============================================================================
// 影移動
//=============================================================================
void CSelectMenu3D::MoveShadow(void) {
	int nNumSelect = GetNumSelect();	//選択肢の数を取得

	//UIモデルの位置を変更
	for (int nIdx = 0; nIdx < nNumSelect; nIdx++)
	{
		//モデルか影がない場合スキップ
		if (m_vpObjModelUI[nIdx] == nullptr || m_vpPlaneShadow[nIdx] == nullptr) continue;

		//影の位置をモデルの位置と同期
		D3DXVECTOR3 posModel = m_vpObjModelUI[nIdx]->GetPos();
		m_vpPlaneShadow[nIdx]->SetPos(posModel);
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
CObjectModelUI* CSelectMenu3D::GetModelUI(unsigned int nIdx) {
	if (nIdx >= m_vpObjModelUI.size()) return nullptr;	//配列から取得できない場合null
	return m_vpObjModelUI[nIdx];
}