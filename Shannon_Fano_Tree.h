#pragma once
#include "Shannon_Fano_Tree_Node.h"
#include "Shannon_Fano.h"
#include <vector>

using namespace std;

class Shannon_Fano_Tree
{
private:
	friend Shannon_Fano;
	Shannon_Fano_Tree_Node * head;
	ListClass <char> encoded_symbols;
	ListClass <vector<bool>> code;

	size_t encoded_size;
	size_t string_size;

	void creating_tree();
	void separation(Shannon_Fano_Tree_Node *);
	void results();

public:
	Shannon_Fano_Tree(Map<char, size_t>*);
};

Shannon_Fano_Tree::Shannon_Fano_Tree(Map<char, size_t>* map)
{
	head = new Shannon_Fano_Tree_Node();
	head->create_head(map);
	creating_tree();

	//counting encoded size
	encoded_size = 0;
	for (size_t i = 0; i < code.get_size(); i++) //symbol and code table
	{
		encoded_size += code.at(i).size() * head->probability.at(i);
	}
};

void Shannon_Fano_Tree::creating_tree()
{
	separation(head);
}

void Shannon_Fano_Tree::separation(Shannon_Fano_Tree_Node * current) // recursive tree creation method
{
	if (current->probability.get_size() == 1)
	{
		// filling the final table
		encoded_symbols.push_back(current->symbols.at(0));

		vector<bool> code_list; //making code
		if (current == head)
		{
			code_list.insert(code_list.cbegin(), 1);
		}
		while (current != head)
		{
			code_list.insert(code_list.cbegin(), current->intermediate_code);
			current = current->up;
		}
		
		code.push_back(code_list);
		code.get_size();
		return;
	}
	else
	{
		int total = 0; // total amount calculation
		for (size_t i = 0; i < current->probability.get_size(); i++)
		{
			total += current->probability.at(i);
		}

		// border search
		int current_total = 0;
		size_t border;
		for (size_t i = 0; i < (current->probability.get_size() - 1) && (current_total + current->probability.at(i)) <= (total / 2); i++)
		{
			current_total += current->probability.at(i);
			border = i;
		}

		//making children
		current->left = new Shannon_Fano_Tree_Node;
		current->left->intermediate_code = 1;
		current->left->up = current;
		for (size_t i = 0; i <= border; i++)
		{
			current->left->probability.push_back(current->probability.at(i));
			current->left->symbols.push_back(current->symbols.at(i));
		}

		current->right = new Shannon_Fano_Tree_Node;
		current->right->intermediate_code = 0;
		current->right->up = current;
		for (size_t i = border + 1; i < current->probability.get_size(); i++)
		{
			current->right->probability.push_back(current->probability.at(i));
			current->right->symbols.push_back(current->symbols.at(i));
		}

		separation(current->left);
		separation(current->right);
	}

}

void Shannon_Fano_Tree::results()
{
	//cout << head->symbols << endl << head->probability << endl << "Codes:\n"; //symbol and probability table
	cout << endl;
	cout << "Symbol/Probability/Code" << endl;
	for (size_t i = 0; i < encoded_symbols.get_size(); i++) //symbol and code table
	{
		cout << encoded_symbols.at(i) << "  " << head->probability.at(i) << "  ";
		for (size_t n = 0; n < code.at(i).size(); n++)
		{
			cout << code.at(i)[n];
		}
		cout << endl;
	}

	cout << endl;
	cout << "String size: " << string_size << " bit" << endl << "Encoded size: " << encoded_size << " bit" << endl;
	cout << "Compression ratio: " << float(string_size) / float(encoded_size) << endl << endl;
}

