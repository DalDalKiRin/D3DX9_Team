#pragma once

// # Float 비교를 할때 이값 이하의 오차는 같은 걸로 따진다 #
#define FEPSILON 0.00001f

// # float 값 같은지 여부 #
#define		FLOATEQUAL( a, b )		( abs((a) - (b) ) < FEPSILON )

// # float 값 0에 가까운지 여부 #
#define		FLOATZERO(a)			( abs((a)) < FEPSILON )

// # 제로 벡터 여부 #
#define		VECTORZERO(v)			( FLOATZERO((v).x) && FLOATZERO((v).y) && FLOATZERO((v).z) )

// # REnderState 쉽게 쓰기 위한 매크로 #
#define		RS(a,b)			Device->SetRenderState((a),(b))	

// # 반 직선 구조체 (RAY) #
typedef struct tagRay {
	D3DXVECTOR3 origin;		// # 직선 시작 위치벡터 #
	D3DXVECTOR3 direction;	// # 직선 방향벡터 (정규화 해야함) #
}Ray, *LPRay;

namespace MyUtil
{
	extern DWORD MaxAnisotropic;		// # 이방성 필터링 최대 단계 #

	extern LPDIRECT3DDEVICE9 Device;	// # 전역 Device ( ★ 가장 중요 ★ ) #

	HRESULT CreateDevice();				// # 디바이스 생성 함수 #
	void ReleaseDevice();				// # 디바이스 해제 함수 #

	POINT GetMousePos();				// # 마우스 위치 #
	void SetMousePos(int x, int y);		// # 마우스 위치 셋팅 #

	float Clamp(float value, float min, float max);	// # value 값을 min 과 max 사이로 맞춤 #
	float Clamp01(float value);						// # value 값 0 ~ 1 사이로 맞춤 #
	float ClampMinusOnePlusOne(float value);		// # value 값 -1 ~ 1 사이로 맞춤 #

	// # float 선형 보간 #
	// t 는 0 ~ 1 의 값이다.
	// t 가 1에 가까워 질 수록 to에 가까워진 값이 리턴
	float Lerp(float from, float to, float t);

	// # float 선형 보간 반대 #
	float InverseLerp(float head, float rear, float value);

	// # 벡터 선형 보간 #
	D3DXVECTOR3 VecLerp(const D3DXVECTOR3& from, const D3DXVECTOR3& to, float t);
	
	// # Random #
	void SetRandomSeed();
	float RandomFloatRange(float min, float max);	// # min ~ max 값 사이의 float 리턴 #
	int RandomIntRange(int min, int max);			// # min ~ max 값 사이의 int   리턴 #

	// # 정점의 노말을 계산해주는 함수 #
	void ComputeNormal
	(
		D3DXVECTOR3* pNormals,			// # 결과로 받을 노말벡터 배열 포인터 (노말 벡터의 배열의 수는 정점 배열의 수와 같다) #
		const D3DXVECTOR3* pVertices,	// # 계산에 사용된 정점 위치 배열 포인터 #
		int verticesNum,				// # 정점 갯수 #
		const DWORD* pIndices,			// # 인덱스 배열 포인터 (일단 인덱스는 DWORD 로 대동단결) #
		int indicesNum					// # 인덱스 배열 포인터 갯수 #
	);

	// # 탄젠트와 바이노말 계산 #
	void ComputeTangentAndBinormal
	(
		D3DXVECTOR3* outTangents,		// # 결과 Tangent 배열 #
		D3DXVECTOR3* outBinormals,		// # 결과 Binormal 배열 #
		const D3DXVECTOR3* pPositions,	// # 정점 위치 배열 #
		const D3DXVECTOR3* pNormals,	// # 정점 노말 배열 #
		const D3DXVECTOR2* pUVs,		// # 정점의 UV 배열 #
		const DWORD* pIndices,			// # 인덱스 배열 #
		DWORD NumTris,					// # 삼각형 갯수 #
		DWORD NumVertices				// # 정점 갯수 #
	);

	// # float 의 비트 값을 손실하지 않은 채 DWORD 형으로 변환 #
	DWORD FloatToDWORD(float f);

	// # 디바이스의 Targent Color 값을 Texture 에 쓴다. #
	void GetDeviceGrabTexture(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9 grabTex);
}