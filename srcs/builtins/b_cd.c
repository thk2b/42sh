/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:37:31 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/21 20:38:04 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <env.h>

int		b_cd(char **av)
{
	char	*dst;
	char	*curpwd;

	if (av == NULL || av[0] == NULL)
		return (1);
	dst = av[1];
	if (dst == NULL)
	{
		MCK(dst = ft_getenv("HOME"), 1);
	}
	else if (dst[0] == '-')
	{
		MCK(dst = ft_getenv("OLD_PWD"), 1);
	}
	MCK(curpwd = ft_getenv("PWD"), 1);
	if (ft_setenv("OLD_PWD", curpwd, 1))
		;
	if (chdir(dst) == -1)
		return (error("cd"));
	if ((curpwd = getcwd(NULL, 0)) == NULL)
		return (error("getcwd"));
	ft_setenv("PWD", curpwd, 1);
	free(curpwd);
	return (0);
}
