#pragma once

#include "cSingletonBase.h"
#include <string>
#include <map>
#include "cSceneChangeEffect.h"
#include "cScene.h"

class cSceneManager : public cSingletonBase<cSceneManager>
{
private:
	// # 씬 체인지 이펙트 클래스를 프렌드 선언 #
	friend class cSceneChangeEffect;

private:
	typedef std::map<std::string, cScene*>	MAP_SCENE;

private:
	cScene*		m_pNowScene;		// 현재 물려 있는 씬
	std::string	m_strNowSceneName;	// 현재 물려 있는 씬 이름
	cScene*		m_pReleaseScene;	// 날릴 씬

	MAP_SCENE	m_Scenes;			// 현재 가지고 있는 씬들
	MAP_SCENE	m_LoadingScenes;	// 로딩 씬들

	std::vector<cSceneChangeEffect*>	m_pChangeEffects;	// 총 씬 체인지 이펙트들
	cSceneChangeEffect*					m_pNowChangeEffect;	// 현재 변경 이펙트

	int			m_nOutEffect;		// 로딩시 빠져나가는 이펙트 기억

	
public:	// 로딩 정보
	float			fProgress;
	std::string		fString;

public:
	cSceneManager();
	~cSceneManager();

	HRESULT Init();
	void Release();
	void Update(float timeDelta);
	void Render();

	// 게임에 사용되는 씬 추가 씬들은 Init 안됨
	void AddScene(std::string sceneName, cScene* pScene);

	// 게임에 사용되는 로딩 씬 추가 씬들은 모두 Init된 상태가 됨
	void AddLoadingScene(std::string sceneName, cScene* pScene);

	// 씬 변경
	void ChangeScene(
		std::string sceneName,
		int effectNum = 0);

	// 씬을 변경하는데 로딩 씬을 추가하여 변경
	void ChangeSceneWithLoading(
		std::string sceneName,
		std::string loadingSceneName,
		int inEffect,
		int outEffect
	);

	// 현재 씬 정보 출력
	void DrawSceneInfo(void);

	// 로딩 쓰레드 함수 프렌드 선언
	friend DWORD CALLBACK LoadingThread(LPVOID lpParam);
};

#define SCENE_MGR cSceneManager::GetInstance()