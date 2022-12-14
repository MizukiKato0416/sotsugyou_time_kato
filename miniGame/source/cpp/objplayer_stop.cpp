//=============================================================================
//
// �~�܂�ԏ��� [objplayer_stop.cpp]
// Author : ��������
//
//=============================================================================
#include "objplayer_stop.h"

#include "billboard.h"
#include "camera.h"
#include "effect.h"
#include "gameScene.h"
#include "gameScene03.h"
#include "input.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"
#include "renderer.h"
#include "score_ui.h"
#include "score.h"
#include "sound.h"

//�G�t�F�N�g
#include "PresetSetEffect.h"
#include "PresetDelaySet.h"


//=============================================================================
// �}�N����`
//=============================================================================

//--------------------------------
//�ړ�
//--------------------------------
#define ADD_MOVE_SPEED								(0.3f)			//����
#define MAX_MOVE_SPEED								(30.0f)			//�ő呬�x

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObjplayerStop::CObjplayerStop()
{
	SetObjType(OBJTYPE_PLAYER);						//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetUpdatePriority(UPDATE_PRIORITY::PLAYER);		//�X�V���̐ݒ�
	SetDrawPriority(DRAW_PRIORITY::CHARA);			//�`�揇�̐ݒ�

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_itemType = CItem::ITEM_TYPE::NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjplayerStop::~CObjplayerStop()
{

}

//=============================================================================
// �v���C���[�̐�������
//=============================================================================
CObjplayerStop* CObjplayerStop::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot) {

	CObjplayerStop* pObjectPlayer;
	pObjectPlayer = new CObjplayerStop();
	if (pObjectPlayer == nullptr) return nullptr;

	pObjectPlayer->Init();
	pObjectPlayer->SetPos(pos);
	pObjectPlayer->SetRot(rot);

	return pObjectPlayer;
}

//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CObjplayerStop::Init(void) {

	CObjectPlayer::Init();

	//�v���C���[�̏����ݒ�
	m_itemType = CItem::ITEM_TYPE::NONE;

	m_move = D3DXVECTOR3(0.f, 0.f, 0.f);

	return S_OK;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CObjplayerStop::Uninit(void) {

	CObjectPlayer::Uninit();
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void CObjplayerStop::Update(void) {
	//�X�V���Ȃ��ݒ�Ȃ�
	if (!GetPlayer()->GetUpdate())
	{
		return;
	}

	//�ړ�
	if (!m_bStopMove) Move();

	CObjectPlayer::Update();
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CObjplayerStop::Draw(void) {

	CObjectPlayer::Draw();
}

//=============================================================================
// �v���C���[�̃Q�[���I�[�o�[���̏���
//=============================================================================
void CObjplayerStop::GameOver(void) {

	CObjectPlayer::GameOver();
}

//=============================================================================
// �ړ�
//=============================================================================
void CObjplayerStop::Move(void) {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();

	CInput* pInput = nullptr;
	CSound *pSound = nullptr;

	if (pManager != nullptr) {
		//���݂̓��̓f�o�C�X�̎擾
		pInput = pManager->GetInputCur();
		//�T�E���h�̎擾
		pSound = pManager->GetSound();
	}

	//�ʒu���̃|�C���^�̎擾
	D3DXVECTOR3 posObjectPlayer = GetPos();
	//�ړ�
	posObjectPlayer += m_move;
	//�ʒu�ݒ�
	SetPos(posObjectPlayer);

	bool bWolf = CGameScene::GetWereWolfPlayerIndex() == GetPlayer()->GetIndex();		//�l�T�̃v���C���[
	bool bVibArea = int(posObjectPlayer.x + 20) % int(GAME03_ONE_METER * 100) < 50;		//�o�C�u�L���G���A 100m���Ƃ̈ʒu��-20����+30�̃G���A

	//�l�T���̏���
	if (CGameScene::GetWereWolfMode() && bWolf && bVibArea) {
		CInputGamepadX* pPadX = dynamic_cast<CInputGamepadX*>(pInput);	//X�p�b�h�̎擾

		if (pPadX != nullptr)
		{
			//�U��������
			pPadX->SetVibration(2000, 2000, 20, GetPlayer()->GetIndex() - 1);
		}
	}

	//����
	if (m_move.x < MAX_MOVE_SPEED) {
		m_move.x += ADD_MOVE_SPEED;
		if (m_move.x > MAX_MOVE_SPEED) m_move.x = MAX_MOVE_SPEED;
	}
	//A�{�^������������
	else if (pInput->GetTrigger(CInput::CODE::SELECT, GetPlayer()->GetIndex() - 1) && m_bCanStop) {
		//��~����
		StopMove();
	}
	//�y��
	CPresetEffect::SetEffect3D(1, GetPos(), {}, {});
}

//=============================================================================
// �ړ��ʂ̌���
//=============================================================================
void CObjplayerStop::StopMove(void) {
	//����
	m_move = D3DXVECTOR3(0.f, 0.f, 0.f);

	m_bStopMove = true;
}