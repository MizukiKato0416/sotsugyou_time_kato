//=============================================================================
//
// �h�[���̋�̏��� [skydome.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "skydome.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CSkyDome::CSkyDome() : CMeshdome()
{

}

//=============================================================================
// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
//=============================================================================
CSkyDome::CSkyDome(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumXZ, int nNumY, float fRadius) : CMeshdome(pos, rot, nNumXZ, nNumY, fRadius, false)
{
	//�`�揇�̐ݒ�
	SetDrawPriority(DRAW_PRIORITY::BG);	//�w�i

	SetTexType(CTexture::TEXTURE_TYPE::MESH_CLOUD_DOME);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSkyDome::~CSkyDome()
{

}

//=============================================================================
// �h�[���̋�̐�������
//=============================================================================
CSkyDome* CSkyDome::Create(D3DXVECTOR3 pos, int nNumXZ, int nNumY, float fRadius, float fRotSpeed) {
	CSkyDome* pSkyDome;
	pSkyDome = new CSkyDome(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), nNumXZ, nNumY, fRadius);
	if (pSkyDome == nullptr) return nullptr;

	pSkyDome->Init();

	//���Z����������
	pSkyDome->SetAlphaBlend(true);
	//�`�揇�̐ݒ�
	pSkyDome->SetDrawPriority(CObject::DRAW_PRIORITY::CLEAR);
	//���C�g���I�t�ɂ���
	pSkyDome->SetLight(false);
	//��]�ʂ̐ݒ�
	pSkyDome->SetRotate(D3DXVECTOR3(0.f, fRotSpeed, 0.f));

	return pSkyDome;
}

//=============================================================================
// �h�[���̋������ɐ�������
//=============================================================================
void CSkyDome::CreateSphere(D3DXVECTOR3 pos, int nNumXZ, int nNumY, float fRadius, float fRotSpeed) {
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//��̊p�x
		D3DXVECTOR3 offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//�������̐ݒ�
		if (nCnt == 1) {
			rot = D3DXVECTOR3(D3DX_PI, 0.0f, 0.0f);
			offset = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		}
		
		CSkyDome* pSkyDome;
		pSkyDome = new CSkyDome(pos + offset, rot, nNumXZ, nNumY, fRadius);
		if (pSkyDome == nullptr) return;

		pSkyDome->Init();

		//���Z����������
		pSkyDome->SetAlphaBlend(true);
		//�`�揇�̐ݒ�
		pSkyDome->SetDrawPriority(CObject::DRAW_PRIORITY::CLEAR);
		//���C�g���I�t�ɂ���
		pSkyDome->SetLight(false);
		//��]�ʂ̐ݒ�
		pSkyDome->SetRotate(D3DXVECTOR3(0.f, fRotSpeed, 0.f));
	}
}

//=============================================================================
// �h�[���̋�̏���������
//=============================================================================
HRESULT CSkyDome::Init(void) {
	CMeshdome::Init();

	return S_OK;
}

//=============================================================================
// �h�[���̋�̏I������
//=============================================================================
void CSkyDome::Uninit(void) {
	CMeshdome::Uninit();
}

//=============================================================================
// �h�[���̋�̍X�V����
//=============================================================================
void CSkyDome::Update(void) {
	CMeshdome::Update();
}

//=============================================================================
// �h�[���̋�̕`�揈��
//=============================================================================
void CSkyDome::Draw(void) {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return;
	//�����_���[�̎擾
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return;
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return;

	//Z�e�N�X�`���ɏ������܂Ȃ�
	if (pRenderer->GetDrawZTex()) return;

	bool bDefFog = pRenderer->GetEffectFogEnable();	//���݂̃t�H�O���擾
	//�t�H�O�Ȃ�
	pRenderer->SetEffectFogEnable(false);

	//�`��
	CMeshdome::Draw();

	//�t�H�O�̏�Ԃ�߂�
	pRenderer->SetEffectFogEnable(bDefFog);
}