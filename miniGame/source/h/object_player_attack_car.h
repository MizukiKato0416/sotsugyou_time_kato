//=============================================================================
//
// �Փ˃Q�[���p�ԏ��� [object_player_attack_car.h]
// Author : ��������
//
//=============================================================================
#ifndef _OBJECT_PLAYER_ATTACK_CAR_H_
#define _OBJECT_PLAYER_ATTACK_CAR_H_

#include "object_player.h"
#include "item.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_OBJECT_PLAYER_ATTACK_CAR_NUM	(4)		//�v���C���[�̍ő吔

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CInput;

//*****************************************************************************
// �N���X
//*****************************************************************************
class CObjectPlayerAttackCar : public CObjectPlayer
{
public:
	CObjectPlayerAttackCar();	//�f�t�H���g�R���X�g���N�^
	~CObjectPlayerAttackCar();	//�f�X�g���N�^

	static CObjectPlayerAttackCar* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//��������

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void GameOver(void);	//�Q�[���I�[�o�[���̏���
	D3DXVECTOR3 GetLastPos(void);	//�Ō�̈ʒu���W�̎擾
	void SetMove(D3DXVECTOR3 move);	//�ړ��ʂ̐ݒ�
	D3DXVECTOR3 GetMove(void);		//�ړ��ʂ̎擾
	float GetRadius(void);			//�����蔻��̔��a�̎擾

	//�o�E���h�ړ��ʎ擾����
	D3DXVECTOR3 GetBoundMove() { return m_boundMove; }
	//�o�E���h�ړ��ʐݒ菈��
	void SetBoundMove(const D3DXVECTOR3 boundMove) { m_boundMove = boundMove; }

	//�f�B�t�F���X��Ԏ擾����
	bool GetDefence() { return m_bDefence; }
	//�f�B�t�F���X��Ԑݒ菈��
	void SetDefence(const bool bDefence) { m_bDefence = bDefence; }

	//�f�B�t�F���X�J�E���^�[�擾����
	int GetDefenceCounter() { return m_nDefenceCounter; }
	//�f�B�t�F���X�J�E���^�[�ݒ菈��
	void SetDefenceCounter(const int nDefenceCounter) { m_nDefenceCounter = nDefenceCounter; }
	//�����L���O�ݒ菈��
	void SetRanking();								

private:

	void Move(CInput* pInput, float fRotCameraY);	//�ړ�
	void DecMove(void);								//�ړ��ʂ̌���
	void DecBoundMove(void);						//�o�E���h�ړ��ʂ̌���
	void Attack(void);								//�A�^�b�N����
	void Defence(void);								//�f�B�t�F���X����
	void Gravity(void);								//�d�͏���
	void Collision(D3DXVECTOR3& pos);				//�����蔻��
	void CollisionObjectPlayer(void);				//�v���C���[�Ƃ̓����蔻��

	D3DXVECTOR3	m_lastPos;			//�Ō�̈ʒu���W
	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_boundMove;		//�o�E���h�ړ���
	float m_fMoveSpeed;				//�ړ����鑬��
	int m_nDefenceCounter;			//�f�B�t�F���X��Ԃ��J�E���g����p
	int m_nFallEffectCounter;		//������G�t�F�N�g�̐����J�E���^�[

	bool m_bAttack;									//�A�^�b�N���Ă��邩�ǂ���
	bool m_bCollOld[MAX_OBJECT_PLAYER_NUM];			//�O�̃t���[�������������ǂ���
	bool m_bDefence;								//�f�B�t�F���X��Ԃ��ǂ���
};

#endif // !_OBJECT_PLAYER_ATTACK_CAR_H_