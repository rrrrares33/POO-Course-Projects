#pragma once

#include "Map.h"

class GameMaster
{
	Map* map;
public:
	GameMaster(const int);
	void play();
	void print_game() const;
	bool endGame() const;
	~GameMaster() { delete map; };
};

