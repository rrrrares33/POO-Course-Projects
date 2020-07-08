#pragma once

#include "Adventurer.h"
#include "Map.h"

//This adventurer can only see under around him by 1 space
//And under the main diagonal

class AdventurerLL : public Adventurer {
public:
	AdventurerLL(const Position& pos) : Adventurer(pos) {}
	
	string get_type() const { return "LL"; }

	Position checkForTreasure(const Map&) const;

	Position get_new_position(const Map&) const;

	~AdventurerLL() { delete this; };
};

