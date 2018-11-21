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


static void	free_tree(t_tree *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	if (root->data)
		free(root->data);
	free(root);
}

static int	process_command(int *status)
{
	char	*line;
	t_tree	*root;
	int		return_status;

	line = NULL;
	ft_printf("$>");
	if (get_next_line(0, &line) != 1) // get_line
		return (1);// theo this makes it weird --> error("cannot get line")
	//parser (calls the tokenizer internally) takes a line, and t_tree **root as argument
		//token list should be cleaned inside parser.
	root = parse(line);
	if (root)
	{
		ft_printf("execute\n");
		//exex_node(root, 0); track return status.
		return_status = exec_node(root, 0);
		//clean the tree, clean line
		free_tree(root);
	}
	else
		return_status = 1;
	//set return status
	*status = return_status;
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
