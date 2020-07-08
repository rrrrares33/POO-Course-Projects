#pragma once

#include <vector>
#include "AdventurerLU.h"
#include "AdventurerLL.h"
#include "AdventurerRL.h"
#include "AdventurerRU.h"

using std::vector; //I will need it to store many things dynamic
using std::ostream;

class Map
{
	//All adventurers.
	vector<Adventurer*> adventurers;	
	//Map.
	vector<vector<string>> map;
	//Map size (constant because it never changes its values during a game).
	const int numberOfRows, numberOfCol;
	
public:
	//Creates world
	Map(const int, const int);

	//Overloaded operator to print the map in it's current state
	friend ostream &operator <<(ostream&, const Map&);

	//Returns number of rows on map
	int getNumberOfRows() const { return this->numberOfRows; }
	
	//Returns number of collums on map
	int getNumberOfCol() const { return this->numberOfCol; }

	//Removes an adventurer to a certain position on map
	void remove_adventurer(Adventurer*);

	//Checks if there are treasures left on the map
	bool checks_for_treaures();

	//Moves an adventurer from an old position to a new one
	void move(Adventurer*, int const, int const);

	//Returns a vector with all adventurers;
	vector<Adventurer*> all_adventurers() { return this->adventurers; }

	//Returns an element from map
	string mapa(int const x, int const y) const { return this->map[x][y]; }

	//Destroys the world
	virtual ~Map();
};

