/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:11:30 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/30 18:20:16 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

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
			return (0);
		else if (ret == 0)
			return (0);
	}
	return (0);
}

int					init_heredoc(t_redirect *redirect)
{
	int		fd[2];
	int		is_eof;

	if (pipe(fd) == -1)
		return (error("pipe"));
	is_eof = ft_strcmp(redirect->path, "EOF") == 0;
	if (redirect->type == HEREDOC_DOC)
		read_heredoc(is_eof, fd, redirect->path);
	else
	{
		ft_putstr_fd(redirect->path, fd[1]);
		ft_putchar_fd('\n', fd[1]);
	}
	if (dup2(fd[0], 0) == -1)
		return (error("dup2"));
	dup2(0, fd[0]);
	close(fd[1]);
	return (0);
}
