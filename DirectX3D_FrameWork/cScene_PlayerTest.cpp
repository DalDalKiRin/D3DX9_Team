#include "stdafx.h"
#include "cScene_PlayerTest.h"

#include "cCamera.h"
#include "cTransform.h"
#include "cBaseObject.h"
#include "cXMesh_Static.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"
#include "cLight_Direction.h"

cScene_PlayerTest::cScene_PlayerTest()
{
	m_pTrans = new cTransform();
}


cScene_PlayerTest::~cScene_PlayerTest()
{
}

HRESULT cScene_PlayerTest::Scene_Init()
{
	D3DXMATRIXA16 matScale;
	D3DXMATRIXA16 matRotateY;
	D3DXMatrixRotationY(&matRotateY, -90.f * ONE_RAD);
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matCorrection = matScale * matRotateY;

	cXMesh_Skinned* pSkinned =
		RESOURCE_SKINNEDXMESH->GetResource(
			"../Resources/Meshes/Elin/Elin_Body.X", &matCorrection);










	D3DXMATRIXA16 matScale2;
	D3DXMATRIXA16 matRotateZ2;
	D3DXMatrixIdentity(&matRotateZ2);
	D3DXMatrixRotationZ(&matRotateZ2, 90.f * ONE_RAD);
	
	D3DXMatrixScaling(&matScale2, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matCorrection2 = matScale2 * matRotateZ2;		// 스케일 자축 이동

	D3DXMatrixIdentity(&matCorrection2);

	cXMesh_Skinned* pSkinned2 =
		RESOURCE_SKINNEDXMESH->GetResource(
			"../Resources/Meshes/Elin/Elin_Head.X", &matCorrection2);





	cXMesh_Skinned* pSkinned3 =
		RESOURCE_SKINNEDXMESH->GetResource(
			"../Resources/Meshes/Elin/Elin_Hair.X", &matCorrection2);

	cBaseObject* pChar;
	pChar = new cBaseObject();
	pChar->SetMesh(pSkinned);
	pChar->SetActive(true);
	pChar->pSkinned->Play("idle");

	cBaseObject* pChar2;
	pChar2 = new cBaseObject();
	pChar2->SetMesh(pSkinned2);
	pChar2->SetActive(true);
	pChar2->pSkinned->Play("idle");

	cBaseObject* pChar3;
	pChar3 = new cBaseObject();
	pChar3->SetMesh(pSkinned3);
	pChar3->SetActive(true);
	pChar3->pSkinned->Play("idle");

	D3DXVECTOR3 pos(0.f, 0.f, 0.f);
	pChar->pTransform->SetWorldPosition(pos);

	this->renderObjects.push_back(pChar);
	this->renderObjects.push_back(pChar2);
	this->renderObjects.push_back(pChar3);

	this->pMainCamera->SetWorldPosition(pChar->pTransform->GetWorldPosition());

	//라이팅 추가
	cLight_Point*	pRedLight = new cLight_Point();
	pRedLight->Color = D3DXCOLOR(1, 0, 0, 1);
	pRedLight->minRange = 2.0f;
	pRedLight->maxRange = 10.0f;
	pRedLight->Intensity = 1.0f;
	pRedLight->pTransform->SetWorldPosition(pChar->pTransform->GetWorldPosition());

	cLight_Point*	pBlueLight = new cLight_Point();
	pBlueLight->Color = D3DXCOLOR(0, 0, 1, 1);
	pBlueLight->minRange = 2.0f;
	pBlueLight->maxRange = 10.0f;
	pBlueLight->Intensity = 1.0f;
	pBlueLight->pTransform->SetWorldPosition(pChar->pTransform->GetWorldPosition());

	this->lights.push_back(pRedLight);
	this->lights.push_back(pBlueLight);

	

	return S_OK;
}

void cScene_PlayerTest::Scene_Release()
{
	//오브젝트 해재
	for (int i = 0; i < this->renderObjects.size(); i++)
		SAFE_DELETE(this->renderObjects[i]);
	this->renderObjects.clear();

	for (int i = 0; i < this->lights.size(); i++)
		SAFE_DELETE(this->lights[i]);
	this->lights.clear();

}

void cScene_PlayerTest::Scene_Update(float timeDelta)
{

	for (int i = 0; i < this->renderObjects.size(); i++)
	{
		this->renderObjects[i]->Update(timeDelta);

	}

	control(timeDelta);
}

void cScene_PlayerTest::Scene_Render1()
{

	//라이트 정보 셋팅
	cXMesh_Skinned::SetLighting(&this->lights);

	cXMesh_Skinned::SetCamera(this->pMainCamera);
	cXMesh_Skinned::sSkinnedMeshEffect->SetTexture("Ramp_Tex", RESOURCE_TEXTURE->GetResource("../Resources/Testures/Ramp_1.png"));
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);


	//for (int i = 0; i < 1; i++)
	//	this->renderObjects[i]->Render();

	renderObjects[0]->Render();


	D3DXMATRIXA16 matNeck;


	matNeck = *renderObjects[0]->pSkinned->GetBoneTransform("Bip01-Neck");
	m_pTrans->matFinal = matNeck;
	renderObjects[1]->pSkinned->Render(m_pTrans);






	matNeck = *renderObjects[0]->pSkinned->GetBoneTransform("Bip01-Head");
	m_pTrans->matFinal = matNeck;
	renderObjects[2]->pSkinned->Render(m_pTrans);


	for (int i = 0; i < this->lights.size(); i++)
	{
		this->lights[i]->RenderGizmo();
	}
}

void cScene_PlayerTest::control(float timeDelta)
{
	//pSkinnedAnimation_Elin_Body->Update(timeDelta);
	//pSkinnedAnimation_Elin_Head->Update(timeDelta);


	//pBaseObject_Elin_Body->Update(timeDelta);


	//if( KEY_MGR->IsStayDown( VK_LCONTROL ))


	//if (KEY_MGR->IsOnceDown('1'))
	//	this->pSkinnedAnimation->Play("idle", 0.3f);
	//
	//if (KEY_MGR->IsOnceDown('2'))
	//	this->pSkinnedAnimation->Play("walk", 0.3f);
	//
	//if (KEY_MGR->IsOnceDown('3'))
	//	this->pSkinnedAnimation->Play("run", 0.3f);


	if (!KEY_MGR->IsStayDown('W') &&
		!KEY_MGR->IsStayDown('S') &&
		!KEY_MGR->IsStayDown('A') &&
		!KEY_MGR->IsStayDown('D'))
	{

		if(renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "idle")
		{
			renderObjects[0]->pSkinned->Play("idle", 0.3f);
			renderObjects[1]->pSkinned->Play("idle", 0.3f);
		}
	}




	if (!KEY_MGR->IsStayDown(VK_LSHIFT) && !KEY_MGR->IsStayDown(VK_RBUTTON))
	{

		if (KEY_MGR->IsStayDown('W') && KEY_MGR->IsStayDown('D'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "walk")
			{
				renderObjects[0]->pSkinned->Play("walk", 0.3f);
				renderObjects[1]->pSkinned->Play("walk", 0.3f);
			}

			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = pMainCamera->GetForward() + pMainCamera->GetRight();
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 3.5f) * timeDelta);

			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());
		}
		else if (KEY_MGR->IsStayDown('W') && KEY_MGR->IsStayDown('A'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "walk")
			{
				renderObjects[0]->pSkinned->Play("walk", 0.3f);
				renderObjects[1]->pSkinned->Play("walk", 0.3f);

			}

			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = pMainCamera->GetForward() + (-(pMainCamera->GetRight()));
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 3.5f) * timeDelta);
		
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		}
		else if (KEY_MGR->IsStayDown('S') && KEY_MGR->IsStayDown('D'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "walk")
			{
				renderObjects[0]->pSkinned->Play("walk", 0.3f);
				renderObjects[1]->pSkinned->Play("walk", 0.3f);

			}

			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = -pMainCamera->GetForward() + pMainCamera->GetRight();
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 3.5f) * timeDelta);
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		}
		else if (KEY_MGR->IsStayDown('S') && KEY_MGR->IsStayDown('A'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "walk")
			{
				renderObjects[0]->pSkinned->Play("walk", 0.3f);
				renderObjects[1]->pSkinned->Play("walk", 0.3f);

			}


			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = -pMainCamera->GetForward() - pMainCamera->GetRight();
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 3.5f) * timeDelta);
		
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		}
		else if (KEY_MGR->IsStayDown('W') &&
			!KEY_MGR->IsStayDown('S') &&
			!KEY_MGR->IsStayDown('A') &&
			!KEY_MGR->IsStayDown('D'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "walk")
			{
				this->renderObjects[0]->pSkinned->Play("walk", 0.3f);
				renderObjects[1]->pSkinned->Play("walk", 0.3f);

			}

			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = pMainCamera->GetForward();
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 3.5f) * timeDelta);
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		
		}

		else if (KEY_MGR->IsStayDown('S') &&
			!KEY_MGR->IsStayDown('W') &&
			!KEY_MGR->IsStayDown('A') &&
			!KEY_MGR->IsStayDown('D'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "walk")
			{
				this->renderObjects[0]->pSkinned->Play("walk", 0.3f);
				renderObjects[1]->pSkinned->Play("walk", 0.3f);
			}

			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = -(pMainCamera->GetForward());
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 3.5f) * timeDelta);

			//	pSkinnedTrans->MovePositionWorld(pSkinnedTrans->GetWorldPosition() + D3DXVECTOR3(0, 0, 0.1f));
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		}

		else if (KEY_MGR->IsStayDown('A') &&
			!KEY_MGR->IsStayDown('W') &&
			!KEY_MGR->IsStayDown('S') &&
			!KEY_MGR->IsStayDown('D'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "walk")
			{
				this->renderObjects[0]->pSkinned->Play("walk", 0.3f);
				renderObjects[1]->pSkinned->Play("walk", 0.3f);

			}

			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = -(pMainCamera->GetRight());
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 3.5f) * timeDelta);
		
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		}

		else if (KEY_MGR->IsStayDown('D') &&
			!KEY_MGR->IsStayDown('S') &&
			!KEY_MGR->IsStayDown('A') &&
			!KEY_MGR->IsStayDown('W'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "walk")
			{
				this->renderObjects[0]->pSkinned->Play("walk", 0.3f);
				renderObjects[1]->pSkinned->Play("walk", 0.3f);

			}

			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = pMainCamera->GetRight();
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 3.5f) * timeDelta);
		
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		}
	}
	else if (KEY_MGR->IsStayDown(VK_LSHIFT))
	{
		if (KEY_MGR->IsStayDown('W') && KEY_MGR->IsStayDown('D'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "run")
			{
				this->renderObjects[0]->pSkinned->Play("run", 0.3f);
				renderObjects[1]->pSkinned->Play("run", 0.3f);

			}

			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = pMainCamera->GetForward() + pMainCamera->GetRight();
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 7.0f) * timeDelta);
		}
		else if (KEY_MGR->IsStayDown('W') && KEY_MGR->IsStayDown('A'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "run")
			{
				this->renderObjects[0]->pSkinned->Play("run", 0.3f);
				renderObjects[1]->pSkinned->Play("run", 0.3f);

			}
			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = pMainCamera->GetForward() + (-(pMainCamera->GetRight()));
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 7.0f) * timeDelta);
		}
		else if (KEY_MGR->IsStayDown('S') && KEY_MGR->IsStayDown('D'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "run")
			{
				this->renderObjects[0]->pSkinned->Play("run", 0.3f);
				renderObjects[1]->pSkinned->Play("run", 0.3f);

			}
			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = -pMainCamera->GetForward() + pMainCamera->GetRight();
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 7.0f) * timeDelta);
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		}
		else if (KEY_MGR->IsStayDown('S') && KEY_MGR->IsStayDown('A'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "run")
			{
				this->renderObjects[0]->pSkinned->Play("run", 0.3f);
				renderObjects[1]->pSkinned->Play("run", 0.3f);

			}
			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = -pMainCamera->GetForward() - pMainCamera->GetRight();
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 7.0f) * timeDelta);
		
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		}
		else if (KEY_MGR->IsStayDown('W') &&
			!KEY_MGR->IsStayDown('S') &&
			!KEY_MGR->IsStayDown('A') &&
			!KEY_MGR->IsStayDown('D'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "run")
			{
				this->renderObjects[0]->pSkinned->Play("run", 0.3f);
				renderObjects[1]->pSkinned->Play("run", 0.3f);

			}
			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = pMainCamera->GetForward();
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 7.0f) * timeDelta);
		
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		}

		else if (KEY_MGR->IsStayDown('S') &&
			!KEY_MGR->IsStayDown('W') &&
			!KEY_MGR->IsStayDown('A') &&
			!KEY_MGR->IsStayDown('D'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "run")
			{
				this->renderObjects[0]->pSkinned->Play("run", 0.3f);
				renderObjects[1]->pSkinned->Play("run", 0.3f);

			}

			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = -(pMainCamera->GetForward());
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 7.0f) * timeDelta);

			//	pSkinnedTrans->MovePositionWorld(pSkinnedTrans->GetWorldPosition() + D3DXVECTOR3(0, 0, 0.1f));
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		}

		else if (KEY_MGR->IsStayDown('A') &&
			!KEY_MGR->IsStayDown('W') &&
			!KEY_MGR->IsStayDown('S') &&
			!KEY_MGR->IsStayDown('D'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "run")
			{
				this->renderObjects[0]->pSkinned->Play("run", 0.3f);
				renderObjects[1]->pSkinned->Play("run", 0.3f);

			}
			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = -(pMainCamera->GetRight());
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 7.0f) * timeDelta);
		
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		}

		else if (KEY_MGR->IsStayDown('D') &&
			!KEY_MGR->IsStayDown('S') &&
			!KEY_MGR->IsStayDown('A') &&
			!KEY_MGR->IsStayDown('W'))
		{
			if (renderObjects[0]->pSkinned->GetNowPlayAnimationName() != "run")
			{
				this->renderObjects[0]->pSkinned->Play("run", 0.3f);
				renderObjects[1]->pSkinned->Play("run", 0.3f);

			}
			D3DXVECTOR3 cameraPosition = pMainCamera->GetLocalPosition();
			D3DXVECTOR3 forward = pMainCamera->GetRight();
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXVECTOR3 right;
			D3DXVec3Cross(&right, &up, &forward);
			D3DXVec3Cross(&forward, &right, &up);
			D3DXVec3Normalize(&forward, &forward);
			D3DXVec3Normalize(&right, &right);

			D3DXMATRIXA16 matDir;
			memcpy(&matDir._11, &right, sizeof(D3DXVECTOR3));
			memcpy(&matDir._21, &up, sizeof(D3DXVECTOR3));
			memcpy(&matDir._31, &forward, sizeof(D3DXVECTOR3));
			memcpy(&matDir._41, &renderObjects[0]->pTransform->GetLocalPosition(), sizeof(D3DXVECTOR3));

			//pTransform->LookDirection(forward);
			renderObjects[0]->pTransform->SetRotateLocal(matDir);
			renderObjects[0]->pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 7.0f) * timeDelta);
			//renderObjects[1]->pTransform->LookDirection(renderObjects[0]->pTransform->GetForward());

		}
	}

}
