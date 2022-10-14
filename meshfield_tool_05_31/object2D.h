//===========================================
//2D�|���S������
//Author:��������
//===========================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_
#include "object.h"
#include "main.h"

//================================================
//�}�N����`
//================================================
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//���_�t�H�[�}�b�g
#define VERTEX_NUM (4)												//���_��

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	float rhw;				//1.0f�ŌŒ�
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
} VERTEX_2D;

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CObject2D : public CObject
{
public:
	//�|���S���̌��_�̎��
	enum class ORIGIN_TYPE
	{
		CENTER = 0,			//����
		LEFT,				//���[
		MAX
	};

	CObject2D(CObject::PRIORITY Priority = CObject::PRIORITY::NONE);	//�R���X�g���N�^
	~CObject2D();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObject2D *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const int &nPriolty);
	D3DXVECTOR3 GetPos(void);
	void SetPos(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);							//�ʒu�ݒ菈��
	void SetPos(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const float &fRot);		//�ʒu�ݒ菈��
	void SetTex(const int &nPattern, const int &nMaxPattern);								//�e�N�X�`���A�j���[�V�����ݒ菈��
	void SetTex(const float &fMoveTexU, const float &fMoveTexV);							//�e�N�X�`���ړ�����
	void SetCol(const D3DCOLORVALUE &col);													//�J���[�ݒ菈��
	void SetCol(const D3DXCOLOR &col);														//�J���[�ݒ菈��
	D3DXCOLOR GetCol(void);																	//�J���[�擾����
	//���_�ݒ菈��
	void SetVtx(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &vtx0, const D3DXVECTOR3 &vtx1, const D3DXVECTOR3 &vtx2, const D3DXVECTOR3 &vtx3);
	void BindTexture(const LPDIRECT3DTEXTURE9 &pTexture);									//�e�N�X�`���ݒ菈��
	void SetOriginType(const ORIGIN_TYPE &originType) { m_OriginType = originType; }		//���_�̎�ސݒ菈��

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�|���S���̈ʒu
	D3DXVECTOR3	m_size;						//�T�C�Y
	ORIGIN_TYPE m_OriginType;				//���_�̎��
};

#endif // !_OBJECT2D_H_