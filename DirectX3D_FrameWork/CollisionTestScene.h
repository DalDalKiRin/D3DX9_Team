#pragma once
#include "cScene.h"

class cPigNose;


class CollisionTestScene : public cScene
{
private:
	cPigNose* pPigNose;
	cPigNose* pPigNose2;

public:
	CollisionTestScene();
	~CollisionTestScene();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

	virtual void Scene_Render_AfterPostEffect(LPDIRECT3DTEXTURE9 pScreen);

};

