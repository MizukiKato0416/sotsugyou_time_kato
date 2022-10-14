#pragma once
#include "main.h"
#include "renderer.h"

D3DXVECTOR3 WorldToScreen(D3DXVECTOR3 pos, D3DXVECTOR3 rot) {
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return D3DXVECTOR3();	//nullの場合終了
	//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return D3DXVECTOR3();	//nullの場合終了
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return D3DXVECTOR3();		//nullの場合終了


	D3DXMATRIX mtxWorld, mtxRot, mtxTrans;	//計算用マトリックス
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//ビューマトリックスを掛ける
	D3DXMATRIX mtxView; 
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxView);

	//プロジェクションマトリックスを掛ける
	D3DXMATRIX mtxProj;
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProj);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxProj);


	return D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
}