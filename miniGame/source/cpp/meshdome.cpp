//=============================================================================
//
// ���b�V���h�[�� [meshdome.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "meshdome.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CMeshdome::CMeshdome() : m_nNumXZ(0), m_nNumY(0)
{

}

//=============================================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//=============================================================================
CMeshdome::CMeshdome(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumXZ, int nNumY, float fRadius, bool bOut) : m_nNumXZ(nNumXZ), m_nNumY(nNumY)
{
	SetPos(pos);
	SetRot(rot);
	m_fRadius = fRadius;
	m_bOut = bOut;
	SetNumVtx((nNumXZ + 1) * (nNumY + 1));	//(XZ�����̃|���S���� + 1) * (Y�����̃|���S���� + 1)
	SetNumIdx((2 * (nNumXZ + 1)) * nNumY + (nNumY - 1) * 2);	//XZ�����Ŏg�����_�� * Y�����̃|���S���� + �k�ރ|���S���̐�
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshdome::~CMeshdome()
{

}

//=============================================================================
// ���b�V���h�[���̐�������
//=============================================================================
CMeshdome* CMeshdome::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumXZ, int nNumY, float fRadius, bool bOut, CTexture::TEXTURE_TYPE typeTex) {
	CMeshdome* pMeshdome;
	pMeshdome = new CMeshdome(pos, rot, nNumXZ, nNumY, fRadius, bOut);
	if (pMeshdome == nullptr) return nullptr;

	pMeshdome->SetTexType(typeTex);
	pMeshdome->Init();

	return pMeshdome;
}

//=============================================================================
// ���b�V���h�[���̏���������
//=============================================================================
HRESULT CMeshdome::Init(void) {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return S_OK;
	//�����_���[�̎擾
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return S_OK;
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return S_OK;

	//���_�o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9* ppVtxBuff = GetPtrVtxBuff();

	int nNumVtx = GetNumVtx();	//���_���̎擾

	//���_�o�b�t�@�̐���
	if (*ppVtxBuff == nullptr) {
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumVtx,
			D3DUSAGE_WRITEONLY,
			0,
			D3DPOOL_MANAGED,
			ppVtxBuff,
			nullptr);
	}

	//���_�o�b�t�@�̐ݒ�
	SetVtxBuff();

	//�C���f�b�N�X�o�b�t�@�̂̎擾
	LPDIRECT3DINDEXBUFFER9* ppIdxBuff = GetPtrIdxBuff();

	int nNumIdx = GetNumIdx();	//�C���f�b�N�X���̎擾

	//�C���f�b�N�X�o�b�t�@�̐���
	if (*ppIdxBuff == nullptr) {
		pDevice->CreateIndexBuffer(sizeof(WORD) * nNumIdx,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			ppIdxBuff,
			nullptr);
	}
	//�C���f�b�N�X�o�b�t�@�̐ݒ�
	if (*ppIdxBuff != nullptr) {
		WORD *pIdx;	//�C���f�b�N�X���ւ̃|�C���^
		//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
		(*ppIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);
		//�ԍ��f�[�^�ݒ�
		for (int nCntIdx = 0; nCntIdx < (m_nNumXZ + 1) * 2 * m_nNumY + (m_nNumY - 1) * 2; nCntIdx++) {
			if (nCntIdx == (m_nNumXZ + 2) * 2 * (1 + nCntIdx / ((m_nNumXZ + 2) * 2)) - 2) {
				pIdx[nCntIdx] = pIdx[nCntIdx - 1];
			}
			else if (nCntIdx == (m_nNumXZ + 2) * 2 * (1 + nCntIdx / ((m_nNumXZ + 2) * 2)) - 1) {
				pIdx[nCntIdx] = (m_nNumXZ + 1) * (2 + nCntIdx / ((m_nNumXZ + 1) * 2 + 2));
			}
			else {
				pIdx[nCntIdx] = (m_nNumXZ + 1 + nCntIdx / 2) - (nCntIdx / ((m_nNumXZ + 2) * 2)) - ((m_nNumXZ + 1)*(nCntIdx % 2));//���@�k�ށ@�� �k�ނɏC��
			}
		}
		//�C���f�b�N�X�o�b�t�@���A�����b�N����
		(*ppIdxBuff)->Unlock();
	}

	CObject3D::Init();

	return S_OK;
}

//=============================================================================
// ���b�V���h�[���̏I������
//=============================================================================
void CMeshdome::Uninit(void) {
	CObject3D::Uninit();
}

//=============================================================================
// ���b�V���h�[���̍X�V����
//=============================================================================
void CMeshdome::Update(void) {
	//���_�o�b�t�@�̍X�V
	SetVtxBuffPos();

	CObject3D::Update();
}

//=============================================================================
// ���b�V���h�[���̕`�揈��
//=============================================================================
void CMeshdome::Draw(void) {
	//�`��
	CObject3D::Draw();
}

//=============================================================================
// ���_�o�b�t�@�̏����X�V
//=============================================================================
void CMeshdome::SetVtxBuff(void) {
	//���_�o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9* ppVtxBuff = GetPtrVtxBuff();

	//���_�o�b�t�@���Ȃ���ΏI��
	if (*ppVtxBuff == nullptr) return;

	int nNumVtx = GetNumVtx();	//���_���̎擾

	VERTEX_3D *pVtx;	//���_�o�b�t�@�̃|�C���^
	//���_�o�b�t�@�����b�N
	(*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
	//���_�̐ݒ�
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++) {
		float fRotXZ = ((nCntVtx % (m_nNumXZ + 1)) / (float)m_nNumXZ) * (D3DX_PI * 2);	//XZ���ʂ��猩���p�x
		float fRotXY = ((nCntVtx / (m_nNumXZ + 1)) / (float)m_nNumY) * (D3DX_PI / 2.0f);//XY���ʂ��猩���p�x

		//�h�[���̌������O�����̏ꍇ
		if (m_bOut == true) {
			fRotXY *= -1.0f;
			fRotXZ *= -1.0f;
		}

		//���_���W�̐ݒ�
		pVtx[nCntVtx].pos = D3DXVECTOR3(sinf(fRotXZ) * (sinf(fRotXY) * m_fRadius),
			cosf(fRotXY) * m_fRadius,
			cosf(fRotXZ) * (sinf(fRotXY) * m_fRadius));

		//�@���x�N�g���̐ݒ�
		D3DXVECTOR3 vecNor = D3DXVECTOR3(pVtx[nCntVtx].pos.x, 0.0f, pVtx[nCntVtx].pos.z);	//�@�������̃x�N�g��
		D3DXVec3Normalize(&vecNor, &vecNor);	//�x�N�g���̐��K��
		pVtx[nCntVtx].nor = vecNor;	//���K�������x�N�g����ݒ�

		//�h�[�����������̏ꍇ
		if (!m_bOut) {
			//�@�����t�ɐݒ�
			pVtx[nCntVtx].nor.x *= -1;
			pVtx[nCntVtx].nor.y *= -1;
			pVtx[nCntVtx].nor.z *= -1;
		}

		pVtx[nCntVtx].tex = D3DXVECTOR2((float)(nCntVtx % (m_nNumXZ + 1)) / m_nNumXZ, (float)(nCntVtx / (m_nNumXZ + 1)) / m_nNumY);	//���b�V���S�̂ŉ摜�P����
		//pVtx[nCntVtx].tex = D3DXVECTOR2((float)(nCntVtx % (m_nNumXZ + 1)), (float)(nCntVtx / (m_nNumXZ + 1)));	//���b�V�����Ƃɉ摜�ꖇ��
	}
	//���_�o�b�t�@���A�����b�N����
	(*ppVtxBuff)->Unlock();
}

//=============================================================================
// ���_�o�b�t�@�̈ʒu�����X�V
//=============================================================================
void CMeshdome::SetVtxBuffPos(void) {
	//���_�o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9* ppVtxBuff = GetPtrVtxBuff();

	//���_�o�b�t�@���Ȃ���ΏI��
	if (*ppVtxBuff == nullptr) return;

	int nNumVtx = GetNumVtx();	//���_���̎擾

	VERTEX_3D *pVtx;	//���_�o�b�t�@�̃|�C���^
	//���_�o�b�t�@�����b�N
	(*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
	//���_�̐ݒ�
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++) {
		float fRotXZ = ((nCntVtx % (m_nNumXZ + 1)) / (float)m_nNumXZ) * (D3DX_PI * 2);	//XZ���ʂ��猩���p�x
		float fRotXY = ((nCntVtx / (m_nNumXZ + 1)) / (float)m_nNumY) * (D3DX_PI / 2.0f);//XY���ʂ��猩���p�x

		//�h�[���̌������O�����̏ꍇ
		if (m_bOut == true) {
			fRotXY *= -1.0f;
			fRotXZ *= -1.0f;
		}

		//���_���W�̐ݒ�
		pVtx[nCntVtx].pos = D3DXVECTOR3(sinf(fRotXZ) * (sinf(fRotXY) * m_fRadius),
			cosf(fRotXY) * m_fRadius,
			cosf(fRotXZ) * (sinf(fRotXY) * m_fRadius));

		pVtx[nCntVtx].tex = D3DXVECTOR2((float)(nCntVtx % (m_nNumXZ + 1)) / m_nNumXZ, (float)(nCntVtx / (m_nNumXZ + 1)) / m_nNumY);	//���b�V���S�̂ŉ摜�P����
		//pVtx[nCntVtx].tex = D3DXVECTOR2((float)(nCntVtx % (m_nNumXZ + 1)), (float)(nCntVtx / (m_nNumXZ + 1)));	//���b�V�����Ƃɉ摜�ꖇ��
	}
	//���_�o�b�t�@���A�����b�N����
	(*ppVtxBuff)->Unlock();
}