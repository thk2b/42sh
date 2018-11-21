/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:38:35 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/20 11:11:48 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_line.h>

char	*line_render(t_line *l)
{
	char	*s;
	size_t	len;
	size_t	start_len;
	size_t	end_len;

	start_len = l->cursor.start;
	end_len = l->bufsize - l->cursor.end;
	len = start_len + end_len;
	MCK(s = (char*)ft_memalloc(sizeof(char) * (len + 1)), NULL);
	ft_memcpy(s, l->buf, start_len);
	ft_memcpy(s + start_len, l->buf + l->cursor.end, end_len);
	return (s);
}
