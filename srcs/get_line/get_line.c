/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:25:02 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/18 20:34:55 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_line.h>
#include <libft.h>
#include <get_next_line.h>

int		get_line(int fd, char **line)
{
	ft_putstr("<$>");
	return (get_next_line(fd, line));
}
