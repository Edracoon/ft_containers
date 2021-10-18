/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:15:12 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/18 20:12:09 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_HPP
# define BTREE_HPP

# include "iterator.hpp"
# include "node.hpp"

# define BLACK	0
# define RED	1

namespace ft {

	template <class T, class Compare, class Alloc>
	class btree
	{
		public:
				typedef	T													value_type;
				typedef	size_t												size_type;
				typedef Compare												value_compare;
				
				typedef	node<const value_type>								const_node;
				typedef	node<value_type>									node;

				typedef node*												node_ptr;
				typedef const_node*											const_node_ptr;

				typedef typename T::first_type								key_type;
				typedef typename Alloc::template rebind< node >::other		allocator_type;
				
				typedef	ft::bidirectional_iterator<value_type>				iterator;
				typedef	ft::const_bidirectional_iterator<value_type>		const_iterator;
				typedef	ft::reverse_iterator<iterator>						reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		public:
				value_compare				_comp;
				allocator_type				_alloc;
				node_ptr					_root;
				node_ptr					NIL;
		
		public:

				// === CONSTRUCTOR === //
				btree( void ) : _comp(value_compare()), _alloc(allocator_type()), _root(NULL) {
					NIL = _alloc.allocate(1);
					_alloc.construct(NIL, value_type());
					NIL->color	= BLACK;
					_root = NIL;
				}
				btree(value_compare	comp) : _comp(comp), _alloc(allocator_type()), _root(NULL) {
					NIL = _alloc.allocate(1);
					_alloc.construct(NIL, value_type());
					NIL->color	= BLACK;
					_root = NIL;
				}
				template <class InputIterator>
				btree(InputIterator first, InputIterator last, value_compare comp, allocator_type alloc)
					: _comp(comp), _alloc(alloc), _root(NULL) {
					NIL = _alloc.allocate(1);
					_alloc.construct(NIL, value_type());
					NIL->color	= BLACK;
					_root = NIL;
					for ( ; first != last ; first++)
						btree_insert(&_root, *first);
				}

		private:
				void create_new_node(node_ptr* node, node_ptr* root,  const T& value)
				{
					*node = _alloc.allocate(1);
					_alloc.construct(*node, value);

					(*node)->parent		= *root;
					(*node)->color		= RED;
					(*node)->NIL		= NIL;
					(*node)->left		= NIL;
					(*node)->right		= NIL;
				}

				// === UTILS === // 
				node_ptr	_get_last() const {
					node_ptr	temp = _root;
					if (temp != NIL)
						while (temp->right != NIL)
							temp	= temp->right;
					return (temp);
				}
			
				node_ptr	_get_inorder_successor(node_ptr right) const {
					node_ptr	temp = right;
					while (temp != NIL && temp->left != NIL) {
						temp = temp->left;
					}
					return (temp);
				}

		public:
				iterator	begin() {
					node_ptr	temp = _root;
					if (_root != NIL) {
						while (temp->left != NIL)
							temp = temp->left;
					}
					return (iterator(temp, _get_last()));
				}
				const_iterator	begin() const {
					const_node_ptr	temp = reinterpret_cast<const_node_ptr>(_root);
					if (_root != NIL) {
						while (temp->left != reinterpret_cast<const_node_ptr>(NIL))
							temp = temp->left;
					}
					return (const_iterator(temp, reinterpret_cast<const_node_ptr>(_get_last())));
				}

				iterator	end() {
					return (iterator(NIL, _get_last()));
				}
				const_iterator	end() const {
					return (const_iterator(reinterpret_cast<const_node_ptr>(NIL), reinterpret_cast<const_node_ptr>(_get_last())));
				}

				// === max_size === // 
				size_type max_size( void ) const {
					if (sizeof(node) == 1)
						return (_alloc.max_size() / 2);
					return (_alloc.max_size());
				}
				// === INSERT === //
				iterator btree_insert(node_ptr *root, const T& value)
				{
					if (*root == NIL)
					{
						*root = _alloc.allocate(1);
						_alloc.construct(*root, value);
						(*root)->color	= BLACK;
						(*root)->parent = NIL;
						(*root)->left	= NIL;
						(*root)->right	= NIL;
						return iterator(*root, NIL);
					}
					while ((*root) != NIL)
					{
						// si les key sont egales, ne pas insert
						if (!_comp((*root)->value.first, value.first) && !_comp(value.first, (*root)->value.first))
							return (iterator(*root, NIL));
						// left insert
						if ((*root)->left == NIL && !(_comp((*root)->value.first, value.first)))
						{
							create_new_node(&((*root)->left), root, value);
							return iterator((*root)->left, NIL);
						}
						// right insert
						if ((*root)->right == NIL && (_comp((*root)->value.first, value.first)))
						{
							create_new_node(&((*root)->right), root, value);
							return iterator((*root)->right, NIL);
						}
						if (_comp((*root)->value.first, value.first))
							root = &((*root)->right);
						else if (!_comp((*root)->value.first, value.first))
							root = &((*root)->left);
					}
					return iterator(NIL, NIL);
				}

				// === DELETE ===
				node_ptr delete_node(node_ptr root, const key_type& k)
				{
					if (root == NIL)
						return (root);

					if (_comp(k, (root)->value.first))
						root->left = delete_node(root->left, k);
					else if (_comp(root->value.first, k))
						root->right = delete_node(root->right, k);

					else // Ici on a trouvé la node a delete car K est ni inferieur ni superieur
					{
						if (root->right == NIL && root->left == NIL)	// Si c'est une feuille
						{
							_alloc.destroy(root);
							root = NIL;
							return NIL;
						}
						else if (root->left == NIL)		// Si il a qu'un seul enfant right
						{
							node_ptr	temp = root->right;
							_alloc.destroy(root);
							root = NIL;
							return (temp);
						}
						else if (root->right == NIL)		// Si il a qu'un seul enfant left
						{
							node_ptr	temp = root->left;
							_alloc.destroy(root);
							root = NIL;
							return (temp);
						}
						else if (root->right != NIL && root->left != NIL)
						{
							node_ptr	temp		= _get_inorder_successor(root->right);	// si la node a deux enfants prendre le inorder successor de root

							node_ptr	tempright	= root->right;
							node_ptr	templeft	= root->left;
							node_ptr	tempparent	= root->parent;

							_alloc.destroy(root);
							root = NIL;

							_alloc.construct(root, temp->value);
							root->right		= tempright;
							root->left		= templeft;
							root->parent	= tempparent;
							root->NIL		= NIL;

							root->right	= delete_node(root->right, temp->value.first);
						}
					}
					return (root);
				}

				// === SIZE ===
				int	size(node_ptr root) const
				{
					// std::cout << root << std::endl;
					if (root == NIL)
						return (0);
					
					return (size((root->left)) + 1 + size((root->right)));
				}

				// === CLEAR === //
				void	btree_clear(node *root)
				{
					if (root == NIL)
						return ;

					btree_clear((root->left));
					btree_clear((root->right));
					if (root->left == NIL && root->right == NIL)
					{
						_alloc.destroy(root);
						_alloc.deallocate(root, 1);
						root = NIL;
					}
				}

				// === FIND === //
				T* btree_find_pair(node_ptr root, const key_type& k) const
				{
					T*	ret;
					if (root == NIL)
						return (NULL);

					ret = btree_find_pair(root->left, k);
					if (ret == NULL && !_comp(k, root->value.first) && !_comp(root->value.first, k))	// std::less<key>
						return &(root->value);
					if (ret == NULL)
						ret = btree_find_pair(root->right, k);
					return (ret);
				}
				
				node_ptr btree_find_node(node_ptr root, const key_type& k) const
				{
					node_ptr	ret;
					if (root == NIL)
						return (NIL);

					ret = btree_find_node(root->left, k);
					if (ret == NIL && !_comp(k, root->value.first) && !_comp(root->value.first, k))	// std::less<key>
						return (root);
					if (ret == NIL)
						ret = btree_find_node(root->right, k);
					return (ret);
				}

				// delete => trouver la valeur a delete puis aller dans le subtree de gauche et chercher la plus grande valeure
				// 			puis la mettre a la place de la node deleted

				// === LEVEL COUNT === //
				int btree_level_count(node_ptr root)
				{
					T	retleft;
					T	retright;

					if (root == NIL)
						return (0);

					retleft = btree_level_count(root->left);
					retright = btree_level_count(root->right);

					return ( (_comp(retleft, retright) == false ? retleft : retright) + 1 );
				}

				void	btree_display(node_ptr root, int space)
				{
					int	i = 5;

					if (root == NIL)
						return ;
					space += 5;
					btree_display(root->right, space);
					while (i++ < space)
						std::cout << " ";
					std::cout << root->value.first << " - " <<  root->value.second << std::endl;
					btree_display(root->left, space);
				}
	};

}

#endif