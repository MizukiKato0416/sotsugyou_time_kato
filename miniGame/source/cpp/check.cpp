//=============================================================================
//
// �`�F�b�N���� [check.cpp]
// Author : ��������
//
//=============================================================================
#include "check.h"
#include "check_icon.h"
#include "object2D.h"
#include "count_down_ui.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CHECK_CHECK_ICON_UNINIT_COUNT	(30)		//�`�F�b�N�A�C�R����������܂ł̎���
#define CHECK_FRAME_DEC_ALPHA			(0.02f)		//�w�i�̃��l������

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CCheck::CCheck()
{
	m_apCheckIcon.clear();
	m_nNumPlayer = 0;
	m_bCheckAll = false;
	m_bAllUninit = false;
	m_bCreateCountDownUi = false;
	m_pFrame = nullptr;
	m_state = STATE::NONE;
	m_pCountDownUi = nullptr;
	m_pTutorial = nullptr;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCheck::~CCheck()
{
	
}

//=============================================================================
// ��������
//=============================================================================
CCheck* CCheck::Create(const int nNumPlayer) {
	CCheck* pCheckIcon;
	pCheckIcon = new CCheck();
	if (pCheckIcon == nullptr) return nullptr;

	pCheckIcon->m_nNumPlayer = nNumPlayer;
	pCheckIcon->Init();

	return pCheckIcon;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCheck::Init(void) {
	
	//�ϐ�������
	m_bCheckAll = false;
	m_bAllUninit = false;
	m_state = STATE::CHECK;
	m_pCountDownUi = nullptr;
	m_bCreateCountDownUi = true;

	//�w�i�̈Â����
	m_pFrame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CTexture::TEXTURE_TYPE::CHECK_BG, SCREEN_WIDTH, SCREEN_HEIGHT);

	const float fDist = 380.0f;	//�v���C���[���m�̋���

	for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
	{
		//�v���C���[���f���̈ʒu
		D3DXVECTOR3 posModel = D3DXVECTOR3(fDist * (-m_nNumPlayer / 2.0f) + fDist / 2.0f + nCntPlayer * fDist, -50.0f, 0.0f);

		//�`�F�b�N�A�C�R���̐���
		m_apCheckIcon.push_back(CCheckIcon::Create(D3DXVECTOR3(SCREEN_WIDTH / (m_nNumPlayer * 2) * (1 + nCntPlayer * 2), SCREEN_HEIGHT / 2.0f, 0.0f),
			                                       posModel, D3DXVECTOR3(0.85f, 0.85f, 0.85f), nCntPlayer + 1));
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCheck::Uninit(void) {

	//��������Ă�����
	if (m_pFrame != nullptr)
	{
		//����
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
	{
		//�A�C�R������������Ă�����
		if (m_apCheckIcon[nCntPlayer] != nullptr)
		{
			//����
			m_apCheckIcon[nCntPlayer]->Uninit();
			m_apCheckIcon[nCntPlayer] = nullptr;
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCheck::Update(void) {
	
	switch (m_state)
	{
	case CCheck::STATE::CHECK:
		//�`�F�b�N����
		Check();
		break;
	case CCheck::STATE::COUNTDOWN:
		//�J�E���g�_�E������
		CountDown();
		break;
	default:
		break;
	}
}

//=============================================================================
//�t���[������������
//=============================================================================
void CCheck::DecFrame()
{
	if (m_pFrame != nullptr)
	{
		//�J���[�擾
		D3DXCOLOR col = m_pFrame->GetColor();
		//��������
		col.a -= CHECK_FRAME_DEC_ALPHA;

		//�����Ȃ��Ȃ�����
		if (col.a <= 0.0f)
		{
			col.a = 0.0f;
			//����
			m_pFrame->Uninit();
			m_pFrame = nullptr;
		}
		else
		{
			m_pFrame->SetColor(col);
		}
	}
}

//=============================================================================
//�`�F�b�N����
//=============================================================================
void CCheck::Check()
{
	//�`�F�b�N�o���Ă��Ȃ�������
	if (!m_bCheckAll)
	{
		int nCheck = 0;
		int nNumPlayer = m_nNumPlayer;
#ifdef _DEBUG
		nNumPlayer = 1;
#else
		nNumPlayer = 1;
#endif // !_DEBUG

		for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
		{
			//�A�C�R������������Ă��Ȃ�������
			if (m_apCheckIcon[nCntPlayer] == nullptr)
			{
				continue;
			}

			if (m_apCheckIcon[nCntPlayer]->GetCheck())
			{
				//���₷
				nCheck++;
			}
		}

		//�`�F�b�N�����v���C���[�̐��ƈ�v���Ă�����
		if (nCheck == nNumPlayer)
		{
			//�S�����`�F�b�N�o������Ԃɂ���
			m_bCheckAll = true;
		}
	}

	//�S�����`�F�b�N�o������
	if (m_bCheckAll)
	{
		//�t���[������������
		DecFrame();

		int nCntUninit = 0;
		for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
		{
			//�A�C�R������������Ă��Ȃ�������
			if (m_apCheckIcon[nCntPlayer] == nullptr)
			{
				nCntUninit++;
				continue;
			}

			//�����Ȃ���ԂȂ�
			if (!m_apCheckIcon[nCntPlayer]->GetUninit())
			{
				//����
				m_apCheckIcon[nCntPlayer]->SetUninit(true, CHECK_CHECK_ICON_UNINIT_COUNT);
			}

			//UI���������Ȃ�
			if (m_apCheckIcon[nCntPlayer]->GetFrame() == nullptr &&m_apCheckIcon[nCntPlayer]->GetButton() == nullptr)
			{
				//����
				m_apCheckIcon[nCntPlayer]->Uninit();
				m_apCheckIcon[nCntPlayer] = nullptr;
			}
		}

		//�S�������Ă����犎���������ԂȂ�
		if (nCntUninit == m_nNumPlayer && m_bCreateCountDownUi)
		{
			//�J�E���g�_�E��UI�̐���
			if (m_pCountDownUi == nullptr)
			{
				m_pCountDownUi = CCountDownUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			}

			m_bAllUninit = true;
			//�J�E���g�_�E����Ԃɂ���
			m_state = STATE::COUNTDOWN;
		}
	}
}

//=============================================================================
//�J�E���g�_�E������
//=============================================================================
void CCheck::CountDown()
{
	//�J�E���gUI�������Ă�����
	if (m_pCountDownUi->GetCountUi() == nullptr)
	{
		//�J�E���g�_�E��UI������
		m_pCountDownUi->Uninit();
		m_pCountDownUi = nullptr;

		m_state = STATE::NONE;
	}
}