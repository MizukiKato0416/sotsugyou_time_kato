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
#include "gameScene.h"

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
#define ATTACK_CAR_NORMAL_MY_BOUND			(1.8f)		//����ɓ��������Ƃ����g�����˕Ԃ�ʂ̔{��
#define ATTACK_CAR_NORMAL_MY_BOUND_WOLF		(0.6f)		//����ɓ��������Ƃ����g�����˕Ԃ�ʂ̔{��(�l�T)
#define ATTACK_CAR_NORMAL_ENEMY_BOUND		(3.0f)		//����ɓ��������Ƃ����肪���˕Ԃ�ʂ̔{��
#define ATTACK_CAR_NORMAL_ENEMY_BOUND_WOLF	(1.5f)		//����ɓ��������Ƃ����肪���˕Ԃ�ʂ̔{��(�l�T)
#define ATTACK_CAR_ATTACK_MY_BOUND			(1.0f)		//�A�^�b�N��Ԃ̎��ɑ���ɓ��������Ƃ����g�����˕Ԃ�ʂ̔{��
#define ATTACK_CAR_ATTACK_MY_BOUND_WOLF		(0.5f)		//�A�^�b�N��Ԃ̎��ɑ���ɓ��������Ƃ����g�����˕Ԃ�ʂ̔{��(�l�T)
#define ATTACK_CAR_ATTACK_ENEMY_BOUND		(1.5f)		//�A�^�b�N��Ԃ̎��ɑ���ɓ��������Ƃ����肪���˕Ԃ�ʂ̔{��
#define ATTACK_CAR_ATTACK_ENEMY_BOUND_WOLF	(0.7f)		//�A�^�b�N��Ԃ̎��ɑ���ɓ��������Ƃ����肪���˕Ԃ�ʂ̔{��(�l�T)
#define ATTACK_CAR_BOUND_DEC				(0.9f)		//�o�E���h�̈ړ��ʌ�����
#define ATTACK_CAR_BOUND_MIN_SPEED			(2.0f)		//�o�E���h����̂ɕK�v�ȍŏ��ړ���

//--------------------------------
//���̑�
//--------------------------------
#define ATTACK_CAR_GRAVITY				(0.5f)		//�d��
#define ATTACK_CAR_DEFENCE_COUNT		(300)		//�f�B�t�F���X��Ԃ̎���

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObjectPlayerAttackCar::CObjectPlayerAttackCar()
{
	SetObjType(OBJTYPE_PLAYER);						//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);		//�X�V���̐ݒ�
	SetDrawPriority(DRAW_PRIORITY::CHARA);			//�`�揇�̐ݒ�

	m_lastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_boundMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fMoveSpeed = 0.0f;
	m_bAttack = false;
	memset(m_bCollOld, false, sizeof(m_bCollOld[MAX_OBJECT_PLAYER_NUM]));

	m_nDefenceCounter = 0;
	m_bDefence = false;
	m_nFallEffectCounter = 0;

	m_pChangeColor = nullptr;
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
	m_fMoveSpeed = 0.0f;
	m_boundMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bAttack = false;
	memset(m_bCollOld, FALSE, sizeof(m_bCollOld[MAX_OBJECT_PLAYER_NUM]));
	m_nDefenceCounter = 0;
	m_bDefence = false;
	m_nFallEffectCounter = 0;

	return S_OK;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CObjectPlayerAttackCar::Uninit(void) {
	//�ύX����F�̃N���X�̔j��
	if (m_pChangeColor != nullptr) {
		m_pChangeColor->Uninit();
		delete m_pChangeColor;
		m_pChangeColor = nullptr;
	}

	CObjectPlayer::Uninit();
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void CObjectPlayerAttackCar::Update(void) {

	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();

	CInput* pInput = nullptr;
	CSound *pSound = nullptr;
	CCamera* pCamera = nullptr;
	CGameScene* pGame = nullptr;

	//----------------------------
	//�J�����̐ݒ�
	//----------------------------
	float fRotCameraY = 0.0f;	//�J�����̊p�x
	if (pCamera != nullptr) {
		fRotCameraY = pCamera->GetRot().y;	//�J�����̊p�x���擾
	}

	//�X�V���Ȃ��ݒ�Ȃ�
	if (!GetPlayer()->GetUpdate())
	{
		//����
		DecBoundMove();

		//����
		DecMove();

		//�ړ��ʐݒ�
		m_move.x = sinf(GetRot().y + D3DX_PI) * m_fMoveSpeed;
		m_move.z = cosf(GetRot().y + D3DX_PI) * m_fMoveSpeed;

		//�d�͏���
		Gravity();

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

		if (GetPos().y > -1000.0f && GetPos().y < -200.0f)
		{
			m_nFallEffectCounter++;

			if (m_nFallEffectCounter == 5)
			{
				//m_nFallEffectCounter = 0;
				//�����G�t�F�N�g
				CPresetDelaySet::Create(3, GetPos(),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f, fRotCameraY,0.0f));
			}
		}

		CObjectPlayer::Update();

		return;
	}

	//�f�B�t�F���X��
	if (m_bDefence) {
		CModel* pModel = GetPtrModel();	//���f���̎擾
		//�F�̕ύX
		if (m_pChangeColor != nullptr && pModel != nullptr) {
			m_pChangeColor->Update();
			D3DXCOLOR col = m_pChangeColor->GetColor();
			pModel->SetMaterialDiffuse(col, 0);
		}
	}

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

	//�f�B�t�F���X��ԏ���
	Defence();

	//----------------------------
	//�����蔻��
	//----------------------------
	Collision(posObjectPlayer);

	if (GetPos().y > -1000.0f && GetPos().y < -200.0f)
	{
		m_nFallEffectCounter++;

		if (m_nFallEffectCounter == 5)
		{
			//m_nFallEffectCounter = 0;
			//�����G�t�F�N�g
			CPresetDelaySet::Create(3, GetPos(),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, fRotCameraY, 0.0f));

		}
	}

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
		rotObjectPlayer.y += fdeltaRot * ATTACK_CAR_ROTATE_SPEED * (fabsf(m_fMoveSpeed) / 8.0f);

		//�p�C���ߎ�
		if (rotObjectPlayer.y > D3DX_PI) {
			rotObjectPlayer.y -= D3DX_PI * 2;
		}
		else if (rotObjectPlayer.y < -D3DX_PI) {
			rotObjectPlayer.y += D3DX_PI * 2;
		}

		//�p�x�̐ݒ�
		CObjectModel::SetRot(rotObjectPlayer);
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

		//�A�^�b�N���Ă����ԂȂ�
		if (m_bAttack && m_boundMove.x == 0.0f && m_boundMove.y == 0.0f && m_boundMove.z == 0.0f)
		{
			//�A�^�b�N���Ă��Ȃ���Ԃɂ���
			m_bAttack = false;
		}
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
//�A�^�b�N����
//=============================================================================
void CObjectPlayerAttackCar::Defence(void)
{
	//�f�B�t�F���X��ԂłȂ��Ƃ�
	if (!m_bDefence)
	{
		return;
	}

	m_nDefenceCounter++;

	//��莞�Ԃ�������
	if (m_nDefenceCounter > ATTACK_CAR_DEFENCE_COUNT)
	{
		//�f�B�t�F���X��Ԃ���߂�
		m_nDefenceCounter = 0;
		m_bDefence = false;
		//�ύX����F�̃N���X�̔j��
		if (m_pChangeColor != nullptr) {
			m_pChangeColor->Uninit();
			delete m_pChangeColor;
			m_pChangeColor = nullptr;
		}
		//�f�t�H���g�̐F�ɖ߂�
		D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//�v���C���[�ԍ��ɂ���ĐF��ς���
		switch (GetPlayer()->GetIndex())
		{
		case 1:
			col = OBJECT_PLAYER_COLOR_1P;
			break;
		case 2:
			col = OBJECT_PLAYER_COLOR_2P;
			break;
		case 3:
			col = OBJECT_PLAYER_COLOR_3P;
			break;
		case 4:
			col = OBJECT_PLAYER_COLOR_4P;
			break;
		}

		//���f���擾
		CModel *pModel = GetPtrModel();
		if (pModel != nullptr)
		{
			//�w�肵���}�e���A���̐F��ݒ�
			pModel->SetMaterialDiffuse(col, 0);
		}
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
		//�����L���O�ݒ菈��
		SetRanking();

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

			//�ړ��ʂ����Ȃ�������
			if (m_fMoveSpeed < ATTACK_CAR_BOUND_MIN_SPEED && m_fMoveSpeed > -ATTACK_CAR_BOUND_MIN_SPEED)
			{
				return;
			}

			//�o�E���h�����
			float fBoundPlayer = ATTACK_CAR_NORMAL_MY_BOUND;
			float fBoundEnemy = ATTACK_CAR_NORMAL_ENEMY_BOUND;

			//�A�^�b�N��ԂȂ�
			if (m_bAttack)
			{
				fBoundPlayer = ATTACK_CAR_ATTACK_MY_BOUND;
				fBoundEnemy = ATTACK_CAR_ATTACK_ENEMY_BOUND;
			}


			//�f�B�t�F���X���Ă����ԂȂ�
			if (m_bDefence)
			{
				fBoundPlayer = ATTACK_CAR_NORMAL_MY_BOUND_WOLF;

				//�A�^�b�N��ԂȂ�
				if (m_bAttack)
				{
					fBoundPlayer = ATTACK_CAR_ATTACK_MY_BOUND_WOLF;
				}
			}
			else
			{
				//�A�^�b�N��ԂȂ�
				if (m_bAttack)
				{
					fBoundPlayer = ATTACK_CAR_ATTACK_MY_BOUND;
				}
			}

			//���肪�f�B�t�F���X���Ă����ԂȂ�
			if (pObjectPlayer->m_bDefence)
			{
				fBoundEnemy = ATTACK_CAR_NORMAL_ENEMY_BOUND_WOLF;

				//�A�^�b�N��ԂȂ�
				if (m_bAttack)
				{
					fBoundEnemy = ATTACK_CAR_ATTACK_ENEMY_BOUND_WOLF;
				}
			}
			else
			{
				//�A�^�b�N��ԂȂ�
				if (m_bAttack)
				{
					fBoundEnemy = ATTACK_CAR_ATTACK_ENEMY_BOUND;
				}
			}

			//����̃o�E���h�ړ��ʎ擾
			D3DXVECTOR3 move = pObjectPlayer->GetBoundMove();

			float fMoveSpeed = m_fMoveSpeed;
			//�������l�T�������犎�A�^�b�N��ԂȂ�
			if (CGameScene::GetWereWolfMode() && CGameScene::GetWereWolfPlayerIndex() == GetPlayer()->GetIndex() && m_bAttack)
			{
				//������΂��ʂ���ɍő�ɂ���
				fMoveSpeed = ATTACK_CAR_ATTACK_MOVE_SPEED /* * 1.1f*/;
			}

			//���˕Ԃ�����
			move.x += sinf(fRot) * fMoveSpeed * fBoundEnemy;
			move.z += cosf(fRot) * fMoveSpeed * fBoundEnemy;
			//����̃o�E���h�ړ��ʐݒ�
			pObjectPlayer->SetBoundMove(move);

			//���g�����˕Ԃ�����
			m_boundMove.x += sinf(fRot + D3DX_PI) * m_fMoveSpeed * fBoundPlayer;
			m_boundMove.z += cosf(fRot + D3DX_PI) * m_fMoveSpeed * fBoundPlayer;

			m_fMoveSpeed = 0.0f;

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

			//����������Ԃɂ���
			m_bCollOld[pObjectPlayer->GetPlayer()->GetIndex() - 1] = true;

			//�Փ˃G�t�F�N�g
			CPresetDelaySet::Create(1, playerPos, {}, {});

			//�}�l�[�W���[�̎擾
			CManager* pManager = CManager::GetManager();
			CInput* pInput = nullptr;
			CInputGamepadX *pPadX = nullptr;
			if (pManager != nullptr) {
				//���݂̓��̓f�o�C�X�̎擾
				pInput = pManager->GetInputCur();
				pPadX = dynamic_cast<CInputGamepadX*>(pInput);
			}

			if (pPadX != nullptr)
			{
				//�U��������
				pPadX->SetVibration(65535, 65535, 15, GetPlayer()->GetIndex() - 1);
				pPadX->SetVibration(65535, 65535, 15, pObjectPlayer->GetPlayer()->GetIndex() - 1);
			}

			return;
		}
		else
		{
			//�������Ă��Ȃ���Ԃɂ���
			m_bCollOld[pObjectPlayer->GetPlayer()->GetIndex() - 1] = false;
		}
		pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
	}
}

//=============================================================================
//�����L���O�ݒ菈��
//=============================================================================
void CObjectPlayerAttackCar::SetRanking()
{
	//�����L���O���ݒ肳��Ă�����
	if (CGameScene::GetRanking(GetPlayer()->GetIndex() - 1) != 0)
	{
		return;
	}

	//�}�l�[�W���[�̎擾
	CManager *pManager = CManager::GetManager();
	if (pManager == nullptr) {
		return;
	}

	//�Q�[���V�[���̎擾
	CGameScene *pGameScene = pManager->GetGameScene();
	if (pGameScene == nullptr) {
		return;
	}

	//�L���X�g
	CGameScene02 *pGameScene02 = dynamic_cast<CGameScene02*>(pGameScene);
	if (pGameScene02 == nullptr) {
		return;
	}

	//�����L���O�ݒ�
	CGameScene::SetRanking(pGameScene02->GetSavePlayerNum(), GetPlayer()->GetIndex() - 1);
	//�����c�����l�������炷
	pGameScene02->AddSavePlayerNum(-1);

	//�T�E���h�̎擾
	CSound* pSound = nullptr;
	if (pManager != nullptr) pSound = pManager->GetSound();
	//�T�E���h���Đ�
	pSound->PlaySound(CSound::SOUND_LABEL::SE_FALL);
}

//�f�B�t�F���X��Ԑݒ菈��
void CObjectPlayerAttackCar::SetDefence(const bool bDefence) {
	m_bDefence = bDefence;
	if (m_pChangeColor == nullptr) {
		m_pChangeColor = CChangeColor::Create(D3DXCOLOR(1.0f, 0.5f, 0.3f, 1.0f), 2.0f);
	}
}