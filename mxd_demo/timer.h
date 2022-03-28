#pragma once
#ifndef __TIMER_H__
#define __TIMER_H__

#include <iostream>
#include <functional>

using namespace std;

class timer
{
public:
	timer();
	~timer();

	int setInterval(function<void(void)>, int);
	void clearInterval(int);
};

#endif // !__TIMER_H__
