#pragma once
#include "cScene.h"

class cScene_GameOver : public cScene
{
public:
	cScene_GameOver();
	~cScene_GameOver();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

