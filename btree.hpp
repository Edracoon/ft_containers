#ifndef BTREE_HPP
# define BTREE_HPP


namespace ft {

template <class T>
class	node
{
	public:
			typedef	T			pair;

			node(const pair& Value) : value(Value), parent(NULL), right(NULL), left(NULL) { }

			pair			value; // pair
			node*			parent;
			node*			right;
			node*			left;
};

template <class Pair, class Compare, class Alloc>
class btree
{
	public:
			typedef Pair												pair;
			typedef Compare												value_compare;
			
			typedef	node<pair>											node;
			typedef typename Alloc::template rebind< node >::other		allocator_type;
			
			typedef	ft::bidirectional_iterator<node>					iterator;
			typedef	ft::const_bidirectional_iterator<const node>		const_iterator;
			typedef	ft::reverse_iterator<iterator>						reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>				const_reverse_iterator;
	public:
			Compare						_comp;
			allocator_type				_alloc;
			node*						_root;
			node*						_last;
	public:

			// === CONSTRUCTOR === //
			btree( void ) : _comp(Compare()), _alloc(allocator_type()), _root(NULL) { }
			btree(Compare	comp) : _comp(comp), _alloc(allocator_type()), _root(NULL) { }
			template <class InputIterator>
			btree(InputIterator first, InputIterator last, Compare comp, allocator_type alloc) : _comp(comp), _alloc(alloc), _root(NULL)
			{
				for ( ; first != last ; first++)
					btree_insert(&_root, *first);
			}

	private:
			node*	_get_last() const {
				node	*temp = _root;
				node	*last;
				while (temp != NULL)
				{
					last	= temp;
					temp	= temp->right;
				}
				return (last);
			}

	public:
			iterator	begin() {
				node *temp = _root;
				while (temp->left != NULL)
					temp = temp->left;
				return (iterator(temp, NULL));
			}
			const_iterator	begin() const {
				node *temp = _root;
				while (temp->left != NULL)
					temp = temp->left;
				return (const_iterator(temp, _get_last()));
			}

			iterator	end() {
				node *temp = _root;
				while (temp != NULL)
				{
					_last	= temp;
					temp	= temp->right;
				}
				return (iterator(temp, _last));
			}
			const_iterator	end() const {
				node *temp = _root;
				while (temp != NULL)
				{
					temp	= temp->right;
				}
				return (const_iterator(temp, _get_last()));
			}

			// === INSERT === //
			iterator btree_insert(node **root, const pair& value)
			{
				if (*root == NULL)
				{
					*root = _alloc.allocate(1);
					_alloc.construct(*root, value);
					(*root)->parent = NULL;
					return iterator(*root, NULL);
				}
				while ((*root) != NULL)
				{
					// si les key sont egales, ne pas insert
					if (!_comp((*root)->value.first, value.first) && !_comp(value.first, (*root)->value.first))
						return (iterator(*root, NULL));
					// left insert
					if ((*root)->left == NULL && !(_comp((*root)->value.first, value.first)))
					{
						(*root)->left = _alloc.allocate(1);
						_alloc.construct((*root)->left, value);
						(*root)->left->parent = *root;
						return iterator((*root)->left, NULL);
					}
					// right insert
					if ((*root)->right == NULL && (_comp((*root)->value.first, value.first)))
					{
						(*root)->right = _alloc.allocate(1);
						_alloc.construct((*root)->right, value);
						(*root)->right->parent = *root;
						return iterator((*root)->right, NULL);
					}
					if (_comp((*root)->value.first, value.first))
						root = &((*root)->right);
					else if (!_comp((*root)->value.first, value.first))
						root = &((*root)->left);
				}
				return iterator(NULL, NULL);
			}

			// === SIZE ===
			int	size(node *root) const
			{
				if (root == NULL)
					return (0);
				return (size((root->left)) + 1 + size((root->right)));
			}

			// === CLEAR === //
			void	btree_clear(node *root)
			{
				if (root->left == NULL && root->right == NULL)
				{
					_alloc.destroy(root);
					_alloc.deallocate(root, 1);
					root = NULL;
					return ;
				}
				if (root->left)
					btree_clear((root->left));
				if (root->right)
					btree_clear((root->right));
			}

			// === FIND === //
			pair & btree_find(node *root, pair data_ref)
			{
				pair	ret;
				if (root == NULL)
					return (NULL);

				ret = btree_find(root->left, data_ref);
				if (ret == NULL && !(_comp(data_ref.first, root->value.first)) && !(root->value.first, _comp(data_ref.first)))	// std::less<key>
					return (root->value);
				if (ret == NULL)
					ret = btree_find(root->right, data_ref);
				return (ret);
			}

			// delete => trouver la valeur a delete puis aller dans le subtree de gauche et chercher la plus grande valeure
			// 			puis la mettre a la place de la node deleted

			// === LEVEL COUNT === //
			int btree_level_count(node *root)
			{
				pair	retleft;
				pair	retright;

				if (root == NULL)
					return (0);

				retleft = btree_level_count(root->left);
				retright = btree_level_count(root->right);

				return ( (_comp(retleft, retright) == false ? retleft : retright) + 1 );
			}

			void	btree_display(node *root, int space)
			{
				int	i = 5;

				if (root == NULL)
					return ;
				space += 5;
				btree_display(root->right, space);
				while (i++ < space)
					printf(" ");
				printf("[%s - %d]\n", root->value.first.c_str(), root->value.second);
				btree_display(root->left, space);
			}
};

}

#endif