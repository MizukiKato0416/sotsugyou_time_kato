//=============================================================================
//
// �v���C���[�A�C�R������ [player_icon.cpp]
// Author : ��������
//
//=============================================================================
#include "player_icon.h"
#include "object2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_ICON_FRAME_SIZE			(D3DXVECTOR3(373.0f, 261.0f, 0.0f))		//�t���[���̑傫��
#define PLAYER_ICON_PLAYER_NUM_SIZE		(D3DXVECTOR3(201.0f, 181.0f, 0.0f))		//�v���C���[�ԍ��̑傫��

#define PLAYER_ICON_ADD_ALPHA			(0.09f)		//���l���Z��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObjectPlayerIcon::CObjectPlayerIcon()
{
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_texTypeFrame = CTexture::TEXTURE_TYPE::NONE;
	m_texTypePlayerNum = CTexture::TEXTURE_TYPE::NONE;
	m_pFrame = nullptr;
	m_pPlayerNum = nullptr;
	m_state = STATE::ADD_ALPHA;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectPlayerIcon::~CObjectPlayerIcon()
{
	
}

//=============================================================================
// ��������
//=============================================================================
CObjectPlayerIcon* CObjectPlayerIcon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale,
	                             const CTexture::TEXTURE_TYPE texTypeFrame, const CTexture::TEXTURE_TYPE texTypePlayerNum) {
	CObjectPlayerIcon* pPlayerIcon;
	pPlayerIcon = new CObjectPlayerIcon();
	if (pPlayerIcon == nullptr) return nullptr;

	pPlayerIcon->m_texTypeFrame = texTypeFrame;
	pPlayerIcon->m_texTypePlayerNum = texTypePlayerNum;
	pPlayerIcon->m_scale = scale;
	pPlayerIcon->m_pos = pos;
	pPlayerIcon->Init();

	return pPlayerIcon;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CObjectPlayerIcon::Init(void) {
	//�����o���̐���
	m_pFrame = CObject2D::Create(m_pos, m_texTypeFrame, PLAYER_ICON_FRAME_SIZE.x * m_scale.x, PLAYER_ICON_FRAME_SIZE.y * m_scale.y);
	//�J���[�ݒ�
	m_pFrame->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	//������ƉE�ɂ��炷��
	m_pos.x += 10.0f;
	//�v���C���[�ԍ��̐���
	m_pPlayerNum = CObject2D::Create(m_pos, m_texTypePlayerNum, PLAYER_ICON_PLAYER_NUM_SIZE.x * m_scale.x, PLAYER_ICON_PLAYER_NUM_SIZE.y * m_scale.y);
	//�J���[�ݒ�
	m_pPlayerNum->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObjectPlayerIcon::Uninit(void) {

	if (m_pFrame != nullptr)
	{
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pPlayerNum != nullptr)
	{
		m_pPlayerNum->Uninit();
		m_pPlayerNum = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObjectPlayerIcon::Update(void) {
	
	switch (m_state)
	{
	case CObjectPlayerIcon::STATE::ADD_ALPHA:
		//���l���Z����
		StateAddAlpha();
		break;
	case CObjectPlayerIcon::STATE::NONE:
		//�������Ȃ�����
		StateNone();
		break;
	case CObjectPlayerIcon::STATE::DEC_ALPHA:
		//���l���Z����
		StateDecAlpha();
		break;
	default:
		break;
	}
}

//=============================================================================
//���l���Z����
//=============================================================================
void CObjectPlayerIcon::StateAddAlpha(){

	int nCntClear = 0;

	//��������Ă�����
	if (m_pFrame != nullptr)
	{
		//�J���[�擾
		D3DXCOLOR col = m_pFrame->GetColor();

		if (col.a < 1.0f)
		{
			//�Z������
			col.a += PLAYER_ICON_ADD_ALPHA;
			if (col.a > 1.0f)
			{
				col.a = 1.0f;
				nCntClear++;
			}
			//�F�ݒ�
			m_pFrame->SetColor(col);
		}
	}

	//��������Ă�����
	if (m_pPlayerNum != nullptr)
	{
		//�J���[�擾
		D3DXCOLOR col = m_pPlayerNum->GetColor();

		if (col.a < 1.0f)
		{
			//�Z������
			col.a += PLAYER_ICON_ADD_ALPHA;
			if (col.a > 1.0f)
			{
				col.a = 1.0f;
				nCntClear++;
			}
			//�F�ݒ�
			m_pPlayerNum->SetColor(col);
		}
	}

	if (nCntClear == 2)
	{
		m_state = STATE::NONE;
	}
}

//=============================================================================
//�������Ȃ�����
//=============================================================================
void CObjectPlayerIcon::StateNone(){

	//��������Ă�����
	if (m_pFrame != nullptr)
	{
		//�J���[�擾
		D3DXCOLOR col = m_pFrame->GetColor();

		if (col.a != 1.0f)
		{
			col.a = 1.0f;
			//�F�ݒ�
			m_pFrame->SetColor(col);
		}
	}

	//��������Ă�����
	if (m_pPlayerNum != nullptr)
	{
		//�J���[�擾
		D3DXCOLOR col = m_pPlayerNum->GetColor();

		if (col.a != 1.0f)
		{
			col.a = 1.0f;
			//�F�ݒ�
			m_pPlayerNum->SetColor(col);
		}
	}
}

//=============================================================================
//���l���Z����
//=============================================================================
void CObjectPlayerIcon::StateDecAlpha(){
	//��������Ă�����
	if (m_pFrame != nullptr)
	{
		//�J���[�擾
		D3DXCOLOR col = m_pFrame->GetColor();

		if (col.a > 0.0f)
		{
			//��������
			col.a -= PLAYER_ICON_ADD_ALPHA;
			//�F�ݒ�
			m_pFrame->SetColor(col);
			if (col.a < 0.0f)
			{
				col.a = 0.0f;
				//����
				m_pFrame->Uninit();
				m_pFrame = nullptr;
			}
		}
	}

	//��������Ă�����
	if (m_pPlayerNum != nullptr)
	{
		//�J���[�擾
		D3DXCOLOR col = m_pPlayerNum->GetColor();

		if (col.a > 0.0f)
		{
			//��������
			col.a -= PLAYER_ICON_ADD_ALPHA;
			//�F�ݒ�
			m_pPlayerNum->SetColor(col);
			if (col.a < 0.0f)
			{
				col.a = 0.0f;
				//����
				m_pPlayerNum->Uninit();
				m_pPlayerNum = nullptr;
			}
		}
	}
}