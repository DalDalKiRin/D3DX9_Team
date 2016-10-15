#pragma once
#include "cScene.h"

class cEnemy;
class cGhost;
class cToad;
class cSnake;
class cPixie;
class cAlice2;

class cGhostAndToadTestScene : public cScene
{
private:
	cEnemy* pGhost;
	cEnemy* pToad;
	cEnemy* pSnake;
	cEnemy* pPixie;
	cEnemy* pAlice2;

public:
	cGhostAndToadTestScene();
	~cGhostAndToadTestScene();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

	virtual void Scene_Render_AfterPostEffect(LPDIRECT3DTEXTURE9 pScreen);

	void testAnimation();
};

