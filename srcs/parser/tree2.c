/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <dmendelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 09:45:55 by dmendelo          #+#    #+#             */
/*   Updated: 2018/12/03 20:02:49 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	else if (is_red(s))
		return (T_RED);
	else if (is_assignment_word(s))
		return (T_ASS);
	return (T_CMD);
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
	while (tokens && tokens->content)
	{
		new = NULL;
		type = tokens->type;
		if (type == T_CMD || type == T_ASS)
			new = create_cmd(&tokens);
		else
			tokens = tokens->next;
		if (type == T_ASS)
			type = T_CMD;
		ast = insert(&ast, new, type);
	}
	if (ast && ast->type != T_SEMI)
		ast = insert(&ast, new, T_SEMI);
	return (ast);
}
