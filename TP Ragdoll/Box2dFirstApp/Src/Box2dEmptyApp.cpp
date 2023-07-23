#pragma once

#include "Game.h"
#include <tchar.h>

using namespace sf;


int _tmain(int argc, _TCHAR* argv[])
{
	Game *Juego;
	Juego = new Game(928, 793, "TP Final - ModAlgVJ2");
	Juego->Loop();

	return 0;
}