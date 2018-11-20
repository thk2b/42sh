/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 09:45:55 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/20 15:54:45 by dmendelo         ###   ########.fr       */
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


void					print_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		print_tree(tree->left);
	printf("type: %d\n", tree->type);
	print_command_info(tree->data);
	if (tree->right)
		print_tree(tree->right);
}

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
	printf("-------------------------------------------------");
	printf("printing new root");
	printf("-------------------------------------------------");
	print_command_info((*new_root)->data);
	return (*new_root);
}
/*
t_tree					*insert(t_tree *parent, t_tree *current, t_cmd *data, char type)
{
	if (!current)
	{
		current = new_leaf(NULL, type, data);
		current->parent = (parent) ? parent : NULL;
		return (current);
	}
	if (compare_precedence(type, current->type) >= 0)
	{
		if (!parent)
			current = build_subtree(current, new_leaf(current->parent, type, data));
		else
		{
			if (compare_precedence(type, parent->type) < 0)
				current = build_subtree(current, new_leaf(current->parent, type, data));
			else
				return (insert(current->parent->parent, current->parent, data, type));
		}
	}
	else
	{
		if (!current->left)
			return (insert(current, current->left, data, type));
		else
			return (insert(current, current->right, data, type));
	}
	return (current);
}
*/

t_tree					*insert(t_tree **root, t_cmd *data, char type)
{
	WOW();
	if (root)
	{
		printf("----------------------------------------");
		printf("printing root node....");
		printf("----------------------------------------");
		if (*root)
			print_command_info((*root)->data);
	}
	if (!(*root))
	{
		printf("\n\nnew_leaf\n\n");
		return (new_leaf(NULL, type, data));
	}
	if (compare_precedence(type, (*root)->type) >= 0)
	{
		printf("\n\n\n\nnew root\n\n");
		t_tree				*new = new_leaf(NULL, type, data);
		return (build_subtree(root, &new));
	}
	if (!(*root)->left)
	{
		printf("\n\n\n\nmoving down left\n\n\n");
		(*root)->left = insert(&(*root)->left, data, type);
	}
	else
	{
		printf("\n\n\n\nmoving down right\n\n\n");
		(*root)->right = insert(&(*root)->right, data, type);
	}
	return (*root);
}

t_tree					*build_tree(t_nodes *tokens)
{
	WOW();
	t_tree				*ast;
	t_tree				*current;
	t_tree				*root;
	char				type;
	t_cmd				*new;

//	ast = init_tree();
	ast = NULL;
	root = ast;
	while (tokens)
	{
	//	ast = root;
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
		printf("----------------------------\n\n\nplacing command:\n");
		print_command_info(new);
		ast = insert(&ast, new, type);
//		if (ast)
//			print_tree(ast);
//		tokens = tokens->next;
	}
	printf("\n\n\n------------------------done reading------------------------");
	printf("------------------------------------------------------------------");
	printf("printing tree....");
	printf("------------------------------------------------------------------\n");
	print_tree(ast);
	return (ast);
}
