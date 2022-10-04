//================================================
//�}�l�[�W������
//Author:��������
//================================================
#include "renderer.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "input_pad_d.h"
#include "input_mouse.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "texture.h"
#include "x_load.h"
#include "game01.h"
#include "fade.h"
#include "sound.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
CManager *CManager::s_pManager = nullptr;
CRenderer *CManager::m_pRenderer = nullptr;
CInputKeyboard *CManager::m_pInputKeyboard = nullptr;
CInputPadX *CManager::m_pInputPadX = nullptr;
CInputPadD *CManager::m_pInputPadD = nullptr;
CInputMouse *CManager::m_pInputMouse = nullptr;
CCamera* CManager::m_apCamera[MAX_CAMERA] = { nullptr };
CLight *CManager::m_apLight[MAX_LIGHT] = { nullptr };
CTexture *CManager::m_pTexture = nullptr;
CXload *CManager::m_pXload = nullptr;
CGame01 *CManager::m_pGame01 = nullptr;
CManager::MODE CManager::m_mode = MODE::GAME01;
CFade *CManager::m_pFade = nullptr;
HWND CManager::m_hWnd = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CManager::CManager()
{
	
}

//================================================
//�f�X�g���N�^
//================================================
CManager::~CManager()
{

}

//================================================
//����������
//================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����ŏ�����
	srand((unsigned int)time(NULL));

	m_hWnd = hWnd;

	//�����_�����O�N���X�̐���
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer;
		if (m_pRenderer != nullptr)
		{
			m_pRenderer->Init(hWnd, bWindow);
		}
	}

	//�L�[�{�[�h�N���X�̐���
	if (m_pInputKeyboard == nullptr)
	{
		m_pInputKeyboard = new CInputKeyboard;
		if (m_pInputKeyboard != nullptr)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	//X�p�b�h�N���X�̐���
	if (m_pInputPadX == nullptr)
	{
		m_pInputPadX = new CInputPadX;
		if (m_pInputPadX != nullptr)
		{
			m_pInputPadX->Init(hInstance, hWnd);
		}
	}

	//D�p�b�h�N���X�̐���
	if (m_pInputPadD == nullptr)
	{
		m_pInputPadD = new CInputPadD;
		if (m_pInputPadD != nullptr)
		{
			m_pInputPadD->Init(hInstance, hWnd);
		}
	}

	//�}�E�X�N���X�̐���
	if (m_pInputMouse == nullptr)
	{
		m_pInputMouse = new CInputMouse;
		if (m_pInputMouse != nullptr)
		{
			m_pInputMouse->Init(hInstance, hWnd);
		}
	}

	//�e�N�X�`���N���X�̐���
	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture;
		if (m_pTexture != nullptr)
		{
			m_pTexture->Init();
		}
	}

	//x�t�@�C���ǂݍ��݃N���X�̐���
	if (m_pXload == nullptr)
	{
		m_pXload = new CXload;
		if (m_pXload != nullptr)
		{
			m_pXload->Init();
		}
	}

	//���C�g�̐���
	m_apLight[0] = CLight::Create(D3DXVECTOR3(-0.6f, -0.5f, 0.6f), D3DXVECTOR3(40000.0f, 80000.0f, -40000.0f));
	m_apLight[1] = CLight::Create(D3DXVECTOR3(0.4f, 0.5f, -0.4f), D3DXVECTOR3(-10000.0f, 0.0f, 10000.0f));
	m_apLight[2] = CLight::Create(D3DXVECTOR3(0.0f, -0.2f, 0.6f), D3DXVECTOR3(10000.0f, 0.0f, -10000.0f));

	//�t�F�[�h�N���X�̐���
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
							MODE::GAME01);	

	return S_OK;
}

//================================================
//�I������
//================================================
void CManager::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	//X�t�@�C���ǂݍ��݃N���X�̔j��
	if (m_pXload != nullptr)
	{
		//�I������
		m_pXload->Uninit();

		//�������̊J��
		delete m_pXload;
		m_pXload = nullptr;
	}

	//�J�����̔j��
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (m_apCamera[nCntCamera] != nullptr)
		{
			//�I������
			m_apCamera[nCntCamera]->Uninit();

			//�������̊J��
			delete m_apCamera[nCntCamera];
			m_apCamera[nCntCamera] = nullptr;
		}
	}

	//���C�g�̔j��
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		if (m_apLight[nCntLight] != nullptr)
		{
			//�I������
			m_apLight[nCntLight]->Uninit();

			//�������̊J��
			delete m_apLight[nCntLight];
			m_apLight[nCntLight] = nullptr;
		}
	}

	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		//�I������
		m_pTexture->Uninit();

		//�������̊J��
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//�}�E�X�N���X�̔j��
	if (m_pInputMouse != nullptr)
	{
		//�I������
		m_pInputMouse->Uninit();

		//�������̊J��
		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}

	//D�p�b�h�N���X�̔j��
	if (m_pInputPadD != nullptr)
	{
		//�I������
		m_pInputPadD->Uninit();

		//�������̊J��
		delete m_pInputPadD;
		m_pInputPadD = nullptr;
	}

	//X�p�b�h�N���X�̔j��
	if (m_pInputPadX != nullptr)
	{
		//�I������
		m_pInputPadX->Uninit();

		//�������̊J��
		delete m_pInputPadX;
		m_pInputPadX = nullptr;
	}

	//�L�[�{�[�h�N���X�̔j��
	if (m_pInputKeyboard != nullptr)
	{
		//�I������
		m_pInputKeyboard->Uninit();

		//�������̊J��
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//�����_���[�N���X�̔j��
	if (m_pRenderer != nullptr)
	{
		//�I������
		m_pRenderer->Uninit();

		//�������̊J��
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//�������̊J��
	delete s_pManager;
	s_pManager = nullptr;
}

//================================================
//�X�V����
//================================================
void CManager::Update(void)
{
	//�L�[�{�[�h
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	//D�p�b�h
	if (m_pInputPadD != nullptr)
	{
		m_pInputPadD->Update();
	}

	//�}�E�X
	if (m_pInputMouse != nullptr)
	{
		m_pInputMouse->Update();
	}

	//X�p�b�h
	if (m_pInputPadX != nullptr)
	{
		m_pInputPadX->Update();
	}

	//�����_���[
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	//�J�����̍X�V����
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (m_apCamera[nCntCamera] != nullptr)
		{
			m_apCamera[nCntCamera]->Update();
		}
	}
}

//================================================
//�`�揈��
//================================================
void CManager::Draw(void)
{
	//�����_���[
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}

//================================================
//�C���X�^���X�擾����
//================================================
CManager *CManager::GetInstance(void)
{
	if (s_pManager == nullptr)
	{
		s_pManager = new CManager;
	}
	return s_pManager;
}

//=============================================================================
// Renderer�擾����
//=============================================================================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// InputKeyboard�擾����
//=============================================================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// InputXPad�擾����
//=============================================================================
CInputPadX* CManager::GetInputPadX(void)
{
	return m_pInputPadX;
}

//=============================================================================
// InputDPad�擾����
//=============================================================================
CInputPadD* CManager::GetInputPadD(void)
{
	return m_pInputPadD;
}

//=============================================================================
// �}�E�X�擾����
//=============================================================================
CInputMouse * CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//=============================================================================
// light�擾����
//=============================================================================
CLight* CManager::GetLight(void)
{
	return m_apLight[0];
}

//=============================================================================
// �e�N�X�`���擾����
//=============================================================================
CTexture* CManager::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// camera�擾����
//=============================================================================
CCamera** CManager::GetCamera(void)
{
	return &m_apCamera[0];
}

//=============================================================================
// Xload�擾����
//=============================================================================
CXload* CManager::GetXload(void)
{
	return m_pXload;
}

//=============================================================================
// game01�擾����
//=============================================================================
CGame01* CManager::GetGame01(void)
{
	return m_pGame01;
}

//=======================================================================
//���[�h�ݒ菈��
//=======================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE::GAME01:
		if (m_pGame01 != nullptr)
		{
			//�J�����̔j��
			for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
			{
				if (m_apCamera[nCntCamera] != nullptr)
				{
					//�I������
					m_apCamera[nCntCamera]->Uninit();

					//�������̊J��
					delete m_apCamera[nCntCamera];
					m_apCamera[nCntCamera] = nullptr;
				}
			}

			m_pGame01->Uninit();
			m_pGame01 = nullptr;
		}
		break;
	default:
		break;
	}

	//�S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	m_mode = mode;

	switch (mode)
	{
	case MODE::GAME01:
		//�Q�[��01�N���X�̐���
		if (m_pGame01 == nullptr)
		{
			m_pGame01 = new CGame01;
			if (m_pGame01 != nullptr)
			{
				//���C���J�����̐���
				for (int nCntCamera = 0; nCntCamera < MAX_MAIN_CAMERA; nCntCamera++)
				{
					m_apCamera[nCntCamera] = CCamera::Create(CAMERA_INIT_POS, D3DXVECTOR3(CAMERA_INIT_ROT_X, D3DX_PI, 0.0f),
																(float)(SCREEN_WIDTH / MAX_MAIN_CAMERA * nCntCamera), 0.0f,
																(float)(SCREEN_WIDTH / MAX_MAIN_CAMERA), (float)SCREEN_HEIGHT);
					m_apCamera[nCntCamera]->SetNum(nCntCamera);
				}

				m_pGame01->Init();
			}
		}
		break;
	}
}


//=============================================================================
// ���[�h�擾����
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// fade�擾����
//=============================================================================
CFade* CManager::GetFade(void)
{
	return m_pFade;
}