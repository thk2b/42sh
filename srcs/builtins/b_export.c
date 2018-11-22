/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:40:04 by acakste           #+#    #+#             */
/*   Updated: 2018/11/21 19:40:05 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int		b_export(char **av)
{
	char	*key;
	char	*value;
	int		argc;

	argc = 0;
	while (av[argc])
		argc++;
	if (argc != 2)
		return (1);
	if (split_assignment(av[1], &key, &value))
	{
		if ((value = get_local_var(av[1])) == NULL)
			return (1);
		if (ft_setenv(av[1], value, 1) || rm_local_var(av[1]))
			return (1);
	}
	else
	{
		if (ft_setenv(key, value, 1))
			return (1);
		ft_strdel(&key);
		ft_strdel(&value);
	}
	return (0);
}