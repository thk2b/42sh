/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:22:53 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/20 18:24:06 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	key_del_backspace(t_rl *rl)
{
	if (!(rl->cx > 0))
		return ;
	ft_memmove(rl->row[rl->cy].buf + rl->cx - 1,
			rl->row[rl->cy].buf + rl->cx, rl->row[rl->cy].bsize - rl->cx + 1);
	rl->row[rl->cy].bsize--;
	key_cursor_left(rl);
}

void	key_del_delete(t_rl *rl)
{
	if (!(rl->cx < rl->row[rl->cy].bsize))
		return ;
	ft_memmove(rl->row[rl->cy].buf + rl->cx, rl->row[rl->cy].buf + rl->cx + 1,
			rl->row[rl->cy].bsize - rl->cx + 1);
	rl->row[rl->cy].bsize--;
}

void	key_del_beg(t_rl *rl)
{
	while (rl->cx)
		key_del_backspace(rl);
}

void	key_del_end(t_rl *rl)
{
	while (rl->cx < rl->row[rl->cy].bsize)
		key_del_delete(rl);
}
