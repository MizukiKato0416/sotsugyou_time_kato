//=======================================================================
//�J�����Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MAX_CAMERA					(1)									//�J�����̍ő吔
#define MAX_MAIN_CAMERA				(1)									//���C���J�����̍ő吔
#define CAMERA_DISTANCE				(500.0f)							//���_�ƒ����_�̋���
#define CAMERA_DISTANCE_DEFAULT		(700.0f)							//�f�t�H���g�̎��_�ƒ����_�̋���
#define CAMERA_INIT_ROT_X			(1.5f)								//�J�����̌���X
#define CAMERA_INIT_POS				(D3DXVECTOR3(0.0f, 0.0f, 0.0f))		//�J�����̏����ʒu
#define CAMERA_DEFAULT_POS			(D3DXVECTOR3(0.0f, 200.0f, 0.0f))	//�J�����̃f�t�H���g�ʒu
#define CAMERA_MAX_POS				(D3DXVECTOR3(0.0f, 350.0f, 0.0f))	//�J�����̍ő�ʒu

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CCamera
{
public:
	//�����o�֐�
	CCamera();				//�R���X�g���N�^
	~CCamera();				//�f�X�g���N�^

	HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const float &viewportX, const float &viewportY, const float &viewportWidth, const float &viewporHeight);
	void Uninit(void);
	void Update(void);
	static CCamera *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const float &viewportX, const float &viewportY, const float &viewportWidth, const float &viewporHeight);
	void Set(void);

	D3DXVECTOR3 GetPosV(void);					//���_�擾����
	D3DXVECTOR3 GetPosR(void);					//�����_�擾����
	void SetPosV(const D3DXVECTOR3 &pos);		//���_�ݒ菈��
	void SetPosR(const D3DXVECTOR3 &pos);		//�����_�ݒ菈��
	D3DXVECTOR3 GetRotV(void);					//���_�̌����擾����
	void SetRotV(const D3DXVECTOR3 &rot);		//���_�̌����ݒ菈��
	void SetNum(const int &nNum);				//camera�̌̎��ʔԍ��ݒ菈��
	int GetNum(void);							//camera�̌̎��ʔԍ��擾����
	//�r���[�|�[�g�擾����
	D3DVIEWPORT9 *GetViewPort(void) { return &m_viewport; }
	//�r���[�}�g���b�N�X�擾����
	D3DXMATRIX GetViewMtx(void) { return m_mtxView; }
	//�v���W�F�N�V�����}�g���b�N�X�擾����
	D3DXMATRIX GetPrjMtx(void) { return m_mtxProjection; }
	//���_�ƒ����_�̋������Z����
	void AddDiffer(const float fAddDiffer) { m_fDifferVR += fAddDiffer; }
	//���_�ƒ����_�̋����ݒ菈��
	void SetDiffer(const float fDiffer) { m_fDifferVR = fDiffer; }
	//���_�ƒ����_�̋����擾����
	float GetDiffer(void) { return m_fDifferVR; }
	//�ړI�̌����ݒ菈��
	void SetRotAsk(const D3DXVECTOR3 rotAsk) { m_rotAsk = rotAsk; }
	//�J������X����]�����邩�ǂ����ݒ菈��
	void SetRotateX(const bool bRotateX) { m_bRotateX = bRotateX; }
	//�J������Y����]�����邩�ǂ����ݒ菈��
	void SetRotateY(const bool bRotateY) { m_bRotateY = bRotateY; }

private:
	//�����o�֐�
	void Rotate(void);						//��]����
	void MainCameraUpdate(void);			//���C���J�����̍X�V����
	void Move(void);						//��������

	D3DXVECTOR3 m_posV;						//���݂̎��_
	D3DXVECTOR3 m_posVDest;					//�ړI�̎��_
	D3DXVECTOR3 m_posR;						//���݂̒����_
	D3DXVECTOR3 m_posRDest;					//�ړI�̒����_
	D3DXVECTOR3 m_vecU;						//������x�N�g��
	D3DXVECTOR3 m_rot;						//���_�̌���
	D3DXVECTOR3 m_rotAsk;					//�ړI�̌���
	D3DXVECTOR3 m_numRot;					//������ς����
	float m_rotDiffer;						//�ړI�̌����Ƃ̍�
	D3DXMATRIX m_mtxProjection;				//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;					//�r���[�}�g���b�N�X
	D3DVIEWPORT9 m_viewport;				//�r���[�|�[�g
	D3DXMATRIX m_mtxWorldCamera;			//���[���h�}�g���b�N�X
	bool m_bRotateX;						//�J����X������]�����ǂ���
	bool m_bRotateY;						//�J����Y������]�����ǂ���
	int m_nNum;								//camera�̌̎��ʔԍ�
	float m_fDifferVR;						//���_�ƒ����_�̋���
	float m_fMoveSpeed;						//�ړ���
};

#endif //!_CAMERA_H_

