/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:37:31 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 19:57:24 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int			b_env(char **av)
{
	extern char	**environ;

	if (av[1])
	{
		ft_printf("env: %s: No such file or directory\n", av[1]);
		return (1);
	}
	ft_putstrv(environ);
	return (0);
}
