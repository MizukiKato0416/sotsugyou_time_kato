#ifndef _TOSCREEN_H_
#define _TOSCREEN_H_

#include "main.h"
#include "renderer.h"

D3DXVECTOR3 WorldToScreen(D3DXVECTOR3 pos);	//���[���h���W����X�N���[�����W�ւ̕ϊ�
D3DXVECTOR3 WorldToScreen(D3DXVECTOR3 pos, D3DXMATRIX mtxView);	//�r���[�}�g���b�N�X���w�肵�����[���h���W����X�N���[�����W�ւ̕ϊ�

#endif // !_TOSCREEN_H_
