/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_RBtree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:20:08 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/21 11:50:38 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_RBTREE_HPP
# define SET_RBTREE_HPP

# include "iterator.hpp"
# include "node.hpp"

# define BLACK	0
# define RED	1

namespace ft
{
	template <class T, class Compare, class Alloc>
	class set_rbtree
	{
		public:
				typedef	T													value_type;
				typedef	T													key_type;
				typedef	size_t												size_type;
				typedef Compare												value_compare;
				
				typedef	node<const value_type>								const_node;
				typedef	node<const value_type>								node;

				typedef node*												node_ptr;
				typedef const_node*											const_node_ptr;

				typedef typename Alloc::template rebind< node >::other		allocator_type;
				
				typedef	ft::const_bidirectional_iterator<value_type>		iterator;
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
				set_rbtree( void ) : _comp(value_compare()), _alloc(allocator_type()), _root(NULL) {
					NIL = _alloc.allocate(1);
					_alloc.construct(NIL, value_type());
					NIL->color	= BLACK;
					NIL->NIL	= NULL;
					_root		= NIL;
					_size		= 0;
				}
				set_rbtree(value_compare	comp) : _comp(comp), _alloc(allocator_type()), _root(NULL) {
					NIL = _alloc.allocate(1);
					_alloc.construct(NIL, value_type());
					NIL->color	= BLACK;
					NIL->NIL	= NULL;
					_root		=	NIL;
					_size		= 0;
				}
				template <class InputIterator>
				set_rbtree(InputIterator first, InputIterator last, value_compare comp, allocator_type alloc)
					: _comp(comp), _alloc(alloc), _root(NULL) {
					NIL = _alloc.allocate(1);
					_alloc.construct(NIL, value_type());
					NIL->color	= BLACK;
					NIL->NIL	= NULL;
					_root		= NIL;
					_size = 0;
					for ( ; first != last ; first++) {
							btree_insert(&_root, *first);
					}
				}
				
				~set_rbtree() {
					this->btree_clear(_root);
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
					while (temp->left != temp->NIL) {
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
					node_ptr	w;
					while(x != _root && x->color == BLACK)
					{
						if(x == x->parent->left)
						{
							w = x->parent->right;
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
							w = x->parent->left;
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
				const_iterator	begin() const {
					const_node_ptr	temp = reinterpret_cast<const_node_ptr>(_root);
					if (temp == reinterpret_cast<const_node_ptr>(NIL))
						return (const_iterator(temp, reinterpret_cast<const_node_ptr>(_get_last())));
					while (temp->left != reinterpret_cast<const_node_ptr>(temp->NIL))
						temp = temp->left;
					return (const_iterator(temp, reinterpret_cast<const_node_ptr>(_get_last())));
				}
				const_iterator	end() const {
					return (const_iterator(reinterpret_cast<const_node_ptr>(NIL), reinterpret_cast<const_node_ptr>(_get_last())));
				}

				// === max_size === // 
				size_type max_size( void ) const {
					return (std::numeric_limits<size_type>::max() / (sizeof(node) - sizeof(node_ptr)));
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
						_size				+= 1;
						return iterator(*root, NIL);
					}
					while ((*root) != NIL)
					{
						// si les key sont egales, ne pas insert
						if (!_comp((*root)->value, value) && !_comp(value, (*root)->value))
							return (iterator(*root, NIL));
						// left insert
						if ((*root)->left == NIL && !(_comp((*root)->value, value)))
						{
							create_new_node(&((*root)->left), root, value);
							_size		+= 1;
							return iterator(insert_fixup((*root)->left), NIL);
						}
						// right insert
						if ((*root)->right == NIL && (_comp((*root)->value, value)))
						{
							create_new_node(&((*root)->right), root, value);
							_size		+= 1;
							return iterator(insert_fixup((*root)->right), NIL);
						}
						if (_comp((*root)->value, value))
							root = &((*root)->right);
						else if (!_comp((*root)->value, value))
							root = &((*root)->left);
					}
					return iterator(NIL, NIL);
				}

				// // === DELETE === //
				void delete_node_RB_algo(node_ptr z)
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
							x->parent = y;
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
					_alloc.destroy(z);
					_alloc.deallocate(z, 1);
					if (y_orignal_color == BLACK)
						delete_fixup(x);
				}
				node_ptr	delete_node_tree(const key_type& k)
				{
					node_ptr temp = this->btree_find_node(_root, k);
					if (temp != NIL) {
						_size		-= 1;
						delete_node_RB_algo(temp);
					}
					return (_root);
				}

				// === CLEAR === //
				void	btree_clear(node_ptr node)
				{	
					if (node == NIL)
						return ;
					btree_clear(node->left);
					btree_clear(node->right);
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
					_root	= NIL;
					_size	= 0;
				}
				
				// === SWAP === //
				void	btree_swap(set_rbtree&	xtree) {
					size_type					temp_size	= _size;
					value_compare				temp_comp	= _comp;
					allocator_type				temp_alloc	= _alloc;
					node_ptr					temp_root	= _root;
					node_ptr					temp_NIL	= NIL;
					
					_size			= xtree._size;
					_comp			= xtree._comp;
					_alloc			= xtree._alloc;
					_root			= xtree._root;
					NIL				= xtree.NIL;

					xtree._size		= temp_size;
					xtree._comp		= temp_comp;
					xtree._alloc	= temp_alloc;
					xtree._root		= temp_root;
					xtree.NIL		= temp_NIL;
				}

				// == FIND NODE === //
				node_ptr btree_find_node(node_ptr root, const key_type& k) const
				{
					while (root != NIL)
					{
						if (!_comp(k, root->value) && !_comp(root->value, k))	// std::less<key>
							return (root);
						if (_comp(k, root->value))
							root = root->left;
						else if (!_comp(k, root->value))
							root = root->right;
					}
					return (NIL);
				}

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
					std::cout << root->value << "(";
					if (  root->color == 1 ) 
						std::cout << "R)" << std::endl;
					else if (  root->color == 0 ) 
						std::cout << "B)" << std::endl;
					btree_display(root->left, space);
				}
	};
}

#endif