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

#include "cPigNose.h"


CollisionTestScene::CollisionTestScene()
{
}


CollisionTestScene::~CollisionTestScene()
{
}

HRESULT CollisionTestScene::Scene_Init()
{
	//기본라이트 방향
	this->pSceneBaseDirectionLight->pTransform->RotateWorld(
		90.0f * ONE_RAD, 0, 0);

//	this->SetEnvironment("../Resources/TextureCUBE/SuperKanjiCube.dds");


	pPigNose = new cPigNose;
	pPigNose->Init();

	pPigNose2 = new cPigNose;
	pPigNose2->Init();

	pPigNose2->getCharObject()->pTransform->SetWorldPosition(3, 0, 5);

	return S_OK;
}

void CollisionTestScene::Scene_Release()
{
	SAFE_RELEASE(pPigNose);
	SAFE_RELEASE(pPigNose2);
}

void CollisionTestScene::Scene_Update(float timeDelta)
{
	pPigNose->getCharObject()->pTransform->DefaultControl2(timeDelta);
	pPigNose->Update(timeDelta);
	pPigNose2->Update(timeDelta);
//	PHYSICS_MGR->IsBlocking(pPigNose->getCharObject()->pTransform,
//		&pPigNose->getCharObject()->BoundBox,
//		pPigNose2->getCharObject()->pTransform,
//		&pPigNose2->getCharObject()->BoundBox, 0.0f);

//	PHYSICS_MGR->IsBlocking(pPigNose->getCharObject(),
//		pPigNose2->getCharObject(), 0.0f);

	bool bReturn = false;

//	bReturn = PHYSICS_MGR->IsOverlap(pPigNose->getCharObject(),
//		pPigNose2->getCharObject());
	bReturn = PHYSICS_MGR->IsOverlap(pPigNose->getCharObject()->pTransform,
		&(cBoundSphere)pPigNose->getCharObject()->BoundBox,
		pPigNose2->getCharObject()->pTransform,
		&(cBoundSphere)pPigNose2->getCharObject()->BoundBox);

	if (bReturn)
		pPigNose->getCharObject()->pTransform->SetWorldPosition(0, 0, 0);
}

void CollisionTestScene::Scene_Render1()
{
	cXMesh_Skinned::SetCamera(this->pMainCamera);
	cXMesh_Skinned::sSkinnedMeshEffect->SetTexture("Ramp_Tex", RESOURCE_TEXTURE->GetResource("../Resources/Testures/Ramp_1.png"));
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);

	pPigNose->Render();
	pPigNose2->Render();
}

void CollisionTestScene::Scene_RenderSprite()
{

}

void CollisionTestScene::Scene_Render_AfterPostEffect(LPDIRECT3DTEXTURE9 pScreen)
{

}