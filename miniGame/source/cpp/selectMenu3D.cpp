//=============================================================================
//
// 3D�I�����j���[���� [selectMenu3D.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "selectMenu3D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DEFAULT_ROTATE_SPAN (30)	//�f�t�H���g�̉�]�X�p�� 0�֎~

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CSelectMenu3D::CSelectMenu3D() : m_posCenter(D3DXVECTOR3()), m_fRadiusModel(0.0f)
{

}

//=============================================================================
// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
//=============================================================================
CSelectMenu3D::CSelectMenu3D(int nNumSelect, D3DXVECTOR3 posCenter, float fRadiusModel, CModel::MODELTYPE typeModel, float fDistCamera, float fHeightCamera, bool bUseBG)
	: CSelectMenu(nNumSelect,bUseBG), m_posCenter(posCenter), m_fRadiusModel(fRadiusModel)
{
	m_fRotModel = 0.0f;
	m_typeModel = typeModel;
	m_nCntRotate = 0;
	m_nSpanRotate = DEFAULT_ROTATE_SPAN;

	m_fDistCamera = fDistCamera;
	m_fRotCamera = 0.0f;
	m_fHeightCamera = fHeightCamera;
	//���E�̓��͂ɂ���
	SetSelectType(SELECT_TYPE::HORIZONTAL);

	CreateModelUI();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSelectMenu3D::~CSelectMenu3D()
{

}

//=============================================================================
// 3D�I�����j���[�̐�������
//=============================================================================
CSelectMenu3D* CSelectMenu3D::Create(int nNumSelect, D3DXVECTOR3 posCenter, float fRadius, CModel::MODELTYPE typeModel, float fDistCamera, float fHeightCamera, bool bUseBG) {
	CSelectMenu3D* pSelectMenu3D;
	pSelectMenu3D = new CSelectMenu3D(nNumSelect, posCenter, fRadius, typeModel, fDistCamera, fHeightCamera, bUseBG);
	if (pSelectMenu3D == nullptr) return nullptr;

	pSelectMenu3D->Init();

	return pSelectMenu3D;
}

//=============================================================================
// 3D�I�����j���[�̏���������
//=============================================================================
HRESULT CSelectMenu3D::Init(void) {
	m_fRotModel = 0.0f;
	m_fSpeedRotModel = 0.0f;
	m_fRotCamera = 0.0f;
	m_nCntRotate = 0;

	CSelectMenu::Init();

	return S_OK;
}

//=============================================================================
// 3D�I�����j���[�̏I������
//=============================================================================
void CSelectMenu3D::Uninit(void) {
	int nNumSelect = GetNumSelect();

	//UI���f���̔j��
	if (m_ppObjModelUIArray != nullptr) {
		for (int nCntModel = 0; nCntModel < nNumSelect; nCntModel++)
		{
			if (m_ppObjModelUIArray[nCntModel] == nullptr) continue;
			m_ppObjModelUIArray[nCntModel]->Uninit();
			m_ppObjModelUIArray[nCntModel] = nullptr;
		}
		m_ppObjModelUIArray = nullptr;
	}

	CSelectMenu::Uninit();
}

//=============================================================================
// 3D�I�����j���[�̍X�V����
//=============================================================================
void CSelectMenu3D::Update(void) {
	//���f���̈ʒu���ړ�
	MoveModel();

	CSelectMenu::Update();
}

//=============================================================================
// UI���f���̐���
//=============================================================================
void CSelectMenu3D::CreateModelUI(void) {
	//���łɐ����ς݂̏ꍇ�I��
	if (m_ppObjModelUIArray != nullptr) return;

	//�I�����̐��̎擾
	int nNumSelect = GetNumSelect();
	m_ppObjModelUIArray = new CObjectModelUI*[nNumSelect];

	//�����ł��Ȃ������ꍇ�I��
	if (m_ppObjModelUIArray == nullptr) return;

	//UI���f�����f���J������ݒ�
	D3DXMATRIX mtxView;	//�r���[�}�g���b�N�X
	D3DXVECTOR3 posR, posV;	//���_�ƒ����_

	posR = m_posCenter;
	posV = D3DXVECTOR3(m_posCenter.x, m_posCenter.y + m_fHeightCamera, m_posCenter.z - m_fDistCamera);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView,
		&posV,
		&posR,
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	for (int nCntModel = 0; nCntModel < nNumSelect; nCntModel++)
	{
		D3DXVECTOR3 posModel;	//UI���f����z�u����ʒu
		posModel = m_posCenter +
			D3DXVECTOR3(sinf(D3DX_PI * 2.0f * (1.0f - (float)nCntModel / nNumSelect) + D3DX_PI) * m_fRadiusModel, //1.0- �ō����̔z�u	+PI�Ŏ�O���ɂP�Ԗڂ̃I�u�W�F�N�g������悤��
				0.0f,
				cosf(D3DX_PI * 2.0f * (1.0f - (float)nCntModel / nNumSelect) + D3DX_PI) * m_fRadiusModel);
		//UI���f���̐���
		m_ppObjModelUIArray[nCntModel] = CObjectModelUI::Create(m_typeModel, posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);

		if (m_ppObjModelUIArray[nCntModel] == nullptr) continue;
		//UI���f���̃r���[�}�g���b�N�X�Ǝ��_��ݒ�
		m_ppObjModelUIArray[nCntModel]->SetViewMatrix(mtxView);
		m_ppObjModelUIArray[nCntModel]->SetViewPos(posV);
	}
}

//=============================================================================
// ���f���̈ړ�
//=============================================================================
void CSelectMenu3D::MoveModel(void) {
	//���f���̃_�u���|�C���^��null�̏ꍇ
	if (m_ppObjModelUIArray == nullptr) {
		//�I���̕ύX�̐�������������
		SetLockChangeSelect(false);
	}

	//�J�E���g0�ȉ��̏ꍇ�I��
	if (m_nCntRotate <= 0) return;

	//�J�E���^�[�����Z
	m_nCntRotate--;

	//��]�����Z
	m_fRotModel += m_fSpeedRotModel;
	//���ߕ�����
	if (m_fRotModel > D3DX_PI * 2) m_fRotModel -= D3DX_PI * 2;

	//�I���̑J�ڂ�������
	if (m_nCntRotate <= 0) {
		//�I���̕ύX�̐�������������
		SetLockChangeSelect(false);
		//�I�����̏���
		EndChangeSelect();

		//�ڕW�p�x��ݒ肷��@�ifloat�̌덷������邽�߁j
		m_fRotModel = m_fRotModelDest;
	}

	int nNumSelect = GetNumSelect();	//�I�����̐����擾

	//UI���f���̈ʒu��ύX
	for (int nCntModel = 0; nCntModel < nNumSelect; nCntModel++)
	{
		//UI���f����z�u����ʒu
		D3DXVECTOR3 posModel = m_posCenter +
			D3DXVECTOR3(sinf(D3DX_PI * 2.0f * (1.0f - (float)nCntModel / nNumSelect) + D3DX_PI + m_fRotModel) * m_fRadiusModel, //1.0- �ō����̔z�u	+PI�Ŏ�O���ɂP�Ԗڂ̃I�u�W�F�N�g������悤��
				0.0f,
				cosf(D3DX_PI * 2.0f * (1.0f - (float)nCntModel / nNumSelect) + D3DX_PI + m_fRotModel) * m_fRadiusModel);
		//UI���f���̈ʒu��ݒ�
		if (m_ppObjModelUIArray[nCntModel] != nullptr) m_ppObjModelUIArray[nCntModel]->SetPos(posModel);
	}
}

//=============================================================================
// �I���̕ύX���J�n���ꂽ�Ƃ��̏���
//=============================================================================
void CSelectMenu3D::BeginChangeSelect(bool bChangePlus) {
	//�I���̕ύX�𐧌�����
	SetLockChangeSelect(true);

	int nIdxCurSelect = GetIdxCurSelect();	//���݂̑I���̔ԍ����擾
	SetRotDest(nIdxCurSelect);

	float fRotDelta;	//�ڕW�p�x�ւ̍���

	//�I�������v���X�����ꍇ�̉�]���鍷�����v�Z
	if (m_fRotModelDest > m_fRotModel) {
		fRotDelta = m_fRotModelDest - m_fRotModel;
	}
	else {
		fRotDelta = D3DX_PI * 2 - (m_fRotModel - m_fRotModelDest);
	}

	//�I�������}�C�i�X�����ꍇ�@�}�C�i�X�ɂ��Ĕ����v����
	if (!bChangePlus) fRotDelta -= D3DX_PI * 2;

	if (m_nSpanRotate == 0) m_nSpanRotate = DEFAULT_ROTATE_SPAN;	//0���Z�΍�
	//�J�E���g�̐ݒ�
	m_nCntRotate = m_nSpanRotate;

	//��]���x��ݒ�
	SetSpeedRotModel(fRotDelta / m_nCntRotate);
}

//=============================================================================
// UI���f���I�u�W�F�N�g�̃|�C���^���擾
//=============================================================================
CObjectModelUI* CSelectMenu3D::GetModelUI(int nIdx) {
	if (m_ppObjModelUIArray == nullptr || nIdx < 0 || nIdx >= GetNumSelect()) return nullptr;	//�z�񂩂�擾�ł��Ȃ��ꍇnull
	return m_ppObjModelUIArray[nIdx];
}