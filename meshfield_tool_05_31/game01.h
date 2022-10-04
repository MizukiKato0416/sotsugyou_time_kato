//===========================================
//ゲーム処理
//Author:加藤瑞葵
//===========================================
#ifndef _GAME01_H_
#define _GAME01_H_
#include "object.h"
#include "main.h"

//前方宣言
class CMeshField;
class CModelSingle;

//================================================
//マクロ定義
//================================================

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
class CGame01 : public CObject
{
public:
	enum class SELECT
	{
		VERTICAL = 0,		//縦
		LINE,				//横
		WIDTH,				//幅
		DEPTH,				//深さ
		CREATE,				//生成
		RADIUS,				//盛り上げる半径
		STRENGTH,			//盛り上げる強さ
		TERRAIN_UP_DOWN,	//地形を盛り上げるかもり下げるか
		MESH_SAVE,			//メッシュテキストファイル書き出し
		MESH_LOAD,			//メッシュ読み込み
		MODEL_SAVE,			//モデルテキストファイル書き出し
		MODEL_LOAD,			//モデル読み込み
		MODEL_NEW_CREATE,	//新しいモデル生成
		MODEL_SELECT,		//モデル選択
		UPDATE,				//情報の更新
		MAX
	};

	CGame01(CObject::PRIORITY Priority = CObject::PRIORITY::NONE);		//コンストラクタ
	~CGame01();															//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetUpDown(void) { return m_bUpDown; }		//上げるか下げるか取得処理

	// スクリーン座標をワールド座標に変換
	D3DXVECTOR3* CalcScreenToWorld(
		D3DXVECTOR3* pout,
		int Sx,  // スクリーンX座標
		int Sy,  // スクリーンY座標
		float fZ,  // 射影空間でのZ値（0～1）
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj
	);
	
	// XZ平面とスクリーン座標の交点算出関数
	D3DXVECTOR3* CalcScreenToXZ(
		D3DXVECTOR3* pout,
		int Sx,
		int Sy,
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj
	);

	//文字を描画するか取得処理
	bool GetDrawCharactor(void) { return m_bDrawCharactor; }

private:
	void SaveTxt(void);								//セーブ処理
	void LoadModelTxt(const string &Pas);			//モデルロード処理
	void ModeSelect(void);							//モード選択処理
	void InputNum(void);							//数値入力処理
	void CreateNewModelSelect(void);				//新しく生成するモデル選択処理
	void CreateNewModel(void);						//新しいモデル生成処理
	void ModelSelect(void);							//生成されているモデル選択処理
	void ModelMove(void);							//モデルの移動処理
	void ModelRotate(void);							//モデルの回転処理
	void DeleteModel(void);							//モデル削除処理
	void DeleteMeshField(void);						//メッシュフィールド削除処理
	void DeleteAllModel(void);						//全てのモデル削除処理
	void DeleteAllObject(void);						//全てのオブジェクト削除処理
	void MeshFieldDeformation(void);				//メッシュフィールド変形処理

	//メンバ変数
	CMeshField *m_pMeshField;			//メッシュフィールドのポインタ
	int m_nLine;						//メッシュフィールドの横の列の数
	int m_nVertical;					//メッシュフィールドの縦の列の数
	SELECT m_select;					//選択肢
	bool m_bPasDrop;					//キーを打ち込んでいるかどうか
	pair<int, bool> key_update;			
	int m_nCntNum;						//文字列を何かい入力したか
	D3DXVECTOR3 m_meshFieldPos;			//メッシュフィールドの位置
	float m_fRadius;					//盛り上げる地点の半径
	float m_fStrength;					//盛り上げる地点の強さ
	bool m_bUpDown;						//盛り上げるか盛り下げるか
	CModelSingle *m_pNewModel;			//新しいモデル
	vector<CModelSingle*> m_apModel;	//生成されたモデル
	int m_nNumModelType;				//何番目のモデルのタイプか
	int m_nNumModel;					//何番目に生成したモデルか
	bool m_bModelSet;					//モデルをロードして生成したかどうか
	float m_fMoveSpeed;					//モデルの移動速度
	bool m_bDrawCharactor;				//文字の描画
};	

#endif // !_GAME01_H_