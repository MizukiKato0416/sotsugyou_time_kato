//===========================================
//�Q�[������
//Author:��������
//===========================================
#ifndef _GAME01_H_
#define _GAME01_H_
#include "object.h"
#include "main.h"

//�O���錾
class CMeshField;
class CModelSingle;

//================================================
//�}�N����`
//================================================

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
class CGame01 : public CObject
{
public:
	enum class SELECT
	{
		VERTICAL = 0,		//�c
		LINE,				//��
		WIDTH,				//��
		DEPTH,				//�[��
		CREATE,				//����
		RADIUS,				//����グ�锼�a
		STRENGTH,			//����グ�鋭��
		TERRAIN_UP_DOWN,	//�n�`�𐷂�グ�邩���艺���邩
		MESH_SAVE,			//���b�V���e�L�X�g�t�@�C�������o��
		MESH_LOAD,			//���b�V���ǂݍ���
		MODEL_SAVE,			//���f���e�L�X�g�t�@�C�������o��
		MODEL_LOAD,			//���f���ǂݍ���
		MODEL_NEW_CREATE,	//�V�������f������
		MODEL_SELECT,		//���f���I��
		UPDATE,				//���̍X�V
		MAX
	};

	CGame01(CObject::PRIORITY Priority = CObject::PRIORITY::NONE);		//�R���X�g���N�^
	~CGame01();															//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetUpDown(void) { return m_bUpDown; }		//�グ�邩�����邩�擾����

	// �X�N���[�����W�����[���h���W�ɕϊ�
	D3DXVECTOR3* CalcScreenToWorld(
		D3DXVECTOR3* pout,
		int Sx,  // �X�N���[��X���W
		int Sy,  // �X�N���[��Y���W
		float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj
	);
	
	// XZ���ʂƃX�N���[�����W�̌�_�Z�o�֐�
	D3DXVECTOR3* CalcScreenToXZ(
		D3DXVECTOR3* pout,
		int Sx,
		int Sy,
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj
	);

	//������`�悷�邩�擾����
	bool GetDrawCharactor(void) { return m_bDrawCharactor; }

private:
	void SaveTxt(void);								//�Z�[�u����
	void LoadModelTxt(const string &Pas);			//���f�����[�h����
	void ModeSelect(void);							//���[�h�I������
	void InputNum(void);							//���l���͏���
	void CreateNewModelSelect(void);				//�V�����������郂�f���I������
	void CreateNewModel(void);						//�V�������f����������
	void ModelSelect(void);							//��������Ă��郂�f���I������
	void ModelMove(void);							//���f���̈ړ�����
	void ModelRotate(void);							//���f���̉�]����
	void DeleteModel(void);							//���f���폜����
	void DeleteMeshField(void);						//���b�V���t�B�[���h�폜����
	void DeleteAllModel(void);						//�S�Ẵ��f���폜����
	void DeleteAllObject(void);						//�S�ẴI�u�W�F�N�g�폜����
	void MeshFieldDeformation(void);				//���b�V���t�B�[���h�ό`����

	//�����o�ϐ�
	CMeshField *m_pMeshField;			//���b�V���t�B�[���h�̃|�C���^
	int m_nLine;						//���b�V���t�B�[���h�̉��̗�̐�
	int m_nVertical;					//���b�V���t�B�[���h�̏c�̗�̐�
	SELECT m_select;					//�I����
	bool m_bPasDrop;					//�L�[��ł�����ł��邩�ǂ���
	pair<int, bool> key_update;			
	int m_nCntNum;						//����������������͂�����
	D3DXVECTOR3 m_meshFieldPos;			//���b�V���t�B�[���h�̈ʒu
	float m_fRadius;					//����グ��n�_�̔��a
	float m_fStrength;					//����グ��n�_�̋���
	bool m_bUpDown;						//����グ�邩���艺���邩
	CModelSingle *m_pNewModel;			//�V�������f��
	vector<CModelSingle*> m_apModel;	//�������ꂽ���f��
	int m_nNumModelType;				//���Ԗڂ̃��f���̃^�C�v��
	int m_nNumModel;					//���Ԗڂɐ����������f����
	bool m_bModelSet;					//���f�������[�h���Đ����������ǂ���
	float m_fMoveSpeed;					//���f���̈ړ����x
	bool m_bDrawCharactor;				//�����̕`��
};	

#endif // !_GAME01_H_