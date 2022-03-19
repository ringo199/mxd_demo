
#include "render.h"

void render(global* g)
{
	BeginBatchDraw();
	renderBG(g);
	renderPlayer(g);
	renderEnemy(g);
	renderBlock(g);
	EndBatchDraw();
}

void renderBG(global* g)
{
	int ox, oy;
	g->carama->mapCoord2CaramaCoora(0, 0, &ox, &oy);
	putimage(ox, oy, &g->carama->bg);
}

void renderPlayer(global* g)
{
	g->pi->render();
}

void renderEnemy(global* g)
{
	g->ene->render();
	g->ene->renderHP();
}

void renderBlock(global* g)
{
	g->rb->render_static_objs();
}
