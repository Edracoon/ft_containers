#ifndef BTREE_HPP
# define BTREE_HPP


namespace ft {

template <class T/*, class Alloc*/>
class	node
{
	public:
			typedef	T			pair;

			node(const pair& Value/*, Alloc alloc*/) : value(Value), right(NULL/*alloc.allocate(1)*/), left(NULL/*alloc.allocate(1)*/) { }

			pair			value; // pair
			node*			right;
			node*			left;
};

template <class Pair, class Compare, class Alloc>
class btree
{
	public:
			typedef Pair												pair;
			typedef Compare												value_compare;
			
			typedef	node<pair /*, typename Alloc::template rebind< node >::other*/ >	node;
			typedef typename Alloc::template rebind< node >::other		allocator_type;
			
			typedef	ft::bidirectional_iterator<node>					iterator;
			typedef	ft::bidirectional_iterator<const node>				const_iterator;
			typedef	ft::reverse_iterator<iterator>						reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>				const_reverse_iterator;
	public:
			Compare						_comp;
			allocator_type				_alloc;
			node*						root;
	public:

			// === CONSTRUCTOR === //
			btree(Compare	comp) : _comp(comp), _alloc(allocator_type())
			{
				root			= NULL;
			}

			iterator	begin() {
				node *temp = root;
				while (temp->left != NULL)
				{
					temp = temp->left;
				}
				return (iterator(temp));
			}

			iterator	end() {
				node *temp = root;
				while (temp != NULL)
				{
					temp = temp->right;
				}
				return (iterator(temp));
			}

			// === INSERT === //
			void btree_insert(node **root, const pair& value)
			{
				if (*root == NULL)
				{
					*root = _alloc.allocate(1);
					_alloc.construct(*root, value);
					return ;
				}
				if (_comp(value.first, (*root)->value.first))
					btree_insert(&((*root)->left), value);
				else
					btree_insert(&((*root)->right), value);
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