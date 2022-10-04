//===========================================
//�p�b�h����(�_�C���N�g)����
//Author:��������
//===========================================
#ifndef _INPUT_PAD_D_H_
#define _INPUT_PAD_D_H_
#include "input.h"

//================================================
//�}�N����`
//================================================
#define STICK_POW (1000)

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CInputPadD : public CInput
{
public:
	//�{�^���̎��
	typedef enum
	{
		X = 0,
		Y,
		A,
		B,
		L,
		R,
		L2,
		R2,
		L_STICK,
		R_STICK,
		BACK,
		START,
		BUTTOM,
		HOME,
		BUTTON_MAX,
	} PADBUTTON;

	//�����o�֐�
	CInputPadD();		//�f�t�H���g�R���X�g���N�^
	~CInputPadD();		//�f�X�g���N�^

	HRESULT Init(const HINSTANCE &hInstance, const HWND &hWnd);		//������
	void Uninit(void);									//�I��
	void Update(void);									//�X�V

	bool GetPress(const int &Botton_Type);						//����
	bool GetTrigger(const int &Botton_Type);					//��񉟂�
	bool GetRelease(const int &Botton_Type);					//������
	DIJOYSTATE2 GetGamepad(void);						//�Q�[���p�b�h���擾
	DIJOYSTATE2 GetGamepadOld(void);					//1�t���[���O�̃Q�[���p�b�h���擾
	static BOOL CALLBACK EnumJoysticksCallback(const LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);

private:
	DIDEVCAPS m_diDevCaps;
	DIJOYSTATE2 m_aState;				//���͏��
	DIJOYSTATE2 m_aStateOld;			//1�t���[���O�̓��͏��
	DIJOYSTATE2 m_aStateTrigger;        //���͏��(�g���K�[)
	DIJOYSTATE2 m_aStateRelease;        //���͏��(�����[�X)
};
#endif // !_INPUT_PAD_D_H_