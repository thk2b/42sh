/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <acakste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:28:04 by acakste           #+#    #+#             */
/*   Updated: 2018/11/28 10:40:22 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <limits.h>
#include <dirent.h>

t_var 	*g_path[NUM_PATH_SLOTS] = {
	NULL
};

/*
**	djb2 by Dan Bernstein
*/
static	unsigned long	hash_func(char *key)
{
	unsigned long hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return (hash);
}

static int	is_executable(char *path, char *exists)
{
	if (access(path, F_OK) == 0)
		return ((*exists = 1));
	return (access(path, X_OK) == 0);
}

t_var	*create_path_elem(char *key, char *value)
{
	t_var	*new;

	new = (t_var*)malloc(sizeof(t_var));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

t_var	*find_path_lst(char *key)
{
	unsigned long	hash;
	t_var			*cur;

	if (!key)
		return (NULL);
	hash = hash_func(key);
	cur = g_path[hash % NUM_PATH_SLOTS];
	return (cur);
}

char	*get_cmd_path(char *key)
{
	t_var			*cur;

	if (!key)
		return (NULL);
	cur = find_path_lst(key);
	while (cur && ft_strcmp(cur->key, key))
	{
		cur = cur->next;
	}
	return ((cur) ? cur->value : NULL); // return a copy of the variable?
}

int		store_cmd_path(char *key, char *value)
{
	t_var	*cur;
	t_var	*new;
	unsigned long hash;

	if (!key)
		return (1);
	hash = hash_func(key);
	cur = g_path[hash % NUM_PATH_SLOTS];
	while (cur && ft_strcmp(cur->key, key))
		cur = cur->next;
	if (cur)
	{
		free(cur->value);
		cur->value = ft_strdup(value);
	}
	else
	{
		new = create_path_elem(key, value);
		new->next = g_path[hash % NUM_PATH_SLOTS];
		g_path[hash % NUM_PATH_SLOTS] = new;
	}
	return (0);
}

int			create_path_map(void)
{
	char			*path_var;
	char			**path_arr;
	struct dirent	*dp;
	DIR				*dirp;
	int				i;

	if ((path_var = ft_getenv("PATH")) == NULL)
		return (1);
	if ((path_arr = ft_strsplit(path_var ,':')) == NULL && path_arr) // why && g_path?
		return (error("no memory"));
	i = -1;
	while (path_arr[++i])
	{
		if ((dirp = opendir(path_arr[i])) == NULL)
			continue ;
		while ((dp = readdir(dirp)) != NULL)
			store_cmd_path(dp->d_name, path_arr[i]);
		if (closedir(dirp) == -1)
			return (1);
		// i++;
	}
	ft_strvdel(path_arr);
	return (0);
}

void		delete_path_map(void)
{
	int		i;
	t_var	*cur;
	t_var	*tmp;

	i = 0;
	while (i < NUM_PATH_SLOTS)
	{
		cur = g_path[i];
		while (cur)
		{
			tmp = cur->next;
			ft_strdel(&cur->key);
			ft_strdel(&cur->value);
			free(cur);
			cur = tmp;
		}
		g_path[i] = NULL;
		i++;
	}
}

//get executable path
char		*path_search(char *exec_name, char *exists)
{
	char	*exec_path;
	char	*full_path;

	if (ft_strchr(exec_name, '/'))
	{
		if (is_executable(exec_name, exists))
			return (ft_strdup(exec_name));
		return (NULL);
	}
	if ((exec_path = get_cmd_path(exec_name)) == NULL)
		return (NULL);
	full_path = ft_strcjoin(exec_path, '/', exec_name);
	return (full_path);
}
