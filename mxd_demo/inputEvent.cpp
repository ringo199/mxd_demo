
#include "inputEvent.h"

void keyEvent()
{
	HANDLE hThread = CreateThread(NULL, 0, create_th, NULL, 0, NULL);

	CloseHandle(hThread);
}

DWORD WINAPI create_th(LPVOID args)
{
	for (;;)
	{
		DispatchCommand(GetCommand());
	}
}

// ��ȡ��������
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

// �ַ���������
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
		GetEventManager()->eventEmit(UI_BACK);
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
		GetEventManager()->eventEmit(UI_NEXT);
	};

	if (_cmd & CMD_UP)			GetEventManager()->eventEmit(GAME_CMD_UP);
	if (_cmd & CMD_DOWN)		GetEventManager()->eventEmit(GAME_CMD_DOWN);
	if (_cmd & CMD_LEFT)		GetEventManager()->eventEmit(GAME_CMD_LEFT);
	if (_cmd & CMD_RIGHT)		GetEventManager()->eventEmit(GAME_CMD_RIGHT);
	if (_cmd & CMD_JUMP)		GetEventManager()->eventEmit(GAME_CMD_JUMP);
	if (_cmd & CMD_ATTACK)		GetEventManager()->eventEmit(GAME_CMD_ATTACK);
	if (_cmd & CMD_SPACE)		GetEventManager()->eventEmit(GAME_GOTO_SCENE, GAME_2);
	if (_cmd & CMD_BACK)		GetEventManager()->eventEmit(GAME_GOTO_SCENE, GAME_1);

	//if (_cmd == 0)				g->gm->_player->cancelRuning();
}
