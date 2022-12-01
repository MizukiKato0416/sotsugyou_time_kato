//=============================================================================
//
// ���V������ [float_object.cpp]
// Author : ��������
//
//=============================================================================
#include "float_object.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFloatObject::CFloatObject()
{
	m_move = { 0.0f, 0.0f, 0.0f };
	m_rotateSpeed = { 0.0f, 0.0f, 0.0f };
}

//=============================================================================
// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
//=============================================================================
CFloatObject::CFloatObject(CModel::MODELTYPE typeModel) : CObjectModel(typeModel, false)
{
	m_move = { 0.0f, 0.0f, 0.0f };
	m_rotateSpeed = { 0.0f, 0.0f, 0.0f };
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFloatObject::~CFloatObject()
{
	
}

//=============================================================================
// ��������
//=============================================================================
CFloatObject* CFloatObject::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move,
	                               const D3DXVECTOR3 rotateSpeed, const CModel::MODELTYPE modelType) {
	CFloatObject* pFloatObject;
	pFloatObject = new CFloatObject(modelType);
	if (pFloatObject == nullptr) return nullptr;

	pFloatObject->SetPos(pos);
	pFloatObject->SetRot(rot);
	pFloatObject->m_move = move;
	pFloatObject->m_rotateSpeed = rotateSpeed;
	
	pFloatObject->Init();

	return pFloatObject;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFloatObject::Init(void) {

	CObjectModel::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFloatObject::Uninit(void) {

	CObjectModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFloatObject::Update(void) {
	
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�ړ��ʉ��Z
	pos += m_move;
	//�ʒu�ݒ�
	SetPos(pos);

	//�����擾
	D3DXVECTOR3 rot = GetRot();
	//�������Z
	rot += m_rotateSpeed;

	//�΂�-�΂��܂�������
	if (rot.x > D3DX_PI)
	{
		rot.x -= D3DX_PI * 2.0f;
	}
	else if (rot.x < -D3DX_PI)
	{
		rot.x += D3DX_PI * 2.0f;
	}

	if (rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}

	if (rot.z > D3DX_PI)
	{
		rot.z -= D3DX_PI * 2.0f;
	}
	else if (rot.z < -D3DX_PI)
	{
		rot.z += D3DX_PI * 2.0f;
	}

	//�����ݒ�
	SetRot(rot);

	CObjectModel::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFloatObject::Draw(void) {
	CObjectModel::Draw();
}