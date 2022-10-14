//===========================================
//���͏���
//Author:��������
//===========================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//================================================
//�}�N����`
//================================================

//================================================
//�\���̂̒�`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CInput
{
public:
	//�����o�֐�
	CInput();					//�R���X�g���N�^
	virtual ~CInput();			//�f�X�g���N�^

	virtual HRESULT Init(const HINSTANCE &hInstance, const HWND &hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;


protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;
	static LPDIRECTINPUTDEVICE8 m_pDeviceJoyStick;
	static LPDIRECTINPUT8 m_pInput;
};

#endif // !_INPUT_H_