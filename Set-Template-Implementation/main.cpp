#include <iostream>

//Used to freeze screen to read output with : _getch();
#include <conio.h>
//Used to test functionalities.
#include <assert.h>	
//Template for my set.
#include "Set.h"

//Function to test each method of set template with assert
void testMethodsOfSet()
{
	//Tests if constructor works correct.
	set<char> test;
	assert(test.size() == 0);
	//=================================

	//Tests if insert and size work correct.
	test.insert((char)'z');
	test.insert((char)'1');
	test.insert((char)'2');
	test.insert((char)'t');
	assert(test.size() == 4);
	//================================

	//Tests if has works correct.
	assert(test.has((char)'2') == true);
	assert(test.has((char)'a') == false);
	assert(test.has((char)'z') == true);
	//=================================

	//Tests if remove and size work correct.
	test.remove((char)'1');
	test.remove((char)'o'); // this does not exist in my set.
	assert(test.size() == 3);
	//=================================

	//Tests copy constructor
	set<char> testAux(test);
	assert(test.size() == testAux.size());
	assert(test.has((char)'z') == testAux.has((char)'z'));
	assert(test.has((char)'1') == testAux.has((char)'1'));
	//=================================

	//Tests overloading of operator "="
	set<char> testAux1 = test;
	assert(test.size() == testAux.size());
	assert(test.has((char)'z') == testAux.has((char)'z'));
	assert(test.has((char)'1') == testAux.has((char)'1'));
	//=================================

}

//Test specialization of set for int
void testIntSpecialization()
{
	//Int specialization of this set
	//Believes that 2 INT values are equal if they have the same parity
	//For example: 1 = 3; 2 != 3.
	//So,the maxim number of values we can have in a set is 2 (one odd and one even)
	set<int> test;
	//First i try to add 3 odd numbers to the set.
	test.insert((int)7);
	test.insert((int)11);
	test.insert((int)3);
	//Size will be 1 because only the first one was added because others have the same parity as the first added.
	assert(test.size() == 1);
	assert(test.has((int)7) == true);
	//Because my Comparator beleves that two int are equal if they have the same parity
	//This will also work ( 3 is an odd number ):
	assert(test.has((int)3) == true);

	//Next I try to add 3 even numbers to the set.	
	test.insert((int)2);
	test.insert((int)6);
	test.insert((int)10);
	//Size will be 2 because only the first one was added because others have the same parity as the first added.
	assert(test.size() == 2);
	assert(test.has((int)2) == true);
}


int main() 
{
	
	set<float> mySet;
	mySet.insert((float)3.2);
	mySet.insert((float)7.123);
	mySet.insert((float)1.2);
	mySet.insert((float)10.2);
	mySet.insert((float)7.12);
	mySet.insert((float)3.1);

	//TEST for overloaded opearator "<<"
	cout << mySet;

	//TEST BLOCK:
	testMethodsOfSet();
	testIntSpecialization();
	//======================

	_getch();
	return 0;
}