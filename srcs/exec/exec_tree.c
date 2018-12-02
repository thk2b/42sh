/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:10:15 by acakste           #+#    #+#             */
/*   Updated: 2018/12/01 20:38:51 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

t_table		g_op[NUM_OP] = {
	{T_CMD, exec_cmd}, {T_PIPE, exec_pipe}, {T_AND, exec_and},
	{T_OR, exec_or}, {T_SEMI, exec_semi}
};

int			exec_node(t_tree *cur, int use_current_process)
{
	int	i;

	if (!cur)
		return (0);
	i = 0;
	while (i < NUM_OP)
	{
		if (cur->type == g_op[i].type)
			return (g_op[i].f(cur, use_current_process));
		i++;
	}
	return (1);
}

static int	set_up_half_pipe(int fd_use, int fd_close, int stream, t_tree *next)
{
	if (close(fd_close) == -1)
		_exit(1);
	dup2(fd_use, stream);
	if (close(fd_use) == -1)
		_exit(1);
	_exit(exec_node(next, 1));
}

int			exec_pipe(t_tree *curr, int use_curr_proc)
{
	int fd[2];
	int return_status[2];
	int	child_pid[2];

	if (pipe(fd) == -1)
		return (error("pipe"));
	if ((child_pid[0] = fork()) == -1)
		return (error("fork"));
	if (child_pid[0] == 0)
		set_up_half_pipe(fd[1], fd[0], 1, curr->left);
	if (use_curr_proc == 0)
		if ((child_pid[1] = fork()) == -1)
			return (1);
	if (child_pid[1] == 0 || use_curr_proc == 1)
		set_up_half_pipe(fd[0], fd[1], 0, curr->right);
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		return (error("fork"));
	waitpid(child_pid[0], &return_status[0], 0);
	waitpid(child_pid[1], &return_status[1], 0);
	return (return_status[1]);
}
