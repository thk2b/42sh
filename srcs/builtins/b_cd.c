/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:37:31 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/23 08:24:38 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <env.h>

static int	special_cases(char **dst)
{
	if (*dst == NULL)
	{
		MCK(*dst = ft_getenv("HOME"), 1);
	}
	else if ((*dst)[0] == '-')
	{
		if (((*dst) = ft_getenv("OLDPWD")) == NULL)
		{
			ft_dprintf(2, "%s: OLDPWD not set\n", "42sh");
			return (1);
		}
		ft_printf("%s\n", (*dst));
	}
	return (0);
}

int			b_cd(char **av)
{
	char	*dst;
	char	*curpwd;

	if (av == NULL || av[0] == NULL)
		return (1);
	dst = av[1];
	if (special_cases(&dst))
		return (1);
	MCK(curpwd = ft_getenv("PWD"), 1);
	if (ft_setenv("OLDPWD", curpwd, 1))
		;
	if (chdir(dst) == -1)
		return (error("cd"));
	if ((curpwd = getcwd(NULL, 0)) == NULL)
		return (error("getcwd"));
	ft_setenv("PWD", curpwd, 1);
	free(curpwd);
	return (0);
}
