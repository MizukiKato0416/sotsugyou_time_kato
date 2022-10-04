//================================================
//�t�F�[�h����
//Author:��������
//================================================
#include "fade.h"
#include "object.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CFade::CFade(CObject::PRIORITY Priority) :CObject2D(Priority)
{
	m_fade = FADE_NONE;								//�t�F�[�h�̏��
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�t�F�[�h�̐F
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CFade::~CFade()
{

}

//================================================
//����������
//================================================
HRESULT CFade::Init(void)
{
	m_fade = FADE_IN;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	CObject2D::Init();

	SetPos(m_pos, m_size);

	return S_OK;
}

//================================================
//�I������
//================================================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_color.a -= 0.05f;
			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_color.a += 0.05f;
			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;
				m_fade = FADE_IN;

				//���[�h�̐ݒ�
				CManager::SetMode(m_modeNext);
			}
		}
		CObject2D::SetCol(m_color);
	}
}

//================================================
//�`�揈��
//================================================
void CFade::Draw(void)
{
	CObject2D::Draw();
}

//================================================
//��������
//================================================
CFade *CFade::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const CManager::MODE &modeNext)
{
	//�C���X�^���X�̐���
	CFade *pFade = nullptr;
	if (pFade == nullptr)
	{
		pFade = new CFade;
		if (pFade != nullptr)
		{
			pFade->m_pos = pos;
			pFade->m_size = size;
			pFade->Init();
			pFade->m_fade = FADE_OUT;
			pFade->m_modeNext = modeNext;				//���̉��(���[�h)
			pFade->m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		}
	}

	return pFade;
}

//================================================
//�ݒ菈��
//================================================
void CFade::SetFade(const CManager::MODE &modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//================================================
//�擾����
//================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}