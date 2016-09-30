#pragma once
#include "cScene.h"

class cScene_Title : public cScene
{
public:
	cScene_Title();
	~cScene_Title();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

