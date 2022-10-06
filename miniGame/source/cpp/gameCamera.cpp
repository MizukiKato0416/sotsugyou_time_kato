//=============================================================================
//
// �Q�[���J�������� [gameCamera.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "gameCamera.h"
#include "manager.h"
#include "renderer.h"
#include "gameScene.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_DRAW_DISTANCE		(5000.0f)	//�`��\�ȍő�̋���
#define DEFAULT_CAMERA_DISTANCE (1200.0f)	//���_�ƒ����_�̋���
#define DEFAULT_CAMERA_ROT_X	(-40.0f)	//�J�����̌���X
#define DEFAULT_CAMERA_POS_Z	(-220.0f)	//�J�����̈ʒuZ

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGameCamera::CGameCamera() : CCamera(MAX_DRAW_DISTANCE)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameCamera::~CGameCamera()
{

}

//=============================================================================
// �Q�[���J�����̐�������
//=============================================================================
CGameCamera* CGameCamera::Create(void) {
	CGameCamera* pGameCamera;
	pGameCamera = new CGameCamera();
	if (pGameCamera == nullptr) return nullptr;

	pGameCamera->Init();

	return pGameCamera;
}

//=============================================================================
// �Q�[���J�����̏���������
//=============================================================================
HRESULT CGameCamera::Init(void) {
	SetPos(D3DXVECTOR3(0.0f, 0.0f, DEFAULT_CAMERA_POS_Z));
	SetRot(D3DXVECTOR3(DEFAULT_CAMERA_ROT_X * (D3DX_PI / 180.0f), D3DX_PI * -0.0f, 0.0f));
	SetLockControll(true);

	//�����̐ݒ�
	SetDistance(DEFAULT_CAMERA_DISTANCE);

	CCamera::Init();

	return S_OK;
}

//=============================================================================
// �Q�[���J�����̏I������
//=============================================================================
void CGameCamera::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// �Q�[���J�����̍X�V����
//=============================================================================
void CGameCamera::Update(void) {
	CCamera::Update();

	D3DXVECTOR3 posCamera = GetPos();
	//�ʒu�̐ݒ�
	SetPos(posCamera);

	//------------------------------------
	//���_�ƒ����_�̐ݒ�
	//------------------------------------
	D3DXVECTOR3 rot = GetRot();
	float fDist = GetDistance();

	SetPosR(posCamera);
	SetPosV(posCamera + D3DXVECTOR3(sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		sinf(rot.x + D3DX_PI) * fDist,
		cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));
}