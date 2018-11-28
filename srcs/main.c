/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:15:39 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/22 20:32:28 by dmendelo         ###   ########.fr       */
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
	if (create_path_map())
		return (1);
	if (init_environ())
		return (1);
	return (0);
}

static void	teardown_shell(void)
{
	delete_path_map();
}

static void	free_assignments(t_assign *lst)
{
	t_assign	*cur;
	t_assign	*tmp;

	cur = lst;
	while (cur)
	{
		ft_strdel(&cur->value);
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
}

static void	free_redirects(t_redirect *lst)
{
	t_redirect	*cur;
	t_redirect	*next;

	cur = lst;
	while (cur)
	{
		ft_strdel(&cur->path);
		next = cur->next;
		free(cur);
		cur = next;
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
		if (root->data->argv)
		{
			i = 0;
			while (root->data->argv[i])
			{
				free(root->data->argv[i]);
				i++;
			}
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

static int	execute_non_interactive_shell(char *line, int *status)
{
	t_tree	*root;
	int		return_status;

	if (!line)
		return (1);
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

int			check_stdin(void)
{

	if (isatty(0))
		return (0);
	return (1);
/*	fd_set			readfds;
	struct timeval	timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
	if (select(1, &readfds, NULL, NULL, &timeout))
	{
		return (1);
	}
	return (0);
	*/
}

int			main(void)
{
	int		status;
	char	*line;

	line = NULL;
	if (check_stdin())
	{
		get_next_line(0, &line);
		init_shell();
		execute_non_interactive_shell(line, &status);
		teardown_shell();
		return (status);
	}
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
