#pragma once
#include "cEnemy.h"

class cVampirLady : public cEnemy
{
private:


public:
	cVampirLady();
	~cVampirLady();

	virtual void Init();
	virtual void Release();
	virtual void Update(float timeDelta);
	virtual void Render();

	virtual void beginSetting();

	virtual void MESH_LOAD();

public:	// # �� ���ʹ̿� �Լ� #
	virtual void AddTarget(cBaseObject* targetObj);	// ��� X
};

