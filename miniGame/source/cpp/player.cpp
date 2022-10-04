//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "input.h"
#include "gameScene.h"

#include "wallCylinder.h"
#include "effect.h"
#include "particle.h"
#include "particleEffect.h"
#include "object2D.h"
#include "billboard.h"

//=============================================================================
// �}�N����`
//=============================================================================
//--------------------------------
//�t�@�C����
//--------------------------------
#define TEXT_FILE_NAME_LOAD_MOTION "data/MOTION/motion_player.txt"

//--------------------------------
//�ړ�
//--------------------------------
#define ADD_MOVE_SPEED (1.0f)	//����
#define DEC_MOVE_SPEED (0.3f)	//����
#define MAX_MOVE_SPEED (15.0f)	//���s���x
#define ROTATE_SPEED (0.05f)	//��]���x

//--------------------------------
//�����蔻��
//--------------------------------
#define COLLISION_RADIUS (70.0f)		//�����蔻��̔��a	�ǂƂ��Ɏg��
#define NUM_COLLISION (10)				//�����蔻��̐�

//--------------------------------
//�Q�[���I�[�o�[��
//--------------------------------
#define FINISH_TIME_CHANGE_COLOR_GAMEOVER (120)	//�Q�[���I�[�o�[��̐F�ύX�ɂ����鎞��
#define START_CHANGE_COLOR_CLEAR (180)	//�Q�[���I�[�o�[��̓����F�֕ύX����J�n����
#define FINISH_TIME_CLEAR (60)			//�Q�[���I�[�o�[��̓����F�ւ̕ύX�ɂ����鎞��

//--------------------------------
//���̑�
//--------------------------------
#define COLOR_OUTLINE (D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f))	//���f���̗֊s�̐F

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CPlayer::CPlayer() : CObjectModel(CModel::MODELTYPE::OBJ_CAR, false)
{
	SetObjType(OBJTYPE_PLAYER);	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);	//�X�V���̐ݒ�
	SetDrawPriority(DRAW_PRIORITY::CHARA);	//�`�揇�̐ݒ�

	m_lastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_destRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nCntGameover = 0;
	m_fMoveSpeed = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// �v���C���[�̐�������
//=============================================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos) {
	CPlayer* pPlayer;
	pPlayer = new CPlayer();
	if (pPlayer == nullptr) return nullptr;

	pPlayer->SetPos(pos);
	pPlayer->Init();

	return pPlayer;
}

//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CPlayer::Init(void) {
	//�v���C���[�̏����ݒ�
	CObjectModel::SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	m_destRot.y =  D3DX_PI;	//������
	m_fMoveSpeed = 0.0f;


	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();

	CObjectModel::Init();

	return S_OK;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CPlayer::Uninit(void) {
	//�I������
	CObjectModel::Uninit();
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void CPlayer::Update(void) {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();

	CInput* pInput = nullptr;
	CSound *pSound = nullptr;
	CCamera* pCamera = nullptr;
	CGameScene* pGame = nullptr;

	if (pManager != nullptr) {
		//���݂̓��̓f�o�C�X�̎擾
		pInput = pManager->GetInputCur();
		//�T�E���h�̎擾
		pSound = pManager->GetSound();
		//�J�����̎擾
		pCamera = pManager->GetCamera();
		//�Q�[���V�[���̎擾
		pGame = pManager->GetGameScene();
	}

	//�ʒu���̃|�C���^�̎擾
	D3DXVECTOR3 posPlayer = GetPos();


	//----------------------------
	//�J�����̐ݒ�
	//----------------------------
	float fRotCameraY = 0.0f;	//�J�����̊p�x
	if (pCamera != nullptr) {
		fRotCameraY = pCamera->GetRot().y;	//�J�����̊p�x���擾
	}

	//----------------------------
	//�ړ�
	//----------------------------

	//�ړ��Ɖ�]
	if (pInput != nullptr) {
		Move(pInput, fRotCameraY);
	}

	//����
	DecMove();

	//----------------------------
	//�ړ��̔��f
	//----------------------------
	//�Ō�̈ʒu���W�̕ۑ�
	m_lastPos = posPlayer;
	//�ړ�
	posPlayer += m_move;
	//�ʒu�ݒ�
	SetPos(posPlayer);

	//----------------------------
	//�����蔻��
	//----------------------------
	Collision(posPlayer);

	//----------------------------
	//���[�V�����̍X�V
	//----------------------------
	CObjectModel::Update();
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CPlayer::Draw(void) {
	if (m_nCntGameover >= START_CHANGE_COLOR_CLEAR + FINISH_TIME_CLEAR) return;	//�t�F�[�h�������͕`�悵�Ȃ� �e�ⓧ�߂̉e�����Ȃ�������

	CObjectModel::Draw();
}

//=============================================================================
// �v���C���[�̃Q�[���I�[�o�[���̏���
//=============================================================================
void CPlayer::GameOver(void) {
	
	
}

//=============================================================================
// �v���C���[�̓����蔻��̏��̎擾
//=============================================================================
void CPlayer::GetCollisionInfo(int nIdxColParts, int* const pNumCol, D3DXVECTOR3** const ppPosColArray, float* const pRadiusCol) {
	
}

//=============================================================================
// �v���C���[�̍Ō�̈ʒu���W�̎擾
//=============================================================================
D3DXVECTOR3 CPlayer::GetLastPos(void) {
	return m_lastPos;
}

//=============================================================================
// �v���C���[�̈ړ��ʂ̐ݒ�
//=============================================================================
void CPlayer::SetMove(D3DXVECTOR3 move) { m_move = move; }

//=============================================================================
// �v���C���[�̈ړ��ʂ̎擾
//=============================================================================
D3DXVECTOR3 CPlayer::GetMove(void) { return m_move; }

//=============================================================================
// �v���C���[�̓����蔻��̔��a�̎擾
//=============================================================================
float CPlayer::GetRadius(void) {
	return COLLISION_RADIUS;
}

//=============================================================================
// �ړ�
//=============================================================================
void CPlayer::Move(CInput* pInput, float fRotCameraY) {
	if (pInput == nullptr) return;

	//�㉺���E�L�[���͏�Ԃ̎擾
	const bool bPressUp = pInput->GetPress(CInput::CODE::MOVE_UP);
	const bool bPressDown = pInput->GetPress(CInput::CODE::MOVE_DOWN);
	const bool bPressLeft = pInput->GetPress(CInput::CODE::MOVE_LEFT);
	const bool bPressRight = pInput->GetPress(CInput::CODE::MOVE_RIGHT);

	bool bDiagonalMove = (bPressUp != bPressDown) && (bPressLeft != bPressRight);	//�΂߈ړ�
	bool bRotateUp, bRotateDown, bRotateLeft, bRotateRight;	//��]�������
	bRotateUp = bRotateDown = bRotateLeft = bRotateRight = false;

	D3DXVECTOR3 moveAddSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ǉ�����ړ���
	D3DXVECTOR3 moveMaxSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ̍ő�

	//------------------------
	//�ړ����x�̍ő���v�Z
	//------------------------
	float fMaxSpeed;	//�ړ����x�̍ő�
	//�n��
	//if (pInput->GetPress(CInput::CODE::DASH)) {
	//	fMaxSpeed = MAX_MOVE_SPEED_DASH;
	//}
	//else {
	fMaxSpeed = MAX_MOVE_SPEED;
	//}


	//------------------------
	//�ړ��ʂ̌���
	//------------------------
	////�O��ړ��̂ǂ��炩�̂݉�����Ă���ꍇ
	//if (bPressUp != bPressDown) {
	//	if (bPressUp) {
	//		moveAddSpeed.z = ADD_MOVE_SPEED;
	//		moveMaxSpeed.z = fMaxSpeed;
	//		bRotateUp = true;
	//	}
	//	else if (bPressDown) {
	//		moveAddSpeed.z = -ADD_MOVE_SPEED;
	//		moveMaxSpeed.z = -fMaxSpeed;
	//		bRotateDown = true;
	//	}
	//	//�΂߈ړ�
	//	if (bDiagonalMove) {
	//		moveAddSpeed.z *= 0.7f;
	//		moveMaxSpeed.z *= 0.7f;
	//	}
	//}
	////���E�ړ��̂ǂ��炩�̂݉�����Ă���ꍇ
	//if (bPressLeft != bPressRight) {
	//	if (bPressLeft) {
	//		moveAddSpeed.x = -ADD_MOVE_SPEED;
	//		moveMaxSpeed.x = -fMaxSpeed;
	//		bRotateLeft = true;
	//	}
	//	else if (bPressRight) {
	//		moveAddSpeed.x = ADD_MOVE_SPEED;
	//		moveMaxSpeed.x = fMaxSpeed;
	//		bRotateRight = true;
	//	}
	//	//�΂߈ړ�
	//	if (bDiagonalMove) {
	//		moveAddSpeed.x *= 0.7f;
	//		moveMaxSpeed.x *= 0.7f;
	//	}
	//}

	//�O��ړ��̂ǂ��炩�̂݉�����Ă���ꍇ
	if (bPressUp != bPressDown) {
		if (bPressUp) {
			bRotateUp = true;
		}
		else if (bPressDown) {
			bRotateDown = true;
		}
	}
	//���E�ړ��̂ǂ��炩�̂݉�����Ă���ꍇ
	if (bPressLeft != bPressRight) {
		if (bPressLeft) {
			bRotateLeft = true;
		}
		else if (bPressRight) {
			bRotateRight = true;
		}
	}


	//A�{�^���������Ă���Ԍ����Ă�������ɐi��
	if (pInput->GetPress(CInput::CODE::ACCELE))
	{
		//����������
		m_fMoveSpeed += ADD_MOVE_SPEED;
		//�ő�l�����傫���Ȃ�����
		if (m_fMoveSpeed > 8.0f)
		{
			m_fMoveSpeed = 8.0f;
		}
	}
	else if (pInput->GetPress(CInput::CODE::REVERSE))
	{//B�{�^������������
		//����������
		m_fMoveSpeed -= ADD_MOVE_SPEED;
		//�ő�l�����傫���Ȃ�����
		if (m_fMoveSpeed < -8.0f)
		{
			m_fMoveSpeed = -8.0f;
		}
	}

	m_move.x = sinf(GetRot().y + D3DX_PI) * m_fMoveSpeed;
	m_move.z = cosf(GetRot().y + D3DX_PI) * m_fMoveSpeed;

	//------------------------
	//�J�����̊p�x�ɍ��킹�Ĉړ��ʂ̍ő�ʂ�ݒ�
	//------------------------
	D3DXVECTOR3 moveMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��̍ő��
	moveMax.x += moveMaxSpeed.x * sinf(fRotCameraY + 0.5f * D3DX_PI);
	moveMax.x += moveMaxSpeed.z * sinf(fRotCameraY);

	moveMax.z += moveMaxSpeed.x * -sinf(fRotCameraY);
	moveMax.z += moveMaxSpeed.z * cosf(fRotCameraY);

	//------------------------
	//����
	//------------------------
	//X�����̈ړ��ʂ��ő�ʖ����̏ꍇ
	if ((moveMax.x > 0 && m_move.x < moveMax.x) || (moveMax.x < 0 && m_move.x > moveMax.x)) {
		//�J�����̊p�x�ɍ��킹�Ĉړ��ʂ�ǉ�
		m_move.x += moveAddSpeed.x * sinf(fRotCameraY + 0.5f * D3DX_PI);
		m_move.x += moveAddSpeed.z * sinf(fRotCameraY);
		//�������Ɉړ��ʂ��ő�𒴂����ꍇ
		if (moveMax.x > 0) {
			if (m_move.x > moveMax.x) {
				m_move.x = moveMax.x;
			}
		}
		else if (moveMax.x < 0) {
			if (m_move.x < moveMax.x) {
				m_move.x = moveMax.x;
			}
		}
	}
	//Z�����̈ړ��ʂ��ő�ʖ����̏ꍇ
	if ((moveMax.z > 0 && m_move.z < moveMax.z) || (moveMax.z < 0 && m_move.z > moveMax.z)) {
		//�J�����̊p�x�ɍ��킹�Ĉړ��ʂ�ǉ�
		m_move.z += moveAddSpeed.x * -sinf(fRotCameraY);
		m_move.z += moveAddSpeed.z * cosf(fRotCameraY);
		//�������Ɉړ��ʂ��ő�𒴂����ꍇ
		if (moveMax.z > 0) {
			if (m_move.z > moveMax.z) {
				m_move.z = moveMax.z;
			}
		}
		else if (moveMax.z < 0) {
			if (m_move.z < moveMax.z) {
				m_move.z = moveMax.z;
			}
		}
	}

	//------------------------
	//��]�����̌���
	//------------------------		
	bool bInputMove = false;	//�ړ��L�[�������Ă��邩�ǂ���
	bInputMove = bRotateUp || bRotateDown || bRotateLeft || bRotateRight;	//�ǂꂩ��������Ă���ꍇ
	//�ړ��L�[������
	if (bInputMove) {
		//�L�[�������Ă���������ڕW�̊p�x�ɂ���
		//��
		if (bRotateUp) {
			if (bRotateRight) {
				m_destRot.y = D3DX_PI * -0.75f + fRotCameraY;
			}
			else if (bRotateLeft) {
				m_destRot.y = D3DX_PI * 0.75f + fRotCameraY;
			}
			else {
				m_destRot.y = D3DX_PI + fRotCameraY;
			}
		}
		//��
		else if (bRotateDown) {
			if (bRotateRight) {
				m_destRot.y = D3DX_PI * -0.25f + fRotCameraY;
			}
			else if (bRotateLeft) {
				m_destRot.y = D3DX_PI * 0.25f + fRotCameraY;
			}
			else {
				m_destRot.y = 0.0f + fRotCameraY;
			}
		}
		//���E
		else {
			if (bRotateRight) {
				m_destRot.y = D3DX_PI * -0.5f + fRotCameraY;
			}
			else if (bRotateLeft) {
				m_destRot.y = D3DX_PI * 0.5f + fRotCameraY;
			}
		}

		//�p�C���ߎ�
		if (m_destRot.y > D3DX_PI) {
			m_destRot.y = -D3DX_PI * 2 + m_destRot.y;
		}
		else if (m_destRot.y < -D3DX_PI) {
			m_destRot.y = D3DX_PI * 2 + m_destRot.y;
		}

		D3DXVECTOR3 rotPlayer = CObjectModel::GetRot();//�p�x�̎擾
		float fdeltaRot;	//�p�x�̍���
		//���݂̊p�x�ƖڕW�̊p�x�̍����̌v�Z
		if (m_destRot.y >= 0.0f) {
			if (rotPlayer.y >= 0.0f) {
				fdeltaRot = m_destRot.y - rotPlayer.y;
			}
			else if (rotPlayer.y < 0.0f) {
				if (m_destRot.y - rotPlayer.y >= D3DX_PI) {
					fdeltaRot = -D3DX_PI - rotPlayer.y - D3DX_PI + m_destRot.y;
				}
				else if (m_destRot.y - rotPlayer.y < D3DX_PI) {
					fdeltaRot = m_destRot.y - rotPlayer.y;
				}
			}
		}
		else if (m_destRot.y < 0.0f) {
			if (rotPlayer.y >= 0.0f) {
				if (rotPlayer.y - m_destRot.y >= D3DX_PI) {
					fdeltaRot = D3DX_PI - rotPlayer.y + D3DX_PI + m_destRot.y;
				}
				else if (rotPlayer.y - m_destRot.y < D3DX_PI) {
					fdeltaRot = m_destRot.y - rotPlayer.y;
				}
			}
			else if (rotPlayer.y < 0.0f) {
				fdeltaRot = m_destRot.y - rotPlayer.y;
			}
		}

		//��]�̔��f
		rotPlayer.y += fdeltaRot * ROTATE_SPEED * (m_fMoveSpeed / 8.0f);

		//�p�C���ߎ�
		if (rotPlayer.y > D3DX_PI) {
			rotPlayer.y = -D3DX_PI;
		}
		else if (rotPlayer.y < -D3DX_PI) {
			rotPlayer.y = D3DX_PI;
		}

		//�p�x�̐ݒ�
		CObjectModel::SetRot(rotPlayer);
	}
}

//=============================================================================
// �ړ��ʂ̌���
//=============================================================================
void CPlayer::DecMove(void) {
	D3DXVECTOR2 vecMoveDec = D3DXVECTOR2(-m_move.x, -m_move.z);	//�ړ��ʃx�N�g���̋t
	D3DXVec2Normalize(&vecMoveDec, &vecMoveDec);	//���K��
	vecMoveDec *= DEC_MOVE_SPEED;	//�ړ��ʂ̉��Z

	//����
	//m_move.x += vecMoveDec.x;
	//m_move.z += vecMoveDec.y;

	m_fMoveSpeed *= 0.95f;

	if (m_fMoveSpeed < 0.1f && m_fMoveSpeed > 0.1f)
	{
		m_fMoveSpeed = 0.0f;
	}

	////X�����̈ړ��ʂ̒�~
	//if (vecMoveDec.x > 0.0f) {
	//	if (m_move.x > 0.0f) {
	//		m_move.x = 0.0f;
	//	}
	//}
	//else if (vecMoveDec.x < 0.0f) {
	//	if (m_move.x < 0.0f) {
	//		m_move.x = 0.0f;
	//	}
	//}
	////Z�����̈ړ��ʂ̒�~
	//if (vecMoveDec.y > 0.0f) {
	//	if (m_move.z > 0.0f) {
	//		m_move.z = 0.0f;
	//	}
	//}
	//else if (vecMoveDec.x < 0.0f) {
	//	if (m_move.z < 0.0f) {
	//		m_move.z = 0.0f;
	//	}
	//}
}

//=============================================================================
// �����蔻��
//=============================================================================
void CPlayer::Collision(D3DXVECTOR3& pos) {
	//�ǂƂ̓����蔻��
	CWallCylinder::Collision(&pos, m_lastPos, COLLISION_RADIUS);
}