/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 07:31:07 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/30 18:17:58 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <fcntl.h>

/*
**	the file becomes stdout
*/

static int			init_redirect(t_redirect *redirect, int append)
{
	int		fd;
	int		flags;

	if ((redirect->old_fd = dup(redirect->fd)) == -1)
		return (error("dup"));
	flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
	if (redirect->path == NULL)
		fd = redirect->fd_dest;
	else if ((fd = open(redirect->path, flags, CREAT_PERMS)) == -1)
		return (error("open"));
	if (dup2(fd, redirect->fd) == -1)
		return (error("dup2"));
	return (0);
}

/*
**	the file becomes stdin
*/

static int			init_infile(t_redirect *redirect)
{
	int	fd;

	if ((redirect->old_fd = dup(redirect->fd)) == -1)
		return (error("dup"));
	if ((fd = open(redirect->path, O_RDONLY)) == -1)
	{
		close(STDIN);
		close(STDOUT);
		return (error(redirect->path));
	}
	if (dup2(fd, 0) == -1)
		return (error("dup2"));
	return (0);
}

int					init_redirects(t_redirect *redirects)
{
	t_redirect	*cur;

	cur = redirects;
	while (cur)
	{
		if (cur->type == REDIRECT_LEFT)
		{
			if (init_infile(cur))
				return (1);
		}
		else if (cur->type == HEREDOC_DOC || cur->type == HEREDOC_STR)
		{
			if (init_heredoc(cur))
				return (1);
		}
		else
		{
			if (init_redirect(cur, cur->type == REDIRECT_APPEND_RIGHT))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int					reset_redirects(t_redirect *redirects)
{
	t_redirect	*cur;

	cur = redirects;
	while (cur)
	{
		if (dup2(cur->old_fd, cur->fd) == -1)
			return (error("dup2"));
		cur = cur->next;
	}
	return (0);
}
