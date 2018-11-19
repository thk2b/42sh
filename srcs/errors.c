/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 20:32:31 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 06:54:12 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int		error(char *msg)
{
	if (msg)
	{
		ft_printf("%s: %s:\n", "42sh", msg, strerror(errno));
	}
	else
	{
		ft_printf("%s: %s\n", "42sh", msg, strerror(errno));
	}
	return (errno);
}

int		error_ret(char *msg, int ret)
{
	if (msg)
	{
		ft_printf("%s: %s:\n", "42sh", msg, strerror(errno));
	}
	else
	{
		ft_printf("%s: %s\n", "42sh", msg, strerror(errno));
	}
	return (ret);
}

void	*error_null(char *msg)
{
	if (msg)
	{
		ft_printf("%s: %s:\n", "42sh", msg, strerror(errno));
	}
	else
	{
		ft_printf("%s: %s\n", "42sh", msg, strerror(errno));
	}
	return (NULL);
}
