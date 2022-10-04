//================================================
//ゲーム01処理
//Author: 加藤瑞葵
//================================================
#include "game01.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_mouse.h"
#include "meshfield.h"
#include "meshsphere.h"
#include "renderer.h"
#include "camera.h"
#include "model_single.h"
#include "model.h"
#include "x_load.h"
#include "object3D.h"

//================================================
//マクロ定義
//================================================
#define GAME01_MODEL_ROTATE_SPEED		(0.03f)		//モデルの回転速度
#define GAME01_MODEL_MOVE_SPEED			(10.0f)		//モデルの移動速度
#define GAME01_MODEL_ADD_MOVE_SPEED		(1.01f)		//モデルの移動速度加速割合
#define GAME01_MODEL_ADD_MOVE			(0.1f)		//モデルの移動速度加算値
#define GAME01_MODEL_SELECT_ALPHA		(0.5f)		//モデルの選択されたときのα値
#define GAME01_FIELD_SIZE				(50000.0f)									//マップの広さ

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CGame01::CGame01(CObject::PRIORITY Priority):CObject(Priority)
{
	m_pMeshField = nullptr;
	m_nLine = 0;
	m_nVertical = 0;
	m_select = SELECT::VERTICAL;
	m_bPasDrop = false;
	m_nCntNum = 0;
	m_meshFieldPos = { 0.0f, 0.0f, 0.0f };
	m_fRadius = 0.0f;
	m_fStrength = 0.0f;
	m_bUpDown = false;
	m_pNewModel = nullptr;
	m_apModel.clear();
	m_nNumModelType = 0;
	m_nNumModel = 0;
	m_bModelSet = false;
	m_fMoveSpeed = 0.0f;
	m_bDrawCharactor = false;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CGame01::~CGame01()
{
	
}

//================================================
//初期化処理
//================================================
HRESULT CGame01::Init(void)
{
	//変数初期化
	m_pMeshField = nullptr;
	m_nLine = 100;
	m_nVertical = 100;
	m_select = SELECT::VERTICAL;
	m_bPasDrop = false;
	m_nCntNum = 0;
	m_meshFieldPos = { 1000.0f, 0.0f, 1000.0f };
	m_fRadius = 50.0f;
	m_fStrength = 0.5f;
	m_bUpDown = true;
	m_pNewModel = nullptr;
	m_apModel.clear();
	m_nNumModelType = 0;
	m_nNumModel = 0;
	m_bModelSet = false;
	m_fMoveSpeed = GAME01_MODEL_MOVE_SPEED;
	m_bDrawCharactor = true;

	//メッシュスフィア生成
	CMeshSphere *pMeshSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(GAME01_FIELD_SIZE, GAME01_FIELD_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                                           32, 8);
	pMeshSphere->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("sky.jpg"));

	CObject3D *pObject3D = CObject3D::Create(D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(GAME01_FIELD_SIZE, 0.0f, GAME01_FIELD_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pObject3D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("mist.png"));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CGame01::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CGame01::Update(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	

	//文字入力が始まっていなかったら
	if (m_bPasDrop == false)
	{
		//モード選択処理
		ModeSelect();

		//ENTERを押したら
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			//入力が始まっていないなら
			if (m_bPasDrop == false)
			{
				//入力を始める
				m_bPasDrop = true;
			}
			//決定項目なら
			if (m_select == CGame01::SELECT::CREATE)
			{//項目がメッシュの生成だったら
				if (m_pMeshField == nullptr)
				{
					//メッシュフィールド生成
					m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_meshFieldPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						                              m_nLine, m_nVertical);
					m_pMeshField->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("floor_01.jpg"));
				}
				//文字列の入力回数をリセット
				m_nCntNum = 0;
				//入力していない状態にする
				m_bPasDrop = false;
			}
			else if(m_select == CGame01::SELECT::TERRAIN_UP_DOWN)
			{//項目がメッシュの盛り上げ、盛り下げの切り替えだったら
				//盛り上げる状態だったら
				if (m_bUpDown == true)
				{
					//盛り下げる状態にする
					m_bUpDown = false;
				}
				else
				{//盛り下げる状態だったら
					//盛り上げる状態にする
					m_bUpDown = true;
				}
				//文字列の入力回数をリセット
				m_nCntNum = 0;
				//入力していない状態にする
				m_bPasDrop = false;
			}
			else if (m_select == CGame01::SELECT::MESH_SAVE)
			{//項目がメッシュの保存なら
				if (m_pMeshField != nullptr)
				{
					//メッシュの情報をテキストに書き出す
					m_pMeshField->SaveText();
				}
				//文字列の入力回数をリセット
				m_nCntNum = 0;
				//入力していない状態にする
				m_bPasDrop = false;
			}
			else if (m_select == CGame01::SELECT::MESH_LOAD)
			{//項目がメッシュの読み込みなら
				if (m_pMeshField == nullptr)
				{
					//メッシュフィールド生成
					m_pMeshField = CMeshField::CreateLoadText("data/mesh_field.txt");
					m_pMeshField->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("floor_01.jpg"));
				}
				//文字列の入力回数をリセット
				m_nCntNum = 0;
				//入力していない状態にする
				m_bPasDrop = false;
			}
			else if (m_select == CGame01::SELECT::MODEL_SAVE)
			{//項目がモデルのテキストファイル書き出しなら
				//モデルをテキストファイルに書き出す
				SaveTxt();
				//文字列の入力回数をリセット
				m_nCntNum = 0;
				//入力していない状態にする
				m_bPasDrop = false;
			}
			else if (m_select == CGame01::SELECT::MODEL_LOAD)
			{//項目がモデルの読み込みなら
				if (m_bModelSet == false)
				{
					//引数に指定したファイルを読み込んでモデルを生成
					LoadModelTxt("data/model_set.txt");
					m_bModelSet = true;
				}
				//文字列の入力回数をリセット
				m_nCntNum = 0;
				//入力していない状態にする
				m_bPasDrop = false;
			}
			else if (m_select == CGame01::SELECT::MODEL_SELECT)
			{//項目がモデル選択なら
				//入力状態なら
				if (m_bPasDrop == true)
				{
					if (m_apModel.size() > 0)
					{
						m_nNumModel = m_apModel.size() - 1;
						//色を薄くする
						m_apModel[m_nNumModel]->GetModel()->SetDiffuse(0.5f);
					}
				}
			}
			else if (m_select == CGame01::SELECT::UPDATE)
			{//項目が情報の更新なら
				if (m_pMeshField != nullptr)
				{
					//メッシュフィールドの法線を更新する
					m_pMeshField->UpdateNor();
				}
				//文字列の入力回数をリセット
				m_nCntNum = 0;
				//入力していない状態にする
				m_bPasDrop = false;
			}
		}
	}
	else
	{//文字が入力されている状態なら
		//数字入力処理
		InputNum();
	}
	
	//選択が新しいモデルを生成のとき
	if (m_select == CGame01::SELECT::MODEL_NEW_CREATE)
	{
		if (CManager::GetInstance()->GetXload()->GetMaxType() > 0)
		{
			if (m_pNewModel == nullptr)
			{
				//モデルの生成
				m_pNewModel = CModelSingle::Create({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, m_nNumModelType, NULL, false);
				m_pNewModel->GetModel()->SetDiffuse(GAME01_MODEL_SELECT_ALPHA);
			}

			//新しく生成するモデル選択処理
			CreateNewModelSelect();

			//新しいモデル生成処理
			CreateNewModel();
		}
	}
	else
	{
		if (m_pNewModel != nullptr)
		{
			m_pNewModel->Uninit();
			m_pNewModel = nullptr;
		}
	}

	//選択が生成されているモデルの選択だったら
	if (m_select == CGame01::SELECT::MODEL_SELECT)
	{
		//モデルが1つ以上生成されていたら
		if (m_apModel.size() > 0)
		{
			if (m_bPasDrop == true)
			{
				//生成されているモデル選択処理
				ModelSelect();

				//モデル移動処理
				ModelMove();

				//モデルの回転処理
				ModelRotate();

				//モデル削除処理
				DeleteModel();
			}
		}
	}

	//メッシュフィールド変形処理
	MeshFieldDeformation();

	//DELETEを押したら
	if (pInputKeyboard->GetTrigger(DIK_DELETE) == true)
	{
		//全てのオブジェクト削除処理
		DeleteAllObject();
	}

	if (m_pMeshField != nullptr)
	{
		//メッシュフィールドの法線を更新する
		m_pMeshField->UpdateNor();
	}


	//F1を押したら
	if (pInputKeyboard->GetTrigger(DIK_F1) == true)
	{
		//文字を描画する状態なら
		if (m_bDrawCharactor)
		{
			//描画しない状態にする
			m_bDrawCharactor = false;
		}
		else
		{//文字を描画しない状態なら
			//描画する状態にする
			m_bDrawCharactor = true;
		}
	}
}

//================================================
//描画処理
//================================================
void CGame01::Draw(void)
{
	//文字を描画する状態なら
	if (m_bDrawCharactor)
	{
		RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		char str[(int)SELECT::MAX][256];
		char str1[256];

		wsprintf(&str[0][0], "\n1.メッシュフィールドの縦の列数　:　%d\n", m_nVertical);
		wsprintf(&str[1][0], "\n\n2.メッシュフィールドの横の列数　:　%d\n", m_nLine);
		wsprintf(&str[2][0], "\n\n\n3.メッシュフィールドの幅（X）　 :　%d\n", (int)m_meshFieldPos.x);
		wsprintf(&str[3][0], "\n\n\n\n4.メッシュフィールドの奥行（Z） :　%d\n", (int)m_meshFieldPos.z);
		wsprintf(&str[4][0], "\n\n\n\n\n5.ENTERでメッシュフィールド生成");
		wsprintf(&str[5][0], "\n\n\n\n\n\n6.盛り上げる半径　:　%d\n", (int)m_fRadius);
		wsprintf(&str[6][0], "\n\n\n\n\n\n\n7.盛り上げる強さ　:　%d\n", (int)(m_fStrength * 100.0f));
		wsprintf(&str[7][0], "\n\n\n\n\n\n\n\n8.盛り上げるか盛り下げるか(1:盛り上げる 0:盛り下げる)　:　%d\n", (int)m_bUpDown);
		wsprintf(&str[8][0], "\n\n\n\n\n\n\n\n\n9.メッシュフィールドをテキスト書き出し\n");
		wsprintf(&str[9][0], "\n\n\n\n\n\n\n\n\n\n10.メッシュフィールドをテキスト読み込み\n");
		wsprintf(&str[10][0], "\n\n\n\n\n\n\n\n\n\n\n11.モデルをテキスト書き出し\n");
		wsprintf(&str[11][0], "\n\n\n\n\n\n\n\n\n\n\n\n12.モデルをテキスト読み込み\n");
		wsprintf(&str[12][0], "\n\n\n\n\n\n\n\n\n\n\n\n\n13.モデル生成 (←→でモデル選択 ENTERで生成)\n");
		if (m_apModel.size() > 0)
		{
			wsprintf(&str[13][0], "\n\n\n\n\n\n\n\n\n\n\n\n\n\n14.生成されているモデル選択 当たり判定(0: なし 1: あり) %d\n", m_apModel[m_nNumModel]->GetColl());
		}
		else
		{
			wsprintf(&str[13][0], "\n\n\n\n\n\n\n\n\n\n\n\n\n\n14.生成されているモデル選択 当たり判定(0: なし 1: あり) \n");
		}
		wsprintf(&str[14][0], "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n15.情報の更新(時間かかるかも)\n");
		wsprintf(&str1[0], "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nWASDで移動 ENTERで確定 SPACE,LSHIFTで上下移動\n　L,Jでy軸回転 Kでy軸回転リセット\n　Cで当たり判定変更");

		for (int nCntText = 0; nCntText < (int)SELECT::MAX; nCntText++)
		{
			if ((int)m_select == nCntText)
			{
				//文字の生成
				CManager::GetInstance()->GetRenderer()->GetFont()->DrawText(NULL, str[nCntText], -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else
			{
				//文字の生成
				CManager::GetInstance()->GetRenderer()->GetFont()->DrawText(NULL, str[nCntText], -1, &rect, DT_LEFT, D3DCOLOR_ARGB(100, 255, 255, 255));
			}
		}
		//文字の生成
		CManager::GetInstance()->GetRenderer()->GetFont()->DrawText(NULL, str1, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

//================================================
//セーブ処理
//================================================
void CGame01::SaveTxt(void)
{
	FILE *pFile;
	pFile = fopen("data/model_set.txt", "w");
	if (pFile != NULL)
	{
		fprintf(pFile, "//-----------------------------------------------\n");
		fprintf(pFile, "//モデルの配置処理\n");
		fprintf(pFile, "//Author: 加藤瑞葵\n");
		fprintf(pFile, "//-----------------------------------------------\n");

		int nNumModel = m_apModel.size();
		for (int nModel = 0; nModel < nNumModel; nModel++)
		{
			D3DXVECTOR3 pos = m_apModel[nModel]->GetPos();
			D3DXVECTOR3 rot = m_apModel[nModel]->GetRot();

			fprintf(pFile, "SET_MODEL\n");
			fprintf(pFile, "pas = %s\n", (m_apModel[nModel]->GetModel()->GetFileName().c_str()));
			fprintf(pFile, "pos = %.2f %.2f %.2f\n", pos.x, pos.y, pos.z);
			fprintf(pFile, "rot = %.2f %.2f %.2f\n", rot.x, rot.y, rot.z);
			fprintf(pFile, "coll = %d\n", m_apModel[nModel]->GetColl());
			fprintf(pFile, "END_SET_MODEL\n");
		}

		fprintf(pFile, "END_SCRIPT\n");
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);
}

//================================================
//モデルロード処理
//================================================
void CGame01::LoadModelTxt(const string &Pas)
{
	//ファイルの読み込み
	FILE *pFile;
	pFile = fopen(Pas.c_str(), "r");
	if (pFile != NULL)
	{
		char cStr[128];
		while (fgets(cStr, 128, pFile) != nullptr)
		{
			if (strncmp("SET_MODEL\n", cStr, 11) == 0)
			{
				char cBuff[1][128];
				string sPas;
				D3DXVECTOR3 pos;
				D3DXVECTOR3 rot;
				int nColl;
				fscanf(pFile, "%*s%*s%s", cBuff);
				fscanf(pFile, "%*s%*s%f%f%f", &pos.x, &pos.y, &pos.z);
				fscanf(pFile, "%*s%*s%f%f%f", &rot.x, &rot.y, &rot.z);
				fscanf(pFile, "%*s%*s%d", &nColl);

				sPas = cBuff[0];
				m_apModel.push_back(CModelSingle::Create(pos, rot, sPas, NULL, nColl));
			}
		}
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);
}

//================================================
//モード選択処理
//================================================
void CGame01::ModeSelect(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//下キーを押したら
	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true && (int)m_select < (int)SELECT::MAX - 1)
	{
		//次の選択肢にする
		int nSelect = (int)m_select;
		nSelect++;
		m_select = (SELECT)nSelect;
	}
	else if (pInputKeyboard->GetTrigger(DIK_UP) == true && (int)m_select > 0)
	{//上キーを押したら
	 //前の選択肢にする
		int nSelect = (int)m_select;
		nSelect--;
		m_select = (SELECT)nSelect;
	}
}

//================================================
//数値入力処理
//================================================
void CGame01::InputNum(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	key_update = pInputKeyboard->GetAllKeyUpdate();

	if (key_update.second == true)
	{
		if (key_update.first >= DIK_1 && key_update.first <= DIK_0)
		{
			int nNum = 0;
			if (m_select == SELECT::VERTICAL)
			{
				nNum = m_nVertical;
			}
			else if (m_select == SELECT::LINE)
			{
				nNum = m_nLine;
			}
			else if (m_select == SELECT::WIDTH)
			{
				nNum = (int)m_meshFieldPos.x;
			}
			else if (m_select == SELECT::DEPTH)
			{
				nNum = (int)m_meshFieldPos.z;
			}
			else if (m_select == SELECT::RADIUS)
			{
				nNum = (int)m_fRadius;
			}
			else if (m_select == SELECT::STRENGTH)
			{
				nNum = (int)(m_fStrength * 100.0f);
			}

			if (key_update.first != DIK_0)
			{
				nNum = key_update.first - 1;
			}
			else
			{
				nNum = 0;
			}


			if (m_select == SELECT::VERTICAL)
			{
				//2桁目以降の時
				if (m_nCntNum != 0)
				{
					nNum = m_nVertical * 10 + nNum;
				}
				m_nVertical = nNum;
			}
			else if (m_select == SELECT::LINE)
			{
				//2桁目以降の時
				if (m_nCntNum != 0)
				{
					nNum = m_nLine * 10 + nNum;
				}
				m_nLine = nNum;
			}
			else if (m_select == SELECT::WIDTH)
			{
				//2桁目以降の時
				if (m_nCntNum != 0)
				{
					nNum = (int)m_meshFieldPos.x * 10 + nNum;
				}
				m_meshFieldPos.x = (float)nNum;
			}
			else if (m_select == SELECT::DEPTH)
			{
				//2桁目以降の時
				if (m_nCntNum != 0)
				{
					nNum = (int)m_meshFieldPos.z * 10 + nNum;
				}
				m_meshFieldPos.z = (float)nNum;
			}
			else if (m_select == SELECT::RADIUS)
			{
				//2桁目以降の時
				if (m_nCntNum != 0)
				{
					nNum = (int)m_fRadius * 10 + nNum;
				}
				m_fRadius = (float)nNum;
			}
			else if (m_select == SELECT::STRENGTH)
			{
				//2桁目以降の時
				if (m_nCntNum != 0)
				{
					nNum = (int)(m_fStrength * 100.0f) * 10 + nNum;
				}
				m_fStrength = (float)nNum / 100.0f;
			}
			m_nCntNum++;
		}
		else if (key_update.first == DIK_RETURN)
		{
			if (m_apModel.size() > 0)
			{
				//色を濃くする
				m_apModel[m_nNumModel]->GetModel()->SetDiffuse(1.0f);
			}

			m_bPasDrop = false;
			m_nCntNum = 0;

			//上限と下限を設定
			if (m_nVertical < 2)
			{
				m_nVertical = 2;
			}
			else if (m_nVertical > 200)
			{
				m_nVertical = 200;
			}
			if (m_nLine < 2)
			{
				m_nLine = 2;
			}
			else if (m_nLine > 200)
			{
				m_nLine = 200;
			}
			if (m_meshFieldPos.x > 10000.0f)
			{
				m_meshFieldPos.x = 10000.0f;
			}
			else if (m_meshFieldPos.x < 1.0f)
			{
				m_meshFieldPos.x = 1.0f;
			}
			if (m_meshFieldPos.z > 10000.0f)
			{
				m_meshFieldPos.z = 10000.0f;
			}
			else if (m_meshFieldPos.z < 1.0f)
			{
				m_meshFieldPos.z = 1.0f;
			}
			if (m_fRadius < 1.0f)
			{
				m_fRadius = 1.0f;
			}
			if (m_fStrength < 0.01f)
			{
				m_fStrength = 0.01f;
			}
		}
	}
}

//================================================
//新しく生成するモデル選択処理
//================================================
void CGame01::CreateNewModelSelect(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//→を押したとき
	if (m_nNumModelType < CManager::GetInstance()->GetXload()->GetMaxType() - 1 && pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{
		//今出ているモデルを消す
		if (m_pNewModel != nullptr)
		{
			m_pNewModel->Uninit();
			m_pNewModel = nullptr;
		}
		//モデルのタイプを次にする
		m_nNumModelType++;
		//モデルの生成
		m_pNewModel = CModelSingle::Create({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, m_nNumModelType, NULL, false);
		m_pNewModel->GetModel()->SetDiffuse(GAME01_MODEL_SELECT_ALPHA);
	}
	else if (m_nNumModelType > 0 && pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{//←を押したとき
	 //今出ているモデルを消す
		if (m_pNewModel != nullptr)
		{
			m_pNewModel->Uninit();
			m_pNewModel = nullptr;
		}
		//モデルのタイプを前にする
		m_nNumModelType--;
		//モデルの生成
		m_pNewModel = CModelSingle::Create({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, m_nNumModelType, NULL, true);
		m_pNewModel->GetModel()->SetDiffuse(GAME01_MODEL_SELECT_ALPHA);
	}
}

//================================================
//新しいモデル生成処理
//================================================
void CGame01::CreateNewModel(void)
{
	//新しく生成するモデルが選択されているとき
	if (m_pNewModel != nullptr)
	{
		//キーボード取得処理
		CInputKeyboard *pInputKeyboard;
		pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

		//エンターキーを押したら
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			//選択されているモデルを生成する
			m_apModel.push_back(CModelSingle::Create({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, m_nNumModelType, NULL, true));
			//モード選択状態をやめる
			m_bPasDrop = false;
			//選択するために出していたモデルを削除
			if (m_pNewModel != nullptr)
			{
				m_pNewModel->Uninit();
				m_pNewModel = nullptr;
			}
		}
	}
}

//================================================
//生成されているモデル選択処理
//================================================
void CGame01::ModelSelect(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//→を押したら
	if (m_nNumModel < m_apModel.size() - 1 && pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{
		//色を戻す
		m_apModel[m_nNumModel]->GetModel()->SetDiffuse(1.0f);
		//次のモデルにする
		m_nNumModel++;
		//色を薄くする
		m_apModel[m_nNumModel]->GetModel()->SetDiffuse(GAME01_MODEL_SELECT_ALPHA);
	}
	else if (m_nNumModel > 0 && pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{//←を押したら
	 //色を戻す
		m_apModel[m_nNumModel]->GetModel()->SetDiffuse(1.0f);
		//前のモデルにする
		m_nNumModel--;
		//色を薄くする
		m_apModel[m_nNumModel]->GetModel()->SetDiffuse(GAME01_MODEL_SELECT_ALPHA);
	}
}

//================================================
//モデルの移動処理
//================================================
void CGame01::ModelMove(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//モデルの位置取得
	D3DXVECTOR3 modelPos = m_apModel[m_nNumModel]->GetPos();

	//カメラのポインタ配列1番目のアドレス取得
	CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
	//cameraの取得
	CCamera* pCamera = &**pCameraAddress;

	//マウス取得処理
	CInputMouse *pInputMouse;
	pInputMouse = CManager::GetInstance()->GetInputMouse();

	if (pCamera != nullptr)
	{
		//カメラの向き取得
		D3DXVECTOR3 rot = pCamera->GetRotV();

		//スティックの傾きがあったらまたはWASDを押したら
		if ((pInputKeyboard->GetPress(DIK_W) == true || pInputKeyboard->GetPress(DIK_A) == true ||
			pInputKeyboard->GetPress(DIK_S) == true || pInputKeyboard->GetPress(DIK_D) == true) &&
			pInputMouse->GetPress(CInputMouse::MOUSE_TYPE_RIGHT) == false)
		{
			//目的の向き設定用
			float fObjectiveRot = 0.0f;

			if (pInputKeyboard->GetPress(DIK_W) == true)
			{
				if (pInputKeyboard->GetPress(DIK_A) == true)
				{
					//目的の向きを設定
					fObjectiveRot = rot.y - D3DX_PI / 4.0f;
				}
				else if (pInputKeyboard->GetPress(DIK_D) == true)
				{
					//目的の向きを設定
					fObjectiveRot = rot.y + D3DX_PI / 4.0f;
				}
				else
				{
					//目的の向きを設定
					fObjectiveRot = rot.y;
				}
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true)
			{
				if (pInputKeyboard->GetPress(DIK_A) == true)
				{
					//目的の向きを設定
					fObjectiveRot = rot.y - D3DX_PI / 4.0f * 3.0f;
				}
				else if (pInputKeyboard->GetPress(DIK_D) == true)
				{
					//目的の向きを設定
					fObjectiveRot = rot.y + D3DX_PI / 4.0f * 3.0f;
				}
				else
				{
					//目的の向きを設定
					fObjectiveRot = rot.y + D3DX_PI;
				}
			}
			else if (pInputKeyboard->GetPress(DIK_A) == true)
			{
				//目的の向きを設定
				fObjectiveRot = rot.y - D3DX_PI / 2.0f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true)
			{
				//目的の向きを設定
				fObjectiveRot = rot.y + D3DX_PI / 2.0f;
			}

			//移動量加算
			modelPos.x += sinf(fObjectiveRot + D3DX_PI) * m_fMoveSpeed;
			modelPos.z += cosf(fObjectiveRot + D3DX_PI) * m_fMoveSpeed;

			//押し続けたときに移動量を増加させる
			m_fMoveSpeed *= GAME01_MODEL_ADD_MOVE_SPEED;
		}
	}

	if (pInputKeyboard->GetPress(DIK_SPACE) == true && pInputMouse->GetPress(CInputMouse::MOUSE_TYPE_RIGHT) == false)
	{//スペースキーを押したら
	 //上に移動させる
		modelPos.y += m_fMoveSpeed;
		//押し続けたときに移動量を増加させる
		m_fMoveSpeed *= GAME01_MODEL_ADD_MOVE_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_LSHIFT) == true && pInputMouse->GetPress(CInputMouse::MOUSE_TYPE_RIGHT) == false)
	{//LSHIFTキーを押したら
	 //下に移動させる
		modelPos.y -= m_fMoveSpeed;
		//押し続けたときに移動量を増加させる
		m_fMoveSpeed *= GAME01_MODEL_ADD_MOVE_SPEED;
	}

	//スペースキーを押していない且つLSHIFTキーを押していないとき且つWASDを押していなかったら
	if (pInputKeyboard->GetPress(DIK_SPACE) == false && pInputKeyboard->GetPress(DIK_LSHIFT) == false && 
		pInputKeyboard->GetPress(DIK_W) == false && pInputKeyboard->GetPress(DIK_A) == false &&
		pInputKeyboard->GetPress(DIK_S) == false && pInputKeyboard->GetPress(DIK_D) == false)
	{
		m_fMoveSpeed = GAME01_MODEL_MOVE_SPEED;
	}

	//↑を押したら
	if (pInputKeyboard->GetPress(DIK_UP))
	{
		//移動量を加算させる
		m_fMoveSpeed += GAME01_MODEL_ADD_MOVE;
	}
	else if (pInputKeyboard->GetPress(DIK_DOWN))
	{//↓を押したら
	 //移動量を減算させる
		m_fMoveSpeed -= GAME01_MODEL_ADD_MOVE;
	}

	//位置を設定
	m_apModel[m_nNumModel]->SetPos(modelPos);
}

//================================================
//モデルの回転処理
//================================================
void CGame01::ModelRotate(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//モデルの回転取得
	D3DXVECTOR3 modelRot = m_apModel[m_nNumModel]->GetRot();

	if (pInputKeyboard->GetPress(DIK_L) == true)
	{//Lキーを押したら
	 //回転値を増加させる
		modelRot.y += GAME01_MODEL_ROTATE_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_J) == true)
	{//Jキーを押したら
	 //回転値を減算させる
		modelRot.y -= GAME01_MODEL_ROTATE_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_K) == true)
	{//Kキーを押したら
	 //回転値を0にする
		modelRot.y = 0.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_C) == true)
	{//Cキーを押したら
	 //当たり判定がありに設定されていたら
		if (m_apModel[m_nNumModel]->GetColl() == true)
		{
			//当たり判定をなしに設定する
			m_apModel[m_nNumModel]->SetColl(false);
		}
		else
		{//当たり判定がなしに設定されていたら
		 //当たり判定をアリに設定する
			m_apModel[m_nNumModel]->SetColl(true);
		}
	}

	//回転値を設定
	m_apModel[m_nNumModel]->SetRot(modelRot);
}

//================================================
//モデル削除処理
//================================================
void CGame01::DeleteModel(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//バックスペースを押したら
	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true)
	{
		if (m_apModel[m_nNumModel] != nullptr)
		{
			//選択されているモデルを消す
			m_apModel[m_nNumModel]->Uninit();
			//選択されているモデルをへんすうから削除
			m_apModel.erase(m_apModel.begin() + m_nNumModel);
			//選択しているモデルを0にする
			m_nNumModel = 0;
			if (m_apModel.size() > 0)
			{
				//色を薄くする
				m_apModel[m_nNumModel]->GetModel()->SetDiffuse(GAME01_MODEL_SELECT_ALPHA);
			}
			else
			{
				//モデルをテキストから読み込んでいない状態にする
				m_bModelSet = false;
			}
		}
	}
}

//================================================
//メッシュフィールド削除処理
//================================================
void CGame01::DeleteMeshField(void)
{
	//メッシュフィールドが生成されているなら
	if (m_pMeshField != nullptr)
	{
		//メッシュフィールドを消す
		m_pMeshField->Uninit();
		m_pMeshField = nullptr;
	}
}

//================================================
//全てのモデル削除処理
//================================================
void CGame01::DeleteAllModel(void)
{
	//モデルがすべて消えるまで回す
	while (m_apModel.size() > 0)
	{
		//モデルが生成されていたら
		if (m_apModel[0] != nullptr)
		{
			//モデルを消す
			m_apModel[0]->Uninit();
			m_apModel[0] = nullptr;
			//モデルをへんすうから削除
			m_apModel.erase(m_apModel.begin());
		}
	}
	//モデルをテキストから読み込んでいない状態にする
	m_bModelSet = false;
}

//================================================
//全てのオブジェクト削除処理
//================================================
void CGame01::DeleteAllObject(void)
{
	//メッシュフィールドの削除
	DeleteMeshField();

	//全てのモデル削除処理
	DeleteAllModel();
}

//================================================
//メッシュフィールド変形処理
//================================================
void CGame01::MeshFieldDeformation(void)
{
	//メッシュフィールドが生成されていたら
	if (m_pMeshField != nullptr)
	{
		//カメラのポインタ配列1番目のアドレス取得
		CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
		//cameraの取得
		CCamera* pCamera = &**pCameraAddress;

		if (pCamera != nullptr)
		{
			//マウス取得処理
			CInputMouse *pInputMouse;
			pInputMouse = CManager::GetInstance()->GetInputMouse();

			//マウスの位置取得
			POINT mouseTriggerPos;
			GetCursorPos(&mouseTriggerPos);
			ScreenToClient(CManager::GetWindowHandle(), &mouseTriggerPos);

			D3DXVECTOR3 pos = { 0.0f, 0.0f, 0.0f };

			// XZ平面とスクリーン座標の交点算出関数
			CalcScreenToXZ(&pos, mouseTriggerPos.x, mouseTriggerPos.y, SCREEN_WIDTH, SCREEN_HEIGHT, &pCamera->GetViewMtx(), &pCamera->GetPrjMtx());
			pos = pos;

			//頂点数分回す
			int nCntVtx = 0;
			for (int nCntBufferX = 0; nCntBufferX < m_pMeshField->GetVertical() + 1; nCntBufferX++)
			{
				for (int nCntBufferY = 0; nCntBufferY < m_pMeshField->GetLine() + 1; nCntBufferY++)
				{
					//座標取得
					D3DXVECTOR3 VtxPos = m_pMeshField->GetBufferPos(nCntVtx);
					//Yを0にする
					//VtxPos.y = 0.0f;
					pos.y = VtxPos.y;
					D3DXVECTOR3 diff = pos - VtxPos;
					float fDiffer = 0.0f;
					fDiffer = sqrtf(D3DXVec3LengthSq(&diff));
					//範囲内に入っているとき
					if (fDiffer < m_fRadius)
					{
						//マウスを押したとき
						if (pInputMouse->GetPress(CInputMouse::MOUSE_TYPE_LEFT) == true)
						{
							float fUpGround = m_fStrength;
							fUpGround = fUpGround * (1.0f - fDiffer / m_fRadius);

							if (m_bUpDown == false)
							{
								fUpGround *= -1.0f;
							}

							//盛り上げる
							m_pMeshField->AddVtxPos(nCntVtx, fUpGround);
						}

						//マウスを離したとき
						if (pInputMouse->GetRelease(CInputMouse::MOUSE_TYPE_LEFT) == true)
						{
							m_pMeshField->SetBuffSavePos(nCntVtx, 0.0f);
						}
					}
					nCntVtx++;
				}
			}
		}
	}
}

// スクリーン座標をワールド座標に変換
D3DXVECTOR3* CGame01::CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // スクリーンX座標
	int Sy,  // スクリーンY座標
	float fZ,  // 射影空間でのZ値（0～1）
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
)
{
	// 各行列の逆行列を算出
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = Screen_w / 2.0f; VP._22 = -Screen_h / 2.0f;
	VP._41 = Screen_w / 2.0f; VP._42 = Screen_h / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// 逆変換
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3(Sx, Sy, fZ), &tmp);

	return pout;
}

// XZ平面とスクリーン座標の交点算出関数
D3DXVECTOR3* CGame01::CalcScreenToXZ(
	D3DXVECTOR3* pout,
	int Sx,
	int Sy,
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
)
{
	D3DXVECTOR3 nearpos;
	D3DXVECTOR3 farpos;
	D3DXVECTOR3 ray;
	CalcScreenToWorld(&nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj);
	CalcScreenToWorld(&farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj);
	ray = farpos - nearpos;
	D3DXVec3Normalize(&ray, &ray);

	// 床との交差が起きている場合は交点を
	// 起きていない場合は遠くの壁との交点を出力
	if (ray.y <= 0) {
		// 床交点
		float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 1, 0));
		float LP0 = D3DXVec3Dot(&(-nearpos), &D3DXVECTOR3(0, 1, 0));
		*pout = nearpos + (LP0 / Lray)*ray;
	}
	else {
		*pout = farpos;
	}

	return pout;
}