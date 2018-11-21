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

static t_var	*g_var[NUM_SLOTS] = {
	 NULL
};

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

char	*get_local_var(char *key)
{
	t_var			*cur;

	cur = find_lst(key);
	while (cur && ft_strcmp(cur->key, key))
		cur = cur->next;
	return ((cur) ? cur->value : NULL); // return a copy of the variable?
}

t_var	*rm_local_var_inst(t_var *cur, char *key)
{
	t_var	*tmp;

	if (!cur)
		return (NULL);
	if (ft_strcmp(cur->key, key) == 0)
	{
		tmp = cur->next;
		free(cur->value);
		free(cur->key);
		free(cur);
		return (tmp);
	}
	cur->next = rm_local_var_inst(cur->next, key);
	return (cur);
}

int		rm_local_var(char *key)
{
	unsigned long	hash;
	t_var			*slot;

	hash = hash_var(key);
	slot = g_var[hash % NUM_SLOTS];
	slot = rm_local_var_inst(slot, key);
	g_var[hash % NUM_SLOTS] = slot;
	return (0);
}

//Should we update the enviornment here?
int		store_local_var(char *key, char *value)
{
	t_var	*cur;
	t_var	*new;
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
	return (0);
}

/*
**	djb2 by Dan Bernstein
*/
unsigned long	hash_var(char *key)
{
	unsigned long hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return (hash);
}
