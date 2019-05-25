#pragma once
#include "Map.h"

enum Color { BLACK, RED };


template <class Key, class Value>
class Map;
template <class Key, class Value>
class Dft_iterator;
class Shannon_Fano;
class Shannon_Fano_Tree_Node;


template <class Key, class Value>
class TreeNode
{

public:
	friend Map<Key, Value>;
	friend Dft_iterator<Key, Value>;
	friend Shannon_Fano;
	friend Shannon_Fano_Tree_Node;

	TreeNode(Key key, Value value); 
	~TreeNode();
	Value get_value(); // for testing
	Color get_color();
	bool leaf();

private:
	bool is_leaf;
	Color color; // BLACK = 0, RED = 1
	Key key; 
	Value value;
	TreeNode * left; 
	TreeNode * right;
	TreeNode * parent; 

};

template <class Key, class Value>
TreeNode<Key, Value>::TreeNode(Key key, Value value)
{
	this->key = key;
	this->value = value;

	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = RED;
}

template <class Key, class Value>
TreeNode<Key, Value>::~TreeNode()
{

	if (parent != nullptr)
	{
		if (parent->left == this)
		{
			parent->left = nullptr;
		}		
		else
		{
			parent->right = nullptr;
		}
			
	}
}

template <class Key, class Value>
Value TreeNode<Key, Value>::get_value()
{
	return value;
}

template <class Key, class Value>
Color TreeNode<Key, Value>::get_color()
{
	return color;
}
template <class Key, class Value>
bool TreeNode<Key, Value>::leaf()
{
	return is_leaf;
}