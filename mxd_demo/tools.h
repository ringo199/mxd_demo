#ifndef __TOOL_H__
#define __TOOL_H__

#pragma once
#include <graphics.h>
#include "carama.h"


unsigned long long getTickCount();
//返回距离上一次调用间隔的时间（单位：ms)，第一次调用时返回0
int getDelay();

void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture, bool is_reverse, double sa_percent);

// 适用于 y <0 以及y>0的任何情况
void putimagePNG2(int x, int y, IMAGE* picture);
void putimagePNG2(int x, int y, IMAGE* picture, bool is_reverse, double sa_percent);
void putimagePNG2(coord* coo, IMAGE* picture, bool is_reverse, double sa_percent);
void putimagePNG2(int x, int y, int winWidth, IMAGE* picture);
void putimagePNG2(int x, int y, int winWidth, IMAGE* picture, bool is_reverse, double sa_percent);
void putimagePNG2(coord* coo, int winWidth, IMAGE* picture, bool is_reverse, double sa_percent);

// 判断两个矩形是否相交
bool rectIntersect(int a1X, int a1Y, int a2X, int a2Y,
    int b1X, int b1Y, int b2X, int b2Y);
bool rectIntersect(area* a1, area* a2);
bool rectIntersect(world_area* a1, world_area* a2);

void  preLoadSound(const char* name);
void  playSound(const char* name);

void testDrawBar(area* a);
void drawBloodBar(area* a, int lineWidth, int boardColor, int emptyColor, int fillColor, float percent);
void drawBloodBar(int x, int y, int width, int height, int lineWidth, int boardColor, int emptyColor, int fillColor, float percent);

#endif