/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 09:45:55 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/20 19:08:33 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

# define ROOT 0

t_tree					*init_tree(void)
{
	t_tree				*new;

	new = (t_tree *)malloc(sizeof(*new));
	new->parent = NULL;
	new->type = ROOT;
	new->right = NULL;
	new->left = NULL;
	new->data = NULL;
	return (new);
}

t_tree					*new_leaf(t_tree *parent, char type, t_cmd *data)
{
	t_tree				*new;

	new = (t_tree *)malloc(sizeof(*new));
	if (parent)
		new->parent = parent;
	else
		new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->data = data;
	new->type = type;
	return (new);
}

char					get_type(char *s)
{
	if (!ft_strcmp(s, "|"))
		return (T_PIPE);
	else if (!ft_strcmp(s, "&&"))
		return (T_AND);
	else if (!ft_strcmp(s, "||"))
		return (T_OR);
	else if (!ft_strcmp(s, ";"))
		return (T_SEMI);
	else
		return (T_CMD);
}


// void					print_operator_type(char type)
// {
// 	if (type == T_PIPE)
// 		printf("------T_PIPE (|)------\n");
// 	else if (type == T_AND)
// 		printf("------T_AND (&&)------\n");
// 	else if (type == T_OR)
// 		printf("------T_OR (||)------\n");
// 	else if (type == T_SEMI)
// 		printf("------T_SEMI (;)------\n");
// 	else
// 		printf("------T_CMD (COMMAND)----------\n");

// }

// void					print_tree(t_tree *tree)
// {
// 	if (!tree)
// 		return ;
// 	if (tree->left)
// 		print_tree(tree->left);
// 	print_operator_type(tree->type);
// 	print_command_info(tree->data);
// 	if (tree->right)
// 		print_tree(tree->right);
// }

int						compare_precedence(char a, char b)
{
	if (a == T_CMD)
	{
		return ((b == T_CMD) ? 0 : -1);
	}
	if (a == T_PIPE)
	{
		if (b == T_PIPE)
			return (0);
		else if (b == T_CMD)
			return (1);
		else
			return (-1);
	}
	if (a == T_OR || a == T_AND)
	{
		if (b == T_SEMI)
			return (-1);
		else if (b == T_OR || b == T_AND)
			return (0);
		else
			return (1);
	}
	if (a == T_SEMI)
		return ((b == T_SEMI) ? 0 : 1);
	return (0);
}

t_tree					*build_subtree(t_tree **current, t_tree **new_root)
{
	(*new_root)->parent = (*current)->parent;
	(*current)->parent = *new_root;
	(*new_root)->left = *current;
	// printf("-------------------------------------------------");
	// printf("printing new root");
	// printf("-------------------------------------------------");
	// print_command_info((*new_root)->data);
	return (*new_root);
}

t_tree					*insert(t_tree **root, t_cmd *data, char type)
{
	t_tree					*new_root;
	
	new_root = NULL;
	if (!(*root))
	{
		return (new_leaf(NULL, type, data));
	}
	if (compare_precedence(type, (*root)->type) >= 0)
	{
		new_root = new_leaf(NULL, type, data);
		return (build_subtree(root, &new_root));
	}
	if (!(*root)->left)
	{
		(*root)->left = insert(&(*root)->left, data, type);
	}
	else
	{
		(*root)->right = insert(&(*root)->right, data, type);
	}
	return (*root);
}

t_tree					*build_tree(t_nodes *tokens)
{
	t_tree				*ast;
	t_tree				*root;
	char				type;
	t_cmd				*new;

	ast = NULL;
	root = ast;
	while (tokens)
	{
		if (!tokens->content)
		{
			break ;
		}
		type = get_type(tokens->content);
		if (type == T_CMD)
			new = create_cmd(&tokens);
		else
		{
			new = NULL;
			tokens = tokens->next;
		}
		ast = insert(&ast, new, type);
	}
	// printf("\n\n\n------------------------done reading------------------------");
	// printf("------------------------------------------------------------------");
	// printf("printing tree....");
	// printf("------------------------------------------------------------------\n");
	// print_tree(ast);
	return (ast);
}
