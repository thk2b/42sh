/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_resize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 21:32:37 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/13 23:53:36 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_resize(t_line *l)
{
	char	*buf;
	size_t	old_cursor_end;
	size_t	old_end_size;

	old_end_size = l->bufsize - l->cursor.end + 1;
	MCK(buf = (char *)malloc(sizeof(char) * (1 + l->bufsize * 2)), 1);
	ft_memcpy(buf, l->buf, l->cursor.start + 1);
	old_cursor_end = l->cursor.end;
	l->cursor.end += l->bufsize;
	l->bufsize *= 2;
	ft_memcpy(buf + l->cursor.end, l->buf + old_cursor_end, old_end_size);
	free(l->buf);
	l->buf = buf;
	return (0);
}
