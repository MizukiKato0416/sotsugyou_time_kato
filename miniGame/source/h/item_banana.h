//=============================================================================
//
// �A�C�e���o�i�i���� [item_banana.h]
// Author : ��������
//
//=============================================================================
#ifndef _ITEM_BANANA_H_
#define _ITEM_BANANA_H_

#include "item.h"
#include "objectModel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CObjectPlayerBalloonCar;

//*****************************************************************************
// �A�C�e���o�i�i�N���X
//*****************************************************************************
class CItemBanana : public CItem
{
public:
	CItemBanana();	//�f�t�H���g�R���X�g���N�^
	CItemBanana(CModel::MODELTYPE typeModel);		//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	virtual ~CItemBanana();	//�f�X�g���N�^
	static CItemBanana* Create(D3DXVECTOR3 pos, CObjectPlayerBalloonCar *pPlayer);	//��������
	virtual HRESULT Init(void);				//����������
	virtual void Uninit(void);				//�I������
	virtual void Update(void);				//�X�V����
	virtual void Draw(void);				//�`�揈��

	//�v���C���[�Ƀq�b�g�����Ƃ��̏���
	virtual void HitPlayer(CObjectPlayerBalloonCar *pPlayer);

private:
	D3DXVECTOR3 m_move;		//�ړ���

};

#endif // !_ITEM_BANANA_H_