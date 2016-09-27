#include "stdafx.h"
#include "cSceneChangeEffect.h"

cSceneChangeEffect::cSceneChangeEffect()
	: m_pPrevScene(NULL)
	, m_pNextScene(NULL)
	, m_pNextRenderTexture(NULL)
	, m_pPrevRenderTexture(NULL)
{
}

cSceneChangeEffect::~cSceneChangeEffect()
{
}

void cSceneChangeEffect::Init()
{
	/*
	// 빈 Texture 만들기
	Device->CreateTexture(
		WINSIZE_X,				// Texture 가로 해상도
		WINSIZE_Y,				// Texture 세로 해상도
		1,						// 밉맵 체인 레벨
		D3DUSAGE_RENDERTARGET,	// RenderTarget용 Texture
		D3DFMT_A8R8G8B8,		// Texture 포맷 RenderTexture용은 D3DFMT_A8R8G8B8로 함
		D3DPOOL_DEFAULT,		// RenderTarget용 Texture는 Pool 을 Default
		&m_pPrevRenderTexture,	// 생성된 Texture 받아올 포인터
		NULL
	);

	// 빈 Texture 만들기
	Device->CreateTexture(
		WINSIZE_X,				// Texture 가로 해상도
		WINSIZE_Y,				// Texture 세로 해상도
		1,						// 밉맵 체인 레벨
		D3DUSAGE_RENDERTARGET,	// RenderTarget용 Texture
		D3DFMT_A8R8G8B8,		// Texture 포맷 RenderTexture용은 D3DFMT_A8R8G8B8로 함
		D3DPOOL_DEFAULT,		// RenderTarget용 Texture는 Pool 을 Default
		&m_pPrevRenderTexture,	// 생성된 Texture 받아올 포인터
		NULL
	);
	*/
}

void cSceneChangeEffect::Release()
{
	/*
	SAFE_RELEASE(m_pPrevRenderTexture);
	SAFE_RELEASE(m_pNextRenderTexture);
	*/
}

void cSceneChangeEffect::ChangeStart(cScene* pPrevScene, cScene* pNextScene, float changeTime)
{
	// 교체 효과에 사용 될 이전 씬과 다음 씬을 기억
	m_pPrevScene = pPrevScene;
	m_pNextScene = pNextScene;

	// 시간 초기화
	m_TotalTime = changeTime;
	m_DeltaTime = 0.0f;
	m_TimeFactor = 0.0f;

	// 시작 시간 기억
	m_StartTime = (float)(TIME_MGR->GetNowRealTimeSec());

	// 교체 씬 드로우 여부 false로 시작
	m_DrawReady = false;
}

void cSceneChangeEffect::Update(float timeDelta)
{
	if (m_DrawReady == false)
	{
		// 이전 씬 화면 렌더
		this->m_pPrevScene->Update(timeDelta);
		this->m_pPrevScene->RenderToMainCamTexture();

		this->m_pNextScene->Update(timeDelta);
		this->m_pNextScene->RenderToMainCamTexture();

		// 렌더 명령이 먹었기 때문에 씬의 화면 Texture를 얻어 올 수 있다.
		this->m_pPrevRenderTexture = this->m_pPrevScene->GetTexture();
		this->m_pNextRenderTexture = this->m_pNextScene->GetTexture();

		/*
		// 참고 복사

		// 원본 Texture
		LPDIRECT3DTEXTURE9 pSrcTex = m_pPrevScene->GetTexture();

		// 복사할 위치 Texture (빈 Texture라도 만들어져 있어야 한다)
		LPDIRECT3DTEXTURE9 pDstTex = m_pPrevRenderTexture;

		// pSrcTex 의 Surface를 얻는다.
		LPDIRECT3DSURFACE9 srcSurface = NULL;
		pSrcTex->GetSurfaceLevel(0, &srcSurface);

		// pDstTex 의 Surface를 얻는다.
		LPDIRECT3DSURFACE9 destSurface = NULL;
		pDstTex->GetSurfaceLevel(0, &destSurface);

		// 고속 복사
		Device->StretchRect(
			srcSurface,		// 원본 Surface
			NULL,			// 원본 Surface의 영역 (NULL이면 전체)
			destSurface,	// 소스 Surface
			NULL,			// 소스 Surface의 영역 (NULL이면 전체)
			D3DTEXF_LINEAR	// 필터링
		);

		srcSurface->Release();
		pDstTex->Release();
		*/

		m_DrawReady = true;
	}

	// 현재 시간
	float nowTime = (float)(TIME_MGR->GetNowRealTimeSec());
	m_DeltaTime = nowTime - m_StartTime;

	// Factor 계산
	m_TimeFactor = m_DeltaTime / m_TotalTime;
	if (m_TimeFactor > 1.0f)
		m_TimeFactor = 1.0f;

	// 교체 시간이 다 되었다면
	if (m_DeltaTime > m_TotalTime)
	{
		SCENE_MGR->GetInstance()->m_pNowScene = m_pNextScene;

		// 이전 씬은 해제 씬으로
		SCENE_MGR->GetInstance()->m_pReleaseScene = m_pPrevScene;

		// 씬 매니저의 교체 Effect은 없다.
		SCENE_MGR->GetInstance()->m_pNowChangeEffect = NULL;

		m_DrawReady = false;
	}
}

void cSceneChangeEffect::Render()
{
	// 드로우 레디가 되어 있지 않으면 안그림
	if (m_DrawReady)
	{
		this->ChangeEffect(m_pPrevRenderTexture, m_pNextRenderTexture, m_TimeFactor);
	}
}

void cSceneChangeEffect::ChangeEffect(LPDIRECT3DTEXTURE9 pPrev, LPDIRECT3DTEXTURE9 pNext, float factor)
{
	SPRITE_MGR->BeginSpriteRender();

	RECT rcSour = { 0, 0, WINSIZE_X, WINSIZE_Y };
	SPRITE_MGR->DrawTexture(pPrev, &rcSour, 0, 0, D3DXCOLOR(1, 1, 1, 1.0f - factor));
	SPRITE_MGR->DrawTexture(pNext, &rcSour, 0, 0, D3DXCOLOR(1, 1, 1, factor));

	SPRITE_MGR->EndSpriteRender();
}