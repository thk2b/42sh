/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:58:36 by acakste           #+#    #+#             */
/*   Updated: 2018/11/28 16:58:37 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int	init_environ(void)
{
	extern char	**environ;
	char		**env_cpy;

	env_cpy = ft_strv_dup(environ);
	if (!env_cpy)
		return (1);
	environ = env_cpy;
	return (0);
}

int	init_shell(void)
{
	if (create_path_map())
		return (1);
	if (init_environ())
		return (1);
	init_local_var();
	return (0);
}

