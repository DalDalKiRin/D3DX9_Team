#include "stdafx.h"
#include "CollisionTestScene.h"
#include "cLight_Direction.h"
#include "cLight_Point.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"

#include "cPixie.h"


CollisionTestScene::CollisionTestScene()
{
}


CollisionTestScene::~CollisionTestScene()
{
}

HRESULT CollisionTestScene::Scene_Init()
{
	//�⺻����Ʈ ����
	this->pSceneBaseDirectionLight->pTransform->RotateWorld(
		90.0f * ONE_RAD, 0, 0);

	// # ȯ�� �� �̹��� ������ #
	//this->SetEnvironment("../Resources/TextureCUBE/SuperKanjiCube.dds");

	pPixie = new cPixie;
	pPixie->Init();
	pPixie->getCharObject()->pTransform->SetWorldPosition(-3, 0, 0);

	return S_OK;
}

void CollisionTestScene::Scene_Release()
{
	SAFE_RELEASE(pPixie);
}

void CollisionTestScene::Scene_Update(float timeDelta)
{
	MoveTest(timeDelta);
	pPixie->Update(timeDelta);
}

void CollisionTestScene::Scene_Render1()
{
	cXMesh_Skinned::SetCamera(this->pMainCamera);
//	cXMesh_Skinned::sSkinnedMeshEffect->SetTexture("Ramp_Tex", RESOURCE_TEXTURE->GetResource("../Resources/Testures/Ramp_1.png"));
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);

	pPixie->Render();
}

void CollisionTestScene::Scene_RenderSprite()
{
	// # �ʿ� ��� �Ⱦ��� �� #
}

void CollisionTestScene::Scene_Render_AfterPostEffect(LPDIRECT3DTEXTURE9 pScreen)
{
	// # �ʿ� ��� �Ⱦ��� �� #
}

void CollisionTestScene::CollisionSphere()
{
	// # ���� ���� �浹�Ǹ� �����ϴ� ������ ��ġ�� �������� �ǵ���. #
}

void CollisionTestScene::CollisionBox()
{
	// # �ڽ��� �ڽ��� �浹�Ǹ� �����ϴ� ������ ��ġ�� �������� �ǵ���. #
}

void CollisionTestScene::CollisionUnMoveBlocking()
{
}

void CollisionTestScene::CollisionMoveBlocking()
{
}

void CollisionTestScene::CollisionRaySphere()
{
	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);
		D3DXVECTOR3 hitPos;
		D3DXVECTOR3 hitNormal;

		bool bReturn = false;

//		bReturn = PHYSICS_MGR->IsRayHitBound(
//			&ray,
//			&(cBoundSphere)pPigNose2->getCharObject()->BoundBox,
//			pPigNose2->getCharObject()->pTransform,
//			&hitPos, &hitNormal
//		);
//		
//		if (bReturn)
//			pPigNose->getCharObject()->pTransform->SetWorldPosition(0, 0, 0);
	}
}

void CollisionTestScene::CollisionRayBox()
{
	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);
		D3DXVECTOR3 hitPos;
		D3DXVECTOR3 hitNormal;

		bool bReturn = false;

//		bReturn = PHYSICS_MGR->IsRayHitBound(
//			&ray,
//			&pPigNose2->getCharObject()->BoundBox,
//			pPigNose2->getCharObject()->pTransform,
//			&hitPos, &hitNormal
//		);
//
//		if (bReturn)
//			pPigNose->getCharObject()->pTransform->SetWorldPosition(0, 0, 0);
	}
}

void CollisionTestScene::MoveTest(float timeDelta)
{
	// # �̵��ϴ� �ӵ� #
	float moveSpeed = 2.0f * timeDelta;

	// # ���� ������ #
	if (KEY_MGR->IsStayDown(VK_LSHIFT))
		moveSpeed *= 3.0f;

	if (KEY_MGR->IsStayDown(VK_RBUTTON))
		return;

	// # �յ� #
//	if (KEY_MGR->IsStayDown('W'))
//	{
//		pPigNose->getCharObject()->pTransform->MovePositionSelf(0.0f, 0.0f, moveSpeed);
//	}
//	else if (KEY_MGR->IsStayDown('S'))
//	{
//		pPigNose->getCharObject()->pTransform->MovePositionSelf(0.0f, 0.0f, -moveSpeed);
//	}
//
//	// # �¿� #
//	if (KEY_MGR->IsStayDown('A'))
//	{
//		pPigNose->getCharObject()->pTransform->MovePositionSelf(-moveSpeed, 0.0f, 0.0f);
//	}
//	else if (KEY_MGR->IsStayDown('D'))
//	{
//		pPigNose->getCharObject()->pTransform->MovePositionSelf(moveSpeed, 0.0f, 0.0f);
//	}
//
//	if (KEY_MGR->IsOnceDown('T'))
//	{
//		D3DXVECTOR3 lookDir;
//		lookDir = pPigNose2->getCharObject()->pTransform->GetWorldPosition()
//			- pPigNose->getCharObject()->pTransform->GetWorldPosition();
//
//		D3DXVec3Normalize(&lookDir, &lookDir);
//
//		pPigNose->getCharObject()->pTransform->LookDirection(lookDir);
//	}
}
