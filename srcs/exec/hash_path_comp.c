/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_path_comp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:29:28 by acakste           #+#    #+#             */
/*   Updated: 2018/11/28 18:29:29 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <dirent.h>

extern t_var	*g_path[];

int						create_path_map(void)
{
	char			*path_var;
	char			**path_arr;
	struct dirent	*dp;
	DIR				*dirp;
	int				i;

	if ((path_var = ft_getenv("PATH")) == NULL)
		return (1);
	if ((path_arr = ft_strsplit(path_var, ':')) == NULL && path_arr)
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
	}
	ft_strvdel(path_arr);
	return (0);
}

void					delete_path_map(void)
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

char					*get_cmd_path(char *key)
{
	t_var			*cur;

	if (!key)
		return (NULL);
	cur = find_path_lst(key);
	while (cur && ft_strcmp(cur->key, key))
	{
		cur = cur->next;
	}
	return ((cur) ? cur->value : NULL);
}

t_var					*create_path_elem(char *key, char *value)
{
	t_var	*new;

	new = (t_var*)malloc(sizeof(t_var));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}
