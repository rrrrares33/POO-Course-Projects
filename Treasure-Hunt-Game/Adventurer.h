#pragma once
//Abstract class used as a base for all travelers
#include <iostream>
#include <string>
#include <exception>	//for try catches

//I include only the parts i need from the std
using std::string;	
using std::to_string;
using std::cout;
using std::endl;
using std::bad_alloc;

//I tried to use #include "Map.h" and it didn't work so i used this.
class Map;

class Adventurer
{

public:
	//Nested class to be used for Adventurer position on map.
	class Position
	{
			int line;
			int col;
	public:
			Position(const int x, const int y) : line(x), col(y) {};
			Position(const Position& obj) : line(obj.line), col(obj.col) {};
			void set_line(const int x) { this->line = x; };
			void set_col(const int y) { this->col = y; };
			int get_line() const { return this->line;};
			int get_col() const { return this->col; };
			//I will use this to compare two positions.
			bool operator==(const Position& p) {
				if (this->line == p.get_line() && this->col == p.get_col())
					return true;
				return false;
			};
			//I do not need to overload !=. (i can make use of the negation of ==).
			~Position() {};
	};
	
//I've set it as protected because it will be used by other derived classes
protected:
	Position position;

public:
	//No need for a constructor without parameters because an adventurer will always have a position
	Adventurer(const Position pos) : position(pos) {};
	
	//Returns position of the adventurer for which it is called. 
	Position get_position() const { return this->position; };

	//Sets a new position of the adventurer for which it is called. 
	void set_position(const Position& new_position);

	//Picks a random position around our adventurer.
	Position random(const Map&) const;

	//Checks if any treasure is around our adventurer (1 space).
	Position checkAround(const Map&) const;

	//Picks the most optimal new position for our traveler towards treasure.
	Position moveToIt(const Position&) const;

	//Returns the type of the agent formed like a string. Each class must have a diffrent type.
	virtual string get_type() const = 0;

	//Check for a treasure in treaveler sight of view.
	virtual Position checkForTreasure(const Map&) const = 0;

	//Tries to look for a new position on map. Each class must have a diffrent method of picking a new position.
	virtual Position get_new_position(const Map&) const = 0;

	//Virtual destructor
	virtual ~Adventurer() = 0 { delete this; };
};