#pragma once
#include "Node.h"

template <class T>
class RBT
{

private:

	//This will store the root of our RBT
	Node<T> *root;
	//This will store the number of nodes in our tree;
	unsigned int size;		

	//Rotates a given node with the left one
	void leftRotate(Node<T>* &x);

	//Rotates a given node with the right one
	void rightRotate(Node<T>* &x);

	//Swaps colors of two Nodes
	void swapColors(Node<T>* &x1, Node<T>* &x2) const;

	//Swaps values of two Nodes
	void swapValues(Node<T>* &u, Node<T>* &v) const;

	//Solves the problem of two consecutive red nodes
	void fixRedRed(Node<T>* &x);

	//Find a Node without a left child under our curent node.
	Node<T> *successor(Node<T>* x) const;

	//Find a node that replaces a deleted node in RBT 
	Node<T> *BSTreplace(Node<T>* &x) const;

	//Deletes a given node from the RBT
	void deleteNode(Node<T>* &v);

	//Solves the problem of two consecutive black nodes
	void fixDoubleBlack(Node<T>* &x);

public:

	RBT<T>() : root(NULL), size(0) {};

	RBT<T>(const T &x);

	unsigned int get_size() const { return this->size; }
	
	//Method to get the root Node;
	Node<T> *getRoot() const { return root; }

	//Search for a value in RBT
	Node<T> *search(const T &n) const;

	//Inserts a new value in RBT 
	void insert(const T &n);

	//It will delete a node with a given value from RBT 
	void deleteByVal(const T &n);

};


//PRIVATE METHODS:

template<class T>
void RBT<T>::leftRotate(Node<T>*& x)
{

	//New parent will be node's right child 
	Node<T> *newParent;
	try
	{
		newParent = new Node<T>;
	}
	catch (bad_alloc newParent)
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	newParent = x->getRight();

	//Update root if current node is root 
	if (x == root)
		root = newParent;

	x->moveDown(newParent);

	//Connect x with new parent's left element 
	x->setRight(newParent->getLeft());

	//Connect new parent's left element with node 
	//If it is not null 
	if (newParent->getLeft() != NULL)
		newParent->getLeft()->setParent(x);

	//Connect new parent with x 
	newParent->setLeft(x);
}

template<class T>
void RBT<T>::rightRotate(Node<T>*& x)
{

	//New parent will be node's left child 
	Node<T> *newParent;
	try
	{
		newParent = new Node<T>;
	}
	catch (bad_alloc newParent)
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	newParent = x->getLeft();

	//Update root if current node is root 
	if (x == root)
		root = newParent;

	x->moveDown(newParent);

	//Connect x with new parent's right element 
	x->setLeft(newParent->getRight());
	//Connect new parent's right element with node 
	//If it is not null 
	if (newParent->getRight() != NULL)
		newParent->getRight()->setParent(x);

	//Connect new parent with x 
	newParent->setRight(x);
}

template<class T>
void RBT<T>::swapColors(Node<T>*& x1, Node<T>*& x2) const
{
	COLORS *aux;
	try
	{
		aux = new COLORS;
	}
	catch (bad_alloc aux)
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	*aux = x1->getColor();
	x1->setColor(x2->getColor());
	x2->setColor(*aux);
}

template<class T>
void RBT<T>::swapValues(Node<T>*& u, Node<T>*& v) const
{

	T *aux;
	try
	{
		aux = new T;
	}
	catch (bad_alloc aux)
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	*aux = u->getVal();
	u->setVal(v->getVal());
	v->setVal(*aux);
}

template<class T>
void RBT<T>::fixRedRed(Node<T>*& x)
{
	{
		//If our node is root, then i will make it black and return.
		if (x == root)
		{
			x->setColor(BLACK);
			return;
		}

		//Initialize parent of Node;
		Node<T> *parent;
		try
		{
			parent = new Node<T>;
		}
		catch (bad_alloc parent)
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}
		parent = x->getParent();

		//Initialize grandparent of Node;
		Node<T> *grandparent;
		try
		{
			grandparent = new Node<T>;
		}
		catch (bad_alloc grandparent)
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}
		grandparent = parent->getParent();


		Node<T> *uncle;
		try
		{
			uncle = new Node<T>;
		}
		catch (bad_alloc uncle)
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}
		uncle = x->uncle();

		if (parent->getColor() != BLACK)
		{
			if (uncle != NULL && uncle->getColor() == RED)
			{
				//Uncle is red, so do recoloring and recurse 
				parent->setColor(BLACK);
				uncle->setColor(BLACK);
				grandparent->setColor(RED);
				fixRedRed(grandparent);
			}
			else
			{
				//Else perform left-right, left-left, right-left, right-right 
				if (parent->isOnLeft())
				{
					if (x->isOnLeft())
					{
						//Left-right 
						swapColors(parent, grandparent);
					}
					else
					{
						//Left-left
						leftRotate(parent);
						swapColors(x, grandparent);
					}
					//left-left and left-right 
					rightRotate(grandparent);
				}
				else
				{
					if (x->isOnLeft())
					{
						//Right-left 
						rightRotate(parent);
						swapColors(x, grandparent);
					}
					else
					{
						//Right-right
						swapColors(parent, grandparent);
					}

					//Right-right and right-left 
					leftRotate(grandparent);
				}
			}
		}
	}
}

template<class T>
Node<T>* RBT<T>::successor(Node<T>* x) const
{
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
	temp = x;
	while (temp->getLeft() != NULL)
		temp = temp->getLeft();
	return temp;
}

template<class T>
Node<T>* RBT<T>::BSTreplace(Node<T>*& x) const
{
	//When node have 2 children 
	if (x->getLeft() != NULL && x->getRight() != NULL)
		return successor(x->getRight());

	//When leaf 
	if (x->getLeft() == NULL && x->getRight() == NULL)
		return NULL;

	//When one child 
	else if (x->getLeft() != NULL)
		return x->getLeft();
	else
		return x->getRight();
}

template<class T>
void RBT<T>::deleteNode(Node<T>*& v)
{
	Node<T> *u;
	try
	{
		u = new Node<T>;
	}
	catch (bad_alloc u)
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	u = BSTreplace(v);

	//True when u and v are both black 
	bool uvBlack = ((u == NULL || u->getColor() == BLACK) && (v->getColor() == BLACK));

	//Initialize parent
	Node<T> *parent;
	try
	{
		parent = new Node<T>;
	}
	catch (bad_alloc parent)
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	parent = v->getParent();

	if (u == NULL)
	{
		//If u is null then v is a leaf 
		if (v == root)
		{
			//If v is root, make root null 
			root = NULL;
		}
		else
		{
			if (uvBlack)
			{
				//If u and v are both black 
				//And v is leaf, fixdoubleblack at v 
				fixDoubleBlack(v);
			}
			else
			{
				//If u or v is red 
				if (v->sibling() != NULL)
					//If sibling is not null, it red should be red
					v->sibling()->setColor(RED);
			}

			//Delete v 
			if (v->isOnLeft())
			{
				parent->setLeft(NULL);
			}
			else
			{
				parent->setRight(NULL);
			}
		}
		delete v;
		return;
	}

	if (v->getLeft() == NULL || v->getRight() == NULL)
	{
		//v has 1 child 
		if (v == root)
		{
			//v is root, copy the value of u in v, then delete u 
			v->setVal(u->getVal());
			v->setLeft(NULL);
			v->setRight(v->getLeft());
			delete u;
		}
		else
		{
			//Detach v from tree and move u up 
			if (v->isOnLeft())
			{
				parent->setLeft(u);
			}
			else
			{
				parent->setRight(u);
			}

			delete v;
			u->setParent(parent);
			if (uvBlack)
			{
				//u and v both black, fixdoubleblack at u 
				fixDoubleBlack(u);
			}
			else
			{
				//u or v red, color u black 
				u->setColor(BLACK);
			}
		}
		return;
	}

	//v has 2 children, swap values with successor and recurse 
	swapValues(u, v);
	deleteNode(u);
}

template<class T>
void RBT<T>::fixDoubleBlack(Node<T>*& x)
{
	{
		if (x == root)
			return;

		//Initialize sibling.
		Node<T> *sibling;
		try
		{
			sibling = new Node <T>;
		}
		catch (bad_alloc sibling)
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}
		sibling = x->sibling();

		//Initialize parent.
		Node<T> *parent;
		try
		{
			parent = new Node<T>;
		}
		catch (bad_alloc parent)
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}
		parent = x->getParent();


		if (sibling == NULL)
		{
			//No sibiling, fixdoubleblack on parent 
			fixDoubleBlack(parent);
		}
		else
		{
			if (sibling->getColor() == RED)
			{
				//Sibling red 
				parent->setColor(RED);
				sibling->setColor(BLACK);
				if (sibling->isOnLeft())
				{
					//If it is left case 
					rightRotate(parent);
				}
				else
				{
					//If it is right case 
					leftRotate(parent);
				}
				fixDoubleBlack(x);
			}
			else
			{
				//Sibling black 
				if (sibling->hasRedChild())
				{
					//If it has at least 1 red children 
					if (sibling->getLeft() != NULL && sibling->getLeft()->getColor() == RED)
					{
						if (sibling->isOnLeft())
						{
							//If it is left left 
							sibling->getLeft()->setColor(sibling->getColor());
							sibling->setColor(parent->getColor());
							rightRotate(parent);
						}
						else
						{
							//If it is right left 
							sibling->getLeft()->setColor(parent->getColor());
							rightRotate(sibling);
							leftRotate(parent);
						}
					}
					else
					{
						if (sibling->isOnLeft())
						{
							//If it is left right 
							sibling->getRight()->setColor(parent->getColor());
							leftRotate(sibling);
							rightRotate(parent);
						}
						else
						{
							//If it is right right 
							sibling->getRight()->setColor(sibling->getColor());
							sibling->setColor(parent->getColor());
							leftRotate(parent);
						}
					}
					parent->setColor(BLACK);
				}
				else
				{
					//2 black children 
					sibling->setColor(RED);
					if (parent->getColor() == BLACK)
						fixDoubleBlack(parent);
					else
						parent->setColor(BLACK);
				}
			}
		}
	}
}

//================================================================



//PUBLIC METHODS:

template<class T>
RBT<T>::RBT(const T & x)
{

	{
		try
		{

			root = new Node<T>;
		}
		catch (bad_alloc root)
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}
		root->setVal(x);
	}
}

template<class T>
Node<T>* RBT<T>::search(const T & n) const
{
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
	temp = root;

	//Normal search in a binary search tree
	while (temp != NULL)
	{
		if (n < temp->getVal())
		{
			if (temp->getLeft() == NULL)
				break;
			else
				temp = temp->getLeft();
		}
		else if (n == temp->getVal())
		{
			break;
		}
		else
		{
			if (temp->getRight() == NULL)
				break;
			else
				temp = temp->getRight();
		}
	}

	return temp;
}

template<class T>
void RBT<T>::insert(const T & n)
{
	Node<T> *newNode;
	try
	{
		newNode = new Node<T>(n);
	}
	catch (bad_alloc newNode)
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}

	if (root == NULL)
	{
		//If root is NULL, simply insert value at root 
		newNode->setColor(BLACK);
		root = newNode;
		size = 1;
	}
	else
	{
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
		temp = search(n);

		if (temp->getVal() == n)
		{
			//Return if value already exists
			//I will not add it
			return;
		}

		//If value is not in RBT, then it will return
		//In temp, the position where next value should be inserted

		newNode->setParent(temp);

		if (n < temp->getVal())
			temp->setLeft(newNode);
		else
			temp->setRight(newNode);

		//Fix double Red violation if it exists 
		fixRedRed(newNode);
		size++;
	}
}

template<class T>
void RBT<T>::deleteByVal(const T & n)
{
	//RBT is empty 
	if (root == NULL)
		return;

	Node<T> *v;
	try
	{
		v = new Node<T>;
	}
	catch (bad_alloc v)
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	v = search(n);

	if (v->getVal() != n) {
		cout << "There is no node with the given value in RBT. (" << n << ')' << endl;
		return;
	}

	deleteNode(v);
	size--;
}

//==============================================================