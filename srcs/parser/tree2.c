/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 09:45:55 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/20 11:06:17 by dmendelo         ###   ########.fr       */
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

t_tree					*new_leaf(t_tree *parent, char type)
{
	t_tree				*new;

	new = (t_tree *)malloc(sizeof(*new));
	new->parent = parent;
	new->left = NULL;
	new->right = NULL;
	new->data = NULL;
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
}

t_tree					*insert(t_tree *current, t_cmd *data, char type)
{
	if (!current)
	{
		current = new_leaf(NULL, type);
		current->data = data;
	}
	if (type < current->type)
	{
		insert(current->parent, data, type);
	}
	else
	{
		if (!current->left)
			insert(current->left, data, type);
		else
			insert(current->right, data, type);
	}
}

t_tree					*build_tree(t_nodes *tokens)
{
	t_tree				*ast;
	t_tree				*current;

	ast = init_tree();
	current = ast;
	while (tokens)
	{
		if (is_op(tokens->content))
		{
			current = insert(current, create_cmd(tokens->content), get_type(tokens->content));
		}
	}
}
