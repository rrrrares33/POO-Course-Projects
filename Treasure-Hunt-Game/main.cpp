//
//Treasure Hunt game simulation
#include <time.h>       //time
#include <conio.h>		//_getch()
#include "Map.h"
#include "GameMaster.h"

using std::cin;

int main() 
{
	//Without this, random will be the same in two consecutive rounds
	srand(time(NULL));
	//Ask for size.
	cout << " What size do you want game's map to be?" << endl;
	cout << " Number(>=15) : ";

	int *aux;
	try {
		aux = new int;
	}
	catch (bad_alloc aux)
	{
		cout << "Alocation Failure.";
		exit(EXIT_FAILURE);
	}
	cin >> *aux;
	cout << endl << endl;

	while (*aux < 15)	//If user entered wrong size.
	{
		cout << " Number should be bigger then 15, enter again." << endl;
		cout << " Number(>=15) : ";
		cin >> *aux;
	}
	cout << endl << endl;

	GameMaster game(*aux);
	delete aux;

	int *rounds;
	try {
		rounds = new int;
	}
	catch (bad_alloc rounds)
	{
		cout << "Alocation Failure.";
		exit(EXIT_FAILURE);
	}
	*rounds = 0;

	while (_getch()=='1')
	{
		//Check if the game is in a final state
		if (game.endGame()) 
		{
			for (int i = 0; i < 15; i++)
				cout << endl;
			cout << endl << endl << "                   GAME OVER" << endl;
			cout << " NO TRAVELER CAN MOVE ANYMORE OR ALL THE TREASURES (TR) WERE FOUND." << endl;
			game.print_game();
			_getch();
			break;
		}
		//If not, it goes on with simulating
		*rounds += 1;
		for (int i = 0; i < 15; i++)
			cout << endl;
		cout << "	ROUND	" << *rounds << endl;
		game.play();
		cout << endl << "  DO YOU TO CONTINUE? 1->YES, ANYTHING OTHER KEY->NO."<<endl;
	}
	delete rounds;
	return 0;
}