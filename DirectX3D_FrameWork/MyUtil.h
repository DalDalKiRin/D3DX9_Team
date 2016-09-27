#pragma once

// # Float �񱳸� �Ҷ� �̰� ������ ������ ���� �ɷ� ������ #
#define FEPSILON 0.00001f

// # float �� ������ ���� #
#define		FLOATEQUAL( a, b )		( abs((a) - (b) ) < FEPSILON )

// # float �� 0�� ������� ���� #
#define		FLOATZERO(a)			( abs((a)) < FEPSILON )

// # ���� ���� ���� #
#define		VECTORZERO(v)			( FLOATZERO((v).x) && FLOATZERO((v).y) && FLOATZERO((v).z) )

// # REnderState ���� ���� ���� ��ũ�� #
#define		RS(a,b)			Device->SetRenderState((a),(b))	

// # �� ���� ����ü (RAY) #
typedef struct tagRay {
	D3DXVECTOR3 origin;		// # ���� ���� ��ġ���� #
	D3DXVECTOR3 direction;	// # ���� ���⺤�� (����ȭ �ؾ���) #
}Ray, *LPRay;

namespace MyUtil
{
	extern DWORD MaxAnisotropic;		// # �̹漺 ���͸� �ִ� �ܰ� #

	extern LPDIRECT3DDEVICE9 Device;	// # ���� Device ( �� ���� �߿� �� ) #

	HRESULT CreateDevice();				// # ����̽� ���� �Լ� #
	void ReleaseDevice();				// # ����̽� ���� �Լ� #

	POINT GetMousePos();				// # ���콺 ��ġ #
	void SetMousePos(int x, int y);		// # ���콺 ��ġ ���� #

	float Clamp(float value, float min, float max);	// # value ���� min �� max ���̷� ���� #
	float Clamp01(float value);						// # value �� 0 ~ 1 ���̷� ���� #
	float ClampMinusOnePlusOne(float value);		// # value �� -1 ~ 1 ���̷� ���� #

	// # float ���� ���� #
	// t �� 0 ~ 1 �� ���̴�.
	// t �� 1�� ����� �� ���� to�� ������� ���� ����
	float Lerp(float from, float to, float t);

	// # float ���� ���� �ݴ� #
	float InverseLerp(float head, float rear, float value);

	// # ���� ���� ���� #
	D3DXVECTOR3 VecLerp(const D3DXVECTOR3& from, const D3DXVECTOR3& to, float t);
	
	// # Random #
	void SetRandomSeed();
	float RandomFloatRange(float min, float max);	// # min ~ max �� ������ float ���� #
	int RandomIntRange(int min, int max);			// # min ~ max �� ������ int   ���� #

	// # ������ �븻�� ������ִ� �Լ� #
	void ComputeNormal
	(
		D3DXVECTOR3* pNormals,			// # ����� ���� �븻���� �迭 ������ (�븻 ������ �迭�� ���� ���� �迭�� ���� ����) #
		const D3DXVECTOR3* pVertices,	// # ��꿡 ���� ���� ��ġ �迭 ������ #
		int verticesNum,				// # ���� ���� #
		const DWORD* pIndices,			// # �ε��� �迭 ������ (�ϴ� �ε����� DWORD �� �뵿�ܰ�) #
		int indicesNum					// # �ε��� �迭 ������ ���� #
	);

	// # ź��Ʈ�� ���̳븻 ��� #
	void ComputeTangentAndBinormal
	(
		D3DXVECTOR3* outTangents,		// # ��� Tangent �迭 #
		D3DXVECTOR3* outBinormals,		// # ��� Binormal �迭 #
		const D3DXVECTOR3* pPositions,	// # ���� ��ġ �迭 #
		const D3DXVECTOR3* pNormals,	// # ���� �븻 �迭 #
		const D3DXVECTOR2* pUVs,		// # ������ UV �迭 #
		const DWORD* pIndices,			// # �ε��� �迭 #
		DWORD NumTris,					// # �ﰢ�� ���� #
		DWORD NumVertices				// # ���� ���� #
	);

	// # float �� ��Ʈ ���� �ս����� ���� ä DWORD ������ ��ȯ #
	DWORD FloatToDWORD(float f);

	// # ����̽��� Targent Color ���� Texture �� ����. #
	void GetDeviceGrabTexture(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9 grabTex);
}