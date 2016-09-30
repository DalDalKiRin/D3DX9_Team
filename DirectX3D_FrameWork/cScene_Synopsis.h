#pragma once
#include "cScene.h"

class cScene_Synopsis : public cScene
{
public:
	cScene_Synopsis();
	~cScene_Synopsis();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

