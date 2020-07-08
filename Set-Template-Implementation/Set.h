#pragma once

#include "Comparator.h";
#include <stack>

using std::endl;

//For overloading << to display our set.
using std::ostream;
//For inorder/preoder traversal of our set (in RBT) to:
	//1.Check if a value is already in set.
	//2.Copy-Constructor
	//3.Overload "<<" to print a set
	//4.Overload "=" to copy a set in to another set
using std::stack;

template <class T, class F = Comparator<T>>
class set
{
	RBT<T> data_tree;

public:
	//Constructor without elements.
	set() {	RBT<T> data_tree() = new RBT<T>;}

	//Copy-Constructor
	//Inorder traversal(without recursion) and add each note one by one
	set(const set& sett);

	//Adds a new value to the set.
	void insert(const T& new_val);

	//Removes a value from set.
	void remove(const T& val_to_del);

	//Checks if a value is in set in O(log n). 
	bool has(const T& value) const;

	//Number of elements from set
	unsigned int size() const { return data_tree.get_size(); }

	//Overloading "<<"
	template <class T, class F = Comparator<T>>
	friend ostream& operator<<(ostream&,set<T>&);

	//Overloading "="
	template <class T, class F = Comparator<T>>
	set<T>& operator=(const set<T>& sett)
	{
		stack<Node<T>*> s;

		Node<T> *currentNode;
		try
		{
			currentNode = new Node<T>;
		}
		catch (bad_alloc currentNode)
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}
		currentNode = sett.data_tree.getRoot();

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

			this->insert(currentNode->getVal());

			//Now we check the right subtree
			currentNode = currentNode->getRight();

		}
		delete currentNode;
		s.empty();
	}

};


template<class T, class F = Comparator<T>>
ostream& operator<<(ostream& out, set<T>& sett)
{
	stack<Node<T>*> s;
	Node<T> *currentNode;
	try
	{
		currentNode = new Node<T>;
	}
	catch (bad_alloc currentNode)
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	} 
	currentNode = sett.data_tree.getRoot();

	out << "Setul contine urmatoarele elemente (stocate in ordine aleatoare): ";

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

		out << currentNode->getVal() << ' ';

		//Now we check the right subtree
		currentNode = currentNode->getRight();

	}
	delete currentNode;
	s.empty();
	out << endl << endl;
	return out;
}


template<class T, class F>
set<T, F>::set(const set & sett)
{
	stack<Node<T>*> s;

	Node<T> *currentNode;
	try
	{
		currentNode = new Node<T>;
	}
	catch (bad_alloc currentNode)
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	currentNode = sett.data_tree.getRoot();

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

		this->insert(currentNode->getVal());

		//Now we check the right subtree
		currentNode = currentNode->getRight();

	}
	delete currentNode;
	s.empty();
}


template<class T, class F>
void set<T, F>::insert(const T & new_val)
{
	if (data_tree.get_size() == 0)
	{
		data_tree.insert(new_val);
	}
	else
	{
		F comp;
		if (!comp.exists(data_tree, new_val))
		{
			data_tree.insert(new_val);
		}
	}
}


template<class T, class F>
void set<T, F>::remove(const T & val_to_del)
{
	F comp;
	if (comp.exists(data_tree, val_to_del))
		data_tree.deleteByVal(val_to_del);
}


template<class T, class F>
bool set<T, F>::has(const T & value) const
{
	F comp;
	return comp.exists(data_tree, value);
}