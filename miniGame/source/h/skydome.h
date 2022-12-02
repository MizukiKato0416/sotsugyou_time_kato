//=============================================================================
//
// �h�[���̋�̏��� [skydome.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _SKY_DOME_H_
#define _SKY_DOME_H_

#include "main.h"
#include "meshdome.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �h�[���̋�N���X
//*****************************************************************************
class CSkyDome : public CMeshdome
{
public:
	CSkyDome();	//�f�t�H���g�R���X�g���N�^
	CSkyDome(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumXZ, int nNumY, float fRadius);	//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CSkyDome();	//�f�X�g���N�^
	static CSkyDome* Create(D3DXVECTOR3 pos, int nNumXZ, int nNumY, float fRadius, float fRotSpeed);	//��������
	static void CreateSphere(D3DXVECTOR3 pos, int nNumXZ, int nNumY, float fRadius, float fRotSpeed);	//����ɐ�������

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

private:

};

#endif // !_SKY_DOME_H_