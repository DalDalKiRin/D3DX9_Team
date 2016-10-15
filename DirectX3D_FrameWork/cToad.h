#pragma once
#include "cEnemy.h"

class cToad : public cEnemy
{
private:
	// # 사신과 플레이어 오브젝트를 받아옴 #
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

public:		// # 각 에너미용 함수 #
	// # 벡터에 타겟 넣음 #
	virtual void AddTarget(cBaseObject* targetObj);
	// # 타겟 찾아냄 #
	void FindTarget(float timeDelta);
	// # 타겟을 당김 #
	void TargetPulling(cBaseObject* targetObj, float timeDelta);
};