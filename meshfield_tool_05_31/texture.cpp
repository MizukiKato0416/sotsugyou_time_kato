//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : �H������
//
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	m_file_data.type.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^
	int element_max;		// �e�N�X�`���J�E���g�l
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X���擾����

	// �t�@�C����ǂݍ���
	m_file_data.file_name_pas = CFileLoad::Load("data\\TEXTURE\\");
	element_max = m_file_data.file_name_pas.second.size();

	for (int count_element = 0; count_element < element_max; count_element++)
	{
		// �^���񋓌^�����
		m_file_data.type[m_file_data.file_name_pas.second[count_element]] = count_element;
	}
	// �p�X�ƃT�C�Y��ۑ�
	m_file_data.pas = m_file_data.file_name_pas.first;
	m_num_tex = m_file_data.file_name_pas.first.size();

	// �T�C�Y����
	for (int nCntTex = 0; nCntTex < m_num_tex; nCntTex++)
	{
		LPDIRECT3DTEXTURE9 pTexBuffer = NULL;	// �e�N�X�`���̃o�b�t�@
		//�e�N�X�`���̐���
		D3DXCreateTextureFromFile(	pDevice,
									m_file_data.pas[nCntTex].c_str(),
									&pTexBuffer);
		// vector�Ɋi�[
		m_texture.push_back(pTexBuffer);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < m_num_tex; nCntTexture++)
	{
		// �e�N�X�`���̔j��
		if (m_texture[nCntTexture] != NULL)
		{
			m_texture[nCntTexture]->Release();
			m_texture[nCntTexture] = NULL;
		}
	}
}