//===========================================
//�p�b�h����(�_�C���N�g)����
//Author:��������
//===========================================
#include "input_pad_d.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//=============================================================================
//�f�t�H���g�R���X�g���N�^
//=============================================================================
CInputPadD::CInputPadD()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CInputPadD::~CInputPadD()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CInputPadD::Init(const HINSTANCE &hInstance, const HWND &hWnd)
{
	CInput::Init(hInstance, hWnd);

	m_pInput->EnumDevices(	DI8DEVCLASS_GAMECTRL, 
							EnumJoysticksCallback,
							NULL,
							DIEDFL_ATTACHEDONLY);

	if (m_pDeviceJoyStick != nullptr)
	{
		//�������[�h��ݒ�
		if (FAILED(m_pDeviceJoyStick->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}
	}
	else
	{
		return E_FAIL;
	}

	m_pDeviceJoyStick->GetCapabilities(&m_diDevCaps);

	m_pDeviceJoyStick->EnumObjects(EnumAxesCallback, (VOID*)hWnd, DIDFT_AXIS);

	m_pDeviceJoyStick->Poll();

	// �A�N�Z�X�����l��(���͐���J�n)
	m_pDeviceJoyStick->Acquire();

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CInputPadD::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CInputPadD::Update(void)
{
	if (m_pDeviceJoyStick != nullptr)
	{
		//��Ԃ�ς���O�ɕۑ�
		m_aStateOld = m_aState;

		DIJOYSTATE2 state;
		//m_aState.rglSlider[0] = m_pDeviceJoyStick->GetObjectInfo();
		//���̓f�o�C�X����f�[�^�擾
		if (SUCCEEDED(m_pDeviceJoyStick->GetDeviceState(sizeof(state), &state)))
		{
			for (int nCntKey = 0; nCntKey < BUTTON_MAX; nCntKey++)
			{
				m_aStateTrigger.rgbButtons[nCntKey] = (m_aState.rgbButtons[nCntKey] ^ state.rgbButtons[nCntKey]) & state.rgbButtons[nCntKey];
				m_aStateRelease.rgbButtons[nCntKey] = (m_aState.rgbButtons[nCntKey] ^ state.rgbButtons[nCntKey]) & ~state.rgbButtons[nCntKey];
			}
			m_aState = state;
		}
		else
		{
			m_pDeviceJoyStick->Acquire();
		}
	}
}

//=============================================================================
// �{�^�����̎擾
//=============================================================================
bool CInputPadD::GetPress(const int &Botton_Type)
{
	return (m_aState.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

bool CInputPadD::GetTrigger(const int &Botton_Type)
{
	return (m_aStateTrigger.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

bool CInputPadD::GetRelease(const int &Botton_Type)
{
	return (m_aStateRelease.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

DIJOYSTATE2 CInputPadD::GetGamepad(void)
{
	return m_aState;
}

DIJOYSTATE2 CInputPadD::GetGamepadOld(void)
{
	return m_aStateOld;
}

//=============================================================================
//�R�[���o�b�N�֐�
//=============================================================================
BOOL CALLBACK CInputPadD::EnumJoysticksCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID /*pvRef*/)
{
	// �W���C�X�e�B�b�N�f�o�C�X�̍쐬
	HRESULT ret = m_pInput->CreateDevice(lpddi->guidInstance, &m_pDeviceJoyStick, NULL);
	if (FAILED(ret)) 
	{
		return DIENUM_STOP;
	}

	// ���̓f�[�^�`���̃Z�b�g
	ret = m_pDeviceJoyStick->SetDataFormat(&c_dfDIJoystick2);
	if (FAILED(ret)) 
	{
		m_pDeviceJoyStick->Release();
		return DIENUM_STOP;
	}

	return DIENUM_STOP;
}

BOOL CALLBACK CInputPadD::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID * /*pContext*/)
{
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = -STICK_POW;
	diprg.lMax = STICK_POW;

	if (FAILED(m_pDeviceJoyStick->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}