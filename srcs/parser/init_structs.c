/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:15:42 by ale-goff          #+#    #+#             */
/*   Updated: 2018/12/01 19:45:35 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redirect				*new_redirection(char *operator_, int fd,
						int fd_dest, int close)
{
	char				type;
	t_redirect			*new;

	new = (t_redirect *)malloc(sizeof(*new));
	type = determine_redirection_type(operator_);
	new->type = type;
	new->fd = fd;
	new->fd_dest = fd_dest;
	new->path = NULL;
	new->next = NULL;
	new->close = close;
	return (new);
}

t_cmd					*init_command(void)
{
	t_cmd				*new;

	new = (t_cmd *)malloc(sizeof(*new));
	new->redirects = NULL;
	new->assign = NULL;
	new->argv = NULL;
	new->return_status = 0;
	return (new);
}

t_tree					*init_tree(void)
{
	t_tree				*new;

	new = (t_tree *)malloc(sizeof(*new));
	new->parent = NULL;
	new->type = 0;
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

void					init_token_info(t_token *info)
{
	info->content = NULL;
	info->status = 0;
	info->type = 0;
}
