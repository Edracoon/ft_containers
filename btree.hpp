/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:15:12 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/18 09:29:21 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_HPP
# define BTREE_HPP

# include "iterator.hpp"
# include "node.hpp"

namespace ft {

				   // T
	template <class T, class Compare, class Alloc>
	class btree
	{
		public:
				typedef Compare												value_compare;
				
				typedef	node<const T>										const_node;
				typedef	node<T>												node;

				typedef node*												node_ptr;
				typedef const_node*											const_node_ptr;

				typedef typename T::first_type								key_type;
				typedef typename Alloc::template rebind< node >::other		allocator_type;
				
				typedef	ft::bidirectional_iterator<T>						iterator;
				typedef	ft::const_bidirectional_iterator<T>					const_iterator;
				typedef	ft::reverse_iterator<iterator>						reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		public:
				value_compare				_comp;
				allocator_type				_alloc;
				node_ptr					_root;
		public:

				// === CONSTRUCTOR === //
				btree( void ) : _comp(value_compare()), _alloc(allocator_type()), _root(NULL) { }
				btree(value_compare	comp) : _comp(comp), _alloc(allocator_type()), _root(NULL) { }
				template <class InputIterator>
				btree(InputIterator first, InputIterator last, value_compare comp, allocator_type alloc)
					: _comp(comp), _alloc(alloc), _root(NULL)
				{
					for ( ; first != last ; first++)
						btree_insert(&_root, *first);
				}

		private:
				node_ptr	_get_last() const {
					node_ptr	temp = _root;
					if (temp)
						while (temp->right != NULL)
							temp	= temp->right;
					return (temp);
				}

		public:
				iterator	begin() {
					node_ptr	temp = _root;
					if (_root) {
						while (temp->left != NULL)
							temp = temp->left;
					}
					return (iterator(temp, _get_last()));
				}
				const_iterator	begin() const {
					const_node_ptr	temp = reinterpret_cast<const_node_ptr>(_root);
					if (_root) {
						while (temp->left != NULL)
							temp = temp->left;
					}
					return (const_iterator(temp, reinterpret_cast<const_node_ptr>(_get_last())));
				}

				iterator	end() {
					return (iterator(NULL, _get_last()));
				}
				const_iterator	end() const {
					return (const_iterator(NULL, reinterpret_cast<const_node_ptr>(_get_last())));
				}

				// === INSERT === //
				iterator btree_insert(node **root, const T& value)
				{
					if (*root == NULL)
					{
						*root = _alloc.allocate(1);
						_alloc.construct(*root, value);
						(*root)->left		= NULL;
						(*root)->right		= NULL;
						(*root)->parent		= NULL;
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

				node*	get_inorder_successor(node* right) {
					node*	temp = right;
					while (temp && temp->left != NULL) {
						temp = temp->left;
					}
					return (temp);
				}
				// === DELETE ===
				node* delete_node(node* root, const key_type& k)
				{
					if (root == NULL)
						return (root);
					// this->btree_display(root, 0);
					// std::cout << "delete_node" << std::endl;
					if (_comp(k, root->value.first))
						root->left = delete_node(root->left, k);
					else if (_comp(root->value.first, k))
						root->right = delete_node(root->right, k);
					
					else // Ici on a trouvé la node a delete car K est ni inferieur ni superieur
					{
						if (root->right == NULL && root->left == NULL)	// Si c'est une feuille
						{
							_alloc.destroy(root);
							_alloc.deallocate(root, 1);
							return NULL;
						}
						else if (root->left == NULL)		// Si il a qu'un seul enfant right
						{
							node*	temp = root->right;
							_alloc.destroy(root);
							_alloc.deallocate(root, 1);
							return (temp);
						}
						else if (root->right == NULL)		// Si il a qu'un seul enfant left
						{
							node*	temp = root->left;
							_alloc.destroy(root);
							_alloc.deallocate(root, 1);
							return (temp);
						}
						node*	temp		= get_inorder_successor(root->right);	// si la node a deux enfants prendre le inorder successor de root
						
						node*	tempright	= root->right;
						node*	templeft	= root->left;
						node*	tempparent	= root->parent;
						
						_alloc.destroy(root);
						_alloc.construct(root, temp->value);
						root->right		= tempright;
						root->left		= templeft;
						root->parent	= tempparent;
						
						root->right	= delete_node(root->right, temp->value.first);
					}
					return (root);
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
					if (root == NULL)
						return ;

					btree_clear((root->left));
					btree_clear((root->right));
					if (root->left == NULL && root->right == NULL)
					{
						_alloc.destroy(root);
						_alloc.deallocate(root, 1);
						root = NULL;
					}
				}

				// === FIND === //
				T* btree_find_pair(node *root, T data_ref) const
				{
					T*	ret;
					if (root == NULL)
						return (NULL);

					ret = btree_find_pair(root->left, data_ref);
					if (ret == NULL && !_comp(data_ref.first, root->value.first) && !_comp(root->value.first, data_ref.first))	// std::less<key>
						return &(root->value);
					if (ret == NULL)
						ret = btree_find_pair(root->right, data_ref);
					return (ret);
				}
				
				node* btree_find_node(node *root, T data_ref) const
				{
					node*	ret;
					if (root == NULL)
						return (NULL);

					ret = btree_find_node(root->left, data_ref);
					if (ret == NULL && !_comp(data_ref.first, root->value.first) && !_comp(root->value.first, data_ref.first))	// std::less<key>
						return (root);
					if (ret == NULL)
						ret = btree_find_node(root->right, data_ref);
					return (ret);
				}

				// delete => trouver la valeur a delete puis aller dans le subtree de gauche et chercher la plus grande valeure
				// 			puis la mettre a la place de la node deleted

				// === LEVEL COUNT === //
				int btree_level_count(node *root)
				{
					T	retleft;
					T	retright;

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
					std::cout << root->value.first << " - " <<  root->value.second << std::endl;
					btree_display(root->left, space);
				}
	};

}

#endif