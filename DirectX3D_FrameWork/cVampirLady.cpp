#include "stdafx.h"
#include "cVampirLady.h"

#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cSkinnedAnimation.h"


cVampirLady::cVampirLady()
{
}


cVampirLady::~cVampirLady()
{
}

void cVampirLady::Init()
{
	MESH_LOAD();
	beginSetting();

	// # �ٿ�� �ڽ� ��ġ �ʱ� ��ġ ���� ���� #
	D3DXVECTOR3 charPosition;
	charPosition = this->pChar->pTransform->GetWorldPosition();
	//	charPosition.y += 0.1f;

	this->pChar->BoundBox.SetBound(
		&charPosition,
		new D3DXVECTOR3(0.05f, 0.3f, 0.05f));

	this->pChar->pSkinned->Play(0, 0.3f);
}

void cVampirLady::Release()
{
	// # ������Ʈ ���� #
	if (this->pChar)
		SAFE_DELETE(this->pChar);
	if (this->pMovePosition)
		SAFE_DELETE(this->pMovePosition);
	if (this->pAggroVolume)
		SAFE_DELETE(this->pAggroVolume);
}

void cVampirLady::Update(float timeDelta)
{
	this->pChar->Update(timeDelta);
}

void cVampirLady::Render()
{
	this->pChar->Render();
}

void cVampirLady::beginSetting()
{
	// # ���Կ� �ӵ��� ���Ѵ� #
	fWeight = 3.0f;
	fMoveSpeed = 0.0f;

	MoveRangeCenter = { 0.0f, 0.0f, 0.0f };
	MoveRangeLength = 0.0f;

	pMovePosition = new cBaseObject;
	pMovePosition->SetActive(false);

	// # ��׷� ���� #
	pAggroVolume = new cBaseObject;
	pAggroVolume->SetActive(true);
	pAggroVolume->BoundBox.SetBound(&pChar->pTransform->GetWorldPosition(), &D3DXVECTOR3(2.0f, 2.0f, 2.0f));
}

void cVampirLady::MESH_LOAD()
{
	// # ũ�� #
	D3DXMATRIXA16 matScale;
	//	D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.2f);
	D3DXMatrixScaling(&matScale, 0.02f, 0.02f, 0.02f);

	// # ȸ�� #
	D3DXMATRIXA16 matRotate;
	D3DXMatrixIdentity(&matRotate);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(270.0f));

	// # �̵� #
	D3DXMATRIXA16 matTranslation;
	D3DXMatrixIdentity(&matTranslation);
	D3DXMatrixTranslation(&matTranslation, 0.0f, 0.0f, 0.0f);

	D3DXMATRIXA16 matCorrection = matScale * matRotate * matTranslation;

	cXMesh_Skinned* pSkinned =
		RESOURCE_SKINNEDXMESH->GetResource
		("../Resources/Enemy/VampirLady/VampirLady.X", &matCorrection);

	pChar = new cBaseObject();
	pChar->SetMesh(pSkinned);
	pChar->SetActive(true);
	pChar->pTransform->SetWorldPosition(0.0f, 0.0f, 0.0f);
}

void cVampirLady::AddTarget(cBaseObject * targetObj)
{
}
