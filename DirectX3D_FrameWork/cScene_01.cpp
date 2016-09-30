#include "StdAfx.h"
#include "cScene_01.h"
#include "cLight_Direction.h"
#include "cLight_Point.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cQuad.h"
#include "cTrailRender.h"

cScene_01::cScene_01(void)
{
}

cScene_01::~cScene_01(void)
{
}

HRESULT cScene_01::Scene_Init()
{
	/*
	//진행률
	SCENE_MGR->fProgress = 0.0f;
	SCENE_MGR->fString = "개벌찟 중";


	double startRealTime = TIME_MGR->GetNowRealTimeSec();

	while( true )
	{
	double nowReadTime = TIME_MGR->GetNowRealTimeSec();
	if( nowReadTime > startRealTime + 3.5 )
	break;
	}

	LOG_MGR->AddLog( "fffff" );


	//진행률
	SCENE_MGR->fProgress = 35.0f;
	SCENE_MGR->fString = "개벌찟2 중";


	startRealTime = TIME_MGR->GetNowRealTimeSec();

	while( true )
	{
	double nowReadTime = TIME_MGR->GetNowRealTimeSec();
	if( nowReadTime > startRealTime + 3.5 )
	break;
	}

	LOG_MGR->AddLog( "fffff" );
	*/
	this->pQuad = new cQuad();
	this->pQuadTrans = new cTransform();
//
//
//
//
//	//진행률
//	SCENE_MGR->fProgress = 70.0f;
//	SCENE_MGR->fString = "지형로딩 중";
//
	m_pTerrain = new cTerrain();
	m_pTerrain->Init(
		"../Resources/Testures/MyHeight512.bmp",
		"../Resources/Testures/terrain1.jpg",
		"../Resources/Testures/terrain2.png",
		"../Resources/Testures/terrain3.png",
		"../Resources/Testures/terrain4.png",
		"../Resources/Testures/Splat.png",
		1.0f,
		200.0f,
		3,
		100);

	m_pTerrainShadow = new cTerrain();
	m_pTerrainShadow->Init(
		"../Resources/Testures/MyHeight128.bmp",
		"../Resources/Testures/terrain1.jpg",
		"../Resources/Testures/terrain2.png",
		"../Resources/Testures/terrain3.png",
		"../Resources/Testures/terrain4.png",
		"../Resources/Testures/Splat.png",
		4.0f,
		200.0f,
		10,
		100);



//	//진행률
//	SCENE_MGR->fProgress = 90.0f;
//	SCENE_MGR->fString = "오브젝트 로딩 중";


	//원래 있던 매쉬에서 다음과 같은 행렬로 보정시켜 
	//모든 정보를 틀어버린다.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.007f, 0.007f, 0.007f);
	D3DXMATRIXA16 matCorrection = matScale;

	//원본 메쉬 로딩
	cXMesh_Static* mesh =
		RESOURCE_STATICXMESH->GetResource(
			"../Resources/Meshes/Tree/PineTree_01.X", &matCorrection);

	cXMesh_Static* Disc =
		RESOURCE_STATICXMESH->GetResource(
			"../Resources/Meshes/Disc.x");

	//오브젝트 생성
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		for (int j = 0; j < OBJECT_NUM; j++)
		{
			cBaseObject* pNewObject = new cBaseObject();
			pNewObject->SetMesh(mesh);
			pNewObject->SetActive(true);

			//if( j % 2 == 0 )
			//	pNewObject->IgnoreCreateShadow = true;	//그림자 안그림

			D3DXVECTOR3 pos(i * 10, 30.0f, j * 20);

			pos.y = this->m_pTerrain->GetHeight(pos.x, pos.z);

			//위치 셋팅
			pNewObject->pTransform->SetWorldPosition(pos);


			//랱더 오브젝트 푸쉬
			this->renderObjects.push_back(pNewObject);
		}
	}

	//디스크 추가
	//cBaseObject* pNewObject2 = new cBaseObject();
	//pNewObject2->SetMesh( Disc );
	//pNewObject2->SetActive( true );
	//pNewObject2->pTransform->SetWorldPosition( 0, -10.0f, 0.0f );
	//pNewObject2->IgnoreCreateShadow = true;		//그림자 안그린다.
	//this->renderObjects.push_back( pNewObject2 );

	//기본라이트 방향
	this->pSceneBaseDirectionLight->pTransform->RotateWorld(
		90.0f * ONE_RAD, 0, 0);

	this->SetEnvironment("../Resources/TextureCUBE/SuperKanjiCube.dds");



	D3DXMATRIXA16 matCorrection2;
	D3DXMatrixScaling(&matCorrection2, 0.1f, 0.1f, 0.1f);
	cXMesh_Skinned* pSkinned = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Female/Femail.X", &matCorrection2);

	cBaseObject* pChar;
	pChar = new cBaseObject();
	pChar->SetMesh(pSkinned);
	pChar->SetActive(true);

	D3DXVECTOR3 pos2(13, 0, 26);
	pos2.y = this->m_pTerrain->GetHeight(pos2.x, pos2.z);
	pChar->pTransform->SetWorldPosition(pos2);

	this->renderObjects.push_back(pChar);

	this->pQuadTrans->SetWorldPosition(pChar->pTransform->GetWorldPosition());
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

//	//진행률
//	SCENE_MGR->fProgress = 100.0f;
//	SCENE_MGR->fString = "로딩 끝 이새끼야....";
//
//
//	//TrailRenderSet
//	this->pTrailRender = new cTrailRender();
//	this->pTrailRender->Init(
//		1.0f,					//꼬리 라이브 타임 ( 이게 크면 환영큐 사이즈가 커지고 꼬리가 오랬동안 남아있다 )
//		1.0f,					//폭
//		RESOURCE_TEXTURE->GetResource("../Resources/Testures/TrailTest.png"),	//메인 Texture
//		D3DXCOLOR(1, 0, 0, 1),												//메인 Texture 로 그릴때 컬러
//		RESOURCE_TEXTURE->GetResource("../Resources/Testures/Stone-normal.jpg")	//외곡 그릴때 외곡 노말
//	);
//	this->pTrailRender->Transform.SetWorldPosition(pChar->pTransform->GetWorldPosition());


	return S_OK;
}

void cScene_01::Scene_Release()
{
	//오브젝트 해재
	for (int i = 0; i < this->renderObjects.size(); i++)
		SAFE_DELETE(this->renderObjects[i]);
	this->renderObjects.clear();
	this->cullObjects.clear();

	SAFE_RELEASE(this->m_pTerrain);
	SAFE_RELEASE(this->m_pTerrainShadow);

	for( int i = 0 ; i < this->lights.size() ; i++ )
		SAFE_DELETE( this->lights[i] );
	this->lights.clear();

	SAFE_DELETE(pQuad);
	SAFE_DELETE(pQuadTrans);

//	//Trail 해재
//	this->pTrailRender->Release();
//	SAFE_DELETE(this->pTrailRender);
}

void cScene_01::Scene_Update(float timDelta)
{
	if (KEY_MGR->IsOnceDown(VK_RETURN))
		SCENE_MGR->ChangeScene("씬0", 2);

	static int i = 0;

	if (KEY_MGR->IsOnceDown('1'))
		i = 0;
	else if (KEY_MGR->IsOnceDown('2'))
		i = 1;

	else if (KEY_MGR->IsOnceDown('3'))
		i = 2;

	else if (KEY_MGR->IsOnceDown('4'))
		i = 3;

	else if (KEY_MGR->IsOnceDown('5'))
		i = 4;
	
	if (i == 0)
		this->pSceneBaseDirectionLight->pTransform->DefaultControl2(timDelta);
	
	else if (i == 1)
		this->lights[0]->pTransform->DefaultControl2(timDelta);

	else if (i == 2)
		this->lights[1]->pTransform->DefaultControl2(timDelta);

	else if (i == 3)
		this->pQuadTrans->DefaultControl2(timDelta);

//	else if (i == 4)
//		this->pTrailRender->Transform.DefaultControl2(timDelta);


	for (int i = 0; i < this->renderObjects.size(); i++)
		this->renderObjects[i]->Update(timDelta);

//	//업데이트
//	this->pTrailRender->Update(timDelta);
//	//this->pTrailRender->Transform.DefaultControl2( timDelta );
	
	//쉐도우맵 준비
	this->ReadyShadowMap(&this->renderObjects, this->m_pTerrain);
}

void cScene_01::Scene_Render1()
{
	//라이트 정보 셋팅
	cXMesh_Skinned::SetLighting(&this->lights);
	cXMesh_Static::SetLighting(&this->lights);

	//카메라에 컬링된거만....
	this->cullObjects.clear();
	for (int i = 0; i < this->renderObjects.size(); i++) {
		//프러스텀 안에 있니?
		if (this->pMainCamera->Frustum.IsInFrustum(this->renderObjects[i]))
			this->cullObjects.push_back(this->renderObjects[i]);
	}

	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);

	cXMesh_Skinned::SetCamera(this->pMainCamera);
	cXMesh_Skinned::sSkinnedMeshEffect->SetTexture("Ramp_Tex", RESOURCE_TEXTURE->GetResource("../Resources/Testures/Ramp_1.png"));
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);

	for (int i = 0; i < this->cullObjects.size(); i++)
		this->cullObjects[i]->Render();

	m_pTerrain->Render(
		this->pMainCamera,
		this->pSceneBaseDirectionLight,
		this->pDirectionLightCamera);
	
	for (int i = 0; i < this->lights.size(); i++)
	{
		this->lights[i]->RenderGizmo();
	}

	/*
	static D3DXVECTOR3 scale( 0, 0, 0 );
	static float disAmout = 0.05f;

	if( KEY_MGR->IsOnceDown( VK_SPACE ) )
	{
	scale = D3DXVECTOR3( 0, 0, 0 );
	disAmout = 0.05f;
	}

	if( disAmout > 0.0f )
	{
	scale += D3DXVECTOR3( 10.0f, 10.0f, 10.0f ) * TIME_MGR->GetFrameDeltaSec();
	disAmout -= 0.05f * TIME_MGR->GetFrameDeltaSec();

	if( disAmout < 0.0f )
	disAmout = 0.0f;
	}

	this->pQuadTrans->SetScale( scale );
	
	//이전까지 그려진 내용을 9 번Texture 에 얻는다.
	GetDeviceGrabTexture( Device, this->pMainCamera->GetRenderTexture( 9 ) );
	LPDIRECT3DTEXTURE9 pDistortNormal = RESOURCE_TEXTURE->GetResource( "../Resources/Testures/CircleNormal.jpg" );
	this->pQuad->Render( this->pQuadTrans, this->pMainCamera->GetRenderTexture( 9 ), pDistortNormal, disAmout );
	*/

	//랜더 ( 왠만하면 알파블랜딩이니깐 나중에 그리자... )
	//this->pTrailRender->Render();
//	this->pTrailRender->RenderDistort(this->pMainCamera);
}


void cScene_01::Scene_Render_AfterPostEffect(LPDIRECT3DTEXTURE9 pScreen)
{
	static D3DXVECTOR3 scale(0, 0, 0);
	static float disAmout = 0.05f;

	if (KEY_MGR->IsOnceDown(VK_SPACE))
	{
		scale = D3DXVECTOR3(0, 0, 0);
		disAmout = 0.05f;
	}

	if (disAmout > 0.0f)
	{
		scale += D3DXVECTOR3(10.0f, 10.0f, 10.0f) * TIME_MGR->GetFrameDeltaSec();
		disAmout -= 0.05f * TIME_MGR->GetFrameDeltaSec();

		if (disAmout < 0.0f)
			disAmout = 0.0f;
	}

	this->pQuadTrans->SetScale(scale);

	//이전까지 그려진 내용을 9 번Texture 에 얻는다.
	GetDeviceGrabTexture(Device, this->pMainCamera->GetRenderTexture(9));
	LPDIRECT3DTEXTURE9 pDistortNormal = RESOURCE_TEXTURE->GetResource("../Resources/Testures/CircleNormal.jpg");
	this->pQuad->Render(this->pQuadTrans, this->pMainCamera->GetRenderTexture(9), pDistortNormal, disAmout);


	/*
	this->pQuadTrans->SetScale( 5, 5, 5 );
	//이전까지 그려진 내용을 9 번Texture 에 얻는다.
	GetDeviceGrabTexture( Device, this->pMainCamera->GetRenderTexture( 9 ) );
	LPDIRECT3DTEXTURE9 pDistortNormal = RESOURCE_TEXTURE->GetResource( "../Resources/Testures/Stone-normal.jpg" );
	this->pQuad->Render( this->pQuadTrans, this->pMainCamera->GetRenderTexture( 9 ), pDistortNormal, 0.05f );
	*/

	/*
	this->pQuadTrans->SetScale( 5, 5, 5 );
	//이전까지 그려진 내용을 9 번Texture 에 얻는다.
	GetDeviceGrabTexture( Device, this->pMainCamera->GetRenderTexture( 9 ) );
	LPDIRECT3DTEXTURE9 pDistortNormal = RESOURCE_TEXTURE->GetResource( "../Resources/Testures/Stone-normal.jpg" );
	this->pQuad->Render( this->pQuadTrans, this->pMainCamera->GetRenderTexture( 9 ), pDistortNormal, 0.005f );
	*/
}

void cScene_01::Scene_RenderSprite()
{
	GetDeviceGrabTexture( Device, this->pMainCamera->GetRenderTexture( 9 ) );
	RECT rcSour = { 0, 0, WINSIZE_X, WINSIZE_Y };
	RECT rcDest = { 0, 0, 300, 300 };
	SPRITE_MGR->DrawArea(  this->pMainCamera->GetRenderTexture( 9 ), &rcSour, &rcDest );
}