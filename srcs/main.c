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

static int	process_command(int *status)
{
	char	*line;
	// t_tree	*root;
	// int		return_status;

	if (get_line(0, &line))
		return (error("cannot get line"));
	//parser (calls the tokenizer internally) takes a line, and t_tree **root as argument
		//token list should be cleaned inside parser.

	//exex_node(root, 0); track return status.

	//clean the tree, clean line

	//set return status
	return (0);
}

int			main(void)
{
	int		status;

	status = 0;
	init_shell();
	while (process_command(&status) == 0)
		;
	teardown_shell();
	return (status);
}
