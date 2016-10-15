#include "stdafx.h"
#include "cGhostAndToadTestScene.h"
#include "cLight_Direction.h"
#include "cLight_Point.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"

#include "cEnemy.h"
#include "cGhost.h"
#include "cToad.h"
#include "cSnake.h"
#include "cPixie.h"
#include "cAlice2.h"

// # 이 씬의 목적 #
// # 두꺼비에게 사신이 다가가면 두꺼비는 당긴다 #
// # 거의 다 다가갔을 때 사신은 죽어버린다 #

// - 이 외의 목적 -
// # 각 모델링을 테스트함 #


cGhostAndToadTestScene::cGhostAndToadTestScene()
{
}


cGhostAndToadTestScene::~cGhostAndToadTestScene()
{
}

HRESULT cGhostAndToadTestScene::Scene_Init()
{
	// 기본라이트 방향
	this->pSceneBaseDirectionLight->pTransform->RotateWorld(
		90.0f * ONE_RAD, 0, 0);

	this->SetEnvironment("../Resources/TextureCUBE/SuperKanjiCube.dds");

	// # 테스트용 두꺼비와 사신 초기화 #
	pGhost = new cGhost;
	pGhost->Init();
	pToad = new cToad;
	pToad->Init();
	pGhost->getCharObject()->pTransform->MovePositionWorld(5, 0, 0);
	pToad->getCharObject()->pTransform->MovePositionWorld(-5, 0, 0);

	pToad->AddTarget(pGhost->getCharObject());
	
	pSnake = new cSnake;
	pSnake->Init();
	pSnake->getCharObject()->pTransform->MovePositionWorld(0, 0, 5);

	pPixie = new cPixie;
	pPixie->Init();
	pPixie->getCharObject()->pTransform->MovePositionWorld(0, 0, -5);

	pAlice2 = new cAlice2;
	pAlice2->Init();
	pAlice2->getCharObject()->pTransform->MovePositionWorld(10, 0, 10);

	return S_OK;
}

void cGhostAndToadTestScene::Scene_Release()
{
	pGhost->Release();
	pToad->Release();
	pSnake->Release();
	pPixie->Release();
	pAlice2->Release();
}

void cGhostAndToadTestScene::Scene_Update(float timeDelta)
{
	testAnimation();

	pGhost->Update(timeDelta);
	pToad->Update(timeDelta);
	pSnake->Update(timeDelta);
	pPixie->Update(timeDelta);
	pAlice2->Update(timeDelta);
}

void cGhostAndToadTestScene::Scene_Render1()
{
	cXMesh_Skinned::SetCamera(this->pMainCamera);
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);

	pGhost->Render();
	pToad->Render();
	pSnake->Render();
	pPixie->Render();
	pAlice2->Render();
}

void cGhostAndToadTestScene::Scene_RenderSprite()
{
}

void cGhostAndToadTestScene::Scene_Render_AfterPostEffect(LPDIRECT3DTEXTURE9 pScreen)
{
}

void cGhostAndToadTestScene::testAnimation()
{
	if (KEY_MGR->IsStayDown('A'))
	{
		if (KEY_MGR->IsOnceDown(VK_NUMPAD0))
			pGhost->getCharObject()->pSkinned->Play("Wait", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD1))
			pGhost->getCharObject()->pSkinned->Play("Walk", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD2))
			pGhost->getCharObject()->pSkinned->Play("UnArmedWait", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD3))
			pGhost->getCharObject()->pSkinned->Play("Die", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD4))
			pGhost->getCharObject()->pSkinned->Play("Die2", 0.3f);
	}
	if (KEY_MGR->IsStayDown('S'))
	{
		if (KEY_MGR->IsOnceDown(VK_NUMPAD0))
			pToad->getCharObject()->pSkinned->Play("Wait", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD1))
			pToad->getCharObject()->pSkinned->Play("Atk1", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD2))
			pToad->getCharObject()->pSkinned->Play("Atk2", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD3))
			pToad->getCharObject()->pSkinned->Play("BeHit", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD4))
			pToad->getCharObject()->pSkinned->Play("Die", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD5))
			pToad->getCharObject()->pSkinned->Play("Die2", 0.3f);
	}
	if (KEY_MGR->IsStayDown('D'))
	{
		if (KEY_MGR->IsOnceDown(VK_NUMPAD0))
			pSnake->getCharObject()->pSkinned->Play("Spawn", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD1))
			pSnake->getCharObject()->pSkinned->Play("Spawn2", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD2))
			pSnake->getCharObject()->pSkinned->Play("Down", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD3))
			pSnake->getCharObject()->pSkinned->Play("Down2", 0.3f);
	}
	if (KEY_MGR->IsStayDown('F'))
	{
		if (KEY_MGR->IsOnceDown(VK_NUMPAD0))
			pPixie->getCharObject()->pSkinned->Play("Idle", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD1))
			pPixie->getCharObject()->pSkinned->Play("Run", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD2))
			pPixie->getCharObject()->pSkinned->Play("Wait", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD3))
			pPixie->getCharObject()->pSkinned->Play("Atk", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD4))
			pPixie->getCharObject()->pSkinned->Play("Die", 0.3f);
		if (KEY_MGR->IsOnceDown(VK_NUMPAD5))
			pPixie->getCharObject()->pSkinned->Play("Die2", 0.3f);
	}
	if (KEY_MGR->IsOnceDown('M'))
	{
		SOUND_MGR->AddSound("테스트", "../Resources/Sounds/숲브금.mp3", true, true);
		SOUND_MGR->Play("테스트");
	}
	if (KEY_MGR->IsOnceDown('N'))
	{
		SOUND_MGR->Stop("테스트");
	}
}
