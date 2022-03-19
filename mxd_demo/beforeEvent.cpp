
#include "beforeEvent.h"

void beforeEvent(global* g)
{
	g->rb->rigidbody_move();
	g->carama->changeCenterPoint(g->pi->player_area.get_coord_center_in_world());
}
