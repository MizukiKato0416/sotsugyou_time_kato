//=============================================================================
//
// �J�E���g�_�E��UI���� [count_down_ui.cpp]
// Author : ��������
//
//=============================================================================
#include "count_down_ui.h"
#include "object2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define COUNT_DOWN_UI_NUMBER_SIZE_X			(188.0f)			//�i���o�[�̃T�C�YX
#define COUNT_DOWN_UI_NUMBER_SIZE_Y			(226.0f)			//�i���o�[�̃T�C�YY
#define COUNT_DOWN_UI_START_SIZE_X			(434.0f * 0.8f)		//START�̃T�C�YX
#define COUNT_DOWN_UI_START_SIZE_Y			(127.0f * 0.8f)		//START�̃T�C�YY

#define COUNT_DOWN_UI_NUMBER_SIZE_ADD_X		(COUNT_DOWN_UI_NUMBER_SIZE_X / 38.0f)		//�i���o�[�T�C�Y���Z�l
#define COUNT_DOWN_UI_NUMBER_SIZE_ADD_Y		(COUNT_DOWN_UI_NUMBER_SIZE_Y / 38.0f)		//�i���o�[�T�C�Y���Z�l
#define COUNT_DOWN_UI_START_SIZE_ADD		(1.02f)										//�X�^�[�g�T�C�Y���Z�l
#define COUNT_DOWN_UI_START_ADD_ALPHA		(0.1f)										//�X�^�[�g���l���Z�l
#define COUNT_DOWN_UI_START_DEC_ALPHA		(0.1f)										//�X�^�[�g���l���Z�l

#define COUNT_DOWN_UI_NEXT_UI_COUNT					(60)		//����UI�ɂ���܂ł̃J�E���g
#define COUNT_DOWN_UI_NUMBER_SIZE_DEC_COUNT			(10)		//�i���o�[UI������������^�C�~���O�̃J�E���g 
#define COUNT_DOWN_UI_NUMBER_SIZE_DEC_STOP_COUNT	(20)		//�i���o�[UI������������̂���߂�^�C�~���O�̃J�E���g 
#define COUNT_DOWN_UI_START_ALPHA_DEC_COUNT			(30)		//�X�^�[�gUI�𔖂�����^�C�~���O�̃J�E���g 

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CCountDownUi::CCountDownUi()
{
	m_pCountUi = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_bStart = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCountDownUi::~CCountDownUi()
{

}

//=============================================================================
// ��������
//=============================================================================
CCountDownUi* CCountDownUi::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale) {
	CCountDownUi* pCountDownUi;
	pCountDownUi = new CCountDownUi();
	if (pCountDownUi == nullptr) return nullptr;

	pCountDownUi->m_pos = pos;
	pCountDownUi->m_scale = scale;
	pCountDownUi->SetPos(pos);
	pCountDownUi->Init();

	return pCountDownUi;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCountDownUi::Init(void) {
	
	//�ϐ�������
	m_bStart = false;

	//�J�E���g�_�E��UI�̐���
	m_pCountUi = CObject2D::Create(m_pos, CTexture::TEXTURE_TYPE::COUNT_DOWN_3,
		                           COUNT_DOWN_UI_NUMBER_SIZE_X * m_scale.x, COUNT_DOWN_UI_NUMBER_SIZE_Y * m_scale.y);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCountDownUi::Uninit(void) {

	if (m_pCountUi != nullptr)
	{
		m_pCountUi->Uninit();
		m_pCountUi = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCountDownUi::Update(void) {
	//��������Ă�����
	if (m_pCountUi != nullptr)
	{
		//�Q�[���X�^�[�g����Ȃ��Ƃ�
		if (m_pCountUi->GetTexType() != CTexture::TEXTURE_TYPE::COUNT_DOWN_START)
		{
			if (m_nCounter >= COUNT_DOWN_UI_NEXT_UI_COUNT)
			{
				//�T�C�Y�����ɖ߂�
				m_pCountUi->SetSize(D3DXVECTOR3(COUNT_DOWN_UI_NUMBER_SIZE_X * m_scale.x, COUNT_DOWN_UI_NUMBER_SIZE_Y * m_scale.y, 0.0f));
				m_nCounter = 0;

				//�e�N�X�`���̕ύX
				if (m_pCountUi->GetTexType() == CTexture::TEXTURE_TYPE::COUNT_DOWN_3)
				{
					m_pCountUi->SetTexType(CTexture::TEXTURE_TYPE::COUNT_DOWN_2);
				}
				else if (m_pCountUi->GetTexType() == CTexture::TEXTURE_TYPE::COUNT_DOWN_2)
				{
					m_pCountUi->SetTexType(CTexture::TEXTURE_TYPE::COUNT_DOWN_1);
				}
				else
				{
					m_pCountUi->SetTexType(CTexture::TEXTURE_TYPE::COUNT_DOWN_START);

					//�F�擾
					D3DXCOLOR col = m_pCountUi->GetColor();
					//��������
					col.a = 0.0f;
					//�F�ݒ�
					m_pCountUi->SetColor(col);
					//�T�C�Y��ݒ�
					m_pCountUi->SetSize(D3DXVECTOR3(COUNT_DOWN_UI_START_SIZE_X * m_scale.x, COUNT_DOWN_UI_START_SIZE_Y * m_scale.y, 0.0f));
					//�X�^�[�g��Ԃɂ���
					m_bStart = true;
				}
			}
			else if (m_nCounter < COUNT_DOWN_UI_NUMBER_SIZE_DEC_STOP_COUNT)
			{
				//�T�C�Y�̕ύX��
				float fAddSizeX = -COUNT_DOWN_UI_NUMBER_SIZE_ADD_X;
				float fAddSizeY = -COUNT_DOWN_UI_NUMBER_SIZE_ADD_Y;

				//�T�C�Y�擾
				D3DXVECTOR3 size = m_pCountUi->GetSize();

				if (m_nCounter < COUNT_DOWN_UI_NUMBER_SIZE_DEC_COUNT)
				{
					fAddSizeX *= -1.0f;
					fAddSizeY *= -1.0f;
				}

				//�T�C�Y��ς���
				size.x += fAddSizeX;
				size.y += fAddSizeY;

				//�T�C�Y�ݒ�
				m_pCountUi->SetSize(size);
			}
		}
		else
		{//�Q�[���X�^�[�g�̎�
			if (m_nCounter >= COUNT_DOWN_UI_START_ALPHA_DEC_COUNT)
			{
				//�J���[�擾
				D3DXCOLOR col = m_pCountUi->GetColor();
				//��������
				col.a -= COUNT_DOWN_UI_START_DEC_ALPHA;
				//�����Ȃ��Ȃ�����
				if (col.a <= 0.0f)
				{
					//����
					m_pCountUi->Uninit();
					m_pCountUi = nullptr;
					return;
				}
				else
				{
					//�F�ݒ�
					m_pCountUi->SetColor(col);
				}
			}
			else
			{
				//�J���[�擾
				D3DXCOLOR col = m_pCountUi->GetColor();
				//�����Ȃ��Ȃ�
				if (col.a < 1.0f)
				{
					//�Z������
					col.a += COUNT_DOWN_UI_START_ADD_ALPHA;
					
					if (col.a > 1.0f)
					{
						col.a = 1.0f;
					}

					//�F�ݒ�
					m_pCountUi->SetColor(col);
				}
			}

			//�T�C�Y�擾
			D3DXVECTOR3 size = m_pCountUi->GetSize();
			//�T�C�Y��ς���
			size *= COUNT_DOWN_UI_START_SIZE_ADD;
			//�T�C�Y�ݒ�
			m_pCountUi->SetSize(size);
		}
	}

	m_nCounter++;
}