#include "stdafx.h"
#include "cPixie.h"

#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cSkinnedAnimation.h"


cPixie::cPixie()
{
}


cPixie::~cPixie()
{
}


void cPixie::Init()
{
	MESH_LOAD();
	beginSetting();
	D3DXVECTOR3 charPosition;
	charPosition = this->pChar->pTransform->GetWorldPosition();
	charPosition.y += 0.1f;

	this->pChar->BoundBox.SetBound(
		&charPosition,
		new D3DXVECTOR3(0.05f, 0.3f, 0.05f));

	this->pChar->pSkinned->Play("Idle", 0.3f);
//	FindMovePosition();
}

void cPixie::Release()
{
	// # 오브젝트 해제 #
	if (this->pChar)
		SAFE_DELETE(this->pChar);
	if (this->pMovePosition)
		SAFE_DELETE(this->pMovePosition);
	if (this->pAggroVolume)
		SAFE_DELETE(this->pAggroVolume);
}

void cPixie::Update(float timeDelta)
{
	this->pChar->Update(timeDelta);

//	if (KEY_MGR->IsOnceDown('G'))
//	{
//		FindMovePosition();
//	}
//	else if (KEY_MGR->IsStayDown('H'))
//	{
//		MovePosition(timeDelta);
//	}
//	MovePosition(timeDelta);
	
	pAggroVolume->BoundBox.SetBound(&pChar->pTransform->GetWorldPosition(), &D3DXVECTOR3(2.0f, 2.0f, 2.0f));
}

void cPixie::Render()
{
	this->pChar->Render();

#ifdef _DEBUG
	this->pChar->BoundBox.RenderGizmo(pChar->pTransform);
	GIZMO_MGR->Circle(MoveRangeCenter, MoveRangeLength, D3DXVECTOR3(0, 1, 0), 0xff00ff00);
	pMovePosition->BoundBox.RenderGizmo(pMovePosition->pTransform);
	pAggroVolume->BoundBox.RenderGizmo(pAggroVolume->pTransform);
#endif
}

void cPixie::beginSetting()
{
	// # 무게와 속도를 정한다 #
	fWeight = 1.0f;
	fMoveSpeed = 5.0f;

	MoveRangeCenter = { 0.0f, 0.0f, 0.0f };
	MoveRangeLength = 10.0f;

	pMovePosition = new cBaseObject;
	pMovePosition->SetActive(true);
	
	// # 어그로 범위 #
	pAggroVolume = new cBaseObject;
	pAggroVolume->SetActive(true);
	pAggroVolume->BoundBox.SetBound(&pChar->pTransform->GetWorldPosition(), &D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	FindMovePosition();	
}

void cPixie::MESH_LOAD()
{
	// # 크기 #
	D3DXMATRIXA16 matScale;
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
		("../Resources/Enemy/Pixie/Pixie.X", &matCorrection);

	pChar = new cBaseObject();
	pChar->SetMesh(pSkinned);
	pChar->SetActive(true);
	pChar->pTransform->SetWorldPosition(0.0f, 0.0f, 0.0f);
}

void cPixie::AddTarget(cBaseObject * targetObj)
{
}

void cPixie::FindMovePosition()
{
	// 찾을 위치 초기화
	D3DXVECTOR3 findPosition;

	while (1)
	{
		findPosition = { 0.0f, 0.0f, 0.0f };

		findPosition.x = RandomFloatRange(
			MoveRangeCenter.x - MoveRangeLength,
			MoveRangeCenter.x + MoveRangeLength);

		findPosition.z = RandomFloatRange(
			MoveRangeCenter.z - MoveRangeLength,
			MoveRangeCenter.z + MoveRangeLength);

		findPosition.y = RandomFloatRange(
			pChar->pTransform->GetWorldPosition().y - 1.0f,
			pChar->pTransform->GetWorldPosition().y + 1.0f
		);
		float length;
		D3DXVECTOR3 a = findPosition - MoveRangeCenter;
		length = D3DXVec3Length(&a);
		if (length < MoveRangeLength)
			break;
	}
	
	D3DXVECTOR3 Direction = findPosition - pChar->pTransform->GetWorldPosition();
	D3DXVec3Normalize(&Direction, &Direction);
	pChar->pTransform->LookDirection(Direction);

	bNormalMoving = true;
	
	pMovePosition->BoundBox.SetBound(&findPosition, &D3DXVECTOR3(0.1f, 0.1f, 0.1f));
}

void cPixie::MovePosition(float timeDelta)
{
	float moveSpeed;
	moveSpeed = fMoveSpeed * timeDelta;

	if (bNormalMoving)
	{
		pChar->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, moveSpeed));
		if (pChar->pSkinned->GetNowPlayAnimationName() != "Run")
			pChar->pSkinned->Play("Run", 0.3f);

		if (CollisionSphere(pMovePosition))
		{
			FindMovePosition();
		}
	}
}
