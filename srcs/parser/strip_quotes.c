/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 07:07:58 by acakste           #+#    #+#             */
/*   Updated: 2018/11/30 07:07:59 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

static int		strip_squote(int quote, char *str, int *i)
{
	if (!(quote & (Q_BSLASH | Q_DQUOTE)))
	{
		ft_strcpy(str, str + 1);
		quote ^= Q_SQUOTE;
	}
	else
	{
		quote &= ~Q_BSLASH;
		*i = *i + 1;
	}
	return (quote);
}

static int		strip_dquote(int quote, char *str, int *i)
{
	if (!(quote & (Q_BSLASH | Q_SQUOTE)))
	{
		ft_strcpy(str, str + 1);
		quote ^= Q_DQUOTE;
	}
	else
	{
		quote &= ~Q_BSLASH;
		*i = *i + 1;
	}
	return (quote);
}

static int		strip_bslash(int quote, char *str, int *i)
{
	if ((!(quote & (Q_BSLASH | Q_SQUOTE))
				|| ((quote & Q_DQUOTE) && ft_strchr("\\\"\n", *str + 1))))
	{
		ft_strcpy(str, str + 1);
		quote |= Q_BSLASH;
	}
	else
	{
		quote &= ~Q_BSLASH;
		*i = *i + 1;
	}
	return (quote);
}

int		strip_str_quotes(char *str)
{
	int		i;
	int		quote;
	int		l;

	i = 0;
	quote = 0;
	l = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quote = strip_squote(quote, str + i, &i);
		else if (str[i] == '\"')
			quote = strip_dquote(quote, str + i, &i);
		else if (str[i] == '\\')
			quote = strip_bslash(quote, str + i, &i);
		else
			i++;
	}
	return (quote & Q_SQUOTE);
}

int				strip_quotes(t_nodes *tokens)
{
	t_nodes *cur;

	cur = tokens;
	while (cur)
	{
		strip_str_quotes(cur->content);
		cur = cur->next;
	}
	return (0);
}
