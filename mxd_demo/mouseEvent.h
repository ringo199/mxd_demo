#pragma once

#ifndef __MOUSE_EVENT_H__
#define __MOUSE_EVENT_H__

#include "var.h"

#define	MOUSE_LEFT_DOWN		0x1
#define	MOUSE_RIGHT_DOWN	0x2
#define	MOUSE_MID_DOWN		0x4 // Êó±ê¹öÂÖ

void mouseEvent();

void GetMouseCommand();
void DispatchMouseCommand();
void MouseStartDown(unsigned long long cmd);
void MouseStayDown(unsigned long long cmd);
void MouseEndDown(unsigned long long cmd);

coord* GetCurMouseEventCoord();
coord* GetLastMouseEventCoord();

#endif
