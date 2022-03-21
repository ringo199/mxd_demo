
#include "beforeEvent.h"

void beforeEvent(global* g)
{
	g->rb->graviry_check();
	g->rb->graviry_force();
	g->rb->rigidbody_check();
	g->carama->changeCenterPoint(g->pi->get_render_area()->get_coord_center_in_world());
}
