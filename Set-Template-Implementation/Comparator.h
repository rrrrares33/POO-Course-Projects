#pragma once
#include "RBT.h"
#include "Node.h"
#include <stack>

using std::stack;
using std::cout;
using std::bad_alloc;

template <class T>
class Comparator
{
public:
	bool exists(const RBT<T> &tree, const T &val) const;
};


template<class T>
bool Comparator<T>::exists(const RBT<T>& tree, const T & val) const
{
	//I will search for a node with the given value in the tree.
	Node<T> *temp;
	try
	{
		temp = new Node<T>;
	}
	catch (bad_alloc temp)
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	temp = tree.search(val);

	//If i found a node with this value, than i will return true.
	if (temp->getVal() == val)
		return true;
	//Else it will return false;
	return false;
}



//Specilization to consider two integers equal if they have the same parity
//ex: 3 == 1;
template <>
class Comparator<int>
{
private:
	RBT<int> tree;
	int val;

public:
	bool exists(const RBT<int> &tree, const int &val) const
	{
		stack<Node<int>*> s;
		
		Node<int> *currentNode;
		try
		{
			currentNode = new Node<int>;
		}
		catch (bad_alloc currentNode)
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}
		currentNode = tree.getRoot();

		while (currentNode != NULL || s.empty() == false)
		{
			//Go to the most left node in the tree.
			while (currentNode != NULL)
			{
				//Place each Node in the stack;
				s.push(currentNode);
				currentNode = currentNode->getLeft();
			}

			//currentNode is NULL.
			currentNode = s.top();
			s.pop();

			//If a integer from RBT has the same parity with our value
			//we return true.
			if (currentNode->getVal() % 2 == val % 2)
				return true;

			//Now we check the right subtree
			currentNode = currentNode->getRight();

		}
		delete currentNode;
		return false;
	}
};
