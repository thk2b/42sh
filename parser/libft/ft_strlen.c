/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 16:03:09 by ale-goff          #+#    #+#             */
/*   Updated: 2018/10/22 19:23:01 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen(const char *str)
{
	char *ptr;

	ptr = (char *)str;
	while (1)
	{
		if (!*(ptr++))
			break ;
		if (!*(ptr++))
			break ;
		if (!*(ptr++))
			break ;
		if (!*(ptr++))
			break ;
	}
	return ((ptr - 1) - str);
}
