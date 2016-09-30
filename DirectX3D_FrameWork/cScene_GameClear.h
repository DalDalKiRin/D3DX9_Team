#pragma once
#include "cScene.h"

class cScene_GameClear : public cScene
{
public:
	cScene_GameClear();
	~cScene_GameClear();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

