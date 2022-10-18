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
class CObjectPlayerIcon : public CObject
{
public:
	enum class STATE
	{
		ADD_ALPHA = 0,	//���l���Z
		NONE,			//�������Ȃ�
		DEC_ALPHA,		//���l���Z
		MAX
	};

	CObjectPlayerIcon();		//�f�t�H���g�R���X�g���N�^
	~CObjectPlayerIcon();	//�f�X�g���N�^
	static CObjectPlayerIcon* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 scale,
		                       const CTexture::TEXTURE_TYPE texTypeFrame, const CTexture::TEXTURE_TYPE texTypePlayerNum);	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void) {}	//�`�揈��

	//��Ԏ擾����
	STATE GetState(void) { return m_state; }
	//��Ԑݒ菈��
	void SetState(STATE state) { m_state = state; }

	//�t���[���̃|�C���^�擾����
	CObject2D *GetFrame(void) { return m_pFrame; }
	//�v���C���[�ԍ��̃|�C���^�擾����
	CObject2D *GetPlayerNum(void) { return m_pPlayerNum; }

private:
	void StateAddAlpha();		//���l���Z����
	void StateNone();			//�������Ȃ�����
	void StateDecAlpha();		//���l���Z����

	D3DXVECTOR3 m_scale;							//�X�P�[��
	D3DXVECTOR3 m_pos;								//�ʒu
	STATE m_state;									//���

	CTexture::TEXTURE_TYPE m_texTypeFrame;			//�t���[���̃e�N�X�`��
	CObject2D *m_pFrame;							//�t���[���̃|�C���^

	CTexture::TEXTURE_TYPE m_texTypePlayerNum;		//�v���C���[�ԍ��̃e�N�X�`��
	CObject2D *m_pPlayerNum;						//�v���C���[�ԍ��̃|�C���^

};

#endif // !_PLAYER_ICON_H_