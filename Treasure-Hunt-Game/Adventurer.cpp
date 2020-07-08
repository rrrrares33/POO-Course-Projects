#include "Adventurer.h"
#include "Map.h"

Adventurer::Position Adventurer::random(const Map& map) const
{
	//Picks a random spot around our traveler
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

	int *contor;
	try {
		contor = new int;
	}
	catch (bad_alloc contor)
	{
		cout << "Alocation Failure.";
		exit(EXIT_FAILURE);
	}

	*contor = 0;

	bool ok = false;
	while (!ok && *contor < 1000)
	{
		*contor += 1;
		int *dice;		//I use it to pick a random spot around traveler.
		try {
			dice = new int;
		}
		catch (bad_alloc dice)
		{
			cout << "Alocation Failure.";
			exit(EXIT_FAILURE);
		}

		*dice = rand() % 8;
		if (*dice == 0 && *x < map.getNumberOfRows() - 1 && (map.mapa(*x + 1, *y) == to_string(0) || map.mapa(*x + 1, *y) == "TR"))
		{
			*x = *x + 1;
			ok = true;
		}
		else if (*dice == 1 && *y < map.getNumberOfCol() - 1 && (map.mapa(*x, *y + 1) == to_string(0) || map.mapa(*x, *y + 1) == "TR"))
		{
			*y = *y + 1;
			ok = true;
		}
		else if (*dice == 2 && *x < map.getNumberOfRows() - 1 && *y < map.getNumberOfCol() - 1 && (map.mapa(*x + 1, *y + 1) == to_string(0) || map.mapa(*x + 1, *y + 1) == "TR"))
		{
			*x = *x + 1;
			*y = *y + 1;
			ok = true;
		}
		else if (*dice == 3 && *x > 0 && (map.mapa(*x - 1, *y) == to_string(0) || map.mapa(*x - 1, *y) == "TR"))
		{
			*x = *x - 1;
			ok = true;
		}
		else if (*dice == 4 && *y > 0 && (map.mapa(*x, *y - 1) == to_string(0) || map.mapa(*x, *y - 1) == "TR"))
		{
			*y = *y - 1;
			ok = true;
		}
		else if (*dice == 5 && *x > 0 && *y > 0 && (map.mapa(*x - 1, *y - 1) == to_string(0) || map.mapa(*x - 1, *y - 1) == "TR"))
		{
			*x = *x - 1;
			*y = *y - 1;
			ok = true;
		}
		else if (*dice == 6 && *y > 0 && *x < map.getNumberOfRows() - 1 && (map.mapa(*x + 1, *y - 1) == to_string(0) || map.mapa(*x + 1, *y - 1) == "TR"))
		{
			*x = *x + 1;
			*y = *y - 1;
			ok = true;
		}
		else if (*dice == 7 && *x > 0 && *y < map.getNumberOfCol() - 1 && (map.mapa(*x - 1, *y + 1) == to_string(0) || map.mapa(*x - 1, *y + 1) == "TR"))
		{
			*x = *x - 1;
			*y = *y + 1;
			ok = true;
		}
		delete dice;
	}

	pos.set_col(*y);
	pos.set_line(*x);
	delete x;
	delete y;
	return pos;
}

Adventurer::Position Adventurer::checkAround(const Map& map) const
{
	//Checks if there is any treasure around our traveler
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

	if (*x > 0 && *y > 0 && *x < map.getNumberOfRows() - 1 && *y < map.getNumberOfCol() - 1) //If i know that i am not on an edge or corner
	{
		if (map.mapa(*x + 1, *y) == "TR")
			*x += 1;
		else if (map.mapa(*x + 1, *y + 1) == "TR")
		{
			*x += 1;
			*y += 1;
		}
		else if (map.mapa(*x, *y + 1) == "TR")
			*y += 1;
		else if (map.mapa(*x - 1, *y) == "TR")
			*x -= 1;
		else if (map.mapa(*x - 1, *y - 1) == "TR")
		{
			*x -= 1;
			*y -= 1;
		}
		else if (map.mapa(*x, *y - 1) == "TR")
			*y -= 1;
		else if (map.mapa(*x + 1, *y - 1) == "TR")
		{
			*x += 1;
			*y -= 1;
		}
		else if (map.mapa(*x - 1, *y + 1) == "TR")
		{
			*x -= 1;
			*y += 1;
		}
	}
	else if (*x == 0)
	{
		if (*y == 0)	//If i am on the left edge of the map
		{
			if (map.mapa(*x, *y + 1) == "TR")
				*y += 1;
			else if (map.mapa(*x + 1, *y) == "TR")
				*x += 1;
			else if (map.mapa(*x + 1, *y + 1) == "TR")
			{
				*x += 1;
				*y += 1;
			}
		}
		else if (*y == map.getNumberOfCol() - 1)	//If i am on the right edge of the map
		{
			if (map.mapa(*x, *y - 1) == "TR")
				*y -= 1;
			else if (map.mapa(*x + 1, *y) == "TR")
				*x += 1;
			else if (map.mapa(*x + 1, *y - 1) == "TR")
			{
				*x += 1;
				*y -= 1;
			}
		}
		else
		{
			if (map.mapa(*x, *y - 1) == "TR")
				*y -= 1;
			else if (map.mapa(*x + 1, *y - 1) == "TR")
			{
				*x += 1;
				*y -= 1;
			}
			else if (map.mapa(*x + 1, *y) == "TR")
				*x += 1;
			else if (map.mapa(*x + 1, *y + 1) == "TR")
			{
				*x += 1;
				*y += 1;
			}
			else if (map.mapa(*x, *y + 1) == "TR")
				*y += 1;
		}
	}
	else if (*x == map.getNumberOfRows() - 1)
	{
		if (*y == 0)
		{
			if (map.mapa(*x - 1, *y) == "TR")
				*x -= 1;
			else if (map.mapa(*x - 1, *y + 1) == "TR")
			{
				*x -= 1;
				*y += 1;
			}
			else if (map.mapa(*x, *y + 1) == "TR")
				*y += 1;
		}
		else if (*y == map.getNumberOfCol() - 1)
		{
			if (map.mapa(*x, *y - 1) == "TR")
				*y -= 1;
			else if (map.mapa(*x - 1, *y - 1) == "TR")
			{
				*x -= 1;
				*y -= 1;
			}
			else if (map.mapa(*x - 1, *y) == "TR")
				*x -= 1;
		}
		else
		{
			if (map.mapa(*x, *y - 1) == "TR")
				*y -= 1;
			else if (map.mapa(*x - 1, *y - 1) == "TR")
			{
				*x -= 1;
				*y -= 1;
			}
			else if (map.mapa(*x - 1, *y) == "TR")
				*x -= 1;
			else if (map.mapa(*x - 1, *y + 1) == "TR")
			{
				*x -= 1;
				*y += 1;
			}
			else if (map.mapa(*x, *y + 1) == "TR")
				*y += 1;
		}
	}
	else if (*y == 0)
	{
		//Corners are already verified with *x==0 and *x=map.getNumberOfRows, so i will check only for the borders.
		if (map.mapa(*x - 1, *y) == "TR")
			*x -= 1;
		else if (map.mapa(*x - 1, *y + 1) == "TR")
		{
			*x -= 1;
			*y += 1;
		}
		else if (map.mapa(*x, *y + 1) == "TR")
			*y += 1;
		else if (map.mapa(*x + 1, *y + 1) == "TR")
		{
			*x += 1;
			*y += 1;
		}
		else if (map.mapa(*x + 1, *y) == "TR")
			*x += 1;
	}
	else if (*y = map.getNumberOfCol() - 1)
	{
		//Corners are already verified with *x==0 and *x=map.getNumberOfRows, so i will check only for the borders.
		if (map.mapa(*x - 1, *y) == "TR")
			*x -= 1;
		else if (map.mapa(*x - 1, *y - 1) == "TR")
		{
			*y -= 1;
			*x -= 1;
		}
		else if (map.mapa(*x, *y - 1) == "TR")
			*y -= 1;
		else if (map.mapa(*x + 1, *y - 1) == "TR")
		{
			*x += 1;
			*y -= 1;
		}
		else if (map.mapa(*x + 1, *y) == "TR")
			*x += 1;
	}

	pos.set_col(*y);
	pos.set_line(*x);
	delete x;
	delete y;
	return pos;
}

Adventurer::Position Adventurer::moveToIt(const Position& treasure) const
{
	//Picks the most optimal new position for our traveler towards treasure.
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

	int *xt, *yt;
	try {
		xt = new int;
	}
	catch (bad_alloc xt)
	{
		cout << "Alocation Failure.";
		exit(EXIT_FAILURE);
	}

	try {
		yt = new int;
	}
	catch (bad_alloc yt)
	{
		cout << "Alocation Failure.";
		exit(EXIT_FAILURE);
	}

	*xt = treasure.get_line();
	*yt = treasure.get_col();

	if (*x < *xt)
		*x += 1;
	else if (*x > *xt)
		*x -= 1;

	if (*y < *yt)
		*y += 1;
	else if (*y > *yt)
		*y -= 1;

	pos.set_col(*y);
	pos.set_line(*x);
	delete x;
	delete y;
	delete xt;
	delete yt;
	return pos;
}

void Adventurer::set_position(const Position& new_position) {
	this->position.set_line(new_position.get_line()); 
	this->position.set_col(new_position.get_col());
}