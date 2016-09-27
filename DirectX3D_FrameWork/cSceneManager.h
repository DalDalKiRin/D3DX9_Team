#pragma once

#include "cSingletonBase.h"
#include <string>
#include <map>
#include "cSceneChangeEffect.h"
#include "cScene.h"

class cSceneManager : public cSingletonBase<cSceneManager>
{
private:
	// # �� ü���� ����Ʈ Ŭ������ ������ ���� #
	friend class cSceneChangeEffect;

private:
	typedef std::map<std::string, cScene*>	MAP_SCENE;

private:
	cScene*		m_pNowScene;		// ���� ���� �ִ� ��
	cScene*		m_pReleaseScene;	// ���� ��

	MAP_SCENE	m_Scenes;			// ���� ������ �ִ� ����
	MAP_SCENE	m_LoadingScenes;	// �ε� ����

	std::vector<cSceneChangeEffect*>	m_pChangeEffects;	// �� �� ü���� ����Ʈ��
	cSceneChangeEffect*					m_pNowChangeEffect;	// ���� ���� ����Ʈ

	int			m_nOutEffect;		// �ε��� ���������� ����Ʈ ���

	
public:	// �ε� ����
	float			fProgress;
	std::string		fString;

public:
	cSceneManager();
	~cSceneManager();

	HRESULT Init();
	void Release();
	void Update(float timeDelta);
	void Render();

	// ���ӿ� ���Ǵ� �� �߰� ������ Init �ȵ�
	void AddScene(std::string sceneName, cScene* pScene);

	// ���ӿ� ���Ǵ� �ε� �� �߰� ������ ��� Init�� ���°� ��
	void AddLoadingScene(std::string sceneName, cScene* pScene);

	// �� ����
	void ChangeScene(
		std::string sceneName,
		int effectNum = 0);

	// ���� �����ϴµ� �ε� ���� �߰��Ͽ� ����
	void ChangeSceneWithLoading(
		std::string sceneName,
		std::string loadingSceneName,
		int inEffect,
		int outEffect
	);

	// �ε� ������ �Լ� ������ ����
	friend DWORD CALLBACK LoadingThread(LPVOID lpParam);
};

#define SCENE_MGR cSceneManager::GetInstance()