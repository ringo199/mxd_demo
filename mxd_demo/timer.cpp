
#include "timer.h"
#include "global.h"
#include <unordered_map>
#include "tools.h"

using namespace global;
using namespace std;

struct timerMap
{
	int id;
	int timervalms;
	function<void(void)> fn;
	bool isStop;
};

unordered_map<int, timerMap> tm;
int id = 0;

DWORD WINAPI create_timer_th(LPVOID);

timer::timer()
{
}

timer::~timer()
{
}

int timer::setInterval(function<void(void)> fn, int timervalms)
{
	int timerid = id++;
	tm[timerid] = { timerid, timervalms, fn, false };
	HANDLE hThread = CreateThread(NULL, 0, create_timer_th, (LPVOID*) &tm[timerid], 0, NULL);

	CloseHandle(hThread);
	return timerid;
}

void timer::clearInterval(int timerid)
{
	tm[timerid].isStop = true;
}

DWORD WINAPI create_timer_th(LPVOID args)
{
	timerMap* t = (timerMap*)args;

	unsigned long long currentTime = getTickCount();
	unsigned long long lastTime = currentTime;
	unsigned long long cnt = 0;
	while (!t->isStop)
	{
		cnt += currentTime - lastTime;
		lastTime = currentTime;
		currentTime = getTickCount();
		if (cnt >= t->timervalms)
		{
			t->fn();
			cnt = 0;
		}
	}
	tm.erase(t->id);
	return 0;
}
