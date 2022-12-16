//=============================================================================
//
// �N���W�b�g�̊G���� [credit_picture.cpp]
// Author : ��������
//
//=============================================================================
#include "credit_picture.h"
#include "object2D.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CREDIT_PICTURE_FRAME_SIZE		(1.8f)		//�t���[���̃T�C�Y
#define CREDIT_PICTURE_OBJECT_NUM		(2)			//��������I�u�W�F�N�g�̐�

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CCreditPicture::CCreditPicture()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRot = 0.0f;
	m_fMoveY = 0.0f;
	m_texType = CTexture::TEXTURE_TYPE::NONE;
	m_pPicture = nullptr;
	m_pFrame = nullptr;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCreditPicture::~CCreditPicture()
{
	
}

//=============================================================================
// ��������
//=============================================================================
CCreditPicture* CCreditPicture::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale, const float fRot, const CTexture::TEXTURE_TYPE texType,
	                                   const float fMoveY) {
	CCreditPicture* pCreditPicture;
	pCreditPicture = new CCreditPicture();
	if (pCreditPicture == nullptr) return nullptr;

	pCreditPicture->m_pos = pos;
	pCreditPicture->m_scale = scale;
	pCreditPicture->m_fRot = fRot;
	pCreditPicture->m_texType = texType;
	pCreditPicture->m_fMoveY = fMoveY;
	pCreditPicture->Init();

	return pCreditPicture;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCreditPicture::Init(void) {
	
	//�ϐ�������
	
	//�t���[���̐���
	m_pFrame = CObject2D::Create(m_pos, CTexture::TEXTURE_TYPE::CREDIT_PICTURE_FRAME,
		                         SCREEN_WIDTH * CREDIT_PICTURE_FRAME_SIZE * m_scale.x, SCREEN_HEIGHT * CREDIT_PICTURE_FRAME_SIZE * m_scale.y);
	m_pFrame->SetAngle(3.14f);

	//�G�̐���
	m_pPicture = CObject2D::Create(m_pos, m_texType, SCREEN_WIDTH * m_scale.x, SCREEN_HEIGHT * m_scale.y);
	m_pPicture->SetAngle(3.14f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCreditPicture::Uninit(void) {

	//�j��
	if (m_pPicture != nullptr)
	{
		m_pPicture->Uninit();
		m_pPicture = nullptr;
	}
	if (m_pFrame != nullptr)
	{
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCreditPicture::Update(void) {
	//��������
	int nCntUninit = 0;
	//�ړ�����
	if (Move(m_pPicture)) nCntUninit++;
	if (Move(m_pFrame)) nCntUninit++;

	//�S����������N���X�j��
	if (nCntUninit >= CREDIT_PICTURE_OBJECT_NUM) Uninit();
}

//=============================================================================
//�ړ�����
//=============================================================================
bool CCreditPicture::Move(CObject2D * &pObject2D)
{
	if (pObject2D == nullptr) return true;

	//�ʒu�ƃT�C�Y�擾
	D3DXVECTOR3 pos = pObject2D->GetPos();
	D3DXVECTOR3 size = pObject2D->GetSize();

	//�ړ�
	pos.y += m_fMoveY;

	//�ʒu���f
	pObject2D->SetPos(pos);

	//���S�Ɍ����Ȃ��Ȃ�����
	if (pos.y <= 0.0f - size.x / 2.0f)
	{
		//����
		pObject2D->Uninit();
		pObject2D = nullptr;
		return true;
	}
	return false;
}
