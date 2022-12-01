//=============================================================================
//
// �X�R�AUI���� [score_ui.cpp]
// Author : ��������
//
//=============================================================================
#include "score_ui.h"
#include "object2D.h"
#include "score.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCORE_UI_FRAME_SIZE		(D3DXVECTOR3(500.0f, 150.0f, 0.0f))	//�t���[���̃T�C�Y
#define SCORE_UI_SCORE_SIZE		(90.0f)								//�X�R�A�̃T�C�Y
#define SCORE_UI_SCORE_POS_X	(10.0f)								//�X�R�A�̈ʒu

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CScoreUi::CScoreUi()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nPlayerNum = 0;
	m_pFrame = nullptr;
	m_pScore = nullptr;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScoreUi::~CScoreUi()
{
	
}

//=============================================================================
// ��������
//=============================================================================
CScoreUi* CScoreUi::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale, const int nNumPlayer) {
	CScoreUi* pScoreUi;
	pScoreUi = new CScoreUi();
	if (pScoreUi == nullptr) return nullptr;

	pScoreUi->m_pos = pos;
	pScoreUi->m_scale = scale;
	pScoreUi->m_nPlayerNum = nNumPlayer;
	pScoreUi->Init();

	return pScoreUi;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScoreUi::Init(void) {
	
	//�t���[���̐���
	m_pFrame = CObject2D::Create(m_pos, CTexture::TEXTURE_TYPE((int)CTexture::TEXTURE_TYPE::SCORE_FRAME_1 + m_nPlayerNum - 1),
		                         SCORE_UI_FRAME_SIZE.x * m_scale.x, SCORE_UI_FRAME_SIZE.y * m_scale.y);

	//�X�R�A�̈ʒu
	D3DXVECTOR3 scorePos = m_pos;
	//�ʒu����ɂ�����
	scorePos.y -= SCORE_UI_SCORE_SIZE * m_scale.x / 2.0f;
	//�E�ɂ��炷
	scorePos.x += (SCORE_UI_SCORE_SIZE * m_scale.x / 2.0f) + (SCORE_UI_SCORE_SIZE * m_scale.x) + SCORE_UI_SCORE_POS_X;

	//�X�R�A�̐���
	m_pScore = CScore::Create(1, CTexture::TEXTURE_TYPE::NUMBER_003, scorePos, SCORE_UI_SCORE_SIZE * m_scale.x);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScoreUi::Uninit(void) {

	if (m_pFrame != nullptr)
	{
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScoreUi::Update(void) {
	
	
}