#pragma once
#include "cEnemy.h"

class cPixie : public cEnemy
{
private:

public:
	cPixie();
	~cPixie();

	virtual void Init();
	virtual void Release();
	virtual void Update(float timeDelta);
	virtual void Render();

	virtual void beginSetting();

	virtual void MESH_LOAD();

	virtual void AddTarget(cBaseObject* targetObj);

public:		// # 각 에너미용 함수 #
	// # 가야 할 위치를 찾는다 #
	void FindMovePosition();
	void MovePosition(float timeDelta);
};