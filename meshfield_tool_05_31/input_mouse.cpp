//================================================
//�}�E�X���͏���
//Author:��������
//================================================
#include "input_mouse.h"
#include "input.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CInputMouse::CInputMouse()
{
	
}

//================================================
//�f�X�g���N�^
//================================================
 CInputMouse::~ CInputMouse()
{

}

//================================================
//����������
//================================================
HRESULT  CInputMouse::Init(const HINSTANCE &hInstance, const HWND &hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//================================================
//�I������
//================================================
void  CInputMouse::Uninit(void)
{
	CInput::Uninit();
}

//================================================
//�X�V����
//================================================
void  CInputMouse::Update(void)
{
	DIMOUSESTATE2 mouseState;
	int nCntKey;

	//���̓f�o�C�X����f�[�^�擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(mouseState), &mouseState)))
	{
		for (nCntKey = 0; nCntKey < MOUSE_TYPE_MAX; nCntKey++)
		{
			m_mouseStateTrigger.rgbButtons[nCntKey] = (m_mouseState.rgbButtons[nCntKey] ^ mouseState.rgbButtons[nCntKey]) & mouseState.rgbButtons[nCntKey];
			m_mouseStateRelease.rgbButtons[nCntKey] = (m_mouseState.rgbButtons[nCntKey] ^ mouseState.rgbButtons[nCntKey]) & ~mouseState.rgbButtons[nCntKey];
		}
		m_mouseState = mouseState;	//�}�E�X�̓��͏��ۑ�
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//=======================================================================
//�}�E�X�̓��͏��擾
//=======================================================================
bool CInputMouse::GetPress(const int &nMouse)
{
	return(m_mouseState.rgbButtons[nMouse] & 0x80) ? true : false;
}

bool CInputMouse::GetTrigger(const int &nMouse)
{
	return(m_mouseStateTrigger.rgbButtons[nMouse] & 0x80) ? true : false;
}

bool CInputMouse::GetRelease(const int &nMouse)
{
	return (m_mouseStateRelease.rgbButtons[nMouse] & 0x80) ? true : false;
}

//=======================================================================
//�}�E�X�̓��͏��擾����
//=======================================================================
DIMOUSESTATE2 CInputMouse::GetMouseState(void)
{
	return m_mouseState;
}

//=======================================================================
//�}�E�X�̈ړ��ʎ擾����
//=======================================================================
D3DXVECTOR2 CInputMouse::GetMouseVelocity(void)
{
	return D3DXVECTOR2((float)m_mouseState.lX, (float)m_mouseState.lY);
}