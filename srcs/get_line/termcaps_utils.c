/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:27:03 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/20 11:34:10 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int		puttc(char *name)
{
	char	tname[1024];
	char	buf[32];
	char	*cap;

	ft_bzero(buf, 32);
	ft_bzero(tname, 1024);
	if (tgetent(tname, getenv("TERM")) != 1)
		return (1);
	cap = tgetstr(name, (char**)&buf);
	if (cap)
		ft_putstr(cap);
	return (0);
}

// char	getchar(int fd)
// {
// 	char	c;
// 	ssize_t	nr;

// 	if ((nr = read(fd, &c, 1)))
// 		return (c);
// 	if (nr == -1)
// 		return (error_ret("read", -1));
// 	return (0);
// }
