
#include "initialize.h"

void initialize()
{
	static global g;
	init(&g);
	loop(&g);
}

void init(global* g)
{
	static carama_info	carama;
	static player_info	pi(&carama);
	static old_enemy	ene(&carama);
	static rigidbody	rb(&carama);

	carama.init(2000, 1000, 1080, 600);

	pi.init(&rb, 300, 600);
	ene.init(&rb, 500, 600);

	g->init(&carama, &pi, &ene, &rb);

	//mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	initgraph(carama._carama_area.get_width(), carama._carama_area.get_height(), 1);

	preLoadSound("res/atk.mp3");
	preLoadSound("res/jump.mp3");

	keyEvent(g);
}

void loop(global* g)
{
	int timer = 0;

	for (;;)
	{
		timer += getDelay();
		if (timer > FRAMES)
		{
			timer = 0;
			*g->update = true;
		}

		if (*g->update)
		{
			*g->update = false;
			beforeEvent(g);
			render(g);
			afterEvent(g);
		}
	}
}
