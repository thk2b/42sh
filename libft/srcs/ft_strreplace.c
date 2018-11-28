/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:13:50 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/27 16:14:14 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strreplace(char *s, char *start, size_t r_len, char *by)
{
	size_t	s_len;
	size_t	e_len;
	size_t	by_len;
	size_t	n_len;
	char	*n;

	s_len = start - s;
	e_len = ft_strlen(s) - r_len - s_len;
	by_len = ft_strlen(by);
	n_len = s_len + by_len + e_len;
	MCK(n = (char*)malloc(sizeof(char) * (n_len + 1)), NULL);
	n[n_len] = '\0';
	ft_strncpy(n, s, s_len);
	ft_strcpy(n + s_len, by);
	ft_strcpy(n + s_len + by_len, start + r_len);
	return (n);
}
