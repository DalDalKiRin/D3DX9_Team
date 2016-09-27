// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <string>

// # �ʿ��� ��� #
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// # ��ũ�� ��� #
#define WINSIZE_X	1280				// # �ʱ� ������ ���� ũ�� #
#define WINSIZE_Y	800					// # �ʱ� ������ ���� ũ�� #
#define WINPOS_X	0					// # �ʱ� ������ ���� ��ġ X #
#define WINPOS_Y	0					// # �ʱ� ������ ���� ��ġ Y #
#define WIN_CLASS	"Elin Of Madness"	// # ������ Ŭ���� �̸� #
#define WIN_TITLE	"Elin Of Madness"	// # ������ Ÿ��Ʋ �̸� #
#define WIN_STYLE	WS_CAPTION | WS_SYSMENU | WS_BORDER	// # ������ ���� #

#define ONE_RAD		0.017453f			// # 1 ������ �� #

// # ��ũ�� �Լ� #
#define SAFE_DELETE(p)		{ if(p){ delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARR(p)	{ if(p){ delete[] (p); (p) = NULL; } }
#define SAFE_RELEASE(p)		{ if(p){ (p)->Release(); (p) = NULL; } }

// # ���� ���� #
extern HWND			g_hWnd;		// # ������ �ڵ� ( �ڽ��� ���α׷����� �����ִ� ������ ��ȣ ) #
extern HINSTANCE	g_hInst;	// # ���α׷� �ν��Ͻ� �ڵ� ( OS �� �ο��� ���α׷� ��ȣ ) #

#include <vector>
#include <map>

// # �Ŵ��� #
#include "MyUtil.h"

using namespace MyUtil;
using namespace std;

// # ��Ÿ ���(�Ŵ�����) #
#include "cTimeMgr.h"
#include "cKeyMgr.h"
#include "cLogMgr.h"
#include "cDXFontManager.h"
#include "cGizmoManager.h"
#include "cPhysicManager.h"
#include "cSpriteManager.h"
#include "cSceneManager.h"
#include "cResourceMgr_Texture.h"
#include "cResourceMgr_ShaderFX.h"
#include "cResourceMgr_XStaticMesh.h"
#include "cResourceMgr_XSkinnedMesh.h"