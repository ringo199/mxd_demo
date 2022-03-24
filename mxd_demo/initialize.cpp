
#include "initialize.h"

using namespace global;

void initialize()
{
	init();
	loop();
}

void init()
{
	initgraph(1080, 600, 1);

	GetUIManager()->eventRegister(GetEventManager());
	GetEventManager()->eventEmit(UI_NEXT);

	keyEvent();
}

void loop()
{
	int timer = 0;

	for (;;)
	{
		timer += getDelay();
		if (timer > FRAMES)
		{
			timer = 0;
			ChangeUpdate(true);
		}

		if (GetUpdate())
		{
			ChangeUpdate(false);
			GetUIManager()->getScene()->beforeEvent();

			BeginBatchDraw();
			GetUIManager()->getScene()->render();
			EndBatchDraw();

			GetUIManager()->getScene()->afterEvent();
		}
	}
}
