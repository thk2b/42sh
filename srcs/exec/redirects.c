/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 07:31:07 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/21 19:20:06 by tkobb            ###   ########.fr       */
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

	flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
	if ((fd = open(redirect->path, flags, CREAT_PERMS)) == -1)
		return (error("open"));
	if (dup2(fd, redirect->fd) == -1)
		return (error("dup2"));
	return (0);
}

/*
**	the file becomes stdin
*/

static int			init_heredoc(t_redirect *redirect)
{
	int	fd;

	if ((fd = open(redirect->path, O_RDONLY)) == -1)
		return (error(redirect->path));
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
		// TODO: expand path
		if (cur->type == REDIRECT_LEFT)
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
