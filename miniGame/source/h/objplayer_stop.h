//=============================================================================
//
// �~�܂�ԏ��� [objplayer_stop.h]
// Author : ��������
//
//=============================================================================
#ifndef _OBJPLAYER_STOP_H_
#define _OBJPLAYER_STOP_H_

#include "object_player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************

//*****************************************************************************
// �~�܂�ԃN���X
//*****************************************************************************
class CObjplayerStop : public CObjectPlayer
{
public:
	CObjplayerStop();	//�f�t�H���g�R���X�g���N�^
	CObjplayerStop(float fSpeedMax);	//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CObjplayerStop();	//�f�X�g���N�^

	static CObjplayerStop* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeedMax);	//��������

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void GameOver(void);	//�Q�[���I�[�o�[���̏���

	void SetCanStop(bool bCan) { m_bCanStop = bCan; }	//��~�\�ݒ�
	void StopMove(void);								//�ړ���~
	bool GetStopMove(void) { return m_bStopMove; }		//��~��Ԃ̎擾

private:
	//�����o�֐�
	void Move(void);		//�ړ�

	//�����o�ϐ�
	const float m_fSpeedMax;		//�ő呬�x
	D3DXVECTOR3 m_move;		//�ړ���
	bool m_bCanStop;		//��~�\
	bool m_bStopMove;		//��~�ς݂��ǂ���
};

#endif // !_OBJPLAYER_STOP_H_