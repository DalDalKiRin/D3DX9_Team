#include "stdafx.h"
#include "cAlice.h"

#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cSkinnedAnimation.h"


cAlice::cAlice()
{
}


cAlice::~cAlice()
{
}

void cAlice::Init()
{
	MESH_LOAD();
	beginSetting();

	// # 바운드 박스 위치 초기 위치 비율 잡음 #
	D3DXVECTOR3 charPosition;
	charPosition = this->pChar->pTransform->GetWorldPosition();
	//	charPosition.y += 0.1f;

	this->pChar->BoundBox.SetBound(
		&charPosition,
		new D3DXVECTOR3(0.05f, 0.3f, 0.05f));

	this->pChar->pSkinned->Play(0, 0.3f);
}

void cAlice::Release()
{
	// # 오브젝트 해제 #
	if (this->pChar)
		SAFE_DELETE(this->pChar);
	if (this->pMovePosition)
		SAFE_DELETE(this->pMovePosition);
	if (this->pAggroVolume)
		SAFE_DELETE(this->pAggroVolume);
}

void cAlice::Update(float timeDelta)
{
	this->pChar->Update(timeDelta);
}

void cAlice::Render()
{
	this->pChar->Render();

//#ifdef _DEBUG
//	this->pChar->pSkinned->RenderAnimationName();
//#endif
}

void cAlice::beginSetting()
{
	// # 무게와 속도를 정한다 #
	fWeight = 3.0f;
	fMoveSpeed = 0.0f;

	MoveRangeCenter = { 0.0f, 0.0f, 0.0f };
	MoveRangeLength = 0.0f;

	pMovePosition = new cBaseObject;
	pMovePosition->SetActive(false);

	// # 어그로 범위 #
	pAggroVolume = new cBaseObject;
	pAggroVolume->SetActive(true);
	pAggroVolume->BoundBox.SetBound(&pChar->pTransform->GetWorldPosition(), &D3DXVECTOR3(2.0f, 2.0f, 2.0f));
}

void cAlice::MESH_LOAD()
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
		("../Resources/Enemy/Alice/Alice.X", &matCorrection);
//		("../Resources/pp/Elin_Hair.X", &matCorrection);

	pChar = new cBaseObject();
	pChar->SetMesh(pSkinned);
	pChar->SetActive(true);
	pChar->pTransform->SetWorldPosition(0.0f, 0.0f, 0.0f);
}

void cAlice::AddTarget(cBaseObject * targetObj)
{
}
