//===========================================
//3D�|���S������
//Author:��������
//===========================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_
#include "object.h"
#include "main.h"

//================================================
//�}�N����`
//================================================
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)		//���_�t�H�[�}�b�g3D
#define VERTEX_3D_NUM (4)														//���_��

//========================================================
//�\���̂̒�`3D
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	D3DXVECTOR3 nor;		//�@���x�N�g��
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
} VERTEX_3D;

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CObject3D : public CObject
{
public:
	CObject3D(CObject::PRIORITY Priority = CObject::PRIORITY::POLYGON_3D);	//�R���X�g���N�^
	~CObject3D();									//�f�X�g���N�^

												//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObject3D *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot);
	D3DXVECTOR3 GetPos(void);											//�ʒu�擾����
	void SetPos(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);		//�ʒu�ݒ菈��
	void SetTex(const int &nPattern, const int &nMaxPattern);			//�e�N�X�`���A�j���[�V�����ݒ菈��
	void SetTex(const float &fMoveTexU, const float &fMoveTexV);		//�e�N�X�`���ړ��ݒ菈��
	void SetCol(const D3DCOLORVALUE &col);								//�J���[�o�����[�ݒ菈��
	void SetCol(const D3DXCOLOR &col);									//�J���[�ݒ菈��
	D3DXCOLOR GetCol(void);												//�J���[�擾����
	void SetCulling(const bool &bCulling);								//�J�����O�ݒ菈��
	void SetAlphaBlend(const bool &bAlphaBlend);						//���Z�����ݒ菈��
	void SetAlphaTest(const bool &bAlphaTest);							//���A�e�X�g�ݒ菈��
	void SetLighting(const bool &bLighting);							//���C�e�B���O�ݒ菈��
	void BindTexture(const LPDIRECT3DTEXTURE9 &pTexture);				//�e�N�X�`���ݒ菈��

private:

protected:
	D3DXVECTOR3 m_pos;							//�|���S���̈ʒu
	D3DXVECTOR3 m_vtxPos[VERTEX_3D_NUM];		//���_�̈ʒu
	D3DXVECTOR3	m_size;							//�T�C�Y
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_vtxRot[VERTEX_3D_NUM];		//���_�̌���
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	D3DXMATRIX m_vtxMtxWorld[VERTEX_3D_NUM];	//���_�̃��[���h�}�g���b�N�X
	bool m_bCulling;							//�J�����O���s�����s��Ȃ���
	bool m_bAlphaBlend;							//���Z�������邩�ǂ���
	bool m_bAlphaTest;							//���e�X�g���邩�ǂ���
	bool m_bLighting;							//���C�e�B���O�L�����ǂ���
};

#endif // !_SCENE3D_H_