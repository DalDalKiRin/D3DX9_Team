#include "stdafx.h"
#include "cMainGame.h"
#include "cImage.h"
#include "cScene_00.h"
#include "cScene_01.h"

// # cScene #
#include "cScene_Boss.h"
#include "cScene_Chapter_00.h"
#include "cScene_Chapter_01.h"
#include "cScene_Town.h"
#include "cScene_Intro.h"
#include "cScene_GameClear.h"
#include "cScene_GameOver.h"
#include "cScene_Title.h"
#include "cScene_Synopsis.h"
#include "cScene_Loading.h"

cMainGame::cMainGame(void)
	: m_nCurrentSceneIndex(0)
{
}


cMainGame::~cMainGame(void)
{
}

// # ���� #
HRESULT cMainGame::Init(void)
{
	// # ���� �õ� #
	SetRandomSeed();

	// # ����̽� ���� #
	CreateDevice();

	// # �Ŵ��� ���� #
	TIME_MGR->Init();
	LOG_MGR->Init(LOG_WINDOW | LOG_FILE, g_hWnd, "Dump");
	DXFONT_MGR->Init(Device);
	GIZMO_MGR->Init(Device);
	SPRITE_MGR->Init(Device);
	SCENE_MGR->Init();

	// �� ����
	SCENE_MGR->AddScene("��0", new cScene_00());
	SCENE_MGR->AddScene("��1", new cScene_01());
	SCENE_MGR->ChangeScene("��1");

	/* # �츮 �� # */
	m_vecSceneName.clear();

	SCENE_MGR->AddScene("Intro", new cScene_Intro());
	m_vecSceneName.push_back("Intro");

	SCENE_MGR->AddScene("Title", new cScene_Title());
	m_vecSceneName.push_back("Title");

	SCENE_MGR->AddScene("Synopsis", new cScene_Synopsis());
	m_vecSceneName.push_back("Synopsis");

	SCENE_MGR->AddScene("Town", new cScene_Town());
	m_vecSceneName.push_back("Town");

	SCENE_MGR->AddScene("Chapter_00", new cScene_Chapter_00());
	m_vecSceneName.push_back("Chapter_00");

	SCENE_MGR->AddScene("Chapter_01", new cScene_Chapter_01());
	m_vecSceneName.push_back("Chapter_01");

	SCENE_MGR->AddScene("Boss", new cScene_Boss());
	m_vecSceneName.push_back("Boss");

	SCENE_MGR->AddScene("Clear", new cScene_GameClear());
	m_vecSceneName.push_back("Clear");

	SCENE_MGR->AddScene("Over", new cScene_GameOver());
	m_vecSceneName.push_back("Over");

	SCENE_MGR->AddScene("Loading", new cScene_Loading());
	m_vecSceneName.push_back("Loading");


	// # ���� �� #
	// return E_FAIL;
	// # ���� �� #
	return S_OK;
}

// # ���� #
void cMainGame::Release()
{
	// �� ����
	m_pNowScene->Release();
	SAFE_DELETE(m_pNowScene);

	// # �Ŵ��� ���� #
	GIZMO_MGR->Release();
	cGizmoManager::ReleaseInstance();
	TIME_MGR->Release();
	cTimeMgr::ReleaseInstance();
	KEY_MGR->Release();
	cKeyMgr::ReleaseInstance();
	LOG_MGR->Release();
	cLogMgr::ReleaseInstance();
	DXFONT_MGR->Release();
	cDXFontManager::ReleaseInstance();
	SPRITE_MGR->Release();
	cSpriteManager::ReleaseInstance();
	SCENE_MGR->Release();
	cSceneManager::ReleaseInstance();
	cPhysicManager::ReleaseInstance();

	RESOURCE_TEXTURE->ClearResource();
	cResourceMgr_Texture::ReleaseInstance();
	RESOURCE_FX->ClearResource();
	cResourceMgr_ShaderFX::ReleaseInstance();
	RESOURCE_STATICXMESH->ClearResource();
	cResourceMgr_XStaticMesh::ReleaseInstance();
	RESOURCE_SKINNEDXMESH->ClearResource();
	cResourceMgr_XSkinnedMesh::ReleaseInstance();

	// # ����̽� ���� #
	ReleaseDevice();
}

// # ������Ʈ #
void cMainGame::Update()
{
	// # Ÿ�� �Ŵ��� ������Ʈ #
	TIME_MGR->UpdateTime(60.0f);

	// # �� ������ ���� �ð� #
	double timeDelta = TIME_MGR->GetFrameDeltaSec();

	// # �� ��ü #
	if (KEY_MGR->IsOnceDown(VK_F1)) SCENE_MGR->ChangeScene("��0");
	else if (KEY_MGR->IsOnceDown(VK_F2)) SCENE_MGR->ChangeScene("��1");

	NextControl();

	

	// # �� ������Ʈ #
	SCENE_MGR->Update(timeDelta);
}

// # ��ο�(����) #
void cMainGame::Draw()
{
	// # ���۸� û���Ѵ�. #
	HRESULT result = Device->Clear(
		0,							// # û���� ������ D3DRECT �迭 ����		( ��ü Ŭ���� 0 ) #
		NULL,						// # û���� ������ D3DRECT �迭 ������	( ��ü Ŭ���� NULL ) #
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,		// # û�ҵ� ���� �÷��� ( D3DCLEAR_TARGET �÷�����, D3DCLEAR_ZBUFFER ���̹���, D3DCLEAR_STENCIL ���ٽǹ��� #
		0xff202020,					// # �÷����۸� û���ϰ� ä���� ����( 0xAARRGGBB ) #
		1.0f,						// # ���̹��۸� û���Ұ� ( 0 ~ 1, 0 �� ī�޶󿡼� ���ϰ���� 1 �� ī�޶󿡼� ���� �� ) #
		0							// # ���ٽ� ���۸� ä�ﰪ #
	);

	// # ���� û�Ұ� ����������? # 
	if (SUCCEEDED(result))
	{
		// # ����̽� ������ ���� ��� #
		Device->BeginScene();

		// # ������ ��� #

		// �� ����
		//m_pNowScene->Render();
		SCENE_MGR->Render();

#ifdef _DEBUG	// # ����� ��忡���� ���� #

		//���� �׸���
		GIZMO_MGR->WorldGrid( 1, 10 );


		// # Ÿ�� ���� ��� #
		TIME_MGR->DrawTimeInfo();

		SCENE_MGR->DrawSceneInfo();
#endif

		Device->EndScene();

		// # �������� ���۳����� ȭ�鿡 ���� #
		Device->Present(0, 0, 0, 0);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// # ���� ���ν��� �Լ� #
LRESULT cMainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_TIMER:
		Update();
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_DESTROY:			// # �����찡 �ı��Ǹ� #
		PostQuitMessage(0);		// # ���α׷� ���� ��û #
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void cMainGame::NextControl(void)
{
	if (KEY_MGR->IsOnceDown(VK_F11))
	{
		m_nCurrentSceneIndex--;
		if (m_nCurrentSceneIndex < 0) m_nCurrentSceneIndex = 0;
		SCENE_MGR->ChangeScene(m_vecSceneName[m_nCurrentSceneIndex]);
	}

	if (KEY_MGR->IsOnceDown(VK_F12))
	{
		m_nCurrentSceneIndex++;
		if (m_nCurrentSceneIndex > 9) m_nCurrentSceneIndex = 9;
		SCENE_MGR->ChangeScene(m_vecSceneName[m_nCurrentSceneIndex]);
	}
}

