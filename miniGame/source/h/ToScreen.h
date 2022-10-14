#pragma once
#include "main.h"
#include "renderer.h"

D3DXVECTOR3 WorldToScreen(D3DXVECTOR3 pos, D3DXVECTOR3 rot) {
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return D3DXVECTOR3();	//null�̏ꍇ�I��
	//�����_���[�̎擾
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return D3DXVECTOR3();	//null�̏ꍇ�I��
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return D3DXVECTOR3();		//null�̏ꍇ�I��


	D3DXMATRIX mtxWorld, mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//�r���[�}�g���b�N�X���|����
	D3DXMATRIX mtxView; 
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxView);

	//�v���W�F�N�V�����}�g���b�N�X���|����
	D3DXMATRIX mtxProj;
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProj);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxProj);


	return D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
}