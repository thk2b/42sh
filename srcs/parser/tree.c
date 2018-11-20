/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:47:49 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/20 09:45:51 by dmendelo         ###   ########.fr       */
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

t_tree	*push_top(t_tree *left, t_tree *right, char type, char **argv)
{
	t_tree *tree;

	tree = init_tree(argv, type);
	
	// if (left == NULL)
	// 	tree->parent = left;
	tree->left = left;
	tree->right = right;
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

int			build_tree(t_tree **tree, char **argv)
{
	t_tree		*root;
	int			precedency;

	precedency = return_presidency(argv);
	while ((*tree)->parent && (*tree)->type < precedency) //Dont forget the pipe and the and : same precedency
		(*tree) = (*tree)->parent;
	if (precedency > 1)
		*tree = push_top(*tree, NULL, precedency, argv);
	if ((*tree)->left == NULL)
	{
		// print_tree(*tree);
		t_tree *lchild = insert((*tree)->left, argv, precedency);
		// (*tree)->parent = lchild;
		// printf("SALUT\n");
	}
	else
	{
		t_tree *rchild = insert((*tree)->right, argv, precedency);
		// (*tree)->parent = rchild;
	}
	// printf("command = ");
	// print_double(argv);
	// printf("\n");
	return (0);
}



/*
**	the idea is here, you need to work a bit with the parent, u have the algorithm in paper in front of you
**	it recognizes the precedency, the type also, the insert might not work very well, you can aslo work with that
**	but try to keep this idea, because, its how the AST has to be build for theo and anton
**	if you dont have a clear idea of how to do it, i can finish it when i come
**	ask anton and theo what you can do then, or maybe improve the lexer, i added some things
**	Good luck Mister :D 
*/

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
		build_tree(&root, array[i]);
		i++;

	}
	print_tree(root);
	return (0);
}
