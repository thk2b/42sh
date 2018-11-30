/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 08:26:55 by acakste           #+#    #+#             */
/*   Updated: 2018/11/19 08:26:57 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

t_var	*g_var[NUM_SLOTS] = {
	NULL
};

void	init_local_var(void)
{
	int	i;

	i = 0;
	while (i < NUM_SLOTS)
	{
		g_var[i] = NULL;
		i++;
	}
}

t_var	*find_lst(char *key)
{
	unsigned long	hash;
	t_var			*cur;

	if (!key)
		return (NULL);
	hash = hash_var(key);
	cur = g_var[hash % NUM_SLOTS];
	return (cur);
}

t_var	*create_var_elem(char *key, char *value)
{
	t_var	*new;

	new = (t_var*)malloc(sizeof(t_var));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

int		rm_local_var(char *key)
{
	unsigned long	hash;
	t_var			*slot;

	hash = hash_var(key);
	slot = g_var[hash % NUM_SLOTS];
	slot = rm_local_var_inst(slot, key);
	g_var[hash % NUM_SLOTS] = slot;
	if (ft_getenv(key) == NULL && update_path_map(key))
		return (1);
	return (0);
}

int		store_local_var(char *key, char *value)
{
	t_var			*cur;
	t_var			*new;
	unsigned long	hash;

	if (!key)
		return (1);
	hash = hash_var(key);
	cur = g_var[hash % NUM_SLOTS];
	while (cur && ft_strcmp(cur->key, key))
		cur = cur->next;
	if (cur)
	{
		free(cur->value);
		cur->value = ft_strdup(value);
	}
	else
	{
		new = create_var_elem(key, value);
		new->next = g_var[hash % NUM_SLOTS];
		g_var[hash % NUM_SLOTS] = new;
	}
	if (update_path_map(key))
		return (1);
	return (0);
}
