#include "stdafx.h"
#include "cEnemyShowScene.h"
#include "cLight_Direction.h"
#include "cLight_Point.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cTrailRender.h"

#include "cAlice.h";
#include "cAlice2.h";
#include "cGhost.h";
#include "cPixie.h";
#include "cPumpkin.h";
#include "cRunMonster.h";
#include "cSnake.h";
#include "cToad.h";
#include "cVampirGentleman.h";
#include "cVampirLady.h";
#include "cZombie.h";
#include "cZombie2.h";


cEnemyShowScene::cEnemyShowScene()
	: Count(0)
	, CurrentAnimationNum(0)
	, MaxAnimationNum(100)
{
}


cEnemyShowScene::~cEnemyShowScene()
{
}

HRESULT cEnemyShowScene::Scene_Init()
{
	//기본라이트 방향
	this->pSceneBaseDirectionLight->pTransform->RotateWorld(
		90.0f * ONE_RAD, 0, 0);

	// # 환경 구 이미지 보여줌 #
	this->SetEnvironment("../Resources/TextureCUBE/SuperKanjiCube.dds");

	this->LoadEnemy();

	this->pTrail = new cTrailRender;
	this->pTrail->Init(
		2.0f,
		3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Testures/TrailTest.png"),
		D3DXCOLOR(0, 0, 1, 0.5f),
		RESOURCE_TEXTURE->GetResource("../Resources/Testures/TrailTest.png")
	);
	
	return S_OK;
}

void cEnemyShowScene::Scene_Release()
{
	for (int i = 0; i < vEnemys.size(); i++)
	{
		SAFE_RELEASE(vEnemys[i]);
	}

	// Trail 해제
	this->pTrail->Release();
	SAFE_DELETE(this->pTrail);
}

void cEnemyShowScene::Scene_Update(float timeDelta)
{
	vEnemys[Count]->Update(timeDelta);
	SceneControl();

	this->pTrail->Update(timeDelta);
	this->pTrail->Transform.DefaultControl2(timeDelta);
}

void cEnemyShowScene::Scene_Render1()
{
	cXMesh_Skinned::SetCamera(this->pMainCamera);
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);

	SelectEnemyRender();

	this->pTrail->Render();
}

void cEnemyShowScene::Scene_RenderSprite()
{
}

void cEnemyShowScene::Scene_Render_AfterPostEffect(LPDIRECT3DTEXTURE9 pScreen)
{
}

void cEnemyShowScene::SceneControl()
{
	if (KEY_MGR->IsOnceDown(VK_LEFT))
	{
		if (Count == 0) Count = MAX_ENEMY_NUM - 1;
		else Count--;

		CurrentAnimationNum = 0;
		MaxAnimationNum = vEnemys[Count]->getCharObject()->pSkinned->GetAnimSetSize();
	}
	else if (KEY_MGR->IsOnceDown(VK_RIGHT))
	{
		if (Count == MAX_ENEMY_NUM - 1) Count = 0;
		else Count++;

		CurrentAnimationNum = 0;
		MaxAnimationNum = vEnemys[Count]->getCharObject()->pSkinned->GetAnimSetSize();
	}
	else if (KEY_MGR->IsOnceDown(VK_UP))
	{
		if (CurrentAnimationNum == MaxAnimationNum - 1) CurrentAnimationNum = 0;
		else CurrentAnimationNum++;
		vEnemys[Count]->getCharObject()->pSkinned->Play(CurrentAnimationNum, 0.3f);
	}
	else if (KEY_MGR->IsOnceDown(VK_DOWN))
	{
		if (CurrentAnimationNum == 0) CurrentAnimationNum = MaxAnimationNum - 1;
		else CurrentAnimationNum--;
		vEnemys[Count]->getCharObject()->pSkinned->Play(CurrentAnimationNum, 0.3f);
	}
}

void cEnemyShowScene::LoadEnemy()
{
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		cEnemy* newEnemy;
		if (i == 0) newEnemy = new cAlice;
		else if (i == 1) newEnemy = new cAlice2;
		else if (i == 2) newEnemy = new cGhost;
		else if (i == 3) newEnemy = new cPixie;
		else if (i == 4) newEnemy = new cPumpkin;
		else if (i == 5) newEnemy = new cRunMonster;
		else if (i == 6) newEnemy = new cSnake;
		else if (i == 7) newEnemy = new cToad;
		else if (i == 8) newEnemy = new cVampirGentleman;
		else if (i == 9) newEnemy = new cVampirLady;
		else if (i == 10) newEnemy = new cZombie;
		else if (i == 11) newEnemy = new cZombie2;
		newEnemy->Init();
		newEnemy->getCharObject()->pSkinned->Play(0, 0.3f);
		vEnemys.push_back(newEnemy);
	}
	MaxAnimationNum = vEnemys[0]->getCharObject()->pSkinned->GetAnimSetSize();
}

void cEnemyShowScene::SelectEnemyRender()
{
	vEnemys[Count]->Render();
	vEnemys[Count]->RenderAnimationName();
	DXFONT_MGR->PrintText("Play", 100, 100 + (CurrentAnimationNum * 20), 0xff00ff00);
}