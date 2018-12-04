/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:48:13 by ale-goff          #+#    #+#             */
/*   Updated: 2018/12/03 17:29:50 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int					check_semicolon(char *input)
{
	int			i;

	i = 0;
	while (IS_SEMI(input[i]))
		i++;
	return (i > 1);
}

int					check_redirections(char *input)
{
	int			i;

	i = 0;
	while (input[i] == '>')
		i++;
	if (i > 2)
		return (1);
	i = 0;
	while (input[i] == '<')
		i++;
	if (i > 3)
		return (1);
	i = 0;
	while (input[i])
	{
		if ((IS_REDIRECT_LEFT(input[i]) && IS_REDIRECT_RIGHT(input[i + 1])) ||
			(IS_REDIRECT_RIGHT(input[i]) && IS_REDIRECT_LEFT(input[i + 1])))
			return (1);
		i++;
	}
	return (0);
}

int					error_special(char *input, t_token_lst **head)
{
	int			i;

	i = 0;
	while (input[i])
	{
		if ((head) && (*head) && is_red(input) && is_op((*head)->tail->content))
		{
			error_message(input);
			return (1);
		}
		i++;
	}
	if (check_semicolon(input) || check_redirections(input))
	{
		error_message(input);
		return (1);
	}
	return (0);
}

int					check_errors(char *content, char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!content || !s)
		return (1);
	while (content[i])
	{
		if (IS_OP(content[i]))
			count++;
		i++;
	}
	if ((count > 1) || (is_op(content) && is_op(s)))
	{
		error_message(content);
		return (1);
	}
	return (0);
}

int					check_input(const char *input)
{
	int			i;
	char		*tmp;

	if (!*input)
		return (1);
	tmp = ft_strtrim(input);
	if (!validate_quotes(tmp))
	{
		ft_dprintf(2, "42sh: unexpected EOF : looking for matching quote\n");
		return (1);
	}
	i = 0;
	while (tmp[i])
		i++;
	if (i > 0 && (IS_SEMI(tmp[0]) || IS_RED(tmp[i - 1]) || tmp[i - 1] == '&'
		|| tmp[i - 1] == '|'))
	{
		IS_RED(tmp[i - 1]) || !IS_SEMI(tmp[i - 1]) ? error_message(tmp + i - 1)
		: error_message(";");
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
