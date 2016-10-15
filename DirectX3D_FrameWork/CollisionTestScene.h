#pragma once
#include "cScene.h"

class cPixie;

class CollisionTestScene : public cScene
{
private:
	cPixie* pPixie;

public:
	CollisionTestScene();
	~CollisionTestScene();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

	virtual void Scene_Render_AfterPostEffect(LPDIRECT3DTEXTURE9 pScreen);


	void CollisionSphere();
	void CollisionBox();
	void CollisionUnMoveBlocking();
	void CollisionMoveBlocking();
	void CollisionRaySphere();
	void CollisionRayBox();

	void MoveTest(float timeDelta);
};

