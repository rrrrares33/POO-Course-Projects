#pragma once
#include "Adventurer.h"

//This type of adventurer will be able to see only around him by 1 space
//And under the secondary diagonal.

class AdventurerRL :  public Adventurer
{
public:
	AdventurerRL(const Position& pos) : Adventurer(pos) {}

	string get_type() const { return "RL"; }

	Position checkForTreasure(const Map&) const;

	Position get_new_position(const Map&) const;

	~AdventurerRL() { delete this; };
};

