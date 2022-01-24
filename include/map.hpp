#ifndef MAP_HPP
#define MAP_HPP
#include <memory>
#include <iostream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include "lexicographical_compare.hpp"
#include "pair.hpp"
#include "iterator.hpp"

template<class T>
struct node;

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> >
	> class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const Key, T> value_type;
			typedef node<value_type> node;
			typedef	std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef	Compare key_compare;
			typedef Allocator allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef ft::MapIterator<value_type> iterator;
			typedef ft::ConstMapIterator<value_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			map()
			{
				_init_constructor(Compare(), Allocator());
			}
			explicit map( const Compare& comp, const Allocator& alloc = Allocator() )
			{
				_init_constructor(comp, alloc);
			}
			template< class InputIt >
			map( InputIt first, InputIt last,
				const Compare& comp = Compare(),
				const Allocator& alloc = Allocator() )
			{
				_init_constructor(comp, alloc);
				while(first != last)
				{
					this->insert(*first);
					first++;
				}
			}
			map( map const & other )
			{
				_init_constructor(other._comp, other._alloc);
				this->_alloc = other._alloc;
				this->_comp = other._comp;
				this->_als = other._als;

				const_iterator it = other.begin();
				const_iterator ite = other.end();
				while(it != ite)
				{
					this->insert(*it);
					it++;
				}
			}
			~map()
			{
				clear();
				_free_node(_end);
			}
			bool empty() const
			{
				if(_size == 0)
					return (1);
				return (0);
			}
			allocator_type get_allocator() const
			{
				return (_alloc);
			}
			size_type size() const
			{
				return (_size);
			}
			size_type max_size() const
			{
				return (_als.max_size());
			}
			ft::pair<iterator, bool> insert( const value_type& value )
			{
				iterator it = find(value.first);
				if(it != _end)
				{
					return (ft::make_pair(it, 0));
				}
				size_type old_size = _size;
				_insert(_root, value);
				if (_root == _end) 
				{
					_root = _last_inserted;
					_root->right = _end;
					_end->parent = _root;
				}
				return (ft::make_pair(iterator(_last_inserted), _size != old_size));
			}
			template< class InputIt >
			void insert( InputIt first, InputIt last )
			{	
				while(first != last)
				{
					insert(*first);
					first++;
				}
			}
			iterator insert( iterator hint, const value_type& value )
			{
				iterator it = find(value.first);
				if(it != _end)
					return (it);
				(void)hint;
				_insert(_root, value);
				if (_root == _end) 
				{
					_root = _last_inserted;
					_root->right = _end;
					_end->parent = _root;
				}
				return (_last_inserted);
			}
			T& at( const Key& key )
			{
				const_iterator it = begin();
				const_iterator ite = end();
				while(it != ite)
				{
					if(it._elem->content.first == key)
						return (it._elem->content.second);
					it++;
				}
				throw std::out_of_range("map::at");
			}	
			const T& at( const Key& key ) const
			{
				const_iterator it = begin();
				const_iterator ite = end();
				while(it != ite)
				{
					if(it._elem->content.first == key)
						return (it._elem->content.second);
					it++;
				}
				throw std::out_of_range("map::at");
			}
			T& operator[]( const Key& key )
			{
				iterator it = find(key);
				if(it == _end)
					return insert(ft::make_pair(key, T())).first->second;
				return (it->second);	
			}
			void clear()
			{
				if (this->empty())
					return;
				_delete_map(_root);
				_root = _end;
				_end->parent = NULL;
				_last_inserted = NULL;
				_size = 0;
			}
			void erase( iterator pos )
			{
				erase(pos._elem->content.first);
			}
			void erase( iterator first, iterator last )
			{	
				while(first != last)
					erase((first++)._elem->content.first);
			}
			size_type erase( const key_type& key )
			{
				size_type old_size = _size;
				_delete_node(_root, key);
				return (old_size != _size);
			}
			iterator find( const Key& key )
			{
				node * tree = this->_search(_root, key);;
				return (iterator(tree));
			}
			const_iterator find( const Key& key ) const
			{
				node * tree = this->_search(_root, key);
				return (const_iterator(tree));
			}
			iterator begin()
			{
				node * start = _root;
				while(start && start->left)
					start = start->left;
				return (iterator(start));
			}
			const_iterator begin() const
			{
				node * start = _root;
				while(start && start->left)
					start = start->left;
				return (const_iterator(start));
			}
			iterator end()
			{
				return (iterator(_end));
			}
			const_iterator end() const
			{
				return (const_iterator(_end));
			}
			reverse_iterator rbegin()
			{
				return( reverse_iterator(end()));
			}
			const_reverse_iterator rbegin() const
			{
				return( const_reverse_iterator(end()));
			}
			reverse_iterator rend()
			{
				return( reverse_iterator(begin()));
			}
			const_reverse_iterator rend() const
			{
				return( const_reverse_iterator(begin()));
			}
			map& operator=( const map& other )
			{
				clear();
				_free_node(_end);
				_init_constructor(other._comp, other._alloc);
				this->_als = other._als;

				const_iterator it = other.begin();
				const_iterator ite = other.end();
				while(it != ite)
				{
					this->insert(*it);
					it++;
				}
				return (*this);
			}
			size_type count( const Key& key ) const
			{
				if(_search(_root, key) == _end)
					return (0);
				return (1);
			}
			ft::pair<iterator,iterator> equal_range( const Key& key )
			{
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}
			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
			{
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}
			iterator lower_bound( const Key& key )
			{
				iterator it = begin();
				iterator ite = end();
				while(it != ite)
				{
					if(!_comp(it->first, key))
						return (it--);
					it++;
				}
				return (it);
			}
			const_iterator lower_bound( const Key& key ) const
			{
				const_iterator it = begin();
				const_iterator ite = end();
				while(it != ite)
				{
					if(!_comp(it->first, key))
						return (it--);
					it++;
				}
				return (it);
			}
			iterator upper_bound( const Key& key )
			{
				iterator it = begin();
				iterator ite = end();
				while(it != ite)
				{
					if(_comp(key, it->first))
						return (it--);
					it++;
				}
				return (it);
			}
			const_iterator upper_bound( const Key& key ) const
			{
				const_iterator it = begin();
				const_iterator ite = end();
				while(it != ite)
				{
					if(_comp(key, it->first))
						return (it--);
					it++;
				}
				return (it);
			}
			key_compare key_comp() const
			{
				return (_comp);
			}
			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
				public:
					value_compare (Compare c) : comp(c) {}
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
			};
			value_compare value_comp() const
			{
				return (value_compare(_comp));
			}
			void swap( map& other )
			{
				node* tmp_root = other._root;
				typename Allocator::template rebind<node>::other tmp_als = other._als;
				size_type tmp_size = other._size;
				Allocator tmp_alloc = other._alloc;
				Compare tmp_comp = other._comp;
				node* tmp_end = other._end;
				node * tmp_last_inserted = other._last_inserted;

				other._root = this->_root;
				other._als = this->_als;
				other._size = this->_size;
				other._alloc = this->_alloc;
				other._comp = this->_comp;
				other._end = this->_end;
				other._last_inserted = this->_last_inserted;

				this->_root = tmp_root;
				this->_als = tmp_als;
				this->_size = tmp_size;
				this->_alloc = tmp_alloc;
				this->_comp = tmp_comp;
				this->_end = tmp_end;
				this->_last_inserted = tmp_last_inserted;
			}
		private:
			node* _search(node *node, const Key & key) const
			{
				if(node == _end || node == NULL)
					return (_end);
				if(node->content.first == key)
					return (node);
				if(_comp(node->content.first, key))
					return(_search(node->right, key));
				else
					return(_search(node->left, key));
			}
			node* _insert(node *root, const value_type & value)
			{
				if(!root || root == _end)
				{
					node * ret = _construct_node(value);
					_last_inserted = ret;
					if(root == _end)
					{
						ret->right = _end;
						_end->parent = ret;
					}
					_size++;
					return (ret);
				}
				if(_comp(value.first, root->content.first))
				{
					root->left = _insert(root->left, value);
					root->left->parent = root;
				}
				else
				{
					root->right = _insert(root->right, value);
					root->right->parent = root;
				}
				return (root);
			}
			node * _construct_node(const value_type & content)
			{
				node * new_node = _als.allocate(1);
				_alloc.construct(&new_node->content, content);
				new_node->parent = NULL;
				new_node->left = NULL;
				new_node->right = NULL;
				return (new_node);
			}
			void _free_node(node *node)
			{
				if(node == NULL)
					return;
				_alloc.destroy(&node->content);
				_als.deallocate(node, 1);
			}
			node *_delete_node(node * root, key_type const & key)
			{
				if(root == NULL || root == _end)
					return root;
				if(_comp(key, root->content.first))
				{
					root->left = _delete_node(root->left, key);
					return (root);
				}
				else if(_comp(root->content.first, key))
				{
					root->right = _delete_node(root->right, key);
					return (root);
				}
				_size -= 1;
				if(root->right == NULL && root->left == NULL)
				{
					if (root == _root)
						_root = _end;
					_free_node(root);
					return (NULL);
				}
				else if(root->left == NULL || root->right == NULL)
				{
					node * tmp;
					if(root->left == NULL)
						tmp = root->right;
					else
						tmp = root->left;
					tmp->parent = root->parent;
					if (root == _root)
						_root = tmp;
					_free_node(root);
					return tmp;
				}	
				else
				{
					node* replace_parent = root;
					node* replace = root->right;

					while (replace->left != NULL) 
					{
						replace_parent = replace;
						replace = replace->left;
					}
					if(replace_parent != root)
						replace_parent->left = replace->right;
					else
						replace_parent->right = replace->right;
					replace->right = root->right;
					if(replace->right)
						replace->right->parent = replace;
					replace->left = root->left;
					if(replace->left)
						replace->left->parent = replace;
					replace->parent = root->parent;
					if(root == _root)
						_root = replace;
					_free_node(root);
					return (replace);
				}	
			}
			void _delete_map(node * node)
			{
				if(node == NULL)
					return;
				if(node->left)
					_delete_map(node->left);
				if(node->right && node->right != _end)
					_delete_map(node->right);
				_free_node(node);
			}
			void _init_constructor(const Compare& comp,
			const Allocator& alloc) 
			{
				_comp = comp;
				_alloc = alloc;
				_root = _construct_node(ft::make_pair(key_type(), mapped_type()));;;
				_last_inserted = NULL;
				_end = _root;
				_size = 0;
			}
			node* _root;
			typename Allocator::template rebind<node>::other _als;
			size_type _size;
			Allocator _alloc;
			Compare _comp;
			node* _end;
			node * _last_inserted;
	};
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if(!(lhs == rhs))
			return (true);
		return (false);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs,
           ft::map<Key,T,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}
}
#endif