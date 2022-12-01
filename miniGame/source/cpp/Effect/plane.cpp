//---------------------------
// Author:�����G��
// ����(plane.cpp)
//---------------------------
#include "manager.h"
#include "renderer.h"

#include "plane.h"
//�}�N����`
#define TEXTURE_FILENAME_3D "data/TEXT/load_EffectTexture.txt"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CPlane::m_pTexture[MAX_TEXTURE] = {};
int CPlane::m_nMaxTex = 0;

CPlane::CPlane() : CScene3D::CScene3D()
{

}

CPlane::~CPlane()
{

}

//����������
HRESULT CPlane::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex)
{
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//if (pManager == nullptr) return;	//null�̏ꍇ�I��
										//�����_���[�̎擾
	CRenderer* pRenderer = pManager->GetRenderer();
	//if (pRenderer == nullptr) return;	//null�̏ꍇ�I��
										//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//if (pDevice == nullptr) return;		//null�̏ꍇ�I��

	m_pos = pos;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	m_TexNum = Tex;

	m_size = size;

	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, -size.z);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(Tex.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, Tex.y);
	pVtx[3].tex = D3DXVECTOR2(Tex.x, Tex.y);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//�I������
void CPlane::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene3D::Uninit();
}

//�X�V����
void CPlane::Update()
{

}

//�`�揈��
void CPlane::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld; //�v�Z�p�}�g���b�N�X
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;	//null�̏ꍇ�I��
	//�����_���[�̎擾
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;	//null�̏ꍇ�I��
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;		//null�̏ꍇ�I��

	//�G�t�F�N�g��Z�e�N�X�`���ɏ������܂Ȃ�
	if (pRenderer->GetDrawZTex()) return;

	//�����ȕ�����`�悵�Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	if (m_nSynthenic == 0)
	{
		//���Z�����֌W
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (m_nSynthenic == 1)
	{
		//���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (m_nSynthenic == 2)
	{
		//�����g�p����
	}
	//����ȊO�̐��l�͉��Z������
	else
	{
		//���Z�����֌W
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	//�V�F�[�_�Ƀ}�g���b�N�X��ݒ�
	pRenderer->SetEffectMatrixWorld(mtxWorld);
	SetMatrix(mtxWorld);

	//�V�F�[�_�Ƀe�N�X�`����ݒ�
	if (m_nTexType >= 0 && m_nTexType < MAX_TEXTURE) {
		pRenderer->SetEffectTexture(m_pTexture[m_nTexType]);
	}
	else {
		pRenderer->SetEffectTexture(nullptr);
	}

	//���_��`��ݒ�
	pRenderer->SetVtxDecl3D();

	//���f�����ݒ肵���}�e���A���̉e�����󂯂Ȃ��悤�Ƀ}�e���A���̐ݒ�
	pRenderer->SetEffectMaterialDiffuse(m_Color);
	pRenderer->SetEffectMaterialEmissive(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	pRenderer->SetEffectMaterialSpecular(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	pRenderer->SetEffectMaterialPower(2.0f);
	//�֊s�̔����F�̐ݒ�
	pRenderer->SetEffectGlow(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 0.0f);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	DWORD dwPassFlag = PASS_3D | PASS_TEXTURE;

	//�p�X�̊J�n
	pRenderer->BeginPassEffect(dwPassFlag);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //�J�n����n�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��

	pRenderer->EndPassEffect();//�G�t�F�N�g�I��

	//�f�t�H���g�ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//�ʏ퍇���ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CPlane::UninitTexture()
{
	//�e�N�X�`���j��
	for (int nCnt = 0; nCnt < m_nMaxTex; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �T�C�Y�Z�b�g
//=============================================================================
void CPlane::SetSize(D3DXVECTOR3 size)
{
	//m_size = size;
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, -size.z);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`������
//=============================================================================
void CPlane::CreateTextureFile()
{
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;	//null�̏ꍇ�I��
										//�����_���[�̎擾
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;	//null�̏ꍇ�I��
										//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;		//null�̏ꍇ�I��

	//�t�@�C���ǂݍ���
	char aFile[256];
	FILE *pFile = fopen(TEXTURE_FILENAME_3D, "r");

	int nCntTex = 0;

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);

			if (strcmp(&aFile[0], "NUM_TEXTURE") == 0)	//NUM_TEXTURE�̕�����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nMaxTex);//�g�p����e�N�X�`������ǂݍ���
			}

			if (strcmp(&aFile[0], "TEXTURE_FILENAME") == 0) //TEXTURE_FILENAME�̕�����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				D3DXCreateTextureFromFile(pDevice, &aFile[0], &m_pTexture[nCntTex]);
				nCntTex++;
			}

			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPT�̕��������������
			{
				break;
			}

		}
	}
	fclose(pFile);
}

//=============================================================================
//�T�C�Y�ύX
//=============================================================================
void CPlane::ChangeSize(D3DXVECTOR3 size)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

				   //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y	, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y	, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y	, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y	, -size.z);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
//���ʃG�t�F�N�g
//=============================================================================
void CPlane::SetPosField(D3DXVECTOR3 pos, D3DXVECTOR3 Size, float Rotate, float Rotate2)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x / 2 + (cosf(Rotate2)) * Size.x, Size.y, pos.z / 2 + (sinf(Rotate))* Size.x);
	pVtx[1].pos = D3DXVECTOR3(pos.x / 2 + (sinf(Rotate))  * Size.x, Size.y, pos.z / 2 - (cosf(Rotate2))* Size.x);
	pVtx[2].pos = D3DXVECTOR3(pos.x / 2 - (sinf(Rotate))  * Size.x, Size.y, pos.z / 2 + (cosf(Rotate2))* Size.x);
	pVtx[3].pos = D3DXVECTOR3(pos.x / 2 - (cosf(Rotate2)) * Size.x, Size.y, pos.z / 2 - (sinf(Rotate))* Size.x);


	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}

//=============================================================================
//�T�C�Y�ύX
//=============================================================================
void CPlane::BillboardSize(float size)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size, size, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size, size, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size, -size, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size, -size, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
//�e�N�X�`���ړ�
//=============================================================================
void CPlane::TexturMove(D3DXVECTOR2 MoveTex)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^
	m_TexMove += MoveTex;

	if (m_TexMove.x >= 1.0f)
	{
		m_TexMove.x -= 1.0f;
	}
	else if (m_TexMove.x < 0.0f)
	{
		m_TexMove.x += 1.0f;
	}

	if (m_TexMove.y >= 1.0f)
	{
		m_TexMove.y -= 1.0f;
	}
	else if (m_TexMove.y < 0.0f)
	{
		m_TexMove.y += 1.0f;
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(m_TexMove.x				, m_TexMove.y);
	pVtx[1].tex = D3DXVECTOR2(m_TexNum.x + m_TexMove.x	, m_TexMove.y);
	pVtx[2].tex = D3DXVECTOR2(m_TexMove.x				, m_TexNum.y + m_TexMove.y);
	pVtx[3].tex = D3DXVECTOR2(m_TexNum.x + m_TexMove.x	, m_TexNum.y + m_TexMove.y);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
//�e�N�X�`���p�^�[��
//=============================================================================
void CPlane::SetTexAnim(D3DXVECTOR2 TexPattern, D3DXVECTOR2 TexAnimSize)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

	m_nSplit = TexPattern;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + m_TexMove.x					, m_TexNum.y + m_nSplit.y * TexAnimSize.y + m_TexMove.y);
	pVtx[1].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + TexAnimSize.x + m_TexMove.x	, m_TexNum.y + m_nSplit.y * TexAnimSize.y + m_TexMove.y);
	pVtx[2].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + m_TexMove.x					, m_TexNum.y + m_nSplit.y *  + TexAnimSize.y + TexAnimSize.y + m_TexMove.y);
	pVtx[3].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + TexAnimSize.x + m_TexMove.x	, m_TexNum.y + m_nSplit.y *  +TexAnimSize.y + TexAnimSize.y + m_TexMove.y);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}

//=============================================================================
//���W
//=============================================================================
void CPlane::SetPosBill(D3DXVECTOR3 pos, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3, D3DXVECTOR3 pos4)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = pos;
	pVtx[1].pos = pos2;
	pVtx[2].pos = pos3;
	pVtx[3].pos = pos4;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}