#include "stdafx.h"
#include "cMainGame.h"
#include "cImage.h"
#include "cScene_00.h"
#include "cScene_01.h"


cMainGame::cMainGame(void)
{
}


cMainGame::~cMainGame(void)
{
}

// # 셋팅 #
HRESULT cMainGame::Init(void)
{
	// # 랜덤 시드 #
	SetRandomSeed();

	// # 디바이스 생성 #
	CreateDevice();

	// # 매니저 세팅 #
	TIME_MGR->Init();
	LOG_MGR->Init(LOG_WINDOW | LOG_FILE, g_hWnd, "Dump");
	DXFONT_MGR->Init(Device);
	GIZMO_MGR->Init(Device);
	SPRITE_MGR->Init(Device);
	SCENE_MGR->Init();

	// 씬 생성
	SCENE_MGR->AddScene("씬0", new cScene_00());
	SCENE_MGR->AddScene("씬1", new cScene_01());

	SCENE_MGR->ChangeScene("씬1");

	// # 실패 시 #
	// return E_FAIL;
	// # 성공 시 #
	return S_OK;
}

// # 해제 #
void cMainGame::Release()
{
	// 씬 해제
	m_pNowScene->Release();
	SAFE_DELETE(m_pNowScene);

	// # 매니저 해제 #
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

	// # 디바이스 해제 #
	ReleaseDevice();
}

// # 업데이트 #
void cMainGame::Update()
{
	// # 타임 매니저 업데이트 #
	TIME_MGR->UpdateTime(60.0f);

	// # 한 프레임 갱신 시간 #
	double timeDelta = TIME_MGR->GetFrameDeltaSec();

	// # 씬 교체 #
	if (KEY_MGR->IsOnceDown(VK_F1)) SCENE_MGR->ChangeScene("씬0");
	else if (KEY_MGR->IsOnceDown(VK_F2)) SCENE_MGR->ChangeScene("씬1");

	// # 씬 업데이트 #
	SCENE_MGR->Update(timeDelta);
}

// # 드로우(렌더) #
void cMainGame::Draw()
{
	// # 버퍼를 청소한다. #
	HRESULT result = Device->Clear(
		0,							// # 청소할 영역의 D3DRECT 배열 갯수		( 전체 클리어 0 ) #
		NULL,						// # 청소할 영역의 D3DRECT 배열 포인터	( 전체 클리어 NULL ) #
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,		// # 청소될 버퍼 플레그 ( D3DCLEAR_TARGET 컬러버퍼, D3DCLEAR_ZBUFFER 깊이버퍼, D3DCLEAR_STENCIL 스텐실버퍼 #
		0xff202020,					// # 컬러버퍼를 청소하고 채워질 색상( 0xAARRGGBB ) #
		1.0f,						// # 깊이버퍼를 청소할값 ( 0 ~ 1, 0 이 카메라에서 제일가까운 1 이 카메라에서 제일 먼 ) #
		0							// # 스텐실 버퍼를 채울값 #
	);

	// # 버퍼 청소가 성공했으면? # 
	if (SUCCEEDED(result))
	{
		// # 디바이스 렌더링 시작 명령 #
		Device->BeginScene();

		// # 렌더링 명령 #

		// 씬 렌더
		//m_pNowScene->Render();
		SCENE_MGR->Render();

#ifdef _DEBUG	// # 디버그 모드에서만 실행 #

		//월드 그리드
		GIZMO_MGR->WorldGrid( 1, 10 );

		// # 타임 정보 출력 #
		TIME_MGR->DrawTimeInfo();
#endif

		Device->EndScene();

		// # 렌더링된 버퍼내용을 화면에 전송 #
		Device->Present(0, 0, 0, 0);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// # 메인 프로시져 함수 #
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

	case WM_DESTROY:			// # 윈도우가 파괴되면 #
		PostQuitMessage(0);		// # 프로그램 종료 요청 #
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

