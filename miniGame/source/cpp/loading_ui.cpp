//=============================================================================
//
// ���[�hUI���� [loading_ui.cpp]
// Author : ��������
//
//=============================================================================
#include "loading_ui.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LOADING_UI_MAX_ANIM_X		(4)		//�A�j���[�V������X�ő�l
#define LOADING_UI_MAX_ANIM_Y		(1)		//�A�j���[�V������Y�ő�l
#define LOADING_UI_ANIM_COUNTER		(20)	//�A�j���[�V�����̑���

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CLoadingUi::CLoadingUi()
{
	m_nFrameCounter = 0;
	m_nAnimCounter = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLoadingUi::~CLoadingUi()
{

}

//=============================================================================
// ��������
//=============================================================================
CLoadingUi* CLoadingUi::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size) {
	CLoadingUi* pLoadingUi;
	pLoadingUi = new CLoadingUi();
	if (pLoadingUi == nullptr) return nullptr;

	pLoadingUi->SetPos(pos);
	pLoadingUi->SetSize(size);
	pLoadingUi->Init();

	return pLoadingUi;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLoadingUi::Init(void) {
	//�ϐ�������
	m_nFrameCounter = 0;
	m_nAnimCounter = 0;

	//�I�u�W�F�N�g�̏�����
	CObject2D::Init();

	//�v���C�I���e�B�̐ݒ�
	SetDrawPriority(CObject::DRAW_PRIORITY::LOADING);
	//�e�N�X�`���̐ݒ�
	SetTexType(CTexture::TEXTURE_TYPE::NOW_LOADING);
	//�e�N�X�`���̐ݒ�
	SetTexAnim(m_nAnimCounter, LOADING_UI_MAX_ANIM_X, LOADING_UI_MAX_ANIM_Y);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLoadingUi::Uninit(void) {
	//�I�u�W�F�N�g�̔j��
	CObject2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLoadingUi::Update(void) {
	//�t���[�����J�E���g
	m_nFrameCounter++;
	if (m_nFrameCounter > LOADING_UI_ANIM_COUNTER)
	{
		m_nFrameCounter = 0;
		//�A�j���[�V������i�߂�
		m_nAnimCounter++;
		//�Ō�܂ōs������ŏ��ɖ߂�
		if (m_nAnimCounter >= LOADING_UI_MAX_ANIM_X) m_nAnimCounter = 0;

		//�e�N�X�`���A�j���[�V�����̐ݒ�
		SetTexAnim(m_nAnimCounter, LOADING_UI_MAX_ANIM_X, LOADING_UI_MAX_ANIM_Y);
	}

	//�X�V����
	CObject2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLoadingUi::Draw(void) {
	//�`�揈��
	CObject2D::Draw();
}