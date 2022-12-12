//=============================================================================
//
// ���D�Q�[���p�ԏ��� [object_player_balloon_car.h]
// Author : ��������
//
//=============================================================================
#ifndef _OBJECT_PLAYER_BALLOON_CAR_H_
#define _OBJECT_PLAYER_BALLOON_CAR_H_

#include "object_player.h"
#include "item.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CObject2D;
class CWeapon;
class CInput;
class CScoreUi;

//*****************************************************************************
// �N���X
//*****************************************************************************
class CObjectPlayerBalloonCar : public CObjectPlayer
{
public:
	enum class OBJECT_PLAYER_BALLOON_CAR_STATE
	{
		NONE = 0,	//�Ȃ�
		NORMAL,		//�ʏ�
		INVINCIBLE,	//���G
		SPIN,		//�X�s��
		MAX
	};

	CObjectPlayerBalloonCar();	//�f�t�H���g�R���X�g���N�^
	~CObjectPlayerBalloonCar();	//�f�X�g���N�^

	static CObjectPlayerBalloonCar* Create(D3DXVECTOR3 pos);	//��������

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void GameOver(void);	//�Q�[���I�[�o�[���̏���
	D3DXVECTOR3 GetLastPos(void);	//�Ō�̈ʒu���W�̎擾
	void SetMove(D3DXVECTOR3 move);	//�ړ��ʂ̐ݒ�
	D3DXVECTOR3 GetMove(void);		//�ړ��ʂ̎擾
	float GetRadius(void);			//�����蔻��̔��a�̎擾

	//��Ԑݒ菈��
	void SetState(const OBJECT_PLAYER_BALLOON_CAR_STATE state) { m_state = state; }
	//��Ԏ擾����
	OBJECT_PLAYER_BALLOON_CAR_STATE GetState(void) { return m_state; }

	//�X�R�AUI�擾����
	CScoreUi *GetScoreUi(void) { return m_pSocreUi; }
	//�X�R�A��������
	void CreateScore();

	//�A�C�e��UI�̃t���[����������
	void CreateItemUiFrame();

	//�|�C���g�D����Ԃ��ǂ����ݒ菈��
	void SetStealPoint(const bool bStealPoint) { m_bStealPoint = bStealPoint; }
	//�|�C���g�D����Ԃ��ǂ����擾����
	bool SetStealPoint(void) { return m_bStealPoint; }

private:
	void Move(CInput* pInput, float fRotCameraY);	//�ړ�
	void DecMove(void);								//�ړ��ʂ̌���
	void DecBoundMove(void);						//�o�E���h���̈ړ��ʂ̌���
	void Collision(D3DXVECTOR3& pos);				//�����蔻��
	void CollisionObjectPlayer(void);				//�v���C���[�Ƃ̓����蔻��
	void StateBound(void);							//�o�E���h��Ԃ̏���
	void StateSpin(void);							//�X�s����Ԃ̏���
	void StateInvincble(void);						//���G��Ԃ̏���
	void UseItem(void);								//�A�C�e���g�p����
	void ItemUi(void);								//�A�C�e��Ui����
	void StealPoint(void);							//�|�C���g�D�揈��

	D3DXVECTOR3	m_lastPos;	//�Ō�̈ʒu���W
	D3DXVECTOR3 m_move;		//�ړ���

	float m_fMoveSpeed;							//�ړ����鑬��
	float m_fBoundMoveSpeed;					//���˕Ԃ�Ƃ��̑���
	float m_fSpinSpeed;							//�X�s���̃X�s�[�h
	OBJECT_PLAYER_BALLOON_CAR_STATE m_state;	//���
	bool m_bBound;								//�o�E���h���邩�ǂ���
	bool m_bStealPoint;							//�|�C���g��D����Ԃ��ǂ���
		
	int m_nSpinCounter;				//�X�s�����鎞�Ԃ̃J�E���^�[
	int m_nInvincbleCounter;		//���G���Ԃ̃J�E���^�[
	int m_nStealPointCounter;		//�|�C���g��D�����Ԃ̃J�E���^�[

	CScoreUi *m_pSocreUi;			//�X�R�A�̃|�C���^
	CObject2D *m_pItemUi;			//�A�C�e����UI
};

#endif // !_OBJECT_PLAYER_BALLOON_CAR_H_