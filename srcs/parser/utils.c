/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:21:05 by ale-goff          #+#    #+#             */
/*   Updated: 2018/12/03 16:23:52 by ale-goff         ###   ########.fr       */
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
	if (ft_strequ(str, "|") || ft_strequ(str, "&&") ||
		ft_strequ(str, ">") || ft_strequ(str, "<"))
		return (0);
	return (1);
}

int						is_aggregation(char *s1, char *s2, char *s3)
{
	if (is_number(s1) && !ft_strcmp(s2, ">") && !ft_strcmp(s3, "&"))
	{
		return (1);
	}
	if (!ft_strcmp(s2, ">") && !ft_strcmp(s3, "&"))
	{
		return (1);
	}
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
