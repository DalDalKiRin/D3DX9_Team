#pragma once
#include "cScene.h"

class cScene_Intro : public cScene
{
public:
	cScene_Intro();
	~cScene_Intro();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

