//=============================================================================
//
// �I�u�W�F�N�g�v���C���[���� [object_player.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _OBJECT_PLAYER_H_
#define _OBJECT_PLAYER_H_

#include "objectModel.h"
#include "item.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_OBJECT_PLAYER_NUM	(4)		//�v���C���[�̍ő吔

//--------------------------------
//�v���C���[�J���[
//--------------------------------
#define OBJECT_PLAYER_COLOR_1P		(D3DXCOLOR(0.1f, 0.3f, 1.0f, 1.0f))	//1p�̃J���[
#define OBJECT_PLAYER_COLOR_2P		(D3DXCOLOR(1.0f, 0.2f, 0.0f, 1.0f))	//2p�̃J���[
#define OBJECT_PLAYER_COLOR_3P		(D3DXCOLOR(0.1f, 0.7f, 0.0f, 1.0f))	//3p�̃J���[
#define OBJECT_PLAYER_COLOR_4P		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//4p�̃J���[

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CPlayer;

//*****************************************************************************
// �N���X
//*****************************************************************************
class CObjectPlayer : public CObjectModel
{
public:
	CObjectPlayer();	//�f�t�H���g�R���X�g���N�^
	virtual ~CObjectPlayer();	//�f�X�g���N�^

	static CObjectPlayer* Create(D3DXVECTOR3 pos);	//��������

	virtual HRESULT Init(void);		//����������
	virtual void Uninit(void);		//�I������
	virtual void Update(void);		//�X�V����
	virtual void Draw(void);		//�`�揈��
	virtual void GameOver(void);	//�Q�[���I�[�o�[���̏���
	float GetRadius(void);			//�����蔻��̔��a�̎擾

	//�v���C���[�擾����
	CPlayer *GetPlayer(void) { return m_pPlayer; }

	//�A�C�e���^�C�v�擾����
	CItem::ITEM_TYPE GetItemType(void) { return m_itemType; }
	//�A�C�e���^�C�v�ݒ菈��
	void SetItemType(CItem::ITEM_TYPE itemType) { m_itemType = itemType; }

protected:
	CItem::ITEM_TYPE m_itemType;	//�A�C�e���̎��

private:

	CPlayer *m_pPlayer;				//�v���C���[�̃|�C���^
};

#endif // !_OBJECT_PLAYER_H_