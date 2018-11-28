/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:19:43 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/27 16:36:48 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

#define NOT_QUOTE	!(quote & (Q_SQUOTE | Q_BSLASH))

int		remove_squote(int quote, char *str, int *i)
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

int		remove_dquote(int quote, char *str, int *i)
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

int		remove_bslash(int quote, char *str, int *i)
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

static int	get_lparam(char *str, int start)
{
	int		i;

	i = start;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i - start);
}

static char	*expand_str(char *str, char *param, int start, int lparam)
{
	char	*new;
	char	*expansion;
	char	*prefix;
	char	*suffix;

	expansion = ft_getenv(param);
	if (!expansion)
		expansion = ft_strnew(0);
	else
		expansion = ft_strdup(expansion);
	ft_strdel(&param);
	if (start > 0)
	{
		prefix = ft_strsub(str, 0, start - 1);
		new = ft_strfjoin(prefix, expansion);
	}
	else
		new = expansion;
	suffix = ft_strsub(str, lparam + start, ft_strlen(str + lparam + start));
	new = ft_strfjoin(new, suffix);
	ft_strdel(&str);
	return (new);
}

char		*expand_param(char *str)
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
			quote = remove_squote(quote, str + i, &i);
		else if (str[i] == '\"')
			quote = remove_dquote(quote, str + i, &i);
		else if (str[i] == '\\')
			quote = remove_bslash(quote, str + i, &i);
		else if (NOT_QUOTE && str[i] == '$' && ft_isalnum(str[i + 1]))
		{
			l = get_lparam(str, i + 1);
			str = expand_str(str, ft_strsub(str, i + 1, l), i + 1, l);
		}
		else
			i++;
	}
	return (str);
}

void		token_expand(char **dst, char *str)
{
	if (!str)
		return ;
	if (*str == '~' && (*(str + 1) == '/' || !*(str + 1)))
		str = expand_str(str, ft_strdup("HOME"), 0, 1);
	*dst = expand_param(str);
}
