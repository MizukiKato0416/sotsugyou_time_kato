//===========================================
//�L�[�{�[�h���͏���
//Author:��������
//===========================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_
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
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();				//�R���X�g���N�^
	~CInputKeyboard();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const HINSTANCE &hInstance, const HWND &hWnd);
	void Uninit(void);
	void Update(void);
	pair<int, bool> GetAllKeyUpdate(void);	// �ǂ̃L�[�������ꂽ��
	bool GetPress(const int &nKey);
	bool GetTrigger(const int &nKey);
	bool GetRelease(const int &nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏��
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏��
};

#endif // !_INPUT_KEYBOARD_H_