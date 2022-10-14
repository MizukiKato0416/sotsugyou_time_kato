//=======================================================================
//���C�g�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MAX_LIGHT (3)	//���C�g�̍ő吔

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CLight
{
public:
	CLight();					//�R���X�g���N�^
	~CLight();					//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 vecDir, const D3DXVECTOR3 &pos);
	void Uninit(void);
	void Update(void);
	static CLight *Create(const D3DXVECTOR3 &vecDir, const D3DXVECTOR3 &pos);


private:
	D3DLIGHT9 m_light;			//���C�g
	int m_nCnt;					//���Ԗڂ̃��C�g��
	static int m_nNum;			//���C�g�̑���
};

#endif //!_LIGHT_H_