
#include "carama.h"
#include "tools.h"


carama_info::carama_info()
{
}

carama_info::~carama_info()
{
}

void carama_info::init(int map_width, int map_height, int camara_width, int camara_height)
{
	this->_map_area.init(0, 0, map_width, map_height);
	this->_carama_area.init(0, 0, camara_width, camara_height);
	this->_move_area.init(0, 0, map_width - camara_width, map_height - camara_height);
}

void carama_info::setCenterPoint(coord* coo)
{
	this->_carama_center_point = coo;
}

void carama_info::changeCenterPoint()
{
	if (_carama_center_point == nullptr) return;
	coord off_coo;
	bool x_final = false,
		 y_final = false;

	while (!x_final || !y_final)
	{
		off_coo = *this->_carama_center_point - *this->_carama_area.get_coord_center();
		if (!x_final)
		{
			if (off_coo.x > 0)
			{
				if (this->_carama_area.get_coord1()->x >= this->_move_area.get_coord2()->x)
				{
					x_final = true;
				}
				else
				{
					this->_carama_area.changeOffX(1);
				}
			}
			else if (off_coo.x < 0)
			{
				if (this->_carama_area.get_coord1()->x <= this->_move_area.get_coord1()->x)
				{
					x_final = true;
				}
				else
				{
					this->_carama_area.changeOffX(-1);
				}
			}
			else
			{
				x_final = true;
			}
		}

		if (!y_final)
		{
			if (off_coo.y > 0)
			{
				if (this->_carama_area.get_coord1()->y >= this->_move_area.get_coord2()->y)
				{
					y_final = true;
				}
				else
				{
					this->_carama_area.changeOffY(1);
				}
			}
			else if (off_coo.y < 0)
			{
				if (this->_carama_area.get_coord1()->y <= this->_move_area.get_coord1()->y)
				{
					y_final = true;
				}
				else
				{
					this->_carama_area.changeOffY(-1);
				}
			}
			else
			{
				y_final = true;
			}
		}
	}
}

bool carama_info::isVisible(area* a)
{
	return rectIntersect(a, &this->_carama_area);
}

//void carama_info::mapCoord2CaramaCoora(int x, int y, int* ox, int* oy, bool* isVisible)
//{
//	*isVisible = !(
//		x < this->cx ||
//		y < this->cy ||
//		x > this->cx + this->carama_width ||
//		y > this->cy + this->carama_height);
//
//	this->mapCoord2CaramaCoora(x, y, ox, oy);
//}

void carama_info::mapCoord2CaramaCoora(int x, int y, int* ox, int* oy)
{
	if (this == nullptr)
	{
		return;
	}
	*ox = x - this->_carama_area.get_coord1()->x;
	*oy = y - this->_carama_area.get_coord1()->y;
}

void carama_info::mapCoord2CaramaCoora(coord incoo, coord* outcoo)
{
	if (this == nullptr)
	{
		return;
	}
	*outcoo = incoo - *this->_carama_area.get_coord1();
}
