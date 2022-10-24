//=============================================================================
//
// �{���������� [create_bom_manager.cpp]
// Author : ��������
//
//=============================================================================
#include "create_bom_manager.h"
#include "bom.h"
#include "gameScene02.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CREATE_BOM_MANAGER_BOM_POS_Y		(500.0f)		//�{���𐶐�����ʒuY

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CCreateBomManager::CCreateBomManager()
{
	m_nFrameCounter = 0;
	m_nFrame = 0;
	m_nNumBom = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCreateBomManager::~CCreateBomManager()
{
	
}

//=============================================================================
// ��������
//=============================================================================
CCreateBomManager* CCreateBomManager::Create(const int nFrame, const int nNumBom) {
	CCreateBomManager* pCheckIcon;
	pCheckIcon = new CCreateBomManager();
	if (pCheckIcon == nullptr) return nullptr;

	pCheckIcon->m_nFrame = nFrame;
	pCheckIcon->m_nNumBom = nNumBom;
	pCheckIcon->Init();

	return pCheckIcon;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCreateBomManager::Init(void) {
	
	//�ϐ�������
	m_nFrameCounter = 0;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCreateBomManager::Uninit(void) {
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCreateBomManager::Update(void) {
	
	m_nFrameCounter++;

	if (m_nFrameCounter > m_nFrame)
	{
		m_nFrameCounter = 0;

		float fRot = 0.0f;
		float fDiffer = 0.0f;
		D3DXVECTOR3 bomPos = D3DXVECTOR3(0.0f, CREATE_BOM_MANAGER_BOM_POS_Y, 0.0f);

		//�{���̐���
		for (int nCntBom = 0; nCntBom < m_nNumBom; nCntBom++)
		{
			//�����������_���Ō��߂�
			fDiffer = (rand() % (int)(GAME_02_STAGE_SIZE) * 100.0f) / 100.0f;
			//�����������_���Ō��߂�
			fRot = (rand() % 629 + -314) / 100.0f;

			//���߂��ʒu�ɏo��
			bomPos.x = sinf(fRot) * fDiffer;
			bomPos.z = cosf(fRot) * fDiffer;

			CBom::Create(bomPos);
		}
	}
}