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
	char		*str;
	int			i;
	int			status;

	if (av[1])
	{
		i = 1;
		status = 0;
		while (av[i])
		{
			str = ft_getenv(av[i++]);
			if (str == NULL)
				status = 1;
			else
				ft_putendl(str);
		}
		return (status);
	}
	ft_putstrv(environ);
	return (0);
}
