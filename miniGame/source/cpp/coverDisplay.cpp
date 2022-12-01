//=============================================================================
//
// ��ʑS�̂𕢂����� [coverDisplay.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "coverDisplay.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CCoverDisplay::CCoverDisplay()
{
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	SetEnableStencil(true);
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCoverDisplay::~CCoverDisplay()
{

}

//=============================================================================
// ��������
//=============================================================================
CCoverDisplay* CCoverDisplay::Create(D3DXCOLOR col) {
	CCoverDisplay* pCoverDisplay;
	pCoverDisplay = new CCoverDisplay();
	if (pCoverDisplay == nullptr) return nullptr;

	pCoverDisplay->Init();
	pCoverDisplay->SetColor(col);

	return pCoverDisplay;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCoverDisplay::Init(void) {
	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCoverDisplay::Uninit(void) {
	CObject2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCoverDisplay::Update(void) {
	CObject2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCoverDisplay::Draw(void) {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;
	//�����_���[�̎擾
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);

	CObject2D::Draw();

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
}