/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:37:31 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 19:58:10 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int			b_setenv(char **av)
{
	extern char	**environ;

	if (av == NULL || av[0] == NULL || av[1] == NULL)
	{
		ft_printf("usage: setenv VAR [VALUE]\n");
		return (1);
	}
	else if (av[2])
		ft_setenv(av[1], av[2], 1);
	else
		ft_setenv(av[1], NULL, 1);
		// return (1);
	return (0);
}
