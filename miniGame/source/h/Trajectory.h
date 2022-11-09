//=============================================================================
// �O�Տ��� [Trajectory.h]
// Author : �����G��
//=============================================================================
#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_


#include "main.h"
#include "plane.h"

class CTrajectory : public CPlane
{
public:
	CTrajectory();
	~CTrajectory();

	HRESULT Init(D3DXVECTOR3 Vtxpos1,
		D3DXVECTOR3 Vtxpos2,
		D3DXVECTOR3 VtxOldpos1,
		D3DXVECTOR3 VtxOldpos2,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		D3DCOLORVALUE Trajectcolor,
		D3DCOLORVALUE TrajectMincolor,
		D3DXVECTOR3 Size,
		D3DXVECTOR3 MinSize,
		int nTex,
		int nLife,
		int Synthetic);

	void Uninit();
	void Update();
	void Draw();

	static CTrajectory *Create(D3DXVECTOR3 Vtxpos1, 
		D3DXVECTOR3 Vtxpos2, 
		D3DXVECTOR3 VtxOldpos1, 
		D3DXVECTOR3 VtxOldpos2, 
		D3DCOLORVALUE color, 
		D3DCOLORVALUE Mincolor, 
		D3DCOLORVALUE Trajectcolor,
		D3DCOLORVALUE TrajectMincolor, 
		D3DXVECTOR3 Size, 
		D3DXVECTOR3 MinSize,
		int nTex,
		int nLife,
		int Synthetic);
private:
	//���_�̍��W
	D3DXVECTOR3 m_pos1;
	D3DXVECTOR3 m_pos2;
	D3DXVECTOR3 m_pos3;
	D3DXVECTOR3 m_pos4;

	D3DCOLORVALUE m_TrajectAddColor;	//�O�ՃJ���[����

	int m_nLife;	//����
	int m_nSynsetic;	//����

	bool m_bUninit;	//�폜
	bool m_bConversion;	//�ϊ��̏I��

};

#endif