#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{

	template<class T>
	struct node
	{
		T content;
		node *parent;
		node *right;
		node *left;
		#ifdef __linux__
			int trick_for_size;
		#endif
		node() : right(NULL), left(NULL), parent(NULL)
		{

		}
		node(T x) : content(x), parent(NULL), right(NULL), left(NULL)
		{

		}
	};

	template <class T>
	node<T>*	_max(node<T> *node)
	{
		ft::node<T> *tmp = node;
		while(tmp && tmp->right)
			tmp = tmp->right;
		return (tmp);
	}

	template <class T>
	node<T>*	_min(node<T> *node)
	{
		ft::node<T> *tmp = node;
		while(tmp && tmp->left)
			tmp = tmp->left;
		return (tmp);
	}

	template <class T>
	node<T>*	_prev(node<T> *node)
	{
		if(!node)
			return (NULL);
		if(node->left)
			return (_max(node->left));
		ft::node<T> *tmp = node->parent;
		while(tmp && tmp->left == node)
		{
			node = tmp;
			tmp = tmp->parent;
		}
		return (tmp);
	}

	template <class T>
	node<T>*	_next(node<T> *node)
	{
		if(!node)
		{
			std::cout << "totem" << std::endl;
			return (NULL);
		}
		if(node->right)
		{
			if(_min(node->right) == NULL)
				std::cout << "hello" << std::endl;
			return (_min(node->right));
		}
		ft::node<T> *tmp = node->parent;
		while(tmp && tmp->right == node)
		{
			node = tmp;
			tmp = tmp->parent;
		}
		return (tmp);
	}
};
#endif