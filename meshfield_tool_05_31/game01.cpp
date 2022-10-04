//================================================
//�Q�[��01����
//Author: ��������
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
//�}�N����`
//================================================
#define GAME01_MODEL_ROTATE_SPEED		(0.03f)		//���f���̉�]���x
#define GAME01_MODEL_MOVE_SPEED			(10.0f)		//���f���̈ړ����x
#define GAME01_MODEL_ADD_MOVE_SPEED		(1.01f)		//���f���̈ړ����x��������
#define GAME01_MODEL_ADD_MOVE			(0.1f)		//���f���̈ړ����x���Z�l
#define GAME01_MODEL_SELECT_ALPHA		(0.5f)		//���f���̑I�����ꂽ�Ƃ��̃��l
#define GAME01_FIELD_SIZE				(50000.0f)									//�}�b�v�̍L��

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
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
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CGame01::~CGame01()
{
	
}

//================================================
//����������
//================================================
HRESULT CGame01::Init(void)
{
	//�ϐ�������
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

	//���b�V���X�t�B�A����
	CMeshSphere *pMeshSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(GAME01_FIELD_SIZE, GAME01_FIELD_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		                                           32, 8);
	pMeshSphere->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("sky.jpg"));

	CObject3D *pObject3D = CObject3D::Create(D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(GAME01_FIELD_SIZE, 0.0f, GAME01_FIELD_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pObject3D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("mist.png"));

	return S_OK;
}

//================================================
//�I������
//================================================
void CGame01::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CGame01::Update(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	

	//�������͂��n�܂��Ă��Ȃ�������
	if (m_bPasDrop == false)
	{
		//���[�h�I������
		ModeSelect();

		//ENTER����������
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			//���͂��n�܂��Ă��Ȃ��Ȃ�
			if (m_bPasDrop == false)
			{
				//���͂��n�߂�
				m_bPasDrop = true;
			}
			//���荀�ڂȂ�
			if (m_select == CGame01::SELECT::CREATE)
			{//���ڂ����b�V���̐�����������
				if (m_pMeshField == nullptr)
				{
					//���b�V���t�B�[���h����
					m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_meshFieldPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						                              m_nLine, m_nVertical);
					m_pMeshField->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("floor_01.jpg"));
				}
				//������̓��͉񐔂����Z�b�g
				m_nCntNum = 0;
				//���͂��Ă��Ȃ���Ԃɂ���
				m_bPasDrop = false;
			}
			else if(m_select == CGame01::SELECT::TERRAIN_UP_DOWN)
			{//���ڂ����b�V���̐���グ�A���艺���̐؂�ւ���������
				//����グ���Ԃ�������
				if (m_bUpDown == true)
				{
					//���艺�����Ԃɂ���
					m_bUpDown = false;
				}
				else
				{//���艺�����Ԃ�������
					//����グ���Ԃɂ���
					m_bUpDown = true;
				}
				//������̓��͉񐔂����Z�b�g
				m_nCntNum = 0;
				//���͂��Ă��Ȃ���Ԃɂ���
				m_bPasDrop = false;
			}
			else if (m_select == CGame01::SELECT::MESH_SAVE)
			{//���ڂ����b�V���̕ۑ��Ȃ�
				if (m_pMeshField != nullptr)
				{
					//���b�V���̏����e�L�X�g�ɏ����o��
					m_pMeshField->SaveText();
				}
				//������̓��͉񐔂����Z�b�g
				m_nCntNum = 0;
				//���͂��Ă��Ȃ���Ԃɂ���
				m_bPasDrop = false;
			}
			else if (m_select == CGame01::SELECT::MESH_LOAD)
			{//���ڂ����b�V���̓ǂݍ��݂Ȃ�
				if (m_pMeshField == nullptr)
				{
					//���b�V���t�B�[���h����
					m_pMeshField = CMeshField::CreateLoadText("data/mesh_field.txt");
					m_pMeshField->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("floor_01.jpg"));
				}
				//������̓��͉񐔂����Z�b�g
				m_nCntNum = 0;
				//���͂��Ă��Ȃ���Ԃɂ���
				m_bPasDrop = false;
			}
			else if (m_select == CGame01::SELECT::MODEL_SAVE)
			{//���ڂ����f���̃e�L�X�g�t�@�C�������o���Ȃ�
				//���f�����e�L�X�g�t�@�C���ɏ����o��
				SaveTxt();
				//������̓��͉񐔂����Z�b�g
				m_nCntNum = 0;
				//���͂��Ă��Ȃ���Ԃɂ���
				m_bPasDrop = false;
			}
			else if (m_select == CGame01::SELECT::MODEL_LOAD)
			{//���ڂ����f���̓ǂݍ��݂Ȃ�
				if (m_bModelSet == false)
				{
					//�����Ɏw�肵���t�@�C����ǂݍ���Ń��f���𐶐�
					LoadModelTxt("data/model_set.txt");
					m_bModelSet = true;
				}
				//������̓��͉񐔂����Z�b�g
				m_nCntNum = 0;
				//���͂��Ă��Ȃ���Ԃɂ���
				m_bPasDrop = false;
			}
			else if (m_select == CGame01::SELECT::MODEL_SELECT)
			{//���ڂ����f���I���Ȃ�
				//���͏�ԂȂ�
				if (m_bPasDrop == true)
				{
					if (m_apModel.size() > 0)
					{
						m_nNumModel = m_apModel.size() - 1;
						//�F�𔖂�����
						m_apModel[m_nNumModel]->GetModel()->SetDiffuse(0.5f);
					}
				}
			}
			else if (m_select == CGame01::SELECT::UPDATE)
			{//���ڂ����̍X�V�Ȃ�
				if (m_pMeshField != nullptr)
				{
					//���b�V���t�B�[���h�̖@�����X�V����
					m_pMeshField->UpdateNor();
				}
				//������̓��͉񐔂����Z�b�g
				m_nCntNum = 0;
				//���͂��Ă��Ȃ���Ԃɂ���
				m_bPasDrop = false;
			}
		}
	}
	else
	{//���������͂���Ă����ԂȂ�
		//�������͏���
		InputNum();
	}
	
	//�I�����V�������f���𐶐��̂Ƃ�
	if (m_select == CGame01::SELECT::MODEL_NEW_CREATE)
	{
		if (CManager::GetInstance()->GetXload()->GetMaxType() > 0)
		{
			if (m_pNewModel == nullptr)
			{
				//���f���̐���
				m_pNewModel = CModelSingle::Create({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, m_nNumModelType, NULL, false);
				m_pNewModel->GetModel()->SetDiffuse(GAME01_MODEL_SELECT_ALPHA);
			}

			//�V�����������郂�f���I������
			CreateNewModelSelect();

			//�V�������f����������
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

	//�I������������Ă��郂�f���̑I����������
	if (m_select == CGame01::SELECT::MODEL_SELECT)
	{
		//���f����1�ȏ㐶������Ă�����
		if (m_apModel.size() > 0)
		{
			if (m_bPasDrop == true)
			{
				//��������Ă��郂�f���I������
				ModelSelect();

				//���f���ړ�����
				ModelMove();

				//���f���̉�]����
				ModelRotate();

				//���f���폜����
				DeleteModel();
			}
		}
	}

	//���b�V���t�B�[���h�ό`����
	MeshFieldDeformation();

	//DELETE����������
	if (pInputKeyboard->GetTrigger(DIK_DELETE) == true)
	{
		//�S�ẴI�u�W�F�N�g�폜����
		DeleteAllObject();
	}

	if (m_pMeshField != nullptr)
	{
		//���b�V���t�B�[���h�̖@�����X�V����
		m_pMeshField->UpdateNor();
	}


	//F1����������
	if (pInputKeyboard->GetTrigger(DIK_F1) == true)
	{
		//������`�悷���ԂȂ�
		if (m_bDrawCharactor)
		{
			//�`�悵�Ȃ���Ԃɂ���
			m_bDrawCharactor = false;
		}
		else
		{//������`�悵�Ȃ���ԂȂ�
			//�`�悷���Ԃɂ���
			m_bDrawCharactor = true;
		}
	}
}

//================================================
//�`�揈��
//================================================
void CGame01::Draw(void)
{
	//������`�悷���ԂȂ�
	if (m_bDrawCharactor)
	{
		RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		char str[(int)SELECT::MAX][256];
		char str1[256];

		wsprintf(&str[0][0], "\n1.���b�V���t�B�[���h�̏c�̗񐔁@:�@%d\n", m_nVertical);
		wsprintf(&str[1][0], "\n\n2.���b�V���t�B�[���h�̉��̗񐔁@:�@%d\n", m_nLine);
		wsprintf(&str[2][0], "\n\n\n3.���b�V���t�B�[���h�̕��iX�j�@ :�@%d\n", (int)m_meshFieldPos.x);
		wsprintf(&str[3][0], "\n\n\n\n4.���b�V���t�B�[���h�̉��s�iZ�j :�@%d\n", (int)m_meshFieldPos.z);
		wsprintf(&str[4][0], "\n\n\n\n\n5.ENTER�Ń��b�V���t�B�[���h����");
		wsprintf(&str[5][0], "\n\n\n\n\n\n6.����グ�锼�a�@:�@%d\n", (int)m_fRadius);
		wsprintf(&str[6][0], "\n\n\n\n\n\n\n7.����グ�鋭���@:�@%d\n", (int)(m_fStrength * 100.0f));
		wsprintf(&str[7][0], "\n\n\n\n\n\n\n\n8.����グ�邩���艺���邩(1:����グ�� 0:���艺����)�@:�@%d\n", (int)m_bUpDown);
		wsprintf(&str[8][0], "\n\n\n\n\n\n\n\n\n9.���b�V���t�B�[���h���e�L�X�g�����o��\n");
		wsprintf(&str[9][0], "\n\n\n\n\n\n\n\n\n\n10.���b�V���t�B�[���h���e�L�X�g�ǂݍ���\n");
		wsprintf(&str[10][0], "\n\n\n\n\n\n\n\n\n\n\n11.���f�����e�L�X�g�����o��\n");
		wsprintf(&str[11][0], "\n\n\n\n\n\n\n\n\n\n\n\n12.���f�����e�L�X�g�ǂݍ���\n");
		wsprintf(&str[12][0], "\n\n\n\n\n\n\n\n\n\n\n\n\n13.���f������ (�����Ń��f���I�� ENTER�Ő���)\n");
		if (m_apModel.size() > 0)
		{
			wsprintf(&str[13][0], "\n\n\n\n\n\n\n\n\n\n\n\n\n\n14.��������Ă��郂�f���I�� �����蔻��(0: �Ȃ� 1: ����) %d\n", m_apModel[m_nNumModel]->GetColl());
		}
		else
		{
			wsprintf(&str[13][0], "\n\n\n\n\n\n\n\n\n\n\n\n\n\n14.��������Ă��郂�f���I�� �����蔻��(0: �Ȃ� 1: ����) \n");
		}
		wsprintf(&str[14][0], "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n15.���̍X�V(���Ԃ����邩��)\n");
		wsprintf(&str1[0], "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nWASD�ňړ� ENTER�Ŋm�� SPACE,LSHIFT�ŏ㉺�ړ�\n�@L,J��y����] K��y����]���Z�b�g\n�@C�œ����蔻��ύX");

		for (int nCntText = 0; nCntText < (int)SELECT::MAX; nCntText++)
		{
			if ((int)m_select == nCntText)
			{
				//�����̐���
				CManager::GetInstance()->GetRenderer()->GetFont()->DrawText(NULL, str[nCntText], -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else
			{
				//�����̐���
				CManager::GetInstance()->GetRenderer()->GetFont()->DrawText(NULL, str[nCntText], -1, &rect, DT_LEFT, D3DCOLOR_ARGB(100, 255, 255, 255));
			}
		}
		//�����̐���
		CManager::GetInstance()->GetRenderer()->GetFont()->DrawText(NULL, str1, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

//================================================
//�Z�[�u����
//================================================
void CGame01::SaveTxt(void)
{
	FILE *pFile;
	pFile = fopen("data/model_set.txt", "w");
	if (pFile != NULL)
	{
		fprintf(pFile, "//-----------------------------------------------\n");
		fprintf(pFile, "//���f���̔z�u����\n");
		fprintf(pFile, "//Author: ��������\n");
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
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);
}

//================================================
//���f�����[�h����
//================================================
void CGame01::LoadModelTxt(const string &Pas)
{
	//�t�@�C���̓ǂݍ���
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
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);
}

//================================================
//���[�h�I������
//================================================
void CGame01::ModeSelect(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//���L�[����������
	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true && (int)m_select < (int)SELECT::MAX - 1)
	{
		//���̑I�����ɂ���
		int nSelect = (int)m_select;
		nSelect++;
		m_select = (SELECT)nSelect;
	}
	else if (pInputKeyboard->GetTrigger(DIK_UP) == true && (int)m_select > 0)
	{//��L�[����������
	 //�O�̑I�����ɂ���
		int nSelect = (int)m_select;
		nSelect--;
		m_select = (SELECT)nSelect;
	}
}

//================================================
//���l���͏���
//================================================
void CGame01::InputNum(void)
{
	//�L�[�{�[�h�擾����
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
				//2���ڈȍ~�̎�
				if (m_nCntNum != 0)
				{
					nNum = m_nVertical * 10 + nNum;
				}
				m_nVertical = nNum;
			}
			else if (m_select == SELECT::LINE)
			{
				//2���ڈȍ~�̎�
				if (m_nCntNum != 0)
				{
					nNum = m_nLine * 10 + nNum;
				}
				m_nLine = nNum;
			}
			else if (m_select == SELECT::WIDTH)
			{
				//2���ڈȍ~�̎�
				if (m_nCntNum != 0)
				{
					nNum = (int)m_meshFieldPos.x * 10 + nNum;
				}
				m_meshFieldPos.x = (float)nNum;
			}
			else if (m_select == SELECT::DEPTH)
			{
				//2���ڈȍ~�̎�
				if (m_nCntNum != 0)
				{
					nNum = (int)m_meshFieldPos.z * 10 + nNum;
				}
				m_meshFieldPos.z = (float)nNum;
			}
			else if (m_select == SELECT::RADIUS)
			{
				//2���ڈȍ~�̎�
				if (m_nCntNum != 0)
				{
					nNum = (int)m_fRadius * 10 + nNum;
				}
				m_fRadius = (float)nNum;
			}
			else if (m_select == SELECT::STRENGTH)
			{
				//2���ڈȍ~�̎�
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
				//�F��Z������
				m_apModel[m_nNumModel]->GetModel()->SetDiffuse(1.0f);
			}

			m_bPasDrop = false;
			m_nCntNum = 0;

			//����Ɖ�����ݒ�
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
//�V�����������郂�f���I������
//================================================
void CGame01::CreateNewModelSelect(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�����������Ƃ�
	if (m_nNumModelType < CManager::GetInstance()->GetXload()->GetMaxType() - 1 && pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{
		//���o�Ă��郂�f��������
		if (m_pNewModel != nullptr)
		{
			m_pNewModel->Uninit();
			m_pNewModel = nullptr;
		}
		//���f���̃^�C�v�����ɂ���
		m_nNumModelType++;
		//���f���̐���
		m_pNewModel = CModelSingle::Create({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, m_nNumModelType, NULL, false);
		m_pNewModel->GetModel()->SetDiffuse(GAME01_MODEL_SELECT_ALPHA);
	}
	else if (m_nNumModelType > 0 && pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{//�����������Ƃ�
	 //���o�Ă��郂�f��������
		if (m_pNewModel != nullptr)
		{
			m_pNewModel->Uninit();
			m_pNewModel = nullptr;
		}
		//���f���̃^�C�v��O�ɂ���
		m_nNumModelType--;
		//���f���̐���
		m_pNewModel = CModelSingle::Create({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, m_nNumModelType, NULL, true);
		m_pNewModel->GetModel()->SetDiffuse(GAME01_MODEL_SELECT_ALPHA);
	}
}

//================================================
//�V�������f����������
//================================================
void CGame01::CreateNewModel(void)
{
	//�V�����������郂�f�����I������Ă���Ƃ�
	if (m_pNewModel != nullptr)
	{
		//�L�[�{�[�h�擾����
		CInputKeyboard *pInputKeyboard;
		pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

		//�G���^�[�L�[����������
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			//�I������Ă��郂�f���𐶐�����
			m_apModel.push_back(CModelSingle::Create({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, m_nNumModelType, NULL, true));
			//���[�h�I����Ԃ���߂�
			m_bPasDrop = false;
			//�I�����邽�߂ɏo���Ă������f�����폜
			if (m_pNewModel != nullptr)
			{
				m_pNewModel->Uninit();
				m_pNewModel = nullptr;
			}
		}
	}
}

//================================================
//��������Ă��郂�f���I������
//================================================
void CGame01::ModelSelect(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//������������
	if (m_nNumModel < m_apModel.size() - 1 && pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{
		//�F��߂�
		m_apModel[m_nNumModel]->GetModel()->SetDiffuse(1.0f);
		//���̃��f���ɂ���
		m_nNumModel++;
		//�F�𔖂�����
		m_apModel[m_nNumModel]->GetModel()->SetDiffuse(GAME01_MODEL_SELECT_ALPHA);
	}
	else if (m_nNumModel > 0 && pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{//������������
	 //�F��߂�
		m_apModel[m_nNumModel]->GetModel()->SetDiffuse(1.0f);
		//�O�̃��f���ɂ���
		m_nNumModel--;
		//�F�𔖂�����
		m_apModel[m_nNumModel]->GetModel()->SetDiffuse(GAME01_MODEL_SELECT_ALPHA);
	}
}

//================================================
//���f���̈ړ�����
//================================================
void CGame01::ModelMove(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//���f���̈ʒu�擾
	D3DXVECTOR3 modelPos = m_apModel[m_nNumModel]->GetPos();

	//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
	CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
	//camera�̎擾
	CCamera* pCamera = &**pCameraAddress;

	//�}�E�X�擾����
	CInputMouse *pInputMouse;
	pInputMouse = CManager::GetInstance()->GetInputMouse();

	if (pCamera != nullptr)
	{
		//�J�����̌����擾
		D3DXVECTOR3 rot = pCamera->GetRotV();

		//�X�e�B�b�N�̌X������������܂���WASD����������
		if ((pInputKeyboard->GetPress(DIK_W) == true || pInputKeyboard->GetPress(DIK_A) == true ||
			pInputKeyboard->GetPress(DIK_S) == true || pInputKeyboard->GetPress(DIK_D) == true) &&
			pInputMouse->GetPress(CInputMouse::MOUSE_TYPE_RIGHT) == false)
		{
			//�ړI�̌����ݒ�p
			float fObjectiveRot = 0.0f;

			if (pInputKeyboard->GetPress(DIK_W) == true)
			{
				if (pInputKeyboard->GetPress(DIK_A) == true)
				{
					//�ړI�̌�����ݒ�
					fObjectiveRot = rot.y - D3DX_PI / 4.0f;
				}
				else if (pInputKeyboard->GetPress(DIK_D) == true)
				{
					//�ړI�̌�����ݒ�
					fObjectiveRot = rot.y + D3DX_PI / 4.0f;
				}
				else
				{
					//�ړI�̌�����ݒ�
					fObjectiveRot = rot.y;
				}
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true)
			{
				if (pInputKeyboard->GetPress(DIK_A) == true)
				{
					//�ړI�̌�����ݒ�
					fObjectiveRot = rot.y - D3DX_PI / 4.0f * 3.0f;
				}
				else if (pInputKeyboard->GetPress(DIK_D) == true)
				{
					//�ړI�̌�����ݒ�
					fObjectiveRot = rot.y + D3DX_PI / 4.0f * 3.0f;
				}
				else
				{
					//�ړI�̌�����ݒ�
					fObjectiveRot = rot.y + D3DX_PI;
				}
			}
			else if (pInputKeyboard->GetPress(DIK_A) == true)
			{
				//�ړI�̌�����ݒ�
				fObjectiveRot = rot.y - D3DX_PI / 2.0f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true)
			{
				//�ړI�̌�����ݒ�
				fObjectiveRot = rot.y + D3DX_PI / 2.0f;
			}

			//�ړ��ʉ��Z
			modelPos.x += sinf(fObjectiveRot + D3DX_PI) * m_fMoveSpeed;
			modelPos.z += cosf(fObjectiveRot + D3DX_PI) * m_fMoveSpeed;

			//�����������Ƃ��Ɉړ��ʂ𑝉�������
			m_fMoveSpeed *= GAME01_MODEL_ADD_MOVE_SPEED;
		}
	}

	if (pInputKeyboard->GetPress(DIK_SPACE) == true && pInputMouse->GetPress(CInputMouse::MOUSE_TYPE_RIGHT) == false)
	{//�X�y�[�X�L�[����������
	 //��Ɉړ�������
		modelPos.y += m_fMoveSpeed;
		//�����������Ƃ��Ɉړ��ʂ𑝉�������
		m_fMoveSpeed *= GAME01_MODEL_ADD_MOVE_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_LSHIFT) == true && pInputMouse->GetPress(CInputMouse::MOUSE_TYPE_RIGHT) == false)
	{//LSHIFT�L�[����������
	 //���Ɉړ�������
		modelPos.y -= m_fMoveSpeed;
		//�����������Ƃ��Ɉړ��ʂ𑝉�������
		m_fMoveSpeed *= GAME01_MODEL_ADD_MOVE_SPEED;
	}

	//�X�y�[�X�L�[�������Ă��Ȃ�����LSHIFT�L�[�������Ă��Ȃ��Ƃ�����WASD�������Ă��Ȃ�������
	if (pInputKeyboard->GetPress(DIK_SPACE) == false && pInputKeyboard->GetPress(DIK_LSHIFT) == false && 
		pInputKeyboard->GetPress(DIK_W) == false && pInputKeyboard->GetPress(DIK_A) == false &&
		pInputKeyboard->GetPress(DIK_S) == false && pInputKeyboard->GetPress(DIK_D) == false)
	{
		m_fMoveSpeed = GAME01_MODEL_MOVE_SPEED;
	}

	//������������
	if (pInputKeyboard->GetPress(DIK_UP))
	{
		//�ړ��ʂ����Z������
		m_fMoveSpeed += GAME01_MODEL_ADD_MOVE;
	}
	else if (pInputKeyboard->GetPress(DIK_DOWN))
	{//������������
	 //�ړ��ʂ����Z������
		m_fMoveSpeed -= GAME01_MODEL_ADD_MOVE;
	}

	//�ʒu��ݒ�
	m_apModel[m_nNumModel]->SetPos(modelPos);
}

//================================================
//���f���̉�]����
//================================================
void CGame01::ModelRotate(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//���f���̉�]�擾
	D3DXVECTOR3 modelRot = m_apModel[m_nNumModel]->GetRot();

	if (pInputKeyboard->GetPress(DIK_L) == true)
	{//L�L�[����������
	 //��]�l�𑝉�������
		modelRot.y += GAME01_MODEL_ROTATE_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_J) == true)
	{//J�L�[����������
	 //��]�l�����Z������
		modelRot.y -= GAME01_MODEL_ROTATE_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_K) == true)
	{//K�L�[����������
	 //��]�l��0�ɂ���
		modelRot.y = 0.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_C) == true)
	{//C�L�[����������
	 //�����蔻�肪����ɐݒ肳��Ă�����
		if (m_apModel[m_nNumModel]->GetColl() == true)
		{
			//�����蔻����Ȃ��ɐݒ肷��
			m_apModel[m_nNumModel]->SetColl(false);
		}
		else
		{//�����蔻�肪�Ȃ��ɐݒ肳��Ă�����
		 //�����蔻����A���ɐݒ肷��
			m_apModel[m_nNumModel]->SetColl(true);
		}
	}

	//��]�l��ݒ�
	m_apModel[m_nNumModel]->SetRot(modelRot);
}

//================================================
//���f���폜����
//================================================
void CGame01::DeleteModel(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�o�b�N�X�y�[�X����������
	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true)
	{
		if (m_apModel[m_nNumModel] != nullptr)
		{
			//�I������Ă��郂�f��������
			m_apModel[m_nNumModel]->Uninit();
			//�I������Ă��郂�f�����ւ񂷂�����폜
			m_apModel.erase(m_apModel.begin() + m_nNumModel);
			//�I�����Ă��郂�f����0�ɂ���
			m_nNumModel = 0;
			if (m_apModel.size() > 0)
			{
				//�F�𔖂�����
				m_apModel[m_nNumModel]->GetModel()->SetDiffuse(GAME01_MODEL_SELECT_ALPHA);
			}
			else
			{
				//���f�����e�L�X�g����ǂݍ���ł��Ȃ���Ԃɂ���
				m_bModelSet = false;
			}
		}
	}
}

//================================================
//���b�V���t�B�[���h�폜����
//================================================
void CGame01::DeleteMeshField(void)
{
	//���b�V���t�B�[���h����������Ă���Ȃ�
	if (m_pMeshField != nullptr)
	{
		//���b�V���t�B�[���h������
		m_pMeshField->Uninit();
		m_pMeshField = nullptr;
	}
}

//================================================
//�S�Ẵ��f���폜����
//================================================
void CGame01::DeleteAllModel(void)
{
	//���f�������ׂď�����܂ŉ�
	while (m_apModel.size() > 0)
	{
		//���f������������Ă�����
		if (m_apModel[0] != nullptr)
		{
			//���f��������
			m_apModel[0]->Uninit();
			m_apModel[0] = nullptr;
			//���f�����ւ񂷂�����폜
			m_apModel.erase(m_apModel.begin());
		}
	}
	//���f�����e�L�X�g����ǂݍ���ł��Ȃ���Ԃɂ���
	m_bModelSet = false;
}

//================================================
//�S�ẴI�u�W�F�N�g�폜����
//================================================
void CGame01::DeleteAllObject(void)
{
	//���b�V���t�B�[���h�̍폜
	DeleteMeshField();

	//�S�Ẵ��f���폜����
	DeleteAllModel();
}

//================================================
//���b�V���t�B�[���h�ό`����
//================================================
void CGame01::MeshFieldDeformation(void)
{
	//���b�V���t�B�[���h����������Ă�����
	if (m_pMeshField != nullptr)
	{
		//�J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
		CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
		//camera�̎擾
		CCamera* pCamera = &**pCameraAddress;

		if (pCamera != nullptr)
		{
			//�}�E�X�擾����
			CInputMouse *pInputMouse;
			pInputMouse = CManager::GetInstance()->GetInputMouse();

			//�}�E�X�̈ʒu�擾
			POINT mouseTriggerPos;
			GetCursorPos(&mouseTriggerPos);
			ScreenToClient(CManager::GetWindowHandle(), &mouseTriggerPos);

			D3DXVECTOR3 pos = { 0.0f, 0.0f, 0.0f };

			// XZ���ʂƃX�N���[�����W�̌�_�Z�o�֐�
			CalcScreenToXZ(&pos, mouseTriggerPos.x, mouseTriggerPos.y, SCREEN_WIDTH, SCREEN_HEIGHT, &pCamera->GetViewMtx(), &pCamera->GetPrjMtx());
			pos = pos;

			//���_������
			int nCntVtx = 0;
			for (int nCntBufferX = 0; nCntBufferX < m_pMeshField->GetVertical() + 1; nCntBufferX++)
			{
				for (int nCntBufferY = 0; nCntBufferY < m_pMeshField->GetLine() + 1; nCntBufferY++)
				{
					//���W�擾
					D3DXVECTOR3 VtxPos = m_pMeshField->GetBufferPos(nCntVtx);
					//Y��0�ɂ���
					//VtxPos.y = 0.0f;
					pos.y = VtxPos.y;
					D3DXVECTOR3 diff = pos - VtxPos;
					float fDiffer = 0.0f;
					fDiffer = sqrtf(D3DXVec3LengthSq(&diff));
					//�͈͓��ɓ����Ă���Ƃ�
					if (fDiffer < m_fRadius)
					{
						//�}�E�X���������Ƃ�
						if (pInputMouse->GetPress(CInputMouse::MOUSE_TYPE_LEFT) == true)
						{
							float fUpGround = m_fStrength;
							fUpGround = fUpGround * (1.0f - fDiffer / m_fRadius);

							if (m_bUpDown == false)
							{
								fUpGround *= -1.0f;
							}

							//����グ��
							m_pMeshField->AddVtxPos(nCntVtx, fUpGround);
						}

						//�}�E�X�𗣂����Ƃ�
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

// �X�N���[�����W�����[���h���W�ɕϊ�
D3DXVECTOR3* CGame01::CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // �X�N���[��X���W
	int Sy,  // �X�N���[��Y���W
	float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
)
{
	// �e�s��̋t�s����Z�o
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = Screen_w / 2.0f; VP._22 = -Screen_h / 2.0f;
	VP._41 = Screen_w / 2.0f; VP._42 = Screen_h / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// �t�ϊ�
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3(Sx, Sy, fZ), &tmp);

	return pout;
}

// XZ���ʂƃX�N���[�����W�̌�_�Z�o�֐�
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

	// ���Ƃ̌������N���Ă���ꍇ�͌�_��
	// �N���Ă��Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��
	if (ray.y <= 0) {
		// ����_
		float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 1, 0));
		float LP0 = D3DXVec3Dot(&(-nearpos), &D3DXVECTOR3(0, 1, 0));
		*pout = nearpos + (LP0 / Lray)*ray;
	}
	else {
		*pout = farpos;
	}

	return pout;
}