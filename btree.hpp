#ifndef BTREE_HPP
# define BTREE_HPP

template <class Tp>
class	node
{
	Tp				value;
	node*			right;
	node*			left;
};

template <class Tp, class Compare, class Allocator>
class btree
{
	public:
			typedef Tp				value_type;
			typedef Compare			value_compare;
			typedef Allocator		allocator_type;
	protected:
			Compare					_comp;
			allocator_type			_alloc;
			node<value_type>*		root;
	public:
			btree(Compare	comp, allocator_type alloc) : _comp(comp), _alloc(alloc) {
				root = new node<value_type>;
				root->right = NULL;
				root->left = NULL;
			}

};

#endif