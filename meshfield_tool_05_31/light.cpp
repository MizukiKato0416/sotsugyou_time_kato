//=======================================================================
//���C�g�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#include "main.h"
#include "light.h"
#include "manager.h"
#include "renderer.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
int CLight::m_nNum = 0;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CLight::CLight()
{
	//���C�g���N���A����
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_nCnt = m_nNum;
	m_nNum++;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CLight::~CLight()
{

}

//================================================
//����������
//================================================
HRESULT CLight::Init(D3DXVECTOR3 vecDir, const D3DXVECTOR3 &pos)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�g���N���A����
	//ZeroMemory(&m_light, sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	m_light.Type = D3DLIGHT_DIRECTIONAL;		//���s����

	//���C�g�̊g�U����ݒ�
	m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//m_light.Diffuse = D3DXCOLOR(1.0f, 0.45f, 0.0f, 1.0f);
	//m_light.Diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

	//�ʒu�ݒ�
	m_light.Position = pos;

	//���K������(�x�N�g���̑傫����1�ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light.Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(m_nCnt, &m_light);

	//���C�g��L���ɂ���
	pDevice->LightEnable(m_nCnt, TRUE);

	return S_OK;
}

//================================================
//�I������
//================================================
void CLight::Uninit(void)
{
	m_nNum--;
}

//================================================
//�X�V����
//================================================
void CLight::Update(void)
{
	
}

//================================================
//��������
//================================================
CLight *CLight::Create(const D3DXVECTOR3 &vecDir, const D3DXVECTOR3 &pos)
{
	//�C���X�^���X�̐���
	CLight *pLight = nullptr;
	if (pLight == nullptr)
	{
		pLight = new CLight;
		if (pLight != nullptr)
		{
			pLight->Init(vecDir, pos);
		}
	}
	return pLight;
}