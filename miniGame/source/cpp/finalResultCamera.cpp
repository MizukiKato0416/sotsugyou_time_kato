//=============================================================================
//
// �ŏI���ʃJ�������� [finalResultCamera.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "finalResultCamera.h"
#include "manager.h"
#include "renderer.h"
#include "gameScene.h"
#include "object_player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_DRAW_DISTANCE		(6000.0f)	//�`��\�ȍő�̋���
#define DEFAULT_CAMERA_DISTANCE (1200.0f)	//���_�ƒ����_�̋���
#define DEFAULT_CAMERA_ROT_X	(-15.0f)	//�J�����̌���X
#define DEFAULT_CAMERA_POS_Z	(-120.0f)	//�J�����̈ʒuZ

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFinalResultCamera::CFinalResultCamera() : CCamera(MAX_DRAW_DISTANCE)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFinalResultCamera::~CFinalResultCamera()
{

}

//=============================================================================
// �ŏI���ʃJ�����̐�������
//=============================================================================
CFinalResultCamera* CFinalResultCamera::Create(void) {
	CFinalResultCamera* pFinalResultCamera;
	pFinalResultCamera = new CFinalResultCamera();
	if (pFinalResultCamera == nullptr) return nullptr;

	pFinalResultCamera->Init();

	return pFinalResultCamera;
}

//=============================================================================
// �ŏI���ʃJ�����̏���������
//=============================================================================
HRESULT CFinalResultCamera::Init(void) {
	SetPos(D3DXVECTOR3(0.0f, -500.0f, 0.0f));
	SetRot(D3DXVECTOR3(DEFAULT_CAMERA_ROT_X * (D3DX_PI / 180.0f), 0.0f, 0.0f));
	SetLockControll(true);

	//�����̐ݒ�
	SetDistance(DEFAULT_CAMERA_DISTANCE);

	//------------------------------------
	//���_�ƒ����_�̐ݒ�
	//------------------------------------
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fDist = DEFAULT_CAMERA_DISTANCE;

	SetPosR(pos);
	SetPosV(pos + D3DXVECTOR3(sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		sinf(rot.x + D3DX_PI) * fDist,
		cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));

	CCamera::Init();

	return S_OK;
}

//=============================================================================
// �ŏI���ʃJ�����̏I������
//=============================================================================
void CFinalResultCamera::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// �ŏI���ʃJ�����̍X�V����
//=============================================================================
void CFinalResultCamera::Update(void) {
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