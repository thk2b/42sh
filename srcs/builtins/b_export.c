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

static void	print_env_export(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		ft_printf("EXPORT %s\n", environ[i]);
		i++;
	}
}

static char	*scan_argv(char **av)
{
	char	*assignment;
	int		argc;

	argc = 0;
	while (av[argc])
		argc++;
	if (argc == 1)
		return (NULL);
	if (ft_strcmp(av[1], "-p") == 0)
	{
		if (argc == 2)
			return ("-p");
		else if (argc == 3)
			assignment = av[2];
		else
			return (NULL);
	}
	else
		assignment = av[1];
	return (assignment);
}

int		b_export(char **av)
{
	char	*key;
	char	*value;
	char	*assignment;

	if ((assignment = scan_argv(av)) == NULL)
		return (1);
	if (ft_strcmp(assignment, "-p") == 0)
		print_env_export();
	else if (split_assignment(assignment, &key, &value))
	{
		if ((value = get_local_var(assignment)) == NULL)
			return (1);
		if (ft_setenv(assignment, value, 1) || rm_local_var(assignment))
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