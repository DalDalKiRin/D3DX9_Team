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
	// # 에너미가 실전에 사용 될 변수 추가될 공간 #
	// ex) int currentHp;

protected:
	cBaseObject*	pChar;				// # 실제 눈에 보이는 오브젝트 #
	cBaseObject*	pMovePosition;		// # 가야 할 곳 #
	tagAnimState	eState;				// # 상태 #

	D3DXVECTOR3		pTargetPosition;	// # 타겟의 위치 #
	bool			bTargeting;			// # 타겟이 있는지 여부 #
	bool			bNormalMoving;		// # 일반 무빙인지 여부 #
	bool			bTargetMoving;		// # 타겟 무빙인지 여부 #

	float			fWeight;			// # 무게 #
	float			fMoveSpeed;			// # 속도 #

	string			sTagName;			// # 태그 이름 #
	bool			bIsDie;				// # 죽은지 여부 #

protected:
	cBaseObject*	pAggroVolume;		// # 어그로 볼륨 #
	D3DXVECTOR3		MoveRangeCenter;	// # 움직일 범위의 중심 #
	float			MoveRangeLength;	// # 움직일 범위의 길이 #


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
	// # 두꺼비용 #
	virtual void AddTarget(cBaseObject* targetObj) = 0;
};

