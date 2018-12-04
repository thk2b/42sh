/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:15:39 by tkobb             #+#    #+#             */
/*   Updated: 2018/12/03 17:12:07 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

static int	process_command(int *status)
{
	char	*line;
	t_tree	*root;
	int		return_status;

	line = NULL;
	line = ft_readline("\x1b[1;37m""42sh:""\x1b[0m"" $> ", 9, RL_DEFAULT);
	line = history_substitution(line);
	if (!line)
		return (0);
	root = parse(line);
	if (root)
	{
		return_status = exec_node(root, 0);
		free_tree(root);
	}
	else
		return_status = 1;
	free(line);
	*status = return_status;
	return (0);
}

int			execute_non_interactive_shell(char *line, int *status)
{
	t_tree	*root;
	int		return_status;

	if (!line)
		return (1);
	init_shell();
	root = parse(line);
	if (root)
	{
		return_status = exec_node(root, 0);
		free_tree(root);
	}
	else
		return_status = 1;
	free(line);
	*status = return_status;
	teardown_shell();
	return (0);
}

int			main(void)
{
	int		status;
	char	*line;

	line = NULL;
	status = 0;
	if (!isatty(0))
	{
		get_next_line(0, &line);
		execute_non_interactive_shell(line, &status);
		return (status);
	}
	init_shell();
	while (process_command(&status) == 0)
		;
	teardown_shell();
	return (status);
}
