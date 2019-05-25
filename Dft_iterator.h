#pragma once
#include "Map.h"
template <class Key, class Value>
class Map;

template <class Key, class Value>
class Dft_iterator // ������������ ����� ��������� 
{
public:
	friend Map<Key, Value>;
	Dft_iterator(Map<Key, Value> * tree);
	~Dft_iterator();
	TreeNode<Key, Value> * next(); // ����� �������� � ���������� ��������
	bool has_next(); // ����� �������� ����������� �������� � ���������� ��������

protected:
	TreeNode<Key, Value> * current; // ��������� �� ������� �������
};

template <class Key, class Value>
Dft_iterator<Key, Value>::Dft_iterator(Map<Key, Value> * tree)
{
	if (tree->head == nullptr)
	{
		current = nullptr;
	}
	else
	{
		current = tree->head; // ������ � ������ ������ �������� ������ ��� ������ ��������� ������ � �������
		while ((current->left != nullptr) || (current->right != nullptr))
		{
			if (current->left == nullptr)
			{
				current = current->right;
			}
			else
				current = current->left;
		}
	}
}

template <class Key, class Value>
Dft_iterator<Key, Value>::~Dft_iterator()
{

}

template <class Key, class Value>
bool Dft_iterator<Key, Value>::has_next()
{
	return (current != nullptr);
}
template <class Key, class Value>
TreeNode<Key, Value> * Dft_iterator<Key, Value>::next()
{
	TreeNode<Key, Value> * to_return = current;
	if (current->parent) // ���� ���� ���� ����
	{

		if ((current->parent->right != nullptr) && (current->parent->right != current)) //���� ����� ������ �� ������ �����, �� ��������
		{
			current = current->parent->right;
			while ((current->left != nullptr) || (current->right != nullptr)) // ��� � ����� ������ ������� ����� (�� ����������� �����)
			{
				if (current->left == nullptr)
				{
					current = current->right;
				}
				else
					current = current->left;
			}
		}
		else // ���� ������ ����� ���, ����������� �����
			current = current->parent;
	}
	else // ���� ������ �� ������
		current = nullptr;

	return to_return; //���������� ���� ��������
}
