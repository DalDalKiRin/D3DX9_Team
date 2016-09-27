#pragma once

#include "cScene.h"

class cSceneChangeEffect
{
private:
	float m_TimeFactor;			// # 교체 시간 진행 비율 (중요) #

	LPDIRECT3DTEXTURE9 m_pPrevRenderTexture;		// 렌더링 될 이펙트 이전 텍스쳐
	LPDIRECT3DTEXTURE9 m_pNextRenderTexture;		// 렌더링 될 이펙트 다음 텍스쳐

	float		m_TotalTime;	// 교체 시간
	float		m_DeltaTime;	// 교체 진행 시간

	float		m_StartTime;	// 교체가 시작된 시간
	
	cScene*		m_pPrevScene;	// 이전 씬
	cScene*		m_pNextScene;	// 다음 씬

	bool		m_DrawReady;	// 교체 씬 드로우 여부

public:
	cSceneChangeEffect();
	~cSceneChangeEffect();

	void Init();
	void Release();

	//						이전 씬				다음 씬			교체 시간
	void ChangeStart(cScene* pPrevScene, cScene* pNextScene, float changeTime);

	void Update(float timeDelta);
	void Render();

	//						이전 텍스쳐			다음 텍스쳐							교체 비율
	virtual void ChangeEffect(LPDIRECT3DTEXTURE9 pPrev, LPDIRECT3DTEXTURE9 pNext, float factor);

	bool IsDrawReady()
	{
		return m_DrawReady;
	}
};

