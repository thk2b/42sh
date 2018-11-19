/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 07:31:07 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 08:08:38 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <fcntl.h>

/*
**	the file becomes stdout
*/

static int	init_redirect(t_redirect *redirect, int append)
{
	int		fd;
	int		flags;

	flags = O_CREAT & append ? O_APPEND : O_TRUNC;
	if ((fd = open(redirect->path, flags, CREAT_PERMS)) == -1)
		return (error("open"));
	if (dup2(fd, 1) == -1)
		return (error("dup2"));
	return (0);
}

/*
**	the file becomes stdin
*/

static int	init_heredoc(t_redirect *redirect)
{
	
}

int			init_redirects(t_redirect *redirects)
{
	char		did_heredoc;
	char		did_redirect;
	t_redirect	*r;

	r = redirects;
	while (r)
	{
		if (!did_redirect && (r->type & REDIRECT_RIGHT)
		&& (did_redirect = 1) == 1) // NO! do the last redirection only
			init_redirect(r, 0);
		else if (!did_redirect && (r->type & REDIRECT_APPEND_RIGHT)
		&& (did_redirect = 1) == 1)
			init_redirect(r, 1);
		else if (!did_heredoc && (r->type & REDIRECT_LEFT)
		&& (did_heredoc = 1) == 1)
			init_heredoc(r);
		r = r->next;
	}
	return (0);
}
