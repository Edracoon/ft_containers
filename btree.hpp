/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:15:12 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/19 20:17:19 by epfennig         ###   ########.fr       */
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
				size_type					_size;
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
					NIL->NIL	= NULL;
					_root		= NIL;
					_size		= 0;
				}
				btree(value_compare	comp) : _comp(comp), _alloc(allocator_type()), _root(NULL) {
					NIL = _alloc.allocate(1);
					_alloc.construct(NIL, value_type());
					NIL->color	= BLACK;
					NIL->NIL	= NULL;
					_root		=	NIL;
					_size		= 0;
				}
				template <class InputIterator>
				btree(InputIterator first, InputIterator last, value_compare comp, allocator_type alloc)
					: _comp(comp), _alloc(alloc), _root(NULL) {
					NIL = _alloc.allocate(1);
					_alloc.construct(NIL, value_type());
					NIL->color	= BLACK;
					NIL->NIL	= NULL;
					_root		= NIL;
					_size		= 0;
					// std::cout << "copy construct tree123\n";
					for ( ; first != last ; first++) {
						// std::cout << "copy construct tree\n";
						btree_insert(&_root, *first);
						// btree_display(_root, 0);
					}
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
					if (temp != temp->NIL) {
						while (temp->right != temp->NIL)
							temp = temp->right;
					}
					return (temp);
				}
			
				node_ptr	_get_inorder_successor(node_ptr right) const {
					node_ptr	temp = right;
					std::cout << "g_i_s : " << right << std::endl;
					while (temp != temp->NIL && temp->left != temp->NIL) {
						temp = temp->left;
					}
					return (temp);
				}

				// === RED-BLACK UTILS === //
				void	_left_rotate(node_ptr	x) {	// LEFT ROTATE
					node_ptr	y;

					y = x->right;
					x->right = y->left;
					if (y->left != NIL)
						y->left->parent = x;
					y->parent = x->parent;
					if (x->parent == NIL)
						_root = y;
					else if (x == x->parent->left)
						x->parent->left = y;
					else
						x->parent->right = y;
					y->left = x;
					x->parent = y;
				}
				void	_right_rotate(node_ptr	x) {	// RIGHT ROTATE
					node_ptr	y;

					y = x->left;
					x->left = y->right;
					if (y->right != NIL)
						y->right->parent = x;
					y->parent = x->parent;
					if (x->parent == NIL)
						_root = y;
					else if (x == x->parent->right)
						x->parent->right = y;
					else
						x->parent->left = y;
					y->right = x;
					x->parent = y;
				}

				node_ptr insert_fixup(node_ptr z)
				{
					node_ptr	temp = z;	// Stock z pour pouvoir le return dans mon iterator
					node_ptr	y;

					while(z->parent->color == RED)
					{
						if(z->parent == z->parent->parent->left) // z.parent is the left child
						{
							
							y = z->parent->parent->right; //uncle of z

							if(y->color == RED) //case 1
							{
								z->parent->color = BLACK;
								y->color = BLACK;
								z->parent->parent->color = RED;
								z = z->parent->parent;
							}
							else // case 2 or case 3
							{
								if(z == z->parent->right) //case 2
								{
									z = z->parent; //marked z.parent as new z
									_left_rotate(z);
								}
								// case 3
								z->parent->color = BLACK; //made parent BLACK
								z->parent->parent->color = RED; //made parent red
								_right_rotate(z->parent->parent);
							}
						}
						else //z.parent is the right child
						{
							y = z->parent->parent->left; //uncle of z

							if(y->color == RED)
							{
								z->parent->color = BLACK;
								y->color = BLACK;
								z->parent->parent->color = RED;
								z = z->parent->parent;
							}
							else
							{
								if(z == z->parent->left)
								{
									z = z->parent; //marked z.parent as new z
									_right_rotate(z);
								}
								z->parent->color = BLACK; //made parent BLACK
								z->parent->parent->color = RED; //made parent red
								_left_rotate(z->parent->parent);
							}
						}
					}
					_root->color = BLACK;
					return temp;
				}
				void delete_fixup(node_ptr x)
				{
					while(x != _root && x->color == BLACK)
					{
						if(x == x->parent->left)
						{
							node_ptr w = x->parent->right;
							if(w->color == RED)
							{
								w->color = BLACK;
								x->parent->color = RED;
								_left_rotate(x->parent);
								w = x->parent->right;
							}
							if(w->left->color == BLACK && w->right->color == BLACK)
							{
								w->color = RED;
								x = x->parent;
							}
							else
							{
								if(w->right->color == BLACK)
								{
									w->left->color = BLACK;
									w->color = RED;
									_right_rotate(w);
									w = x->parent->right;
								}
								w->color = x->parent->color;
								x->parent->color = BLACK;
								w->right->color = BLACK;
								_left_rotate(x->parent);
								x = _root;
							}
						}
						else
						{
							node_ptr w = x->parent->left;
							if(w->color == RED)
							{
								w->color = BLACK;
								x->parent->color = RED;
								_right_rotate(x->parent);
								w = x->parent->left;
							}
							if(w->right->color == BLACK && w->left->color == BLACK)
							{
								w->color = RED;
								x = x->parent;
							}
							else
							{
								if(w->left->color == BLACK)
								{
									w->right->color = BLACK;
									w->color = RED;
									_left_rotate(w);
									w = x->parent->left;
								}
								w->color = x->parent->color;
								x->parent->color = BLACK;
								w->left->color = BLACK;
								_right_rotate(x->parent);
								x = _root;
							}
						}
					}
					x->color = BLACK;
				}

				void rb_transplant(node_ptr u, node_ptr v)
				{
					if(u->parent == NIL)
						_root = v;
					else if(u == u->parent->left)
						u->parent->left = v;
					else
						u->parent->right = v;
					v->parent = u->parent;
				}
		public:
				iterator	begin() {
					node_ptr	temp = _root;
					if (_root != NIL)
					{
						while (temp->left != temp->NIL)
							temp = temp->left;
					}
					return (iterator(temp, _get_last()));
				}
				const_iterator	begin() const {
					const_node_ptr	temp = reinterpret_cast<const_node_ptr>(_root);
					if (temp == reinterpret_cast<const_node_ptr>(NIL))
						return (const_iterator(temp, reinterpret_cast<const_node_ptr>(_get_last())));
					while (temp->left != reinterpret_cast<const_node_ptr>(temp->NIL))
						temp = temp->left;
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
						(*root)->color		= BLACK;
						(*root)->parent 	= NIL;
						(*root)->left		= NIL;
						(*root)->right		= NIL;
						(*root)->NIL		= NIL;
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
							_size += 1;
							return iterator(insert_fixup((*root)->left), NIL);
						}
						// right insert
						if ((*root)->right == NIL && (_comp((*root)->value.first, value.first)))
						{
							create_new_node(&((*root)->right), root, value);
							_size += 1;
							return iterator(insert_fixup((*root)->right), NIL);
						}
						if (_comp((*root)->value.first, value.first))
							root = &((*root)->right);
						else if (!_comp((*root)->value.first, value.first))
							root = &((*root)->left);
					}
					return iterator(NIL, NIL);
				}

				// === DELETE === //
				// node_ptr delete_node(node_ptr root, const key_type& k)
				// {
				// 	if (root == NIL)
				// 		return (root);

				// 	if (_comp(k, (root)->value.first))
				// 		root->left = delete_node(root->left, k);
				// 	else if (_comp(root->value.first, k))
				// 		root->right = delete_node(root->right, k);

				// 	else // Ici on a trouvé la node a delete car K est ni inferieur ni superieur
				// 	{
				// 		// bool	original_color	= root->color;
				// 		if (root->right == NIL && root->left == NIL)	// Si c'est une feuille
				// 		{
				// 			// _size -= 1;
				// 			_alloc.destroy(root);
				// 			root = NIL;
				// 			return NIL;
				// 		}
				// 		else if (root->left == NIL)		// Si il a qu'un seul enfant right
				// 		{
				// 			node_ptr	temp = root->right;
				// 			// _size -= 1;
				// 			_alloc.destroy(root);
				// 			root = NIL;
				// 			return (temp);
				// 		}
				// 		else if (root->right == NIL)		// Si il a qu'un seul enfant left
				// 		{
				// 			node_ptr	temp = root->left;
				// 			// _size -= 1;
				// 			_alloc.destroy(root);
				// 			root = NIL;
							
				// 			return (temp);
				// 		}
				// 		else if (root->right != NIL && root->left != NIL)
				// 		{
				// 			node_ptr	temp		= _get_inorder_successor(root->right);	// si la node a deux enfants prendre le inorder successor de root
				// 			node_ptr	tempright	= root->right;
				// 			node_ptr	templeft	= root->left;
				// 			node_ptr	tempparent	= root->parent;
				// 			bool		colortemp	= root->color;

				// 			_alloc.destroy(root);
				// 			_alloc.construct(root, temp->value);
				// 			root->right		= tempright;
				// 			root->left		= templeft;
				// 			root->parent	= tempparent;
				// 			root->NIL		= NIL;
				// 			root->color		= colortemp;
				// 			// root->NIL->NIL	= NIL;

				// 			root->right	= delete_node(root->right, temp->value.first);
				// 			// if (original_color == BLACK)
				// 			// 	delete_fixup(root->right);
				// 		}
				// 	}
				// 	return (root);
				// }

				// DELETE TEMPORAIRE POUR TESTER
				void delete_node(node_ptr z)
				{
					node_ptr y = z;
					node_ptr x;
					bool y_orignal_color = y->color;
					if(z->left == NIL)
					{
						x = z->right;
						rb_transplant(z, z->right);
					}
					else if(z->right == NIL)
					{
						x = z->left;
						rb_transplant(z, z->left);
					}
					else
					{
						
						y = _get_inorder_successor(z->right);
						y_orignal_color = y->color;
						x = y->right;
						if(y->parent == z) {
							x->parent = z;
						}
						else
						{
							rb_transplant(y, y->right);
							y->right = z->right;
							y->right->parent = y;
						}
						rb_transplant(z, y);
						y->left = z->left;
						y->left->parent = y;
						y->color = z->color;
					}
					if(y_orignal_color == BLACK)
						delete_fixup(x);
				}
				node_ptr	delete_node_test(node_ptr root, const key_type& k)
				{
					delete_node(this->btree_find_node(root, k));
					return (_root);
				}
				// === SIZE ===
				int	size(node_ptr root) const
				{
					if (root == NIL || root->NIL == NULL)
						return (0);
					
					return (size((root->left)) + 1 + size((root->right)));
				}

				// === CLEAR === //
				void	btree_clear()
				{
					// if (_root == NIL)
					// 	return ;

					// btree_clear((root->left));
					// btree_clear((root->right));
					_alloc.destroy(_root);
					
					_root = NIL;
				}

				// === FIND === //
				T* btree_find_pair(node_ptr root, const key_type& k) const
				{
					T*	ret;
					// std::cout << "here1" << std::endl;
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

				void	btree_display(node_ptr root, int space) const
				{
					int	i = 5;

					if (root == NIL)
						return ;
					space += 5;
					btree_display(root->right, space);
					while (i++ < space)
						std::cout << " ";
					std::cout << root->value.first << "(";
					if (  root->color == 1 ) 
						std::cout << "R)" << std::endl;
					else if (  root->color == 0 ) 
						std::cout << "B)" << std::endl;
					btree_display(root->left, space);
				}
	};

}

#endif