//=============================================================================
//
// �e�N�X�`������ [texture.cpp]
// Author : �ߊԏr��
//
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXT_FILE_NAME_TEXTURE "data/TEXT/load_texture.txt"
#define MAX_LOAD_TEXT (128)		//��x�Ƀt�@�C������ǂݍ��ރe�L�X�g�̃o�C�g��

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[(int)TEXTURE_TYPE::ENUM_MAX] = {};
char CTexture::m_asFilePath[(int)TEXTURE_TYPE::ENUM_MAX][MAX_TEXTURE_FILE_PATH] = {};

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CTexture::Load(const char* sLoadType) {
	LPDIRECT3DDEVICE9 pDevice = nullptr;	//�f�o�C�X�ւ̃|�C���^
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	//�����_���[�̎擾
	CRenderer* pRenderer = nullptr;
	if (pManager != nullptr) pRenderer = pManager->GetRenderer();
	//�f�o�C�X�̎擾
	if (pRenderer != nullptr) pDevice = pRenderer->GetDevice();
	//�f�o�C�X��null�̏ꍇ�I��
	if (pDevice == nullptr) return S_OK;

	//-------------------------------------
	//�t�@�C���̓ǂݍ���
	//-------------------------------------
	FILE *pFile;		//�t�@�C���ւ̃|�C���^
	char sLoadText[MAX_LOAD_TEXT];//��s���ǂݍ��ރt�@�C���̃e�L�X�g
	char *pLoadText;	//�t�@�C���̃e�L�X�g�𕪊�����������

	bool bLoadTexture[(int)TEXTURE_TYPE::ENUM_MAX];	//�e�N�X�`���ǂݍ��݃t���O
	memset(&bLoadTexture, 0, sizeof(bLoadTexture));	//false�ŏ�����

	//�t�@�C�����J��
	pFile = fopen(TEXT_FILE_NAME_TEXTURE, "r");
	if (pFile == nullptr) return S_OK;	//���[�h�I��

	for (int nIdxType = 1; //���ɓǂݍ��ރe�N�X�`���̎��	0��NONE�����邽��1����
		fgets(sLoadText, MAX_LOAD_TEXT, pFile) != nullptr && nIdxType < (int)TEXTURE_TYPE::ENUM_MAX;) //��s���Ƃɕ�������擾
	{
		pLoadText = strtok(sLoadText, " \t\n");	//������̕����i�� �^�u ���s�j
		//�e�L�X�g���Ȃ�
		if (pLoadText == nullptr) continue;
		//�R�����g
		if (strstr(pLoadText, "//") != nullptr) continue;

		//�f�B���N�g�����̃R�s�[
		if (strlen(pLoadText) < MAX_TEXTURE_FILE_PATH) {
			strcpy(m_asFilePath[nIdxType], pLoadText);
		}

		//������̕����i�� �^�u ���s = ,�j
		pLoadText = strtok(nullptr, " ,=\t\n");

		while (pLoadText != nullptr)
		{
			//�ǂݍ��݂̃^�C�v�ƈ�v���Ă����ꍇ�I��
			bLoadTexture[nIdxType] = strcmp(pLoadText, sLoadType) == 0 || strcmp(pLoadText, "all") == 0;
			if (bLoadTexture[nIdxType]) break;

			//������̕����i�� �^�u ���s = ,�j
			pLoadText = strtok(nullptr, " ,=\t\n");
		}

		//�ǂݍ��ރC���f�b�N�X�̉��Z
		nIdxType++;
	}
	//�t�@�C�������
	fclose(pFile);

	//0��NONE�����邽��1����
	for (int nCnt = 1; nCnt < (int)TEXTURE_TYPE::ENUM_MAX; nCnt++)
	{
		//���łɃe�N�X�`������������Ă����ꍇ�j��
		if (m_apTexture[nCnt] != nullptr) {
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}

		//�ǂݍ��݃t���O�������Ă��Ȃ��ꍇ
		if (!bLoadTexture[nCnt]) continue;

		//�e�N�X�`���̐���
		D3DXCreateTextureFromFile(pDevice,
			m_asFilePath[nCnt],	// �e�N�X�`���p�X
			&m_apTexture[nCnt]);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CTexture::Unload(void) {
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < (int)TEXTURE_TYPE::ENUM_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
	}
}

//=============================================================================
// �e�N�X�`���̎擾
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE type) {
	if (type < (TEXTURE_TYPE)0 || type >= TEXTURE_TYPE::ENUM_MAX) return nullptr;
	return m_apTexture[(int)type];
}

//=============================================================================
// �e�N�X�`���̎擾
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(char* texPath) {
	for (int nCnt = 0; nCnt < (int)TEXTURE_TYPE::ENUM_MAX; nCnt++)
	{
		//�e�N�X�`���̃p�X�ƈ�v���Ă����ꍇ
		if (strcmp(m_asFilePath[nCnt], texPath) == 0) {
			return m_apTexture[nCnt];
		}
	}
	return nullptr;
}

//=============================================================================
// �e�N�X�`���̃p�X�̎擾
//=============================================================================
char* CTexture::GetPathName(TEXTURE_TYPE type) {
	if (type < (TEXTURE_TYPE)0 || type >= TEXTURE_TYPE::ENUM_MAX) return nullptr;
	return m_asFilePath[(int)type];
}