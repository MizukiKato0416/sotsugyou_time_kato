//=============================================================================
//
// �Q�[���J����03���� [gameCamera03.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "gameCamera03.h"
#include "gameScene.h"
#include "manager.h"
#include "object_player.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_DRAW_DISTANCE		(50000.0f)	//�`��\�ȍő�̋���
#define DEFAULT_CAMERA_DISTANCE (1500.0f)	//���_�ƒ����_�̋���
#define DEFAULT_CAMERA_ROT_X	(-20.0f)	//�J�����̌���X
#define DEFAULT_CAMERA_POS	(D3DXVECTOR3(0.0f, 50.0f, 0.0f))

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGameCamera03::CGameCamera03() : CCamera(MAX_DRAW_DISTANCE)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameCamera03::~CGameCamera03()
{

}

//=============================================================================
// �Q�[���J�����̐�������
//=============================================================================
CGameCamera03* CGameCamera03::Create(void) {
	CGameCamera03* pGameCamera;
	pGameCamera = new CGameCamera03();
	if (pGameCamera == nullptr) return nullptr;

	pGameCamera->Init();

	return pGameCamera;
}

//=============================================================================
// �Q�[���J�����̏���������
//=============================================================================
HRESULT CGameCamera03::Init(void) {
	SetPos(DEFAULT_CAMERA_POS);
	SetRot(D3DXVECTOR3(DEFAULT_CAMERA_ROT_X * (D3DX_PI / 180.0f), D3DX_PI * -0.0f, 0.0f));
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
// �Q�[���J�����̏I������
//=============================================================================
void CGameCamera03::Uninit(void) {
	CCamera::Uninit();
}

//=============================================================================
// �Q�[���J�����̍X�V����
//=============================================================================
void CGameCamera03::Update(void) {
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