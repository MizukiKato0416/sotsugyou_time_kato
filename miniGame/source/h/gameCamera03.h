//=============================================================================
//
// �Q�[���J����03���� [gameCamera03.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _GAMECAMERA03_H_
#define _GAMECAMERA03_H_

#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �Q�[���J����03�N���X
//*****************************************************************************
class CGameCamera03 : public CCamera
{
public:
	CGameCamera03();		//�f�t�H���g�R���X�g���N�^
	~CGameCamera03();	//�f�X�g���N�^
	static CGameCamera03* Create(void);	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����

	void OverLook(float fMinPos, float fMaxPos);	//���n��

private:
	bool m_bOverLook;
	D3DXVECTOR3 m_destPos;	//�J�����̖ڕW�ʒu
	float m_fSpeedMovePos;	//�J�����̖ڕW�ʒu�ւ̈ړ����x
	float m_fDestDist;		//�J�����̖ڕW����
	float m_fSpeedDist;		//�J�����̖ڕW�����ւ̈ړ����x
};

#endif // !_GAMECAMERA03_H_