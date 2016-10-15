#pragma once

class cBaseObject;
class cCamera;
class cSkinnedAnimation;

enum tagAnimState
{
	IDLE,
	RUN,
	WAIT,
	ATTACK,
	DIE
};

class cEnemy
{
protected:
	// # ���ʹ̰� ������ ��� �� ���� �߰��� ���� #
	// ex) int currentHp;

protected:
	cBaseObject*	pChar;				// # ���� ���� ���̴� ������Ʈ #
	cBaseObject*	pMovePosition;		// # ���� �� �� #
	tagAnimState	eState;				// # ���� #

	D3DXVECTOR3		pTargetPosition;	// # Ÿ���� ��ġ #
	bool			bTargeting;			// # Ÿ���� �ִ��� ���� #
	bool			bNormalMoving;		// # �Ϲ� �������� ���� #
	bool			bTargetMoving;		// # Ÿ�� �������� ���� #

	float			fWeight;			// # ���� #
	float			fMoveSpeed;			// # �ӵ� #

	string			sTagName;			// # �±� �̸� #
	bool			bIsDie;				// # ������ ���� #

protected:
	cBaseObject*	pAggroVolume;		// # ��׷� ���� #
	D3DXVECTOR3		MoveRangeCenter;	// # ������ ������ �߽� #
	float			MoveRangeLength;	// # ������ ������ ���� #


public:
	cEnemy();
	~cEnemy();

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float timeDelta) = 0;
	virtual void Render() = 0;

	virtual void beginSetting() = 0;
	
	virtual void MESH_LOAD() = 0;

	cBaseObject* getCharObject() { return pChar; }

	bool CollisionBox(cBaseObject* targetObj);
	bool CollisionSphere(cBaseObject* targetObj);
	bool CollisionSphere(cBaseObject* targetObj1, cBaseObject* targetObj2);
	void CollisionBlocking(cBaseObject* targetObj, float targetWeight);

	bool GetIsDie()
	{
		return bIsDie;
	}

	void RenderAnimationName()
	{
		pChar->pSkinned->RenderAnimationName();
	}
public:
	// # �β���� #
	virtual void AddTarget(cBaseObject* targetObj) = 0;
};

