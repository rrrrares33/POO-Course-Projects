#include "Map.h"

Map::Map(const int collumns, const int rows) : numberOfCol(collumns), numberOfRows(rows) {
	//Initializing the table clean
	map.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		map[i].resize(collumns);
		for (int j = 0; j < collumns; j++)
			map[i][j] = "0";
	}
	//Add adventures on corners of the map
	adventurers.resize(4);
	Adventurer::Position pos(0, 0);
	adventurers[0] = new AdventurerLU(pos);		//First traveler will always be on first space of matrix
	pos.set_col(collumns - 1);
	adventurers[1] = new AdventurerRU(pos);		//Second traveler will always be on the first line  and last coll
	pos.set_col(0);
	pos.set_line(rows - 1);
	adventurers[2] = new AdventurerLL(pos);		//Third traveler will always be on last line, first column
	pos.set_col(collumns - 1);
	adventurers[3] = new AdventurerRL(pos);		//Fourth traveler will always be on the last space of the matrix
	for (int i = 0; i < adventurers.size(); i++)
	{
		pos = (*adventurers[i]).get_position();
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
		map[*x][*y] = (*adventurers[i]).get_type();
		delete x;
		delete y;
	}
	//Adds Treasures to the map
	int contor = 0;
	while (contor < 3)
	{
		int *x;
		try {
			x = new int;
		}
		catch (bad_alloc x)
		{
			cout << "Alocation Failure.";
			exit(EXIT_FAILURE);
		}
		*x = rand() % rows;
		int *y;
		try {
			y = new int;
		}
		catch (bad_alloc y)
		{
			cout << "Alocation Failure.";
			exit(EXIT_FAILURE);
		}
		*y = rand() % collumns;
		if (map[*x][*y] == to_string(0))
		{
			map[*x][*y] = "TR";
			contor++;
		}
		delete x;
		delete y;
	}
}

ostream & operator<<(ostream & out, const Map& map)
{
	out << "-";
	for (int j = 0; j < map.getNumberOfCol(); j++)
		out << "----";
	out << endl;
	for (int i = 0; i < map.getNumberOfRows(); i++)
	{
		for (int j = 0; j < map.getNumberOfCol(); j++)
			if (map.mapa(i,j).length() == 1)
				out << "|" << map.mapa(i,j) << "  ";
			else
				out << "|" << map.mapa(i,j) << " ";
		out << "|";
		out << endl;
		out << "-";
		for (int j = 0; j < map.getNumberOfCol(); j++)
			out << "----";
		out << endl;
	}
	return out;
}

void Map::remove_adventurer(Adventurer* adv)
{
	//I use this to remove an adventurer from the map.
	Adventurer::Position pos = (*adv).get_position();
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
	map[*x][*y] = "1";
	for (int i = 0; i < adventurers.size(); i++)
		if ((*adventurers[i]).get_position() == adv->get_position())
		{
			adventurers.erase(adventurers.begin() + i);
			break;
		}
	delete x;
	delete y;
}

bool Map::checks_for_treaures()
{
	//I use this to check whether there are any treasures left on the map or not.
	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map[i].size(); j++)
			if (map[i][j] == "TR")
				return true;
	return false;
}

void Map::move(Adventurer* adv, const int newPosX, const int newPosY)
{
	Adventurer::Position pos = adv->get_position();
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

	map[*x][*y] = "1";				//"1" will be used for explored spaces
	*x = newPosX;
	*y = newPosY;
	map[*x][*y] = adv->get_type();	//I will put a player on a new place
	pos.set_col(*y);
	pos.set_line(*x);

	adv->set_position(pos);			//And i will set it's new position;4
	delete x;
	delete y;
}

Map::~Map()
{
	for (int i = 0; i < this->getNumberOfRows(); i++)
		while (map[i].size() > 0)
			map[i].pop_back();
	adventurers.clear();
}

