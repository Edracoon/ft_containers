#ifndef BTREE_HPP
# define BTREE_HPP


namespace ft {

template <class T>
class	node
{
	public:
			T				value; // pair
			node*			right;
			node*			left;
};

template <class Pair, class Compare, class Alloc>
class btree
{
	public:
			typedef Pair											pair;
			typedef Compare											value_compare;
			typedef	node<pair>										node;
			typedef typename Alloc::template rebind< node >::other	allocator_type;
	protected:
			Compare						_comp;
			allocator_type				_alloc;
			node*						root;
	public:

			// === CONSTRUCTOR === //
			btree(Compare	comp) : _comp(comp), _alloc(allocator_type())
			{
				root			= NULL;
			}

			node *btree_create_node(pair	value)
			{
				node	*temp = _alloc.allocate(1);

				temp->left		= NULL;
				temp->right		= NULL;
				temp->value		= value;
				
				return (temp);
			}

			// === INSERT === //
			void btree_insert(node **root, pair value)
			{
				if (*root == NULL)
				{
					(*root) = btree_create_node(value);
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
};

}

#endif