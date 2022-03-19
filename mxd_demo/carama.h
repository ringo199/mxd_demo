#pragma once

#ifndef __CARAMA_H__
#define __CARAMA_H__

#include <stdio.h>
#include <graphics.h>
#include "var.h"

// 1. map width, height
// 2. carama width, height, x, y

class carama_info
{
public:
	carama_info();
	~carama_info();

	area _map_area;		// 地图总大小
	area _carama_area;	// 视野大小
	area _move_area;	// 可以移动的视野大小，从左上角到右下角的全部面积

	// tmp
	IMAGE bg;

	void init(int map_width, int map_height, int camara_width, int camara_height, area* center_point_area);
	void init(int map_width, int map_height, int camara_width, int camara_height);

	void changeCenterPoint(coord* coo);

	//void mapCoord2CaramaCoora(int x, int y, int* ox, int* oy, bool* isVisible);
	void mapCoord2CaramaCoora(int x, int y, int* ox, int* oy);
	void mapCoord2CaramaCoora(coord incoo, coord* outcoo);
};


class world_area : public area
{
public:
	void set_carama(carama_info* carama);

	coord* get_coord1();
	coord* get_coord2();
	coord* get_coord_center();
private:
	carama_info* _carama;
};


#endif
