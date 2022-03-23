
#include "global.h"

global::global()
{
	this->update		=	&s_update;
	this->uiManager		=	NULL;
	this->eventManager	=	NULL;
}

global::~global()
{
}

void global::init(UIManager* uiManager, event_manager* eventManager)
{
	this->uiManager = uiManager;
	this->eventManager = eventManager;
}
