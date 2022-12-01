//=============================================================================
//
// モデル処理 [model.h]
// Author : 鶴間俊樹
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MODEL_FILE_PATH (128)	//モデルのファイルのパスの長さの最大
#define MAX_MATERIAL (16)			//モデルごとのマテリアルの最大数

//*****************************************************************************
// モデルクラス
//*****************************************************************************
class CModel
{
public:
	//モデルの種類
	enum class MODELTYPE{
		//オブジェクト
		OBJ_CAR = 0,					//車
		OBJ_STADIUM,					//スタジアム
		OBJ_BALLOON_PINK,				//風船(ピンク)
		OBJ_BALLOON_GOLD,				//風船(ゴールド)
		OBJ_ITEM_BOX,					//アイテムボックス
		OBJ_BANANA,						//バナナ
		OBJ_ATTACK_CAR_STAGE,			//衝突ゲーム用ステージ
		OBJ_BOM,						//爆弾
		OBJ_BROKEN_TOWER,				//壊れた塔
		OBJ_BROKEN_GATE,				//壊れた門
		OBJ_BROKEN_TOWER_FRAGMENT_01,	//壊れた塔の破片
		OBJ_BROKEN_TOWER_FRAGMENT_02,	//壊れた塔の破片
		OBJ_BROKEN_TOWER_FRAGMENT_03,	//壊れた塔の破片
		OBJ_BROKEN_TOWER_FRAGMENT_04,	//壊れた塔の破片
		OBJ_BROKEN_TOWER_FRAGMENT_05,	//壊れた塔の破片
		OBJ_BROKEN_TOWER_FRAGMENT_06,	//壊れた塔の破片
		OBJ_ITEM_SHIELD,				//アイテム盾
		OBJ_SPHERE_COVER,				//球のカバー
		OBJ_HATENA,						//はてなマーク
		OBJ_MENU_STAGE,					//メニューのステージ
		OBJ_SHADOW,						//影

		OBJ_FIND_WOLF_TOWER,			//人狼見つけるシーンのタワー
		OBJ_FIND_WOLF_FACE_01,			//人狼見つけるシーンの顔オブジェクト
		OBJ_FIND_WOLF_FACE_02,			//人狼見つけるシーンの顔オブジェクト
		OBJ_FIND_WOLF_FACE_03,			//人狼見つけるシーンの顔オブジェクト
		OBJ_RESULT_TOWER,				//結果画面のタワー
		OBJ_RESULT_CROWN,				//結果画面の冠
		OBJ_RESULT_CLOUD_00,			//結果画面の雲00
		OBJ_RESULT_CLOUD_01,			//結果画面の雲01
		OBJ_RESULT_CLOUD_02,			//結果画面の雲02
		OBJ_RESULT_BALLOON_00,			//結果画面の風船00
		OBJ_RESULT_BALLOON_01,			//結果画面の風船01
		OBJ_RESULT_BALLOON_02,			//結果画面の風船02

		OBJ_TITLE_DUNE_00,				//砂丘00
		OBJ_TITLE_DUNE_01,				//砂丘01
		OBJ_TITLE_DUNE_02,				//砂丘02

		//プレイヤー
		pl_0, pl_1, pl_2, pl_3, pl_4, pl_5, pl_6, pl_7, pl_8, 

		ENUM_MAX	//最大数
	};

	//モデルデータ
	typedef struct
	{
		LPD3DXMESH pMesh;	//メッシュ（頂点情報）へのポインタ
		LPD3DXBUFFER pBuffMat;	//マテリアルへのポインタ
		DWORD nNumMat;	//マテリアルの数
	} ModelData;

	//色の変更
	typedef struct {
		D3DXCOLOR colAdd;	//変更中はフレーム毎に加算される色
		int nTimeFinish;	//色の変更にかかる時間
		int nCnt;			//カウンター
	} ChangeDiffuse;

	CModel();	//デフォルトコンストラクタ
	~CModel();	//デストラクタ
	static CModel* Create(MODELTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel* pParent, bool bOutLine);	//生成処理
	static HRESULT Load(void);	//モデルデータの読み込み
	static void Unload(void);	//モデルデータの解放
	static ModelData GetModelData(MODELTYPE type);	//モデルデータの取得
	static char* GetPathName(MODELTYPE type);		//テクスチャのパスの文字列の取得
	static D3DXCOLOR GetDefaultColor(MODELTYPE type, int nIdx);	//モデルのデフォルトの色を取得
	static int GetNumMat(MODELTYPE type);		//マテリアル数取得

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理
	void SetPos(D3DXVECTOR3 pos);	//位置座標の設定
	D3DXVECTOR3 GetPos(void);		//位置座標の取得
	void SetRot(D3DXVECTOR3 rot);	//角度の設定
	D3DXVECTOR3 GetRot(void);		//角度の取得
	void UpdateMtxWorld(void);		//ワールドマトリックスの更新
	D3DXMATRIX GetMtxWorld(void);			//ワールドマトリックスの取得
	D3DXMATRIX* GetPtrMtxWorld(void);		//ワールドマトリックスのポインタの取得
	void SetModelType(MODELTYPE type);		//モデルのタイプの設定
	MODELTYPE GetModelType(void);			//モデルのタイプの取得
	void SetMaterialDiffuse(D3DXCOLOR col, int nIdx);	//マテリアルの色の設定
	D3DXCOLOR GetMaterialDiffuse(int nIdx);				//マテリアルの色の取得
	void SetMaterialDiffuseAlpha(float fAlpha, int nIdx);	//マテリアルのアルファ値を設定
	void SetMaterialDiffuseAlphaAll(float fAlpha);			//すべてのマテリアルのアルファ値を設定
	float GetMaterialDiffuseAlpha(int nIdx);				//マテリアルのアルファ値を取得
	void SetMaterialSpecular(D3DXCOLOR col, int nIdx);	//マテリアルのスペキュラー色の設定
	void SetMaterialEmissive(D3DXCOLOR col, int nIdx);	//マテリアルの発光色の設定
	void SetMaterialPower(float fPower, int nIdx);		//マテリアルの反射の質感の設定
	void StartChangeMaterialDiffuse(int nIdxMat, D3DXCOLOR colDest, int nTimeFin);	//マテリアルの色の変更の開始
	void SetColorGlow(D3DXCOLOR col) { m_colGlow = col; }	//輪郭の発光色の設定
	void SetPowerGlow(float fPower) { m_powGlow = fPower; }	//輪郭の強度の設定

	void CreateCloneMesh(void);		//複製メッシュの生成
	void ExpansionCloneMesh(void);	//複製メッシュを膨張させる
	void SetColorOutline(D3DXCOLOR col);	//輪郭の色の設定
	void SetDrawOutline(bool bDraw);		//輪郭の表示設定

private:
	void UpdateColorChange(void);	//色の変更の更新

	static ModelData m_aModelData[(int)MODELTYPE::ENUM_MAX];	//全モデルの情報
	static char m_asFilePath[(int)MODELTYPE::ENUM_MAX][MAX_MODEL_FILE_PATH];	// モデルのテキストファイルのパス
	static D3DXMATERIAL m_aMatDefault[(int)MODELTYPE::ENUM_MAX][MAX_MATERIAL];	//モデルのマテリアルの初期値
	static CTexture::TEXTURE_TYPE m_aTexType[(int)MODELTYPE::ENUM_MAX][MAX_MATERIAL];	//マテリアルごとのテクスチャの種類

	MODELTYPE m_modelType;	//モデルの種類
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//向き
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
	CModel* m_pParent;		//親のモデルへのポインタ
	int m_nIdxParent;		//親のインデックス
	D3DXMATERIAL m_aMat[MAX_MATERIAL];	//モデルのマテリアル
	ChangeDiffuse m_aChangeDiffuse[MAX_MATERIAL];	//モデルのマテリアルの色を変更する構造体の配列

	D3DXCOLOR m_colGlow;	//輪郭の発光色の色
	float m_powGlow;	//輪郭の強度

	bool m_bOutline;			//輪郭があるかどうか
	D3DXCOLOR m_colOutline;	//輪郭の色
	LPD3DXMESH m_pCloneMesh;	//複製したメッシュのポインタ
};

#endif // !_MODEL_H_