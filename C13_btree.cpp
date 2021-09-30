#include<iostream>
#include <queue>
#include <stdio.h>

typedef struct s_node
{
		struct s_node	*left;
		struct s_node	*right;
		int				item;
} t_node;


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

void btree_apply_suffix(t_node *root, void (*applyf)(t_node *))
{
	if (root == NULL)
		return ;
	btree_apply_suffix(root->left, applyf);
	btree_apply_suffix(root->right, applyf);
	applyf(root);
}

void    btree_display(t_node *root, int space) {
    int    i = 5;

	if (root == NULL)
		return ;
	space += 5;
	btree_display(root->right, space);
	while (i++ < space)
		printf(" ");
	printf("%d\n", root->item);
	btree_display(root->left, space);
}

void	print_content(t_node *root)
{
	std::cout << root->item << " ";
}

int	main(void)
{
	t_node	*root;

	root = btree_create_node(1);

	root->left = btree_create_node(2);
	root->right = btree_create_node(3);

	root->left->left = btree_create_node(4);
	root->left->right = btree_create_node(5);

	root->right->right = btree_create_node(6);
	root->right->left = btree_create_node(7);

	btree_apply_prefix(root, print_content);
	std::cout << std::endl;
	btree_apply_infix(root, print_content);
	std::cout << std::endl;
	btree_apply_suffix(root, print_content);
	
	std::cout << std::endl;
	btree_display(root, 1);
}



// void printLevelOrder(t_node *root)
// {
// 	// Base Case
// 	if (root == NULL)
// 		return;
 
// 	// Create an empty queue for level order traversal
// 	std::queue<t_node *> q;

// 	// Enqueue Root and initialize height
// 	q.push(root);

// 	while (q.empty() == false)
// 	{
// 		// nodeCount (queue size) indicates number
// 		// of nodes at current level.
// 		int nodeCount = q.size();

// 		// Dequeue all nodes of current level and
// 		// Enqueue all nodes of next level
// 		while (nodeCount > 0)
// 		{
// 			t_node *node = q.front();
// 			std::cout << node->item << " ";
// 			q.pop();
// 			if (node->left != NULL)
// 				q.push(node->left);
// 			if (node->right != NULL)
// 				q.push(node->right);
// 			nodeCount--;
// 		}
// 		std::cout << std::endl;
// 	}
// }