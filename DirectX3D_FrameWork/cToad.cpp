#include "stdafx.h"
#include "cToad.h"

#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cSkinnedAnimation.h"

cToad::cToad()
{
}

cToad::~cToad()
{
}

void cToad::Init()
{
	MESH_LOAD();
	beginSetting();

	// # 바운드 박스 위치 초기 위치 비율 잡음 #
	D3DXVECTOR3 charPosition;
	charPosition = this->pChar->pTransform->GetWorldPosition();
	charPosition.y += 0.1f;

	this->pChar->BoundBox.SetBound(
		&charPosition,
		new D3DXVECTOR3(0.05f, 0.3f, 0.05f));

	this->pChar->pSkinned->Play("Wait", 0.3f);
}

void cToad::Release()
{
	// # 오브젝트 해제 #
	if (this->pChar)
		SAFE_DELETE(this->pChar);
	if (this->pMovePosition)
		SAFE_DELETE(this->pMovePosition);
	if (this->pAggroVolume)
		SAFE_DELETE(this->pAggroVolume);
}

void cToad::Update(float timeDelta)
{
	this->pChar->Update(timeDelta);
	this->pAggroVolume->pTransform->SetWorldPosition(pChar->pTransform->GetWorldPosition());

	FindTarget(timeDelta);
}

void cToad::Render()
{
	this->pChar->Render();

#ifdef _DEBUG
	this->pAggroVolume->BoundBox.RenderGizmo(pAggroVolume->pTransform);
#endif
}

void cToad::beginSetting()
{
	// # 무게와 속도를 정한다 #
	fWeight = 3.0f;
	fMoveSpeed = 0.0f;		// # 두꺼비는 움직이지 않을 것임 #

	MoveRangeCenter = { 0.0f, 0.0f, 0.0f };
	MoveRangeLength = 0.0f;

	pMovePosition = new cBaseObject;
	pMovePosition->SetActive(false);

	// # 어그로 범위 #
	pAggroVolume = new cBaseObject;
	pAggroVolume->SetActive(true);
	pAggroVolume->BoundBox.SetBound(&pChar->pTransform->GetWorldPosition(), &D3DXVECTOR3(2.0f, 2.0f, 2.0f));
}

void cToad::MESH_LOAD()
{
	// # 크기 #
	D3DXMATRIXA16 matScale;
//	D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.2f);
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
		("../Resources/Enemy/Toad/Toad.X", &matCorrection);

	pChar = new cBaseObject();
	pChar->SetMesh(pSkinned);
	pChar->SetActive(true);
	pChar->pTransform->SetWorldPosition(0.0f, 0.0f, 0.0f);
}

void cToad::AddTarget(cBaseObject* targetObj)
{
	vFoodOfToad.push_back(targetObj);
}

void cToad::FindTarget(float timeDelta)
{
	cBaseObject* nearFood = NULL;
	for (int i = 0; i < vFoodOfToad.size(); i++)
	{
		// # 비활성화된 오브젝트라면 넘김 #
		if (vFoodOfToad[i]->IsActive() == false)
			continue;

		bool CollOn = CollisionSphere(pAggroVolume, vFoodOfToad[i]);
		if (CollOn)
		{
			if (nearFood)
			{
				float a, b;
				a = D3DXVec3Length( &(vFoodOfToad[i]->pTransform->GetWorldPosition()
					- (pChar)->pTransform->GetWorldPosition()) );
				b = D3DXVec3Length(&(nearFood->pTransform->GetWorldPosition()
					- (pChar)->pTransform->GetWorldPosition()));
				if (a < b)
					nearFood = vFoodOfToad[i];
			}
			else if (!nearFood)
			{
				nearFood = vFoodOfToad[i];
			}
		}
	}

	if (nearFood)
	{
		if (pChar->pSkinned->GetNowPlayAnimationName() != "Atk1")
			pChar->pSkinned->Play("Atk1", 0.3f);
		TargetPulling(nearFood, timeDelta);
	}
	else if (!nearFood)
	{
		if (pChar->pSkinned->GetNowPlayAnimationName() != "Wait")
			pChar->pSkinned->Play("Wait", 0.3f);
	}
}

void cToad::TargetPulling(cBaseObject* targetObj, float timeDelta)
{
	D3DXVECTOR3 pullDir;
	pullDir = pChar->pTransform->GetWorldPosition() - targetObj->pTransform->GetWorldPosition();
	D3DXVec3Normalize(&pullDir, &pullDir);

	targetObj->pTransform->MovePositionSelf(pullDir * timeDelta);

	if (CollisionBox(targetObj))
	{
		if (targetObj->pSkinned->GetNowPlayAnimationName() != "Die")
			targetObj->pSkinned->PlayOneShotAfterHold("Die", 0.3f);
	}
}
