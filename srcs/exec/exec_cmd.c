/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 06:14:19 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 07:28:43 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <ft_printf.h>
#include <libft.h>
#include <unistd.h>

char	*search_cmd(char *exec_name)
{
	char	exists;
	char	*exec_path;

	exists = 0;

	exec_path = path_search(exec_name, &exists);
	if (exec_path)
		return (exec_path);
	ft_printf("%s: %s: %s\n", "42sh", exists ? "permission denied" : "command not found", exec_name); // move to errors.c?
	return (NULL);
}

int		exec_cmd(t_tree *tree)
{
	extern char	**environ;
	char		*path;

	// if (tree->data->assign)
		//do all the assignments
	// if (tree->data->redirects)
		//do all the redirects
	if ((path = search_cmd(tree->data->argv[0])) == NULL)
		return (127);
	execve(path, tree->data->argv, environ);
	return (error("execve"));
}
