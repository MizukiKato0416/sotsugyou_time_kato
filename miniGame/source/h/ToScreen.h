#ifndef _TOSCREEN_H_
#define _TOSCREEN_H_

#include "main.h"
#include "renderer.h"

D3DXVECTOR3 WorldToScreen(D3DXVECTOR3 pos);	//ワールド座標からスクリーン座標への変換
D3DXVECTOR3 WorldToScreen(D3DXVECTOR3 pos, D3DXMATRIX mtxView);	//ビューマトリックスを指定したワールド座標からスクリーン座標への変換

#endif // !_TOSCREEN_H_
