
#include "inputEvent.h"

void keyEvent(global* g)
{
	HANDLE hThread = CreateThread(NULL, 0, create_th, (LPVOID)g, 0, NULL);

	CloseHandle(hThread);
}

DWORD WINAPI create_th(LPVOID args)
{
	global* g = (global*)args;

	for (;;)
	{
		DispatchCommand(GetCommand(), g);
	}
}

// 获取控制命令
int GetCommand()
{
	int c = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)			c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)		c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)			c |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)			c |= CMD_DOWN;
	if (GetAsyncKeyState(VK_LMENU) & 0x8000)		c |= CMD_JUMP;
	if (GetAsyncKeyState(VK_LCONTROL) & 0x8000)		c |= CMD_ATTACK;
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)		c |= CMD_LSHI;
	if (GetAsyncKeyState(VK_RSHIFT) & 0x8000)		c |= CMD_RSHI;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)		c |= CMD_SPACE;
	if (GetAsyncKeyState(VK_BACK) & 0x8000)			c |= CMD_BACK;
	
	return c;
}

// 分发控制命令
void DispatchCommand(int _cmd, global* g)
{
	if (_cmd & CMD_LSHI)
	{
		static int count1 = 10000;
		count1++;
		if (count1 < 10000)
		{
			return;
		}
		count1 = 0;
		g->eventManager->eventEmit(UI_BACK);
	}
	if (_cmd & CMD_RSHI)
	{
		static int count2 = 10000;
		count2++;
		if (count2 < 10000)
		{
			return;
		}
		count2 = 0;
		g->eventManager->eventEmit(UI_NEXT);
	};
	if (_cmd & CMD_UP)			g->eventManager->eventEmit(GAME_CMD_UP);
	if (_cmd & CMD_DOWN)		g->eventManager->eventEmit(GAME_CMD_DOWN);
	if (_cmd & CMD_LEFT)		g->eventManager->eventEmit(GAME_CMD_LEFT);
	if (_cmd & CMD_RIGHT)		g->eventManager->eventEmit(GAME_CMD_RIGHT);
	if (_cmd & CMD_JUMP)		g->eventManager->eventEmit(GAME_CMD_JUMP);
	if (_cmd & CMD_ATTACK)		g->eventManager->eventEmit(GAME_CMD_ATTACK);
	if (_cmd & CMD_SPACE)		g->eventManager->eventEmit(GAME_GOTO_SCENE, GAME_2);
	if (_cmd & CMD_BACK)		g->eventManager->eventEmit(GAME_GOTO_SCENE, GAME_1);

	//if (_cmd == 0)				g->gm->_player->cancelRuning();
}
