/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <acakste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:28:04 by acakste           #+#    #+#             */
/*   Updated: 2018/11/27 19:49:58 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <limits.h>
#include <dirent.h>

t_var	*g_path[NUM_PATH_SLOTS] = {
	NULL
};

/*
**	djb2 by Dan Bernstein
*/

static unsigned long	hash_func(char *key)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *key++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}

static int				is_executable(char *path, char *exists)
{
	if (access(path, F_OK) == 0)
		return ((*exists = 1));
	return (access(path, X_OK) == 0);
}

t_var					*find_path_lst(char *key)
{
	unsigned long	hash;
	t_var			*cur;

	if (!key)
		return (NULL);
	hash = hash_func(key);
	cur = g_path[hash % NUM_PATH_SLOTS];
	return (cur);
}

int						store_cmd_path(char *key, char *value)
{
	t_var			*cur;
	t_var			*new;
	unsigned long	hash;

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

char					*path_search(char *exec_name, char *exists)
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
