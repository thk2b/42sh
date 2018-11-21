/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_newline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 17:38:22 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/20 18:24:06 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	key_newline(t_rl *rl)
{
	rl->quote_status &= ~Q_BSLASH;
	rl_row_insert(rl, NULL);
	rl->cx = 0;
	rl->cy++;
	ft_putstr(tgetstr("do", NULL));
	ft_putstr(tgetstr("cr", NULL));
	ft_putstr("> ");
}
