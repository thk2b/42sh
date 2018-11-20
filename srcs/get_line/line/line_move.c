/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 21:40:20 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/14 11:24:49 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

int	line_move_right(t_line *l)
{
	if (l->cursor.end == l->bufsize - 1)
		return (1);
	l->buf[l->cursor.start++] = l->buf[l->cursor.end++];
	return (0);
}

int	line_move_left(t_line *l)
{
	if (l->cursor.start == 0)
		return (1);
	l->buf[--l->cursor.end] = l->buf[--l->cursor.start];
	l->buf[l->cursor.start] = '\0';
	return (0);
}
