/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 20:32:31 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/21 19:28:45 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int		error(char *msg)
{
	if (msg)
	{
		ft_dprintf(2, "%s: %s: %s\n", "42sh", msg, strerror(errno));
	}
	else
	{
		ft_dprintf(2, "%s: %s\n", "42sh", strerror(errno));
	}
	return (errno);
}

int		error_ret(char *msg, int ret)
{
	if (msg)
	{
		ft_dprintf(2, "%s: %s: %s\n", "42sh", msg, strerror(errno));
	}
	else
	{
		ft_dprintf(2, "%s: %s\n", "42sh", strerror(errno));
	}
	return (ret);
}

void	*error_null(char *msg)
{
	if (msg)
	{
		ft_dprintf(2, "%s: %s: %s\n", "42sh", msg, strerror(errno));
	}
	else
	{
		ft_dprintf(2, "%s: %s\n", "42sh", strerror(errno));
	}
	return (NULL);
}
