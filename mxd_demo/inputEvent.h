#pragma once
#ifndef __INPUT_EVENT_H__
#define __INPUT_EVENT_H__

#include <stdio.h>
#include "tools.h"
#include "global.h"
#include "event_manager.h"

#define	CMD_UP			0x1
#define	CMD_DOWN		0x2
#define	CMD_LEFT		0x4
#define	CMD_RIGHT		0x8
#define	CMD_ATTACK		0x10
#define	CMD_JUMP		0x20
#define	CMD_LSHI		0x40
#define	CMD_RSHI		0x80
#define	CMD_SPACE		0x100
#define	CMD_BACK		0x200

void keyEvent(global*);
DWORD WINAPI create_th(LPVOID);
int  GetCommand();								// 获取控制命令
void DispatchCommand(int _cmd, global*);		// 分发控制命令

#endif
