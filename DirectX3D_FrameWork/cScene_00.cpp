#include "StdAfx.h"
#include "cScene_00.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTrailRender.h"


cScene_00::cScene_00(void)
{
}

cScene_00::~cScene_00(void)
{
}

HRESULT cScene_00::Scene_Init()
{
	//원래 있던 매쉬에서 다음과 같은 행렬로 보정시켜 
	//모든 정보를 틀어버린다.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, 180.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	//원본 메쉬 로딩
	cXMesh_Static* mesh =
		RESOURCE_STATICXMESH->GetResource(
			"../Resources/Meshes/Fighter/Fighter.X", &matCorrection);


	cXMesh_Static* box =
		RESOURCE_STATICXMESH->GetResource(
			"../Resources/Meshes/Disc.x");

	//오브젝트 생성
	cBaseObject* pNewObject1 = new cBaseObject();
	pNewObject1->SetMesh(mesh);
	pNewObject1->SetActive(true);

	cBaseObject* pNewObject2 = new cBaseObject();
	pNewObject2->SetMesh(box);
	pNewObject2->SetActive(true);
	pNewObject2->pTransform->SetWorldPosition(0, -10.0f, 0.0f);
	pNewObject2->IgnoreCreateShadow = true;		//그림자 안그린다.
	pNewObject2->ApplyShadow = true;


	cBaseObject* pNewObject3 = new cBaseObject();
	pNewObject3->SetMesh(mesh);
	pNewObject3->SetActive(true);
	pNewObject3->pTransform->SetWorldPosition(0, -5.0f, 0.0f);
	pNewObject3->ApplyShadow = true;


	//랱더 오브젝트 푸쉬
	this->renderObjects.push_back(pNewObject1);
	this->renderObjects.push_back(pNewObject2);
	this->renderObjects.push_back(pNewObject3);



	//라이트 위치
	this->pSceneBaseDirectionLight->pTransform->SetWorldPosition(0, 20, 0);
	this->pSceneBaseDirectionLight->pTransform->SetRotateWorld(90.0f * ONE_RAD, 0, 0);



	//TrailRenderSet
	this->pTrailRender = new cTrailRender();
	this->pTrailRender->Init(
		1.0f,					//꼬리 라이브 타임 ( 이게 크면 환영큐 사이즈가 커지고 꼬리가 오랬동안 남아있다 )
		1.0f,					//폭
		RESOURCE_TEXTURE->GetResource("../Resources/Testures/TrailTest.png"),	//메인 Texture
		D3DXCOLOR(1, 0, 0, 1),												//메인 Texture 로 그릴때 컬러
		RESOURCE_TEXTURE->GetResource("../Resources/Testures/TrailTest.png")	//외곡 그릴때 외곡 노말
	);


	return S_OK;
}

void cScene_00::Scene_Release()
{
	//오브젝트 해재
	for (int i = 0; i < this->renderObjects.size(); i++)
		SAFE_DELETE(this->renderObjects[i]);
	this->renderObjects.clear();
	this->cullObjects.clear();

	//Trail 해재
	this->pTrailRender->Release();
	SAFE_DELETE(this->pTrailRender);
}

void cScene_00::Scene_Update(float timDelta)
{
	this->pMainCamera->UpdateFrustum();
	this->cullObjects.clear();
	for (int i = 0; i < this->renderObjects.size(); i++) {

		this->renderObjects[i]->Update(timDelta);

		//프러스텀 안에 있니?
		if (this->pMainCamera->Frustum.IsInFrustum(this->renderObjects[i]))
		{
			this->cullObjects.push_back(this->renderObjects[i]);
		}
	}


	//업데이트
	this->pTrailRender->Update(timDelta);
	this->pTrailRender->Transform.DefaultControl2(timDelta);


	//쉐도우맵 준비
	this->ReadyShadowMap(&this->renderObjects);  //랜더링될 오브젝트 전달한다 ( 반드시 Render 에서 하지말고 업데이트에서 해라 )
}

void cScene_00::Scene_Render1()
{
	cXMesh_Static::SetCamera(this->pMainCamera);

	//베이스 라이팅 셋팅
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);



	for (int i = 0; i < this->cullObjects.size(); i++) {
		this->cullObjects[i]->Render();
	}

	//프러텀을 그려보장
	this->pDirectionLightCamera->Frustum.RenderGizmo();
	this->pSceneBaseDirectionLight->pTransform->RenderGizmo();


	//랜더 ( 왠만하면 알파블랜딩이니깐 나중에 그리자... )
	this->pTrailRender->Render();
}

void cScene_00::Scene_RenderSprite()
{
	//쉐도우 맵을 그려보자....
	RECT rcSour = { 0, 0, 4096, 4096 };
	RECT rcDest = { 0, 0, 300, 300 };


	SPRITE_MGR->DrawArea(this->pDirectionLightCamera->GetShadowTexture(),
		&rcSour,
		&rcDest);
}