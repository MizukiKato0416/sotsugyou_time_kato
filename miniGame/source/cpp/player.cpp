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
#include "item_banana.h"

//=============================================================================
// �}�N����`
//=============================================================================
//--------------------------------
//�t�@�C����
//--------------------------------
#define TEXT_FILE_NAME_LOAD_MOTION "data/MOTION/motion_player.txt"

//--------------------------------
//�v���C���[�J���[
//--------------------------------
#define PLAYER_COLOR_1P		(D3DXCOLOR(0.1f, 0.3f, 1.0f, 1.0f))	//1p�̃J���[
#define PLAYER_COLOR_2P		(D3DXCOLOR(1.0f, 0.2f, 0.0f, 1.0f))	//2p�̃J���[
#define PLAYER_COLOR_3P		(D3DXCOLOR(0.1f, 0.7f, 0.0f, 1.0f))	//3p�̃J���[
#define PLAYER_COLOR_4P		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//4p�̃J���[

//--------------------------------
//�ړ�
//--------------------------------
#define ADD_MOVE_SPEED (1.0f)	//����
#define DEC_MOVE_SPEED (0.3f)	//����
#define MAX_MOVE_SPEED (15.0f)	//���s���x
#define ROTATE_SPEED (0.1f)		//��]���x

//--------------------------------
//�����蔻��
//--------------------------------
#define COLLISION_RADIUS (40.0f)		//�����蔻��̔��a	�ǂƂ��Ɏg��

//--------------------------------
//��]
//--------------------------------
#define PLAYER_SPIN_COUNT	(180)								//�X�s�����鎞��
#define PLAYER_SPIN_SPEED	(0.08f)								//�X�s�����鑬��

//--------------------------------
//���̑�
//--------------------------------
#define COLOR_OUTLINE		(D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f))	//���f���̗֊s�̐F

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CPlayer::m_nPlayerNum = 0;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CPlayer::CPlayer() : CObjectModel(CModel::MODELTYPE::OBJ_CAR, false)
{
	//���������Z
	m_nPlayerNum++;

	SetObjType(OBJTYPE_PLAYER);	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);	//�X�V���̐ݒ�
	SetDrawPriority(DRAW_PRIORITY::CHARA);	//�`�揇�̐ݒ�

	m_lastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_destRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nIndex = m_nPlayerNum;
	m_nCntGameover = 0;
	m_fMoveSpeed = 0.0f;
	m_fBoundMoveSpeed = 0.0f;
	m_state = PLAYER_STATE::NONE;
	m_itemType = CItem::ITEM_TYPE::NONE;
	m_nSpinCounter = 0;
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
	m_fBoundMoveSpeed = 0.0f;
	m_state = PLAYER_STATE::NOMAL;
	m_itemType = CItem::ITEM_TYPE::NONE;
	m_nSpinCounter = 0;

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();

	CObjectModel::Init();

	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�v���C���[�ԍ��ɂ���ĐF��ς���
	switch (m_nIndex)
	{
	case 1:
		col = PLAYER_COLOR_1P;
		break;
	case 2:
		col = PLAYER_COLOR_2P;
		break;
	case 3:
		col = PLAYER_COLOR_3P;
		break;
	case 4:
		col = PLAYER_COLOR_4P;
		break;
	default:
		break;
	}

	//���f���擾
	CModel *pModel = GetPtrModel();
	if (pModel!= nullptr)
	{
		//�w�肵���}�e���A���̐F��ݒ�
		pModel->SetMaterialDiffuse(col,0);
	}

	return S_OK;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CPlayer::Uninit(void) {
	m_nPlayerNum--;

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
	CInputGamepadX *pPadX = static_cast<CInputGamepadX*>(pInput);


	//�ʒu���̃|�C���^�̎擾
	D3DXVECTOR3 posPlayer = GetPos();


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
	case CPlayer::PLAYER_STATE::NOMAL:
		//----------------------------
		//�ړ�
		//----------------------------

		//�ړ��Ɖ�]
		if (pInput != nullptr) {
			Move(pInput, fRotCameraY);
		}

		break;
	case CPlayer::PLAYER_STATE::BOUND:
		//�o�E���h��ԏ���
		StateBound();
		break;
	case CPlayer::PLAYER_STATE::SPIN:
		//�X�s������
		StateSpin();
		break;
	default:
		break;
	}	

	//----------------------------
	//�ړ��̔��f
	//----------------------------
	//�Ō�̈ʒu���W�̕ۑ�
	m_lastPos = posPlayer;
	//�ړ�
	posPlayer += m_move;
	//�ʒu�ݒ�
	SetPos(posPlayer);



	//L1�{�^������������
	if (pPadX->GetTrigger(CInput::CODE::USE_ITEM, m_nIndex - 1))
	{
		//�A�C�e���g�p
		UseItem();
	}

	//----------------------------
	//�����蔻��
	//----------------------------
	Collision(posPlayer);

	//----------------------------
	//���f���̍X�V
	//----------------------------
	CObjectModel::Update();
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CPlayer::Draw(void) {
	
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

	CInputGamepadX *pPadX = static_cast<CInputGamepadX*>(pInput);

	//�㉺���E�L�[���͏�Ԃ̎擾
	const bool bPressUp = pPadX->GetPress(CInput::CODE::MOVE_UP, m_nIndex - 1);
	const bool bPressDown = pPadX->GetPress(CInput::CODE::MOVE_DOWN, m_nIndex - 1);
	const bool bPressLeft = pPadX->GetPress(CInput::CODE::MOVE_LEFT, m_nIndex - 1);
	const bool bPressRight = pPadX->GetPress(CInput::CODE::MOVE_RIGHT, m_nIndex - 1);

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


	//A�{�^���������Ă���Ԍ����Ă�������ɐi��
	if (pPadX->GetPress(CInput::CODE::ACCELE, m_nIndex - 1))
	{
		//����������
		m_fMoveSpeed += ADD_MOVE_SPEED;
		//�ő�l�����傫���Ȃ�����
		if (m_fMoveSpeed > MAX_MOVE_SPEED)
		{
			m_fMoveSpeed = MAX_MOVE_SPEED;
		}
	}
	else if (pPadX->GetPress(CInput::CODE::REVERSE, m_nIndex - 1))
	{//B�{�^������������
		//����������
		m_fMoveSpeed -= ADD_MOVE_SPEED;
		//�ő�l�����傫���Ȃ�����
		if (m_fMoveSpeed < -MAX_MOVE_SPEED)
		{
			m_fMoveSpeed = -MAX_MOVE_SPEED;
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
void CPlayer::DecBoundMove(void) {
	//����
	m_fBoundMoveSpeed *= DEC_MOVE_SPEED;

	//����̒l�̌덷�ɂȂ�����
	if (m_fBoundMoveSpeed < MOVE_ZERO_RANGE && m_fBoundMoveSpeed > -MOVE_ZERO_RANGE)
	{
		//�ړ��ʂ�0�ɂ���
		m_fBoundMoveSpeed = 0.0f;
		m_fMoveSpeed = 0.0f;

		//��Ԃ�ʏ�ɂ���
		m_state = PLAYER_STATE::NOMAL;
	}
}

//=============================================================================
// �����蔻��
//=============================================================================
void CPlayer::Collision(D3DXVECTOR3& pos) {

	//�v���C���[�Ƃ̓����蔻��
	CollisionPlayer();

	//�ǂƂ̓����蔻��
	if (CWallCylinder::Collision(&pos, m_lastPos, COLLISION_RADIUS))
	{
		//�ʒu�ݒ�
		SetPos(pos);

		if (m_state == PLAYER_STATE::BOUND)
		{
			return;
		}

		//��Ԃ�BOUND�ɐݒ�
		m_state = PLAYER_STATE::BOUND;

		//�o�E���h���̏�����ݒ�
		m_fBoundMoveSpeed = m_fMoveSpeed * PLAYER_BOUND_SPEED;
		//�ŏ��l�͈̔͂�菬�����Ȃ�����
		if (m_fBoundMoveSpeed < MOVE_ZERO_RANGE && m_fBoundMoveSpeed > -MOVE_ZERO_RANGE)
		{
			//�ړ��ʂ�0�ɂ���
			m_fBoundMoveSpeed = 0.0f;
			m_fMoveSpeed = 0.0f;

			//��Ԃ�ʏ�ɂ���
			m_state = PLAYER_STATE::NOMAL;
		}
	}
}

//=============================================================================
//�v���C���[�Ƃ̓����蔻��
//=============================================================================
void CPlayer::CollisionPlayer(void)
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
		CPlayer *pPlayer = static_cast<CPlayer*> (pObject);

		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 playerPos = pPlayer->GetPos();
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

			if (m_state == PLAYER_STATE::BOUND)
			{
				return;
			}

			//��Ԃ�BOUND�ɐݒ�
			m_state = PLAYER_STATE::BOUND;

			//�o�E���h���̏�����ݒ�
			m_fBoundMoveSpeed = m_fMoveSpeed * PLAYER_BOUND_SPEED;
			//�ŏ��l�͈̔͂�菬�����Ȃ�����
			if (m_fBoundMoveSpeed < MOVE_ZERO_RANGE && m_fBoundMoveSpeed > -MOVE_ZERO_RANGE)
			{
				//�ړ��ʂ�0�ɂ���
				m_fBoundMoveSpeed = 0.0f;
				m_fMoveSpeed = 0.0f;

				//��Ԃ�ʏ�ɂ���
				m_state = PLAYER_STATE::NOMAL;
			}
		}
		pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
	}
}

//=============================================================================
//�o�E���h��Ԃ̏���
//=============================================================================
void CPlayer::StateBound(void)
{
	//�����Ă�������Ƌt�̕����ɒ��˕Ԃ�
	m_move.x = sinf(GetRot().y) * m_fBoundMoveSpeed;
	m_move.z = cosf(GetRot().y) * m_fBoundMoveSpeed;

	//�ړ��ʂ̌���
	DecBoundMove();
}

//=============================================================================
//�X�s����Ԃ̏���
//=============================================================================
void CPlayer::StateSpin(void)
{
	//�J�E���^�[���Z
	m_nSpinCounter++;
	//����̒l���傫���Ȃ�����
	if (m_nSpinCounter > PLAYER_SPIN_COUNT)
	{
		m_nSpinCounter = 0;
		//��Ԃ�ʏ�ɂ���
		m_state = PLAYER_STATE::NOMAL;
	}
	else
	{
		//�����擾
		D3DXVECTOR3 rot = GetRot();

		//��]������
		rot.y += PLAYER_SPIN_SPEED;

		//�����ݒ�
		SetRot(rot);
	}
}

//=============================================================================
//�A�C�e���g�p����
//=============================================================================
void CPlayer::UseItem(void)
{
	//�A�C�e���������Ă����ԂȂ�
	if (m_itemType == CItem::ITEM_TYPE::NONE || m_state == PLAYER_STATE::SPIN)
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
	default:
		break;
	}
}
