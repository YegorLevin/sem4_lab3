#pragma once
#include "TreeNode.h"
#include "Dft_iterator.h"
#include "ListClass.h"

#include <iostream>
#include <stdexcept>

using namespace std;

template <class Key, class Value>
class Map
{
private:
	friend Dft_iterator<Key, Value>;
	friend Shannon_Fano;

	TreeNode<Key, Value> * head;

	TreeNode<Key, Value> * grandparent(TreeNode<Key, Value> * current);
	TreeNode<Key, Value> * uncle(TreeNode<Key, Value> *current);
	TreeNode<Key, Value> * brother(TreeNode<Key, Value> * current);

	void rotate_left(TreeNode<Key, Value> * current);
	void rotate_right(TreeNode<Key, Value> * current);

	void insert_case1(TreeNode<Key, Value> * current);
	void insert_case2(TreeNode<Key, Value> * current);
	void insert_case3(TreeNode<Key, Value> * current);
	void insert_case4(TreeNode<Key, Value> * current);
	void insert_case5(TreeNode<Key, Value> * current);

	void delete_one_child(TreeNode<Key, Value> *current);
	void replace_node(TreeNode<Key, Value> * first, TreeNode<Key, Value> * second);

	void delete_case1(TreeNode<Key, Value> * current);
	void delete_case2(TreeNode<Key, Value> * current);
	void delete_case3(TreeNode<Key, Value> * current);
	void delete_case4(TreeNode<Key, Value> * current);
	void delete_case5(TreeNode<Key, Value> * current);
	void delete_case6(TreeNode<Key, Value> * current);

	void print_Tree(TreeNode<Key, Value> * p, int level = 0); // recursive method for output


public:
	Map();
	~Map();

	void print(); // output tree to the console


	void insert(Key key, Value value); // adding a node to the tree
	ListClass<Key> * get_keys();
	ListClass<Value> * get_values();
	void clear();
	TreeNode<Key, Value> * find(Key key);

	bool is_empty(); // check for the emptiness of the tree

	void remove(Key key); // deleting a tree node by key
};




template<class Key, class Value>
bool Map<Key, Value>::is_empty()
{
	return head == nullptr;
}

template<class Key, class Value>
void Map<Key, Value>::clear()
{
	if (!is_empty())
	{
		Dft_iterator<Key, Value> * dft_iterator = new Dft_iterator<Key, Value>(this);
		TreeNode<Key, Value> * previous;
		while (dft_iterator->has_next())
		{
			previous = dft_iterator->current;
			dft_iterator->next();
			delete previous;
		}
		delete dft_iterator;
		head = nullptr;
	}
}



template<class Key, class Value>
Map<Key, Value>::Map()
{
	head = nullptr;
}

template<class Key, class Value>
Map<Key, Value> ::~Map()
{
	clear();
}

template<class Key, class Value>
void Map<Key, Value>::print_Tree(TreeNode<Key, Value> * p, int level)
{
	if (p) 
	{
		print_Tree(p->right, level + 1);
		for (int i = 0; i < level; i++)
			cout << "     ";
		if (p->is_leaf)
			cout << "(LEAF)" << endl;
		else
		{
			cout << p->key << "(" << (p->color == 0 ? "BK" : "RD") << ")" << "<" << endl;
			print_Tree(p->left, level + 1);
		}
			
	}
}

template<class Key, class Value>
void Map<Key, Value>::print()
{
	print_Tree(this->head);
}


template<class Key, class Value>
TreeNode<Key, Value> * Map<Key, Value>::grandparent(TreeNode<Key, Value> * current)
{
	if ((current != nullptr) && (current->parent != nullptr))
		return current->parent->parent;
	else
		return nullptr;
}

template<class Key, class Value>
TreeNode<Key, Value> * Map<Key, Value>::uncle(TreeNode<Key, Value> *current)
{
	TreeNode<Key, Value> * grandparentptr = grandparent(current);
	if (grandparentptr == nullptr)
		return nullptr; // No grandparent means no uncle
	if (current->parent == grandparentptr->left)
		return grandparentptr->right;
	else
		return grandparentptr->left;
}

template<class Key, class Value>
void Map<Key, Value>::rotate_left(TreeNode<Key, Value> * current)
{
	TreeNode<Key, Value> * pivot = current->right;

	pivot->parent = current->parent; // while perhaps the pivot becomes the head of the tree 
	if (current->parent == nullptr)
		head = pivot;
	if (current->parent != nullptr) {
		if (current->parent->left == current)
			current->parent->left = pivot;
		else
			current->parent->right = pivot;
	}

	current->right = pivot->left;
	if (pivot->left != nullptr)
		pivot->left->parent = current;

	current->parent = pivot;
	pivot->left = current;
}

template<class Key, class Value>
void Map<Key, Value>::rotate_right(TreeNode<Key, Value> * current)
{
	TreeNode<Key, Value> * pivot = current->left;

	pivot->parent = current->parent; // while perhaps the pivot becomes the head of the tree 
	if (current->parent == nullptr)
		head = pivot;
	if (current->parent != nullptr) {
		if (current->parent->left == current)
			current->parent->left = pivot;
		else
			current->parent->right = pivot;
	}

	current->left = pivot->right;
	if (pivot->right != nullptr)
		pivot->right->parent = current;

	current->parent = pivot;
	pivot->right = current;
}


//~~~~~~~~~~~~~~~~~~~~~insert cases~~~~~~~~~~~~~~~~~~~~~~
template<class Key, class Value>
void Map<Key, Value>::insert_case1(TreeNode<Key, Value> * current)
{
	if (current->parent == nullptr) // head node case
	{
		current->color = BLACK;
	}

	else
		insert_case2(current);
}

template<class Key, class Value>
void Map<Key, Value>::insert_case2(TreeNode<Key, Value> * current) // parent is BLACK
{
	if (current->parent->color == BLACK)
		return; /* Tree is still valid */
	else
		insert_case3(current);
}

template<class Key, class Value>
void Map<Key, Value>::insert_case3(TreeNode<Key, Value> * current) // parent and uncle are RED
{
	TreeNode<Key, Value> * uncleptr = uncle(current);


	if ((uncleptr != nullptr) && (uncleptr->color == RED))
	{
		current->parent->color = BLACK;
		uncleptr->color = BLACK;
		TreeNode<Key, Value> * grandparentptr = grandparent(current);
		grandparentptr->color = RED;
		insert_case1(grandparentptr);
	}
	else
	{
		insert_case4(current);
	}
}

template<class Key, class Value>
void Map<Key, Value>::insert_case4(TreeNode<Key, Value> * current) //parent is RED, uncle is BLACK, current is right, parent is left or opposite 
{
	TreeNode<Key, Value> * grandparentptr = grandparent(current);

	if ((current == current->parent->right) && (current->parent == grandparentptr->left)) {
		rotate_left(current->parent);
		current = current->left;
	}
	else if ((current == current->parent->left) && (current->parent == grandparentptr->right)) {
		rotate_right(current->parent);
		current = current->right;
	}
	insert_case5(current);
}

template<class Key, class Value>
void Map<Key, Value>::insert_case5(TreeNode<Key, Value> * current)  //parent is RED, uncle is BLACK, current is right, parent is right or opposite 
{
	TreeNode<Key, Value> * grandparentptr = grandparent(current);

	current->parent->color = BLACK;
	grandparentptr->color = RED;
	if ((current == current->parent->left) && (current->parent == grandparentptr->left)) {
		rotate_right(grandparentptr);
	}
	else {
		rotate_left(grandparentptr);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


template<class Key, class Value>
void Map<Key, Value>::insert(Key key, Value value)
{
	if (find(key) != nullptr)
		throw domain_error("There are nodes with this key");
	TreeNode<Key, Value> * current = head;
	if (head == nullptr) //if the tree is empty, create the first node
	{
		head = new TreeNode<Key, Value>(key, value);
		current = head;
	}
	else
	{
		bool end = 0; //have we reached the end of the tree

		while (!end) { //move down to the end comparing the key of our element with the keys in the tree
			if (key < current->key)// if our key is less than the specified key of the tree, then we go down to the left
			{

				if (current->left->is_leaf == false) //if it's not the final element, then go down below
					current = current->left;
				else // if it's final, create an element to the left of it with our key
				{
					end = 1;
					current = current->left;
					current->value = value;
					current->key = key;
				}

			}
			else // if our key is greater than or equal to the specified key of the tree, then we go down to the right
			{

				if (current->right->is_leaf == false) //if it's not the final element, then go down below
					current = current->right;
				else // if it's final, create an element to the left of it with our key
				{
					end = 1;
					current = current->right;
					current->value = value;
					current->key = key;
				}


			}
			

			
		}

	}
	current->is_leaf = false;
	current->color = RED;
	//creating leaves
	current->left = new TreeNode<Key, Value>(current->key, current->value);
	current->right = new TreeNode<Key, Value>(current->key, current->value);
	current->left->parent = current;
	current->right->parent = current;
	current->left->is_leaf = true;
	current->right->is_leaf = true;
	current->left->color = BLACK;
	current->right->color = BLACK;

	insert_case1(current); // coloring

}

template<class Key, class Value>
ListClass<Key> * Map<Key, Value>::get_keys()
{
	Dft_iterator<Key, Value> * dft_iterator = new Dft_iterator<Key, Value>(this);
	ListClass<Key> * list = new ListClass<Key>;
	TreeNode<Key, Value> * current;
	while (dft_iterator->has_next())
	{
		current = dft_iterator->next();
		if (current->is_leaf == false)
			list->push_back(current->key);
	}
	return list;
}

template<class Key, class Value>
ListClass<Value> * Map<Key, Value>::get_values()
{
	Dft_iterator<Key, Value> * dft_iterator = new Dft_iterator<Key, Value>(this);
	ListClass<Value> * list = new ListClass<Value>;
	TreeNode<Key, Value> * current;
	while (dft_iterator->has_next())
	{
		current = dft_iterator->next();
		if (current->is_leaf == false)
			list->push_back(current->value);
	}
	return list;
}

template<class Key, class Value>
TreeNode<Key, Value> * Map<Key, Value>::find(Key key)
{
	TreeNode<Key, Value> * current = head;
	while (current != nullptr && current->is_leaf == false && current->key != key)
	{
		if (key < current->key)
		{
			current = current->left;
		}
		else
			current = current->right;
	}
	if (current == nullptr || current->is_leaf)
		return nullptr;
	else
		return current;
}

template<class Key, class Value>
TreeNode<Key, Value> * Map<Key, Value>::brother(TreeNode<Key, Value> *current)
{
	if (current == current->parent->left)
		return current->parent->right;
	else
		return current->parent->left;
}

template<class Key, class Value>
void Map<Key, Value>::replace_node(TreeNode<Key, Value> * first, TreeNode<Key, Value> * second) //data exchange between nodes
{
	Value support_value;
	Key support_key;
	Color support_color;
	bool support_leaf;

	support_color = first->color;
	first->color = second->color;
	second->color = support_color;

	support_value = first->value;
	first->value = second->value;
	second->value = support_value;

	support_key = first->key;
	first->key = second->key;
	second->key = support_key;

	support_leaf = first->is_leaf;
	first->is_leaf = second->is_leaf;
	second->is_leaf = support_leaf;
}


template<class Key, class Value>
void Map<Key, Value>::delete_one_child(TreeNode<Key, Value> *current)
{
	//Condition: current has at most one nonzero child
	 
	TreeNode<Key, Value> *child = current->right->leaf() ? current->left : current->right;

	replace_node(current, child); //data exchange between nodes

	if (child->color == BLACK) {
		if (current->color == RED)
			current->color = BLACK;
		else
			delete_case1(current);
	}

	bool left = false;
	if (current->left == child)
	{
		left = true;
	}

	delete child;

	if (current->is_leaf) // deleting unnecessary leaves
	{
		if (current->left != nullptr)
			delete current->left;
		if (current->right != nullptr)
			delete current->right;

	}
	else // creating new leaf
	{
		if (left)
		{
			current->left = new TreeNode<Key, Value>(current->key, current->value);
			current->left->parent = current;
			current->left->is_leaf = true;
			current->left->color = BLACK;
		}
		else
		{
			current->right = new TreeNode<Key, Value>(current->key, current->value);
			current->right->parent = current;
			current->right->is_leaf = true;
			current->right->color = BLACK;
		}
	}
	
}

template<class Key, class Value>
void Map<Key, Value>::remove(Key key)
{
	TreeNode<Key, Value> * current = find(key);
	if (current->right->leaf() == false && current->left->leaf() == false) // finding node to delete
	{
		TreeNode<Key, Value> * deleting = current->right;
		while (deleting->left->leaf() == false)
		{
			deleting = deleting->left;
		}
		current->key = deleting->key;
		current->value = deleting->value;
		current = deleting;
	}
	delete_one_child(current);

}

//~~~~~~~~~~~~~~~~~~~~~delete cases~~~~~~~~~~~~~~~~~~~~~~

template<class Key, class Value>
void Map<Key, Value>::delete_case1(TreeNode<Key, Value> * current) // child is new head
{
	if (current->parent != nullptr)
		delete_case2(current);
}

template<class Key, class Value>
void Map<Key, Value>::delete_case2(TreeNode<Key, Value> * current) // brother is red
{
	TreeNode<Key, Value> * brotherptr = brother(current);

	if (brotherptr->color == RED) 
	{
		current->parent->color = RED;
		brotherptr->color = BLACK;
		if (current == current->parent->left)
			rotate_left(current->parent);
		else
			rotate_right(current->parent);
	}
	delete_case3(current);
}

template<class Key, class Value>
void Map<Key, Value>::delete_case3(TreeNode<Key, Value> * current) //brother is black and brother's children are black, parent is black
{
	TreeNode<Key, Value> * brotherptr = brother(current);

	if ((current->parent->color == BLACK) &&
		(brotherptr->color == BLACK) &&
		(brotherptr->left->color == BLACK) &&
		(brotherptr->right->color == BLACK)) 
	{
		brotherptr->color = RED;
		delete_case1(current->parent);
	}
	else
		delete_case4(current);
}

template<class Key, class Value>
void Map<Key, Value>::delete_case4(TreeNode<Key, Value> * current) // brother and his chindren are black but parent is red
{
	TreeNode<Key, Value> * brotherptr = brother(current);

	if ((current->parent->color == RED) &&
		(brotherptr->color == BLACK) &&
		(brotherptr->left->color == BLACK) &&
		(brotherptr->right->color == BLACK)) 
	{
		brotherptr->color = RED;
		current->parent->color = BLACK;
	}
	else
		delete_case5(current);
}

template<class Key, class Value>
void Map<Key, Value>::delete_case5(TreeNode<Key, Value> * current) 
//brother is black, brother's left child is red, right child is black, current is left child or opposite 
{
	TreeNode<Key, Value> * brotherptr = brother(current);

	if (brotherptr->color == BLACK) { /* this if statement is trivial,
due to case 2 (even though case 2 changed the sibling to a sibling's child,
the sibling's child can't be red, since no red parent can have a red child). */
/* the following statements just force the red to be on the left of the left of the parent,
   or right of the right, so case six will rotate correctly. */
		if ((current == current->parent->left) &&
			(brotherptr->right->color == BLACK) &&
			(brotherptr->left->color == RED)) 
		{ /* this last test is trivial too due to cases 2-4. */
			brotherptr->color = RED;
			brotherptr->left->color = BLACK;
			rotate_right(brotherptr);
		}
		else if ((current == current->parent->right) &&
			(brotherptr->left->color == BLACK) &&
			(brotherptr->right->color == RED))
		{/* this last test is trivial too due to cases 2-4. */
			brotherptr->color = RED;
			brotherptr->right->color = BLACK;
			rotate_left(brotherptr);
		}
	}
	delete_case6(current);
}
template<class Key, class Value>
void Map<Key, Value>::delete_case6(TreeNode<Key, Value> * current)
//brother is black, brother's right child is red, current is left child or opposite 
{
	TreeNode<Key, Value> * brotherptr = brother(current);

	brotherptr->color = current->parent->color;
	current->parent->color = BLACK;

	if (current == current->parent->left)
	{
		brotherptr->right->color = BLACK;
		rotate_left(current->parent);
	}
	else {
		brotherptr->left->color = BLACK;
		rotate_right(current->parent);
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

