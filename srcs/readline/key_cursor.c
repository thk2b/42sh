/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:24:39 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/20 18:24:06 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	key_cursor_left(t_rl *rl)
{
	if (!(rl->cx > 0))
		return ;
	ft_putstr(tgetstr("le", NULL));
	rl->cx--;
}

void	key_cursor_right(t_rl *rl)
{
	if (!(rl->cx <= rl->row[rl->cy].bsize))
		return ;
	ft_putstr(tgetstr("nd", NULL));
	rl->cx++;
}

void	key_cursor_beg(t_rl *rl)
{
	while (rl->cx)
		key_cursor_left(rl);
}

void	key_cursor_end(t_rl *rl)
{
	while (rl->cx < rl->row[rl->cy].bsize)
		key_cursor_right(rl);
}
