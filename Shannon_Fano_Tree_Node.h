#pragma once
#include "Shannon_Fano_Tree.h"

class Shannon_Fano_Tree;

class Shannon_Fano_Tree_Node
{
	friend Shannon_Fano_Tree;
private:
	ListClass<char> symbols;
	ListClass<size_t> probability;
	bool intermediate_code;

	Shannon_Fano_Tree_Node * left;
	Shannon_Fano_Tree_Node * right;
	Shannon_Fano_Tree_Node * up;

	Shannon_Fano_Tree_Node();

	void create_head(Map<char, size_t>*);
};

Shannon_Fano_Tree_Node::Shannon_Fano_Tree_Node()
{
	left = nullptr;
	right = nullptr;
	up = nullptr;
}

void Shannon_Fano_Tree_Node::create_head(Map<char, size_t> * map)
{
	Dft_iterator<char, size_t> * dft_iterator = new Dft_iterator<char, size_t>(map);


	while (dft_iterator->has_next()) //sorting
	{
		TreeNode<char, size_t> * current = dft_iterator->next();
		char symbol = current->key;
		size_t current_probability = current->value;
		size_t i = 0;
		while (i < probability.get_size() && current_probability>probability.at(i))
		{
			i++;
		}
		symbols.insert(i, symbol);
		probability.insert(i, current_probability);
	}
}