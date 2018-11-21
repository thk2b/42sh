/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 06:14:19 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 15:58:44 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <ft_printf.h>
#include <libft.h>
#include <unistd.h>
#include <ft_sh.h>

char	*search_cmd(char *exec_name)
{
	char	exists;
	char	*exec_path;

	exists = 0;

	exec_path = path_search(exec_name, &exists);
	if (exec_path)
		return (exec_path);
	ft_dprintf(2, "%s: %s: %s\n", "42sh", exists ? "permission denied" : "command not found", exec_name); // move to errors.c?
	return (NULL);
}

int		exec_cmd(t_tree *tree)
{
	extern char	**environ;
	char		*path;
	int			return_status;

	if (tree->data->assign)
		store_assignments(tree->data->assign);
	expand(tree->data->argv);
	if (tree->data->redirects)
		init_redirects(tree->data->redirects);
	return_status = 0;
	if (builtin(tree->data->argv, &return_status) == 0) // if we execute builtin, stop
		return (return_status);
	if ((path = search_cmd(tree->data->argv[0])) == NULL)
		return (127);
//	signal(SIGCHLD, SIG_DFL); // set SIGCHLD to it's original purpose
	execve(path, tree->data->argv, environ);
	return (error("execve"));
}
