/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:42:03 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/27 15:36:22 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

/*
**	Searches for a builtin with name == av[0]
**	Executes it and sets the return status
**	Returns 1 if a builtin was found, 0 if not
*/

static t_builtin	g_builtins[] = {
	{"cd", b_cd},
	{"exit", b_exit},
	{"echo", b_echo},
	{"env", b_env},
	{"setenv", b_setenv},
	{"unsetenv", b_unsetenv},
	{"export", b_export},
	{"unset", b_unset},
	{"history", history_builtin},
	{NULL, NULL}
};

int		builtin(t_cmd *cmd, int *return_status)
{
	int	i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(g_builtins[i].name, cmd->argv[0]) == 0)
		{
			if (cmd->redirects)
				init_redirects(cmd->redirects);
			*return_status = g_builtins[i].fn(cmd->argv);
			if (cmd->redirects)
				reset_redirects(cmd->redirects);
			return (0);
		}
		i++;
	}
	return (1);
}
