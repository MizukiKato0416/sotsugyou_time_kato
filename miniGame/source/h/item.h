//=============================================================================
//
// �A�C�e������ [item.h]
// Author : ��������
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "objectModel.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CObjectPlayerBalloonCar;
class CObject2D;

//*****************************************************************************
// �A�C�e���N���X
//*****************************************************************************
class CItem : public CObjectModel
{
public:
	//�A�C�e���̎��
	enum class ITEM_TYPE
	{
		NONE = 0,
		BANANA,
		MAX
	};

	CItem();	//�f�t�H���g�R���X�g���N�^
	CItem(CModel::MODELTYPE typeModel);		//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	virtual ~CItem();	//�f�X�g���N�^
	static CItem* Create(D3DXVECTOR3 pos, const CObjectPlayerBalloonCar *pPlayer);	//��������
	virtual HRESULT Init(void);				//����������
	virtual void Uninit(void);				//�I������
	virtual void Update(void);				//�X�V����
	virtual void Draw(void);				//�`�揈��

	//�v���C���[�Ƀq�b�g�����Ƃ��̏���
	virtual void HitPlayer(CObjectPlayerBalloonCar *pPlayer);

private:
	int m_nPlayerIndex;		//���̃A�C�e���������Ă���v���C���[�̃C���f�b�N�X

protected:
	//�������v���C���[�̃|�C���^���A��
	bool CollisionPlayer(const float fMySize);	//�v���C���[�Ƃ̓����蔻��
	CObjectPlayerBalloonCar *m_pPlayer;							//���˂����v���C���[�̃|�C���^
};

#endif // !_ITEM_H_