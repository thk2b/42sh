/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:10:15 by acakste           #+#    #+#             */
/*   Updated: 2018/11/18 19:10:16 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

t_table		g_op[NUM_OP] = {
	{T_CMD, exec_cmd}, {T_PIPE, exec_pipe}, {T_AND, exec_and},
	{T_OR, exec_or}, {T_SEMI, exec_semi}
};

int		exec_node(t_tree *cur, int use_current_process)
{
	int	i;

	i = 0;
	while (i < NUM_OP)
	{
		if (cur->type == g_op[i].type)
			return (g_op[i].f(cur, use_current_process));
		i++;
	}
	return (1);
}

int		exec_semi(t_tree *tree, int use_current_process)
{
	int return_status[2];
	int	child_pid[2];

	if ((child_pid[0] = fork()) == -1)
		return (1);
	if (child_pid[0] == 0)
		exec_node(tree->left, 1);
	if (use_current_process == 0)
		if ((child_pid[1] = fork()) == -1)
			return (1);
	if (child_pid[1] == 0 || use_current_process == TRUE)
		exec_node(tree->right, 1);
	waitpid(child_pid[0], &return_status[0], 0);
    waitpid(child_pid[1], &return_status[1], 0);
    return (return_status[1]);
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
		return (1);
	if ((child_pid[0] = fork()) == -1)
		return (1);
	if (child_pid[0] == 0)
		set_up_half_pipe(fd[1], fd[0], 1, curr->left);
	if (use_curr_proc == 0)
			if ((child_pid[1] = fork()) == -1)
				return (1);
	if (child_pid[1] == 0 || use_curr_proc == 1)
		set_up_half_pipe(fd[0], fd[1], 0, curr->right);
	if (close(fd[0]) == -1 || close(fd[1] == -1))
		_exit(1);
    waitpid(child_pid[0], &return_status[0], 0);
    waitpid(child_pid[1], &return_status[1], 0);
    return (return_status[1]);
}

//What will happen if the first exec fails. What happens to the use_current_process process? Will it terminate?
int		exec_and(t_tree *tree, int use_current_process)
{
	int return_status[2];
	int	child_pid[2];

	if ((child_pid[0] = fork()) == -1)
		return (1);
	if (child_pid[0] == 0)
		exec_node(tree->left, 1);
	waitpid(child_pid[0], &return_status[0], 0);
	if (return_status[0] != 0)
		return (return_status[0]);
	if (use_current_process == 0)
		if ((child_pid[1] = fork()) == -1)
			return (1);
	if (child_pid[1] == 0 || use_current_process == TRUE)
		exec_node(tree->right, 1);
    waitpid(child_pid[1], &return_status[1], 0);
    return (return_status[1]);
}

int		exec_or(t_tree *tree, int use_current_process)
{
	int return_status[2];
	int	child_pid[2];

	if ((child_pid[0] = fork()) == -1)
		return (1);
	if (child_pid[0] == 0)
		exec_node(tree->left, 1);
	waitpid(child_pid[0], &return_status[0], 0);
	if (return_status[0] == 0)
		return (return_status[0]);
	if (use_current_process == 0)
		if ((child_pid[1] = fork()) == -1)
			return (1);
	if (child_pid[1] == 0 || use_current_process == TRUE)
		exec_node(tree->right, 1);
    waitpid(child_pid[1], &return_status[1], 0);
    return (return_status[1]);
}

int		exec_cmd(t_tree *tree)
{
	if (tree->cmd->assign)
		//do all the assignments
	if (tree->cmd->redirects)
		//do all the redirects
	//search_simple_cmd();
}

/*
int     exec_pipe(t_tree *curr, int use_curr_proc)
{
    int fd[2];
    int return_status[2];
    int child_pid[2];

    if (pipe(fd) == -1) 
        return (1);
    if ((child_pid[0] = fork()) == -1)
        return (1);
    if (child_pid[0] == 0)
    {
        if (close(fd[0]) == -1)
            _exit(1);
        dup2(fd[1], 1);
        if (close(fd[1]) == -1)
            _exit(1);
        _exit(exec_node(curr->left, 1));
    }
    if (use_curr_proc == 0)
        if ((child_pid[1] = fork()) == -1)
            return (1);
    if (child_pid[1] == 0 || use_curr_proc == 1)
    {
        if (close(fd[1]) == -1)
            _exit(1);
        dup2(fd[0], 0);
        if (close(fd[0]) == -1)
            _exit(1);
        _exit(exec_node(curr->right, 1));
    }
    if (close(fd[0]) == -1)
        _exit(1);
    if (close(fd[1]) == -1)
        _exit(1);
    waitpid(child_pid[0], &return_status[0], 0);
    waitpid(child_pid[1], &return_status[1], 0);
    return (return_status[1]);
}*/
