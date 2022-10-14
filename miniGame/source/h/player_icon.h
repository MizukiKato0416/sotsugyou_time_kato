//=============================================================================
//
// �v���C���[�̃A�C�R������ [player_icon.h]
// Author : ��������
//
//=============================================================================
#ifndef _PLAYER_ICON_H_
#define _PLAYER_ICON_H_

#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CObject2D;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CPlayerIcon : public CObject
{
public:
	CPlayerIcon();		//�f�t�H���g�R���X�g���N�^
	~CPlayerIcon();	//�f�X�g���N�^
	static CPlayerIcon* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale,
		                       const CTexture::TEXTURE_TYPE texTypeFrame, const CTexture::TEXTURE_TYPE texTypePlayerNum);	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void) {}	//�`�揈��

private:
	D3DXVECTOR3 m_scale;								//�X�P�[��
	CTexture::TEXTURE_TYPE m_texTypeFrame;				//�t���[���̃e�N�X�`��
	CTexture::TEXTURE_TYPE m_texTypePlayerNum;			//�v���C���[�ԍ��̃e�N�X�`��
};

#endif // !_PLAYER_ICON_H_