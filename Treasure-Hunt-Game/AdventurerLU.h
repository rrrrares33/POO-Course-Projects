#pragma once
#include "Adventurer.h"

//This type of adventurer will be able to see only around him by 1 space
//And above the second diagonal.

class AdventurerLU : public Adventurer
{
public:
	AdventurerLU(const Position& pos) : Adventurer(pos) {}

	string get_type() const { return "LU"; }

	Position checkForTreasure(const Map&) const;

	Position get_new_position(const Map&) const;

	~AdventurerLU() { delete this; };
};

