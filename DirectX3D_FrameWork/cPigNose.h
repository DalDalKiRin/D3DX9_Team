#pragma once
#include "cEnemy.h"

class cPigNose : public cEnemy
{
	bool find;

public:
	cPigNose();
	~cPigNose();

	virtual void Init();
	virtual void Release();
	virtual void Update(float timeDelta);
	virtual void Render();

	virtual void beginSetting();

	virtual void MESH_LOAD();
	void findPlayer();
};

