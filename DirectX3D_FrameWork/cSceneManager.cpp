#include "stdafx.h"
#include "cSceneManager.h"
#include "cSceneChangeEffectUpDown.h"

// LPVOID �� void*�� ������
// void* �����ʹ� ��� �ּҸ� �� ���� �� ������ ���� �ּҸ� ����ȯ�Ͽ� ���
DWORD CALLBACK LoadingThread(LPVOID lpParam)
{
	// �Ű� ������ ���� �� ����ȯ
	cScene* pScene = (cScene*)lpParam;

	// �ε� ���� �ʱ�ȭ
	SCENE_MGR->fProgress = 0.0f;
	SCENE_MGR->fString = "";

	// �Ű� ������ ���� �� �ʱ�ȭ
	pScene->Init();

	// ������� �Դٸ� pScene�� �ʱ�ȭ�� ���� ����
	// SCENE_MGR->m_pNowScene = pScene;

	// �ʱ�ȭ�� �� ��ȯ ȿ������ ���� �̷���� �� �ִ�.
	// �̶� ȿ���� �������� �� ��ü���� ����
	// ����� ȿ���� �������� �� ���� ��ü�ϰ� �Ǹ�
	// �� ȿ���� ������ �ε� ���� �ҷ����� ��Ȳ�̸�
	// �ε� ���� ȣ��ȴ�.

	while (true)
	{
		// ��ü Effect �� ������.
		if (SCENE_MGR->m_pNowChangeEffect == NULL)
		{
			// �� ������ ���� ���� ������ �ʿ�� ���� (���� ���� �ε�����)
			//SCENE_MGR->m_pReleaseScene = SCENE_MGR->m_pNowScene;

			// ���� ������ ȿ��
			cSceneChangeEffect* pChangeEffect = SCENE_MGR->m_pChangeEffects[SCENE_MGR->m_nOutEffect];

			// ���� ������ ȿ���� �������� �ʴ´ٸ�
			if (pChangeEffect == NULL)
				SCENE_MGR->m_pNowScene = pScene;
			// ���� ������ ȿ���� �����ϸ�
			else
			{
				// ���� ȿ�� �� ���
				SCENE_MGR->m_pNowChangeEffect = pChangeEffect;

				// ���� ���� ȿ���� ������ �ڵ����� ���� ��
				// (�̶� ���� ���� �ε� ���̱� ������ ������ ��ϵȴٰ� �ϴ��� �������� ����)
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
	// �� ��ȯ ȿ�� �߰�
	m_pChangeEffects.push_back(NULL);		// 0���� ȿ�� ���� ���� NULL �߰�

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
	// �÷� �ִ� ���� �ִٸ�.
	if (this->m_pNowScene != NULL)
	{
		this->m_pNowScene->Release();
	}

	// ��ȯ ȿ�� �ϴ� ������. (0���� NULL�̴� 1������)
	for (int i = 1; i < this->m_pChangeEffects.size(); i++)
	{
		m_pChangeEffects[i]->Release();
		SAFE_DELETE(m_pChangeEffects[i]);
	}
}

void cSceneManager::Update(float timeDelta)
{
	// ���� ���� �ִٸ�
	if (m_pReleaseScene)
	{
		bool sceneIsLoading = false;
		MAP_SCENE::iterator iter;

		for (iter = this->m_LoadingScenes.begin(); iter != m_LoadingScenes.end(); ++iter)
		{
			// ���� ���� �ε� ���̶�� ������ �ȵȴ�.
			if (iter->second == m_pReleaseScene)
			{
				sceneIsLoading = true;
				break;
			}
		}

		// ���� ���� ������ ���� �ε� ���� �ƴ϶�� �Ƚ��ϰ� ������
		if (sceneIsLoading == false)
		{
			m_pReleaseScene->Release();
		}
		m_pReleaseScene = NULL;
	}

	// ���� ȿ���� �ִٸ�
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
	// ���� ȿ���� �ִٸ�

	// ��ο� �غ� ���� �ʾҴٸ� ü���� Effect �� �׸��� �ȵ�
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

// ���ӿ� ���Ǵ� �� �߰� ������ �ʱ�ȭ�� �ȵ�
void cSceneManager::AddScene(std::string sceneName, cScene* pScene)
{
	MAP_SCENE::iterator iter = m_Scenes.find(sceneName);

	// �ߺ� ����
	if (iter == m_Scenes.end())
	{
		m_Scenes.insert(std::make_pair(sceneName, pScene));
	}
}

// ���ӿ� ���Ǵ� �ε� �� �߰� ������ ��� �ʱ�ȭ�� ���°� �ȴ�.
void cSceneManager::AddLoadingScene(std::string sceneName, cScene* pScene)
{
	MAP_SCENE::iterator iter = m_LoadingScenes.find(sceneName);

	// �ߺ� ����
	if (iter == m_LoadingScenes.end())
	{
		// Init�� �ϰ� ����.
		pScene->Init();
		m_LoadingScenes.insert(std::make_pair(sceneName, pScene));
	}
}

// �� ����
void cSceneManager::ChangeScene(std::string sceneName, int effectNum)
{
	// ��ü Effect
	cSceneChangeEffect* pChangeEffect = this->m_pChangeEffects[effectNum];

	// ���� ã�´�.
	MAP_SCENE::iterator iter = m_Scenes.find(sceneName);

	// �� ã����
	if (iter == m_Scenes.end())
		return;

	// -------- # �߰� ���� ó�� # -----------

	// ���� ���� ü���� ���� ������ �ȹٲ�
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

	// ������ �����ִ� ���� �ְ� ü���� ȿ���� �ִٸ�
	if (m_pNowScene && pChangeEffect != NULL)
	{
		m_pNowChangeEffect = pChangeEffect;

		// �ι� ° ���� Init �� ���·� ����.
		iter->second->Init();
		m_strNowSceneName = sceneName;

		// ü���� ȿ�� �ߵ�
		m_pNowChangeEffect->ChangeStart(
			m_pNowScene,
			iter->second,
			1.0f			// ȿ�� ü���� �ð�
		);
	}
	// �װ� �ƴ϶��
	else
	{
		// ������ �����ִ� �� ���� ������ ����
		m_pReleaseScene = m_pNowScene;

		// ���ο� ���� ���� ������
		m_pNowScene = iter->second;

		// ���ο� �� �ʱ�ȭ
		m_pNowScene->Init();
		m_strNowSceneName = sceneName;
	}
}

// ���� �����ϴµ� �ε����� �߰��Ͽ� ����
void cSceneManager::ChangeSceneWithLoading(
	std::string sceneName,
	std::string loadingSceneName,
	int inEffect, int outEffect)
{
	// �ε� ���� ã�´�.
	MAP_SCENE::iterator iter = m_LoadingScenes.find(loadingSceneName);

	// �� ã����
	if (iter == m_LoadingScenes.end())
		return;

	// �ε� �� ���
	cScene* pLoadingScene = iter->second;

	// ���� �� ���� ã�´�.
	iter = m_Scenes.find(sceneName);

	// �� ã����
	if (iter == m_Scenes.end())
		return;

	// ���� �� ���� ���
	cScene* pNextScene = iter->second;

	// ������ Effect ���
	m_nOutEffect = outEffect;

	// # ��Ƽ ������ �ε� ���� #
	// �ٸ� ������� ���� ���� Init �Ѵ�.
	DWORD dwThreadID;
	HANDLE hThread;

	// �ϲ� ����
	hThread = CreateThread(
		NULL,			// ������ �Ӽ� �ϴ� NULL
		0,				// �������� ���� ������ (0���� �ϸ� MainThread�� ���� 1MB�� ��)
		LoadingThread,	// ���Ӱ� �����Ǵ� �������� ���� �Լ� CALLBACK �Լ� ������
		pNextScene,		// ���Ӱ� �����Ǵ� �������� ���� �Լ��� �Ű� ���� ������
		0,				// ������ �÷��� (0���� �ָ� �ٷ� LoadingThread ������)
		&dwThreadID		// ������� ������ ID
	);

	// ���̻� ���� �� �ʿ�� ������ �ڵ� ����
	CloseHandle(hThread);

	// �� ���� ȿ�� Effect
	cSceneChangeEffect* pChangeEffect = m_pChangeEffects[inEffect];

	// ���Խ� ȿ�� ��ȯ�� ���ٸ�
	if (pChangeEffect == NULL)
	{
		// ���� ���� ���� ������ ���
		m_pReleaseScene = m_pNowScene;

		// ���ο� ���� �ε� ������
		m_pNowScene = pLoadingScene;
	}
	// ���� �� ȿ���� �����ϸ�
	else
	{
		// ���� ȿ�� �� ���
		m_pNowChangeEffect = pChangeEffect;

		// ���� ���� ȿ���� ������ �ڵ����� ����
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
