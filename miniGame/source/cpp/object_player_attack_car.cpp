//=============================================================================
//
// �Փ˃Q�[���p�ԏ��� [object_player_attack_car.cpp]
// Author : ��������
//
//=============================================================================
#include "object_player_attack_car.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "input.h"
#include "PresetSetEffect.h"
#include "player.h"
#include "gameScene02.h"

#include "PresetDelaySet.h"
//=============================================================================
// �}�N����`
//=============================================================================

//--------------------------------
//�ړ�
//--------------------------------
#define ATTACK_CAR_ADD_MOVE_SPEED			(0.1f)		//����
#define ATTACK_CAR_DEC_MOVE_SPEED			(0.93f)		//����
#define ATTACK_CAR_MAX_MOVE_SPEED			(7.0f)		//�ő呬�x
#define ATTACK_CAR_MOVE_ZERO_RANGE			(0.08f)		//�ړ��ʂ�0�ɂ���͈�
#define ATTACK_CAR_ATTACK_MOVE_SPEED		(40.0f)		//�A�^�b�N���̈ړ���

#define ATTACK_CAR_ROTATE_SPEED				(0.025f)	//��]���x

//--------------------------------
//�����蔻��
//--------------------------------
#define COLLISION_RADIUS	(40.0f)		//�����蔻��̔��a	�ǂƂ��Ɏg��

//--------------------------------
//�o�E���h
//--------------------------------
#define ATTACK_CAR_NORMAL_MY_BOUND		(1.0f)		//����ɓ��������Ƃ����g�����˕Ԃ�ʂ̔{��
#define ATTACK_CAR_NORMAL_ENEMY_BOUND	(1.5f)		//����ɓ��������Ƃ����肪���˕Ԃ�ʂ̔{��
#define ATTACK_CAR_ATTACK_MY_BOUND		(1.0f)		//�A�^�b�N��Ԃ̎��ɑ���ɓ��������Ƃ����g�����˕Ԃ�ʂ̔{��
#define ATTACK_CAR_ATTACK_ENEMY_BOUND	(1.5f)		//�A�^�b�N��Ԃ̎��ɑ���ɓ��������Ƃ����肪���˕Ԃ�ʂ̔{��
#define ATTACK_CAR_BOUND_DEC			(0.9f)		//�o�E���h�̈ړ��ʌ�����

//--------------------------------
//���̑�
//--------------------------------
#define ATTACK_CAR_GRAVITY				(0.5f)		//�d��

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObjectPlayerAttackCar::CObjectPlayerAttackCar()
{
	SetObjType(OBJTYPE_PLAYER);						//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);		//�X�V���̐ݒ�
	SetDrawPriority(DRAW_PRIORITY::CHARA);			//�`�揇�̐ݒ�

	m_lastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_destRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_boundMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fMoveSpeed = 0.0f;
	m_bAttack = false;
	memset(m_bCollOld, false, sizeof(m_bCollOld[MAX_OBJECT_PLAYER_NUM]));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectPlayerAttackCar::~CObjectPlayerAttackCar()
{
	
}

//=============================================================================
// �v���C���[�̐�������
//=============================================================================
CObjectPlayerAttackCar* CObjectPlayerAttackCar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot) {
	
	CObjectPlayerAttackCar* pObjectPlayer;
	pObjectPlayer = new CObjectPlayerAttackCar();
	if (pObjectPlayer == nullptr) return nullptr;

	pObjectPlayer->SetPos(pos);
	pObjectPlayer->Init();
	pObjectPlayer->SetRot(rot);

	return pObjectPlayer;
}

//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CObjectPlayerAttackCar::Init(void) {

	CObjectPlayer::Init();

	//�v���C���[�̏����ݒ�
	CObjectModel::SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	m_destRot.y =  D3DX_PI;	//������
	m_fMoveSpeed = 0.0f;
	m_boundMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bAttack = false;
	memset(m_bCollOld, FALSE, sizeof(m_bCollOld[MAX_OBJECT_PLAYER_NUM]));

	return S_OK;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CObjectPlayerAttackCar::Uninit(void) {

	CObjectPlayer::Uninit();
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void CObjectPlayerAttackCar::Update(void) {

	//�X�V���Ȃ��ݒ�Ȃ�
	if (!GetPlayer()->GetUpdate())
	{
		//��ʂȂ�
		if (GetPlayer()->GetRanking() == 1)
		{
			return;
		}

		//�d�͏���
		Gravity();

		//����
		DecBoundMove();

		//�ړ��ʐݒ�
		m_move.x = sinf(GetRot().y + D3DX_PI) * m_fMoveSpeed;
		m_move.z = cosf(GetRot().y + D3DX_PI) * m_fMoveSpeed;

		//----------------------------
		//�ړ��̔��f
		//----------------------------
		//�ʒu���̃|�C���^�̎擾
		D3DXVECTOR3 posObjectPlayer = GetPos();
		//�Ō�̈ʒu���W�̕ۑ�
		m_lastPos = posObjectPlayer;
		//�ړ�
		posObjectPlayer += m_move + m_boundMove;
		//�ʒu�ݒ�
		SetPos(posObjectPlayer);

		CObjectPlayer::Update();

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

	//�����Ă��Ȃ�������
	if (GetPos().y >= 0.0f)
	{
		//�ړ��Ɖ�]
		if (pInput != nullptr) {
			Move(pInput, fRotCameraY);
		}
	}
	

	//�d�͏���
	Gravity();

	//----------------------------
	//�ړ��̔��f
	//----------------------------
	//�Ō�̈ʒu���W�̕ۑ�
	m_lastPos = posObjectPlayer;
	//�ړ�
	posObjectPlayer += m_move + m_boundMove;
	//�ʒu�ݒ�
	SetPos(posObjectPlayer);

	//----------------------------
	//�����蔻��
	//----------------------------
	Collision(posObjectPlayer);

	CObjectPlayer::Update();
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CObjectPlayerAttackCar::Draw(void) {
	
	CObjectPlayer::Draw();
}

//=============================================================================
// �v���C���[�̃Q�[���I�[�o�[���̏���
//=============================================================================
void CObjectPlayerAttackCar::GameOver(void) {
	
	CObjectPlayer::GameOver();
}

//=============================================================================
// �v���C���[�̍Ō�̈ʒu���W�̎擾
//=============================================================================
D3DXVECTOR3 CObjectPlayerAttackCar::GetLastPos(void) {
	return m_lastPos;
}

//=============================================================================
// �v���C���[�̈ړ��ʂ̐ݒ�
//=============================================================================
void CObjectPlayerAttackCar::SetMove(D3DXVECTOR3 move) { m_move = move; }

//=============================================================================
// �v���C���[�̈ړ��ʂ̎擾
//=============================================================================
D3DXVECTOR3 CObjectPlayerAttackCar::GetMove(void) { return m_move; }

//=============================================================================
// �v���C���[�̓����蔻��̔��a�̎擾
//=============================================================================
float CObjectPlayerAttackCar::GetRadius(void) {
	return COLLISION_RADIUS;
}

//=============================================================================
// �ړ�
//=============================================================================
void CObjectPlayerAttackCar::Move(CInput* pInput, float fRotCameraY) {
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

	if (!m_bAttack)
	{
		//A�{�^���������Ă���Ԍ����Ă�������ɐi��
		if (pInput->GetPress(CInput::CODE::ACCELE, GetPlayer()->GetIndex() - 1))
		{
			//����������
			m_fMoveSpeed += ATTACK_CAR_ADD_MOVE_SPEED;
			//�ő�l�����傫���Ȃ�����
			if (m_fMoveSpeed > ATTACK_CAR_MAX_MOVE_SPEED)
			{
				m_fMoveSpeed = ATTACK_CAR_MAX_MOVE_SPEED;
			}
			//---------------------------------
			//��
			CPresetEffect::SetEffect3D(0, GetPos(), {}, {});
			//---------------------------------
		}
		else if (pInput->GetPress(CInput::CODE::REVERSE, GetPlayer()->GetIndex() - 1))
		{//B�{�^������������
		 //����������
			m_fMoveSpeed -= ATTACK_CAR_ADD_MOVE_SPEED;
			//�ő�l�����傫���Ȃ�����
			if (m_fMoveSpeed < -ATTACK_CAR_MAX_MOVE_SPEED)
			{
				m_fMoveSpeed = -ATTACK_CAR_MAX_MOVE_SPEED;
			}
		}
		else
		{
			//����
			DecMove();
		}
	}
	else
	{
		//����
		DecMove();
	}

	//����
	DecBoundMove();

	//�A�^�b�N����
	Attack();

	//�ړ��ʐݒ�
	m_move.x = sinf(GetRot().y + D3DX_PI) * m_fMoveSpeed;
	m_move.z = cosf(GetRot().y + D3DX_PI) * m_fMoveSpeed;

	//�A�^�b�N��ԂȂ�
	if (m_bAttack)
	{
		return;
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

		D3DXVECTOR3 rotObjectPlayer = CObjectModel::GetRot();//�p�x�̎擾
		float fdeltaRot;	//�p�x�̍���
		//���݂̊p�x�ƖڕW�̊p�x�̍����̌v�Z
		if (m_destRot.y >= 0.0f) {
			if (rotObjectPlayer.y >= 0.0f) {
				fdeltaRot = m_destRot.y - rotObjectPlayer.y;
			}
			else if (rotObjectPlayer.y < 0.0f) {
				if (m_destRot.y - rotObjectPlayer.y >= D3DX_PI) {
					fdeltaRot = -D3DX_PI - rotObjectPlayer.y - D3DX_PI + m_destRot.y;
				}
				else if (m_destRot.y - rotObjectPlayer.y < D3DX_PI) {
					fdeltaRot = m_destRot.y - rotObjectPlayer.y;
				}
			}
		}
		else if (m_destRot.y < 0.0f) {
			if (rotObjectPlayer.y >= 0.0f) {
				if (rotObjectPlayer.y - m_destRot.y >= D3DX_PI) {
					fdeltaRot = D3DX_PI - rotObjectPlayer.y + D3DX_PI + m_destRot.y;
				}
				else if (rotObjectPlayer.y - m_destRot.y < D3DX_PI) {
					fdeltaRot = m_destRot.y - rotObjectPlayer.y;
				}
			}
			else if (rotObjectPlayer.y < 0.0f) {
				fdeltaRot = m_destRot.y - rotObjectPlayer.y;
			}
		}

		//��]�̔��f
		rotObjectPlayer.y += fdeltaRot * ATTACK_CAR_ROTATE_SPEED * (m_fMoveSpeed / 8.0f);

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
void CObjectPlayerAttackCar::DecMove(void) {
	//����
	m_fMoveSpeed *= ATTACK_CAR_DEC_MOVE_SPEED;

	//����̒l�̌덷�ɂȂ�����
	if (m_fMoveSpeed < ATTACK_CAR_MOVE_ZERO_RANGE && m_fMoveSpeed > -ATTACK_CAR_MOVE_ZERO_RANGE)
	{
		//�ړ��ʂ�0�ɂ���
		m_fMoveSpeed = 0.0f;

		//�A�^�b�N���Ă��Ȃ���ԂȂ�
		if (!m_bAttack)
		{
			return;
		}

		//�A�^�b�N���Ă��Ȃ���Ԃɂ���
		m_bAttack = false;
	}
}

//=============================================================================
//�o�E���h�ړ��ʂ̌���
//=============================================================================
void CObjectPlayerAttackCar::DecBoundMove(void)
{
	//����
	m_boundMove *= ATTACK_CAR_BOUND_DEC;

	//����̒l�̌덷�ɂȂ�����
	if (m_boundMove.x < ATTACK_CAR_MOVE_ZERO_RANGE && m_boundMove.x > -ATTACK_CAR_MOVE_ZERO_RANGE,
		m_boundMove.z < ATTACK_CAR_MOVE_ZERO_RANGE && m_boundMove.z > -ATTACK_CAR_MOVE_ZERO_RANGE)
	{
		//�ړ��ʂ�0�ɂ���
		m_boundMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
//�A�^�b�N����
//=============================================================================
void CObjectPlayerAttackCar::Attack(void)
{
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	CInput* pInput = nullptr;
	if (pManager != nullptr) {
		//���݂̓��̓f�o�C�X�̎擾
		pInput = pManager->GetInputCur();
	}

	//�{�^������������
	if (pInput->GetTrigger(CInput::CODE::CAR_ATTACK, GetPlayer()->GetIndex() - 1))
	{
		//�A�^�b�N���Ă����ԂȂ�
		if (m_bAttack)
		{
			return;
		}

		//�A�^�b�N���Ă����Ԃɂ���
		m_bAttack = true;
		//�ړ��ʐݒ�
		m_fMoveSpeed = ATTACK_CAR_ATTACK_MOVE_SPEED;
	}
}

//=============================================================================
//�d�͏���
//=============================================================================
void CObjectPlayerAttackCar::Gravity(void)
{
	//�d�͉��Z
	m_move.y -= ATTACK_CAR_GRAVITY;

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//������0�ɂ���
	pos.y = 0.0f;

	//�X�e�[�W�̒��S����v���C���[�܂ł̋������Z�o
	float fDiffer = D3DXVec3Length(&pos);

	//�X�e�[�W�O�ɏo����
	if (fDiffer - GetRadius() > GAME_02_STAGE_SIZE)
	{
		//����
		DecMove();

		//�����L���O���ݒ肳��Ă��Ȃ�������
		if (GetPlayer()->GetRanking() == 0)
		{
			//�����L���O�ݒ�
			GetPlayer()->SetRanking();

			//�}�l�[�W���[�̎擾
			CManager* pManager = CManager::GetManager();
			//�T�E���h�̎擾
			CSound* pSound = nullptr;
			if (pManager != nullptr) pSound = pManager->GetSound();
			//�T�E���h���Đ�
			pSound->PlaySound(CSound::SOUND_LABEL::SE_FALL);
		}

		return;
	}

	//�d�͂�0�ɂ���
	m_move.y = 0.0f;
}

//=============================================================================
// �����蔻��
//=============================================================================
void CObjectPlayerAttackCar::Collision(D3DXVECTOR3& pos) {

	//�����Ă���Ȃ�
	if (GetPos().y < 0.0f)
	{
		return;
	}

	//�v���C���[�Ƃ̓����蔻��
	CollisionObjectPlayer();
}

//=============================================================================
//�v���C���[�Ƃ̓����蔻��
//=============================================================================
void CObjectPlayerAttackCar::CollisionObjectPlayer(void)
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
		CObjectPlayerAttackCar *pObjectPlayer = static_cast<CObjectPlayerAttackCar*> (pObject);

		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 playerPos = pObjectPlayer->GetPos();

		//�����Ă�����
		if (playerPos.y < 0.0f)
		{
			pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
			continue;
		}

		D3DXVECTOR3 myPos = GetPos();

		//��_�̋����x�N�g��
		D3DXVECTOR2 differVec = D3DXVECTOR2(playerPos.x - myPos.x, playerPos.z - myPos.z);
		//��_�̋���
		float fDiffer = D3DXVec2Length(&differVec);

		//�������Ă�����
		if (fDiffer <= COLLISION_RADIUS * 2.0f)
		{
			//�O�̃t���[���������Ă��Ȃ�������
			if (!m_bCollOld[pObjectPlayer->GetPlayer()->GetIndex() - 1])
			{
				//�}�l�[�W���[�̎擾
				CManager* pManager = CManager::GetManager();
				//�T�E���h�̎擾
				CSound* pSound = nullptr;
				if (pManager != nullptr) pSound = pManager->GetSound();
				//�T�E���h���Đ�
				pSound->PlaySound(CSound::SOUND_LABEL::SE_CRASH);
			}

			//���g�ƑΏۂ̃I�u�W�F�N�g�̊p�x�����߂�
			float fRot = atan2((playerPos.x - myPos.x), (playerPos.z - myPos.z));
			//����̈ʒu�������o��
			playerPos.x = myPos.x + (sinf(fRot) * (COLLISION_RADIUS * 2.0f));
			playerPos.z = myPos.z + (cosf(fRot) * (COLLISION_RADIUS * 2.0f));
			//�ʒu�ݒ�
			pObjectPlayer->SetPos(playerPos);

			//�ړ��ʂ��}�C�i�X�Ȃ�
			if (m_fMoveSpeed < 0)
			{
				//�t�����ɂ���
				fRot += D3DX_PI;
			}


			float fBoundPlayer = ATTACK_CAR_NORMAL_MY_BOUND;
			float fBoundEnemy = ATTACK_CAR_NORMAL_ENEMY_BOUND;

			if (m_bAttack)
			{
				fBoundPlayer = ATTACK_CAR_ATTACK_MY_BOUND;
				fBoundEnemy = ATTACK_CAR_ATTACK_ENEMY_BOUND;
			}

			//����̃o�E���h�ړ��ʎ擾
			D3DXVECTOR3 move = pObjectPlayer->GetBoundMove();
			//���˕Ԃ�����
			move.x += sinf(fRot) * m_fMoveSpeed * fBoundEnemy;
			move.z += cosf(fRot) * m_fMoveSpeed * fBoundEnemy;
			//����̃o�E���h�ړ��ʐݒ�
			pObjectPlayer->SetBoundMove(move);

			//���g�����˕Ԃ�����
			m_boundMove.x += sinf(fRot + D3DX_PI) * m_fMoveSpeed * fBoundPlayer;
			m_boundMove.z += cosf(fRot + D3DX_PI) * m_fMoveSpeed * fBoundPlayer;

			m_fMoveSpeed = 0.0f;

			//����������Ԃɂ���
			m_bCollOld[pObjectPlayer->GetPlayer()->GetIndex() - 1] = true;

			//�Փ˃G�t�F�N�g
			CPresetDelaySet::Create(1, playerPos);

			return;
		}
		else
		{
			//����������Ԃɂ���
			m_bCollOld[pObjectPlayer->GetPlayer()->GetIndex() - 1] = false;
		}
		pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
	}
}