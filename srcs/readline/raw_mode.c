/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:46:42 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/20 18:26:20 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <termios.h>

void	raw_mode_enable(void)
{
	t_termios	raw;

	tcgetattr(STDERR_FILENO, &raw);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDERR_FILENO, TCSAFLUSH, &raw);
}

void	raw_mode_disable(void)
{
	t_termios	raw;

	tcgetattr(STDERR_FILENO, &raw);
	raw.c_lflag |= (ECHO | ICANON | ISIG);
	tcsetattr(STDERR_FILENO, TCSAFLUSH, &raw);
}
