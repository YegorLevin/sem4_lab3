#pragma once
#include "Map.h"

#include <string>

#include <iostream>
#include <stdexcept>
#include "Shannon_Fano_Tree.h"

using namespace std;


class Shannon_Fano
{
private:
	Map<char, size_t> * map;
	Shannon_Fano_Tree * ShannonTree;
	void create_map(string input);

public:
	Shannon_Fano();
	size_t get_encoded_size();
	size_t get_string_size();
	void encoding(string input);
	void decoding(string input);
	void results();
};


Shannon_Fano::Shannon_Fano()
{
	map = new Map<char, size_t>;
}




void Shannon_Fano::results()
{
	ShannonTree->results();

}


void Shannon_Fano::create_map(string input)
{
	TreeNode<char, size_t> * current_symbol;
	for (size_t i = 0; i < input.size(); i++)
	{
		current_symbol = map->find(input.at(i));
		if (current_symbol == nullptr)
		{
			map->insert(input.at(i), 1);
		}
		else
		{
			current_symbol->value++;
		}
	}
}
size_t Shannon_Fano::get_encoded_size()
{
	return ShannonTree->encoded_size;
}
size_t Shannon_Fano::get_string_size()
{
	return ShannonTree->string_size;
}

void Shannon_Fano::encoding(string input)
{
	if (input.size() < 1) // if nothing to encode 
		throw invalid_argument("Nothing to encode");

	create_map(input);
	ShannonTree = new Shannon_Fano_Tree(map);

	ShannonTree->string_size = input.size() * 8;


	cout << endl << "Encoded string:" << endl;
	//encoded string
	for (size_t i = 0; i < input.size(); i++)
	{
		size_t j = 0;
		while (input[i] != ShannonTree->encoded_symbols.at(j)) //finding an index for the current character
		{
			j++;
		}
		for (size_t k = 0; k < ShannonTree->code.at(j).size(); k++) // code output
		{
			cout << ShannonTree->code.at(j)[k];
		}
	}

	cout << endl;

}

void Shannon_Fano::decoding(string input)
{
	bool decoded;
	size_t offset;

	cout << endl << "Decoded string:" << endl;
	for (size_t string_counter = 0; string_counter < input.size(); string_counter++) 
	{
		decoded = false;
		
		for (size_t list_counter = 0; decoded == false; list_counter++)
		{
			if (list_counter == ShannonTree->code.get_size()) // if code is wrong
			{
				throw invalid_argument("Wrong code");
			}
			offset = 0;
			for (size_t code_counter = 0; code_counter < ShannonTree->code.at(list_counter).size(); code_counter++)// finding symbol
			{
				if ((input[string_counter+offset]=='0'&& ShannonTree->code.at(list_counter)[code_counter] == 1) 
					|| (input[string_counter + offset] == '1'&& ShannonTree->code.at(list_counter)[code_counter] == 0)
					|| (string_counter + offset == input.size()))
				{
					break; // this symbol isn't right
				}

				if (code_counter == ShannonTree->code.at(list_counter).size() - 1) //decoded
				{
					decoded = true;
					cout << ShannonTree->encoded_symbols.at(list_counter);
				}
				offset++;
			}
				
		}
		string_counter += offset-1; //offset to the next symbol
	}
}