//===========================================
//�v���C���[�̃��[�V��������
//Author:��������
//===========================================
#ifndef _MOTION_PLAYER_H_
#define _MOTION_PLAYER_H_
#include "main.h"
#include "player.h"
#include "motion_road.h"
#include "manager.h"

//================================================
//�}�N����`
//================================================

//================================================
//�\���̂̒�`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CMotionPlayer
{
public:

	CMotionPlayer();			//�R���X�g���N�^
	~CMotionPlayer();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(CPlayer *&pPlayer);
	void Uninit(void);
	void Update(CPlayer *pPlayer);

	static CMotionPlayer *Create(CPlayer *pPlayer);									//��������
	void SetMotion(const CMotionRoad::MOTION_PLAYER_TYPE &type, CPlayer *&pPlayer);			//���[�V�����ݒ菈��
	void SetMotion(const int &nType, CPlayer *pPlayer);									//���[�V�����ݒ菈��
	CMotionRoad::MOTION_PLAYER_TYPE GetMotion(void);								//���[�V�����擾����
	bool GetConnect(void);															//���[�V�������Ȃ��Ă���Œ����ǂ����擾����
	int GetKey(void) { return m_nKey; }												//�L�[�擾����
	int GetFrame(void) { return (int)m_fCounter; }									//���[�V�����J�E���^�[�擾����
	void SetFrameMax(const int &nFrame) { m_fConnectMaxFrame = (float)nFrame; }			//���[�V�����J�E���^�[�ő�l�ݒ菈��
	//�L�[�ő吔�擾����
	int GetKeyMax(void) { return CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_PLAYER, m_type).nNumKey; }
	//���[�V�����J�E���^�[�ő吔�擾����
	int GetFrameMax(void) { return CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_PLAYER, m_type).aKeyInfo[m_nKey].nFrame; }
	

private:
	std::vector<MOTION_INFO> m_aInfo;					//���[�V�������
	CMotionRoad::MOTION_PLAYER_TYPE m_type;				//���݂̃��[�V�����^�C�v
	CMotionRoad::MOTION_PLAYER_TYPE m_typeNext;			//���̃��[�V�����^�C�v
	CMotionRoad::MOTION_PLAYER_TYPE m_typeOld;			//�O�̃��[�V�����^�C�v
	int m_nKey;											//�L�[No,(���݂̃L�[)
	float m_fCounter;									//���[�V�����̃J�E���^�[
	bool m_bConnect;									//���[�V�������Ȃ��Ă��邩�ǂ���
	float m_fConnectMaxFrame;							//���[�V�������Ȃ���Ƃ��̃t���[�����ő�l
	std::vector<D3DXVECTOR3> m_posOld;					//���[�V�������Ȃ���Ƃ��̑O�̃��f���̈ʒu
	std::vector<D3DXVECTOR3> m_rotOld;					//���[�V�������Ȃ���Ƃ��̑O�̃��f���̌���
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_MOTION_PLAYER_H_