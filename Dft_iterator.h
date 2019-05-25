#pragma once
#include "Map.h"
template <class Key, class Value>
class Map;

template <class Key, class Value>
class Dft_iterator // родительский класс итератора 
{
public:
	friend Map<Key, Value>;
	Dft_iterator(Map<Key, Value> * tree);
	~Dft_iterator();
	TreeNode<Key, Value> * next(); // метод перехода к следующему элементу
	bool has_next(); // метод проверки способности перехода к следующему элементу

protected:
	TreeNode<Key, Value> * current; // указатель на текущий элемент
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
		current = tree->head; // проход к самому левому элементу дерева для начала обратного обхода в глубину
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
	if (current->parent) // если есть куда идти
	{

		if ((current->parent->right != nullptr) && (current->parent->right != current)) //если можно пройти на правую ветку, то проходим
		{
			current = current->parent->right;
			while ((current->left != nullptr) || (current->right != nullptr)) // идём в самый нижний элемент ветки (по возможности левый)
			{
				if (current->left == nullptr)
				{
					current = current->right;
				}
				else
					current = current->left;
			}
		}
		else // если справа веток нет, поднимаемся вверх
			current = current->parent;
	}
	else // если обошли всё дерево
		current = nullptr;

	return to_return; //возвращаем ключ элемента
}
