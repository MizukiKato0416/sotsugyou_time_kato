//=============================================================================
//
// ���D���� [balloon.cpp]
// Author : ��������
//
//=============================================================================
#include "balloon.h"
#include "manager.h"
#include "sound.h"
#include "objectList.h"
#include "object_player_balloon_car.h"
#include "score.h"
#include "score_ui.h"
#include "gameScene.h"

//�G�t�F�N�g
#include "PresetSetEffect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BALLOON_PLAYER_COLL_SIZE	(30.0f)		//�����蔻��̎��̃v���C���[�̃T�C�Y
#define BALLOON_ADD_MOVE			(0.02f)		//���D�̉�����
#define BALLOON_MAX_MOVE			(0.2f)		//���D�̍ő�ړ���
#define BALLOON_UP_POS				(20.0f)		//���D�̏オ��ʒu
#define BALLOON_DOWN_POS			(10.0f)		//���D�̉�����ʒu
#define BALLOON_NORMAL_SCORE		(1)			//���D�̃|�C���g(�ʏ�)
#define BALLOON_GOLD_SCORE			(3)			//���D�̃|�C���g(�S�[���h)

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CBalloon::m_nNum = 0;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CBalloon::CBalloon()
{
	m_nNum++;

	m_bGold = false;
	m_bUp = false;
	m_move = { 0.0f, 0.0f, 0.0f };
}

//=============================================================================
// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
//=============================================================================
CBalloon::CBalloon(CModel::MODELTYPE typeModel) : CObjectModel(typeModel, false)
{
	m_nNum++;

	m_bGold = false;
	m_bUp = false;
	m_move = { 0.0f, 0.0f, 0.0f };
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBalloon::~CBalloon()
{
	m_nNum--;
}

//=============================================================================
// ��������
//=============================================================================
CBalloon* CBalloon::Create(bool bGold, D3DXVECTOR3 pos) {
	
	//�f�t�H���g�̃��f����ݒ�
	CModel::MODELTYPE typeModel = CModel::MODELTYPE::OBJ_BALLOON_PINK;
	
	//���F�ɐݒ肳��Ă�����
	if (bGold)
	{
		typeModel = CModel::MODELTYPE::OBJ_BALLOON_GOLD;
	}

	CBalloon* pBalloon;
	pBalloon = new CBalloon(typeModel);
	if (pBalloon == nullptr) return nullptr;

	pBalloon->SetPos(pos);
	pBalloon->m_bGold = bGold;
	
	pBalloon->Init();

	return pBalloon;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBalloon::Init(void) {
	
	m_move = { 0.0f, 0.0f, 0.0f };
	m_bUp = true;

	CModel *pModel = GetPtrModel();
	if (pModel != nullptr)
	{
		for (int nIdxMat = 0; nIdxMat < MAX_MATERIAL; nIdxMat++)
		{
			//�w�肵���}�e���A���̐F��ݒ�
			pModel->SetMaterialSpecular(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), nIdxMat);
			pModel->SetMaterialPower(8.0f, nIdxMat);
		}
	}

	CObjectModel::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBalloon::Uninit(void) {

	CObjectModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBalloon::Update(void) {
	
	//�Q�[���I�[�o�[�Ȃ�
	if (CManager::GetManager()->GetGameScene()->GetGameOver())
	{
		//����
		Uninit();
		return;
	}

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//����
	if (m_bUp)
	{
		m_move.y += BALLOON_ADD_MOVE;

		if (pos.y > BALLOON_UP_POS)
		{
			m_bUp = false;
		}
	}
	else
	{
		m_move.y -= BALLOON_ADD_MOVE;

		if (pos.y < BALLOON_DOWN_POS)
		{
			m_bUp = true;
		}
	}

	if (m_move.y > BALLOON_MAX_MOVE)
	{
		m_move.y = BALLOON_MAX_MOVE;
	}
	else if (m_move.y < -BALLOON_MAX_MOVE)
	{
		m_move.y = -BALLOON_MAX_MOVE;
	}

	//�ړ��ʂ�ݒ�
	pos += m_move;

	SetPos(pos);

	//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//�����D�̃L���L��
	if (m_bGold)
	{
		CPresetEffect::SetEffect3D(7, D3DXVECTOR3(pos.x, pos.y + 70, pos.z), {}, {});		//������o
	}
	//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	//�v���C���[�Ƃ̓����蔻��
	if (CollisionPlayer())
	{
		//�}�l�[�W���[�̎擾
		CManager* pManager = CManager::GetManager();
		//�T�E���h�̎擾
		CSound *pSound = nullptr;
		if (pManager != nullptr) pSound = pManager->GetSound();
		//���Đ�
		if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_BALLOON_BREAK);

		//�F�ɂ���ĕς���
		if (m_bGold)
		{
			//���Đ�
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_POINT_3);
		}
		else
		{
			//���Đ�
			if (pSound != nullptr) pSound->PlaySound(CSound::SOUND_LABEL::SE_POINT_1);

		}

		//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
		//���D�擾�G�t�F�N�g
		CPresetEffect::SetEffect3D(2, D3DXVECTOR3(pos.x,pos.y + 30,pos.z), {}, {});		//�Ռ��g
		CPresetEffect::SetEffect3D(3, D3DXVECTOR3(pos.x,pos.y + 30,pos.z), {}, {});		//�o
		CPresetEffect::SetEffect3D(4, D3DXVECTOR3(pos.x,pos.y + 30,pos.z), {}, {});		//������o
		//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
		//�������Ă��������
		Uninit();
		return;
	}

	CObjectModel::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBalloon::Draw(void) {
	CObjectModel::Draw();
}

//=============================================================================
//�v���C���[�Ƃ̓����蔻��
//=============================================================================
bool CBalloon::CollisionPlayer(void)
{
	CObject* pObject = GetObjectTopAll();	//�S�I�u�W�F�N�g�̃��X�g�̐擪���擾

	while (pObject != nullptr) {
		CObject* pObjNext = GetObjectNextAll(pObject);	//���X�g�̎��̃I�u�W�F�N�g�̃|�C���^���擾

		//�I�u�W�F�N�g�^�C�v�̊m�F
		bool bMatchType = false;
		if (pObject->GetObjType() & OBJTYPE_PLAYER) bMatchType = true;

		if (!bMatchType)
		{
			pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
			continue;
		}

		//�v���C���[�ɃL���X�g
		CObjectPlayerBalloonCar *pPlayer = static_cast<CObjectPlayerBalloonCar*> (pObject);

		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 playerPos = pPlayer->GetPos();
		//���D�̈ʒu�擾
		D3DXVECTOR3 balloonPos = GetPos();

		//��_�̋����x�N�g��
		D3DXVECTOR2 differVec = D3DXVECTOR2(playerPos.x - balloonPos.x, playerPos.z - balloonPos.z);
		//��_�̋���
		float fDiffer = D3DXVec2Length(&differVec);

		//�������Ă�����
		if (fDiffer <= BALLOON_PLAYER_COLL_SIZE + BALLOON_SIZE)
		{
			//�F�ɂ���ăX�R�A�𑝂₷
			if (m_bGold)
			{
				pPlayer->GetScoreUi()->GetScore()->AddScore(BALLOON_GOLD_SCORE);
			}
			else
			{
				pPlayer->GetScoreUi()->GetScore()->AddScore(BALLOON_NORMAL_SCORE);
			}
			return true;
		}

		pObject = pObjNext;	//���X�g�̎��̃I�u�W�F�N�g����
	}

	return false;
}
