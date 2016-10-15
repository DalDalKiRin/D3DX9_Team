#pragma once
#include "cEnemy.h"

class cToad : public cEnemy
{
private:
	// # ��Ű� �÷��̾� ������Ʈ�� �޾ƿ� #
	vector<cBaseObject*> vFoodOfToad;

public:
	cToad();
	~cToad();

	virtual void Init();
	virtual void Release();
	virtual void Update(float timeDelta);
	virtual void Render();

	virtual void beginSetting();

	virtual void MESH_LOAD();

public:		// # �� ���ʹ̿� �Լ� #
	// # ���Ϳ� Ÿ�� ���� #
	virtual void AddTarget(cBaseObject* targetObj);
	// # Ÿ�� ã�Ƴ� #
	void FindTarget(float timeDelta);
	// # Ÿ���� ��� #
	void TargetPulling(cBaseObject* targetObj, float timeDelta);
};