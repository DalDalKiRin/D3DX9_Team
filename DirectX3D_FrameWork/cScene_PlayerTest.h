#pragma once
#include "cScene.h"

class cBaseObject;
class cCamera;
class cSkinnedAnimation;

class cScene_PlayerTest : public cScene
{
private:
	std::vector<cBaseObject*>	renderObjects;
	std::vector<cLight*>		lights;

	cTransform* m_pTrans;

public:
	cScene_PlayerTest();
	~cScene_PlayerTest();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	void control(float timeDelta);
};

