/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:18:34 by acakste           #+#    #+#             */
/*   Updated: 2018/11/19 10:18:35 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>


int		split_assignment(char *str, char **key, char **value)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	*key = ft_strsub(str, 0, equal - str);
	*value = ft_strdup(equal + 1);
	if (!(*key) || !(*value))
		return (1);
	return (0);
}

int		store_assignments(t_assign *lst)
{
	t_assign	*cur;
	char		*key;
	char		*value;

	cur = lst;
	while (cur)
	{
		split_assignment(cur->value, &key, &value);
		store_local_var(key, value);
		ft_strdel(&key);
		ft_strdel(&value);
		cur = cur->next;
	}
	return (0);
}