
#include "beforeEvent.h"

void beforeEvent(global* g)
{
	g->rb->graviry_check();
	g->rb->rigidbody_check();
	g->carama->changeCenterPoint(g->pi->player_area.get_coord_center_in_world());
}
