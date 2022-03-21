
#include "carama.h"


carama_info::carama_info()
{
}

carama_info::~carama_info()
{
}

void carama_info::init(int map_width, int map_height, int camara_width, int camara_height, area* center_point_area)
{
	this->_map_area.init(0, 0, map_width, map_height);
	this->_carama_area.init(0, 0, camara_width, camara_height);
	this->_move_area.init(0, 0, map_width - camara_width, map_height - camara_height);

	//this->changeCenterPoint(center_point_area->get_coord_center());
	loadimage(&this->bg, "res/bark/bg.png", this->_map_area.get_width(), this->_map_area.get_height(), true);
}

void carama_info::init(int map_width, int map_height, int camara_width, int camara_height)
{
	this->_map_area.init(0, 0, map_width, map_height);
	this->_carama_area.init(0, 0, camara_width, camara_height);
	this->_move_area.init(0, 0, map_width - camara_width, map_height - camara_height);

	loadimage(&this->bg, "res/bark/bg.png", this->_map_area.get_width(), this->_map_area.get_height(), true);
}

void carama_info::changeCenterPoint(coord* coo)
{
	coord off_coo;
	bool x_final = false,
		 y_final = false;

	while (!x_final || !y_final)
	{
		off_coo = *coo - *this->_carama_area.get_coord_center();
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

// world_area

void world_area::set_carama(carama_info* carama)
{
	this->_carama = carama;
}

coord* world_area::get_coord1()
{
	if (this->_is_ref)
	{
		this->_carama->mapCoord2CaramaCoora(*this->_ref_coo + this->_off_coo, &this->_real_coo1);
	}
	else
	{
		this->_carama->mapCoord2CaramaCoora(this->_coo, &this->_real_coo1);
	}

	return &this->_real_coo1;
}

coord* world_area::get_coord2()
{
	this->_real_coo2 = *this->get_coord1();

	this->_real_coo2.x += this->_w;
	this->_real_coo2.y += this->_h;

	return &this->_real_coo2;
}

coord* world_area::get_coord_center()
{
	this->_real_coo_center = *this->get_coord1();

	this->_real_coo_center.x += this->_w * 0.5;
	this->_real_coo_center.y += this->_h * 0.5;

	return &this->_real_coo_center;
}
