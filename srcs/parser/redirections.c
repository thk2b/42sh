/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:18:59 by ale-goff          #+#    #+#             */
/*   Updated: 2018/12/03 16:46:12 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char					determine_redirection_type(char *o)
{
	if (!ft_strcmp(o, "<"))
		return (REDIRECT_LEFT);
	else if (!ft_strcmp(o, ">"))
		return (REDIRECT_RIGHT);
	else if (!ft_strcmp(o, ">>"))
		return (REDIRECT_APPEND_RIGHT);
	else if (!ft_strcmp(o, "<<"))
		return (HEREDOC_DOC);
	else if (!ft_strcmp(o, "<<<"))
		return (HEREDOC_STR);
	else
		return (0);
}

int						is_redirection(char *s)
{
	if (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>") || !ft_strcmp(s, "<") ||
		!ft_strcmp(s, "<<") || !ft_strcmp(s, "|") || !ft_strcmp(s, "<<<"))
		return (1);
	return (0);
}

void					push_back_test(t_redirect **redir, t_redirect *redirect)
{
	t_redirect *head;

	if (!(*redir))
	{
		*redir = redirect;
		return ;
	}
	head = *redir;
	while (head->next != NULL)
		head = head->next;
	head->next = redirect;
}

t_redirect				*pull_aggregation(t_nodes **node, int fd)
{
	t_redirect	*aggreg;
	int			fd_dest;
	int			close;

	close = 0;
	fd_dest = 0;
	aggreg = NULL;
	if ((*node)->next->next && (*node)->next->next->content)
	{
		if (is_number((*node)->next->next->content))
			fd_dest = ft_atoi((*node)->next->next->content);
		else if (!ft_strcmp((*node)->next->next->content, "-"))
			close = 1;
	}
	aggreg = new_redirection((*node)->content, fd, fd_dest, close);
	aggreg->path = NULL;
	return (aggreg);
}

int						pull_redirection(t_nodes **node, t_nodes *prev,
						t_cmd **cmd)
{
	t_redirect			*redirection;
	int					fd;

	redirection = NULL;
	if (prev && prev->content && is_number(prev->content))
		fd = ft_atoi(prev->content);
	else
	{
		if (ft_strequ((*node)->content, "<") || ft_strequ((*node)->content, "<<") ||
			ft_strequ((*node)->content, "<<<"))
			fd = STDIN;
		else
			fd = STDOUT;
	}
	if ((*node)->next && ft_strequ((*node)->next->content, "&"))
		redirection = pull_aggregation(node, fd);
	else if ((*node)->next)
	{
		redirection = new_redirection((*node)->content, fd, 0, 0);
		redirection->path = ft_strdup((*node)->next->content);
		(*node) = (*node)->next;
	}
	push_back_test(&(*cmd)->redirects, redirection);
	return (0);
}
