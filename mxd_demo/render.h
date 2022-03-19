#pragma once
#ifndef __RENDER_H__
#define __RENDER_H__

#include <stdio.h>
#include "tools.h"
#include "global.h"
#include "collision.h"

void render(global*);
void renderBG(global*);
void renderPlayer(global*);
void renderEnemy(global*);
void renderBlock(global*);

#endif
