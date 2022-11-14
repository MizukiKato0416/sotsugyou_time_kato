//=============================================================================
//
// ���ɐi�ރ{�^��UI���� [next_button.cpp]
// Author : ��������
//
//=============================================================================
#include "next_button.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CNextButton::CNextButton()
{
	m_nFrameCounter = 0;
	m_nCounter = 0;
	m_fDecAlpha = 0.0f;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNextButton::~CNextButton()
{

}

//=============================================================================
// ��������
//=============================================================================
CNextButton* CNextButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const CTexture::TEXTURE_TYPE texType,
		                         const int nCounter, const float fDecAlpha) {
	CNextButton* pNextButton;
	pNextButton = new CNextButton();
	if (pNextButton == nullptr) return nullptr;

	pNextButton->m_nCounter = nCounter;
	pNextButton->m_fDecAlpha = fDecAlpha;
	pNextButton->Init();
	pNextButton->SetPos(pos);
	pNextButton->SetSize(size);
	pNextButton->SetTexType(texType);

	return pNextButton;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CNextButton::Init(void) {

	//�ϐ�������
	m_nFrameCounter = 0;

	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CNextButton::Uninit(void) {
	CObject2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CNextButton::Update(void) {

	//�J���[�擾
	D3DXCOLOR col = GetColor();

	if (col.a <= 0.0f)
	{
		m_nFrameCounter++;
		if (m_nFrameCounter <= m_nCounter) return;

		//�w�肳�ꂽ�t���[���ɂȂ�����
		m_nFrameCounter = 0;
		//������悤�ɂ���
		col.a = 1.0f;
		
	}
	else
	{
		//��������
		col.a -= m_fDecAlpha;
	}
	//�J���[�ݒ�
	SetColor(col);

	CObject2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CNextButton::Draw(void) {
	CObject2D::Draw();
}