/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 20:03:05 by ale-goff          #+#    #+#             */
/*   Updated: 2018/12/01 19:10:18 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int					is_alpha_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c == '-' || c == '.' || c == '=' || c == '/' || c == '$' || c == '~'
		|| c == '_' || c == ':' || c == ',' ||
		c == '\n' || c == '\'')
		return (1);
	return (0);
}

char				*ft_strdup_range(const char *str, int begin, int end)
{
	char			*duplicate;
	int				dp;
	int				sp;

	if (begin > end)
		return (NULL);
	duplicate = malloc(sizeof(char) * (end - begin + 2));
	sp = begin;
	dp = 0;
	while (sp <= end)
	{
		duplicate[dp] = str[sp];
		dp += 1;
		sp += 1;
	}
	duplicate[dp] = '\0';
	return (duplicate);
}

void				free_append(char **s, char *end)
{
	char			*new;

	new = ft_strcjoin(*s, 0, end);
	free(*s);
	*s = new;
}

int					skip_whitespace(const char *input, int p)
{
	while (input[p] && IS_SPACE(input[p]))
		p += 1;
	return (p);
}
