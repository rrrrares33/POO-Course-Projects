#include "AdventurerLU.h"
#include "Map.h"

//This type of adventurer will be able to see only around him by 1 space
//And above the second diagonal.

Adventurer::Position AdventurerLU::checkForTreasure(const Map& map) const
{
	//Check above secondary diagonal for any treasure, going to every paralel of it.
	Adventurer::Position pos = this->get_position();

	int *x, *y;
	try {
		x = new int;
	}
	catch (bad_alloc x)
	{
		cout << "Alocation Failure.";
		exit(EXIT_FAILURE);
	}

	try {
		y = new int;
	}
	catch (bad_alloc y)
	{
		cout << "Alocation Failure.";
		exit(EXIT_FAILURE);
	}
	*x = pos.get_line();
	*y = pos.get_col();

	for (int i = 1; i < map.getNumberOfRows(); i++)
	{
		int col = 0;
		for (int linie = i; linie > -1; linie--)
			if (map.mapa(linie, col) == "TR")
			{
				*x = linie;
				*y = col;
			}
			else
			{
				col += 1;
			}
		if (*x != pos.get_line() || *y != pos.get_col())
			break;
	}

	pos.set_col(*y);
	pos.set_line(*x);
	delete x;
	delete y;
	return pos;
}

Adventurer::Position AdventurerLU::get_new_position(const Map& map) const
{
	Adventurer::Position pos = this->position;
	
	//I check if there is a treasure in the surroundings
	Adventurer::Position aux = this->checkAround(map);
	if (!(aux == pos))	//If it is, i will return it's position.
	{
		pos.set_col(aux.get_col());
		pos.set_line(aux.get_line());
		return pos;
	}
	//If it continues, then there is not any treasure around.

	int *x, *y;
	try {
		x = new int;
	}
	catch (bad_alloc x)
	{
		cout << "Alocation Failure.";
		exit(EXIT_FAILURE);
	}

	try {
		y = new int;
	}
	catch (bad_alloc y)
	{
		cout << "Alocation Failure.";
		exit(EXIT_FAILURE);
	}
	*x = pos.get_line();
	*y = pos.get_col();


	//I check whether my traveler is in his part of vision
	if (*x + *y < map.getNumberOfRows())
	{
		//I check for treasure in the part of vision
		Adventurer::Position treasure = this->checkForTreasure(map);
		if (!(treasure == pos)) //If i found a treasure
		{
			//I memorize its the next best move towards it
			Adventurer::Position newPosition = this->moveToIt(treasure);
			//If it is posibel to move it (map[i][j] == 0), move it 
			if (map.mapa(newPosition.get_line(), newPosition.get_col()) == to_string(0))
			{
				pos.set_col(newPosition.get_col());
				pos.set_line(newPosition.get_line());
				delete x;
				delete y;
				return pos;
			}
			//Else pick a random spot.
			else 
			{
				Adventurer::Position randomSpot = this->random(map);
				pos.set_col(randomSpot.get_col());
				pos.set_line(randomSpot.get_line());
				delete x;
				delete y;
				return pos;
			}
		}
		//If i did not found any treasure
		{
			//I will try to move traveler out of his view zone, and if it is not possible, it will pick a random spot and try again next round.
			if (map.mapa(*x + 1, *y + 1) == to_string(0))
			{
				Adventurer::Position newPos(*x + 1, *y + 1);
				delete x;
				delete y;
				return newPos;
			}
			else if (map.mapa(*x + 1, *y) == to_string(0))
			{
				Adventurer::Position newPos(*x + 1, *y);
				delete x;
				delete y;
				return newPos;
			}
			else if (map.mapa(*x, *y + 1) == to_string(0))
			{
				Adventurer::Position newPos(*x, *y + 1);
				delete x;
				delete y;
				return newPos;
			}
			else
			{
				Adventurer::Position newRandomPos = this->random(map);
				delete x;
				delete y;
				return newRandomPos;
			}
		}
	}
	else
	{
		//If he is on the other side of his vision, he will only move randomly.
		Adventurer::Position newRandomPos = this->random(map);
		delete x;
		delete y;
		return newRandomPos;
	}
}
