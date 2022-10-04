//================================================
//�p�[�e�B�N������
//Author:��������
//================================================
#include "effect3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//================================================
//�}�N����`
//================================================
#define EFFECT3D_DRAW_DIFFERE		(1000)	//�G�t�F�N�g�̕`�悷��͈�


//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CEffect3D::CEffect3D(CObject::PRIORITY Priority) : CBillboard(Priority)
{
	m_type = EFFECT3D_TYPE::NONE;
	m_pControl = nullptr;
	m_bAlphaBlendSubtraction = false;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CEffect3D::~CEffect3D()
{

}

//================================================
//����������
//================================================
HRESULT CEffect3D::Init(void)
{
	//�ϐ�������
	m_bAlphaBlendSubtraction = false;

	CBillboard::Init();

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::EFFECT_3D);

	return S_OK;
}

//================================================
//�I������
//================================================
void CEffect3D::Uninit(void)
{
	CBillboard::Uninit();
	if (m_pControl != nullptr)
	{
		//m_pControl->Uninit();
		m_pControl = nullptr;
	}
}

//================================================
//�X�V����
//================================================
void CEffect3D::Update(void)
{
	if (m_pControl != nullptr)
	{
		//�R���g���[���N���X�X�V�������Ăяo��
		//m_pControl->Update(this);

		if (m_pControl != nullptr)
		{
			//�ʒu�Ɉړ��ʂ����蓖�Ă�
			//m_pos += m_pControl->GetMove();
			//�ʒu�̐ݒ�
			CObject::SetPos(m_pos);
		}
	}
}

//================================================
//�`�揈��
//================================================
void CEffect3D::Draw(void)
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

	//���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

	//Z�o�b�t�@�̏�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CBillboard::Draw();

	//Z�e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�A���t�@�e�X�g���ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

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
CEffect3D* CEffect3D::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXCOLOR &col, const EFFECT3D_TYPE &type)
{
	//�C���X�^���X�̐���
	CEffect3D *pEffect3D = nullptr;
	if (pEffect3D == nullptr)
	{
		pEffect3D = new CEffect3D();
		if (pEffect3D != nullptr)
		{
			pEffect3D->m_type = type;
			pEffect3D->m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pEffect3D->m_pos = pos;
			pEffect3D->m_size = size;
			pEffect3D->Init();

			//��ނɂ���Ăǂ̃R���g���[���N���X�̔h���N���X�����蓖�Ă邩�����߂�
			switch (pEffect3D->m_type)
			{
			case EFFECT3D_TYPE::NONE:
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("effect000.jpg");
				break;
			default:
				pEffect3D->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("effect000.jpg");
				break;
			}
			pEffect3D->SetCol(col);
		}
	}
	return pEffect3D;
}
