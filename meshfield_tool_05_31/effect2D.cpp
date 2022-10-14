//================================================
//�p�[�e�B�N������
//Author:��������
//================================================
#include "effect2D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//================================================
//�}�N����`
//================================================


//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CEffect2D::CEffect2D(CObject::PRIORITY Priority) : CObject2D(Priority)
{
	m_type = EFFECT2D_TYPE::NONE;
	m_bAlphaBlendSubtraction = false;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CEffect2D::~CEffect2D()
{

}

//================================================
//����������
//================================================
HRESULT CEffect2D::Init(void)
{
	//�ϐ�������
	m_bAlphaBlendSubtraction = false;

	CObject2D::Init();

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::EFFECT_2D);

	return S_OK;
}

//================================================
//�I������
//================================================
void CEffect2D::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CEffect2D::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CEffect2D::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	if (m_bAlphaBlendSubtraction == false)
	{
		//���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else
	{
		//���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	CObject2D::Draw();

	if (m_bAlphaBlendSubtraction == false)
	{
		//a�u�����f�B���O��ʏ�ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else
	{
		//���Z��������ʏ�̍����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//================================================
//��������
//================================================
CEffect2D* CEffect2D::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXCOLOR &col, const EFFECT2D_TYPE &type)
{
	//�C���X�^���X�̐���
	CEffect2D *pEffect2D = nullptr;
	if (pEffect2D == nullptr)
	{
		pEffect2D = new CEffect2D();
		if (pEffect2D != nullptr)
		{
			pEffect2D->m_type = type;
			pEffect2D->Init();
			pEffect2D->SetCol(col);
			pEffect2D->SetPos(pos, size);
		}
	}
	return pEffect2D;
}
