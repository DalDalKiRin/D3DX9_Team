#include "stdafx.h"
#include "cSceneManager.h"
#include "cSceneChangeEffectUpDown.h"

// LPVOID 는 void*형 포인터
// void* 포인터는 모든 주소를 다 받을 수 있으며 받은 주소를 형변환하여 사용
DWORD CALLBACK LoadingThread(LPVOID lpParam)
{
	// 매개 변수로 받은 씬 형변환
	cScene* pScene = (cScene*)lpParam;

	// 로딩 정보 초기화
	SCENE_MGR->fProgress = 0.0f;
	SCENE_MGR->fString = "";

	// 매개 변수로 받은 씬 초기화
	pScene->Init();

	// 여기까지 왔다면 pScene는 초기화가 끝난 것임
	// SCENE_MGR->m_pNowScene = pScene;

	// 초기화가 씬 전환 효과보다 먼저 이루어질 수 있다.
	// 이때 효과가 진행중일 때 교체하지 말자
	// 참고로 효과가 진행중일 때 씬을 교체하게 되면
	// 씬 효과가 끝나고 로딩 씬이 불러지는 상황이면
	// 로딩 씬이 호출된다.

	while (true)
	{
		// 교체 Effect 가 끝났다.
		if (SCENE_MGR->m_pNowChangeEffect == NULL)
		{
			// 이 곳에서 이전 씬을 해제할 필요는 없다 (이전 씬은 로딩씬임)
			//SCENE_MGR->m_pReleaseScene = SCENE_MGR->m_pNowScene;

			// 빠져 나가는 효과
			cSceneChangeEffect* pChangeEffect = SCENE_MGR->m_pChangeEffects[SCENE_MGR->m_nOutEffect];

			// 빠져 나가는 효과가 존재하지 않는다면
			if (pChangeEffect == NULL)
				SCENE_MGR->m_pNowScene = pScene;
			// 빠져 나가는 효과가 존재하면
			else
			{
				// 변경 효과 씬 등록
				SCENE_MGR->m_pNowChangeEffect = pChangeEffect;

				// 이전 씬은 효과가 끝나고 자동으로 해제 됨
				// (이때 이전 씬은 로딩 씬이기 때문에 해제가 등록된다고 하더라도 해제되지 않음)
				pChangeEffect->ChangeStart(
					SCENE_MGR->m_pNowScene,
					pScene,
					1.0f);
			}
			break;
		}
	}

	return 0;
}

cSceneManager::cSceneManager()
	: m_pNowScene(NULL)
	, m_pReleaseScene(NULL)
	, m_pNowChangeEffect(NULL)
	, m_strNowSceneName("")
{
}

cSceneManager::~cSceneManager()
{
}

HRESULT cSceneManager::Init()
{
	// 씬 전환 효과 추가
	m_pChangeEffects.push_back(NULL);		// 0번은 효과 없음 따라서 NULL 추가

	cSceneChangeEffect* pEffect1 = new cSceneChangeEffect;
	pEffect1->Init();
	m_pChangeEffects.push_back(pEffect1);

	cSceneChangeEffect* pEffect2 = new cSceneChangeEffectUpDown;
	pEffect2->Init();
	m_pChangeEffects.push_back(pEffect2);

	return S_OK;
}

void cSceneManager::Release()
{
	// 올려 있는 씬이 있다면.
	if (this->m_pNowScene != NULL)
	{
		this->m_pNowScene->Release();
	}

	// 전환 효과 싹다 날린다. (0번은 NULL이니 1번부터)
	for (int i = 1; i < this->m_pChangeEffects.size(); i++)
	{
		m_pChangeEffects[i]->Release();
		SAFE_DELETE(m_pChangeEffects[i]);
	}
}

void cSceneManager::Update(float timeDelta)
{
	// 날릴 씬이 있다면
	if (m_pReleaseScene)
	{
		bool sceneIsLoading = false;
		MAP_SCENE::iterator iter;

		for (iter = this->m_LoadingScenes.begin(); iter != m_LoadingScenes.end(); ++iter)
		{
			// 날릴 씬이 로딩 씬이라면 날리면 안된다.
			if (iter->second == m_pReleaseScene)
			{
				sceneIsLoading = true;
				break;
			}
		}

		// 지금 현재 날리는 씬이 로딩 씬이 아니라면 안심하고 날리자
		if (sceneIsLoading == false)
		{
			m_pReleaseScene->Release();
		}
		m_pReleaseScene = NULL;
	}

	// 변경 효과가 있다면
	if (m_pNowChangeEffect)
	{
		m_pNowChangeEffect->Update(timeDelta);
	}
	else
	{
		if (m_pNowScene)
			m_pNowScene->Update(timeDelta);
	}
}

void cSceneManager::Render()
{
	// 변경 효과가 있다면

	// 드로우 준비가 되지 않았다면 체인지 Effect 를 그리면 안됨
	if (m_pNowChangeEffect && m_pNowChangeEffect->IsDrawReady())
	{
		m_pNowChangeEffect->Render();
	}
	else
	{
		if (m_pNowScene)
			m_pNowScene->Render();
	}
}

// 게임에 사용되는 씬 추가 씬들은 초기화가 안됨
void cSceneManager::AddScene(std::string sceneName, cScene* pScene)
{
	MAP_SCENE::iterator iter = m_Scenes.find(sceneName);

	// 중복 방지
	if (iter == m_Scenes.end())
	{
		m_Scenes.insert(std::make_pair(sceneName, pScene));
	}
}

// 게임에 사용되는 로딩 씬 추가 씬들은 모두 초기화된 상태가 된다.
void cSceneManager::AddLoadingScene(std::string sceneName, cScene* pScene)
{
	MAP_SCENE::iterator iter = m_LoadingScenes.find(sceneName);

	// 중복 방지
	if (iter == m_LoadingScenes.end())
	{
		// Init을 하고 넣음.
		pScene->Init();
		m_LoadingScenes.insert(std::make_pair(sceneName, pScene));
	}
}

// 씬 변경
void cSceneManager::ChangeScene(std::string sceneName, int effectNum)
{
	// 교체 Effect
	cSceneChangeEffect* pChangeEffect = this->m_pChangeEffects[effectNum];

	// 씬을 찾는다.
	MAP_SCENE::iterator iter = m_Scenes.find(sceneName);

	// 못 찾으면
	if (iter == m_Scenes.end())
		return;

	// -------- # 추가 예외 처리 # -----------

	// 현재 씬과 체인지 씬이 같으면 안바꿈
//	if (m_pNowScene == iter->second)
//		return;

	if (m_pNowScene == iter->second)
	{
		m_pNowScene->Release();
		m_pNowScene->Init();
		m_strNowSceneName = sceneName;
		return;
	}

	// --------------------------------------

	// 기존에 물려있는 씬이 있고 체인지 효과가 있다면
	if (m_pNowScene && pChangeEffect != NULL)
	{
		m_pNowChangeEffect = pChangeEffect;

		// 두번 째 씬은 Init 된 상태로 들어간다.
		iter->second->Init();
		m_strNowSceneName = sceneName;

		// 체인지 효과 발동
		m_pNowChangeEffect->ChangeStart(
			m_pNowScene,
			iter->second,
			1.0f			// 효과 체인지 시간
		);
	}
	// 그게 아니라면
	else
	{
		// 기존에 물려있던 씬 해제 씬으로 대입
		m_pReleaseScene = m_pNowScene;

		// 새로운 씬을 현재 씬으로
		m_pNowScene = iter->second;

		// 새로운 씬 초기화
		m_pNowScene->Init();
		m_strNowSceneName = sceneName;
	}
}

// 씬을 변경하는데 로딩씬을 추가하여 변경
void cSceneManager::ChangeSceneWithLoading(
	std::string sceneName,
	std::string loadingSceneName,
	int inEffect, int outEffect)
{
	// 로딩 씬을 찾는다.
	MAP_SCENE::iterator iter = m_LoadingScenes.find(loadingSceneName);

	// 못 찾으면
	if (iter == m_LoadingScenes.end())
		return;

	// 로딩 씬 기억
	cScene* pLoadingScene = iter->second;

	// 변경 될 씬을 찾는다.
	iter = m_Scenes.find(sceneName);

	// 못 찾으면
	if (iter == m_Scenes.end())
		return;

	// 변경 될 씬을 기억
	cScene* pNextScene = iter->second;

	// 나가는 Effect 기억
	m_nOutEffect = outEffect;

	// # 멀티 쓰레드 로딩 시작 #
	// 다른 쓰레드로 다음 씬을 Init 한다.
	DWORD dwThreadID;
	HANDLE hThread;

	// 일꾼 생성
	hThread = CreateThread(
		NULL,			// 쓰레드 속성 일단 NULL
		0,				// 쓰레드의 스택 사이즈 (0으로 하면 MainThread와 같은 1MB가 됨)
		LoadingThread,	// 새롭게 생성되는 쓰레드의 메인 함수 CALLBACK 함수 포인터
		pNextScene,		// 새롭게 생성되는 쓰레드의 메인 함수의 매개 변수 포인터
		0,				// 쓰레드 플래그 (0으로 주면 바로 LoadingThread 가실행)
		&dwThreadID		// 만들어진 쓰레드 ID
	);

	// 더이상 조작 할 필요는 없으니 핸들 날림
	CloseHandle(hThread);

	// 씬 변경 효과 Effect
	cSceneChangeEffect* pChangeEffect = m_pChangeEffects[inEffect];

	// 진입시 효과 전환이 없다면
	if (pChangeEffect == NULL)
	{
		// 이전 씬은 해제 씬으로 등록
		m_pReleaseScene = m_pNowScene;

		// 새로운 씬을 로딩 씬으로
		m_pNowScene = pLoadingScene;
	}
	// 진입 씬 효과가 존재하면
	else
	{
		// 변경 효과 씬 등록
		m_pNowChangeEffect = pChangeEffect;

		// 이전 씬은 효과가 끝나고 자동으로 해제
		pChangeEffect->ChangeStart(
			m_pNowScene,
			pLoadingScene,
			1.0f);
	}
}

void cSceneManager::DrawSceneInfo(void)
{
	char szTemp[128];
	wsprintf(szTemp, "%s", m_strNowSceneName.c_str());
	DXFONT_MGR->PrintTextOutline(szTemp, 0, 60, 0xffffff00, 0xff000000);
}
