/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:15:39 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/22 10:21:19 by pdeguing         ###   ########.fr       */
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


static int	init_environ(void)
{
	extern char	**environ;
	char		**env_cpy;

	env_cpy = ft_strv_dup(environ);
	if (!env_cpy)
		return (1);
	environ = env_cpy;
	return (0);
}

static int	init_shell(void)
{
	if (path_init())
		return (1);
	if (init_environ())
		return (1);
	return (0);
}

static void	teardown_shell(void)
{
	path_teardown();
}

static void	free_assignments(t_assign *lst)
{
	t_assign	*cur;

	cur = lst;
	while (cur)
	{
		ft_strdel(&cur->value);
		free(cur);
		cur = cur->next;
	}
}

static void	free_redirects(t_redirect *lst)
{
	t_redirect	*cur;

	cur = lst;
	while (cur)
	{
		ft_strdel(&cur->path);
		free(cur);
		cur = cur->next;
	}
}

static void	free_tree(t_tree *root)
{
	int			i;

	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	if (root->data)
	{
		i = 0;
		while (root->data->argv[i])
		{
			free(root->data->argv[i]);
			i++;
		}
		free(root->data->argv);
		free_assignments(root->data->assign);
		free_redirects(root->data->redirects);
		free(root->data);
	}
	free(root);
}

static int	process_command(int *status)
{
	char	*line;
	t_tree	*root;
	int		return_status;

	line = NULL;
	line = ft_readline("\x1b[1;37m""42sh:""\x1b[0m"" $> ", 9, RL_DEFAULT);
	//parser (calls the tokenizer internally) takes a line, and t_tree **root as argument
		//token list should be cleaned inside parser.
	if (!line)
		return (0);
	root = parse(line);
	if (root)
	{
		//exex_node(root, 0); track return status.
		return_status = exec_node(root, 0);
		//clean the tree, clean line
		free_tree(root);
	}
	else
		return_status = 1;
	//set return status
	free(line);
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

/*
**	TODO
**	try assignments and redirects. Any leaks?
*/
