
#include "mouseEvent.h"

#include "global.h"
#include <stdio.h>
#include "tools.h"

#define KEY_DOWN(VK) ((GetAsyncKeyState(VK)& 0x8000 ? 1:0))
#define KEY_DOWN_FOREGROUND(vk) (KEY_DOWN(vk) && GetForegroundWindow() == GetHWnd()) //前景窗口判断

using namespace global;

static unsigned long long clickLeftTimer = 0;
static coord lastLeftClickCoord; // 用来做双击
static coord curLeftClickCoord;

static unsigned long long clickRightTimer = 0;
static coord lastRightClickCoord; // 用来做双击
static coord curRightClickCoord;

static unsigned long long clickMidTimer = 0;
static coord lastMidClickCoord; // 用来做双击
static coord curMidClickCoord;

static unsigned long long lastMouseEvent = 0;
static unsigned long long curMouseEvent = 0;

POINT pt;

DWORD WINAPI create_mouse_th(LPVOID);

void mouseEvent()
{
	HANDLE hThread = CreateThread(NULL, 0, create_mouse_th, NULL, 0, NULL);

	CloseHandle(hThread);
}

DWORD WINAPI create_mouse_th(LPVOID args)
{
	for (;;)
	{
		GetMouseCommand();
		DispatchMouseCommand();
	}
}

void GetMouseCommand()
{
	lastMouseEvent = curMouseEvent;
	curMouseEvent = 0;
	GetCursorPos(&pt);
	ScreenToClient(GetForegroundWindow(), &pt);

	if (KEY_DOWN_FOREGROUND(VK_LBUTTON))	curMouseEvent |= MOUSE_LEFT_DOWN;
	if (KEY_DOWN_FOREGROUND(VK_RBUTTON))	curMouseEvent |= MOUSE_RIGHT_DOWN;
	if (KEY_DOWN_FOREGROUND(VK_MBUTTON))	curMouseEvent |= MOUSE_MID_DOWN;
}

void DispatchMouseCommand()
{
	MouseStartDown(~lastMouseEvent & curMouseEvent);
	//MouseStayDown(lastMouseEvent & curMouseEvent);
	MouseEndDown(lastMouseEvent & ~curMouseEvent);
}

void MouseStartDown(unsigned long long cmd)
{
	if (cmd & MOUSE_LEFT_DOWN)
	{
		curLeftClickCoord.x = pt.x;
		curLeftClickCoord.y = pt.y;
	}

	if (cmd & MOUSE_RIGHT_DOWN)
	{
		curRightClickCoord.x = pt.x;
		curRightClickCoord.y = pt.y;
	}

	if (cmd & MOUSE_MID_DOWN)
	{
		curMidClickCoord.x = pt.x;
		curMidClickCoord.y = pt.y;
	}
}

void MouseStayDown(unsigned long long cmd)
{
	if (cmd & MOUSE_LEFT_DOWN)	{}
	if (cmd & MOUSE_RIGHT_DOWN) {}
	if (cmd & MOUSE_MID_DOWN)	{}
}

void MouseEndDown(unsigned long long cmd)
{
	if (cmd & MOUSE_LEFT_DOWN)
	{
		GetUIObjectManager()->checkClickEvent(&curLeftClickCoord);
		GetObjectManager()->checkClickEvent(&curLeftClickCoord);
		lastLeftClickCoord = curLeftClickCoord;
		curLeftClickCoord = coord(0, 0);
		clickLeftTimer = getTickCount();
	}

	if (cmd & MOUSE_RIGHT_DOWN)
	{
		lastRightClickCoord = curRightClickCoord;
		curRightClickCoord = coord(0, 0);
		clickRightTimer = getTickCount();
	}

	if (cmd & MOUSE_MID_DOWN)
	{
		lastMidClickCoord = curMidClickCoord;
		curMidClickCoord = coord(0, 0);
		clickMidTimer = getTickCount();
	}
}
