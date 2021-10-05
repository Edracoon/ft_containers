#include<iostream>
#include <queue>
#include <stdio.h>

typedef struct s_node
{
		struct s_node	*left;
		struct s_node	*right;
		int				item;
} t_node;

void	btree_display(t_node *root, int space)
{
	int	i = 5;

	if (root == NULL)
		return ;
	space += 5;
	btree_display(root->right, space);
	while (i++ < space)
		printf(" ");
	printf("%d\n", root->item);
	btree_display(root->left, space);
}

t_node *btree_create_node(int	item)
{
	t_node	*temp = new t_node;

	temp->left		= NULL;
	temp->right		= NULL;
	temp->item		= item;
	
	return (temp);
}

void btree_apply_prefix(t_node *root, void (*applyf)(t_node *))
{
	if (root == NULL)
		return ;
	applyf(root);
	btree_apply_prefix(root->left, applyf);
	btree_apply_prefix(root->right, applyf);
}

void btree_apply_infix(t_node *root, void (*applyf)(t_node *))
{
	if (root == NULL)
		return ;
	btree_apply_infix(root->left, applyf);
	applyf(root);
	btree_apply_infix(root->right, applyf);
}

void	btree_apply_suffix(t_node *root, void (*applyf)(t_node *))
{
	if (root == NULL)
		return ;
	btree_apply_suffix(root->left, applyf);
	btree_apply_suffix(root->right, applyf);
	applyf(root);
}

void btree_insert_data(t_node **root, int item)
{
	if (*root == NULL)
	{
		(*root) = btree_create_node(item);
		return ;
	}
	if (item < (*root)->item) // std::less<key>
		btree_insert_data(&((*root)->left), item);
	else
		btree_insert_data(&((*root)->right), item);
}

void *btree_search_item(t_node *root, int data_ref)
{
	void *	ret;
	if (root == NULL)
		return (NULL);

	ret = btree_search_item(root->left, data_ref);
	if (ret == NULL && data_ref == root->item)	// std::less<key>
		return (root);
	if (ret == NULL)
		ret = btree_search_item(root->right, data_ref);
	return (ret);
}

// delete => trouver la valeur a delete puis aller dans le subtree de gauche et chercher la plus grande valeure
// 			puis la mettre a la place de la node deleted


int btree_level_count(t_node *root)
{
	int	retleft;
	int	retright;

	if (root == NULL)
		return (0);

	retleft = btree_level_count(root->left);
	retright = btree_level_count(root->right);

	return ( (retleft > retright ? retleft : retright) + 1 );
}

int	main(void)
{
	t_node	*root = NULL;

	btree_insert_data(&root, 10);
	btree_insert_data(&root, 2);
	btree_insert_data(&root, 5);
	btree_insert_data(&root, 1);
	btree_insert_data(&root, 20);
	btree_insert_data(&root, 15);
	btree_insert_data(&root, 25);

	t_node *ret = (t_node *)btree_search_item(root, 15);
	if (ret != NULL)
		std::cout << "btree_search_item(root, 9) = " << ret->item << std::endl;
	else
		std::cout << "btree_search_item(root, 9) = " << "NULL" << std::endl;

	std::cout << "btree_level_count(root) = " << btree_level_count(root) << std::endl;

	btree_display(root, 1);
}