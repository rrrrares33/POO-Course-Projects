#pragma once
#include "Adventurer.h"

//This type of adventurer will be able to see only around him by 1 space
//And above the main diagonal.

class AdventurerRU : public Adventurer
{
public:
	AdventurerRU(const Position& pos) : Adventurer(pos) {}

	string get_type() const { return "RU"; }

	Position checkForTreasure(const Map&) const;

	Position get_new_position(const Map&) const;

	~AdventurerRU() { delete this; };
};

