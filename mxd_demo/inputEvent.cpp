
#include "inputEvent.h"
#include "global.h"
#include <stdio.h>
#include "tools.h"

#define KEY_DOWN(VK) ((GetAsyncKeyState(VK)& 0x8000 ? 1:0))
#define KEY_DOWN_FOREGROUND(vk) (KEY_DOWN(vk) && GetForegroundWindow() == GetHWnd()) //Ç°¾°´°¿ÚÅÐ¶Ï

using namespace global;

static unsigned long long lastKeyEvent = 0;
static unsigned long long curKeyEvent = 0;

static unsigned long long lastLetterKeyEvent = 0;
static unsigned long long curLetterKeyEvent = 0;

DWORD WINAPI create_th(LPVOID);

void GetCommand();
void DispatchCommand();
void InputLetterStartDown(unsigned long long cmd);
void InputStartDown(unsigned long long cmd);
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

	lastLetterKeyEvent = curLetterKeyEvent;
	curLetterKeyEvent = 0;
	
	if (KEY_DOWN_FOREGROUND(VK_UP))			curKeyEvent |= CMD_UP;
	if (KEY_DOWN_FOREGROUND(VK_DOWN))		curKeyEvent |= CMD_DOWN;
	if (KEY_DOWN_FOREGROUND(VK_LEFT))		curKeyEvent |= CMD_LEFT;
	if (KEY_DOWN_FOREGROUND(VK_RIGHT))		curKeyEvent |= CMD_RIGHT;
	if (KEY_DOWN_FOREGROUND(VK_LMENU))		curKeyEvent |= CMD_JUMP;
	if (KEY_DOWN_FOREGROUND(VK_LCONTROL))	curKeyEvent |= CMD_ATTACK;
	if (KEY_DOWN_FOREGROUND(VK_LSHIFT))		curKeyEvent |= CMD_LSHI;
	if (KEY_DOWN_FOREGROUND(VK_RSHIFT))		curKeyEvent |= CMD_RSHI;
	if (KEY_DOWN_FOREGROUND(VK_SPACE))		curKeyEvent |= CMD_SPACE;
	if (KEY_DOWN_FOREGROUND(VK_BACK))		curKeyEvent |= CMD_BACK;
	if (KEY_DOWN_FOREGROUND(VK_ESCAPE))		curKeyEvent |= CMD_ESC;
	if (KEY_DOWN_FOREGROUND(VK_RETURN))		curKeyEvent |= CMD_ENTER;

	/*
	 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
	 * 0x3A - 0x40 : unassigned
	 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	 */
	for (int i = 0; i < 26; ++i)
	{
		if (KEY_DOWN_FOREGROUND(0x41 + i))			curLetterKeyEvent |= (CMD_A << i);
	}

	for (int i = 0; i < 10; ++i)
	{
		if (KEY_DOWN_FOREGROUND(0x30 + i))			curKeyEvent |= (CMD_0 << i);
	}
}

void DispatchCommand()
{
	if (GetFocusInput() != NULL)
	{
		InputLetterStartDown(~lastLetterKeyEvent & curLetterKeyEvent);
		InputStartDown(~lastKeyEvent & curKeyEvent);
	}
	else
	{
		ButtonStartDown(~lastKeyEvent & curKeyEvent);
		ButtonStayDown(lastKeyEvent & curKeyEvent);
		ButtonEndDown(lastKeyEvent & ~curKeyEvent);
	}
}

void InputLetterStartDown(unsigned long long cmd)
{
	for (int i = 0; i < 26; ++i)
	{
		if (cmd & (CMD_A << i))
		{
			GetFocusInput()->txt.append(1, 'a' + i);
		}
	}
}

void InputStartDown(unsigned long long cmd)
{
	if (cmd & CMD_ESC)
	{
		ChangeFocusInput(NULL);
	}
	if (cmd & CMD_ENTER)
	{
		ChangeFocusInput(NULL);
	}
	
	if (cmd & CMD_BACK)
	{
		if (!GetFocusInput()->txt.empty())
			GetFocusInput()->txt.erase(GetFocusInput()->txt.end() - 1);
	}
	if (cmd & CMD_SPACE)
	{
		GetFocusInput()->txt.append(" ");
	}

	for (int i = 0; i < 10; ++i)
	{
		if (cmd & (CMD_0 << i))
		{
			GetFocusInput()->txt.append(1, '0' + i);
		}
	}
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
