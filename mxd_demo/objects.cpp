
#include "objects.h"

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
}

render_object::~render_object()
{
}

world_area* render_object::get_render_area()
{
	return &this->_render_area;
}
