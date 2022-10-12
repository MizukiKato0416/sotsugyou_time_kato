//---------------------------
//Author:佐藤秀亮
//シーン(scene3d.cpp)
//---------------------------
#include "scene3d.h"
#include "manager.h"
#include "renderer.h"

CScene3D::CScene3D() : CObject::CObject()
{

}

CScene3D::~CScene3D()
{

}


//初期化処理
HRESULT CScene3D::Init()
{
	return S_OK;
}

//終了処理
void CScene3D::Uninit()
{
	Release();
}

//更新処理
void CScene3D::Update()
{
	
}

//描画処理
void CScene3D::Draw()
{
	
}