//================================================
//���f���P�̂��o������
//Author:KatoMizuki
//================================================
#include "object2D.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "model_single.h"
#include "renderer.h"
#include "model.h"
#include "x_load.h"
#include "object3D.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CModelSingle::CModelSingle(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = nullptr;
	m_pModel = nullptr;
	m_bCollision = false;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CModelSingle::~CModelSingle()
{

}

//================================================
//����������
//================================================
HRESULT CModelSingle::Init(void)
{
	//�e�̐ݒ�
	m_pModel->SetParent(m_pParent);


	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CObject::OBJTYPE::MODEL);

	//�T�C�Y���擾
	m_size = m_pModel->GetSize();
	SetSize(m_size);
	SetPos(m_pos);

	return S_OK;
}

//================================================
//�I������
//================================================
void CModelSingle::Uninit(void)
{
	Release();
}

//================================================
//�X�V����
//================================================
void CModelSingle::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CModelSingle::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_mtxWorld);		//���f���̃��[���h�}�g���b�N�X�̏�����

	//���f���̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//���f���̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���f���̕`��
	m_pModel->Draw();
}

//================================================
//��������
//================================================
CModelSingle *CModelSingle::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const string &sPas, CModel *pParent, const bool &Collision)
{
	//�C���X�^���X�̐���
	CModelSingle *pModelSingle = nullptr;
	if (pModelSingle == nullptr)
	{
		pModelSingle = new CModelSingle;
		if (pModelSingle != nullptr)
		{
			pModelSingle->m_bCollision = Collision;
			pModelSingle->m_rot = rot;
			pModelSingle->m_pParent = pParent;
			pModelSingle->m_pos = pos;
			//���f���̐���
			pModelSingle->m_pModel = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), sPas);
			pModelSingle->Init();
		}
	}
	return pModelSingle;
}

//================================================
//��������
//================================================
CModelSingle * CModelSingle::Create(const D3DXVECTOR3 & pos, const D3DXVECTOR3 & rot, const int & nType, CModel * pParent, const bool & Collision)
{
	//�C���X�^���X�̐���
	CModelSingle *pModelSingle = nullptr;
	if (pModelSingle == nullptr)
	{
		pModelSingle = new CModelSingle;
		if (pModelSingle != nullptr)
		{
			pModelSingle->m_bCollision = Collision;
			pModelSingle->m_rot = rot;
			pModelSingle->m_pParent = pParent;
			pModelSingle->m_pos = pos;
			//���f���̐���
			pModelSingle->m_pModel = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), nType);
			pModelSingle->Init();
		}
	}
	return pModelSingle;
}

//================================================
//�����蔻�菈��
//================================================
bool CModelSingle::SimpleCollision(CObject *pObject)
{
	bool bLand = false;	//���n���Ă��邩�ǂ���

	//�I�u�W�F�N�g��������|�C���^
	vector<CObject*> object;

	//�擪�̃|�C���^����
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::MODEL));
	int object_size = object.size();

	for (int count_object = 0; count_object < object_size; count_object++)
	{
		if (object[count_object]->GetObjType() == CObject::OBJTYPE::MODEL)
		{
			//���f���V���O���ɃL���X�g
			CModelSingle *pModelSingle = nullptr;
			pModelSingle = (CModelSingle*)object[count_object];

			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Ώۂ̈ʒu
			D3DXVECTOR3 posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���f���̈ʒu
			D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Ώۂ̃T�C�Y
			D3DXVECTOR3 sizeModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���f���̃T�C�Y
			D3DXVECTOR3 posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Ώۂ�1�t���[���O�̈ʒu

			//���f���̈ʒu�E�T�C�Y�擾
			posModel = pModelSingle->GetPos();
			sizeModel = pModelSingle->GetSize();

			//�Ώۂ̈ʒu�E�T�C�Y�擾
			pos = pObject->GetPos();
			posOld = pObject->GetPosOld();
			size = pObject->GetSize();

			if (pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
				pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
				pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
				pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
				pos.y <= posModel.y + sizeModel.y &&
				posOld.y >= posModel.y + sizeModel.y)
			{
				pos.y = posModel.y + sizeModel.y;
				//�ʒu��ݒ�
				pObject->SetPos(pos);

				bLand = true;
			}
			else if (pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
					 pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
					 pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
					 pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
					 pos.y + size.y >= posModel.y &&
					 posOld.y + size.y <= posModel.y)
			{
				pos.y = posModel.y - size.y;
				//�ʒu��ݒ�
				pObject->SetPos(pos);
			}
			if (pos.y + size.y > posModel.y &&
				pos.y < posModel.y + sizeModel.y &&
				pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
				pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
				pos.x + size.x / 2.0f >= posModel.x - sizeModel.x / 2.0f &&
				posOld.x + size.x / 2.0f <= posModel.x - sizeModel.x / 2.0f)
			{
				pos.x = posModel.x - sizeModel.x / 2.0f - size.x / 2.0f;
				//�ʒu��ݒ�
				pObject->SetPos(pos);
			}
			else if (pos.y + size.y > posModel.y &&
					 pos.y < posModel.y + sizeModel.y &&
					 pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
					 pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
					 pos.x - size.x / 2.0f <= posModel.x + sizeModel.x / 2.0f &&
					 posOld.x - size.x / 2.0f >= posModel.x + sizeModel.x / 2.0f)
			{
				pos.x = posModel.x + sizeModel.x / 2.0f + size.x / 2.0f;
				//�ʒu��ݒ�
				pObject->SetPos(pos);
			}
			if (pos.y + size.y > posModel.y &&
				pos.y < posModel.y + sizeModel.y &&
				pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
				pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
				pos.z + size.x / 2.0f >= posModel.z - sizeModel.z / 2.0f &&
				posOld.z + size.x / 2.0f <= posModel.z - sizeModel.z / 2.0f)
			{
				pos.z = posModel.z - sizeModel.z / 2.0f - size.x / 2.0f;
				//�ʒu��ݒ�
				pObject->SetPos(pos);
			}
			else if (pos.y + size.y > posModel.y &&
					 pos.y < posModel.y + sizeModel.y &&
					 pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
					 pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
					 pos.z - size.x / 2.0f <= posModel.z + sizeModel.z / 2.0f &&
					 posOld.z - size.x / 2.0f >= posModel.z + sizeModel.z / 2.0f)
			{
				pos.z = posModel.z + sizeModel.z / 2.0f + size.x / 2.0f;
				//�ʒu��ݒ�
				pObject->SetPos(pos);
			}
		}
	}
	return bLand;
}

//================================================
//��]�����Ă��������蔻�菈��
//================================================
bool CModelSingle::Collision(CObject *pObject)
{
	//���n���Ă��邩�ǂ���
	bool bLand = false;

	//�I�u�W�F�N�g��������|�C���^
	vector<CObject*> object;

	//�擪�̃|�C���^����
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::MODEL));
	int object_size = object.size();

	for (int count_object = 0; count_object < object_size; count_object++)
	{
		if (object[count_object]->GetObjType() == CObject::OBJTYPE::MODEL)
		{
			//pObject��CModelSingle�ɃL���X�g
			CModelSingle *pModelSingle = (CModelSingle*)object[count_object];

			//�����蔻�������ݒ�Ȃ�
			if (pModelSingle->m_bCollision == true)
			{
				//8���_�̎擾
				D3DXVECTOR3 vtxPos[MODEL_VTX];
				for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++)
				{
					vtxPos[nCntVtx] = pModelSingle->m_pModel->GetVtxPos(nCntVtx);
				}

				//�v���C���[�̃T�C�Y�擾
				D3DXVECTOR3 objectSize = pObject->GetSize();

				//�Ώۂ̕��̕��傫������
				vtxPos[0].x -= objectSize.x / 2.0f;
				vtxPos[1].x += objectSize.x / 2.0f;
				vtxPos[2].x -= objectSize.x / 2.0f;
				vtxPos[3].x += objectSize.x / 2.0f;
				vtxPos[4].x -= objectSize.x / 2.0f;
				vtxPos[5].x += objectSize.x / 2.0f;
				vtxPos[6].x -= objectSize.x / 2.0f;
				vtxPos[7].x += objectSize.x / 2.0f;
				vtxPos[0].z += objectSize.x / 2.0f;
				vtxPos[1].z += objectSize.x / 2.0f;
				vtxPos[2].z += objectSize.x / 2.0f;
				vtxPos[3].z += objectSize.x / 2.0f;
				vtxPos[4].z -= objectSize.x / 2.0f;
				vtxPos[5].z -= objectSize.x / 2.0f;
				vtxPos[6].z -= objectSize.x / 2.0f;
				vtxPos[7].z -= objectSize.x / 2.0f;

				//8���_�̃��[���h�}�g���b�N�X���擾
				D3DXMATRIX *pVtxMtxWorld = pModelSingle->m_pModel->GetVtxMtxWorld();
				//8���_�̐ݒ�
				for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++, pVtxMtxWorld++)
				{
					pModelSingle->m_pModel->SetVtxMtxWorld(vtxPos[nCntVtx], nCntVtx);
					vtxPos[nCntVtx] = D3DXVECTOR3(pVtxMtxWorld->_41, pVtxMtxWorld->_42, pVtxMtxWorld->_43);
				}

				//���_���璸�_�܂ł̃x�N�g���Z�o�p
				D3DXVECTOR3 vtxVec[6][2];
				//���_���璸�_�܂ł̃x�N�g���Z�o
				//���̖�
				vtxVec[0][0] = vtxPos[0] - vtxPos[1];
				vtxVec[0][1] = vtxPos[3] - vtxPos[1];
				//�E�̖�
				vtxVec[1][0] = vtxPos[1] - vtxPos[5];
				vtxVec[1][1] = vtxPos[7] - vtxPos[5];
				//�O�̖�
				vtxVec[2][0] = vtxPos[5] - vtxPos[4];
				vtxVec[2][1] = vtxPos[6] - vtxPos[4];
				//���̖�
				vtxVec[3][0] = vtxPos[4] - vtxPos[0];
				vtxVec[3][1] = vtxPos[2] - vtxPos[0];
				//��̖�
				vtxVec[4][0] = vtxPos[1] - vtxPos[0];
				vtxVec[4][1] = vtxPos[4] - vtxPos[0];
				//���̖�
				vtxVec[5][0] = vtxPos[7] - vtxPos[6];
				vtxVec[5][1] = vtxPos[2] - vtxPos[6];

				//�@���ۑ��p�ϐ�
				D3DXVECTOR3 vecNor[6];
				for (int nCntSurfase = 0; nCntSurfase < 6; nCntSurfase++)
				{
					//�e�ʂ̖@�������߂�
					D3DXVec3Cross(&vecNor[nCntSurfase], &vtxVec[nCntSurfase][0], &vtxVec[nCntSurfase][1]);

					//�x�N�g���𐳋K������(�x�N�g���̑傫����1�ɂ���)
					D3DXVec3Normalize(&vecNor[nCntSurfase], &vecNor[nCntSurfase]);
				}

				//�Ώۂ̌��݈ʒu�擾
				D3DXVECTOR3 pos = pObject->GetPos();

				//�Ώۂ�1�t���[���O�̈ʒu�擾
				D3DXVECTOR3 posOld = pObject->GetPosOld();

				//���_�̈ʒu����Ώۂ̌��݂̈ʒu�̃x�N�g�����Z�o
				D3DXVECTOR3 vecPos[6];
				//���̖�
				vecPos[0] = pos - vtxPos[0];
				//�E�̖�
				vecPos[1] = pos - vtxPos[1];
				//�O�̖�
				vecPos[2] = pos - vtxPos[5];
				//���̖�
				vecPos[3] = pos - vtxPos[4];
				//��̖�
				vecPos[4] = pos - vtxPos[1];
				//���̖�
				vecPos[5] = pos - vtxPos[7];

				//�Z�o�����x�N�g���Ɩ@���̃x�N�g���̓��ς����߂�
				float fVecDot[6];
				for (int nCntSurfase = 0; nCntSurfase < 6; nCntSurfase++)
				{
					fVecDot[nCntSurfase] = D3DXVec3Dot(&vecNor[nCntSurfase], &vecPos[nCntSurfase]);
				}

				//�|���S���̒��_����Ώۂ�1�t���[���O�̈ʒu�̃x�N�g�����Z�o
				D3DXVECTOR3 vecPosOld[6];
				//���̖�
				vecPosOld[0] = posOld - vtxPos[0];
				//�E�̖�
				vecPosOld[1] = posOld - vtxPos[1];
				//�O�̖�
				vecPosOld[2] = posOld - vtxPos[5];
				//���̖�
				vecPosOld[3] = posOld - vtxPos[4];
				//��̖�
				vecPosOld[4] = posOld - vtxPos[1];
				//���̖�
				vecPosOld[5] = posOld - vtxPos[7];

				//�Z�o�����x�N�g���Ɩ@���̃x�N�g���̓��ς����߂�
				float fVecDotOld[6];
				for (int nCntSurfase = 0; nCntSurfase < 6; nCntSurfase++)
				{
					fVecDotOld[nCntSurfase] = D3DXVec3Dot(&vecNor[nCntSurfase], &vecPosOld[nCntSurfase]);
				}

				//���ς̌v�Z���ʂ��}�C�i�X�̎�
				if (fVecDot[0] <= 0.0f && fVecDot[1] <= 0.0f && fVecDot[2] <= 0.0f && fVecDot[3] <= 0.0f && fVecDot[4] <= 0.0f &&
					fVecDotOld[4] > -FLT_EPSILON * 10000)
				{//��̖�
				 //�����o���ʒu�����߂�
					D3DXVECTOR3 objectPos = pos;
					objectPos.y = ((vecNor[4].x * vecPos[4].x) - (vecNor[4].z * vecPos[4].z)) / vecNor[4].y;

					objectPos.y += pModelSingle->m_pos.y + pModelSingle->m_size.y;
					//objectPos.y += pModelSingle->m_pos.y ;

					pObject->SetPos(objectPos);
					bLand = true;
				}
				else if (fVecDot[0] <= 0.0f && fVecDot[1] <= 0.0f && fVecDot[2] <= 0.0f && fVecDot[3] <= 0.0f && fVecDot[5] <= 0.0f &&
					fVecDotOld[5] > -FLT_EPSILON * 10000)
				{//���̖�
				
				}
				if (fVecDot[0] <= 0.0f && fVecDot[1] <= 0.0f && fVecDot[3] <= 0.0f && fVecDot[4] <= 0.0f && fVecDot[5] <= 0.0f &&
					fVecDotOld[0] > -FLT_EPSILON * 10000)
				{//���̖�
					//���[�u�x�N�g�������߂�
					D3DXVECTOR3 moveVec = pos - posOld;

					//���[�u�x�N�g���Ɩ@���̓��ς����߂�
					float fDotMoveVec = -D3DXVec3Dot(&moveVec, &vecNor[0]);

					//�@���̕����ɓ��ϕ��L�΂����x�N�g�������߂�
					D3DXVECTOR3 norInVec = D3DXVECTOR3(vecNor[0].x * fDotMoveVec, vecNor[0].y * fDotMoveVec, vecNor[0].z * fDotMoveVec);

					//�Ώۂ̉��o������߂�
					D3DXVECTOR3 objectPos;
					objectPos = pos + norInVec;

					pObject->SetPos(objectPos);
				}
				else if (fVecDot[1] <= 0.0f && fVecDot[2] <= 0.0f && fVecDot[3] <= 0.0f && fVecDot[4] <= 0.0f && fVecDot[5] <= 0.0f &&
						 fVecDotOld[2] > -FLT_EPSILON * 10000)
				{//�O�̖�
					//���[�u�x�N�g�������߂�
					D3DXVECTOR3 moveVec = pos - posOld;

					//���[�u�x�N�g���Ɩ@���̓��ς����߂�
					float fDotMoveVec = -D3DXVec3Dot(&moveVec, &vecNor[2]);

					//�@���̕����ɓ��ϕ��L�΂����x�N�g�������߂�
					D3DXVECTOR3 norInVec = D3DXVECTOR3(vecNor[2].x * fDotMoveVec, vecNor[2].y * fDotMoveVec, vecNor[2].z * fDotMoveVec);

					//�Ώۂ̉��o������߂�
					D3DXVECTOR3 objectPos;
					objectPos = pos + norInVec;

					pObject->SetPos(objectPos);
				}
				if (fVecDot[0] <= 0.0f && fVecDot[1] <= 0.0f && fVecDot[2] <= 0.0f && fVecDot[4] <= 0.0f && fVecDot[5] <= 0.0f &&
					fVecDotOld[1] > -FLT_EPSILON * 10000)
				{//�E�̖�
					//���[�u�x�N�g�������߂�
					D3DXVECTOR3 moveVec = pos - posOld;

					//���[�u�x�N�g���Ɩ@���̓��ς����߂�
					float fDotMoveVec = -D3DXVec3Dot(&moveVec, &vecNor[1]);

					//�@���̕����ɓ��ϕ��L�΂����x�N�g�������߂�
					D3DXVECTOR3 norInVec = D3DXVECTOR3(vecNor[1].x * fDotMoveVec, vecNor[1].y * fDotMoveVec, vecNor[1].z * fDotMoveVec);

					//�Ώۂ̉��o������߂�
					D3DXVECTOR3 objectPos;
					objectPos = pos + norInVec;

					pObject->SetPos(objectPos);
				}
				else if (fVecDot[0] <= 0.0f && fVecDot[2] <= 0.0f && fVecDot[3] <= 0.0f && fVecDot[4] <= 0.0f && fVecDot[5] <= 0.0f &&
						 fVecDotOld[3] > -FLT_EPSILON * 10000)
				{//���̖�
					//���[�u�x�N�g�������߂�
					D3DXVECTOR3 moveVec = pos - posOld;

					//���[�u�x�N�g���Ɩ@���̓��ς����߂�
					float fDotMoveVec = -D3DXVec3Dot(&moveVec, &vecNor[3]);

					//�@���̕����ɓ��ϕ��L�΂����x�N�g�������߂�
					D3DXVECTOR3 norInVec = D3DXVECTOR3(vecNor[3].x * fDotMoveVec, vecNor[3].y * fDotMoveVec, vecNor[3].z * fDotMoveVec);

					//�Ώۂ̉��o������߂�
					D3DXVECTOR3 objectPos;
					objectPos = pos + norInVec;

					pObject->SetPos(objectPos);
				}
			}
		}
	}
	return bLand;
}

//================================================
//�����̏Փ˔���
//================================================
int CModelSingle::CollisionAny(CObject *pObject)
{
	//�I�u�W�F�N�g��������|�C���^
	vector<CObject*> object;

	//�擪�̃|�C���^����
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::MODEL));
	int object_size = object.size();

	for (int count_object = 0; count_object < object_size; count_object++)
	{
		if (object[count_object]->GetObjType() == CObject::OBJTYPE::MODEL)
		{
			//pObject��CModelSingle�ɃL���X�g
			CModelSingle *pModelSingle = (CModelSingle*)object[count_object];

			//�����蔻�������ݒ�Ȃ�
			if (pModelSingle->m_bCollision == true)
			{
				//8���_�̎擾
				D3DXVECTOR3 vtxPos[MODEL_VTX];
				for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++)
				{
					vtxPos[nCntVtx] = pModelSingle->m_pModel->GetVtxPos(nCntVtx);
				}

				//8���_�̃��[���h�}�g���b�N�X���擾
				D3DXMATRIX *pVtxMtxWorld = pModelSingle->m_pModel->GetVtxMtxWorld();
				//8���_�̐ݒ�
				for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++, pVtxMtxWorld++)
				{
					//���[���h�}�g���b�N�X�ݒ�
					pModelSingle->SetMtxWorld();
					//���f���̐ݒ�
					//pModelSingle->m_pModel->SetVtxMtxWorld(vtxPos[nCntVtx], nCntVtx);
					vtxPos[nCntVtx] = D3DXVECTOR3(pVtxMtxWorld->_41, pVtxMtxWorld->_42, pVtxMtxWorld->_43);
				}


				//���_���璸�_�܂ł̃x�N�g���Z�o�p
				D3DXVECTOR3 vtxVec[6][2];
				//���_���璸�_�܂ł̃x�N�g���Z�o
				//���̖�
				vtxVec[0][0] = vtxPos[0] - vtxPos[1];
				vtxVec[0][1] = vtxPos[3] - vtxPos[1];
				//�E�̖�
				vtxVec[1][0] = vtxPos[1] - vtxPos[5];
				vtxVec[1][1] = vtxPos[7] - vtxPos[5];
				//�O�̖�
				vtxVec[2][0] = vtxPos[5] - vtxPos[4];
				vtxVec[2][1] = vtxPos[6] - vtxPos[4];
				//���̖�
				vtxVec[3][0] = vtxPos[4] - vtxPos[0];
				vtxVec[3][1] = vtxPos[2] - vtxPos[0];
				//��̖�
				vtxVec[4][0] = vtxPos[1] - vtxPos[0];
				vtxVec[4][1] = vtxPos[4] - vtxPos[0];
				//���̖�
				vtxVec[5][0] = vtxPos[7] - vtxPos[6];
				vtxVec[5][1] = vtxPos[2] - vtxPos[6];

				//�@���ۑ��p�ϐ�
				D3DXVECTOR3 vecNor[6];
				for (int nCntSurfase = 0; nCntSurfase < 6; nCntSurfase++)
				{
					//�e�ʂ̖@�������߂�
					D3DXVec3Cross(&vecNor[nCntSurfase], &vtxVec[nCntSurfase][0], &vtxVec[nCntSurfase][1]);

					//�x�N�g���𐳋K������(�x�N�g���̑傫����1�ɂ���)
					D3DXVec3Normalize(&vecNor[nCntSurfase], &vecNor[nCntSurfase]);
				}

				//�Ώۂ̌��݈ʒu�擾
				D3DXVECTOR3 pos = pObject->GetPos();

				//���_�̈ʒu����Ώۂ̌��݂̈ʒu�̃x�N�g�����Z�o
				D3DXVECTOR3 vecPos[6];
				//���̖�
				vecPos[0] = pos - vtxPos[0];
				//�E�̖�
				vecPos[1] = pos - vtxPos[1];
				//�O�̖�
				vecPos[2] = pos - vtxPos[5];
				//���̖�
				vecPos[3] = pos - vtxPos[4];
				//��̖�
				vecPos[4] = pos - vtxPos[1];
				//���̖�
				vecPos[5] = pos - vtxPos[7];

				//�Z�o�����x�N�g���Ɩ@���̃x�N�g���̓��ς����߂�
				float fVecDot[6];
				for (int nCntSurfase = 0; nCntSurfase < 6; nCntSurfase++)
				{
					fVecDot[nCntSurfase] = D3DXVec3Dot(&vecNor[nCntSurfase], &vecPos[nCntSurfase]);
				}

				//�S�Ă̓��ς̌v�Z���ʂ��}�C�i�X�̎�
				if (fVecDot[0] <= 0.0f && fVecDot[1] <= 0.0f && fVecDot[2] <= 0.0f &&
					fVecDot[3] <= 0.0f && fVecDot[4] <= 0.0f && fVecDot[5] <= 0.0f)
				{
					
				}
			}
		}
	}
	return 0;
}

//================================================
//���[���h�}�g���b�N�X�ݒ菈��
//================================================
void CModelSingle::SetMtxWorld(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X

	D3DXMatrixIdentity(&m_mtxWorld);		//���f���̃��[���h�}�g���b�N�X�̏�����

											//���f���̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//���f���̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���f���̃��[���h�}�g���b�N�X�ݒ�
	m_pModel->SetMtxWorldPos();
}
