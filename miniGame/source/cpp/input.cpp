//=============================================================================
//
// ���͏��� [input.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "input.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//******************************************************************************************************************
// �C���v�b�g�N���X
//******************************************************************************************************************
//=============================================================================
// �C���v�b�g�̃f�t�H���g�R���X�g���N�^
//=============================================================================
CInput::CInput()
{
	m_pDevice = nullptr;
}

//=============================================================================
// �C���v�b�g�̃f�X�g���N�^
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// �C���v�b�g�̏���������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd) {
	if (m_pInput == nullptr) {
		//DirectInput�I�u�W�F�N�g�̍쐬
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL))) {
			return E_FAIL;
		}
	}
	return S_OK;
}

//=============================================================================
// �C���v�b�g�̏I������
//=============================================================================
void CInput::Uninit(void) {
	//���̓f�o�C�X�̊J��
	if (m_pDevice != nullptr) {
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
	//DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != nullptr) {
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//******************************************************************************************************************
// �L�[�{�[�h�N���X
//******************************************************************************************************************
//=============================================================================
// �L�[�{�[�h�̃f�t�H���g�R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	//�L�[���̃N���A
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));
}

//=============================================================================
// �L�[�{�[�h�̃f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// �L�[�{�[�h�̏���������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd) {
	//�C���v�b�g�̏�����
	CInput::Init(hInstance, hWnd);
	//�L�[�{�[�h�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL))) {
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CInputKeyboard::Uninit(void) {
	CInput::Uninit();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputKeyboard::Update(void) {
	BYTE aKeyState[256];
	int nCntKey;
	//���̓f�o�C�X����f�[�^�擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0]))) {
		for (nCntKey = 0; nCntKey < 256; nCntKey++) {
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�̓��͏��ۑ�
		}
	}
	else {
		m_pDevice->Acquire();
	}
}

//=============================================================================
// �L�[�{�[�h�̃v���X����
//=============================================================================
bool CInputKeyboard::GetPress(int nKey) {
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[����
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey) {
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̓��͔���i�v���X�j
//=============================================================================
bool CInputKeyboard::GetPress(CODE code, int nIdx) {
	switch (code)
	{
		//�I��
	case CODE::SELECT:
		if (GetPress(DIK_RETURN)) {
			return true;
		}
		break;

		//�߂�
	case CODE::BACK:
		if (GetPress(DIK_ESCAPE)) {
			return true;
		}
		break;

		//�㉺���E
	case CODE::MOVE_UP:
		if (GetPress(DIK_W)) {
			return true;
		}
		break;
	case CODE::MOVE_DOWN:
		if (GetPress(DIK_S)) {
			return true;
		}
		break;
	case CODE::MOVE_LEFT:
		if (GetPress(DIK_A)) {
			return true;
		}
		break;
	case CODE::MOVE_RIGHT:
		if (GetPress(DIK_D)) {
			return true;
		}
		break;
		//�㏸�E���~
	case CODE::MOVE_RISE:
		if (GetPress(DIK_E)) {
			return true;
		}
		break;
	case CODE::MOVE_FALL:
		if (GetPress(DIK_Q)) {
			return true;
		}
		break;


		//�J�����̑O�㍶�E
	case CODE::ROTATE_UP:
		if (GetPress(DIK_I)) {
			return true;
		}
		break;
	case CODE::ROTATE_DOWN:
		if (GetPress(DIK_K)) {
			return true;
		}
		break;
	case CODE::ROTATE_LEFT:
		if (GetPress(DIK_J)) {
			return true;
		}
		break;
	case CODE::ROTATE_RIGHT:
		if (GetPress(DIK_L)) {
			return true;
		}
		break;

		//�A�N�Z��
	case CODE::ACCELE:
		if (GetPress(DIK_SPACE)) {
			return true;
		}
		break;
		//�o�b�N
	case CODE::REVERSE:
		if (GetPress(DIK_LSHIFT)) {
			return true;
		}
		break;
	}
	return false;
}

//=============================================================================
// �L�[�{�[�h�̓��͔���i�g���K�[�j
//=============================================================================
bool CInputKeyboard::GetTrigger(CODE code, int nIdx) {
	switch (code)
	{
		//�I��
	case CODE::SELECT:
		if (GetTrigger(DIK_SPACE) || GetTrigger(DIK_RETURN)) {
			return true;
		}
		break;
		//�߂�
	case CODE::BACK:
		if (GetTrigger(DIK_ESCAPE)) {
			return true;
		}
		break;
		//�|�[�Y
	case CODE::PAUSE:
		if (GetTrigger(DIK_P)) {
			return true;
		}
		break;

		//�ړ��̏㉺���E
	case CODE::MOVE_UP:
		if (GetTrigger(DIK_W)) {
			return true;
		}
		break;
	case CODE::MOVE_DOWN:
		if (GetTrigger(DIK_S)) {
			return true;
		}
		break;
	case CODE::MOVE_LEFT:
		if (GetTrigger(DIK_A)) {
			return true;
		}
		break;
	case CODE::MOVE_RIGHT:
		if (GetTrigger(DIK_D)) {
			return true;
		}
		break;

		//�㏸�E���~
	case CODE::MOVE_RISE:
		if (GetTrigger(DIK_E)) {
			return true;
		}
		break;
	case CODE::MOVE_FALL:
		if (GetTrigger(DIK_Q)) {
			return true;
		}
		break;

		//��]�̏㉺���E
	case CODE::ROTATE_UP:
		if (GetTrigger(DIK_I)) {
			return true;
		}
		break;
	case CODE::ROTATE_DOWN:
		if (GetTrigger(DIK_K)) {
			return true;
		}
		break;
	case CODE::ROTATE_LEFT:
		if (GetTrigger(DIK_J)) {
			return true;
		}
		break;
	case CODE::ROTATE_RIGHT:
		if (GetTrigger(DIK_L)) {
			return true;
		}
		break;

		//�I���̏㉺���E
	case CODE::SELECT_UP:
		if (GetTrigger(DIK_UP)) {
			return true;
		}
		break;
	case CODE::SELECT_DOWN:
		if (GetTrigger(DIK_DOWN)) {
			return true;
		}
		break;
	case CODE::SELECT_LFET:
		if (GetTrigger(DIK_LEFT)) {
			return true;
		}
		break;
	case CODE::SELECT_RIGHT:
		if (GetTrigger(DIK_RIGHT)) {
			return true;
		}
		break;
		//�C���^���N�g
	case CODE::USE_ITEM:
		if (GetTrigger(DIK_E)) {
			return true;
		}
		break;

#ifdef _DEBUG
	case CODE::DEBUG_0:
		if (GetTrigger(DIK_F1)) {
			return true;
		}
		break;
	case CODE::DEBUG_1:
		if (GetTrigger(DIK_F2)) {
			return true;
		}
		break;
	case CODE::DEBUG_2:
		if (GetTrigger(DIK_F3)) {
			return true;
		}
		break;
	case CODE::DEBUG_3:
		if (GetTrigger(DIK_F4)) {
			return true;
		}
		break;
#endif

	}
	return false;
}

//******************************************************************************************************************
// �Q�[���p�b�h�N���X(Xinput)
//******************************************************************************************************************
//=============================================================================
// �}�N����`(Xinput)
//=============================================================================
//�W���̃}�N����`�ɂȂ��������̂��`
#define XINPUT_GAMEPAD_L (0x100)	// L�{�^��
#define XINPUT_GAMEPAD_R (0x200)	// R�{�^��

//=============================================================================
// �Q�[���p�b�h�̃f�t�H���g�R���X�g���N�^(Xinput)
//=============================================================================
CInputGamepadX::CInputGamepadX()
{
	ZeroMemory(&m_aState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_aStateLast, sizeof(XINPUT_STATE));
	ZeroMemory(&m_aVibrationState, sizeof(XINPUT_VIBRATION));
	memset(m_abConnect, false, sizeof(m_abConnect[MAX_PAD_CONNECT_NUM]));
	memset(m_aCntVibration, NULL, sizeof(m_aCntVibration[MAX_PAD_CONNECT_NUM]));
	memset(m_abVibration, false, sizeof(m_abVibration[MAX_PAD_CONNECT_NUM]));
}

//=============================================================================
// �Q�[���p�b�h�̃f�X�g���N�^(Xinput)
//=============================================================================
CInputGamepadX::~CInputGamepadX()
{
}

//=============================================================================
// �Q�[���p�b�h�̏���������(Xinput)
//=============================================================================
void CInputGamepadX::Init(void) {
	ZeroMemory(&m_aState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_aStateLast, sizeof(XINPUT_STATE));
	ZeroMemory(&m_aVibrationState, sizeof(XINPUT_VIBRATION));
	memset(m_abConnect, false, sizeof(m_abConnect[MAX_PAD_CONNECT_NUM]));
	memset(m_aCntVibration, NULL, sizeof(m_aCntVibration[MAX_PAD_CONNECT_NUM]));
	memset(m_abVibration, false, sizeof(m_abVibration[MAX_PAD_CONNECT_NUM]));
}

//=============================================================================
// �Q�[���p�b�h�̏I������(Xinput)
//=============================================================================
void CInputGamepadX::Uninit(void) {
	CInput::Uninit();
}

//=============================================================================
// �Q�[���p�b�h�̍X�V����(Xinput)
//=============================================================================
void CInputGamepadX::Update(void) {

	for (int nIdx = 0; nIdx < MAX_PAD_CONNECT_NUM; nIdx++)
	{
		XINPUT_STATE state;

		DWORD dwResult = XInputGetState(nIdx, &state);

		m_aStateLast[nIdx] = m_aState[nIdx];
		m_aState[nIdx] = state;

		if (dwResult == ERROR_SUCCESS)
		{
			// Controller is connected
			m_abConnect[nIdx] = true;
		}
		else
		{
			// Controller is not connected
			m_abConnect[nIdx] = false;
		}

		if (XInputGetState(nIdx, &state) == ERROR_SUCCESS)
		{
			// Zero value if thumbsticks are within the dead zone
			if ((m_aState[nIdx].Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				m_aState[nIdx].Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
				(m_aState[nIdx].Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					m_aState[nIdx].Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			{
				m_aState[nIdx].Gamepad.sThumbLX = 0;
				m_aState[nIdx].Gamepad.sThumbLY = 0;
			}
		}

		//�o�C�u���[�V�����̃J�E���g
		if (m_aCntVibration[nIdx] > 0) {
			m_aCntVibration[nIdx]--;
		}
		//�o�C�u���[�V�����̏I��
		if (m_aCntVibration[nIdx] <= 0 && m_abVibration[nIdx]) {
			SetVibration(0, 0, 0, nIdx);
			m_abVibration[nIdx] = false;
		}
	}
}

//=============================================================================
// �Q�[���p�b�h�ڑ��̔���(Xinput)
//=============================================================================
bool CInputGamepadX::GetConnectGamepad(int nIdx) {
	return m_abConnect[nIdx];
}

//=============================================================================
// �Q�[���p�b�h�̃{�^���̃v���X����(Xinput)
//=============================================================================
bool CInputGamepadX::GetButtonPress(int nButton, int nIdx) {
	if (!m_abConnect[nIdx]) return false;	//�ڑ�����Ă��Ȃ��ꍇfalse��Ԃ�
	return (m_aState[nIdx].Gamepad.wButtons & nButton) ? true : false;
}

//=============================================================================
// �Q�[���p�b�h�̃{�^���̃g���K�[����(Xinput)
//=============================================================================
bool CInputGamepadX::GetButtonTrigger(int nButton, int nIdx) {
	if (!m_abConnect[nIdx]) return false;	//�ڑ�����Ă��Ȃ��ꍇfalse��Ԃ�
	return !(m_aStateLast[nIdx].Gamepad.wButtons & nButton) && (m_aState[nIdx].Gamepad.wButtons & nButton);
}

//=============================================================================
// �Q�[���p�b�h�̃g���K�[�̃v���X����(Xinput)
//=============================================================================
bool CInputGamepadX::GetTriggerPress(TRIGGER_TYPE type, int nIdx) {
	if (!m_abConnect[nIdx]) return false;	//�ڑ�����Ă��Ȃ��ꍇfalse��Ԃ�
	switch (type)
	{
	case TRIGGER_TYPE::RIGHT:
		return m_aState[nIdx].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		break;
	case TRIGGER_TYPE::LEFT:
		return m_aState[nIdx].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		break;
	default:
		return false;
		break;
	}
}

//=============================================================================
// �Q�[���p�b�h�̃g���K�[�̃g���K�[����(Xinput)
//=============================================================================
bool CInputGamepadX::GetTriggerTrigger(TRIGGER_TYPE type, int nIdx) {
	if (!m_abConnect[nIdx]) return false;	//�ڑ�����Ă��Ȃ��ꍇfalse��Ԃ�
	switch (type)
	{
	case TRIGGER_TYPE::RIGHT:
		return !(m_aStateLast[nIdx].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) && (m_aState[nIdx].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		break;
	case TRIGGER_TYPE::LEFT:
		return !(m_aStateLast[nIdx].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) && (m_aState[nIdx].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		break;
	default:
		return false;
		break;
	}
}

//=============================================================================
// �Q�[���p�b�h�̍��X�e�B�b�N�̔���(Xinput)
//=============================================================================
bool CInputGamepadX::GetLeftStick(STICK_TYPE type, int nIdx) {
	if (!m_abConnect[nIdx]) return false;	//�ڑ�����Ă��Ȃ��ꍇfalse��Ԃ�

	switch (type)
	{
	case STICK_TYPE::MOVE_UP:
		return m_aState[nIdx].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		break;
	case STICK_TYPE::MOVE_DOWN:
		return m_aState[nIdx].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		break;
	case STICK_TYPE::MOVE_LEFT:
		return m_aState[nIdx].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		break; 
	case STICK_TYPE::MOVE_RIGHT:
		return m_aState[nIdx].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		break;

	default:
		return false;
		break;
	}
}

//=============================================================================
// �Q�[���p�b�h�̍��X�e�B�b�N�̔���(Xinput)
//=============================================================================
bool CInputGamepadX::GetRightStick(STICK_TYPE type, int nIdx) {
	if (!m_abConnect[nIdx]) return false;	//�ڑ�����Ă��Ȃ��ꍇfalse��Ԃ�
	switch ((STICK_TYPE)type)
	{
	case STICK_TYPE::MOVE_UP:
		return m_aState[nIdx].Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		break;
	case STICK_TYPE::MOVE_DOWN:
		return m_aState[nIdx].Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		break;
	case STICK_TYPE::MOVE_LEFT:
		return m_aState[nIdx].Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		break;
	case STICK_TYPE::MOVE_RIGHT:
		return m_aState[nIdx].Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		break;

	default:
		return false;
		break;
	}
}

//=============================================================================
// �Q�[���p�b�h�̓��͔���i�v���X�j
//=============================================================================
bool CInputGamepadX::GetPress(CODE code, int nIdx) {
	switch (code)
	{
		//�I��
	case CODE::SELECT:
		if (GetButtonPress(XINPUT_GAMEPAD_START, nIdx)) {
			return true;
		}
		break;

		//�߂�
	case CODE::BACK:
		if (GetButtonPress(XINPUT_GAMEPAD_B, nIdx) || GetButtonPress(XINPUT_GAMEPAD_BACK, nIdx)) {
			return true;
		}
		break;

		//�㉺���E
	case CODE::MOVE_UP:
		if (GetLeftStick(STICK_TYPE::MOVE_UP, nIdx)) {
			return true;
		}
		break;
	case CODE::MOVE_DOWN:
		if (GetLeftStick(STICK_TYPE::MOVE_DOWN, nIdx)) {
			return true;
		}
		break;
	case CODE::MOVE_LEFT:
		if (GetLeftStick(STICK_TYPE::MOVE_LEFT, nIdx)) {
			return true;
		}
		break;
	case CODE::MOVE_RIGHT:
		if (GetLeftStick(STICK_TYPE::MOVE_RIGHT, nIdx)) {
			return true;
		}
		break;

		//�J�����̏㉺���E
	case CODE::ROTATE_UP:
		if (GetRightStick(STICK_TYPE::MOVE_UP, nIdx)) {
			return true;
		}
		break;
	case CODE::ROTATE_DOWN:
		if (GetRightStick(STICK_TYPE::MOVE_DOWN, nIdx)) {
			return true;
		}
		break;
	case CODE::ROTATE_LEFT:
		if (GetRightStick(STICK_TYPE::MOVE_LEFT, nIdx)) {
			return true;
		}
		break;
	case CODE::ROTATE_RIGHT:
		if (GetRightStick(STICK_TYPE::MOVE_RIGHT, nIdx)) {
			return true;
		}
		break;

		//�A�N�Z��
	case CODE::ACCELE:
		if (GetButtonPress(XINPUT_GAMEPAD_A, nIdx)) {
			return true;
		}
		break;

		//�o�b�N
	case CODE::REVERSE:
		if (GetButtonPress(XINPUT_GAMEPAD_B, nIdx)) {
			return true;
		}
		break;

	}
	return false;
}

//=============================================================================
// �Q�[���p�b�h�̓��͔���i�g���K�[�j
//=============================================================================
bool CInputGamepadX::GetTrigger(CODE code, int nIdx) {
	switch (code)
	{
		//�I��
	case CODE::SELECT:
		if (GetButtonTrigger(XINPUT_GAMEPAD_A, nIdx)) {
			return true;
		}
		break;
		//�߂�
	case CODE::BACK:
		if (GetButtonTrigger(XINPUT_GAMEPAD_B, nIdx) || GetButtonTrigger(XINPUT_GAMEPAD_BACK, nIdx)) {
			return true;
		}
		break;
		//�|�[�Y
	case CODE::PAUSE:
		if (GetButtonTrigger(XINPUT_GAMEPAD_START, nIdx)) {
			return true;
		}
		break;

		//�㉺���E
	case CODE::MOVE_UP:
		if (GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP, nIdx)) {
			return true;
		}
		break;
	case CODE::MOVE_DOWN:
		if (GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN, nIdx)) {
			return true;
		}
		break;
	case CODE::MOVE_LEFT:
		if (GetButtonTrigger(XINPUT_GAMEPAD_DPAD_LEFT, nIdx)) {
			return true;
		}
		break;
	case CODE::MOVE_RIGHT:
		if (GetButtonTrigger(XINPUT_GAMEPAD_DPAD_RIGHT, nIdx)) {
			return true;
		}
		break;


		//�I���̏㉺���E
	case CODE::SELECT_UP:
		if (GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP, nIdx)) {
			return true;
		}
		break;
	case CODE::SELECT_DOWN:
		if (GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN, nIdx)) {
			return true;
		}
		break;
	case CODE::SELECT_LFET:
		if (GetButtonTrigger(XINPUT_GAMEPAD_DPAD_LEFT, nIdx)) {
			return true;
		}
		break;
	case CODE::SELECT_RIGHT:
		if (GetButtonTrigger(XINPUT_GAMEPAD_DPAD_RIGHT, nIdx)) {
			return true;
		}
		break;


		//�A�C�e���̎g�p
	case CODE::USE_ITEM:
		if (GetButtonTrigger(XINPUT_GAMEPAD_L, nIdx)) {
			return true;
		}
		break;

		//�A�^�b�N
	case CODE::CAR_ATTACK:
		if (GetButtonTrigger(XINPUT_GAMEPAD_R, nIdx)) {
			return true;
		}
		break;

		//�`�F�b�N
	case CODE::CHECK_X:
		if (GetButtonTrigger(XINPUT_GAMEPAD_X, nIdx)) {
			return true;
		}
		break;
	case CODE::CHECK_B:
		if (GetButtonTrigger(XINPUT_GAMEPAD_B, nIdx)) {
			return true;
		}
		break;
	case CODE::CHECK_A:
		if (GetButtonTrigger(XINPUT_GAMEPAD_A, nIdx)) {
			return true;
		}
		break;
	case CODE::CHECK_Y:
		if (GetButtonTrigger(XINPUT_GAMEPAD_Y, nIdx)) {
			return true;
		}
		break;

	}
	return false;
}

//=============================================================================
// �Q�[���p�b�h�̃o�C�u���[�V�����̐ݒ�(Xinput)
//=============================================================================
void CInputGamepadX::SetVibration(int nLeftValue, int nRightValue, int nCntVibration, int nIdx) {
	m_aVibrationState[nIdx].wLeftMotorSpeed = nLeftValue; // use any value between 0-65535 here
	m_aVibrationState[nIdx].wRightMotorSpeed = nRightValue; // use any value between 0-65535 here
	XInputSetState(0, &m_aVibrationState[nIdx]);
	m_aCntVibration[nIdx] = nCntVibration;
	m_abVibration[nIdx] = true;
}