#pragma once
#include "cScene.h"

class cScene_Loading : public cScene
{
public:
	cScene_Loading();
	~cScene_Loading();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

