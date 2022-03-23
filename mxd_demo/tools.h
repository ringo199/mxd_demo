#ifndef __TOOL_H__
#define __TOOL_H__

#pragma once
#include <graphics.h>
#include "carama.h"


unsigned long long getTickCount();
//���ؾ�����һ�ε��ü����ʱ�䣨��λ��ms)����һ�ε���ʱ����0
int getDelay();

void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture, bool is_reverse, double sa_percent);

// ������ y <0 �Լ�y>0���κ����
void putimagePNG2(int x, int y, IMAGE* picture);
void putimagePNG2(int x, int y, IMAGE* picture, bool is_reverse, double sa_percent);
void putimagePNG2(coord* coo, IMAGE* picture, bool is_reverse, double sa_percent);
void putimagePNG2(int x, int y, int winWidth, IMAGE* picture);
void putimagePNG2(int x, int y, int winWidth, IMAGE* picture, bool is_reverse, double sa_percent);
void putimagePNG2(coord* coo, int winWidth, IMAGE* picture, bool is_reverse, double sa_percent);

// �ж����������Ƿ��ཻ
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