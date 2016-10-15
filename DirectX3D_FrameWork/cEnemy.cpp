#include "stdafx.h"
#include "cEnemy.h"


cEnemy::cEnemy()
	: eState(IDLE)
	, pTargetPosition(0.0f, 0.0f, 0.0f)
	, bTargeting(false)
	, fWeight(0.0f)
	, fMoveSpeed(0.0f)
	, MoveRangeCenter(0.0f, 0.0f, 0.0f)
	, MoveRangeLength(0.0f)
	, bNormalMoving(false)
	, bTargetMoving(false)
	, pChar(NULL)
	, pMovePosition(NULL)
	, pAggroVolume(NULL)
	, sTagName("")
	, bIsDie(false)
{
}

cEnemy::~cEnemy()
{
}

bool cEnemy::CollisionBox(cBaseObject * targetObj)
{
	return PHYSICS_MGR->IsOverlap(
		targetObj->pTransform,
		&targetObj->BoundBox,
		pChar->pTransform,
		&pChar->BoundBox
	);
}

bool cEnemy::CollisionSphere(cBaseObject * targetObj)
{
	return PHYSICS_MGR->IsOverlap(
		targetObj->pTransform,
		&(cBoundSphere)targetObj->BoundBox,
		pChar->pTransform,
		&(cBoundSphere)pChar->BoundBox
	);
}

bool cEnemy::CollisionSphere(cBaseObject * targetObj1, cBaseObject * targetObj2)
{
	return PHYSICS_MGR->IsOverlap(
		targetObj2->pTransform,
		&(cBoundSphere)targetObj2->BoundBox,
		targetObj1->pTransform,
		&(cBoundSphere)targetObj1->BoundBox
	);
}

void cEnemy::CollisionBlocking(cBaseObject * targetObj, float targetWeight)
{
	float power;
	if (targetWeight >= fWeight)
		power = 1.0f;
	else
	{
		float fullWeight = fWeight + targetWeight;
		fullWeight = (targetWeight / fullWeight);
		power = fullWeight;
	}

	PHYSICS_MGR->IsBlocking(targetObj->pTransform,
		&targetObj->BoundBox,
		pChar->pTransform,
		&pChar->BoundBox, power);
}

void cEnemy::AddTarget(cBaseObject * targetObj)
{
}
