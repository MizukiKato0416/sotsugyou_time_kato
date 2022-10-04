//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "objectModel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

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

private:
	void Move(CInput* pInput, float fRotCameraY);	//�ړ�
	void DecMove(void);	//�ړ��ʂ̌���
	void Collision(D3DXVECTOR3& pos);	//�����蔻��

	D3DXVECTOR3	m_lastPos;	//�Ō�̈ʒu���W
	D3DXVECTOR3 m_destRot;	//�ڕW�̊p�x
	D3DXVECTOR3 m_move;		//�ړ���

	int m_nCntGameover;		//�Q�[���I�[�o�[��̃J�E���g
};

#endif // !_PLAYER_H_