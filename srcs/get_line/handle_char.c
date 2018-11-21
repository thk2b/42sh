/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:26:00 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/20 11:43:13 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int			handle_char(t_line *line, char c)
{
	if (c == '\t')
		return (0);
	if (c == 27)
		return (handle_escape(line));
	if (c == 127)
		return (handle_backspace(line));
	cursor_putchar(c);
	if (c == '\n')
		return (-1);
	line_append(line, c);
	return (0);
}

int			handle_escape(t_line *line)
{
	char	c;

	if (read(0, &c, 1) != 1)
		return (1);
	if (c != 91)
		return (handle_char(line, c));
	if (read(0, &c, 1) != 1)
		return (1);
	if (ft_strchr("ABCD", c))
		return (handle_arrow(line, c));
	return (handle_char(line, c));
}

int			handle_arrow(t_line *line, char c)
{
	if (c == DIR_LEFT)
	{
		if (line_move_left(line))
			return (0);
	}
	else if (c == DIR_RIGHT)
	{
		if (line_move_right(line))
			return (0);
	}
	cursor_move(c);
	return (0);
}

int			handle_backspace(t_line *line)
{
	if (line_delete(line))
		return (0);
	return (cursor_delchar());
}
