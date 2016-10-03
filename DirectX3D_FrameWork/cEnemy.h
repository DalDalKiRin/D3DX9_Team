#pragma once
#include "cScene.h"

class cBaseObject;
class cCamera;
class cSkinnedAnimation;

class cEnemy
{
protected:
	// # 에너미가 실전에 사용 될 변수 추가될 공간 #
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

