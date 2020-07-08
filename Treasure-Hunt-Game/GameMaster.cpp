#include "GameMaster.h"

GameMaster::GameMaster(const int x)
{
	cout << "!!!!!!!!!        Beggining of the game         !!!!!!!!" << endl;
	map = new Map(x, x);
	cout << (*map);
	cout << endl;
	cout << "LL = This traveler can only see under the main diagonal." << endl;
	cout << "LU = This traveler can only see above the secondary diagonal." << endl;
	cout << "RL = This traveler can only see under the secondary diagonal." << endl;
	cout << "RU = This traveler can only see above the main diagonal." << endl;
	cout << "TR = Treasure, desired by all travelers." << endl << endl;
	cout << "DO YOU WANT TO BEGIN ? 1->YES, ANY OTHER KEY->NO."<<endl;
}

void GameMaster::print_game() const
{
	cout << (*map);
}

void GameMaster::play() {
	vector <Adventurer*> adventurers = map->all_adventurers();
	string text = "";
	bool comoara;
	for (int i = 0; i < adventurers.size(); i++)
	{
		comoara = false;
		Adventurer::Position aux = (*adventurers[i]).get_new_position(*map);
		if (!((*adventurers[i]).get_position() == aux)) {
			if (map->mapa(aux.get_line(), aux.get_col()) == "TR")
			{
				cout << "TTRAVELER " << (*adventurers[i]).get_type() << " FOUND A TREASURE(TR)." << endl;
				comoara = true;
			}
			map->move(adventurers[i], aux.get_line(), aux.get_col());
			if (comoara)
			{
				map->remove_adventurer(adventurers[i]);
			}
			text += "Traveler with id ";
			text += (*adventurers[i]).get_type() + " moved on position " + to_string(aux.get_line()) + ' ' + to_string(aux.get_col()) + '\n';
		}
		else
		{
			text += "Traveler with id ";
			text += (*adventurers[i]).get_type() + " can not move.\n";
		}
	}
	cout << (*map);
	cout << endl;
	cout << text;
}

bool GameMaster::endGame() const
{
	//If all treasures were found, than game is over.
	if (!(map->checks_for_treaures()))
		return true;
	vector <Adventurer*> adventurers = map->all_adventurers();
	//If all left adventurers can not move, then game is over
	for (int i = 0; i < adventurers.size(); i++)
	{
		Adventurer::Position aux = (*adventurers[i]).get_new_position(*map);
		if (!((*adventurers[i]).get_position() == aux))		//"==" is already overloaded
		{
			//If this two positions are not equal, then at least one agent moved.
			return false;
		}
	}
	//If no adventurer could have moved, then it is game over.  
	return true;
}