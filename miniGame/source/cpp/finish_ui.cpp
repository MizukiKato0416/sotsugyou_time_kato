//=============================================================================
//
// �t�B�j�b�V��UI���� [finish.cpp]
// Author : ��������
//
//=============================================================================
#include "finish_ui.h"
#include "manager.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FINISH_UI_DEFAULT_SIZE		(D3DXVECTOR3(450.0f * 1.2f, 120.0f * 1.2f, 0.0f))											//UI�̃f�t�H���g�T�C�Y
#define FINISH_UI_INIT_SIZE			(D3DXVECTOR3(FINISH_UI_DEFAULT_SIZE.x * 3.0f, FINISH_UI_DEFAULT_SIZE.y * 3.0f, 0.0f))		//UI�̏����T�C�Y

#define FINISH_UI_DEC_SIZE			(0.93f)		//UI�̃T�C�Y���Z�l
#define FINISH_UI_ADD_SIZE			(1.01f)		//UI�̃T�C�Y���Z�l

#define FINISH_UI_INIT_COLOR		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))		//UI�̏����J���[
#define FINISH_UI_ADD_COLOR_ALPHA	(0.2f)									//UI�̃��l���Z��
#define FINISH_UI_DEC_COLOR_ALPHA	(0.015f)								//UI�̃��l���Z��

#define FINISH_UI_STATE_NONE_COUNT	(60)									//�������Ȃ���Ԃ̎���

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFinishUi::CFinishUi()
{
	m_state = STATE::DEC_SIZE;
	m_nFrameCounter = 0;
	m_nDelay = 0;
	m_nDelayCounter = 0;
	m_fMaxAlpha = 0.0f;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFinishUi::~CFinishUi()
{

}

//=============================================================================
// ��������
//=============================================================================
CFinishUi* CFinishUi::Create(const D3DXVECTOR3 pos, const int nDelay, const float fMaxAlpha) {
	CFinishUi* pFinishUi;
	pFinishUi = new CFinishUi();
	if (pFinishUi == nullptr) return nullptr;

	pFinishUi->m_nDelay = nDelay;
	pFinishUi->m_fMaxAlpha = fMaxAlpha;
	pFinishUi->SetPos(pos);
	pFinishUi->SetSize(FINISH_UI_INIT_SIZE);
	pFinishUi->Init();

	return pFinishUi;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFinishUi::Init(void) {
	
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//�����Đ�
	if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_TIME_UP);

	//�ϐ�������
	m_state = STATE::DEC_SIZE;
	m_nFrameCounter = 0;
	m_nDelayCounter = 0;

	//�e�N�X�`���̐ݒ�
	SetTexType(CTexture::TEXTURE_TYPE::FINISH);

	//�J���[�̐ݒ�
	SetColor(FINISH_UI_INIT_COLOR);

	//�I�u�W�F�N�g�̏�����
	CObject2D::Init();
	SetDrawPriority(CObject::DRAW_PRIORITY::FRONT);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFinishUi::Uninit(void) {
	//�I�u�W�F�N�g�̔j��
	CObject2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFinishUi::Update(void) {

	if (m_nDelayCounter < m_nDelay)
	{
		m_nDelayCounter++;
		return;
	}
	

	switch (m_state)
	{
	case CFinishUi::STATE::DEC_SIZE:
		//�T�C�Y���Z����
		StateDecSize();
		break;
	case CFinishUi::STATE::NONE:
		//�������Ȃ�����
		StateNone();
		break;
	case CFinishUi::STATE::ADD_SIZE:
		//�T�C�Y���Z����
		if (StateAddSize())
		{
			//����
			Uninit();
			return;
		}
		break;
	default:
		break;
	}

	//�X�V����
	CObject2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFinishUi::Draw(void) {
	//�`�揈��
	CObject2D::Draw();
}

//=============================================================================
//�T�C�Y���Z����
//=============================================================================
void CFinishUi::StateDecSize()
{
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();
	//����������
	size *= FINISH_UI_DEC_SIZE;
	if (size.x < FINISH_UI_DEFAULT_SIZE.x)
	{
		size.x = FINISH_UI_DEFAULT_SIZE.x;
	}
	if (size.y < FINISH_UI_DEFAULT_SIZE.y)
	{
		size.y = FINISH_UI_DEFAULT_SIZE.y;
	}
	//�T�C�Y�ݒ�
	SetSize(size);


	//�J���[�擾
	D3DXCOLOR col = GetColor();
	if (col.a < m_fMaxAlpha)
	{
		//�Z������
		col.a += FINISH_UI_ADD_COLOR_ALPHA;
		if (col.a > m_fMaxAlpha)
		{
			col.a = m_fMaxAlpha;
		}
		//�J���[�ݒ�
		SetColor(col);
	}


	//����̃T�C�Y�ɂȂ�����
	if (size.x <= FINISH_UI_DEFAULT_SIZE.x && size.y <= FINISH_UI_DEFAULT_SIZE.y)
	{
		//�������Ȃ���Ԃɂ���
		m_state = STATE::NONE;
	}
}

//=============================================================================
//�������Ȃ�����
//=============================================================================
void CFinishUi::StateNone()
{
	//�t���[���J�E���g�����Z
	m_nFrameCounter++;
	if (m_nFrameCounter > FINISH_UI_STATE_NONE_COUNT)
	{
		//�T�C�Y���Z��Ԃɂ���
		m_state = STATE::ADD_SIZE;
		//���Z�b�g
		m_nFrameCounter = 0;
	}
}

//=============================================================================
//�T�C�Y���Z����
//=============================================================================
bool CFinishUi::StateAddSize()
{
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();
	//�傫������
	size *= FINISH_UI_ADD_SIZE;
	//�T�C�Y�ݒ�
	SetSize(size);


	//�J���[�擾
	D3DXCOLOR col = GetColor();
	if (col.a > 0.0f)
	{
		//��������
		col.a -= FINISH_UI_DEC_COLOR_ALPHA;
		if (col.a < 0.0f)
		{
			col.a = 0.0f;
			//�J���[�ݒ�
			SetColor(col);
			return true;
		}
		//�J���[�ݒ�
		SetColor(col);
	}
	return false;
}