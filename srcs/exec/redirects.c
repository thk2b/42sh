/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 07:31:07 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 08:43:35 by tkobb            ###   ########.fr       */
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

	flags = O_WRONLY & O_CREAT & append ? O_APPEND : O_TRUNC;
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

static void			get_last_redirects(t_redirect *redirects,
	t_redirect **last_redirect, t_redirect **last_heredoc)
{
	t_redirect	*r;
	t_redirect	*lr;
	t_redirect	*lh;

	r = redirects;
	lr= NULL;
	lh = NULL;
	while (r)
	{
		if (r->type == REDIRECT_APPEND_RIGHT || r->type == REDIRECT_RIGHT)
			lr = r;
		else if (r->type == REDIRECT_LEFT)
			lh = r;
		r = r->next;
	}
	*last_redirect = lr;
	*last_heredoc = lh;
}

int					init_redirects(t_redirect *redirects)
{
	t_redirect	*redirect;
	t_redirect	*heredoc;

	get_last_redirects(redirects, &redirect, &heredoc);
	init_redirect(redirect, redirect->type == REDIRECT_APPEND_RIGHT);
	init_heredoc(heredoc);
	return (0);
}
