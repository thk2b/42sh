/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 07:31:07 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/30 17:49:34 by tkobb            ###   ########.fr       */
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

static int			read_heredoc(int stop_eof, int *fds, char *end)
{
	char	*line;
	int		cmp;
	int		ret;
	int		len;

	while ((ret = get_next_line(0, &line)) >= 0)
	{
		if (stop_eof && ret == 0)
			cmp = 0;
		else if ((cmp = ft_strcmp(line, end)))
		{
			len = ft_strlen(line);
			line[len] = '\n';
			write(fds[1], line, len + 1);
			free(line);
		}
		if (cmp == 0)
			return 0;
		else if (ret == 0)
			return 0;
	}
	return 0;
}

static int			init_heredoc(t_redirect *redirect)
{
	int		fd[2];
	int		is_eof;

	if (pipe(fd) == -1)
		return (error("pipe"));
	is_eof = ft_strcmp(redirect->path, "EOF") == 0;
	read_heredoc(is_eof, fd, redirect->path);
	if (dup2(fd[0], 0) == -1)
		return (error("dup2"));
	dup2(0, fd[0]);
	// close(fd[0]);
	close(fd[1]);
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
		else if (cur->type == HEREDOC_DOC)
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
