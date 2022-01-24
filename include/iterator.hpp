#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "utils.hpp"
#include <cstddef>

namespace ft
{
	template < class T >
	struct ConstMapIterator;
	template < class T >
	struct ConstVectorIterator;
	struct input_iterator_tag { };	
	struct output_iterator_tag { };	
	struct forward_iterator_tag : public input_iterator_tag { };	
	struct bidirectional_iterator_tag : public forward_iterator_tag { };	
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };	
	struct contiguous_iterator_tag: public random_access_iterator_tag { };
	template <typename Iter>
	size_t it_dist(Iter it, Iter ite)
	{
		size_t ret = 0;
		while(it != ite)
		{
			it++;
			ret++;
		}
		return (ret);
	}
	template<
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T& >
	struct iterator
	{
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template< class Iter >
	struct iterator_traits
	{
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type; 	
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template< class T >
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type; 	
		typedef T* pointer;
		typedef T& reference;
		typedef ft::random_access_iterator_tag iterator_category;
	};

	template < class T >
	struct VectorIterator : public ft::iterator<
									ft::random_access_iterator_tag,
									T,
									std::ptrdiff_t,
									T*,
									T&>
	{
		public:
			typedef std::ptrdiff_t difference_type;
			typedef T value_type; 	
			typedef T* pointer;
			typedef T& reference;
			typedef ft::random_access_iterator_tag iterator_category;
			VectorIterator() {};
			VectorIterator(T *elem) {_elem = elem;};
			virtual ~VectorIterator() {};
			VectorIterator(const VectorIterator & to_copy) : _elem(to_copy._elem)
			{

			}
			VectorIterator & operator=(const VectorIterator & to_copy)
			{
				_elem = to_copy._elem;
				return (*this);
			}
			bool operator==(const VectorIterator & cmp) const
			{
				if(this->_elem == cmp._elem)
					return (1);
				return (0);
			}
			bool operator==(const ConstVectorIterator<T> & cmp) const
			{
				if(this->_elem == cmp._elem)
					return (1);
				return (0);
			}
			bool operator!=(const VectorIterator & cmp) const
			{
				if(this->_elem != cmp._elem)
					return (1);
				return (0);
			}
			bool operator!=(const ConstVectorIterator<T> & cmp) const
			{
				if(this->_elem != cmp._elem)
					return (1);
				return (0);
			}
			bool operator>=(const VectorIterator & cmp) const
			{
				if(this->_elem >= cmp._elem)
					return (1);
				return (0);
			}
			bool operator>=(const ConstVectorIterator<T> & cmp) const
			{
				if(this->_elem >= cmp._elem)
					return (1);
				return (0);
			}
			bool operator<=(const VectorIterator & cmp) const
			{
				if(this->_elem <= cmp._elem)
					return (1);
				return (0);
			}
			bool operator<=(const ConstVectorIterator<T> & cmp) const
			{
				if(this->_elem <= cmp._elem)
					return (1);
				return (0);
			}
			bool operator<(const VectorIterator & cmp) const
			{
				if(this->_elem < cmp._elem)
					return (1);
				return (0);
			}
			bool operator<(const ConstVectorIterator<T> & cmp) const
			{
				if(this->_elem < cmp._elem)
					return (1);
				return (0);
			}
			bool operator>(const VectorIterator & cmp) const
			{
				if(this->_elem > cmp._elem)
					return (1);
				return (0);
			}
			bool operator>(const ConstVectorIterator<T> & cmp) const
			{
				if(this->_elem > cmp._elem)
					return (1);
				return (0);
			}
			pointer operator->() const
			{
				return (_elem);
			}
			reference operator*() const
			{
				return (*_elem);
			}
			VectorIterator &operator++()
			{
				_elem++;
				return (*this);
			}
			VectorIterator operator++(int)
			{
				VectorIterator old = *this;
				operator++();
				return(old);
			}
			VectorIterator &operator--()
			{
				_elem--;
				return (*this);
			}
			VectorIterator operator--(int)
			{
				VectorIterator old = *this;
				operator--();
				return(old);
			}
			VectorIterator operator+(difference_type nbr)
			{
				return(VectorIterator(this->_elem + nbr));
			}
			friend VectorIterator operator+(difference_type nbr, VectorIterator & rhs)
			{
				return(VectorIterator(rhs._elem + nbr));
			}
			VectorIterator operator-(difference_type nbr)
			{
				return(VectorIterator(this->_elem - nbr));
			}
			difference_type operator-(VectorIterator & rhs)
			{
				return(this->_elem - rhs._elem);
			}
			difference_type operator-(ConstVectorIterator<T> & rhs)
			{
				return(this->_elem - rhs._elem);
			}
			VectorIterator operator-=(difference_type nbr)
			{
				this->_elem -= nbr;
				return(*this);
			}
			VectorIterator operator+=(difference_type nbr)
			{
				this->_elem += nbr;
				return(*this);
			}
			reference operator[](difference_type nbr) const
			{
				return(this->_elem[nbr]);
			}
			T *_elem;
	};
	template < class T >
	struct ConstVectorIterator : public ft::iterator<
									ft::random_access_iterator_tag,
									T,
									std::ptrdiff_t,
									T*,
									T&>
	{
		public:
			typedef std::ptrdiff_t difference_type;
			typedef const T value_type; 	
			typedef const T* pointer;
			typedef const T& reference;
			typedef ft::random_access_iterator_tag iterator_category;
			ConstVectorIterator() {};
			ConstVectorIterator(T *elem) {_elem = elem;};
			virtual ~ConstVectorIterator() {};
			ConstVectorIterator(const ConstVectorIterator & to_copy) : _elem(to_copy._elem)
			{

			}
			ConstVectorIterator(VectorIterator<T> const & to_copy) : _elem(to_copy._elem)
			{

			}
			ConstVectorIterator & operator=(const ConstVectorIterator & to_copy)
			{
				_elem = to_copy._elem;
				return (*this);
			}
			bool operator==(const ConstVectorIterator & cmp) const
			{
				if(this->_elem == cmp._elem)
					return (1);
				return (0);
			}
			bool operator!=(const ConstVectorIterator & cmp) const
			{
				if(this->_elem != cmp._elem)
					return (1);
				return (0);
			}
			bool operator>=(const ConstVectorIterator & cmp) const
			{
				if(this->_elem >= cmp._elem)
					return (1);
				return (0);
			}
			bool operator<=(const ConstVectorIterator & cmp) const
			{
				if(this->_elem <= cmp._elem)
					return (1);
				return (0);
			}
			bool operator<(const ConstVectorIterator & cmp) const
			{
				if(this->_elem < cmp._elem)
					return (1);
				return (0);
			}
			bool operator>(const ConstVectorIterator & cmp) const
			{
				if(this->_elem > cmp._elem)
					return (1);
				return (0);
			}
			pointer operator->() const
			{
				return (_elem);
			}
			reference operator*() const
			{
				return (*_elem);
			}
			ConstVectorIterator &operator++()
			{
				_elem = _elem + 1;
				return (*this);
			}
			ConstVectorIterator operator++(int)
			{
				ConstVectorIterator old = *this;
				operator++();
				return(old);
			}
			ConstVectorIterator &operator--()
			{
				_elem = _elem - 1;
				return (*this);
			}
			ConstVectorIterator operator--(int)
			{
				ConstVectorIterator old = *this;
				operator--();
				return(old);
			}
			ConstVectorIterator operator+(difference_type nbr)
			{
				return(ConstVectorIterator(this->_elem + nbr));
			}
			friend ConstVectorIterator operator+(difference_type nbr, ConstVectorIterator & rhs)
			{
				return(ConstVectorIterator(rhs._elem + nbr));
			}
			ConstVectorIterator operator-(difference_type nbr)
			{
				return(ConstVectorIterator(this->_elem - nbr));
			}
			difference_type operator-(ConstVectorIterator & rhs)
			{
				return(this->_elem - rhs._elem);
			}
			difference_type operator-(const ConstVectorIterator & rhs) const
			{
				return(this->_elem - rhs._elem);
			}
			difference_type operator-(const VectorIterator<T> & rhs)
			{
				return(this->_elem - rhs._elem);
			}
			ConstVectorIterator operator-=(difference_type nbr)
			{
				this->_elem -= nbr;
				return(*this);
			}
			ConstVectorIterator operator+=(difference_type nbr)
			{
				this->_elem += nbr;
				return(*this);
			}
			reference operator[](int nbr) const
			{
				return*(this->_elem + nbr);
			}
			T *_elem;
	};
	template < class Iter >
	struct reverse_iterator : public ft::iterator<
					typename ft::iterator_traits<Iter>::iterator_category
					, typename ft::iterator_traits<Iter>::value_type
					, typename ft::iterator_traits<Iter>::difference_type
					, typename ft::iterator_traits<Iter>::pointer
					, typename ft::iterator_traits<Iter>::reference >
	{
		public:
			typedef Iter iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer pointer;
			typedef typename ft::iterator_traits<Iter>::reference reference;
			reverse_iterator() : current(NULL)
			{

			}
			explicit reverse_iterator( iterator_type x ) : current(x)
			{

			}
			template< class U >
			reverse_iterator( const reverse_iterator<U>& other ) : current(other.base())
			{

			}
			iterator_type base() const
			{
				return (current);
			}
			reverse_iterator& operator++()
			{
				current--;
				return (*this);
			}
			reverse_iterator& operator--()
			{
				current++;
				return (*this);
			}
			reverse_iterator operator++( int )
			{
				reverse_iterator copy;

				copy = *this;
				operator++();
				return (copy);
			}
			reverse_iterator operator--( int )
			{
				reverse_iterator copy;

				copy = *this;
				operator--();
				return (copy);
			}
			reverse_iterator operator+( difference_type n ) const
			{
				return(reverse_iterator(base() - n));
			}
			reverse_iterator operator-( difference_type n ) const
			{
				return(reverse_iterator(base() + n));
			}
			reverse_iterator& operator+=( difference_type n )
			{
				current = current - n;
				return (*this);
			}
			reverse_iterator& operator-=( difference_type n )
			{
				current = current + n;
				return (*this);
			}
			reference operator*() const
			{
				iterator_type tmp = current;
				return (*--tmp);
			}
			pointer operator->() const
			{
				return &(operator*());
			}
			reference operator[]( difference_type n ) const
			{
				iterator_type ret = base();
				return (ret[-n -1]);
			}
			template <class U>
			difference_type		operator-(const reverse_iterator<U> &u)
			{
				return u.base().operator-(this->current);
			}
			friend reverse_iterator	operator+(difference_type n, const reverse_iterator &rhs)
			{ 
				return rhs.operator+(n); 
			}
			protected:
				iterator_type current;
	};
	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() == rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() != rhs.base());	
	}
	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() > rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() < rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	}
	template < class T >
	struct MapIterator : public ft::iterator<
									ft::bidirectional_iterator_tag,
									T,
									std::ptrdiff_t,
									T*,
									T&>
	{
		public:
			typedef std::ptrdiff_t difference_type;
			typedef T value_type; 	
			typedef T* pointer;
			typedef T& reference;
			typedef node<T> node;
			typedef ft::bidirectional_iterator_tag iterator_category;
			MapIterator() : _elem(NULL) {}
			MapIterator(node *elem) {_elem = elem;}
			virtual ~MapIterator() {}
			MapIterator(MapIterator const & to_copy)
			{
				_elem = to_copy._elem;
			}
			MapIterator & operator=(MapIterator const & to_copy)
			{
				_elem = to_copy._elem;
				return (*this);
			}
			bool operator==(MapIterator const & cmp) const
			{
				if(this->_elem == cmp._elem)
					return (1);
				return (0);
			}
			bool operator!=(MapIterator const & cmp) const
			{
				if(this->_elem != cmp._elem)
					return (1);
				return (0);
			}
			pointer operator->() const
			{
				return &(_elem->content);
			}
			reference operator*() const
			{
				return (_elem->content);
			}
			MapIterator &operator++()
			{
				_elem = _next(_elem);
				return (*this);
			}
			MapIterator operator++(int)
			{
				MapIterator old = *this;
				operator++();
				return(old);
			}
			MapIterator &operator--()
			{
				_elem = _prev(_elem);
				return (*this);
			}
			MapIterator operator--(int)
			{
				MapIterator old = *this;
				operator--();
				return(old);
			}
			node *_elem;
	};
	template < class T >
	struct ConstMapIterator : public ft::iterator<
									ft::bidirectional_iterator_tag,
									T,
									std::ptrdiff_t,
									T*,
									T&>
	{
		public:
			typedef std::ptrdiff_t difference_type;
			typedef const T value_type; 	
			typedef const T* pointer;
			typedef const T& reference;
			typedef node<T> node;
			typedef ft::bidirectional_iterator_tag iterator_category;
			ConstMapIterator() : _elem(NULL) {}
			ConstMapIterator(node *elem) {_elem = elem;}
			virtual ~ConstMapIterator() {}
			ConstMapIterator(ConstMapIterator const & to_copy)
			{
				_elem = to_copy._elem;
			}
			ConstMapIterator(MapIterator<T> const & to_copy) : _elem(to_copy._elem)
			{

			}
			ConstMapIterator & operator=(ConstMapIterator const & to_copy)
			{
				_elem = to_copy._elem;
				return (*this);
			}
			bool operator==(ConstMapIterator const & cmp) const
			{
				if(this->_elem == cmp._elem)
					return (1);
				return (0);
			}
			bool operator!=(ConstMapIterator const & cmp) const
			{
				if(this->_elem != cmp._elem)
					return (1);
				return (0);
			}
			pointer operator->() const
			{
				return &(_elem->content);
			}
			reference operator*() const
			{
				return (_elem->content);
			}
			ConstMapIterator &operator++()
			{
				_elem = _next(_elem);
				return (*this);
			}
			ConstMapIterator operator++(int)
			{
				ConstMapIterator old = *this;
				operator++();
				return(old);
			}
			ConstMapIterator &operator--()
			{
				_elem = _prev(_elem);
				return (*this);
			}
			ConstMapIterator operator--(int)
			{
				ConstMapIterator old = *this;
				operator--();
				return(old);
			}
			node *_elem;
	};
}
#endif