//=============================================================================
//
// �v���C���[�A�C�R������ [player_icon.cpp]
// Author : ��������
//
//=============================================================================
#include "player_icon.h"
#include "object2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_ICON_FRAME_SIZE			(D3DXVECTOR3(373.0f, 261.0f, 0.0f))		//�t���[���̑傫��
#define PLAYER_ICON_PLAYER_NUM_SIZE		(D3DXVECTOR3(201.0f, 181.0f, 0.0f))		//�v���C���[�ԍ��̑傫��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CPlayerIcon::CPlayerIcon()
{
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayerIcon::~CPlayerIcon()
{
	m_texTypeFrame = CTexture::TEXTURE_TYPE::NONE;
	m_texTypePlayerNum = CTexture::TEXTURE_TYPE::NONE;
}

//=============================================================================
// ��������
//=============================================================================
CPlayerIcon* CPlayerIcon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale,
	                             const CTexture::TEXTURE_TYPE texTypeFrame, const CTexture::TEXTURE_TYPE texTypePlayerNum) {
	CPlayerIcon* pPlayerIcon;
	pPlayerIcon = new CPlayerIcon();
	if (pPlayerIcon == nullptr) return nullptr;

	pPlayerIcon->m_texTypeFrame = texTypeFrame;
	pPlayerIcon->m_texTypePlayerNum = texTypePlayerNum;
	pPlayerIcon->m_scale = scale;
	pPlayerIcon->SetPos(pos);
	pPlayerIcon->Init();

	return pPlayerIcon;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayerIcon::Init(void) {
	
	//�����o���̐���
	//CObject2D::Create(GetPos(), m_texTypeFrame, PLAYER_ICON_FRAME_SIZE);

	//�v���C���[�ԍ��̐���
	//CObject2D::Create(GetPos(), m_texTypePlayerNum, PLAYER_ICON_PLAYER_NUM_SIZE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayerIcon::Uninit(void) {


	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayerIcon::Update(void) {
	
}