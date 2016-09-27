#pragma once
#include "cScene.h"

class cBaseObject;
class cCamera;
class cTerrain;
class cSkinnedAnimation;
class cQuad;

#define OBJECT_NUM 30

class cTrailRender;


class cScene_01 : public cScene
{
private:
	std::vector<cBaseObject*>			renderObjects;			//씬에 배치된 랜더 오브젝트 배열
	std::vector<cBaseObject*>			cullObjects;			//컬링된 오브젝트
	std::vector<cLight*>				lights;					//라이팅..

	cTerrain*		m_pTerrain;
	cTerrain*		m_pTerrainShadow;

	cQuad*			pQuad;
	cTransform*		pQuadTrans;

//	cTrailRender*	pTrailRender;

public:
	cScene_01(void);
	~cScene_01(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

	virtual void Scene_Render_AfterPostEffect(LPDIRECT3DTEXTURE9 pScreen);


};

