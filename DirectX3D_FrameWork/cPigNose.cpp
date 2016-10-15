#include "stdafx.h"
#include "cPigNose.h"

#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cSkinnedAnimation.h"


cPigNose::cPigNose()
	: find(false)
{
}


cPigNose::~cPigNose()
{
}


void cPigNose::Init()
{
	MESH_LOAD();
	D3DXVECTOR3 charPosition;
	charPosition = this->pChar->pTransform->GetWorldPosition();
	charPosition.y += 0.6f;

	this->pChar->BoundBox.SetBound(
		&charPosition,
		new D3DXVECTOR3(1.0f, 0.8f, 1.0f));
}

void cPigNose::Release()
{
	// # 오브젝트 해제 #
	SAFE_DELETE(this->pChar);
}

void cPigNose::Update(float timeDelta)
{
	this->pChar->Update(timeDelta);
	if (find)
		findPlayer();
}

void cPigNose::Render()
{
	this->pChar->Render();
	this->pChar->BoundBox.RenderGizmo(pChar->pTransform);
}

void cPigNose::beginSetting()
{
}

void cPigNose::MESH_LOAD()
{
	// # 크기 #
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);

	// # 회전 #
	D3DXMATRIXA16 matRotate;
	D3DXMatrixIdentity(&matRotate);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180.0f));

	// # 이동 #
	D3DXMATRIXA16 matTranslation;
	D3DXMatrixIdentity(&matTranslation);

	D3DXMATRIXA16 matCorrection = matScale * matRotate * matTranslation;

	cXMesh_Skinned* pSkinned =
		RESOURCE_SKINNEDXMESH->GetResource
		("../Resources/Meshes/PigNose/pigNose.X", &matCorrection);

	pChar = new cBaseObject();
	pChar->SetMesh(pSkinned);
	pChar->SetActive(true);
	pChar->pTransform->SetWorldPosition(0.0f, 0.0f, 0.0f);
}

void cPigNose::findPlayer()
{
}
