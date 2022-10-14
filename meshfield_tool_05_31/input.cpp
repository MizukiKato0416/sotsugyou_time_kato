//================================================
//���͏���
//Author:��������
//================================================
#include "input.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECTINPUTDEVICE8 CInput::m_pDeviceJoyStick = nullptr;
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CInput::CInput()
{
	m_pDevice = nullptr;
}

//================================================
//�f�X�g���N�^
//================================================
CInput::~CInput()
{

}

//================================================
//����������
//================================================
HRESULT CInput::Init(const HINSTANCE &hInstance, const HWND &hWnd)
{
	//DirectInput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//================================================
//�I������
//================================================
void CInput::Uninit(void)
{
	//���̓f�o�C�X�̊J��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	//DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}