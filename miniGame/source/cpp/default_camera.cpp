//=============================================================================
//
// �f�t�H���g�J�������� [default_camera.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "default_camera.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_DRAW_DISTANCE (2000.0f)		//�`��\�ȍő�̋���
#define DEFAULT_CAMERA_DISTANCE (1000.0f)	//���_�ƒ����_�̋���

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
// �^�C�g���J�����̐�������
//=============================================================================
CDefaultCamera* CDefaultCamera::Create(void) {
	CDefaultCamera* pDefaultCamera;
	pDefaultCamera = new CDefaultCamera();
	if (pDefaultCamera == nullptr) return nullptr;

	pDefaultCamera->Init();

	return pDefaultCamera;
}

//=============================================================================
// �^�C�g���J�����̏���������
//=============================================================================
HRESULT CDefaultCamera::Init(void) {
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetRot(D3DXVECTOR3(D3DX_PI * -0.1f, D3DX_PI * 0.0f, 0.0f));
	//�����̐ݒ�
	SetDistance(DEFAULT_CAMERA_DISTANCE);

	CCamera::Init();

	//�J�����̃R���g���[���s��
	SetLockControll(true);

	return S_OK;
}

//=============================================================================
// �^�C�g���J�����̏I������
//=============================================================================
void CDefaultCamera::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// �^�C�g���J�����̍X�V����
//=============================================================================
void CDefaultCamera::Update(void) {
	CCamera::Update();

	D3DXVECTOR3 rot = GetRot();
	//��]������
	rot.y += 0.005f;
	if (rot.y > D3DX_PI) {
		rot.y -= D3DX_PI * 2;
	}
	SetRot(rot);

	//------------------------------------
	//���_�ƒ����_�̐ݒ�
	//------------------------------------
	D3DXVECTOR3 pos = GetPos();
	float fDist = GetDistance();

	SetPosR(pos);
	SetPosV(D3DXVECTOR3(pos.x + sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		pos.y + sinf(rot.x + D3DX_PI) * fDist,
		pos.z + cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));	//���_�����S�̏ꍇ����ύX�����Ƃ��Ɉړ����Ȃ��悤��X��]��PI�𑫂��Ă���
}