/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:07:47 by acakste           #+#    #+#             */
/*   Updated: 2018/11/21 20:07:47 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int		b_unset(char **av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		rm_local_var(av[i]);
		i++;
	}
	return (0);
}
