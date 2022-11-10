//=============================================================================
//
// �l�T����V�[���J�������� [find_wolf_camera.cpp]
// Author : ��������
//
//=============================================================================
#include "find_wolf_camera.h"
#include "manager.h"
#include "renderer.h"
#include "gameScene.h"
#include "object_player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FIND_WOLF_CAMERA_MAX_DRAW_DISTANCE		(4000.0f)	//�`��\�ȍő�̋���
#define FIND_WOLF_CAMERA_DEFAULT_CAMERA_DISTANCE (600.0f)	//���_�ƒ����_�̋���
#define FIND_WOLF_CAMERA_DEFAULT_CAMERA_ROT_X	(-30.0f)	//�J�����̌���X
#define FIND_WOLF_CAMERA_DEFAULT_CAMERA_POS_Z	(30.0f)	//�J�����̈ʒuZ

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFindWolfCamera::CFindWolfCamera() : CCamera(FIND_WOLF_CAMERA_MAX_DRAW_DISTANCE)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFindWolfCamera::~CFindWolfCamera()
{

}

//=============================================================================
// �Q�[���J�����̐�������
//=============================================================================
CFindWolfCamera* CFindWolfCamera::Create(void) {
	CFindWolfCamera* pFindWolfCamera;
	pFindWolfCamera = new CFindWolfCamera();
	if (pFindWolfCamera == nullptr) return nullptr;

	pFindWolfCamera->Init();

	return pFindWolfCamera;
}

//=============================================================================
// �Q�[���J�����̏���������
//=============================================================================
HRESULT CFindWolfCamera::Init(void) {
	SetPos(D3DXVECTOR3(0.0f, 0.0f, FIND_WOLF_CAMERA_DEFAULT_CAMERA_POS_Z));
	SetRot(D3DXVECTOR3(FIND_WOLF_CAMERA_DEFAULT_CAMERA_ROT_X * (D3DX_PI / 180.0f), D3DX_PI * -0.0f, 0.0f));
	SetLockControll(true);

	//�����̐ݒ�
	SetDistance(FIND_WOLF_CAMERA_DEFAULT_CAMERA_DISTANCE);

	//------------------------------------
	//���_�ƒ����_�̐ݒ�
	//------------------------------------
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fDist = FIND_WOLF_CAMERA_DEFAULT_CAMERA_DISTANCE;

	SetPosR(pos);
	SetPosV(pos + D3DXVECTOR3(sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		sinf(rot.x + D3DX_PI) * fDist,
		cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));

	CCamera::Init();

	return S_OK;
}

//=============================================================================
// �Q�[���J�����̏I������
//=============================================================================
void CFindWolfCamera::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// �Q�[���J�����̍X�V����
//=============================================================================
void CFindWolfCamera::Update(void) {
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