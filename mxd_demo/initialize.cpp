
#include "initialize.h"

void initialize()
{
	static global g;
	init(&g);
	loop(&g);
}

void init(global* g)
{
	initgraph(1080, 600, 1);

	static UIManager		uiManager;
	static event_manager	eventManager;

	uiManager.eventRegister(&eventManager);

	eventManager.eventEmit(UI_NEXT);

	g->init(&uiManager, &eventManager);

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
			g->uiManager->getScene()->beforeEvent();

			BeginBatchDraw();
			g->uiManager->getScene()->render();
			EndBatchDraw();

			g->uiManager->getScene()->afterEvent();
		}
	}
}
