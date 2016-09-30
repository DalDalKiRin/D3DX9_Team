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

	// # 셋팅 #
	HRESULT Init(void);

	// # 해제 #
	void Release(void);

	// # 업데이트 #
	void Update(void);

	// # 드로우(렌더) #
	void Draw(void);

public:

	// 프로시저
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

public :
	// # 디버깅용 #
	void NextControl(void);

};

