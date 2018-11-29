/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:21:05 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/28 18:55:20 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int						get_ptr_len(char **s)
{
	int					p;

	if (!s)
		return (0);
	p = 0;
	while (s[p])
		p++;
	return (p);
}

void					free_2d(char **s)
{
	int					p;

	p = 0;
	while (s[p])
	{
		free(s[p]);
		p += 1;
	}
	free(s);
}

int						is_word(char *str)
{
	if (ft_strchr(str, '|') || ft_strchr(str, '&') ||
		ft_strchr(str, '>') || ft_strchr(str, '<'))
		return (0);
	return (1);
}

int						is_aggregation(char *s1, t_nodes *prev)
{
	if (prev)
		if (!ft_strcmp(s1, "&") && !ft_strcmp(prev->content, ">"))
			return (1);
	return (0);
}

int						is_assignment_word(char *s)
{
	int					p;
	int					assignment;

	assignment = 0;
	if (s && (s[0] == '=' || ft_isdigit(s[0])))
		return (0);
	p = 0;
	while (s[p])
	{
		if (!IS_VALID_CHAR(s[p]))
			return (0);
		else if (s[p] == '=')
			assignment = 1;
		p += 1;
	}
	if (assignment)
		return (1);
	return (0);
}
