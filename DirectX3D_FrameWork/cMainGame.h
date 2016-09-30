#pragma once

class cImage;
class cScene;

class cMainGame
{
private:
	cScene*					m_pNowScene;

	vector<std::string>		m_vecSceneName;
	int						m_nCurrentSceneIndex;

public:
	cMainGame(void);
	~cMainGame(void);

	// # ���� #
	HRESULT Init(void);

	// # ���� #
	void Release(void);

	// # ������Ʈ #
	void Update(void);

	// # ��ο�(����) #
	void Draw(void);

public:

	// ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

public :
	// # ������ #
	void NextControl(void);

};

