//=============================================================================
//
// ���D�Q�[���p�ԏ��� [object_player_balloon_car.cpp]
// Author : ��������
//
//=============================================================================
#include "object_player_balloon_car.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "input.h"
#include "gameScene.h"

#include "wallCylinder.h"
#include "effect.h"
#include "object2D.h"
#include "billboard.h"
#include "item_banana.h"

#include "PresetSetEffect.h"
#include "PresetDelaySet.h"
#include "score_ui.h"
#include "score.h"
#include "player.h"
#include "gameScene01.h"

//=============================================================================
// �}�N����`
//=============================================================================

//--------------------------------
//�ړ�
//--------------------------------
#define ADD_MOVE_SPEED								(0.15f)			//����
#define DEC_MOVE_SPEED								(0.93f)			//����
#define MAX_MOVE_SPEED								(9.0f)			//�ő呬�x
#define MAX_MOVE_SPEED_STEAL_POINT					(9.0f * 1.3f)	//�ő呬�x(�|�C���g�D�掞)
#define MOVE_ZERO_RANGE								(0.08f)			//�ړ��ʂ�0�ɂ���͈�
#define ROTATE_SPEED								(0.025f)		//��]���x
#define OBJECT_PLAYER_BALLOON_CAR_BOUND_SPEED		(0.9f)			//�o�E���h�����

//--------------------------------
//�����蔻��
//--------------------------------
#define COLLISION_RADIUS (40.0f)		//�����蔻��̔��a	�ǂƂ��Ɏg��

//--------------------------------
//��]
//--------------------------------
#define OBJECT_PLAYER_BALLOON_CAR_SPIN_COUNT			(90)		//�X�s�����鎞��
#define OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED			(0.3f)		//�X�s�����鑬��
#define OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED_DEC		(0.91f)		//�X�s�����鑬�����Z�l
#define OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED_DEC_COUNT	(60)		//�X�s�����鑬�����������鎞��

//--------------------------------
//���G
//--------------------------------
#define OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COUNTER	(150)	//���G����
#define OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ALPHA	(0.7f)	//���G���̃��l
#define OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD	(0.3f)	//���G���̃J���[���Z�l

//--------------------------------
//���̑�
//--------------------------------
#define COLOR_OUTLINE								(D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f))	//���f���̗֊s�̐F
#define SCORE_UI_POS_Y								(650.0f)							//�X�R�AUI�̈ʒuY

//--------------------------------
//�A�C�e��
//--------------------------------
#define OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_POS_Y		(580.0f)							//�A�C�e��UI�̈ʒuY
#define OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_POS_X		(90.0f)								//�A�C�e��UI�̈ʒuX�����l
#define OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_SIZE		(50.0f)								//�A�C�e��UI�̃T�C�Y
#define OBJECT_PLAYER_BALLOON_CAR_STEAL_POINT		(2)									//���肩��D���|�C���g�̗�
#define OBJECT_PLAYER_BALLOON_CAR_STEAL_POINT_TIME	(60 * 3)							//���肩��D����Ԃ̎���


//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObjectPlayerBalloonCar::CObjectPlayerBalloonCar()
{
	SetObjType(OBJTYPE_PLAYER);						//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);		//�X�V���̐ݒ�
	SetDrawPriority(DRAW_PRIORITY::CHARA);			//�`�揇�̐ݒ�

	m_lastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fMoveSpeed = 0.0f;
	m_fBoundMoveSpeed = 0.0f;
	m_fSpinSpeed = 0.0f;
	m_state = OBJECT_PLAYER_BALLOON_CAR_STATE::NONE;
	m_itemType = CItem::ITEM_TYPE::NONE;
	m_nSpinCounter = 0;
	m_nInvincbleCounter = 0;
	m_nStealPointCounter = 0;
	m_bBound = false;
	m_bStealPoint = false;
	m_pSocreUi = nullptr;
	m_pItemUi = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectPlayerBalloonCar::~CObjectPlayerBalloonCar()
{
	
}

//=============================================================================
// �v���C���[�̐�������
//=============================================================================
CObjectPlayerBalloonCar* CObjectPlayerBalloonCar::Create(D3DXVECTOR3 pos) {
	
	CObjectPlayerBalloonCar* pObjectPlayer;
	pObjectPlayer = new CObjectPlayerBalloonCar();
	if (pObjectPlayer == nullptr) return nullptr;

	pObjectPlayer->SetPos(pos);
	pObjectPlayer->Init();

	return pObjectPlayer;
}

//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CObjectPlayerBalloonCar::Init(void) {

	CObjectPlayer::Init();

	//�v���C���[�̏����ݒ�
	CObjectModel::SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	m_fMoveSpeed = 0.0f;
	m_fBoundMoveSpeed = 0.0f;
	m_state = OBJECT_PLAYER_BALLOON_CAR_STATE::NORMAL;
	m_itemType = CItem::ITEM_TYPE::NONE;
	m_nSpinCounter = 0;
	m_nInvincbleCounter = 0;
	m_bBound = false;
	m_bStealPoint = false;
	m_fSpinSpeed = OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED;
	m_pItemUi = nullptr;
	m_nStealPointCounter = 0;

	return S_OK;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CObjectPlayerBalloonCar::Uninit(void) {

	CObjectPlayer::Uninit();
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void CObjectPlayerBalloonCar::Update(void) {
	//�X�V���Ȃ��ݒ�Ȃ�
	if (!GetPlayer()->GetUpdate())
	{
		return;
	}

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
	D3DXVECTOR3 posObjectPlayer = GetPos();


	//----------------------------
	//�J�����̐ݒ�
	//----------------------------
	float fRotCameraY = 0.0f;	//�J�����̊p�x
	if (pCamera != nullptr) {
		fRotCameraY = pCamera->GetRot().y;	//�J�����̊p�x���擾
	}

	//��ԕ���
	switch (m_state)
	{
	case CObjectPlayerBalloonCar::OBJECT_PLAYER_BALLOON_CAR_STATE::NORMAL:
		//�ړ��Ɖ�]
		if (pInput != nullptr && !m_bBound) {
			Move(pInput, fRotCameraY);
		}
		break;
	case CObjectPlayerBalloonCar::OBJECT_PLAYER_BALLOON_CAR_STATE::INVINCIBLE:
		//�ړ��Ɖ�]
		if (pInput != nullptr && !m_bBound) {
			Move(pInput, fRotCameraY);
		}

		//���G����
		StateInvincble();
		break;
	case CObjectPlayerBalloonCar::OBJECT_PLAYER_BALLOON_CAR_STATE::SPIN:
		//�X�s������
		StateSpin();
		break;
	default:
		break;
	}	

	//�o�E���h����
	StateBound();

	//----------------------------
	//�ړ��̔��f
	//----------------------------
	//�Ō�̈ʒu���W�̕ۑ�
	m_lastPos = posObjectPlayer;
	//�ړ�
	posObjectPlayer += m_move;
	//�ʒu�ݒ�
	SetPos(posObjectPlayer);

	//L1�{�^������������
	if (pInput->GetTrigger(CInput::CODE::USE_ITEM, GetPlayer()->GetIndex() - 1))
	{
		//�A�C�e���g�p
		UseItem();
	}

	//�|�C���g�D����
	StealPoint();

	//�A�C�e��UI�̏���
	ItemUi();

	//----------------------------
	//�����蔻��
	//----------------------------
	Collision(posObjectPlayer);

	CObjectPlayer::Update();
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CObjectPlayerBalloonCar::Draw(void) {
	
	CObjectPlayer::Draw();
}

//=============================================================================
// �v���C���[�̃Q�[���I�[�o�[���̏���
//=============================================================================
void CObjectPlayerBalloonCar::GameOver(void) {
	
	CObjectPlayer::GameOver();
}

//=============================================================================
// �v���C���[�̍Ō�̈ʒu���W�̎擾
//=============================================================================
D3DXVECTOR3 CObjectPlayerBalloonCar::GetLastPos(void) {
	return m_lastPos;
}

//=============================================================================
// �v���C���[�̈ړ��ʂ̐ݒ�
//=============================================================================
void CObjectPlayerBalloonCar::SetMove(D3DXVECTOR3 move) { m_move = move; }

//=============================================================================
// �v���C���[�̈ړ��ʂ̎擾
//=============================================================================
D3DXVECTOR3 CObjectPlayerBalloonCar::GetMove(void) { return m_move; }

//=============================================================================
// �v���C���[�̓����蔻��̔��a�̎擾
//=============================================================================
float CObjectPlayerBalloonCar::GetRadius(void) {
	return COLLISION_RADIUS;
}

//=============================================================================
//�X�R�A��������
//=============================================================================
void CObjectPlayerBalloonCar::CreateScore()
{
	//�X�R�AUI�̐��� 
	m_pSocreUi = CScoreUi::Create(D3DXVECTOR3(SCREEN_WIDTH / (MAX_OBJECT_PLAYER_BALLOON_CAR_NUM + 1) * GetPlayer()->GetIndex(), SCORE_UI_POS_Y, 0.0f),
		                          D3DXVECTOR3(0.5f, 0.5f, 0.5f), GetPlayer()->GetIndex());
}

//=============================================================================
//�A�C�e��UI�̃t���[����������
//=============================================================================
void CObjectPlayerBalloonCar::CreateItemUiFrame()
{
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / (MAX_OBJECT_PLAYER_BALLOON_CAR_NUM + 1) * GetPlayer()->GetIndex() - OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_POS_X, OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_POS_Y, 0.0f),
		              CTexture::TEXTURE_TYPE((int)CTexture::TEXTURE_TYPE::ITEM_UI_FRAME_1 + GetPlayer()->GetIndex() - 1), OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_SIZE, OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_SIZE);
}

//=============================================================================
// �ړ�
//=============================================================================
void CObjectPlayerBalloonCar::Move(CInput* pInput, float fRotCameraY) {
	if (pInput == nullptr) return;

	//�㉺���E�L�[���͏�Ԃ̎擾
	const bool bPressUp = pInput->GetPress(CInput::CODE::MOVE_UP, GetPlayer()->GetIndex() - 1);
	const bool bPressDown = pInput->GetPress(CInput::CODE::MOVE_DOWN, GetPlayer()->GetIndex() - 1);
	const bool bPressLeft = pInput->GetPress(CInput::CODE::MOVE_LEFT, GetPlayer()->GetIndex() - 1);
	const bool bPressRight = pInput->GetPress(CInput::CODE::MOVE_RIGHT, GetPlayer()->GetIndex() - 1);

	bool bDiagonalMove = (bPressUp != bPressDown) && (bPressLeft != bPressRight);	//�΂߈ړ�
	bool bRotateUp, bRotateDown, bRotateLeft, bRotateRight;	//��]�������
	bRotateUp = bRotateDown = bRotateLeft = bRotateRight = false;

	D3DXVECTOR3 moveAddSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ǉ�����ړ���
	D3DXVECTOR3 moveMaxSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ̍ő�

	
	//------------------------
	//�ړ��ʂ̌���
	//------------------------

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

	//�ő呬�x
	float fMaxSpeed = MAX_MOVE_SPEED;
	//�|�C���g�D�掞
	if (m_bStealPoint) fMaxSpeed = MAX_MOVE_SPEED_STEAL_POINT;

	//A�{�^���������Ă���Ԍ����Ă�������ɐi��
	if (pInput->GetPress(CInput::CODE::ACCELE, GetPlayer()->GetIndex() - 1))
	{
		//����������
		m_fMoveSpeed += ADD_MOVE_SPEED;
		//�ő�l�����傫���Ȃ�����
		if (m_fMoveSpeed > fMaxSpeed)
		{
			m_fMoveSpeed = fMaxSpeed;
		}
		//---------------------------------
		//��
		CPresetEffect::SetEffect3D(0, GetPos() , {}, {});
		//---------------------------------
	}
	else if (pInput->GetPress(CInput::CODE::REVERSE, GetPlayer()->GetIndex() - 1))
	{//B�{�^������������
		//����������
		m_fMoveSpeed -= ADD_MOVE_SPEED;
		//�ő�l�����傫���Ȃ�����
		if (m_fMoveSpeed < -fMaxSpeed)
		{
			m_fMoveSpeed = -fMaxSpeed;
		}
	}
	else
	{
		//����
		DecMove();
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
	//��]�����̌���
	//------------------------		
	bool bInputMove = false;	//�ړ��L�[�������Ă��邩�ǂ���
	bInputMove = bRotateUp || bRotateDown || bRotateLeft || bRotateRight;	//�ǂꂩ��������Ă���ꍇ
	//�ړ��L�[������
	if (bInputMove) {
		float destRotY;	//�ڕW�p�x

		//�L�[�������Ă���������ڕW�̊p�x�ɂ���
		//��
		if (bRotateUp) {
			if (bRotateRight) {
				destRotY = D3DX_PI * -0.75f + fRotCameraY;
			}
			else if (bRotateLeft) {
				destRotY = D3DX_PI * 0.75f + fRotCameraY;
			}
			else {
				destRotY = D3DX_PI + fRotCameraY;
			}
		}
		//��
		else if (bRotateDown) {
			if (bRotateRight) {
				destRotY = D3DX_PI * -0.25f + fRotCameraY;
			}
			else if (bRotateLeft) {
				destRotY = D3DX_PI * 0.25f + fRotCameraY;
			}
			else {
				destRotY = 0.0f + fRotCameraY;
			}
		}
		//���E
		else {
			if (bRotateRight) {
				destRotY = D3DX_PI * -0.5f + fRotCameraY;
			}
			else if (bRotateLeft) {
				destRotY = D3DX_PI * 0.5f + fRotCameraY;
			}
		}

		//�p�C���ߎ�
		if (destRotY > D3DX_PI) {
			destRotY += -D3DX_PI * 2;
		}
		else if (destRotY < -D3DX_PI) {
			destRotY += D3DX_PI * 2;
		}

		//��i���͋t����
		if (m_fMoveSpeed < 0.0f) {
			destRotY += D3DX_PI;
			if (destRotY > D3DX_PI) {
				destRotY += -D3DX_PI * 2;
			}
		}

		D3DXVECTOR3 rotObjectPlayer = CObjectModel::GetRot();//�p�x�̎擾
		float fdeltaRot;	//�p�x�̍���
		//���݂̊p�x�ƖڕW�̊p�x�̍����̌v�Z
		if (destRotY >= 0.0f) {
			if (rotObjectPlayer.y >= 0.0f) {
				fdeltaRot = destRotY - rotObjectPlayer.y;
			}
			else if (rotObjectPlayer.y < 0.0f) {
				if (destRotY - rotObjectPlayer.y >= D3DX_PI) {
					fdeltaRot = -D3DX_PI - rotObjectPlayer.y - D3DX_PI + destRotY;
				}
				else if (destRotY - rotObjectPlayer.y < D3DX_PI) {
					fdeltaRot = destRotY - rotObjectPlayer.y;
				}
			}
		}
		else if (destRotY < 0.0f) {
			if (rotObjectPlayer.y >= 0.0f) {
				if (rotObjectPlayer.y - destRotY >= D3DX_PI) {
					fdeltaRot = D3DX_PI - rotObjectPlayer.y + D3DX_PI + destRotY;
				}
				else if (rotObjectPlayer.y - destRotY < D3DX_PI) {
					fdeltaRot = destRotY - rotObjectPlayer.y;
				}
			}
			else if (rotObjectPlayer.y < 0.0f) {
				fdeltaRot = destRotY - rotObjectPlayer.y;
			}
		}

		//��]�̔��f
		rotObjectPlayer.y += fdeltaRot * ROTATE_SPEED * (fabsf(m_fMoveSpeed) / 8.0f);

		//�p�C���ߎ�
		if (rotObjectPlayer.y > D3DX_PI) {
			rotObjectPlayer.y = -D3DX_PI;
		}
		else if (rotObjectPlayer.y < -D3DX_PI) {
			rotObjectPlayer.y = D3DX_PI;
		}

		//�p�x�̐ݒ�
		CObjectModel::SetRot(rotObjectPlayer);
		//---------------------------------
		//�y��
		CPresetEffect::SetEffect3D(1, GetPos(), {}, {});
		//---------------------------------
	}
}

//=============================================================================
// �ړ��ʂ̌���
//=============================================================================
void CObjectPlayerBalloonCar::DecMove(void) {
	//����
	m_fMoveSpeed *= DEC_MOVE_SPEED;

	//����̒l�̌덷�ɂȂ�����
	if (m_fMoveSpeed < MOVE_ZERO_RANGE && m_fMoveSpeed > -MOVE_ZERO_RANGE)
	{
		//�ړ��ʂ�0�ɂ���
		m_fMoveSpeed = 0.0f;
	}
}

//=============================================================================
// �ړ��ʂ̌���
//=============================================================================
void CObjectPlayerBalloonCar::DecBoundMove(void) {
	//����
	m_fBoundMoveSpeed *= DEC_MOVE_SPEED;

	//����̒l�̌덷�ɂȂ�����
	if (m_fBoundMoveSpeed < MOVE_ZERO_RANGE && m_fBoundMoveSpeed > -MOVE_ZERO_RANGE)
	{
		//�ړ��ʂ�0�ɂ���
		m_fBoundMoveSpeed = 0.0f;
		m_fMoveSpeed = 0.0f;

		//��Ԃ�ʏ�ɂ���
		m_bBound = false;
	}
}

//=============================================================================
// �����蔻��
//=============================================================================
void CObjectPlayerBalloonCar::Collision(D3DXVECTOR3& pos) {

	//�v���C���[�Ƃ̓����蔻��
	CollisionObjectPlayer();

	//�ǂƂ̓����蔻��
	if (CWallCylinder::Collision(&pos, m_lastPos, COLLISION_RADIUS))
	{
		//�ʒu�ݒ�
		SetPos(pos);

		if (m_state == OBJECT_PLAYER_BALLOON_CAR_STATE::SPIN)
		{
			//return;
		}

		if (m_bBound)
		{
			return;
		}

		//��Ԃ�BOUND�ɐݒ�
		m_bBound = true;

		//�o�E���h���̏�����ݒ�
		m_fBoundMoveSpeed = m_fMoveSpeed * OBJECT_PLAYER_BALLOON_CAR_BOUND_SPEED;
		//�ŏ��l�͈̔͂�菬�����Ȃ�����
		if (m_fBoundMoveSpeed < MOVE_ZERO_RANGE && m_fBoundMoveSpeed > -MOVE_ZERO_RANGE)
		{
			//�ړ��ʂ�0�ɂ���
			m_fBoundMoveSpeed = 0.0f;
			m_fMoveSpeed = 0.0f;

			//��Ԃ�ʏ�ɂ���
			m_bBound = false;
		}
	}
}

//=============================================================================
//�v���C���[�Ƃ̓����蔻��
//=============================================================================
void CObjectPlayerBalloonCar::CollisionObjectPlayer(void)
{
	CObject* pObject = GetObjectTopAll();	//�S�I�u�W�F�N�g�̃��X�g�̐擪���擾

	while (pObject != nullptr) {
		CObject* pObjNext = GetObjectNextAll(pObject);	//���X�g�̎��̃I�u�W�F�N�g�̃|�C���^���擾

		//�I�u�W�F�N�g�^�C�v�̊m�F
		bool bMatchType = false;
		if (pObject->GetObjType() & OBJTYPE_PLAYER) bMatchType = true;

		if (!bMatchType || pObject == this)
		{
			pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
			continue;
		}

		//�v���C���[�ɃL���X�g
		CObjectPlayerBalloonCar *pObjectPlayer = static_cast<CObjectPlayerBalloonCar*> (pObject);

		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 playerPos = pObjectPlayer->GetPos();
		D3DXVECTOR3 myPos = GetPos();

		//��_�̋����x�N�g��
		D3DXVECTOR2 differVec = D3DXVECTOR2(playerPos.x - myPos.x, playerPos.z - myPos.z);
		//��_�̋���
		float fDiffer = D3DXVec2Length(&differVec);

		//�������Ă�����
		if (fDiffer <= COLLISION_RADIUS * 2.0f)
		{
			//���g�ƑΏۂ̃I�u�W�F�N�g�̊p�x�����߂�
			float fRot = atan2((myPos.x - playerPos.x), (myPos.z - playerPos.z));

			//���g�̈ʒu�������o��
			myPos.x = playerPos.x + (sinf(fRot) * (COLLISION_RADIUS * 2.0f));
			myPos.z = playerPos.z + (cosf(fRot) * (COLLISION_RADIUS * 2.0f));

			//�ʒu�ݒ�
			SetPos(myPos);

			if (!m_bStealPoint) return;

			//�|�C���g��D����ԂȂ�
			//����̃|�C���g��D��

			int nAddScore = OBJECT_PLAYER_BALLOON_CAR_STEAL_POINT;
			if (pObjectPlayer->GetScoreUi()->GetScore()->GetScore() <= OBJECT_PLAYER_BALLOON_CAR_STEAL_POINT)
			{
				nAddScore = pObjectPlayer->GetScoreUi()->GetScore()->GetScore();
			}
			m_pSocreUi->GetScore()->AddScore(nAddScore);

			//�X�R�A���ő�l�𒴂�����
			if (GetScoreUi()->GetScore()->GetScore() > BALLOON_SCORE_MAX)
			{
				//�����Ȃ��悤�ɂ���
				GetScoreUi()->GetScore()->SetScore(BALLOON_SCORE_MAX);
			}

			pObjectPlayer->GetScoreUi()->GetScore()->AddScore(-nAddScore);
			m_bStealPoint = false;
			m_nStealPointCounter = 0;
		}
		pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
	}
}

//=============================================================================
//�o�E���h��Ԃ̏���
//=============================================================================
void CObjectPlayerBalloonCar::StateBound(void)
{
	if (m_bBound)
	{
		//�����Ă�������Ƌt�̕����ɒ��˕Ԃ�
		m_move.x = sinf(GetRot().y) * m_fBoundMoveSpeed;
		m_move.z = cosf(GetRot().y) * m_fBoundMoveSpeed;

		//�ړ��ʂ̌���
		DecBoundMove();
	}
}

//=============================================================================
//�X�s����Ԃ̏���
//=============================================================================
void CObjectPlayerBalloonCar::StateSpin(void)
{
	//�J�E���^�[���Z
	m_nSpinCounter++;
	//����̒l���傫���Ȃ�����
	if (m_nSpinCounter > OBJECT_PLAYER_BALLOON_CAR_SPIN_COUNT)
	{
		m_nSpinCounter = 0;
		//��Ԃ𖳓G�ɂ���
		m_state = OBJECT_PLAYER_BALLOON_CAR_STATE::INVINCIBLE;
	}
	else
	{
		//�����擾
		D3DXVECTOR3 rot = GetRot();

		if (m_nSpinCounter > OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED_DEC_COUNT)
		{
			//����������
			m_fSpinSpeed *= OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED_DEC;
		}
		else
		{
			m_fSpinSpeed = OBJECT_PLAYER_BALLOON_CAR_SPIN_SPEED;
		}

		//��]������
		rot.y += m_fSpinSpeed;

		//�����ݒ�
		SetRot(rot);
	}
}

//=============================================================================
//���G��Ԃ̏���
//=============================================================================
void CObjectPlayerBalloonCar::StateInvincble(void)
{
	//�ŏ�����
	if (m_nInvincbleCounter == 0)
	{
		//���f���擾
		CModel *pModel = GetPtrModel();
		if (pModel != nullptr)
		{
			//�}�e���A�����擾
			int nNumMat = CModel::GetNumMat(pModel->GetModelType());

			for (int nCntMat = 0; nCntMat < nNumMat; nCntMat++)
			{
				//�J���[�擾
				D3DXCOLOR col = pModel->GetMaterialDiffuse(nCntMat);

				//��������
				col.a = OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ALPHA;
				//�F�����Z
				col.r += OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD;
				col.g += OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD;
				col.b += OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD;

				//�F�ݒ�
				pModel->SetMaterialDiffuse(col, nCntMat);
			}
		}
	}

	m_nInvincbleCounter++;
	if (m_nInvincbleCounter > OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COUNTER)
	{
		m_nInvincbleCounter = 0;

		//���f���擾
		CModel *pModel = GetPtrModel();
		if (pModel != nullptr)
		{
			//�}�e���A�����擾
			int nNumMat = CModel::GetNumMat(pModel->GetModelType());

			for (int nCntMat = 0; nCntMat < nNumMat; nCntMat++)
			{
				//�J���[�擾
				D3DXCOLOR col = pModel->GetMaterialDiffuse(nCntMat);

				//���ɖ߂�
				col.a = 1.0f;
				//�F�����Z
				col.r -= OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD;
				col.g -= OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD;
				col.b -= OBJECT_PLAYER_BALLOON_CAR_INVINCIBLE_COL_ADD;

				//�F�ݒ�
				pModel->SetMaterialDiffuse(col, nCntMat);
			}
		}

		//�ʏ��Ԃɂ���
		m_state = OBJECT_PLAYER_BALLOON_CAR_STATE::NORMAL;
	}
}

//=============================================================================
//�A�C�e���g�p����
//=============================================================================
void CObjectPlayerBalloonCar::UseItem(void)
{
	//�A�C�e���������Ă����ԂȂ�
	if (m_itemType == CItem::ITEM_TYPE::NONE || m_state == OBJECT_PLAYER_BALLOON_CAR_STATE::SPIN)
	{
		return;
	}

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�A�C�e���𐶐�����
	switch (m_itemType)
	{
	case CItem::ITEM_TYPE::BANANA:
		//�o�i�i�̐���
		CItemBanana::Create(pos, this);
		break;
	case CItem::ITEM_TYPE::STEAL_POINT:
		//�|�C���g��D����Ԃɂ���
		m_bStealPoint = true;
		m_itemType = CItem::ITEM_TYPE::NONE;
		break;
	default:
		break;
	}

	//�A�C�e��UI������
	if (m_pItemUi != nullptr)
	{
		m_pItemUi->Uninit();
		m_pItemUi = nullptr;
	}
}

//=============================================================================
//�A�C�e��Ui����
//=============================================================================
void CObjectPlayerBalloonCar::ItemUi(void)
{
	//�A�C�e���������Ă��Ȃ���Ԃ܂��̓A�C�e��UI����������Ă���Ȃ�
	if (m_itemType == CItem::ITEM_TYPE::NONE || m_pItemUi != nullptr)
	{
		return;
	}
	
	//�A�C�e����UI����
	m_pItemUi = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / (MAX_OBJECT_PLAYER_BALLOON_CAR_NUM + 1) * GetPlayer()->GetIndex() - OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_POS_X, OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_POS_Y, 0.0f),
		                          CTexture::TEXTURE_TYPE::NONE, OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_SIZE, OBJECT_PLAYER_BALLOON_CAR_ITEM_UI_SIZE);

	//�e�N�X�`����ύX
	switch (m_itemType)
	{
	case CItem::ITEM_TYPE::BANANA:
		m_pItemUi->SetTexType(CTexture::TEXTURE_TYPE::ITEM_BANANA);
		break;
	case CItem::ITEM_TYPE::STEAL_POINT:
		m_pItemUi->SetTexType(CTexture::TEXTURE_TYPE::ITEM_GASOLINE);
		break;
	default:
		break;
	}
}

//=============================================================================
//�|�C���g�D�揈��
//=============================================================================
void CObjectPlayerBalloonCar::StealPoint()
{
	if (!m_bStealPoint) return;

	//�|�C���g��D����ԂȂ�
	m_nStealPointCounter++;

	//�G�t�F�N�g
	CPresetDelaySet::Create(4, GetPos(), {}, {});

	if (m_nStealPointCounter <= OBJECT_PLAYER_BALLOON_CAR_STEAL_POINT_TIME) return;

	//���ԊO�Ȃ�
	m_bStealPoint = false;
	m_nStealPointCounter = 0;
}