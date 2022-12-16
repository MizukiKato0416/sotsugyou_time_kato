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
#define MAX_DRAW_DISTANCE			(50000.0f)							//�`��\�ȍő�̋���
#define DEFAULT_CAMERA_DISTANCE		(1500.0f)							//���_�ƒ����_�̋���
#define DEFAULT_CAMERA_ROT_X		(-10.0f)							//�J�����̌���X
#define DEFAULT_CAMERA_POS			(D3DXVECTOR3(0.0f, 50.0f, 0.0f))	//�J�����̏����ʒu

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGameCamera03::CGameCamera03() : CCamera(MAX_DRAW_DISTANCE)
{
	m_bMove = false;
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
	m_destPos = DEFAULT_CAMERA_POS;
	m_fDestDist = DEFAULT_CAMERA_DISTANCE;
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

	D3DXVECTOR3 posCamera = GetPos();	//�ʒu�̎擾
	float fDist = GetDistance();		//�����̎擾

	if (m_bMove) {
		//�ڕW�ʒu�܂ňړ�
		posCamera.x += m_fSpeedMoveDest;
		if (m_fSpeedMoveDest > 0.0f) {
			if (posCamera.x > m_destPos.x) posCamera.x = m_destPos.x;
		}
		else if (m_fSpeedMoveDest < 0.0f) {
			if (posCamera.x < m_destPos.x) posCamera.x = m_destPos.x;
		}
		//�ʒu�̐ݒ�
		SetPos(posCamera);


		//�ڕW�����܂ňړ�
		if (fDist < m_fDestDist) {
			fDist += m_fSpeedDist;
			if (fDist > m_fDestDist) fDist = m_fDestDist;
		}

		//�����̍X�V
		SetDistance(fDist);
	}

	//------------------------------------
	//���_�ƒ����_�̐ݒ�
	//------------------------------------
	D3DXVECTOR3 rot = GetRot();

	SetPosR(posCamera);
	SetPosV(posCamera + D3DXVECTOR3(sinf(rot.y) * fDist * cosf(rot.x + D3DX_PI),
		sinf(rot.x + D3DX_PI) * fDist,
		cosf(rot.y) * fDist * cosf(rot.x + D3DX_PI)));
}

//=============================================================================
// �ڕW�ʒu�����߂�
//=============================================================================
void CGameCamera03::SetDestPos(float fDestPos, int nFrameMove) {
	m_bMove = true;
	m_destPos.x = fDestPos;
	m_fSpeedMoveDest = (m_destPos.x - GetPos().x) / nFrameMove;
}

//=============================================================================
// ���n��
//=============================================================================
void CGameCamera03::OverLook(float fMinPos, float fMaxPos, int nFrameMove) {
	m_bMove = true;

	float fDistMinToMax = fMaxPos - fMinPos;	//�Œ�ʒu����ő�ʒu�ւ̋���

	//�ڕW��X�ʒu�𒆐S�ɂ���
	m_destPos.x = fMinPos + fDistMinToMax / 2.0f;
	m_fSpeedMoveDest = (m_destPos.x - GetPos().x) / nFrameMove;

	m_fDestDist = fDistMinToMax * 1.2f;	//�����������̂��炢
	m_fSpeedDist = (m_fDestDist - GetDistance()) / nFrameMove;
}