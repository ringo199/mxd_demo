
#include "afterEvent.h"

void afterEvent(global* g)
{
	g->pi->animator();
	g->ene->animator();

	g->pi->checkIsRuning();
	g->ene->ai();

	hit(g);
}
