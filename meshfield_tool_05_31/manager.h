//===========================================
//�}�l�[�W������
//Author:��������
//===========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "object.h"
#include "camera.h"
#include "light.h"

//�O���錾
class CRenderer;
class CInputKeyboard;
class CInputPadX;
class CInputPadD;
class CInputMouse;
class CTexture;
class CGame01;
class CFade;
class CXload;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CManager
{
public:
	//���[�h�̎��
	enum class MODE
	{
		GAME01 = 0,		//�Q�[��01
		MAX
	};

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CManager *GetInstance(void);											//�C���X�^���X�擾����
	static CRenderer *GetRenderer(void);										//�����_���[�擾����
	static CInputKeyboard *GetInputKeyboard(void);								//�L�[�{�[�h�擾����
	static CInputPadX *GetInputPadX(void);										//�p�b�h(X)�擾����
	static CInputPadD *GetInputPadD(void);										//�p�b�h(D)�擾����
	static CInputMouse *GetInputMouse(void);									//�}�E�X�擾����
	static CLight *GetLight(void);												//���C�g�擾����
	static CTexture *GetTexture(void);											//�e�N�X�`���擾����
	static CCamera** GetCamera(void);											//�J�����擾����
	static CXload *GetXload(void);												//x�t�@�C���ǂݍ��ݎ擾����
	static CGame01 *GetGame01(void);											//�Q�[��01�擾����
	static void SetMode(MODE mode);												//���[�h�ݒ�
	static MODE GetMode(void);													//���[�h�擾
	static CFade *GetFade(void);												//�t�F�[�h�擾����
	static HWND GetWindowHandle(void) { return m_hWnd; }						//hwnd�擾����

private:
	//�����o�֐�
	CManager();				//�R���X�g���N�^
	~CManager();			//�f�X�g���N�^

	static CManager *s_pManager;						//�}�l�[�W���[�̃C���X�^���X
	static CRenderer *m_pRenderer;						//�����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;			//�L�[�{�[�h�̃|�C���^
	static CInputPadX *m_pInputPadX;					//�p�b�h(X)�̃|�C���^
	static CInputPadD *m_pInputPadD;					//�p�b�h(D)�̃|�C���^
	static CInputMouse *m_pInputMouse;					//�}�E�X�̃|�C���^
	static CLight *m_apLight[MAX_LIGHT];				//���C�g�̃|�C���^
	static CTexture *m_pTexture;						//�e�N�X�`���̃|�C���^
	static CCamera* m_apCamera[MAX_CAMERA];				//�J�����̃|�C���^
	static CXload *m_pXload;							//x�t�@�C���ǂݍ��݂̃|�C���^
	static CGame01 *m_pGame01;							//�Q�[��01�̃|�C���^
	static MODE m_mode;									//���[�h
	static CFade *m_pFade;								//�t�F�[�h�̃|�C���^
	static HWND m_hWnd;									//�E�B���h�E�n���h��
};


#endif // !_MANAGER_H_