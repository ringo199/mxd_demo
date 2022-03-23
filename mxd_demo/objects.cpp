
#include "objects.h"
#include "tools.h"

object::object(carama_info* carama)
{
	this->_carama = carama;
}

object::~object()
{
}

render_object::render_object(carama_info* carama)
{
	this->_render_area.set_carama(carama);
	this->_render_base_point = NULL;
}

render_object::~render_object()
{
}

world_area* render_object::get_render_area()
{
	return &this->_render_area;
}

void block::render()
{
	drawBloodBar(this->get_render_area()->get_coord1()->x, this->get_render_area()->get_coord1()->y, this->get_render_area()->get_width(), this->get_render_area()->get_height(),
		0, RED, RED, RED, 1.0);
}
