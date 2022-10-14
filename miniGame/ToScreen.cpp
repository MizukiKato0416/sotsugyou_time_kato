#include "ToScreen.h"
#include "renderer.h"
#include "manager.h"

D3DXVECTOR3 WorldToScreen(D3DXVECTOR3 pos)
{
	//マネージャーの取得
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return D3DXVECTOR3();	//nullの場合終了
													//レンダラーの取得
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return D3DXVECTOR3();	//nullの場合終了
													//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return D3DXVECTOR3();		//nullの場合終了


	//ビューマトリックスを取得
	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//プロジェクションマトリックスを取得
	D3DXMATRIX mtxProj;
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProj);

	// ビューポート行列（スクリーン行列）の作成
	float w = SCREEN_WIDTH / 2.0f;
	float h = SCREEN_HEIGHT / 2.0f;

	D3DXMATRIX viewport = {
		w , 0 , 0 , 0 ,
		0 ,-h , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		w , h , 0 , 1
	};

	D3DXVECTOR3 screenPos;
	D3DXVECTOR3 worldPos = pos;

	// ビュー変換とプロジェクション変換
	D3DXVec3TransformCoord(&worldPos, &worldPos, &mtxView);
	D3DXVec3TransformCoord(&worldPos, &worldPos, &mtxProj);

	// zで割って-1~1の範囲に収める
	worldPos.x /= worldPos.z; worldPos.y /= worldPos.z; worldPos.z /= worldPos.z;

	// スクリーン変換
	D3DXVec3TransformCoord(&screenPos, &worldPos, &viewport);

	return screenPos;
}
