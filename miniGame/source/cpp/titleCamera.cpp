//=============================================================================
//
// �^�C�g���J�������� [titleCamera.cpp]
// Author : ��������
//
//=============================================================================
#include "titleCamera.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TITLE_CAMERA_MAX_DRAW_DISTANCE			(4000.0f)	//�`��\�ȍő�̋���
#define TITLE_CAMERA_DEFAULT_CAMERA_DISTANCE	(50.0f)		//���_�ƒ����_�̋���
#define TITLE_CAMERA_ROT_X						(40.0f)		//�J�����̌���X
#define TITLE_CAMERA_POS_Z						(-550.0f)	//�J�����̈ʒuZ
#define TITLE_CAMERA_POS_Y						(20.0f)		//�J�����̈ʒuY

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTitleCamera::CTitleCamera() : CCamera(TITLE_CAMERA_MAX_DRAW_DISTANCE)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitleCamera::~CTitleCamera()
{

}

//=============================================================================
// �Q�[���J�����̐�������
//=============================================================================
CTitleCamera* CTitleCamera::Create(void) {
	CTitleCamera* pTitleCamera;
	pTitleCamera = new CTitleCamera();
	if (pTitleCamera == nullptr) return nullptr;

	pTitleCamera->Init();

	return pTitleCamera;
}

//=============================================================================
// �Q�[���J�����̏���������
//=============================================================================
HRESULT CTitleCamera::Init(void) {
	SetPos(D3DXVECTOR3(0.0f, TITLE_CAMERA_POS_Y, TITLE_CAMERA_POS_Z));
	SetRot(D3DXVECTOR3(TITLE_CAMERA_ROT_X * (D3DX_PI / 180.0f), D3DX_PI * -0.0f, 0.0f));
	SetLockControll(true);

	//�����̐ݒ�
	SetDistance(TITLE_CAMERA_DEFAULT_CAMERA_DISTANCE);

	//------------------------------------
	//���_�ƒ����_�̐ݒ�
	//------------------------------------
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fDist = TITLE_CAMERA_DEFAULT_CAMERA_DISTANCE;

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
void CTitleCamera::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// �Q�[���J�����̍X�V����
//=============================================================================
void CTitleCamera::Update(void) {
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