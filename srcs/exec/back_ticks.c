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

static int	backtick_sub(char *str, t_tree **root, char **res)
{
	char	*sub_str;
	int		fd;
	int		child_pid;

	if ((sub_str = strsub_ticks(str)) == NULL)
		return (0);
	if ((*root = parse_backticks(sub_str)) == NULL)
		return (-1);
	free(sub_str);
	fd = set_up_tick_pipe(*root, &child_pid);
	*res = build_str_from_pipe(fd);
	if (close((fd)) == -1)
		return (-1);
	waitpid(child_pid, &fd, 0);
	return (0);
}

int			exec_backticks(char **dst, char *str)
{
	t_tree	*root;
	char	*res;
	int		len;

	if (backtick_sub(str, &root, &res) == -1)
		return (-1);
	*dst = create_res_str(str, res);
	len = ft_strlen(res);
	free_tree(root);
	ft_strdel(&str);
	ft_strdel(&res);
	return (len);
}
