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

private:

	void Move(CInput* pInput, float fRotCameraY);	//�ړ�
	void DecMove(void);								//�ړ��ʂ̌���
	void Collision(D3DXVECTOR3& pos);				//�����蔻��
	void CollisionObjectPlayer(void);				//�v���C���[�Ƃ̓����蔻��

	D3DXVECTOR3	m_lastPos;	//�Ō�̈ʒu���W
	D3DXVECTOR3 m_destRot;	//�ڕW�̊p�x
	D3DXVECTOR3 m_move;		//�ړ���

	float m_fMoveSpeed;				//�ړ����鑬��
};

#endif // !_OBJECT_PLAYER_ATTACK_CAR_H_