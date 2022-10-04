//===========================================
//�t�F�[�h����
//Author:��������
//===========================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"
#include "object.h"
#include "object2D.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CFade : public CObject2D
{
public:
	//�t�F�[�h�̎��
	typedef enum
	{
		FADE_NONE = 0,		//�������Ă��Ȃ�
		FADE_IN,			//�t�F�[�h�C��
		FADE_OUT,			//�t�F�[�h�A�E�g
		FADE_MAX
	} FADE;

	CFade(CObject::PRIORITY Priority = CObject::PRIORITY::FADE);		//�R���X�g���N�^
	~CFade();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	FADE GetFade(void);
	void SetFade(const CManager::MODE &modeNext);
	static CFade *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const CManager::MODE &modeNext);

private:
	FADE m_fade;							//�t�F�[�h�̏��
	CManager::MODE m_modeNext;				//���̉��(���[�h)
	D3DXCOLOR m_color;						//�t�F�[�h�̐F
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_size;						//�T�C�Y
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_FADE_H_