/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:47:49 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/19 20:23:13 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_cmd	*init_cmd(char **argv)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->argv = argv;
	return (cmd);
}

t_tree	*init_tree(char **argv, char type)
{
	t_tree		*tree;

	tree = (t_tree*)malloc(sizeof(t_tree));
	tree->type = type;
	tree->left = NULL;
	tree->right = NULL;
	tree->parent = NULL;
	tree->data = init_cmd(argv);
	return (tree);
}

void	print_double(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		printf("%s ", arr[i]);
		i++;
	}
}

void	print_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->parent != NULL)
	{
		printf("parent = ");
		print_double(tree->parent->data->argv);
		printf("value = ");
		print_double(tree->data->argv);
		printf("type = %d\n", tree->type);
	}
	else
	{
		printf("value = ");
		print_double(tree->data->argv);
		printf("type = %d\n", tree->type);
	}
	if (tree->left != NULL)
		print_tree(tree->left);
	if (tree->right != NULL)
		print_tree(tree->right);
}

t_tree		*insert(t_tree *tree, char **args, int type)
{
	if (tree == NULL)
		return (init_tree(args, type));
	return (tree);
}

void		token_to_command(void);

t_tree		*join_tree(t_tree *left, t_tree *right, char **argv, char type)
{
	t_tree *tree = init_tree(argv, type);

	tree->left = left;
	tree->right = right;
	if (tree->left != NULL)
		left->parent = tree;
	if (tree->right != NULL)
		right->parent = tree;
	return (tree);
}

int		return_presidency(char **argv)
{
	int		presidency;

	presidency = 0;
	if (IS_OP(**argv))
		presidency = T_AND;
	else if (IS_SEMI(**argv))
		presidency = T_SEMI;
	else
		presidency = T_CMD;
	return (presidency);
}

int			build_tree(t_tree *tree, char **argv)
{
	t_tree		*root;
	int			precedency;

	precedency = return_presidency(argv);
	while ((tree) && (tree)->type < precedency) //Dont forget the pipe and the and
		tree = tree->parent;
	if (!tree)
		tree = init_tree(argv, precedency);
	else if ((tree)->left == NULL)
		insert((tree)->left, argv, precedency);
	else
		insert((tree)->right, argv, precedency);
	print_tree(tree);
	printf("command = ");
	print_double(argv);
	printf("\n");
	return (0);
}

int		main(int ac, char **av)
{
	int		i = 0;
	t_tree	*root;
	char *param1[] = {"ls", "-l", NULL};
	char *param2[] = {"echo", NULL};
	char *param3[] = {"cat", "-e", NULL};
	char *del1[] = {"&&", NULL};
	char *del2[] = {";", NULL};
	char **array[] = {
		del1,
		param2,
		del2,
		param3
	};
	root = init_tree(param1, 1);
	while (i < 4)
	{
		build_tree(root, array[i]);
		i++;
	}
	return (0);
}