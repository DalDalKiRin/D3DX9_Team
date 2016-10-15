#include "stdafx.h"
#include "cGhost.h"

#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cSkinnedAnimation.h"

cGhost::cGhost()
{
}

cGhost::~cGhost()
{
}

void cGhost::Init()
{
	MESH_LOAD();
	beginSetting();
	D3DXVECTOR3 charPosition;
	charPosition = this->pChar->pTransform->GetWorldPosition();
	charPosition.y += 0.1f;

	this->pChar->BoundBox.SetBound(
		&charPosition,
		new D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	this->pChar->pSkinned->Play("Wait", 0.3f);
}

void cGhost::Release()
{
	// # 오브젝트 해제 #
	if (this->pChar)
		SAFE_DELETE(this->pChar);
	if (this->pMovePosition)
		SAFE_DELETE(this->pMovePosition);
	if (this->pAggroVolume)
		SAFE_DELETE(this->pAggroVolume);
}

void cGhost::Update(float timeDelta)
{
	this->pChar->Update(timeDelta);
	pChar->pTransform->DefaultControl2(timeDelta);

	if (pChar->pSkinned->GetNowPlayAnimationName() == "Die")
	{
		if (pChar->pSkinned->GetPlayAniTime() >= 0.95f)
		{
			pChar->pTransform->SetWorldPosition(
				D3DXVECTOR3(
					pChar->pTransform->GetWorldPosition().x,
					pChar->pTransform->GetWorldPosition().y - timeDelta,
					pChar->pTransform->GetWorldPosition().z
				)
			);
			bIsDie = true;
		}
	}
}

void cGhost::Render()
{
	this->pChar->Render();

#ifdef _DEBUG
	this->pChar->BoundBox.RenderGizmo(pChar->pTransform);
#endif
}

void cGhost::beginSetting()
{
	// # 무게와 속도를 정한다 #
	fWeight = 0.0f;
	fMoveSpeed = 1.0f;

	MoveRangeCenter = { 0.0f, 0.0f, 0.0f };
	MoveRangeLength = 10.0f;

	pMovePosition = new cBaseObject;
	pMovePosition->SetActive(true);

	// # 어그로 범위 #
	pAggroVolume = new cBaseObject;
	pAggroVolume->SetActive(true);
	pAggroVolume->BoundBox.SetBound(&pChar->pTransform->GetWorldPosition(), &D3DXVECTOR3(2.0f, 2.0f, 2.0f));
}

void cGhost::MESH_LOAD()
{
	// # 크기 #
	D3DXMATRIXA16 matScale;
//	D3DXMatrixScaling(&matScale, 0.25f, 0.25f, 0.25f);
	D3DXMatrixScaling(&matScale, 0.02f, 0.02f, 0.02f);

	// # 회전 #
	D3DXMATRIXA16 matRotate;
	D3DXMatrixIdentity(&matRotate);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(270.0f));

	// # 이동 #
	D3DXMATRIXA16 matTranslation;
	D3DXMatrixIdentity(&matTranslation);
	D3DXMatrixTranslation(&matTranslation, 0.0f, 0.0f, 0.0f);

	D3DXMATRIXA16 matCorrection = matScale * matRotate * matTranslation;

	cXMesh_Skinned* pSkinned =
		RESOURCE_SKINNEDXMESH->GetResource
		("../Resources/Enemy/Ghost/Ghost.X", &matCorrection);

	pChar = new cBaseObject();
	pChar->SetMesh(pSkinned);
	pChar->SetActive(true);
	pChar->pTransform->SetWorldPosition(0.0f, 0.0f, 0.0f);
}

void cGhost::AddTarget(cBaseObject * targetObj)
{
}