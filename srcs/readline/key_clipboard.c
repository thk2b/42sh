/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_clipboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:29:32 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/20 18:24:07 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

char						*g_clipboard = NULL;

void	key_copy(t_rl *rl)
{
	ft_strdel(&g_clipboard);
	g_clipboard = ft_strdup(rl->row[rl->cy].buf);
}

void	key_paste(t_rl *rl)
{
	ft_strdel(&rl->row[rl->cy].buf);
	rl->row[rl->cy].buf = ft_strdup(g_clipboard);
	rl->row[rl->cy].bsize = ft_strlen(rl->row[rl->cy].buf);
	rl->cx = rl->row[rl->cy].bsize;
}
