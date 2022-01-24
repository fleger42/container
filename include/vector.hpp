#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <iostream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include "iterator.hpp"
#include "lexicographical_compare.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
struct iterator;

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef T& reference;
			typedef T const & const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef ft::VectorIterator<T> iterator;
			typedef ft::ConstVectorIterator<T> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			vector( )	: container(NULL), allocator(Allocator()), _size(0), _capacity(0)
			{

			}
			explicit vector( const Allocator& alloc ) : container(NULL), allocator(alloc), _size(0), _capacity(0)
			{
				
			}
			explicit vector(size_type count, const T & value = T(), const Allocator & alloc = Allocator()) : container(NULL), allocator(alloc), _size(0), _capacity(count)
			{
				if(count)
					container = allocator.allocate(count);
				for(size_type i = 0; i < count; i++)
				{
					allocator.construct(container + i, value);
					_size++;
				}
			}
			template < class InputIt>
			vector( InputIt first, InputIt last, const Allocator & alloc = Allocator(),
			typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL) : container(NULL), allocator(alloc), _size(0), _capacity(0)
			{
				size_type i = 0;
				_capacity = ft::it_dist(first, last);
				if(_capacity)
					container = allocator.allocate(_capacity);
				while(first != last)
				{
					allocator.construct(container + i, *first);
					first++;
					i++;
					_size++;
				}
			}
			vector( const vector & other)
			{
				this->allocator = other.allocator;
				this->_size = other._size;
				this->_capacity = other._size;
				this->container = NULL;
				if(_capacity)
					this->container = this->allocator.allocate(_capacity);
				for(size_type i = 0; i < this->_size; i++)
				{
					allocator.construct(container + i, other.container[i]);
				}
			}
			~vector()
			{
				this->delete_vector(this->container);
				this->_size = 0;
				this->_capacity = 0;
			}
			vector& operator=( const vector& other )
			{
				if(*this == other)
					return (*this);
				this->delete_vector(this->container);
				this->allocator = other.allocator;
				this->_size = other._size;
				this->_capacity = other._capacity;
				this->container = NULL;
				if(_capacity)
					this->container = this->allocator.allocate(_capacity);
				for(size_type i = 0; i < this->_size; i++)
				{
					allocator.construct(container + i, other.container[i]);
				}
				return (*this);
			}
			reference operator[]( size_type pos )
			{
				return (container[pos]);
			}
			const_reference operator[]( size_type pos ) const
			{
				return (container[pos]);
			}
			reference front()
			{
				return (container[0]);
			}
			const_reference front() const
			{
				return (container[0]);
			}
			reference back()
			{
				return (container[_size - 1]);
			}
			const_reference back() const
			{
				return (container[_size - 1]);
			}
			T* data()
			{
				return (container);
			}
			const T* data() const
			{
				return (container);
			}
			size_type size() const
			{
				return (this->_size);
			}
			allocator_type get_allocator() const
			{
				return(allocator);
			}
			void assign( size_type count, const T& value )
			{
				size_type size = count;
				size_type capacity = 0;
				if(_capacity < count)	
					capacity = count;
				else
					capacity = _capacity;			
				T * tmp = NULL;
				tmp = this->allocator.allocate(capacity);
				for(size_type i = 0; i < count; i++)
					allocator.construct(tmp + i, value);
				this->delete_vector(this->container);
				this->container = tmp;
				_capacity = capacity;
				_size = size;
			}
			template< class InputIt >
			void assign( InputIt first, InputIt last,
			typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL)
			{
				size_type i = 0;
				size_type size = ft::it_dist(first, last);
				size_type capacity = 0;
				if(_capacity < size)	
					capacity = size;
				else
					capacity = _capacity;
				T * tmp = NULL;
				if(capacity)
					tmp = this->allocator.allocate(capacity);
				while(first != last)
				{
					allocator.construct(tmp + i, *first);
					first++;
					i++;
				}
				this->delete_vector(this->container);
				this->container = tmp;
				_capacity = capacity;
				_size = size;
			}
			reference at( size_type pos )
			{
				if(pos < 0 || pos >= _size)
				{	
					std::stringstream ss;
					ss << "vector::_M_range_check: __n (which is " << pos << ")"
					<< " >= this->size() (which is " << _size << ")";
					throw std::out_of_range(ss.str());
				}
				return(container[pos]);
			}
			const_reference at( size_type pos ) const
			{
				if(pos < 0 || pos >= _size)
				{	
					std::stringstream ss;
					ss << "vector::_M_range_check: __n (which is " << pos << ")"
					<< " >= this->size() (which is " << _size << ")";
					throw std::out_of_range(ss.str());
				}
				return(container[pos]);
			}
			size_type capacity() const
			{
				return (_capacity);
			}
			bool empty() const
			{
				if(_size == 0)
					return (true);
				else
					return (false);
			}
			size_type max_size() const
			{
				return (allocator.max_size());
			}
			void reserve( size_type new_cap )
			{
				if(new_cap < _capacity)
					return ;
				if(new_cap > max_size())
					throw std::length_error("vector::reserve");
				this->container = reallocate(this->container, new_cap);
			}
			void clear()
			{
				for(size_type i = 0; i < _size; i++)
					allocator.destroy(container + i);
				_size = 0;
			}
			void push_back( const T& value )
			{
				if(_size >= _capacity)
				{
					T *tmp;
					_capacity = (_capacity == 0) ? 1 : _capacity * 2;
					tmp = allocator.allocate(_capacity);
					for(size_type i = 0; i < _size; i++)
					{
						allocator.construct(tmp + i, container[i]);
					}
					delete_vector(this->container);
					container = tmp;
				}
				allocator.construct(container + _size, value);
				_size++;
			}
			void swap( vector& other )
			{

				allocator_type tmp_allocator = this->allocator;
				T * tmp_container = this->container;
				size_type tmp_size = this->_size;
				size_type tmp_capacity = this->_capacity;

				this->allocator = other.allocator;
				this->container = other.container;
				this->_size = other._size;
				this->_capacity = other._capacity;

				other.allocator = tmp_allocator;
				other.container = tmp_container;
				other._size = tmp_size;
				other._capacity = tmp_capacity;
			}
			void resize( size_type count, T value = T() )
			{
				if(count == _size)
					return ;
				if(count < _size)
				{
					for(size_type i = 0; i < _size - count; i++)
						allocator.destroy(container + _size - i - 1);
					_size = count;
				}
				else
				{
					this->container = reallocate(this->container, getCapacity(count));
					for(size_type i = 0; i < count - _size; i++)
						allocator.construct(container + _size + i, value);
					_size = count;
				}
			}
			void pop_back()
			{
				allocator.destroy(container +_size - 1);
				_size--;
			}
			iterator erase( iterator pos )
			{
				iterator it = begin();
				iterator ite = end();
				size_type size = pos - it;
				_size--;
				size_type i = size;
				while(pos != ite)
				{
					allocator.destroy(container + i);
					if(i < _size)
						allocator.construct(container + i, container[i + 1]);
					pos++;
					i++;
				}
				return (iterator(container + size));
			}
			iterator erase( iterator first, iterator last )
			{
				iterator it = begin();
				iterator ite = end();
				size_type size = first - it;
				size_type span = last - first;
				size_type i = size;
				if(span == 0)
					return (last);
				while(first != ite)
				{
					allocator.destroy(container + i);
					if(i + span < _size)
						allocator.construct(container + i, container[i + span]);
					first++;
					i++;
				}
				_size -= span;
				return (iterator(container + size));
			}
			void insert( iterator pos, size_type count, const T& value )
			{
				if(count == 0)
					return ;
				iterator it = begin();
				iterator ite = end();
				size_type size = ite - it;
				size_type iter = ite - pos;
				if(_size + count > _capacity)
				{
					if(_size * 2 > _size + count)
						container = reallocate(container, _size * 2);
					else
						container = reallocate(container, (_capacity + count));
				}
				while(iter)
				{
					if(size + count - 1 < _size && container + size + count - 1)
						allocator.destroy(container + size + count - 1);
					allocator.construct(container + size + count - 1, container[size - 1]);
					size--;
					iter--;
				}
				for(size_type i = count; i; i--)
				{
					//std::cout << "construct container[" << size + i - 1 << "]=" << value << std::endl;
					if(size + i - 1 < _size && container + size + i - 1)
						allocator.destroy(container + size + i - 1);
					allocator.construct(container + size + i - 1, value);
				}
				_size+= count;
			}
			iterator insert( iterator pos, const T& value )// 4 7 6 [3] 9 5 on veut insérer 2  => 4 7 6 2 [3] 9 5
			{
				iterator it = begin();
				iterator ite = end();
				size_type size = ite - it;
				size_type iter = ite - pos;
				if(_size + 1 > _capacity)
					container = reallocate(container, getCapacity(_capacity + 1));
				while(iter)
				{	
					if(size < _size && container + size)
						allocator.destroy(container + size);			
					allocator.construct(container + size, container[size - 1]);
					size--;
					iter--;
				}
				if(size < _size && container + size)
					allocator.destroy(container + size);
				allocator.construct(container + size, value);
				_size++;
				return (iterator(container + size));
			}
			template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last,
			typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL)
			{
				iterator it = begin();
				iterator ite = end();
				size_type size = ite - it;
				size_type iter = ite - pos;
				size_type i;
				size_type count = ft::it_dist(first, last);
				if(_size + count > _capacity)
					container = reallocate(container, getCapacity(_capacity + count));
				while(iter)
				{
					//std::cout << "replace container[" << size + count - 1 << "]=" << container[size + count - 1] << "with container[" << size << "]=" << container[size - 1] << std::endl;
					if(size + count - 1 < _size && container + size + count - 1)
						allocator.destroy(container + size + count - 1);
					allocator.construct(container + size + count - 1, container[size - 1]);
					size--;
					iter--;
				}
				i = 1;
				while(first != last)
				{
					if(size + i - 1 < _size && container + size + i - 1)
						allocator.destroy(container + size + i - 1);
					allocator.construct(container + size + i - 1, *first);
					i++;
					first++;
				}
				_size+= count;
			}
			iterator begin()
			{
				return (iterator(container));
			}
			const_iterator begin() const
			{
				return (const_iterator(container));
			}
			iterator end()
			{
				return(iterator(container + _size));
			}
			const_iterator end() const
			{
				return(const_iterator(container + _size));
			}
			const_reverse_iterator rbegin() const
			{
				return(const_reverse_iterator(end()));
			}
			reverse_iterator rbegin()
			{
				return(reverse_iterator(end()));
			}
			const_reverse_iterator rend() const
			{
				return(const_reverse_iterator(begin()));
			}
			reverse_iterator rend()
			{
				return(reverse_iterator(begin()));
			}
		private:
			size_type getCapacity(size_type size)
			{
				if (size > _capacity && size < (_capacity * 2))
					return (_capacity * 2);
				else if (size > _capacity && size >= (_capacity * 2))
					return (size);
				else
					return (_capacity);
			}
			T *reallocate(T *to_rea, size_type new_capacity)
			{
				T *tmp = NULL;
				if(new_capacity)
					tmp = this->allocator.allocate(new_capacity);
				for(size_type i = 0; i < _size; i++)
				{
					allocator.construct(tmp + i, to_rea[i]);
				}
				delete_vector(to_rea);
				_capacity = new_capacity;
				return (tmp);
			}
			void delete_vector(T *to_rea)
			{
				for(size_type i = 0; i < _size; i++)
					allocator.destroy(to_rea + i);
				if(_capacity)
					allocator.deallocate(to_rea, _capacity);
				to_rea = NULL;
			}
			T *container;
			allocator_type allocator;
			size_type _size;
			size_type _capacity;
			iterator _it;
	};

template< class T, class Alloc >
void swap( vector<T,Alloc>& lhs, vector<T,Alloc>& rhs )
{
	lhs.swap(rhs);
}

template< class T, class Alloc >
bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
{
	if(lhs.size() != rhs.size())
		return (false);
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
{
	if(!(lhs == rhs))
		return (true);
	return (false);
}

template< class T, class Alloc >
bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
{
	if(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
		return (true);
	return (false);
}

template< class T, class Alloc >
bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
{
	if(lhs < rhs || lhs == rhs)
		return (true);
	return (false);
}

template< class T, class Alloc >
bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
{
	if(!(lhs <= rhs))
		return (true);
	return (false);
}

template< class T, class Alloc >
bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
{
	if(lhs > rhs || lhs == rhs)
		return (true);
	return (false);
}
};
#endif