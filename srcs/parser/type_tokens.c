/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 20:07:01 by ale-goff          #+#    #+#             */
/*   Updated: 2018/12/01 18:37:42 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void				error_message(char *line)
{
	ft_dprintf(2, "%s: syntax error near: %s\n", "42sh", line);
}

int					skip_to_end_of_line(const char *input, int *p)
{
	while (input[*p] && input[*p] != '\n')
		*p += 1;
	return (END);
}

int					is_op(char *str)
{
	if (ft_strequ(str, "&&") || ft_strequ(str, "||") ||
		ft_strequ(str, "|") || ft_strequ(str, ";"))
		return (1);
	return (0);
}

int					classify_token(char c)
{
	if (is_alpha_numeric(c))
		return (T_ALPHANUM);
	else if (c == '&')
		return (T_AND);
	else if (c == '|')
		return (T_PIPE);
	else if (c == ';')
		return (T_SEMI);
	else if (IS_QU(c))
		return (T_QUOTE);
	else if (IS_SPACE(c))
		return (T_SPACE);
	else if (c == '#')
		return (T_COMMENT);
	else
		return (0);
}

int					is_red(char *input)
{
	if (ft_strequ(input, ">>") || ft_strequ(input, "<") ||
	ft_strequ(input, "<<") || ft_strequ(input, "<<<") ||
	ft_strequ(input, ">>") || ft_strequ(input, ">"))
		return (1);
	return (0);
}
