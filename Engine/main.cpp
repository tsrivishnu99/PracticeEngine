#pragma once
#include "CoreEngine.h"

void main()
{
	CoreEngine game;
	game.init(800,600,"Demo Game");
	game.gameLoop();
	getchar();
}