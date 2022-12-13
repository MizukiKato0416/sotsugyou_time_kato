//=============================================================================
//
// ���͏��� [input.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PAD_CONNECT_NUM	(4)		//�Q�[���p�b�h�ڑ���

//*****************************************************************************
// �C���v�b�g�N���X
//*****************************************************************************
class CInput
{
public:
	enum class CODE {
		//�V�X�e��
		SELECT = 0,
		BACK,
		PAUSE,
		//�ړ�
		MOVE_UP,	//��
		MOVE_DOWN,	//��
		MOVE_LEFT,	//��
		MOVE_RIGHT,	//�E
		MOVE_RISE,	//�㏸
		MOVE_FALL,	//���~
		//��]
		ROTATE_UP,		//��
		ROTATE_DOWN,	//��
		ROTATE_LEFT,	//��
		ROTATE_RIGHT,	//�E
		//�I��
		SELECT_UP,
		SELECT_DOWN,
		SELECT_LEFT,
		SELECT_RIGHT,
		//�A�N�V����
		ACCELE,			//�A�N�Z��
		REVERSE,		//�o�b�N
		USE_ITEM,		//�A�C�e���̎g�p
		CAR_ATTACK,		//�A�^�b�N
		CAR_DEFENSE,	//�`�[�g�p�f�B�t�F���X
		//�`�F�b�N
		CHECK_X,		//X�{�^��
		CHECK_B,		//B�{�^��
		CHECK_A,		//A�{�^��
		CHECK_Y,		//Y�{�^��

#ifdef _DEBUG
		//�f�o�b�O�p
		DEBUG_0,
		DEBUG_1,
		DEBUG_2,
		DEBUG_3,
#endif

		CODE_MAX
	};

	CInput();			//�f�t�H���g�R���X�g���N�^
	virtual ~CInput();	//�f�X�g���N�^
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//����������
	virtual void Uninit(void);		//�I������
	virtual void Update(void) = 0;		//�X�V����
	virtual bool GetPress(CODE code, int nIdx) = 0;		//���͔���i�v���X�j
	virtual bool GetTrigger(CODE code, int nIdx) = 0;	//���͔���i�g���K�[�j

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;
	static LPDIRECTINPUT8 m_pInput;
};

//*****************************************************************************
// �L�[�{�[�h�N���X
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(CODE code, int nIdx);	//���͔���i�v���X�j
	bool GetTrigger(CODE code, int nIdx);	//���͔���i�g���K�[�j

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:
	BYTE m_aKeyState[256];
	BYTE m_aKeyStateTrigger[256];
};

//*****************************************************************************
// �Q�[���p�b�h�N���X(Xinput)
//*****************************************************************************
class CInputGamepadX : public CInput
{
public:
	//�g���K�[�̍��E
	enum class TRIGGER_TYPE {
		RIGHT = 0,
		LEFT,
		ENUM_MAX
	};

	//�X�e�B�b�N�̏㉺���E
	enum class STICK_TYPE {
		MOVE_UP = 0,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		ENUM_MAX
	};

	CInputGamepadX();	//�f�t�H���g�R���X�g���N�^
	~CInputGamepadX();	//�f�X�g���N�^
	void Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	bool GetPress(CODE code, int nIdx);	//���͔���i�v���X�j
	bool GetTrigger(CODE code, int nIdx);	//���͔���i�g���K�[�j

	bool GetConnectGamepad(int nIdx);	//�Q�[���p�b�h�ڑ��̔���
	bool GetButtonPress(int nButton, int nIdx);		//�{�^���̃v���X����
	bool GetButtonTrigger(int nButton, int nIdx);		//�{�^���̃g���K�[����
	bool GetTriggerPress(TRIGGER_TYPE type, int nIdx);		//�g���K�[�̃v���X����
	bool GetTriggerTrigger(TRIGGER_TYPE type, int nIdx);	//�g���K�[�̃g���K�[����
	bool GetLeftStick(STICK_TYPE type, int nIdx);			//���X�e�B�b�N�̔���
	bool GetRightStick(STICK_TYPE type, int nIdx);			//�E�X�e�B�b�N�̔���
	void SetVibration(int nLeftValue, int nRightValue, int nCntVibration, int nIdx);	//�o�C�u���[�V�����̐ݒ�

private:
	XINPUT_STATE m_aState[MAX_PAD_CONNECT_NUM];		//�R���g���[���[�̏��
	XINPUT_STATE m_aStateLast[MAX_PAD_CONNECT_NUM];	//�R���g���[���[�̂ЂƂO�̏�ԁi�g���K�[����p�j
	XINPUT_VIBRATION m_aVibrationState[MAX_PAD_CONNECT_NUM];	//�o�C�u���[�V����
	bool m_abConnect[MAX_PAD_CONNECT_NUM];		//�ڑ��m�F
	int m_aCntVibration[MAX_PAD_CONNECT_NUM];	//�o�C�u���[�V�����p�̃J�E���^�[
	bool m_abVibration[MAX_PAD_CONNECT_NUM];	//�o�C�u���[�V���������s�����ǂ���
};

#endif // !_INPUT_H_