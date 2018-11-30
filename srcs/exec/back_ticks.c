/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_ticks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 08:58:37 by acakste           #+#    #+#             */
/*   Updated: 2018/11/27 20:28:07 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

static char	*strsub_ticks(char *str)
{
	char	*first_tick;
	char	*end_tick;
	char	*sub_str;

	if ((first_tick = ft_strchr(str, '`')) == NULL)
		return (NULL);
	if ((end_tick = ft_strchr(first_tick + 1, '`')) == NULL)
		return (NULL);
	sub_str = ft_strsub(first_tick + 1, 0, end_tick - (first_tick + 1));
	return (sub_str);
}

static int	set_up_tick_pipe(t_tree *root, int *child_pid)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	if ((*child_pid = fork()) == -1)
		return (-1);
	if (*child_pid == 0)
	{
		if (close((fd)[0]) == -1)
			_exit(1);
		dup2((fd)[1], 1);
		if (close((fd)[1]) == -1)
			_exit(1);
		_exit(exec_node(root, 1));
	}
	else
	{
		if (close((fd)[1]) == -1)
			return (-1);
	}
	return (fd[0]);
}

static char	*create_res_str(char *init_str, char *new_str)
{
	char	*first_tick;
	char	*end_tick;
	char	*full_res;

	if ((first_tick = ft_strchr(init_str, '`')) == NULL)
		return (NULL);
	if ((end_tick = ft_strchr(first_tick + 1, '`')) == NULL)
		return (NULL);
	full_res = ft_strreplace(init_str, first_tick,
						(end_tick + 1) - first_tick, new_str);
	return (full_res);
}

static char	*build_str_from_pipe(int fd)
{
	char	*res;
	char	*tmp;
	char	*line;

	res = ft_strdup("");
	while (get_next_line((fd), &line) == 1)
	{
		if ((*res))
		{
			tmp = res;
			res = ft_strjoin(res, " ");
			free(tmp);
		}
		tmp = res;
		res = ft_strjoin(res, line);
		free(tmp);
		free(line);
	}
	return (res);
}

int			exec_backticks(char **dst, char *str)
{
	char	*sub_str;
	t_tree	*root;
	int		fd;
	char	*res;
	int		child_pid;

	if ((sub_str = strsub_ticks(str)) == NULL)
		return (0);
	if ((root = parse(sub_str)) == NULL)
		return (1);
	fd = set_up_tick_pipe(root, &child_pid);
	res = build_str_from_pipe(fd);
	if (close((fd)) == -1)
		return (1);
	waitpid(child_pid, &fd, 0);
	*dst = create_res_str(str, res);
	free(str);	
	free(res);
	return (0);
}
