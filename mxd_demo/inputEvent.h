#pragma once
#ifndef __INPUT_EVENT_H__
#define __INPUT_EVENT_H__

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
#define	CMD_ESC			0x400
#define	CMD_ENTER		0x800
#define CMD_0			0x1000

#define	CMD_A			0x1

void keyEvent();

#endif
