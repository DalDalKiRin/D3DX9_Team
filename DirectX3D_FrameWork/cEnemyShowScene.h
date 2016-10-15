#pragma once
#include "cScene.h"

class cTrailRender;

class cEnemy;
class cAlice;
class cAlice2;
class cGhost;
class cPixie;
class cPumpkin;
class cRunMonster;
class cSnake;
class cToad;
class cVampirGentleman;
class cVampirLady;
class cZombie;
class cZombie2;

// # - ���� ���� - #
// ���ӿ� �ִ� ���ʹ̵���
// �Ѹ����� �ڼ��� �ľ��ϱ� ���� ��

#define MAX_ENEMY_NUM 12

class cEnemyShowScene : public cScene
{
private:
	int Count;
	int CurrentAnimationNum;
	int MaxAnimationNum;

	// # Enemys #
	vector<cEnemy*> vEnemys;
	// # ------ #

	// # Trail Render #
	cTrailRender* pTrail;
	// # ------------ #
public:
	cEnemyShowScene();
	~cEnemyShowScene();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

	virtual void Scene_Render_AfterPostEffect(LPDIRECT3DTEXTURE9 pScreen);

	void SceneControl();
	void LoadEnemy();
	void SelectEnemyRender();
};

