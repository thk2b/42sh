/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:15:39 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 08:48:43 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

/*
**	Initialize
**	Loop
**		Get line
**		Tokenize
**		Parse
**		Expand
**		Execute
**	Teardown
*/

static int	init_shell(void)
{
	if (path_init())
		return (1);
	return (0);
}

static void	teardown_shell(void)
{
	path_teardown();
}

static int	process_command(void)
{
	char	*line;

	if (get_line(0, line))
		return (error("cannot get line"));
	return (0);
}

int			main(void)
{
	int		status;

	status = 0;
	init_shell();
	while (process_command())
		;
	teardown_shell();
	return (status);
}
