/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 20:39:48 by tkobb             #+#    #+#             */
/*   Updated: 2018/12/01 19:58:41 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>
#include <limits.h>

int	ft_vdprintf(int fd, const char *fmt, va_list ap)
{
	int		len;
	size_t	num_written;
	char	*tmp;

	if (!fmt || !*fmt)
		return (0);
	len = ft_vasprintf(&tmp, fmt, ap);
	num_written = write(fd, tmp, len);
	free(tmp);
	return ((int)num_written);
}

int	ft_dprintf(int fd, const char *fmt, ...)
{
	va_list	ap;
	size_t	num_written;

	if (!fmt || !*fmt)
		return (0);
	va_start(ap, fmt);
	num_written = ft_vdprintf(fd, fmt, ap);
	va_end(ap);
	return ((int)num_written);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	size_t	num_written;

	if (!fmt || !*fmt)
		return (0);
	va_start(ap, fmt);
	num_written = ft_vdprintf(1, fmt, ap);
	va_end(ap);
	return ((int)num_written);
}
