//=============================================================================
//
// �Q�[���V�[��02���� [gameScene02.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _GAME_SCENE02_H_
#define _GAME_SCENE02_H_

#include "gameScene.h"
#include "main.h"
#include "object_player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAME_02_STAGE_SIZE				(700.0f)				//���ā[���̑傫��

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObjectPlayerIcon;
class CObjectPlayerAttackCar;
class CCreateBomManager;
class CMeshwall;

//*****************************************************************************
// �Q�[���V�[���N���X
//*****************************************************************************
class CGameScene02 : public CGameScene
{
public:
	CGameScene02();	//�f�t�H���g�R���X�g���N�^
	virtual ~CGameScene02();	//�f�X�g���N�^
	void Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void GameOver(void);	//�Q�[���I�[�o�[

	//�����Ă���v���C���[�̐��ݒ菈��
	void SetSavePlayerNum(const int nSavePlayerNum) { m_nSavePlayerNum = nSavePlayerNum; }
	//�����Ă���v���C���[�̐����Z����
	void AddSavePlayerNum(const int nAddNum) { m_nSavePlayerNum += nAddNum; }
	//�����Ă���v���C���[�̐��ݎ擾����
	int GetSavePlayerNum() { return m_nSavePlayerNum; }

private:
	//�V��̏��
	enum class WEATHER_STATE
	{
		CLOUDY = 0,		//�܂�
		SUNNY,			//����
		MAX
	};

	void UpdateGame(void);					//�Q�[�����̍X�V
	void UpdateGameOver(void);				//�Q�[���I�[�o�[���̍X�V
	void UpdateReady(void);					//������Ԓ��̍X�V

	void CreatePlayerIcon(int nCntPlayer);	//�v���C���[�A�C�R����������
	void CountDownUi(void);					//�J�E���g�_�E��UI�̏���
	bool Finish(void);						//�t�B�j�b�V�����邩�m�F����
	void HurryUp(void);						//�}������
	void Cloud(void);						//�_�̏���
	void CreateItem();						//�A�C�e����������
	void SetRanking();						//�����L���O�ݒ菈��

	CObjectPlayerAttackCar* m_apPlayer[MAX_OBJECT_PLAYER_NUM];			//�v���C���[�̃|�C���^
	CObjectPlayerIcon *m_apPlayerIcon[MAX_OBJECT_PLAYER_NUM];			//�v���C���[�A�C�R���̃|�C���^
	CCreateBomManager *m_pCreateBomManager;								//�{�������̃|�C���^
	std::vector<CMeshwall*> m_pCloud;									//�_�̃|�C���^

	int m_nCntGameClear;					//�Q�[���N���A��̃J�E���g
	int m_nItemCounter;						//�A�C�e���̐����J�E���^�[
	int m_nSavePlayerNum;					//�����Ă���v���C���[�̐�
	bool m_bHurryUp;						//�}�����ǂ���
	WEATHER_STATE m_weatherState;			//�V��̏��
};

#endif // !_GAME_SCENE01_H_