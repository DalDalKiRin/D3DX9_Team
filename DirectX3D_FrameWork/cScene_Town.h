#pragma once
#include "cScene.h"

class cScene_Town : public cScene
{
public:
	cScene_Town();
	~cScene_Town();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

