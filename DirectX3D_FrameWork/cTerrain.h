#pragma once

class cQuadTree;
class cCamera;
class cLight_Direction;

class cTerrain
{
public:

	// Terrain ���� ����ü
	typedef struct tagTERRAINVERTEX
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 normal;
		D3DXVECTOR3 binormal;
		D3DXVECTOR3 tangent;
		D3DXVECTOR2 baseUV;		// 0 ~ 1  UV
		D3DXVECTOR2 tileUV;		// Ÿ��	  UV
	}TERRAINVERTEX, *LPTERRAINVERTEX;

	// Terrain �ε��� ����ü (�� ����ü �ϳ��� �ﰢ�� �ϳ� ���)
	typedef struct tagTERRAINTRI {
		DWORD dw0;
		DWORD dw1;
		DWORD dw2;
	}TERRAINTRI, *LPTERRAINTRI;

private:
	LPDIRECT3DVERTEXBUFFER9			m_pTerrainVB;
	LPDIRECT3DINDEXBUFFER9			m_pTerrainIB;
	LPDIRECT3DVERTEXDECLARATION9	m_pTerrainDecl;

	float		m_fHeightScale;		// ���� ������
	float		m_fCellScale;		// �� �ϳ��� ũ��

	int			m_nVerNumX;			// ���� ���� ��
	int			m_nVerNumZ;			// ���� ���� ��
	int			m_nTotalVerNum;		// �� ���� ��

	int			m_nCellNumX;		// ���� �� ��
	int			m_nCellNumZ;		// ���� �� ��
	int			m_nTotalCellNum;	// �� �� ��
	int			m_nTotalTri;		// �ﰢ�� ����

	float		m_fTerrainSizeZ;	// �ͷ��� ���� ������
	float		m_fTerrainSizeX;	// �ͷ��� ���� ������

	// # ��Ȯ�� ���� ����� ���� �ʿ��ϴ� #
	float		m_fTerrainStartX;	// �ͷ��� ���� ��ġ X
	float		m_fTerrainStartZ;	// �ͷ��� ���� ��ġ Z
	float		m_fTerrainEndX;		// �ͷ���   �� ��ġ X
	float		m_fTerrainEndZ;		// �ͷ���   �� ��ġ Z

	LPTERRAINVERTEX		m_pTerrainVertices;	// �ͷ��� ���� ����
	LPDIRECT3DTEXTURE9	m_pHeightMap;		// �ͷ��� ���� ��

	cQuadTree*			m_pQuadTree;		// ���� Ʈ��

	LPDIRECT3DTEXTURE9	m_pTexTile_0;		// �ͷ��� 0 �� Ÿ��
	LPDIRECT3DTEXTURE9	m_pTexTile_1;		// �ͷ��� 1 �� Ÿ��
	LPDIRECT3DTEXTURE9	m_pTexTile_2;		// �ͷ��� 2 �� Ÿ��
	LPDIRECT3DTEXTURE9	m_pTexTile_3;		// �ͷ��� 3 �� Ÿ��
	LPDIRECT3DTEXTURE9	m_pTexSlat;			// ���÷��� �ؽ���

public:
	LPD3DXEFFECT		m_pTerrainEffect;	// �ͷ��� ����Ʈ

public:
	cTerrain();
	~cTerrain();

	// �ʱ�ȭ
	HRESULT Init(
		const char* szHeightMapName,	// ���� �� �̸�
		const char* szTile_0,			// Ÿ�� �̹��� 0
		const char* szTile_1,			// Ÿ�� �̹��� 1
		const char* szTile_2,			// Ÿ�� �̹��� 2
		const char* szTile_3,			// Ÿ�� �̹��� 3
		const char* szTileSplat,		// Ÿ�� �̹��� ��Ʈ��
		float cellSize,					// �ϳ��� �� ũ��
		float heightScale,				// ���� ������
		int smoothLevel,				// ������ ó�� Ƚ��
		int tileNum);					// Ÿ�ϸ� ����

	// ����
	void Release();

	// ����
	void Render(cCamera* pCam, cLight_Direction* pDirectionLight);
	void Render(cCamera* pCam, cLight_Direction* pDirectionLight, cCamera* pDirectionLightCamera);
	void RenderShadow(cCamera* pDirectionLightCam);

	// Ray ��Ʈ ��ġ�� ��´�.
	bool IsIntersectRay(D3DXVECTOR3* pOut, const LPRay pRay);

	// �ش� X, Z ��ġ�� ������ ���̸� ��´�.
	float GetHeight(float x, float z);

	// �ش� X, Z ��ġ�� ��� ���͸� ��´�.
	bool GetSlant(D3DXVECTOR3* pOut, float gravityPower, float x, float z);

private:
	// �ͷ��� �����
	HRESULT CreateTerrain(int smooth, int tileNum);

	// �ͷ��� ������
	void SmoothTerrain(int passed);
};

