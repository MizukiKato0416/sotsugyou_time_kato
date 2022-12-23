//=============================================================================
//
// �f�t�H���g�J�������� [default_camera.cpp]
// Author : 
//
//=============================================================================
#include "default_camera.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_DRAW_DISTANCE (2000.0f)		//�`��\�ȍő�̋���

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CDefaultCamera::CDefaultCamera() : CCamera(MAX_DRAW_DISTANCE)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDefaultCamera::~CDefaultCamera()
{

}

//=============================================================================
// �f�t�H���g�J�����̐�������
//=============================================================================
CDefaultCamera* CDefaultCamera::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fDist) {
	CDefaultCamera* pDefaultCamera;
	pDefaultCamera = new CDefaultCamera();
	if (pDefaultCamera == nullptr) return nullptr;

	//�����_�ƌ����̐ݒ�
	pDefaultCamera->SetPos(pos);
	pDefaultCamera->SetRot(rot);
	//�����̐ݒ�
	pDefaultCamera->SetDistance(fDist);
	//����������
	pDefaultCamera->Init();

	return pDefaultCamera;
}

//=============================================================================
// �f�t�H���g�J�����̏���������
//=============================================================================
HRESULT CDefaultCamera::Init(void) {
	//------------------------------------
	//���_�ƒ����_�̐ݒ�
	//------------------------------------
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fDist = GetDistance();

	SetPosR(pos);
	SetPosV(pos + D3DXVECTOR3(sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		sinf(rot.x + D3DX_PI) * fDist,
		cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));

	CCamera::Init();

	return S_OK;
}

//=============================================================================
// �f�t�H���g�J�����̏I������
//=============================================================================
void CDefaultCamera::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// �f�t�H���g�J�����̍X�V����
//=============================================================================
void CDefaultCamera::Update(void) {
	CCamera::Update();

	//------------------------------------
	//���_�ƒ����_�̐ݒ�
	//------------------------------------
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fDist = GetDistance();

	SetPosR(pos);
	SetPosV(D3DXVECTOR3(pos.x + sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		pos.y + sinf(rot.x + D3DX_PI) * fDist,
		pos.z + cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));	//���_�����S�̏ꍇ����ύX�����Ƃ��Ɉړ����Ȃ��悤��X��]��PI�𑫂��Ă���
}