//================================================
//3D�|���S���̏�����
//Author:��������
//================================================
#include <math.h>
#include "floor.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CFloor::CFloor(CObject::PRIORITY Priority) :CObject3D(Priority)
{
	
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CFloor::~CFloor()
{

}

//================================================
//����������
//================================================
HRESULT CFloor::Init(void)
{
	CObject3D::Init();

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::FLOOR);

	return S_OK;
}

//================================================
//�I������
//================================================
void CFloor::Uninit(void)
{
	CObject3D::Uninit();
}

//================================================
//�X�V����
//================================================
void CFloor::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CFloor::Draw(void)
{
	CObject3D::Draw();
}

//================================================
//��������
//================================================
CFloor* CFloor::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot)
{
	//�C���X�^���X�̐���
	CFloor *pFloor = nullptr;
	if (pFloor == nullptr)
	{
		pFloor = new CFloor();
		if (pFloor != nullptr)
		{
			pFloor->m_pos = pos;
			pFloor->m_size = size;
			pFloor->m_rot = rot;
			pFloor->Init();
		}
	}
	return pFloor;
}

//================================================
//�����蔻��
//================================================
bool CFloor::Collision(CObject *pObject, const float &fRadius)
{
	bool bLand = false;	//���n���Ă��邩�ǂ���

	//�I�u�W�F�N�g��������|�C���^
	vector<CObject*> object;

	//�擪�̃|�C���^����
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::POLYGON_3D));
	int nProprty_Size = object.size();

	for (int nCnt = 0; nCnt < nProprty_Size; nCnt++)
	{
		if (object[nCnt]->GetObjType() == CObject::OBJTYPE::FLOOR)
		{
			//�|�C���^��CFloor�ɃL���X�g
			CFloor *pFloor = nullptr;
			pFloor = (CFloor*)object[nCnt];

			//�e���_����e���_�̃x�N�g�����Z�o
			D3DXVECTOR3 vtxPos[VERTEX_3D_NUM];
			for (int nCntVtx = 0; nCntVtx < VERTEX_3D_NUM; nCntVtx++)
			{
				vtxPos[nCntVtx] = D3DXVECTOR3(pFloor->m_vtxMtxWorld[nCntVtx]._41,
											  pFloor->m_vtxMtxWorld[nCntVtx]._42,
											  pFloor->m_vtxMtxWorld[nCntVtx]._43);
			}

			//�����̔��a���傫������
			vtxPos[0] += D3DXVECTOR3(-fRadius, 0.0f, fRadius);
			vtxPos[1] += D3DXVECTOR3(fRadius, 0.0f, fRadius);
			vtxPos[2] += D3DXVECTOR3(-fRadius, 0.0f, -fRadius);
			vtxPos[3] += D3DXVECTOR3(fRadius, 0.0f, -fRadius);


			D3DXVECTOR3 vecVtx[VERTEX_3D_NUM];
			vecVtx[0] = vtxPos[1] - vtxPos[0];
			vecVtx[1] = vtxPos[3] - vtxPos[1];
			vecVtx[2] = vtxPos[2] - vtxPos[3];
			vecVtx[3] = vtxPos[0] - vtxPos[2];

			//�@���ۑ��p
			D3DXVECTOR3 vecNor;

			//���_���璸�_�܂ł̃x�N�g���Z�o�p
			D3DXVECTOR3 vtxVec[2];
			//���_���璸�_�܂ł̃x�N�g���Z�o
			vtxVec[0] = vtxPos[1] - vtxPos[0];
			vtxVec[1] = vtxPos[2] - vtxPos[0];

			//�|���S���̖@�������߂�
			D3DXVec3Cross(&vecNor, &vtxVec[0], &vtxVec[1]);

			//�x�N�g���𐳋K������(�x�N�g���̑傫����1�ɂ���)
			D3DXVec3Normalize(&vecNor, &vecNor);

			//�Ώۂ̌��݈ʒu�擾
			D3DXVECTOR3 pos = pObject->GetPos();

			//�e���_����Ώۂ̌��݈ʒu�܂ł̃x�N�g�����Z�o
			D3DXVECTOR3 vecObj[VERTEX_3D_NUM];
			vecObj[0] = pos - vtxPos[0];
			vecObj[1] = pos - vtxPos[1];
			vecObj[2] = pos - vtxPos[3];
			vecObj[3] = pos - vtxPos[2];

			//�Ώۂ�1�t���[���O�̈ʒu�擾
			D3DXVECTOR3 posOld = pObject->GetPosOld();

			//�e���_����Ώۂ�1�t���[���O�̈ʒu�܂ł̃x�N�g�����Z�o
			D3DXVECTOR3 vecObjOld[VERTEX_3D_NUM];
			vecObjOld[0] = posOld - vtxPos[0];
			vecObjOld[1] = posOld - vtxPos[1];
			vecObjOld[2] = posOld - vtxPos[3];
			vecObjOld[3] = posOld - vtxPos[2];

			//�e���_����Ώۂ̌��݈ʒu�܂ł̃x�N�g���Ɗe���_����e���_�̃x�N�g���̊O��(2D)�����߂�
			float fvecCross[VERTEX_3D_NUM];
			//�e���_����Ώۂ�1�t���[���O�̈ʒu�܂ł̃x�N�g���Ɗe���_����e���_�̃x�N�g���̊O��(2D)�����߂�
			float fvecCrossOld[VERTEX_3D_NUM];

			for (int nCntVec = 0; nCntVec < VERTEX_3D_NUM; nCntVec++)
			{
				//�O�ς̌v�Z
				fvecCross[nCntVec] = (vecVtx[nCntVec].x * vecObj[nCntVec].z) - (vecObj[nCntVec].x * vecVtx[nCntVec].z);
				fvecCrossOld[nCntVec] = (vecVtx[nCntVec].x * vecObjOld[nCntVec].z) - (vecObjOld[nCntVec].x * vecVtx[nCntVec].z);
			}

			//�|���S���͈͓̔��ɂ��邩�ǂ���
			if ((fvecCross[0] <= 0.0f && fvecCross[1] <= 0.0f && fvecCross[2] <= 0.0f && fvecCross[3] <= 0.0f) ||
				(fvecCrossOld[0] <= 0.0f && fvecCrossOld[1] <= 0.0f && fvecCrossOld[2] <= 0.0f && fvecCrossOld[3] <= 0.0f))
			{
				//�|���S���̈ʒu����Ώۂ̌��݂̈ʒu�̃x�N�g�����Z�o
				D3DXVECTOR3 vecPos;
				vecPos = pos - pFloor->m_pos;

				//�Z�o�����x�N�g���Ɩ@���̃x�N�g���̓��ς����߂�
				float fVecDot;
				fVecDot = D3DXVec3Dot(&vecNor, &vecPos);

				//�|���S���̒��_����Ώۂ�1�t���[���O�̈ʒu�̃x�N�g�����Z�o
				D3DXVECTOR3 vecPosOld;
				vecPosOld = posOld - pFloor->m_pos;

				//�Z�o�����x�N�g���Ɩ@���̃x�N�g���̓��ς����߂�
				float fVecDotOld;
				fVecDotOld = D3DXVec3Dot(&vecNor, &vecPosOld);

				//���ς̌v�Z���ʂ��}�C�i�X�̎�
				if (fVecDot < 0.0f && fVecDotOld >= -FLT_EPSILON * 10000)
				{
					//�����o���ʒu�����߂�
					D3DXVECTOR3 objectPos = pos;
					objectPos.y = ((vecNor.x * vecPos.x) - (vecNor.z * vecPos.z)) / vecNor.y;

					objectPos.y += pFloor->m_pos.y;

					pObject->SetPos(objectPos);
					bLand = true;
				}
			}
		}
	}
	return bLand;
}

//================================================
//�e�Ƃ̓����蔻��
//================================================
bool CFloor::CollisionShadow(CObject * pObject)
{
	bool bLand = false;	//���n���Ă��邩�ǂ���

	//�I�u�W�F�N�g��������|�C���^
	vector<CObject*> object;

	//�擪�̃|�C���^����
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::POLYGON_3D));
	int nProprty_Size = object.size();

	for (int nCnt = 0; nCnt < nProprty_Size; nCnt++)
	{
		if (object[nCnt]->GetObjType() == CObject::OBJTYPE::FLOOR)
		{
			//�|�C���^��CFloor�ɃL���X�g
			CFloor *pFloor = nullptr;
			pFloor = (CFloor*)object[nCnt];

			//�e���_����e���_�̃x�N�g�����Z�o
			D3DXVECTOR3 vtxPos[VERTEX_3D_NUM];
			for (int nCntVtx = 0; nCntVtx < VERTEX_3D_NUM; nCntVtx++)
			{
				vtxPos[nCntVtx] = D3DXVECTOR3(pFloor->m_vtxMtxWorld[nCntVtx]._41,
											  pFloor->m_vtxMtxWorld[nCntVtx]._42,
											  pFloor->m_vtxMtxWorld[nCntVtx]._43);
			}
			D3DXVECTOR3 vecVtx[VERTEX_3D_NUM];
			vecVtx[0] = vtxPos[1] - vtxPos[0];
			vecVtx[1] = vtxPos[3] - vtxPos[1];
			vecVtx[2] = vtxPos[2] - vtxPos[3];
			vecVtx[3] = vtxPos[0] - vtxPos[2];

			//�@���ۑ��p
			D3DXVECTOR3 vecNor;

			//���_���璸�_�܂ł̃x�N�g���Z�o�p
			D3DXVECTOR3 vtxVec[2];
			//���_���璸�_�܂ł̃x�N�g���Z�o
			vtxVec[0] = vtxPos[1] - vtxPos[0];
			vtxVec[1] = vtxPos[2] - vtxPos[0];

			//�|���S���̖@�������߂�
			D3DXVec3Cross(&vecNor, &vtxVec[0], &vtxVec[1]);

			//�x�N�g���𐳋K������(�x�N�g���̑傫����1�ɂ���)
			D3DXVec3Normalize(&vecNor, &vecNor);

			//�Ώۂ̌��݈ʒu�擾
			D3DXVECTOR3 pos = pObject->GetPos();

			//�e���_����Ώۂ̌��݈ʒu�܂ł̃x�N�g�����Z�o
			D3DXVECTOR3 vecObj[VERTEX_3D_NUM];
			vecObj[0] = pos - vtxPos[0];
			vecObj[1] = pos - vtxPos[1];
			vecObj[2] = pos - vtxPos[3];
			vecObj[3] = pos - vtxPos[2];

			//�Ώۂ�1�t���[���O�̈ʒu�擾
			D3DXVECTOR3 posOld = pObject->GetPosOld();

			//�e���_����Ώۂ�1�t���[���O�̈ʒu�܂ł̃x�N�g�����Z�o
			D3DXVECTOR3 vecObjOld[VERTEX_3D_NUM];
			vecObjOld[0] = posOld - vtxPos[0];
			vecObjOld[1] = posOld - vtxPos[1];
			vecObjOld[2] = posOld - vtxPos[3];
			vecObjOld[3] = posOld - vtxPos[2];

			//�e���_����Ώۂ̌��݈ʒu�܂ł̃x�N�g���Ɗe���_����e���_�̃x�N�g���̊O��(2D)�����߂�
			float fvecCross[VERTEX_3D_NUM];
			//�e���_����Ώۂ�1�t���[���O�̈ʒu�܂ł̃x�N�g���Ɗe���_����e���_�̃x�N�g���̊O��(2D)�����߂�
			float fvecCrossOld[VERTEX_3D_NUM];

			for (int nCntVec = 0; nCntVec < VERTEX_3D_NUM; nCntVec++)
			{
				//�O�ς̌v�Z
				fvecCross[nCntVec] = (vecVtx[nCntVec].x * vecObj[nCntVec].z) - (vecObj[nCntVec].x * vecVtx[nCntVec].z);
				fvecCrossOld[nCntVec] = (vecVtx[nCntVec].x * vecObjOld[nCntVec].z) - (vecObjOld[nCntVec].x * vecVtx[nCntVec].z);
			}

			//�|���S���͈͓̔��ɂ��邩�ǂ���
			if ((fvecCross[0] <= 0.0f && fvecCross[1] <= 0.0f && fvecCross[2] <= 0.0f && fvecCross[3] <= 0.0f) ||
				(fvecCrossOld[0] <= 0.0f && fvecCrossOld[1] <= 0.0f && fvecCrossOld[2] <= 0.0f && fvecCrossOld[3] <= 0.0f))
			{
				//�ʒu�����̈ʒu�ɂ���
				pos.y = pFloor->m_pos.y;

				//�ʒu��ݒ�
				pObject->SetPos(pos);

				bLand = true;
			}
		}
	}
	return bLand;
}
