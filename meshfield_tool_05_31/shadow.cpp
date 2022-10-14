//================================================
//�e�̏���
//Author:��������
//================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "floor.h"

//================================================
//�}�N����`
//================================================
#define SHADOW_ADD_SIZE					(4.0f)		//�n�ʂƂ̋����̉����̈ꑝ�₷��
#define SHADOW_ADD_ALPHA				(200.0f)	//�n�ʂƂ̋����̉����̈ꔖ�����邩

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CShadow::CShadow(CObject::PRIORITY Priority) :CObject3D(Priority)
{
	m_pObject = nullptr;
	m_bDraw = false;
	m_size = { 0.0f, 0.0f, 0.0f };
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CShadow::~CShadow()
{

}

//================================================
//����������
//================================================
HRESULT CShadow::Init(void)
{
	//�ϐ�������
	m_bDraw = true;

	CObject3D::Init();

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::SHADOW);
	//���C�e�B���O�𖳌��ɂ���
	SetLighting(false);
	//���e�X�g��L���ɂ���
	SetAlphaTest(true);

	return S_OK;
}

//================================================
//�I������
//================================================
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}

//================================================
//�X�V����
//================================================
void CShadow::Update(void)
{
	//�ʒu�ƃT�C�Y���擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	//�J���[���擾
	D3DXCOLOR col = GetCol();

	//�Ώۂ̃I�u�W�F�N�g�̈ʒu���擾
	D3DXVECTOR3 posObj = m_pObject->GetPos();

	//�����̍������߂�
	float fDiffer = posObj.y - pos.y;

	//���ɂ���Ĕ�����ς���
	col.a = 1.0f - fDiffer / SHADOW_ADD_ALPHA;

	//�����Ȃ��Ȃ�����
	if (col.a <= 0.0f)
	{
		//�`�悳��Ă����ԂȂ�
		if (m_bDraw == true)
		{
			//�`�悵�Ȃ��悤�ɂ���
			m_bDraw = false;
		}
	}
	else
	{
		//�`�悳��Ă��Ȃ���ԂȂ�
		if (m_bDraw == false)
		{
			//�`�悷��
			m_bDraw = true;
		}
	}

	//���ɂ���đ傫����ς���
	size.x = m_size.x + fDiffer / SHADOW_ADD_SIZE;
	size.z = m_size.z + fDiffer / SHADOW_ADD_SIZE;

	//�ʒu�A�T�C�Y�A�J���[��ݒ�
	SetPos(D3DXVECTOR3(posObj.x, 0.01f, posObj.z), size);
	SetCol(col);

	//�����蔻��
	Collision();
}

//================================================
//�`�揈��
//================================================
void CShadow::Draw(void)
{
	//�`�悷��Ȃ�
	if (m_bDraw == true)
	{
		//�f�o�C�X�̃|�C���^
		LPDIRECT3DDEVICE9 pDevice;
		//�f�o�C�X�̎擾
		pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

		//���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		CObject3D::Draw();

		//���Z��������ʏ�̍����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//================================================
//��������
//================================================
CShadow* CShadow::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, CObject *pObject)
{
	//�C���X�^���X�̐���
	CShadow *pShadow = nullptr;
	if (pShadow == nullptr)
	{
		pShadow = new CShadow();
		if (pShadow != nullptr)
		{
			pShadow->m_pos = pos;
			pShadow->m_size = size;
			pShadow->m_pObject = pObject;
			pShadow->Init();
			pShadow->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("effect000.jpg"));
		}
	}
	return pShadow;
}

//================================================
//�����蔻��
//================================================
void CShadow::Collision(void)
{
	//���Ƃ̓����蔻��
	if (CFloor::CollisionShadow(this) == false)
	{
		//�`�悳��Ȃ��悤�ɂ���
		m_bDraw = false;
	}
}