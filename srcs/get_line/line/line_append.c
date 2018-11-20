/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 21:38:16 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/13 21:39:31 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

int	line_append(t_line *l, char c)
{
	l->buf[l->cursor.start++] = c;
	if (l->cursor.start == l->cursor.end)
	{
		if (line_resize(l))
			return (1);
	}
	return (0);
}
