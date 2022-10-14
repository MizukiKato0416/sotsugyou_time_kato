//===========================================
//�}�E�X���͏���
//Author:��������
//===========================================
#ifndef _INPUT_MOUSE_H_
#define _INPUT_MOUSE_H_
#include "input.h"

//================================================
//�}�N����`
//================================================
#define NUM_KEY_MAX (256)		//�L�[�̍ő吔


//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CInputMouse : public CInput
{
public:
	typedef enum
	{
		MOUSE_TYPE_LEFT = 0,
		MOUSE_TYPE_RIGHT,
		MOUSE_TYPE_WHEEL,
		MOUSE_TYPE_MAX
	} MOUSE_TYPE;

	CInputMouse();			//�R���X�g���N�^
	~CInputMouse();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const HINSTANCE &hInstance, const HWND &hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(const int &nMouse);
	bool GetTrigger(const int &nMouse);
	bool GetRelease(const int &nMouse);
	DIMOUSESTATE2 GetMouseState(void);	//�}�E�X�̓��͏��擾����

	D3DXVECTOR2 GetMouseVelocity(void);	//�}�E�X�̈ړ��ʎ擾����

private:
	DIMOUSESTATE2 m_mouseState;
	DIMOUSESTATE2 m_mouseStateTrigger;			//�}�E�X�̓��͏��
	DIMOUSESTATE2 m_mouseStateRelease;			//�}�E�X�̓��͏��
};

#endif // !_INPUT_MOUSE_H_