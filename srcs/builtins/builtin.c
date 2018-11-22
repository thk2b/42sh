/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:42:03 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 16:36:59 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

/*
**	Searches for a builtin with name == av[0]
**	Executes it and sets the return status
**	Returns 1 if a builtin was found, 0 if not
*/

int		builtin(char **av, int *return_status)
{
	static t_builtin	builtins[] = {
		{"cd", b_cd},
		{"exit", b_exit},
		{"echo", b_echo},
		{"env", b_env},
		{"setenv", b_setenv},
		{"unsetenv", b_unsetenv},
		{"export", b_export},
		{"unset", b_unset},
		{NULL, NULL}
	};
	int					i;

	i = 0;
	while (builtins[i].name)
	{
		if (ft_strcmp(builtins[i].name, av[0]) == 0)
		{
			*return_status = builtins[i].fn(av);
			return (0); // exit or return ? we use child for builtins now
		}
		i++;
	}
	return (1);
}
