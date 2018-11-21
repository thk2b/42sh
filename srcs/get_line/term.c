/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 09:47:53 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/20 11:38:23 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <termios.h>

int		term_init(void)
{
	struct termios	t;

	if (TERMCAPS_ENABLED == 0)
		return (0);
	if (tcgetattr(0, &t) == -1)
		return (error("tcgetattr"));
	t.c_lflag &= ~ECHO;
	t.c_lflag &= ~ICANON;
	if (tcsetattr(0, TCIFLUSH, &t))
		return (error("tcsetattr"));
	return (0);
}

void	term_reset(void)
{
	struct termios	t;

	if (tcgetattr(0, &t) == -1)
		return ((void)error("tcgetattr"));
	t.c_lflag &= (ECHO | ICANON);
	if (tcsetattr(0, TCIFLUSH, &t))
		return ((void)error("tcsetattr"));
}
