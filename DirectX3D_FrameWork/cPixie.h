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

public:		// # �� ���ʹ̿� �Լ� #
	// # ���� �� ��ġ�� ã�´� #
	void FindMovePosition();
	void MovePosition(float timeDelta);
};