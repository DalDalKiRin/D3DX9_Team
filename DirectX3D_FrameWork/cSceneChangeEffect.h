#pragma once

#include "cScene.h"

class cSceneChangeEffect
{
private:
	float m_TimeFactor;			// # ��ü �ð� ���� ���� (�߿�) #

	LPDIRECT3DTEXTURE9 m_pPrevRenderTexture;		// ������ �� ����Ʈ ���� �ؽ���
	LPDIRECT3DTEXTURE9 m_pNextRenderTexture;		// ������ �� ����Ʈ ���� �ؽ���

	float		m_TotalTime;	// ��ü �ð�
	float		m_DeltaTime;	// ��ü ���� �ð�

	float		m_StartTime;	// ��ü�� ���۵� �ð�
	
	cScene*		m_pPrevScene;	// ���� ��
	cScene*		m_pNextScene;	// ���� ��

	bool		m_DrawReady;	// ��ü �� ��ο� ����

public:
	cSceneChangeEffect();
	~cSceneChangeEffect();

	void Init();
	void Release();

	//						���� ��				���� ��			��ü �ð�
	void ChangeStart(cScene* pPrevScene, cScene* pNextScene, float changeTime);

	void Update(float timeDelta);
	void Render();

	//						���� �ؽ���			���� �ؽ���							��ü ����
	virtual void ChangeEffect(LPDIRECT3DTEXTURE9 pPrev, LPDIRECT3DTEXTURE9 pNext, float factor);

	bool IsDrawReady()
	{
		return m_DrawReady;
	}
};

