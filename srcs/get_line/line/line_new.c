/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 21:36:27 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/13 21:42:48 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"
#include "libft.h"

t_line	*line_new(void)
{
	t_line	*l;

	MCK(l = (t_line*)malloc(sizeof(t_line)), NULL);
	l->bufsize = LINE_BUFSIZE;
	MCK(l->buf = (char*)ft_memalloc(sizeof(char) * (l->bufsize + 1)), NULL);
	l->cursor.start = 0;
	l->cursor.end = l->bufsize - 1;
	if (l->cursor.start + 1 >= l->cursor.end)
	{
		if (line_resize(l))
			return (NULL);
	}
	return (l);
}
