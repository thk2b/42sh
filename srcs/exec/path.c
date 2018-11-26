/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 06:18:30 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/22 08:55:45 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <env.h>
#include <libft.h>
#include <unistd.h>
#include <limits.h>

static char	**g_path;

int			path_init(void)
{
	extern char	**environ;
	char		*path_str;

	if ((path_str = ft_getenv("PATH")) == NULL)
		return (0);
	if ((g_path = ft_strsplit(path_str ,':')) == NULL && g_path)
		return (error("no memory"));
	return (0);
}

static int	is_executable(char *path, char *exists)
{
	if (access(path, F_OK) == 0)
		return ((*exists = 1));
	return (access(path, X_OK) == 0);
}

static void	build_exec_path(char *dst, char *path, char *name)
{
	size_t	len;

	ft_strncpy(dst, path, PATH_MAX - 1);
	len = ft_strlen(path);
	ft_strncpy(dst + len, "/", PATH_MAX - len - 1);
	ft_strncpy(dst + len + 1, name, PATH_MAX - len - 2);
	dst[PATH_MAX] = '\0';
}

char		*path_search(char *exec_name, char *exists)
{
	char	exec_path[PATH_MAX + 1];
	size_t	i;

	if (ft_strchr(exec_name, '/'))
	{
		if (is_executable(exec_name, exists))
			return (ft_strdup(exec_name));
		return (NULL);
	}
	i = 0;
	while (g_path[i])
	{
		build_exec_path(exec_path, g_path[i], exec_name);
		if (is_executable(exec_path, exists))
			return (ft_strdup(exec_path));
		i++;
	}
	return (NULL);
}

void		path_teardown(void)
{
	ft_strvdel(g_path);
}
