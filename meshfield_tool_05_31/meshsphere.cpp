//================================================
//���b�V���X�t�B�A����
//Author:��������
//================================================
#include "renderer.h"
#include "meshsphere.h"
#include "object3D.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMeshSphere::CMeshSphere(CObject::PRIORITY Priority):CObject(Priority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLine = 0;
	m_nVertical = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CMeshSphere::~CMeshSphere()
{

}

//================================================
//����������
//================================================
HRESULT CMeshSphere::Init(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�ʒu�E�T�C�Y�ݒ菈��
	CObject::SetPos(m_pos);
	CObject::SetSize(m_size);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((m_nVertical + 1) * (m_nLine + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);


	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nNum = 0;
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{
		for (int nLine = 0; nLine < m_nLine + 1; nLine++, nNum++)
		{
			//���_���W
			pVtx[nNum].pos = D3DXVECTOR3(cosf((D3DX_PI * 2.0f / m_nLine) * nLine) * (sinf(((D3DX_PI * 2.0f / m_nLine) * nVertical) + ((D3DX_PI * 2.0f / m_nLine) * m_nVertical)) * (m_size.x / 2.0f)) ,
											m_pos.y + sinf((D3DX_PI * 2.0f / m_nLine) * nVertical) * (m_size.x / 2.0f),
											sinf((D3DX_PI * 2.0f / m_nLine) * nLine) * (sinf(((D3DX_PI * 2.0f / m_nLine) * nVertical) + ((D3DX_PI * 2.0f / m_nLine) * m_nVertical)) * (m_size.x / 2.0f)));
			//�J���[
			pVtx[nNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//�e�N�X�`��
			pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f / m_nLine * nLine), 0.0f + (1.0f / m_nVertical * nVertical));
		}
	}

	//�@���x�N�g�������߂�
	D3DXVECTOR3 vec[2];		//�O�όv�Z�p�x�N�g��
	D3DXVECTOR3 vecNor;		//�@���x�N�g��

	//�O�όv�Z�̂��߂̃x�N�g�������߂�
	vec[0] = D3DXVECTOR3(pVtx[1].pos.x - pVtx[0].pos.x, pVtx[1].pos.y - pVtx[0].pos.y, pVtx[1].pos.z - pVtx[0].pos.z);
	vec[1] = D3DXVECTOR3(pVtx[m_nLine + 1].pos.x - pVtx[0].pos.x, pVtx[m_nLine + 1].pos.y - pVtx[0].pos.y, pVtx[m_nLine + 1].pos.z - pVtx[0].pos.z);

	//�O�όv�Z
	D3DXVec3Cross(&vecNor, &vec[0], &vec[1]);

	//�x�N�g���𐳋K������(�x�N�g���̑傫����1�ɂ���)
	D3DXVec3Normalize(&vecNor, &vecNor);

	//�@��
	nNum = 0;
	for (int nVertical = 0; nVertical < m_nVertical + 1; nVertical++)
	{
		for (int nLine = 0; nLine < m_nLine + 1; nLine++, nNum++)
		{
			pVtx[nNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((m_nVertical - 1) * (m_nLine + 3) + (m_nLine + 1) * (m_nVertical + 1)),
								D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, nullptr);

	WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^
					//�C���f�b�N�X�o�b�t�@�����b�N���ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt1 = 0; nCnt1 < m_nVertical; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 < m_nLine + 1; nCnt2++)
		{
			//�ԍ��f�[�^�̐ݒ�
			pIdx[(nCnt2 * 2) + 0 + (m_nLine + 2) * 2 * nCnt1] = static_cast<WORD>((m_nLine + 1) + nCnt2 + (m_nLine + 1) * nCnt1);
			pIdx[(nCnt2 * 2) + 1 + (m_nLine + 2) * 2 * nCnt1] = static_cast<WORD>(0				+ nCnt2 + (m_nLine + 1) * nCnt1);
		}
	}
	for (int nCnt3 = 0; nCnt3 < m_nVertical - 1; nCnt3++)
	{
		pIdx[((m_nLine + 1) * 2 + 0) * (nCnt3 + 1) + (2 * nCnt3)] = static_cast<WORD>(m_nLine + (m_nLine + 1) * nCnt3);
		pIdx[((m_nLine + 1) * 2 + 1) * (nCnt3 + 1) + (1 * nCnt3)] = static_cast<WORD>(m_nLine * 2 + 2 + (m_nLine + 1) * nCnt3);
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();


	return S_OK;
}

//================================================
//�I������
//================================================
void CMeshSphere::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CMeshSphere::Update(void)
{
	m_rot.y += 0.0001f;
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
}

//================================================
//�`�揈��
//================================================
void CMeshSphere::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	//�v�Z�p�}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);		//���[���h�}�g���b�N�X�̏�����

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	pDevice->SetFVF(FVF_VERTEX_3D);					//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, m_pTexture);				//�e�N�X�`���̐ݒ�

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
									0,
									0,
									((m_nLine + 1) * (m_nVertical + 1)),				//���_�̐�
									0,													//�J�n���钸�_�̃C���f�b�N�X
									2 * m_nLine * m_nVertical + (m_nVertical * 4) - 4);	//�`�悷��v���~�e�B�u��

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//================================================
//��������
//================================================
CMeshSphere* CMeshSphere::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const int &nLine, const int &nVertical)
{
	//�C���X�^���X�̐���
	CMeshSphere *pMeshSphere = nullptr;
	if (pMeshSphere == nullptr)
	{
		pMeshSphere = new CMeshSphere;
		if (pMeshSphere != nullptr)
		{
			//�ϐ�������
			pMeshSphere->m_rot = rot;
			pMeshSphere->m_nLine = nLine;
			pMeshSphere->m_nVertical = nVertical;
			pMeshSphere->m_pos = pos;
			pMeshSphere->m_size = size;
			//����������
			pMeshSphere->Init();
		}
	}
	return pMeshSphere;
}

//================================================
//�e�N�X�`�����蓖�ď���
//================================================
void CMeshSphere::BindTexture(const LPDIRECT3DTEXTURE9 &pTexture)
{
	m_pTexture = pTexture;
}
