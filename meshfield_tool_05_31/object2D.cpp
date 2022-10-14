//================================================
//2D�|���S������
//Author:��������
//================================================
#include "renderer.h"
#include "object2D.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CObject2D::CObject2D(CObject::PRIORITY Priority):CObject(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_OriginType = ORIGIN_TYPE::CENTER;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CObject2D::~CObject2D()
{

}

//================================================
//����������
//================================================
HRESULT CObject2D::Init(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	

	//�ʒu�E�T�C�Y�ݒ菈��
	CObject::SetPos(m_pos);
	CObject::SetSize(m_size);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (m_OriginType)
	{
	case ORIGIN_TYPE::CENTER:
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
		break;
	case ORIGIN_TYPE::LEFT:
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y / 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y / 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y / 2.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y / 2.0f, 0.0f);
		break;
	default:
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
		break;
	}
	
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

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
void CObject2D::Uninit(void)
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
void CObject2D::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CObject2D::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, m_pTexture);	//�e�N�X�`���̐ݒ�

												//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�`����J�n���钸�_�̃C���f�b�N�X
		2);					//�`�悷��v���~�e�B�u��
}

//================================================
//��������
//================================================
CObject2D* CObject2D::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const int &nPriolity)
{
	//�C���X�^���X�̐���
	CObject2D *pObject2D = nullptr;
	if (pObject2D == nullptr)
	{
		pObject2D = new CObject2D(static_cast<CObject::PRIORITY>(nPriolity));
		if (pObject2D != nullptr)
		{
			pObject2D->m_pos = pos;
			pObject2D->m_size = size;
			pObject2D->Init();
		}
	}
	return pObject2D;
}

//================================================
//�ʒu�擾����
//================================================
D3DXVECTOR3 CObject2D::GetPos(void)
{
	return m_pos;
}

//================================================
//�ʒu�ݒ菈��
//================================================
void CObject2D::SetPos(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	m_pos = pos;
	m_size = size;

	//�ʒu�E�T�C�Y�ݒ菈��
	CObject::SetPos(m_pos);
	CObject::SetSize(m_size);

	VERTEX_2D *pVtx;	// ���_���
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (m_OriginType)
	{
	case ORIGIN_TYPE::CENTER:
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
		break;
	case ORIGIN_TYPE::LEFT:
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y / 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y / 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y / 2.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y / 2.0f, 0.0f);
		break;
	default:
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�ʒu�ݒ菈��
//================================================
void CObject2D::SetPos(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const float &fRot)
{
	m_pos = pos;
	m_size = size;

	//�ʒu�E�T�C�Y�ݒ菈��
	CObject::SetPos(m_pos);
	CObject::SetSize(m_size);

	//�p�x�����߂�
	float fTanR = atan2f(m_size.y / 2.0f, m_size.x / 2.0f);
	//���a�����߂�
	float fCircleR = sqrtf((float)pow(m_size.x / 2.0f, 2.0f) + (float)pow(m_size.y / 2.0f, 2.0f));

	VERTEX_2D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fCircleR * cosf(fTanR - fRot), m_pos.y - fCircleR * sinf(fTanR - fRot), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fCircleR * cosf(fTanR + fRot), m_pos.y - fCircleR * sinf(fTanR + fRot), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fCircleR * cosf(fTanR + fRot), m_pos.y + fCircleR * sinf(fTanR + fRot), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fCircleR * cosf(fTanR - fRot), m_pos.y + fCircleR * sinf(fTanR - fRot), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�e�N�X�`���ݒ菈��
//================================================
void CObject2D::SetTex(const int &nPattern, const int &nMaxPattern)
{
	VERTEX_2D *pVtx;	// ���_���
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
void CObject2D::SetTex(const float &fMoveTexU, const float &fMoveTexV)
{
	VERTEX_2D *pVtx;	// ���_���
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
void CObject2D::SetCol(const D3DCOLORVALUE &col)
{
	VERTEX_2D *pVtx;	// ���_���
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
void CObject2D::SetCol(const D3DXCOLOR &col)
{
	VERTEX_2D *pVtx;	// ���_���
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
D3DXCOLOR CObject2D::GetCol(void)
{
	VERTEX_2D *pVtx;	// ���_���
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCOLOR col;
	col = pVtx[0].col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return col;
}

//================================================
//4���_�ݒ菈��
//================================================
void CObject2D::SetVtx(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &vtx0, const D3DXVECTOR3 &vtx1, const D3DXVECTOR3 &vtx2, const D3DXVECTOR3 &vtx3)
{
	m_pos = pos;

	VERTEX_2D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = vtx0;
	pVtx[1].pos = vtx1;
	pVtx[2].pos = vtx2;
	pVtx[3].pos = vtx3;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�e�N�X�`�����蓖�ď���
//================================================
void CObject2D::BindTexture(const LPDIRECT3DTEXTURE9 &pTexture)
{
	m_pTexture = pTexture;
}
