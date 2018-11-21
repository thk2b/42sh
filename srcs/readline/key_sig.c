/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_sig.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:01:05 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/20 18:24:06 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	key_sig_int(t_rl *rl)
{
	rl->status = -1;
}

void	key_sig_eof(t_rl *rl)
{
	if (!rl->row[0].bsize)
	{
		rl->row[0].buf = ft_strdup("exit");
		rl->row[0].bsize = ft_strlen(rl->row[0].buf);
		rl->status = 1;
	}
}
