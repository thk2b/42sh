/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var_comp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:28:59 by acakste           #+#    #+#             */
/*   Updated: 2018/11/28 16:28:59 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <local_var.h>

/*
**	djb2 by Dan Bernstein
*/

unsigned long	hash_var(char *key)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *key++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}

t_var			*rm_local_var_inst(t_var *cur, char *key)
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

char			*get_local_var(char *key)
{
	t_var			*cur;

	if (!key)
		return (NULL);
	cur = find_lst(key);
	while (cur && ft_strcmp(cur->key, key))
		cur = cur->next;
	return ((cur) ? cur->value : NULL);
}
