#pragma once
#include "cScene.h"

class cScene_Boss : public cScene
{
public:
	cScene_Boss();
	~cScene_Boss();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

