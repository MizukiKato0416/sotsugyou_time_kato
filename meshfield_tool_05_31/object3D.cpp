//================================================
//3D�|���S������
//Author:��������
//================================================
#include "renderer.h"
#include "object3D.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CObject3D::CObject3D(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCntVtx = 0; nCntVtx < VERTEX_3D_NUM; nCntVtx++)
	{
		m_vtxPos[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vtxRot[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bCulling = false;
	m_bAlphaBlend = false;
	m_bAlphaTest = false;
	m_bLighting = false;
	SetObjType(CObject::OBJTYPE::POLYGON_3D);
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CObject3D::~CObject3D()
{

}

//================================================
//����������
//================================================
HRESULT CObject3D::Init(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�ϐ�������
	m_bCulling = true;
	m_bAlphaBlend = false;
	m_bAlphaTest = false;
	m_bLighting = true;

	//�ʒu�E�T�C�Y�ݒ菈��
	CObject::SetPos(m_pos);
	CObject::SetSize(m_size);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(- m_size.x / 2.0f, + m_size.y / 2.0f, + m_size.z / 2.0f);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x / 2.0f, + m_size.y / 2.0f, + m_size.z / 2.0f);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x / 2.0f, - m_size.y / 2.0f, - m_size.z / 2.0f);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x / 2.0f, - m_size.y / 2.0f, - m_size.z / 2.0f);

	for (int nCntVtx = 0; nCntVtx < VERTEX_3D_NUM; nCntVtx++)
	{
		m_vtxPos[nCntVtx] = pVtx[nCntVtx].pos;
		m_vtxRot[nCntVtx] = m_vtxRot[nCntVtx];
	}

	//�@���x�N�g�������߂�
	D3DXVECTOR3 vec[2];		//�O�όv�Z�p�x�N�g��
	D3DXVECTOR3 vecNor;		//�@���x�N�g��

	//�O�όv�Z�̂��߂̃x�N�g�������߂�
	vec[0] = D3DXVECTOR3(pVtx[1].pos.x - pVtx[0].pos.x, pVtx[1].pos.y - pVtx[0].pos.y, pVtx[1].pos.z - pVtx[0].pos.z);
	vec[1] = D3DXVECTOR3(pVtx[2].pos.x - pVtx[0].pos.x, pVtx[2].pos.y - pVtx[0].pos.y, pVtx[2].pos.z - pVtx[0].pos.z);

	//�O�όv�Z
	D3DXVec3Cross(&vecNor, &vec[0], &vec[1]);

	//�x�N�g���𐳋K������(�x�N�g���̑傫����1�ɂ���)
	D3DXVec3Normalize(&vecNor, &vecNor);

	//�@��
	pVtx[0].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);
	pVtx[1].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);
	pVtx[2].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);
	pVtx[3].nor = D3DXVECTOR3(vecNor.x, vecNor.y, vecNor.z);

	//�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I������
//================================================
void CObject3D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CObject3D::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CObject3D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

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

	//�J�����O���s��Ȃ��ݒ�Ȃ�
	if (m_bCulling == false)
	{
		// �J�����O���s��Ȃ�
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	//���Z�������s���ݒ�Ȃ�
	if (m_bAlphaBlend == true)
	{
		//�A���t�@�e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

		//���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		//Z�o�b�t�@�̏�������
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	//���e�X�g���s���ݒ�Ȃ�
	if (m_bAlphaTest == true)
	{
		//�A���t�@�e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
	}

	//���C�e�B���O���s��Ȃ��ݒ�Ȃ�
	if (m_bAlphaTest == true)
	{
		//���C�e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);					//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, m_pTexture);				//�e�N�X�`���̐ݒ�

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,											//�J�n���钸�_�̃C���f�b�N�X
		2);											//�`�悷��v���~�e�B�u��

	//���C�e�B���O���s��Ȃ��ݒ�Ȃ�
	if (m_bAlphaTest == true)
	{
		//���C�e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	//���e�X�g���s���ݒ�Ȃ�
	if (m_bAlphaTest == true)
	{
		//�A���t�@�e�X�g���ɖ߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
	}

	//���Z�������s���ݒ�Ȃ�
	if (m_bAlphaBlend == true)
	{
		//Z�e�X�g�����ɖ߂�
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//a�u�����f�B���O��ʏ�ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//�A���t�@�e�X�g���ɖ߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
	}

	//�J�����O���s��Ȃ��ݒ�Ȃ�
	if (m_bCulling == false)
	{
		// �J�����O���s��
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}

	//4���_�̐ݒ�
	for (int nCntVtx = 0; nCntVtx < VERTEX_3D_NUM; nCntVtx++)
	{
		D3DXMatrixIdentity(&m_vtxMtxWorld[nCntVtx]);		//���[���h�}�g���b�N�X�̏�����

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_vtxRot[nCntVtx].y, m_vtxRot[nCntVtx].x, m_vtxRot[nCntVtx].z);
		D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_vtxPos[nCntVtx].x, m_vtxPos[nCntVtx].y, m_vtxPos[nCntVtx].z);
		D3DXMatrixMultiply(&m_vtxMtxWorld[nCntVtx], &m_vtxMtxWorld[nCntVtx], &mtxTrans);

		D3DXMATRIX mtxParent;		//�e�̃}�g���b�N�X
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
CObject3D* CObject3D::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot)
{
	//�C���X�^���X�̐���
	CObject3D *pScene3D = nullptr;
	if (pScene3D == nullptr)
	{
		pScene3D = new CObject3D();
		if (pScene3D != nullptr)
		{
			pScene3D->m_pos = pos;
			pScene3D->m_size = size;
			pScene3D->m_rot = rot;
			pScene3D->Init();
		}
	}
	return pScene3D;
}

//================================================
//�ʒu�擾����
//================================================
D3DXVECTOR3 CObject3D::GetPos(void)
{
	return m_pos;
}

//================================================
//�ʒu�ݒ菈��
//================================================
void CObject3D::SetPos(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	m_pos = pos;
	m_size = size;

	//�ʒu�E�T�C�Y�ݒ菈��
	CObject::SetPos(m_pos);
	CObject::SetSize(m_size);

	VERTEX_3D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3( - m_size.x / 2.0f, + m_size.y / 2.0f,  + m_size.z / 2.0f);
	pVtx[1].pos = D3DXVECTOR3( + m_size.x / 2.0f, + m_size.y / 2.0f,  + m_size.z / 2.0f);
	pVtx[2].pos = D3DXVECTOR3( - m_size.x / 2.0f, - m_size.y / 2.0f,  - m_size.z / 2.0f);
	pVtx[3].pos = D3DXVECTOR3( + m_size.x / 2.0f, - m_size.y / 2.0f,  - m_size.z / 2.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�e�N�X�`���ݒ菈��
//================================================
void CObject3D::SetTex(const int &nPattern, const int &nMaxPattern)
{
	VERTEX_3D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((1.0f / nMaxPattern) * nPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / nMaxPattern) + (1.0f / nMaxPattern) * nPattern, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / nMaxPattern) * nPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / nMaxPattern) + (1.0f / nMaxPattern) * nPattern, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�e�N�X�`���ݒ菈��
//================================================
void CObject3D::SetTex(const float &fMoveTexU, const float &fMoveTexV)
{
	VERTEX_3D *pVtx;	// ���_���
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + fMoveTexU, 0.0f + fMoveTexV);
	pVtx[1].tex = D3DXVECTOR2(1.0f + fMoveTexU, 0.0f + fMoveTexV);
	pVtx[2].tex = D3DXVECTOR2(0.0f + fMoveTexU, 1.0f + fMoveTexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + fMoveTexU, 1.0f + fMoveTexV);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�J���[�ݒ菈��
//================================================
void CObject3D::SetCol(const D3DCOLORVALUE &col)
{
	VERTEX_3D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�J���[�ݒ菈��
//================================================
void CObject3D::SetCol(const D3DXCOLOR &col)
{
	VERTEX_3D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�J���[�擾����
//================================================
D3DXCOLOR CObject3D::GetCol(void)
{
	VERTEX_3D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCOLOR col;
	col = pVtx[0].col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return col;
}

//================================================
//�J�����O�ݒ菈��
//================================================
void CObject3D::SetCulling(const bool &bCulling)
{
	m_bCulling = bCulling;
}

//================================================
//���Z�����ݒ菈��
//================================================
void CObject3D::SetAlphaBlend(const bool &bAlphaBlend)
{
	m_bAlphaBlend = bAlphaBlend;
}

//================================================
//���e�X�g�ݒ菈��
//================================================
void CObject3D::SetAlphaTest(const bool &bAlphaTest)
{
	m_bAlphaTest = bAlphaTest;
}

//================================================
//���C�e�B���O�ݒ菈��
//================================================
void CObject3D::SetLighting(const bool &bLighting)
{
	m_bLighting = bLighting;
}

//================================================
//�e�N�X�`�����蓖�ď���
//================================================
void CObject3D::BindTexture(const LPDIRECT3DTEXTURE9 &pTexture)
{
	m_pTexture = pTexture;
}