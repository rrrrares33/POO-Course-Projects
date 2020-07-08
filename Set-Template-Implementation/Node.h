#pragma once

//Enumeration of colors used in every node to mantain RBT structure
enum COLORS { RED, BLACK };	

template <class T> 
class RBT;

template <class T>
class Node
{

private:

	T val;
	COLORS color;
	Node<T> *left, *right, *parent;


protected:
	Node(const T& val);

	//We need a method to acces a node beside our parent's node.(like an uncle to our node)
	Node<T>* uncle() const;

	//Checks position of our node relative to it's parent
	bool isOnLeft() const { return this == parent->left; }

	//We need a methoud to acces the sibling to our node.
	Node<T>* sibling() const;

	//Moves down a node and moves given node in its place
	void moveDown(Node<T>* &givenNode);

	//Checks the color of the children of our Node.
	bool hasRedChild() const {return ((left != NULL && left->color == RED) || (right != NULL && right->color == RED));}

	//Getters (to be used only by my RBT structure);
	COLORS getColor() const { return this->color; }
	Node<T>* getParent() const { return this->parent; }

	//Setters (to be used only by my RBT structure);
	void setVal(T val)  { this->val = val; }
	void setColor(COLORS col)  { this->color = col; }
	void setLeft(Node<T>* left)  { this ->left = left; }
	void setRight(Node<T>* right) { this->right = right; }
	void setParent(Node<T>* parent) { this->parent = parent; }

	friend class RBT<T>;

public:

	//Constructor without parameters (made public for try-catches).
	Node<T>() : left(NULL), right(NULL), parent(NULL) {};

	/*~Node<T>()
	{
		if (this != nil)
		{
			if (this->left != nil)
				delete this->left;
			if (this->right != nil)
				delete this->right;
		}
		delete this;
	}*/

	//Getters (that i need to use outside of RBT).
	T getVal() const { return this->val; }
	Node<T>* getRight() const { return this->right; }
	Node<T>* getLeft() const { return this->left; }
};



template<class T>
Node<T>::Node(const T & val): val(val)
{

	//Initially, we only have root, without a parent or left/right
	//So we make them NULL
	parent = left = right = NULL;
	//And every node at insertion is RED so we make it RED;
	color = RED;
}

template<class T>
Node<T>* Node<T>::uncle() const
{
	// If our node has no parent or parent has no parent, then there should not be an uncle 
	if (parent == NULL || parent->parent == NULL)
		return NULL;

	if (parent->isOnLeft())
		// If parent is on left, then uncle should be on right. 
		return parent->parent->right;
	else
		// Else, uncle is for sure on left.
		return parent->parent->left;
}

template<class T>
Node<T>* Node<T>::sibling() const
{
	//Sibling will not exist if there is no parent (like in the root)
	if (parent == NULL)
		return NULL;

	if (isOnLeft())
		return parent->right;

	return parent->left;
}

template<class T>
void Node<T>::moveDown(Node<T>*& givenNode)
{

	if (parent != NULL)
	{
		if (isOnLeft())
		{
			parent->left = givenNode;
		}
		else
		{
			parent->right = givenNode;
		}
	}
	givenNode->parent = parent;
	parent = givenNode;
}
