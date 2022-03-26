
#include "objects.h"
#include "tools.h"

#include "global.h"

using namespace global;

object::object()
{
	this->_base_point = this;
}

object::~object()
{
}

render_object::render_object()
{
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

void transpoint::render()
{
	drawBloodBar(this->get_render_area()->get_coord1()->x, this->get_render_area()->get_coord1()->y, this->get_render_area()->get_width(), this->get_render_area()->get_height(),
		0, WHITE, WHITE, WHITE, 1.0);
}

void transpoint_object::trans()
{
	GetEventManager()->eventEmit(GAME_GOTO_SCENE, this->_game_scene);
}

void NPC::render()
{
	drawBloodBar(this->get_render_area()->get_coord1()->x, this->get_render_area()->get_coord1()->y, this->get_render_area()->get_width(), this->get_render_area()->get_height(),
		0, BLUE, BLUE, BLUE, 1.0);
}
