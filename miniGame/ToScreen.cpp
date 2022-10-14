#include "ToScreen.h"
#include "renderer.h"
#include "manager.h"

D3DXVECTOR3 WorldToScreen(D3DXVECTOR3 pos)
{
	//�}�l�[�W���[�̎擾
	CManager* pManager = CManager::GetManager();
	if (pManager == nullptr) return D3DXVECTOR3();	//null�̏ꍇ�I��
													//�����_���[�̎擾
	CRenderer* pRenderer = pManager->GetRenderer();
	if (pRenderer == nullptr) return D3DXVECTOR3();	//null�̏ꍇ�I��
													//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pDevice == nullptr) return D3DXVECTOR3();		//null�̏ꍇ�I��


	//�r���[�}�g���b�N�X���擾
	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�v���W�F�N�V�����}�g���b�N�X���擾
	D3DXMATRIX mtxProj;
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProj);

	// �r���[�|�[�g�s��i�X�N���[���s��j�̍쐬
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

	// �r���[�ϊ��ƃv���W�F�N�V�����ϊ�
	D3DXVec3TransformCoord(&worldPos, &worldPos, &mtxView);
	D3DXVec3TransformCoord(&worldPos, &worldPos, &mtxProj);

	// z�Ŋ�����-1~1�͈̔͂Ɏ��߂�
	worldPos.x /= worldPos.z; worldPos.y /= worldPos.z; worldPos.z /= worldPos.z;

	// �X�N���[���ϊ�
	D3DXVec3TransformCoord(&screenPos, &worldPos, &viewport);

	return screenPos;
}
