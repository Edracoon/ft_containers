#ifndef BTREE_HPP
# define BTREE_HPP

template <class Tp, class Compare, class Allocator>
class btree
{
	public:
			typedef Tp				value_type;
			typedef Compare			value_compare;
			typedef Allocator		allocator_type;
	protected:
			Compare			_comp;
			allocator_type	_alloc;

			value_type		_value;
			btree*			_right;
			btree*			_left;


};

#endif