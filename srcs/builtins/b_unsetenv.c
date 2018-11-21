/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unsetenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:37:31 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 19:58:04 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int			b_unsetenv(char **av)
{
	extern char	**environ;
	int			status;
	int			i;

	if (av == NULL || av[0] == NULL || av[1] == NULL)
		return (1);
	status = 0;
	i = 1;
	while (av[i])
		status = (ft_unsetenv(av[i++]) == 1) || status;
	return (status);
}
