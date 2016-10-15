#pragma once
#include "cEnemy.h"

class cGhost : public cEnemy
{
private:

public:
	cGhost();
	~cGhost();

	virtual void Init();
	virtual void Release();
	virtual void Update(float timeDelta);
	virtual void Render();

	virtual void beginSetting();

	virtual void MESH_LOAD();
	
	virtual void AddTarget(cBaseObject* targetObj);

public:		// # 각 에너미용 함수 #


};