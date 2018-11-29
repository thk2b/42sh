/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 23:23:59 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/22 13:19:38 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <path.h>
#include <libft.h>

char	**ft_getenvp(const char *name)
{
	extern char **environ;
	int			i;
	char		*end;
	int			len;

	i = 0;
	len = ft_strlen(name);
	while (environ[i])
	{
		if ((end = ft_strchr(environ[i], '=')) == NULL)
			;
		if (end - environ[i] != len)
			;
		else if (ft_strncmp(environ[i], name, end - environ[i]) == 0)
			return (environ + i);
		i++;
	}
	return (NULL);
}

int		ft_setenv(const char *name, const char *value, int overwrite)
{
	char	**current;
	char	*str;

	current = ft_getenvp(name);
	if (current && overwrite == 0)
		return (-1);
	MCK(str = ft_strcjoin(name, '=', value), -1);
	if (current == NULL)
		return (ft_putenv(str));
	if (ft_strcmp(name, "PATH") == 0)
	{
		delete_path_map();
		if (create_path_map())
			return (-1);
	}
	free(*current);
	return ((*current = str) != 0);
}
