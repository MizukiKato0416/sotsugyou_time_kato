//=============================================================================
// �x���t���v���Z�b�g�Ăяo���N���X
// Author : ������
//=============================================================================
#include "manager.h"
#include "PresetDelaySet.h"
#include "loadeffect.h"
#include "presetseteffect.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPresetDelaySet::CPresetDelaySet() : CScene3D()
{
	m_pos = {};			// �ʒu
	m_Endpos = {};	//��r
	m_rot = {};	//��]
	m_nDelay = 0;		// �f�B���C
	m_nCallCnt = 0;		// �Ăяo���J�E���g 
	m_nArray = 0;		// �ԍ�
	m_bUninit = false;	// �I�����肷�邩
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPresetDelaySet::~CPresetDelaySet()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CPresetDelaySet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Endpos, D3DXVECTOR3 rot)
{
	m_pos = pos;	// �ʒu
	m_Endpos = Endpos;	//��r
	m_rot = rot;	//��]

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CPresetDelaySet::Uninit()
{
	Release();
}

//=============================================================================
// �X�V
//=============================================================================
void CPresetDelaySet::Update()
{
	// �v���Z�b�g�Ăяo������ۑ�
	CLoadEffect::CALL_PRESET CallPreset = CLoadEffect::GetCallPreset(m_nArray);

	// �G�t�F�N�g���Ăяo��
	if (m_nDelay >= CallPreset.m_nDelay[m_nCallCnt])
	{
		for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
		{
			CPresetEffect::SetEffect3D(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, m_Endpos, m_rot);
		}
		m_nCallCnt++;
	}

	// �R�[�������ő吔�𒴂���
	if (m_nCallCnt >= CallPreset.m_CallMax)
	{
		Uninit();
	}

	// �f�B���C��i�߂�
	m_nDelay++;
}

//=============================================================================
// �`��
//=============================================================================
void CPresetDelaySet::Draw()
{

}

//=============================================================================
// ����
//=============================================================================
CPresetDelaySet* CPresetDelaySet::Create(int nArray, D3DXVECTOR3 pos, D3DXVECTOR3 Endpos, D3DXVECTOR3 rot)
{
	// �������m��
	CPresetDelaySet *pPresetDelay = nullptr;
	pPresetDelay = new CPresetDelaySet();

	if (pPresetDelay)
	{
		pPresetDelay->m_nArray = nArray;
		pPresetDelay->Init(pos, Endpos, rot);
	}

	return pPresetDelay;
}

//=============================================================================
// ����
//=============================================================================
CPresetDelaySet* CPresetDelaySet::Create(std::string sName, D3DXVECTOR3 pos, D3DXVECTOR3 Endpos, D3DXVECTOR3 rot)
{
	return Create(CLoadEffect::GetPresetName(sName), pos, Endpos, rot);
}