//=============================================================================
//
// �`�F�b�N�A�C�R������ [check_icon.h]
// Author : ��������
//
//=============================================================================
#ifndef _CHECK_ICON_H_
#define _CHECK_ICON_H_

#include "object.h"
#include "object_player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CObject2D;
class CObjectModelUI;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCheckIcon : public CObject
{
public:
	CCheckIcon();		//�f�t�H���g�R���X�g���N�^
	~CCheckIcon();		//�f�X�g���N�^
	static CCheckIcon* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 posModel, const D3DXVECTOR3 scale, const int nPlayerNum);	//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void) {}	//�`�揈��

	//�m�F�ł������擾����
	bool GetCheck() { return m_bCheck; }
	//�������擾����
	bool GetUninit() { return m_bUninit; }
	//�������ݒ菈��
	void SetUninit(const bool bUninit, const int nDelay) { m_bUninit = bUninit, m_nDelay = nDelay; }
	//�t���[���̃|�C���^�擾����
	CObject2D *GetFrame(void) { return m_pFrame; }
	//�{�^���̃|�C���^�擾����
	CObject2D *GetButton(void) { return m_pButton; }

private:
	//���菈��
	void Decide();
	//���l���Z����
	void DecAlpha();
	//�}�e���A���ݒ菈��
	void SetMaterial(CObjectModelUI *pPlayerModel);
	//���f����]����
	void RotateModel();
	//���f���I������
	void SelectModel();

	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_posModel;					//���f���̏����ʒu
	D3DXVECTOR3 m_scale;					//�X�P�[��
	CObject2D *m_pFrame;					//�t���[��
	CObject2D *m_pButton;					//�{�^��
	CObjectModelUI *m_pPlayerModel;			//�v���C���[�̃��f��

	int m_nPlayerNum;			//�v���C���[�ԍ�
	int m_nCounter;				//�t���[���J�E���g�p
	int m_nDelay;				//�x���p

	bool m_bCheck;				//�m�F�ł������ǂ���
	bool m_bUninit;				//�������ǂ���
};

#endif // !_CHECK_ICON_H_