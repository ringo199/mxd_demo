
#include "inputEvent.h"
#include "global.h"
#include <stdio.h>
#include "tools.h"

using namespace global;

static unsigned long long lastKeyEvent = 0;
static unsigned long long curKeyEvent = 0;

DWORD WINAPI create_th(LPVOID);

void GetCommand();
void DispatchCommand();
void ButtonStartDown(unsigned long long cmd);
void ButtonStayDown(unsigned long long cmd);
void ButtonEndDown(unsigned long long cmd);

void keyEvent()
{
	HANDLE hThread = CreateThread(NULL, 0, create_th, NULL, 0, NULL);

	CloseHandle(hThread);
}

DWORD WINAPI create_th(LPVOID args)
{
	for (;;)
	{
		GetCommand();
		DispatchCommand();
	}
}

void GetCommand()
{
	lastKeyEvent = curKeyEvent;
	curKeyEvent = 0;

	if (GetAsyncKeyState(VK_UP) & 0x8000)			curKeyEvent |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)			curKeyEvent |= CMD_DOWN;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)			curKeyEvent |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)		curKeyEvent |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_LMENU) & 0x8000)		curKeyEvent |= CMD_JUMP;
	if (GetAsyncKeyState(VK_LCONTROL) & 0x8000)		curKeyEvent |= CMD_ATTACK;
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)		curKeyEvent |= CMD_LSHI;
	if (GetAsyncKeyState(VK_RSHIFT) & 0x8000)		curKeyEvent |= CMD_RSHI;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)		curKeyEvent |= CMD_SPACE;
	if (GetAsyncKeyState(VK_BACK) & 0x8000)			curKeyEvent |= CMD_BACK;
}

void DispatchCommand()
{
	ButtonStartDown(~lastKeyEvent & curKeyEvent);
	ButtonStayDown(lastKeyEvent & curKeyEvent);
	ButtonEndDown(lastKeyEvent & ~curKeyEvent);
}

void ButtonStartDown(unsigned long long cmd)
{
	if (cmd & CMD_LSHI)		GetEventManager()->eventEmit(UI_BACK);
	if (cmd & CMD_RSHI)		GetEventManager()->eventEmit(UI_NEXT);

	if (cmd & CMD_UP)		GetEventManager()->eventEmit(GAME_CMD_UP);
	if (cmd & CMD_DOWN)		GetEventManager()->eventEmit(GAME_CMD_DOWN);
	if (cmd & CMD_LEFT)		GetEventManager()->eventEmit(GAME_CMD_LEFT);
	if (cmd & CMD_RIGHT)	GetEventManager()->eventEmit(GAME_CMD_RIGHT);
	if (cmd & CMD_JUMP)		GetEventManager()->eventEmit(GAME_CMD_JUMP);
	if (cmd & CMD_ATTACK)	GetEventManager()->eventEmit(GAME_CMD_ATTACK);
}

void ButtonStayDown(unsigned long long cmd)
{
	if (cmd & CMD_LEFT)		GetEventManager()->eventEmit(GAME_CMD_LEFT);
	if (cmd & CMD_RIGHT)	GetEventManager()->eventEmit(GAME_CMD_RIGHT);
	if (cmd & CMD_JUMP)		GetEventManager()->eventEmit(GAME_CMD_JUMP);
	if (cmd & CMD_ATTACK)	GetEventManager()->eventEmit(GAME_CMD_ATTACK);
}

void ButtonEndDown(unsigned long long cmd)
{
	if (cmd & CMD_LEFT)		GetEventManager()->eventEmit(GAME_CMD_STAY);
	if (cmd & CMD_RIGHT)	GetEventManager()->eventEmit(GAME_CMD_STAY);
}
