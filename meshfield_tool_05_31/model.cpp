//=======================================================================
//���f��(x�t�@�C��)�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "x_load.h"
#include "object.h"
#include "texture.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CModel::CModel()
{
	m_pMesh = nullptr;		
	m_pBuffMat = nullptr;	
	m_nNumMat = 0;
	memset(&m_pTexture, NULL, sizeof(m_pTexture));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = nullptr;
	m_bObjParent = false;
	m_diffuseAlpha = 1.0f;

	for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++)
	{
		m_vtxPos[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vtxRot[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CModel::~CModel()
{

}

//================================================
//����������
//================================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, string sPas)
{
	//�ϐ�������
	m_bObjParent = false;
	m_diffuseAlpha = 1.0f;

	m_vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
	m_vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

	m_rot = rot;
	m_pos = pos;

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	
	

	//�e�N�X�`���f�[�^�̎擾
	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL *)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		LPDIRECT3DTEXTURE9 texbuf = NULL;
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{
			for (int nCntTex = 0; nCntTex < CManager::GetInstance()->GetTexture()->GetNum(); nCntTex++)
			{
				string sTexturePas = CManager::GetInstance()->GetTexture()->GetPas(nCntTex);
				if (strcmp(sTexturePas.c_str(), pMat[nCntMat].pTextureFilename) == 0)
				{
					texbuf = CManager::GetInstance()->GetTexture()->GetTexture(nCntTex);
					m_pTexture.push_back(texbuf);
				}
			}
		}
		else
		{
			m_pTexture.push_back(texbuf);
		}
	}

	//���_���̎擾
	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	//���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//���_���W�̑��

		//�S�Ă̒��_���r���čő�l�ƍŏ���𔲂��o��
		//�ő�l
		if (vtx.x >= m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y >= m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z >= m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}
		//�ŏ��l
		if (vtx.x <= m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y <= m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z <= m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}

		m_size.x = m_vtxMax.x - m_vtxMin.x;
		m_size.y = m_vtxMax.y - m_vtxMin.y;
		m_size.z = m_vtxMax.z - m_vtxMin.z;

		pVtxBuff += sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//8���_�̈ʒu�����߂�
	m_vtxPos[0].x = m_vtxMin.x;
	m_vtxPos[0].z = m_vtxMax.z;
	m_vtxPos[0].y = m_vtxMax.y;
	m_vtxPos[1].x = m_vtxMax.x;
	m_vtxPos[1].z = m_vtxMax.z;
	m_vtxPos[1].y = m_vtxMax.y;
	m_vtxPos[2].x = m_vtxMin.x;
	m_vtxPos[2].z = m_vtxMax.z;
	m_vtxPos[2].y = m_vtxMin.y;
	m_vtxPos[3].x = m_vtxMax.x;
	m_vtxPos[3].z = m_vtxMax.z;
	m_vtxPos[3].y = m_vtxMin.y;
	m_vtxPos[4].x = m_vtxMin.x;
	m_vtxPos[4].z = m_vtxMin.z;
	m_vtxPos[4].y = m_vtxMax.y;
	m_vtxPos[5].x = m_vtxMax.x;
	m_vtxPos[5].z = m_vtxMin.z;
	m_vtxPos[5].y = m_vtxMax.y;
	m_vtxPos[6].x = m_vtxMin.x;
	m_vtxPos[6].z = m_vtxMin.z;
	m_vtxPos[6].y = m_vtxMin.y;
	m_vtxPos[7].x = m_vtxMax.x;
	m_vtxPos[7].z = m_vtxMin.z;
	m_vtxPos[7].y = m_vtxMin.y;

	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();
	return S_OK;
}

//================================================
//�I������
//================================================
void CModel::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	int nTexType = m_pTexture.size();
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < nTexType; nCntTex++)
	{
		if (m_pTexture[nCntTex] != nullptr)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = nullptr;
		}
	}
}

//================================================
//�X�V����
//================================================
void CModel::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CModel::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;						//�e�̃}�g���b�N�X

	D3DXMatrixIdentity(&m_mtxWorld);			//���[���h�}�g���b�N�X�̏�����

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	if (m_bObjParent == false)
	{
		//�e�p�[�c�̐e�̃}�g���b�N�X�̐ݒ�
		if (m_pParent != nullptr)
		{
			mtxParent = m_pParent->GetMtx();
		}
		else
		{
			pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
		}
	}
	else
	{
		mtxParent = *m_mtxWorldParent;
	}
	

	//�Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Diffuse.a = m_diffuseAlpha;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//8���_�̐ݒ�
	for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++)
	{
		D3DXMatrixIdentity(&m_vtxMtxWorld[nCntVtx]);		//���[���h�}�g���b�N�X�̏�����

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_vtxRot[nCntVtx].y, m_vtxRot[nCntVtx].x, m_vtxRot[nCntVtx].z);
		D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_vtxPos[nCntVtx].x, m_vtxPos[nCntVtx].y, m_vtxPos[nCntVtx].z);
		D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxTrans);

		//�e�̃}�g���b�N�X
		mtxParent = m_mtxWorld;

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_vtxMtxWorld[nCntVtx]);
	}
}

//================================================
//��������
//================================================
CModel* CModel::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const string &sPas)
{
	//�C���X�^���X�̐���
	CModel *pModel = nullptr;
	if (pModel == nullptr)
	{
		pModel = new CModel;
		if (pModel != nullptr)
		{
			//X�t�@�C�����ǂݍ���
			pModel->m_pBuffMat = CManager::GetInstance()->GetXload()->GetBuffMat(sPas);
			pModel->m_nNumMat = CManager::GetInstance()->GetXload()->GetNumMat(sPas);
			pModel->m_pMesh = CManager::GetInstance()->GetXload()->GetMesh(sPas);
			pModel->m_sFileName = sPas;
			pModel->Init(pos, rot, sPas);
		}
	}
	return pModel;
}

//================================================
//��������
//================================================
CModel * CModel::Create(const D3DXVECTOR3 & pos, const D3DXVECTOR3 & rot, const int & nType)
{
	//�C���X�^���X�̐���
	CModel *pModel = nullptr;
	if (pModel == nullptr)
	{
		pModel = new CModel;
		if (pModel != nullptr)
		{
			//X�t�@�C�����ǂݍ���
			pModel->m_pBuffMat = CManager::GetInstance()->GetXload()->GetBuffMat(nType);
			pModel->m_nNumMat = CManager::GetInstance()->GetXload()->GetNumMat(nType);
			pModel->m_pMesh = CManager::GetInstance()->GetXload()->GetMesh(nType);
			pModel->m_sFileName = CManager::GetInstance()->GetXload()->GetType(nType);
			pModel->Init(pos, rot, CManager::GetInstance()->GetXload()->GetType(nType));
		}
	}
	return pModel;
}

//================================================
//�e�ݒ菈��
//================================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//================================================
//�e�ݒ菈��
//================================================
D3DXMATRIX CModel::GetMtx(void)
{
	return m_mtxWorld;
}

//================================================
//�T�C�Y�擾����
//================================================
D3DXVECTOR3 CModel::GetSize(void)
{
	return m_size;
}

//================================================
//�����蔻�菈��
//================================================
void CModel::Collision(void)
{
	//�I�u�W�F�N�g��������|�C���^
	vector<CObject*> object;

	//�擪�̃|�C���^����
	object = CObject::GetObject(static_cast<int>(CObject::PRIORITY::MODEL));
	int nProprty_Size = object.size();

	for (int nCntPriorty = 0; nCntPriorty < nProprty_Size; nCntPriorty++)
	{
		if (object[nProprty_Size]->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//������̓����蔻��Ɏg��
			//CPlayer *pPlayer = nullptr;									//�v���C���[�̃|�C���^
			D3DXVECTOR3 posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�Ώۂ̈ʒu
			D3DXVECTOR3 sizePlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�Ώۂ̃T�C�Y
			D3DXVECTOR3 posOldPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�Ώۂ�1�t���[���O�̈ʒu
			D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�@���x�N�g��
			D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�Ώۂ̃��[�u�x�N�g��
			D3DXVECTOR3 norInVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�@���x�N�g���̕����ɑΏۂƖ@���x�N�g���̓��ϕ��L�΂����x�N�g��
			D3DXVECTOR3 posPlayerVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�Ώۂ������o���ʒu�܂ł̃x�N�g��
			D3DXVECTOR3 posFinPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�Ώۂ������o���ʒu
			D3DXVECTOR3 vecVtx[4];										//�ΏۂƂ̃x�N�g���Z�o�̂��߂Ɏg�����_�܂ł̃x�N�g��
			D3DXVECTOR3 vecObj[4];										//�ΏۂƂ̃x�N�g���Z�o�̂��߂Ɏg���Ώۂ܂ł̃x�N�g��
			D3DXVECTOR3 vecObjOld[4];									//1�t���[���O�̑ΏۂƂ̃x�N�g���Z�o�̂��߂Ɏg���Ώۂ܂ł̃x�N�g��
			D3DXVECTOR3 vecNorVtx[2];									//�ʂ̖@���x�N�g�������߂邽�߂̒��_�x�N�g��
			float fVecNorObj[4];										//�Ώۂƒ��_�̖@���x�N�g���̒���
			float fVecNorObjOld[4];										//1�t���[���O�̑Ώۂƒ��_�̖@���x�N�g���̒���
			float fInVec = 0.0f;										//�ΏۂƖ@���x�N�g���̓���

			//�ォ��̓����蔻��Ɏg��
			D3DXVECTOR3 topVtxVec[4];									//�ΏۂƂ̃x�N�g���Z�o�̂��߂Ɏg�����_�܂ł̃x�N�g��
			D3DXVECTOR3 topVecObj[4];									//�ΏۂƂ̃x�N�g���Z�o�̂��߂Ɏg���Ώۂ܂ł̃x�N�g��
			D3DXVECTOR3 topVecObjOld[4];								//1�t���[���O�̑ΏۂƂ̃x�N�g���Z�o�̂��߂Ɏg���Ώۂ܂ł̃x�N�g��
			float fTopVecNorObj[4];										//�Ώۂƒ��_�̖@���x�N�g���̒���
			float fTopVecNorObjOld[4];									//1�t���[���O�̑Ώۂƒ��_�̖@���x�N�g���̒���

			//����������
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				vecVtx[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				vecObj[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				vecObjOld[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				fVecNorObj[nCnt] = 0.0f;
				fVecNorObjOld[nCnt] = 0.0f;
			}

			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				vecNorVtx[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}

			//�v���C���[�̃|�C���^�ɃL���X�g
			//pPlayer = (CPlayer*)object[nProprty_Size];

			//�v���C���[�̈ʒu�擾
			//posPlayer = pPlayer->GetPos();
			//posOldPlayer = pPlayer->GetPosOld();

			//�v���C���[�̃T�C�Y�擾
			//sizePlayer = pPlayer->GetSize();

			//�Ώۂ̕��̕��傫������
			m_vtxPos[0].x -= sizePlayer.x / 2.0f;
			m_vtxPos[1].x += sizePlayer.x / 2.0f;
			m_vtxPos[2].x -= sizePlayer.x / 2.0f;
			m_vtxPos[3].x += sizePlayer.x / 2.0f;
			m_vtxPos[4].x -= sizePlayer.x / 2.0f;
			m_vtxPos[5].x += sizePlayer.x / 2.0f;
			m_vtxPos[6].x -= sizePlayer.x / 2.0f;
			m_vtxPos[7].x += sizePlayer.x / 2.0f;
			m_vtxPos[0].z += sizePlayer.x / 2.0f;
			m_vtxPos[1].z += sizePlayer.x / 2.0f;
			m_vtxPos[2].z += sizePlayer.x / 2.0f;
			m_vtxPos[3].z += sizePlayer.x / 2.0f;
			m_vtxPos[4].z -= sizePlayer.x / 2.0f;
			m_vtxPos[5].z -= sizePlayer.x / 2.0f;
			m_vtxPos[6].z -= sizePlayer.x / 2.0f;
			m_vtxPos[7].z -= sizePlayer.x / 2.0f;

			//�f�o�C�X�̃|�C���^
			LPDIRECT3DDEVICE9 pDevice;
			//�f�o�C�X�̎擾
			pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

			D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;						//�e�̃}�g���b�N�X

			//8���_�̐ݒ�
			for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++)
			{
				D3DXMatrixIdentity(&m_vtxMtxWorld[nCntVtx]);		//���[���h�}�g���b�N�X�̏�����

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, m_vtxRot[nCntVtx].y, m_vtxRot[nCntVtx].x, m_vtxRot[nCntVtx].z);
				D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, m_vtxPos[nCntVtx].x, m_vtxPos[nCntVtx].y, m_vtxPos[nCntVtx].z);
				D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxTrans);

				mtxParent = m_mtxWorld;

				//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxParent);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &m_vtxMtxWorld[nCntVtx]);
			}

			//���_�̃x�N�g�����o��
			vecVtx[0] = D3DXVECTOR3(m_vtxMtxWorld[3]._41 - m_vtxMtxWorld[2]._41, 0.0f, m_vtxMtxWorld[3]._43 - m_vtxMtxWorld[2]._43);
			vecVtx[1] = D3DXVECTOR3(m_vtxMtxWorld[7]._41 - m_vtxMtxWorld[3]._41, 0.0f, m_vtxMtxWorld[7]._43 - m_vtxMtxWorld[3]._43);
			vecVtx[2] = D3DXVECTOR3(m_vtxMtxWorld[6]._41 - m_vtxMtxWorld[7]._41, 0.0f, m_vtxMtxWorld[6]._43 - m_vtxMtxWorld[7]._43);
			vecVtx[3] = D3DXVECTOR3(m_vtxMtxWorld[2]._41 - m_vtxMtxWorld[6]._41, 0.0f, m_vtxMtxWorld[2]._43 - m_vtxMtxWorld[6]._43);

			//�ォ��̓����蔻��p���_�̃x�N�g�����o��
			topVtxVec[0] = D3DXVECTOR3(m_vtxMtxWorld[1]._41 - m_vtxMtxWorld[0]._41, 0.0f, m_vtxMtxWorld[1]._43 - m_vtxMtxWorld[0]._43);
			topVtxVec[1] = D3DXVECTOR3(m_vtxMtxWorld[3]._41 - m_vtxMtxWorld[1]._41, 0.0f, m_vtxMtxWorld[3]._43 - m_vtxMtxWorld[1]._43);
			topVtxVec[2] = D3DXVECTOR3(m_vtxMtxWorld[2]._41 - m_vtxMtxWorld[3]._41, 0.0f, m_vtxMtxWorld[2]._43 - m_vtxMtxWorld[3]._43);
			topVtxVec[3] = D3DXVECTOR3(m_vtxMtxWorld[0]._41 - m_vtxMtxWorld[2]._41, 0.0f, m_vtxMtxWorld[0]._43 - m_vtxMtxWorld[2]._43);

			//�ΏۂƂ̃x�N�g�����o��
			vecObj[0] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[2]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[2]._43);
			vecObj[1] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[3]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[3]._43);
			vecObj[2] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[7]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[7]._43);
			vecObj[3] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[6]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[6]._43);

			//�ォ��̓����蔻��p�ΏۂƂ̃x�N�g�����o��
			topVecObj[0] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[0]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[0]._43);
			topVecObj[1] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[1]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[1]._43);
			topVecObj[2] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[3]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[3]._43);
			topVecObj[3] = D3DXVECTOR3(posPlayer.x - m_vtxMtxWorld[2]._41, 0.0f, posPlayer.z - m_vtxMtxWorld[2]._43);

			//�Ώۂ�1�t���[���O�̃x�N�g�����o��
			vecObjOld[0] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[2]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[2]._43);
			vecObjOld[1] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[3]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[3]._43);
			vecObjOld[2] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[7]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[7]._43);
			vecObjOld[3] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[6]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[6]._43);

			//�ォ��̓����蔻��p�Ώۂ�1�t���[���O�̃x�N�g�����o��
			topVecObjOld[0] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[0]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[0]._43);
			topVecObjOld[1] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[1]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[1]._43);
			topVecObjOld[2] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[3]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[3]._43);
			topVecObjOld[3] = D3DXVECTOR3(posOldPlayer.x - m_vtxMtxWorld[2]._41, 0.0f, posOldPlayer.z - m_vtxMtxWorld[2]._43);

			//�O�ς̌v�Z
			fVecNorObj[0] = (vecVtx[0].x * vecObj[0].z) - (vecObj[0].x * vecVtx[0].z);
			fVecNorObj[1] = (vecVtx[1].x * vecObj[1].z) - (vecObj[1].x * vecVtx[1].z);
			fVecNorObj[2] = (vecVtx[2].x * vecObj[2].z) - (vecObj[2].x * vecVtx[2].z);
			fVecNorObj[3] = (vecVtx[3].x * vecObj[3].z) - (vecObj[3].x * vecVtx[3].z);

			//�ォ��̓����蔻��p�O�ς̌v�Z
			fTopVecNorObj[0] = (topVtxVec[0].x * topVecObj[0].z) - (topVecObj[0].x * topVtxVec[0].z);
			fTopVecNorObj[1] = (topVtxVec[1].x * topVecObj[1].z) - (topVecObj[1].x * topVtxVec[1].z);
			fTopVecNorObj[2] = (topVtxVec[2].x * topVecObj[2].z) - (topVecObj[2].x * topVtxVec[2].z);
			fTopVecNorObj[3] = (topVtxVec[3].x * topVecObj[3].z) - (topVecObj[3].x * topVtxVec[3].z);

			//1�t���[���O�̊O�ς̌v�Z
			fVecNorObjOld[0] = (vecVtx[0].x * vecObjOld[0].z) - (vecObjOld[0].x * vecVtx[0].z);
			fVecNorObjOld[1] = (vecVtx[1].x * vecObjOld[1].z) - (vecObjOld[1].x * vecVtx[1].z);
			fVecNorObjOld[2] = (vecVtx[2].x * vecObjOld[2].z) - (vecObjOld[2].x * vecVtx[2].z);
			fVecNorObjOld[3] = (vecVtx[3].x * vecObjOld[3].z) - (vecObjOld[3].x * vecVtx[3].z);

			//�ォ��̓����蔻��p1�t���[���O�̊O�ς̌v�Z
			fTopVecNorObjOld[0] = (topVtxVec[0].x * topVecObjOld[0].z) - (topVecObjOld[0].x * topVtxVec[0].z);
			fTopVecNorObjOld[1] = (topVtxVec[1].x * topVecObjOld[1].z) - (topVecObjOld[1].x * topVtxVec[1].z);
			fTopVecNorObjOld[2] = (topVtxVec[2].x * topVecObjOld[2].z) - (topVecObjOld[2].x * topVtxVec[2].z);
			fTopVecNorObjOld[3] = (topVtxVec[3].x * topVecObjOld[3].z) - (topVecObjOld[3].x * topVtxVec[3].z);

			//�ǂ̕ǂɂԂ����Ă��邩
			if (fVecNorObjOld[0] >= 0.0f && fVecNorObj[0] < 0.0f)
			{
				//�ʃx�N�g�������߂邽�߂̒��_�x�N�g���̎Z�o
				vecNorVtx[0] = D3DXVECTOR3(m_vtxMtxWorld[1]._41 - m_vtxMtxWorld[3]._41,
										m_vtxMtxWorld[1]._42 - m_vtxMtxWorld[3]._42,
										m_vtxMtxWorld[1]._43 - m_vtxMtxWorld[3]._43);
				vecNorVtx[1] = D3DXVECTOR3(m_vtxMtxWorld[2]._41 - m_vtxMtxWorld[3]._41,
										m_vtxMtxWorld[2]._42 - m_vtxMtxWorld[3]._42,
										m_vtxMtxWorld[2]._43 - m_vtxMtxWorld[3]._43);
			}
			else if (fVecNorObjOld[1] >= 0.0f && fVecNorObj[1] < 0.0f)
			{
				//�ʃx�N�g�������߂邽�߂̒��_�x�N�g���̎Z�o
				vecNorVtx[0] = D3DXVECTOR3(m_vtxMtxWorld[5]._41 - m_vtxMtxWorld[7]._41,
										m_vtxMtxWorld[5]._42 - m_vtxMtxWorld[7]._42,
										m_vtxMtxWorld[5]._43 - m_vtxMtxWorld[7]._43);
				vecNorVtx[1] = D3DXVECTOR3(m_vtxMtxWorld[3]._41 - m_vtxMtxWorld[7]._41,
										m_vtxMtxWorld[3]._42 - m_vtxMtxWorld[7]._42,
										m_vtxMtxWorld[3]._43 - m_vtxMtxWorld[7]._43);
			}
			else if (fVecNorObjOld[2] >= 0.0f && fVecNorObj[2] < 0.0f)
			{
				//�ʃx�N�g�������߂邽�߂̒��_�x�N�g���̎Z�o
				vecNorVtx[0] = D3DXVECTOR3(m_vtxMtxWorld[4]._41 - m_vtxMtxWorld[6]._41,
										m_vtxMtxWorld[4]._42 - m_vtxMtxWorld[6]._42,
										m_vtxMtxWorld[4]._43 - m_vtxMtxWorld[6]._43);
				vecNorVtx[1] = D3DXVECTOR3(m_vtxMtxWorld[7]._41 - m_vtxMtxWorld[6]._41,
										m_vtxMtxWorld[7]._42 - m_vtxMtxWorld[6]._42,
										m_vtxMtxWorld[7]._43 - m_vtxMtxWorld[6]._43);
			}
			else if (fVecNorObjOld[3] >= 0.0f && fVecNorObj[3] < 0.0f)
			{
				//�ʃx�N�g�������߂邽�߂̒��_�x�N�g���̎Z�o
				vecNorVtx[0] = D3DXVECTOR3(m_vtxMtxWorld[0]._41 - m_vtxMtxWorld[2]._41,
										m_vtxMtxWorld[0]._42 - m_vtxMtxWorld[2]._42,
										m_vtxMtxWorld[0]._43 - m_vtxMtxWorld[2]._43);
				vecNorVtx[1] = D3DXVECTOR3(m_vtxMtxWorld[6]._41 - m_vtxMtxWorld[2]._41,
										m_vtxMtxWorld[6]._42 - m_vtxMtxWorld[2]._42,
										m_vtxMtxWorld[6]._43 - m_vtxMtxWorld[2]._43);
			}
			

			//���̑傫���ɖ߂�
			m_vtxPos[0].z -= sizePlayer.x / 2.0f;
			m_vtxPos[1].z -= sizePlayer.x / 2.0f;
			m_vtxPos[2].z -= sizePlayer.x / 2.0f;
			m_vtxPos[3].z -= sizePlayer.x / 2.0f;
			m_vtxPos[4].z += sizePlayer.x / 2.0f;
			m_vtxPos[5].z += sizePlayer.x / 2.0f;
			m_vtxPos[6].z += sizePlayer.x / 2.0f;
			m_vtxPos[7].z += sizePlayer.x / 2.0f;
			m_vtxPos[0].x += sizePlayer.x / 2.0f;
			m_vtxPos[1].x -= sizePlayer.x / 2.0f;
			m_vtxPos[2].x += sizePlayer.x / 2.0f;
			m_vtxPos[3].x -= sizePlayer.x / 2.0f;
			m_vtxPos[4].x += sizePlayer.x / 2.0f;
			m_vtxPos[5].x -= sizePlayer.x / 2.0f;
			m_vtxPos[6].x += sizePlayer.x / 2.0f;
			m_vtxPos[7].x -= sizePlayer.x / 2.0f;

			//�@���x�N�g�������߂�
			D3DXVec3Cross(&nor, &vecNorVtx[0], &vecNorVtx[1]);
			D3DXVec3Normalize(&nor, &nor);			//���K������(�x�N�g���̑傫����1�ɂ���)

			//���[�u�x�N�g�������߂�
			moveVec = D3DXVECTOR3(posPlayer.x - posOldPlayer.x, posPlayer.y - posOldPlayer.y, posPlayer.z - posOldPlayer.z);

			//���[�u�x�N�g���Ɩ@���̓��ς����߂�
			fInVec = (-moveVec.x * nor.x) + (-moveVec.y * nor.y) + (-moveVec.z * nor.z);

			//�@���̕����ɓ��ϕ��L�΂����x�N�g�������߂�
			norInVec = D3DXVECTOR3(nor.x * fInVec, nor.y * fInVec, nor.z * fInVec);

			//�Ώۂ������߂��ʒu�̃x�N�g�������߂�
			posPlayerVec = D3DXVECTOR3(nor.x * sizePlayer.x / 2.0f, nor.y * sizePlayer.x / 2.0f, nor.z * sizePlayer.x / 2.0f);

			//�����蔻��
			if (((fVecNorObj[0] < 0.0f && fVecNorObj[1] < 0.0f && fVecNorObj[2] < 0.0f && fVecNorObj[3] < 0.0f) &&
				(fVecNorObjOld[0] >= 0.0f || fVecNorObjOld[1] >= 0.0f || fVecNorObjOld[2] >= 0.0f || fVecNorObjOld[3] >= 0.0f)))
			{
				//�Ώۂ̉��o������߂�
				posFinPlayer.x = (moveVec.x + norInVec.x);
				posFinPlayer.y = (moveVec.y + norInVec.y);
				posFinPlayer.z = (moveVec.z + norInVec.z);

				//�������Ă�
				posPlayer.x = posOldPlayer.x;
				posPlayer.z = posOldPlayer.z;
				posPlayer.x += posFinPlayer.x;
				posPlayer.z += posFinPlayer.z;

				//�ʒu��ݒ�
				//pPlayer->SetPos(posPlayer);
			}
		}
	}
}

//================================================
//���f���̈ʒu�ݒ菈��
//================================================
void CModel::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//================================================
//���f���̈ʒu�擾����
//================================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

//================================================
//���f���̒��_�ʒu�擾����
//================================================
D3DXVECTOR3 CModel::GetVtxPos(const int &nCntVtx)
{
	return m_vtxPos[nCntVtx];
}

//================================================
//���f���̒��_�ʒu�ݒ菈��
//================================================
void CModel::SetVtxPos(const int & nCntVtx, const D3DXVECTOR3 &pos)
{
	m_vtxPos[nCntVtx] = pos;
}

//================================================
//���f���̌����ݒ菈��
//================================================
void CModel::SetRot(const D3DXVECTOR3 &rot)
{
	m_rot = rot;
}

//================================================
//���f���̌����擾����
//================================================
D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//================================================
//���[���h�}�g���b�N�X�擾����
//================================================
D3DXMATRIX *CModel::GetVtxMtxWorld(void)
{
	return &m_vtxMtxWorld[0];
}

//================================================
//���[���h�}�g���b�N�X�ݒ菈��
//================================================
void CModel::SetVtxMtxWorld(const D3DXVECTOR3 &vtxPos, const int &nCntVtx)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//8���_�̐ݒ�
	D3DXMatrixIdentity(&m_vtxMtxWorld[nCntVtx]);		//���[���h�}�g���b�N�X�̏�����

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_vtxRot[nCntVtx].y, m_vtxRot[nCntVtx].x, m_vtxRot[nCntVtx].z);
	D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, vtxPos.x, vtxPos.y, vtxPos.z);
	D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxTrans);

	D3DXMATRIX mtxParent;		//�e�̃}�g���b�N�X
	mtxParent = m_mtxWorld;

	//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_vtxMtxWorld[nCntVtx]);
}

//================================================
//���[���h�}�g���b�N�X�ݒ菈��
//================================================
void CModel::SetMtxWorldPos(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;						//�e�̃}�g���b�N�X

	D3DXMatrixIdentity(&m_mtxWorld);			//���[���h�}�g���b�N�X�̏�����

												//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�p�[�c�̐e�̃}�g���b�N�X�̐ݒ�
	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMtx();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//�Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//8���_�̐ݒ�
	for (int nCntVtx = 0; nCntVtx < MODEL_VTX; nCntVtx++)
	{
		D3DXMatrixIdentity(&m_vtxMtxWorld[nCntVtx]);		//���[���h�}�g���b�N�X�̏�����

															//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_vtxRot[nCntVtx].y, m_vtxRot[nCntVtx].x, m_vtxRot[nCntVtx].z);
		D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_vtxPos[nCntVtx].x, m_vtxPos[nCntVtx].y, m_vtxPos[nCntVtx].z);
		D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxTrans);

		//�e�̃}�g���b�N�X
		mtxParent = m_mtxWorld;

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_vtxMtxWorld[nCntVtx]);
	}
}
