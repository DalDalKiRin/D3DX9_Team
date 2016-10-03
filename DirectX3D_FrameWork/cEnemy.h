#pragma once
#include "cScene.h"

class cBaseObject;
class cCamera;
class cSkinnedAnimation;

class cEnemy
{
protected:
	// # ���ʹ̰� ������ ��� �� ���� �߰��� ���� #
	// ex) int currentHp;

protected:
	cBaseObject*	pChar;

public:
	cEnemy();
	~cEnemy();

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float timeDelta) = 0;
	virtual void Render() = 0;
	
	virtual void MESH_LOAD() = 0;

	cBaseObject* getCharObject() { return pChar; }
};

