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
class CScore;

//*****************************************************************************
// �v���C���[�N���X
//*****************************************************************************
class CPlayer : public CObjectModel
{
public:
	enum class PLAYER_STATE
	{
		NONE = 0,	//�Ȃ�
		NORMAL,		//�ʏ�
		INVINCIBLE,	//���G
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

	//�X�V���邩�ǂ����擾����
	bool GetUpdate() { return m_bUpdate; }
	//�X�V���邩�ǂ����ݒ菈��
	void SetUpdate(const bool bUpdate) { m_bUpdate = bUpdate; }

	//�X�R�A�擾����
	CScore *GetScore(void) { return m_pSocre; }
	//�X�R�A��������
	void CreateScore();

private:
	void Move(CInput* pInput, float fRotCameraY);	//�ړ�
	void DecMove(void);								//�ړ��ʂ̌���
	void DecBoundMove(void);						//�o�E���h���̈ړ��ʂ̌���
	void Collision(D3DXVECTOR3& pos);				//�����蔻��
	void CollisionPlayer(void);						//�v���C���[�Ƃ̓����蔻��
	void StateBound(void);							//�o�E���h��Ԃ̏���
	void StateSpin(void);							//�X�s����Ԃ̏���
	void StateInvincble(void);						//���G��Ԃ̏���
	void UseItem(void);								//�A�C�e���g�p����

	D3DXVECTOR3	m_lastPos;	//�Ō�̈ʒu���W
	D3DXVECTOR3 m_destRot;	//�ڕW�̊p�x
	D3DXVECTOR3 m_move;		//�ړ���

	static int m_nPlayerNum;		//�v���C���[�̐�
	int m_nIndex;					//�v���C���[�ԍ�
	float m_fMoveSpeed;				//�ړ����鑬��
	float m_fBoundMoveSpeed;		//���˕Ԃ�Ƃ��̑���
	float m_fSpinSpeed;				//�X�s���̃X�s�[�h
	PLAYER_STATE m_state;			//���
	CItem::ITEM_TYPE m_itemType;	//�A�C�e���̎��
	bool m_bBound;					//�o�E���h���邩�ǂ���
	bool m_bUpdate;					//�X�V���������邩�ǂ���

	int m_nSpinCounter;				//�X�s�����鎞�Ԃ̃J�E���^�[
	int m_nInvincbleCounter;		//���G���Ԃ̃J�E���^�[

	CScore *m_pSocre;				//�X�R�A�̃|�C���^
};

#endif // !_PLAYER_H_