//===========================================
//���b�V���t�B�[���h����
//Author:��������
//===========================================
#ifndef _MESH_FIELD_H_
#define _MESH_FIELD_H_
#include "object.h"
#include "main.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMeshField : public CObject
{
public:
	CMeshField(CObject::PRIORITY Priority = CObject::PRIORITY::MESH_FIELD);	//�R���X�g���N�^
	~CMeshField();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshField *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const int &nLine, const int &nVertical);
	//�e�L�X�g�t�@�C������̐�������
	static CMeshField *CreateLoadText(string sPas);
	//�e�N�X�`���ݒ菈��
	void BindTexture(const LPDIRECT3DTEXTURE9 &pTexture);
	//���_���W�ݒ菈��
	D3DXVECTOR3 GetBufferPos(const int &nNumVtx) { return m_bufferPos[nNumVtx]; }
	//���_���W���Z����
	void AddVtxPos(const int &nNumVtx, const float &fHeight);
	//���_���W�擾����
	D3DXVECTOR3 GetVtxPos(const int &nNumVtx) { return m_bufferPos[nNumVtx]; }
	//�c�̃|���S���̐��擾����
	int GetVertical(void) { return m_nVertical; }
	//���̃|���S���̐��擾����
	int GetLine(void) { return m_nLine; }
	//�C���f�b�N�X�o�b�t�@�[�̒��_�ʒu�ۑ��p�ϐ��擾����
	void SetBuffSavePos(const int &nNumVtx, const float &fHeight) { m_bufferSavePos[nNumVtx].y = fHeight; }
	//�e�L�X�g�ɃZ�[�u���鏈��
	void SaveText(void);
	//�@���X�V����
	void UpdateNor(void);


private:
	//�����o�֐�

	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;							//�|���S���̈ʒu
	std::vector<D3DXVECTOR3> m_indexPos;		//�C���f�b�N�X�o�b�t�@�[�̒��_�ʒu
	std::vector<D3DXVECTOR3> m_indexSavePos;	//�C���f�b�N�X�o�b�t�@�[�̒��_�ʒu�ۑ��p
	std::vector<D3DXVECTOR3> m_indexRot;		//�C���f�b�N�X�o�b�t�@�[�̒��_����
	std::vector<D3DXVECTOR3> m_bufferPos;		//�o�b�t�@�[�̒��_�ʒu
	std::vector<D3DXVECTOR3> m_bufferSavePos;	//�o�b�t�@�[�̒��_�ʒu�ۑ��p
	D3DXVECTOR3	m_size;							//�T�C�Y
	D3DXVECTOR3 m_rot;							//����
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	std::vector<D3DXMATRIX> m_indexMtxWorld;	//�C���f�b�N�X�o�b�t�@���[���h�}�g���b�N�X
	int m_nVertical;							//�c�̃|���S���̐� 
	int m_nLine;								//���̃|���S���̐�
};

#endif // !_MESH_FIELD_H_