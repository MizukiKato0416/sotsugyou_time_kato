//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "objectModel.h"
#include "item.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER_NUM	(4)		//�v���C���[�̍ő吔

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CObject2D;
class CWeapon;
class CInput;

//*****************************************************************************
// �v���C���[�N���X
//*****************************************************************************
class CPlayer : public CObjectModel
{
public:
	enum class PLAYER_STATE
	{
		NONE = 0,	//�Ȃ�
		NOMAL,		//�ʏ�
		BOUND,		//�o�E���h
		SPIN,		//�X�s��
		MAX
	};

	CPlayer();	//�f�t�H���g�R���X�g���N�^
	~CPlayer();	//�f�X�g���N�^

	static CPlayer* Create(D3DXVECTOR3 pos);	//��������

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void GameOver(void);	//�Q�[���I�[�o�[���̏���
	void GetCollisionInfo(int nIdxColParts, int* const pNumCol, D3DXVECTOR3** const ppPosColArray, float* const pRadiusCol);	//�����蔻��̏��̎擾
	D3DXVECTOR3 GetLastPos(void);	//�Ō�̈ʒu���W�̎擾
	void SetMove(D3DXVECTOR3 move);	//�ړ��ʂ̐ݒ�
	D3DXVECTOR3 GetMove(void);		//�ړ��ʂ̎擾
	float GetRadius(void);			//�����蔻��̔��a�̎擾
	//��Ԑݒ菈��
	void SetState(const PLAYER_STATE state) { m_state = state; }
	//��Ԏ擾����
	PLAYER_STATE GetState(void) { return m_state; }
	//�v���C���[�ԍ��ݒ菈��
	void SetIndex(const int nIndex) { m_nIndex = nIndex; }
	//�v���C���[�ԍ��擾����
	int GetIndex(void) { return m_nIndex; }
	//�v���C���[�̑����擾����
	static int GetNum(void) { return m_nPlayerNum; }
	//�A�C�e���^�C�v�擾����
	CItem::ITEM_TYPE GetItemType(void) { return m_itemType; }
	//�A�C�e���^�C�v�ݒ菈��
	void SetItemType(CItem::ITEM_TYPE itemType) { m_itemType = itemType; }

private:
	void Move(CInput* pInput, float fRotCameraY);	//�ړ�
	void DecMove(void);	//�ړ��ʂ̌���
	void DecBoundMove(void);	//�o�E���h���̈ړ��ʂ̌���
	void Collision(D3DXVECTOR3& pos);	//�����蔻��
	void CollisionPlayer(void);	//�v���C���[�Ƃ̓����蔻��
	void StateBound(void);				//�o�E���h��Ԃ̏���

	D3DXVECTOR3	m_lastPos;	//�Ō�̈ʒu���W
	D3DXVECTOR3 m_destRot;	//�ڕW�̊p�x
	D3DXVECTOR3 m_move;		//�ړ���

	static int m_nPlayerNum;		//�v���C���[�̐�
	int m_nIndex;					//�v���C���[�ԍ�
	int m_nCntGameover;				//�Q�[���I�[�o�[��̃J�E���g
	float m_fMoveSpeed;				//�ړ����鑬��
	float m_fBoundMoveSpeed;		//���˕Ԃ�Ƃ��̑���
	PLAYER_STATE m_state;			//���
	CItem::ITEM_TYPE m_itemType;	//�A�C�e���̎��
};

#endif // !_PLAYER_H_