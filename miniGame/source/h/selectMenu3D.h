//=============================================================================
//
// 3D�I�����j���[���� [selectMenu3D.h]
// Author : �ߊԏr��
//
//=============================================================================
#ifndef _SELECT_MENU_3D_H_
#define _SELECT_MENU_3D_H_

#include "selectMenu.h"
#include "objectModelUI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// 3D�I�����j���[�N���X
//*****************************************************************************
class CSelectMenu3D : public CSelectMenu
{
public:

	CSelectMenu3D();		//�f�t�H���g�R���X�g���N�^
	CSelectMenu3D(int nNumSelect, D3DXVECTOR3 posCenter, float fRadiusModel, bool bUseBG);	//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	virtual ~CSelectMenu3D();		//�f�X�g���N�^
	static CSelectMenu3D* Create(int nNumSelect, D3DXVECTOR3 posCenter, float fRadius, CModel::MODELTYPE typeModel, float fDistCamera, float fHeightCamera, bool bUseBG, bool bUseShadow);	//��������
	virtual HRESULT Init(void);	//����������
	virtual void Uninit(void);	//�I������
	virtual void Update(void);	//�X�V����
	virtual void Draw(void) {}	//�`�揈��

	virtual void BeginChangeSelect(bool bChangePlus);	//�I���̕ύX���J�n���ꂽ�Ƃ��̏���
	virtual void EndChangeSelect(void) {}	//�I���̕ύX���I�������Ƃ��̏���

	CObjectModelUI* GetModelUI(unsigned int nIdx);	//UI���f���I�u�W�F�N�g�̃|�C���^���擾
	virtual void SetIdxCurSelect(int nIdx);			//���݂̑I���̔ԍ���ݒ肵�A���̊p�x�Ƀ��f�������킹��
	void SetSpeedRotModel(float fSpeed) { m_fSpeedRotModel = fSpeed; }	//���f���ړ����̉�]���x�̐ݒ�
	float GetSpeedRotModel(void) { return m_fSpeedRotModel; }			//���f���ړ����̉�]���x�̎擾
	void SetCountRotate(int nCnt) { m_nCntRotate = nCnt; }		//��]����J�E���g�̐ݒ�
	int GetCountRotate(void) { return m_nCntRotate; }			//��]����J�E���g�̐ݒ�
	void SetSpanRotate(int nSpan) { m_nSpanRotate = nSpan; }	//��]�X�p���̐ݒ�

	void SetRotDest(int nIdxCurSelect) { m_fRotModelDest = D3DX_PI * 2 * ((float)nIdxCurSelect / GetNumSelect()); }	//�ڕW�̊p�x��I���̃C���f�b�N�X����ݒ�

	void SetRoulette(bool bRoulette) { m_bRoulette = bRoulette; }	//���[���b�g��Ԃ̐ݒ�
	bool GetRoulette(void) { return m_bRoulette; }	//���[���b�g��Ԃ̎擾
	void BeginRoulette(int nCntRoulette, float fSpeedRot, float fSpeedRate) { m_bRoulette = true; m_nCntRoulette = nCntRoulette; m_fSpeedRotModel = fSpeedRot; m_fRouletteSpeedRate = fSpeedRate; }	//���[���b�g�̊J�n
	int GetCountRoulette(void) { return m_nCntRoulette; }	//���[���b�g�̃J�E���g�̎擾


private:
	void CreateModelUI(void);	//���f���̐���
	void RotateMenu(void);		//���j���[����]
	void RouletteMenu(void);	//���[���b�g�Ń��j���[����]
	void MoveModel(void);		//���f���ړ�
	void MoveShadow(void);		//�e�ړ�

	const D3DXVECTOR3 m_posCenter;	//���j���[�̒����̈ʒu
	const float m_fRadiusModel;		//�I�u�W�F�N�g��z�u���锼�a

	std::vector<CObjectModelUI*> m_vpObjModelUI;	//UI���f���I�u�W�F�N�g�̃|�C���^�̃x�N�^�[�z��
	CModel::MODELTYPE m_typeModel;					//�������郂�f���̎�ށi�S�Ẵ��f���͂��ꂪ�����̃^�C�v�j
	bool m_bUsePlaneShadow;							//�e�̎g�p
	std::vector<CObjectModelUI*> m_vpPlaneShadow;	//UI���f���̉e�̃|�C���^�̃x�N�^�[�z��

	int m_nSpanRotate;		//��]�̃X�p��
	int m_nCntRotate;		//��]����J�E���g
	float m_fRotModel;		//���f���̔z�u�ʒu�����߂�p�x
	float m_fRotModelDest;	//���f���̖ڕW�p�x
	float m_fSpeedRotModel;	//���f���ړ����̉�]���x

	bool m_bRoulette;			//���[���b�g�̉�]
	int m_nCntRoulette;			//���[���b�g��]����J�E���g
	float m_fRouletteSpeedRate;	//���[���b�g�̑��x�̏�Z�����l

	float m_fDistCamera;	//���j���[�p�̃J�����̋���
	float m_fRotCamera;		//���j���[�p�̃J������Y�p�x
	float m_fHeightCamera;	//���j���[�p�̃J�����̈ʒu�̍���
};

#endif // !_SELECT_MENU_3D_H_