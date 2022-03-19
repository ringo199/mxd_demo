
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

	return c;
}

// 分发控制命令
void DispatchCommand(int _cmd, global* g)
{
	//if (_cmd & CMD_UP)		g->pi->updown(-1);
	//if (_cmd & CMD_DOWN)		g->pi->updown(1);
	if (_cmd & CMD_LEFT)		g->pi->run(-1);
	if (_cmd & CMD_RIGHT)		g->pi->run(1);
	if (_cmd & CMD_JUMP)		g->pi->jump();
	if (_cmd & CMD_ATTACK)		g->pi->attack();
	if (_cmd == 0)				g->pi->cancelRuning();
}
