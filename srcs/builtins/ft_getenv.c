/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 23:21:17 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/22 13:34:09 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include <unistd.h>

char		*ft_getenv(const char *name)
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
			return (end + 1);
		i++;
	}
	return (NULL);
}
