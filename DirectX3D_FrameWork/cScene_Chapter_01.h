#pragma once
#include "cScene.h"

class cScene_Chapter_01 : public cScene
{
public:
	cScene_Chapter_01();
	~cScene_Chapter_01();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

